import numpy as np
import run_command as rc
import bin_info2 as BI
import analyze_differ as ad
from LT.datafile import dfile
import argparse as AG
import sys
from sys import argv
import os
import shutil as SU

dtr = np.pi/180.

#----------------------------------------------------------------------
def check_dir(current_dir):
    # create output directory (if necessary)
    try:
        os.mkdir(current_dir)
        print "created : ", current_dir
    except:
        msg = sys.exc_info()[1]
        if msg.errno == 17 :
            print current_dir, " exists, will use it "
        else:
            print "check_dir problem : ", msg
            sys.exit()
# done

#User Input
pm_set = int(sys.argv[1])
model = sys.argv[2]
data_set = int(sys.argv[3])

#Code usage example: ipython run_differ_general_v2.py 80 fsi 1

#average kinematics directory for avg. kin with the nominal cut settings
avg_kin_dir = '../../../Deep_CrossSections/average_kinematics/Em_nom40MeV/'   #'./avg_kin_dir/'
results_dir = './kin_syst_results/'

#create input/output filenames for average kinematics to be read/ to write out systematics results
if pm_set == 80:
   input_fname = 'pm%i_%s_norad_avgkin.txt'%(pm_set, model)              #average kinematics file
   input_file = avg_kin_dir+input_fname  
   output_file = results_dir+'pm%i_%s_results.txt'%(pm_set, model)       #results file where derivatives are written
else:
   input_fname = 'pm%i_%s_norad_avgkin_set%i.txt'%(pm_set, model, data_set)
   input_file = avg_kin_dir+input_fname
   output_file = results_dir+'pm%i_%s_set%i_results.txt'%(pm_set, model, data_set)


#Clean summary files (since they open in append mode inside the loop, we do not want to append past data)
fsumin = open('./summary_files/SummaryInput_pm%i_%s_set%i.txt'%(pm_set, model, data_set), 'w').close()
fsumout = open('./summary_files/SummaryOutput_pm%i_%s_set%i.txt'%(pm_set, model, data_set), 'w').close()

#Create Summary table to write derivatives for each (Pm, thnq) bin
#This file will be used in analyze_differ.py (by write_table() function), but it must be passed to get_sig_tot() first
ftable_name= './summary_files/DervTable_pm%i_%s_set%i.txt'%(pm_set, model, data_set)
ftable_out = open(ftable_name, 'w')
ftable_out.write('#This table containes the kinematics derivatives, where ds_dkin is the derivative of the cross section\n')
ftable_out.write('#with respect to the kinematic variable in units of %/mrad or %/MeV\n')
ftable_out.write('#There are also the relative systematic errors of individual kinematic variables, and the total error added in quadrature\n')
ftable_out.write('#to see which is the dominant source of the systematics errors\n')

ftable_out.write('#!ib[i,0]/  pm_bin[f,1]/   thnq_bin[f,2]/   ds_dthe[f,3]/   ds_dphe[f,4]/   ds_def[f,5]/   ds_dthp[f,6]/   ds_dphp[f,7]/  ds_dthb[f,8]/   ds_dphb[f,9]/    ds_dE[f,10]/    sig_the[f,11]/   sig_phe[f,12]/   sig_ef[f,13]/   sig_thp[f,14]/   sig_php[f,15]/  sig_thb[f,16]/   sig_phb[f,17]/    sig_E[f,18]/    sig_tot[f,19]/ \n')
ftable_out.close()


#Make a copy of the avg. kin. file
input_copy = input_fname.replace('.txt', '_systematics.txt')
print("CMD: cp "+input_file+" ./"+input_copy)
os.system("cp "+input_file+" ./"+input_copy)
kin_file = dfile(input_copy)


#file to write input specectrometer kinematics for each (Pm, thnq) bin
#Only used temporarily for that bin, as it is overwritten when the
#next bin is read
differ_file = 'differ.in'

kin_file.add_key('tot_err')  #add new header to store total systematic error per bin
#get average of cos(phi_pq)
cont = np.array( kin_file.get_data('cont') )  #2d bin content
cphi = np.array( kin_file.get_data('cos_phi') )
cphi_av = np.average(cphi, weights=(cont>0))  #average ONLY over non-zero bin content
print('cos_phi average=',cphi_av)
phi_off = 0.
if cphi_av >= 0 :
   phi_off = np.pi

#Loop over 2D (Pm, thnq) bins to get avg. kin for each bin
for ik, ka in enumerate(kin_file.data):
   
   cont = ka['cont']       #2d bin content
   ib = ka['i_b']          #2d bin
   Ei = ka['Ei']           #Avg. incident energy (MeV) / kinematic bin
   Ef = Ei - ka['omega']   #Avg. final electron energy (MeV) / kinematic bin
   pm_bin = ka['yb']     #pm_bin center value (bin center +/- 20 MeV)
   thnq_bin = ka['xb']   #theta_nq bin center value (bin center +/- 5 deg) 
       
   
   ftable_bin = np.array([ib, pm_bin, thnq_bin])   #array with bin info to pass to write_table() function in analyze_differ.py

   #create differ input file name
   outf = open(differ_file,"w")
   outf.write('theta_e, phi_e, final electron energy, second line:step sizes in mr and MeV \n')
   l = '%f , 0., %f \n'%(ka['th_e'], Ef)
   outf.write(l)
   outf.write('1.,1.,0.1\n')
   outf.write('theta_p, phi_p (dont change sign for other side) theta=hor, phi = vert \n')
   
   # calculate php for the proton. Use the average value of phi
   # an offst of pi (or 180 degrees) needs to be subtracted for phi centered around 0 degrees
   # coordinate system used: beam direction: z
   #                         left side     : x
   #                         vertical up   : y
   # this currently wotks only for in-plane settings
   # calculations in calc_kin.C
   #
   # Double_t p_par = ( pow(pf,2) + pow(q_lab,2) - pow(pmc, 2))/ (2.*q_lab) ;
   # Double_t p_perp2 = abs(pow(pf, 2) - pow(p_par, 2));
   # Double_t p_perp = sqrt(p_perp2);
   pf = ka['pf']
   q_lab = ka['q_lab']
   pmc = ka['pm_mc']
   #angle of q with resp. to beam
   cthq = (Ei - Ef*np.cos( ka['th_e']*dtr ) )/q_lab
   theta_q = np.arccos(cthq)
   #direction of the proton
   #phi_v = ka['phi']*dtr - phi_off   #'phi' is actually phi_pq (I dont have 'phi' directly in kin file)
   #cosphi = ka['cos_phi']    #cos(phi_pq)
   phi_v = np.arccos(ka['cos_phi'])  #arccos(x) is returned in radians (no need to convert to radians)
   #phi_v = phi - phi_off   #'phi' is actually phi_pq
   
   p_par = (pf**2 + q_lab**2 - pmc**2)/(2.*q_lab)
   p_per = np.sqrt(pf**2 - p_par**2)
   #find phi
   py = p_per*np.sin(phi_v)
   sphp = py/pf
   php = np.arcsin(sphp)/dtr   #this is the actual out-of-plane proton angle
   #find theta
   p_xz = np.sqrt(pf**2 - py**2)
   if (p_par == 0.):
      cthpp = 0.
   else:
      cthpp = p_par/p_xz
   thpp = np.arccos(cthpp)
   if phi_v == np.pi/2.:
      thp = theta_q/dtr
   elif phi_v < np.pi/2.:
      thp = (theta_q - thpp)/dtr
   else:
      thp = (theta_q + thpp)/dtr
   l = '%f, %f \n'%(thp, php)
   outf.write(l)
   outf.write('1.,1.\n')
   outf.write('theta_b, phi_b, Incident Energy (theta = vertical, phi = hor !)\n')
   l = '0., 0., %f \n'%(ka['Ei'])
   outf.write(l)
   outf.write('1., 1., 0.1 \n')
   outf.write('omega independent of E i=1 (energy loss), i=0 otherwise \n')
   outf.write('0\n')
   #output files
   outf.close()   

   outf = open('./differ.in', 'r')
   data_summary= outf.read()
   outf.close()
   fsumin = open('./summary_files/SummaryInput_pm%i_%s_set%i.txt'%(pm_set, model, data_set), 'a')
   fsumin.write(data_summary)
   fsumin.write('----------------------------------------------------------------------------------\n')
   fsumin.close()

   #ready to run differ
   run_differ = './differ3'
   rc.run_command(run_differ, 'differ.out','differ_err')
   # now analyze differ, output tot_err is in %
   tot_err = ad.get_sig_tot('differ.out',  ftable_name, ftable_bin, print_all = False)
   if np.isnan(tot_err):
      print 'total_err could not be calculated, it is set to 100% for kinematics : ', kin_file, ' bin ib = ', ib
      tot_err = 100.      
   ka['tot_err'] = tot_err

   fout_differ = open('./differ.out')
   data_summary= fout_differ.read()
   fsumout = open('./summary_files/SummaryOutput_pm%i_%s_set%i.txt'%(pm_set, model, data_set), 'a')
   fsumout.write(data_summary)
   fsumout.write('----------------------------------------------------------------------------------\n')
   fsumout.close()

#write the new data into a file
results = open(output_file, 'w')
kin_file.add_header_comment(' ------------------------- ')
kin_file.add_header_comment(' tot_err is in % !')
kin_file.add_header_comment(' ------------------------- ')
kin_file.write_all(results, complete_header = True)

