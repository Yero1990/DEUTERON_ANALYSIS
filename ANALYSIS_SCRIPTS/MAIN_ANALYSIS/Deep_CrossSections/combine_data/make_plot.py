import LT.box as B
from LT.datafile import dfile
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy.ma as ma
import sys                                     
import os                                                                                                       
from sys import argv  
import matplotlib
matplotlib.use('Agg')


#Set font
csfont = {'fontname':'Times New Roman'}

def set_labels(axis='', label='', fts=0):
    if axis=='x':
        B.pl.xlabel(label, fontweight='bold', fontsize=fts, **csfont)
    if axis=='y':
        B.pl.ylabel(label, fontweight='bold', fontsize=fts, **csfont)
    if axis=='title':
        B.pl.title(label, fontweight='bold', fontsize=fts, **csfont)
     

def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)
    
    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr


#Conversion factor:  1 fm = 1/ (197 MeV),   
#The reduced cross section is in MeV^-3 units
MeV2fm = 197**3    #convert MeV^-3 to fm^3

#User Input (Dir. Name to store output)
sys_ext = sys.argv[1]   
    
dir_name = sys_ext+"_plots"
print(dir_name)
#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)
 
'''
#Get Xsec Data Files
f80 = B.get_file('../bin_centering_corrections/%s/pm80_laget_bc_corr.txt'%(sys_ext))

#Get Bin Information (Same info for all files)
i_b = B.get_data(f80, 'i_b')    #2D bin number
i_x = B.get_data(f80, 'i_x')    #x (th_nq) bin number
i_y = B.get_data(f80, 'i_y')    #y (pmiss) bin number
thnq = B.get_data(f80, 'xb')      #th_nq value at bin center
pm =  B.get_data(f80, 'yb')      #pmiss value at bin center

#Get 80 MeV Xsec
dataXsec_80     = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr')
dataXsec_err_80 = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr_err')
pwiaXsec_80     = B.get_data(f80, 'pwiaXsec_theory')
fsiXsec_80      = B.get_data(f80, 'fsiXsec_theory')


#convert '-1' to nan (better for plotting,as plots ignore nan)
convert2NaN(dataXsec_80, value=-1)
convert2NaN(dataXsec_err_80, value=-1)
convert2NaN(pwiaXsec_80, value=-1)
convert2NaN(fsiXsec_80, value=-1)
'''

#Get Reduced Xsec Data File
f = B.get_file('./%s/redXsec_combined.txt'%(sys_ext))

#Get Bin Information (Same info for all files)                                                                                                  
i_b = B.get_data(f, 'i_b')    #2D bin number                                                                    
i_x = B.get_data(f, 'i_x')    #x (th_nq) bin number                                                                                    
i_y = B.get_data(f, 'i_y')    #y (pmiss) bin number                                        
thnq = B.get_data(f, 'xb')      #th_nq value at bin center                                                          
pm =  B.get_data(f, 'yb')      #pmiss value at bin center   

#Get 80 MeV Red. Xsec (prepare arrays for masking)
red_dataXsec_80     = B.get_data(f, 'red_dataXsec_80')
red_dataXsec_err_80 = B.get_data(f, 'red_dataXsec_err_80')
red_pwiaXsec_80     = B.get_data(f, 'red_pwiaXsec_80')
red_fsiXsec_80      = B.get_data(f, 'red_fsiXsec_80')

#Get 580 MeV Red. Xsec
red_dataXsec_580set1     = B.get_data(f,'red_dataXsec_580set1')
red_dataXsec_err_580set1 = B.get_data(f,'red_dataXsec_err_580set1')
red_dataXsec_580set2     = B.get_data(f,'red_dataXsec_580set2')
red_dataXsec_err_580set2 = B.get_data(f,'red_dataXsec_err_580set2')
red_dataXsec_580avg      = B.get_data(f,'red_dataXsec_580avg')
red_dataXsec_580avg_err  = B.get_data(f,'red_dataXsec_580avg_err')

red_pwiaXsec_580set1 = B.get_data(f,'red_pwiaXsec_580set1')
red_pwiaXsec_580set2 = B.get_data(f,'red_pwiaXsec_580set2')
red_pwiaXsec_580avg  = B.get_data(f,'red_pwiaXsec_580avg')
red_fsiXsec_580set1  = B.get_data(f,'red_fsiXsec_580set1')
red_fsiXsec_580set2  = B.get_data(f,'red_fsiXsec_580set2')
red_fsiXsec_580avg   = B.get_data(f,'red_fsiXsec_580avg')

#Get 750 MeV Red. Xsec
red_dataXsec_750set1     = B.get_data(f,'red_dataXsec_750set1')
red_dataXsec_err_750set1 = B.get_data(f,'red_dataXsec_err_750set1')
red_dataXsec_750set2     = B.get_data(f,'red_dataXsec_750set2')
red_dataXsec_err_750set2 = B.get_data(f,'red_dataXsec_err_750set2')
red_dataXsec_750set3     = B.get_data(f,'red_dataXsec_750set3')
red_dataXsec_err_750set3 = B.get_data(f,'red_dataXsec_err_750set3')
red_dataXsec_750avg      = B.get_data(f,'red_dataXsec_750avg')
red_dataXsec_750avg_err  = B.get_data(f,'red_dataXsec_750avg_err')

red_pwiaXsec_750set1 = B.get_data(f,'red_pwiaXsec_750set1')
red_pwiaXsec_750set2 = B.get_data(f,'red_pwiaXsec_750set2')
red_pwiaXsec_750set3 = B.get_data(f,'red_pwiaXsec_750set3')
red_pwiaXsec_750avg  = B.get_data(f,'red_pwiaXsec_750avg')
red_fsiXsec_750set1  = B.get_data(f,'red_fsiXsec_750set1')
red_fsiXsec_750set2  = B.get_data(f,'red_fsiXsec_750set2')
red_fsiXsec_750set3  = B.get_data(f,'red_fsiXsec_750set3')
red_fsiXsec_750avg   = B.get_data(f,'red_fsiXsec_750avg')

#Get Combined Final Red Xsec for all kinematics
red_dataXsec_avg     = B.get_data(f,'red_dataXsec_avg')
red_dataXsec_avg_err = B.get_data(f,'red_dataXsec_avg_err')
red_dataXsec_avg_syst_err = B.get_data(f,'red_dataXsec_avg_syst_err')
red_dataXsec_avg_tot_err = B.get_data(f,'red_dataXsec_avg_tot_err')

red_pwiaXsec_avg     = B.get_data(f,'red_pwiaXsec_avg')
red_fsiXsec_avg      = B.get_data(f,'red_fsiXsec_avg')

#convert '-1' to nan
convert2NaN(red_dataXsec_avg, value=-1)
convert2NaN(red_dataXsec_avg_err, value=-1)
convert2NaN(red_pwiaXsec_avg, value=-1)
convert2NaN(red_fsiXsec_avg, value=-1)

def plot_data_sets():
    
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 


    for i, ithnq in enumerate(thnq_arr):
        print(ithnq)
        plt.clf()
        B.pl.figure(i)

        B.plot_exp(pm[thnq==ithnq], red_dataXsec_580set1[thnq==ithnq]*MeV2fm, red_dataXsec_err_580set1[thnq==ithnq]*MeV2fm, color='red',  marker='^', label='580 (set1)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_580set2[thnq==ithnq]*MeV2fm, red_dataXsec_err_580set2[thnq==ithnq]*MeV2fm, color='blue', marker='s', label='580 (set2)')
       
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set1[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set1[thnq==ithnq]*MeV2fm, color='magenta', markerfacecolor='none', marker='v', label='750 (set1)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set2[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set2[thnq==ithnq]*MeV2fm, color='cyan',    markerfacecolor='none', marker='D', label='750 (set2)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set3[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set3[thnq==ithnq]*MeV2fm, color='green',   markerfacecolor='none', marker='s', label='750 (set3)')

        B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, color='black', marker='o', label='Combined Data')

        B.pl.yscale('log')


        B.pl.xlim(0,1.2)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        B.pl.title(r'Reduced Data Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))

        B.pl.legend()
    
        B.pl.savefig(dir_name+'/dataSets_redXsec_thnq%i.pdf'%(ithnq))

    #B.pl.show('same')

def plot_theory_sets(model=''):
    
    
    if (model=='pwia'):
        thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 

        '''
        #Mask '-' values
        red_pwiaXsec_580set1_masked =  ma.masked_array(red_pwiaXsec_580set1, mask=red_pwiaXsec_580set1<0)
        red_pwiaXsec_580set2_masked =  ma.masked_array(red_pwiaXsec_580set2, mask=red_pwiaXsec_580set2<0)
        
        red_pwiaXsec_750set1_masked =  ma.masked_array(red_pwiaXsec_750set1, mask=red_pwiaXsec_750set1<0)
        red_pwiaXsec_750set2_masked =  ma.masked_array(red_pwiaXsec_750set2, mask=red_pwiaXsec_750set2<0)
        red_pwiaXsec_750set3_masked =  ma.masked_array(red_pwiaXsec_750set3, mask=red_pwiaXsec_750set3<0)
        '''


        for i, ithnq in enumerate(thnq_arr):
            print(ithnq)
            B.pl.clf()
            B.pl.figure(i)

            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_580set1[thnq==ithnq]*MeV2fm, color='red',  linestyle='--',  label='580 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_580set2[thnq==ithnq]*MeV2fm, color='blue', linestyle='--', label='580 (set2)')
            
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set1[thnq==ithnq]*MeV2fm, color='magenta',linestyle='--', label='750 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set2[thnq==ithnq]*MeV2fm, color='cyan',   linestyle='--', label='750 (set2)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set3[thnq==ithnq]*MeV2fm, color='green',  linestyle='--', label='750 (set3)')
            
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_avg[thnq==ithnq]*MeV2fm, color='black', linestyle='--', label='Combined PWIA Theory')

            B.pl.yscale('log')


            B.pl.xlim(0,1.2)
            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
            th_nq_min = ithnq - 5
            th_nq_max = ithnq + 5
            B.pl.title(r'Reduced PWIA Theoretical Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))

            B.pl.legend()
    
            B.pl.savefig(dir_name+'/%s_theorySets_redXsec_thnq%i.pdf'%(model, ithnq))

        #B.pl.show('same')

    if (model=='fsi'):
        thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 


        for i, ithnq in enumerate(thnq_arr):
            print(ithnq)
            B.pl.clf()
            B.pl.figure(i)
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_580set1[thnq==ithnq]*MeV2fm, color='red',  linestyle='--',  label='580 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_580set2[thnq==ithnq]*MeV2fm, color='blue', linestyle='--', label='580 (set2)')
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set1[thnq==ithnq]*MeV2fm, color='magenta',linestyle='--', label='750 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set2[thnq==ithnq]*MeV2fm, color='cyan',   linestyle='--', label='750 (set2)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set3[thnq==ithnq]*MeV2fm, color='green',  linestyle='--', label='750 (set3)')
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_avg[thnq==ithnq]*MeV2fm, color='black', linestyle='--', label='Combined FSI Theory')
            
            B.pl.yscale('log')
            
                
            B.pl.xlim(0,1.2)
            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
            th_nq_min = ithnq - 5
            th_nq_max = ithnq + 5
            B.pl.title(r'Reduced FSI Theoretical Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
            
            B.pl.legend()
            
            B.pl.savefig(dir_name+'/%s_theorySets_redXsec_thnq%i.pdf'%(model, ithnq))
                
        #B.pl.show('same')




def plot_final():

    #----MASKING ARRAYS TO CHOOSE ERRORS BELOW 50 %-------
    #The Limit on the red. Xsec error should be placed at the very end, when the combined data is plotted (all data sets and overlapping bins have been combined)
    red_dataXsec_avg_masked = np.ma.array(red_dataXsec_avg, mask=(red_dataXsec_avg_err>0.5*red_dataXsec_avg))
    red_dataXsec_avg_masked = np.ma.filled(red_dataXsec_avg_masked.astype(float), np.nan)


    #Read Hall A data
    pm_ha35, red_dataXsec_ha35, red_dataXsec_err_ha35 = read_halla_data(35)
    pm_ha45, red_dataXsec_ha45, red_dataXsec_err_ha45 = read_halla_data(45)  

    #Plot momentum distribution vs. Pmiss for different theta_nq
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    for i, ithnq in enumerate(thnq_arr):

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5


        #Read Other Theoretical Models (V18, CD-BONN)
        pm_bin1, red_pwiaXsec_V18 = read_theoretical_models("V18", "PWIA", ithnq)
        pm_bin2, red_fsiXsec_V18 = read_theoretical_models("V18", "FSI", ithnq) 
        pm_bin3, red_pwiaXsec_CD = read_theoretical_models("CD-Bonn", "PWIA", ithnq)                                   
        pm_bin4, red_fsiXsec_CD = read_theoretical_models("CD-Bonn", "FSI", ithnq)    

    
        #Read Hall A Data
        #pm_ha, red_dataXsec_ha, red_dataXsec_err_ha = read_halla_data(ithnq)

        #print(pm_ha)


        #------Convert to fm^-3--------

        #THEORY
        red_pwiaXsec_avg[thnq==ithnq] = red_pwiaXsec_avg[thnq==ithnq]*MeV2fm    #Laget PWIA
        red_fsiXsec_avg[thnq==ithnq] = red_fsiXsec_avg[thnq==ithnq]*MeV2fm    #Laget FSI
        red_pwiaXsec_V18 = red_pwiaXsec_V18*MeV2fm
        red_fsiXsec_V18 = red_fsiXsec_V18*MeV2fm
        red_pwiaXsec_CD = red_pwiaXsec_CD*MeV2fm
        red_fsiXsec_CD = red_fsiXsec_CD*MeV2fm

        #Do Interpolation to make theory curves smooth
        f_red_pwiaXsec_avg = interp1d(pm[thnq==ithnq], red_pwiaXsec_avg[thnq==ithnq])   #Laget PWIA
        f_red_fsiXsec_avg = interp1d(pm[thnq==ithnq], red_fsiXsec_avg[thnq==ithnq])     #Laget FSI

        f_red_pwiaXsec_V18 = interp1d(pm_bin1, red_pwiaXsec_V18)
        f_red_fsiXsec_V18 = interp1d(pm_bin2, red_fsiXsec_V18)
       
        f_red_pwiaXsec_CD = interp1d(pm_bin3, red_pwiaXsec_CD)
        f_red_fsiXsec_CD = interp1d(pm_bin4, red_fsiXsec_CD)


        print(ithnq)
        B.pl.clf()
        B.pl.figure(i)

        
        #----------PLOT FINAL REDUCED XSEC VS. THETA_nq------------
        '''
        #B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, marker='o', color='black', logy=True, label='Data' )
        #B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, marker='o', color='gray', markerfacecolor='none', label='Statistical Error, (statistics < 50 % )' )
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm, red_dataXsec_avg_tot_err[thnq==ithnq]*MeV2fm, marker='o', color='k', markerfacecolor='k', label='Hall C DATA (statistics < 50 % )' )
        
        #--------------HALL A DATA---------------
        if(ithnq==35):
            #Plot Hall A Data for thnq==35 or 45 deg
            B.plot_exp(pm_ha35, red_dataXsec_ha35, red_dataXsec_err_ha35, marker='^', color='c', label='Hall A DATA')
        if(ithnq==45):                                                                                                             
            #Plot Hall A Data for thnq==35 or 45 deg                                                                                                                                                    
            B.plot_exp(pm_ha45, red_dataXsec_ha45, red_dataXsec_err_ha45, marker='^', color='c', label='Hall A DATA')
        #----------------------------------------

        B.plot_exp(pm[thnq==ithnq], f_red_pwiaXsec_avg(pm[thnq==ithnq]), linestyle='--', marker='None', color='blue', logy=False, label='Paris PWIA')
        B.plot_exp(pm[thnq==ithnq], f_red_fsiXsec_avg(pm[thnq==ithnq]), linestyle='-', marker='None', color='blue', logy=False, label='Paris FSI')

        B.plot_exp(pm_bin1, f_red_pwiaXsec_V18(pm_bin1), linestyle='--', marker='None', color='green', logy=False, label='V18 PWIA')   
XO        B.plot_exp(pm_bin2, f_red_fsiXsec_V18(pm_bin2), linestyle='-', marker='None', color='green', logy=False, label='V18 FSI') 

        B.plot_exp(pm_bin3, f_red_pwiaXsec_CD(pm_bin3), linestyle='--', marker='None', color='magenta', logy=False, label='CD-Bonn PWIA')     
        B.plot_exp(pm_bin4, f_red_fsiXsec_CD(pm_bin4), linestyle='-', marker='None', color='magenta', logy=False, label='CD-Bonn FSI') 

        B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')
        B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
        B.pl.ylim(0, 1.e-4)
        B.pl.xlim(0.4, 1.19)
        B.pl.title(r'Reduced Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        # B.pl.yscale('linear')
        B.pl.legend()            
        B.pl.savefig(dir_name+'/final_redXsec_thnq%i_linear.pdf'%(ithnq))
        '''

        #------Plot the Exp. Data relative errors dsig / sig  to know how large are the contributions from systematics and statistical------ 
        '''
        B.pl.clf()
        B.pl.figure(i+1)

        y = np.array([0. for i in range(len(pm[thnq==ithnq]))])

        dsig_sig_stats = red_dataXsec_avg_err[thnq==ithnq]*MeV2fm / (red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm)
        dsig_sig_syst = red_dataXsec_avg_syst_err[thnq==ithnq]*MeV2fm / (red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm)
        dsig_sig_tot = red_dataXsec_avg_tot_err[thnq==ithnq]*MeV2fm / (red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm)

        for i in range(len(y)):
            if (np.isnan(dsig_sig_tot[i])):
                y[i] = np.nan

        B.plot_exp(pm[thnq==ithnq],  y, dsig_sig_stats*100., marker='o', color='b', label='Statistical Error')
        B.plot_exp(pm[thnq==ithnq],  y, dsig_sig_syst*100., marker='o', color='r', label='Systematics Error')
        B.plot_exp(pm[thnq==ithnq],  y, dsig_sig_tot*100., marker='o', color='k', label='Total Error')
        B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')
        B.pl.ylabel(r'Data Relative Error [%]')
        B.pl.ylim(-100, 100)
        B.pl.title(r'Relative Error, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/final_redXsec_relativeError_thnq%i.pdf'%(ithnq))
        '''
    
        
        #--------------Plot the % Deviation of data and all models relative to the CD-Bonn FSI model------------------------
        '''
        B.pl.clf()
        B.pl.figure(i+2)
   
        relative_err_fsi = (red_dataXsec_avg_masked[thnq==ithnq] - red_fsiXsec_avg[thnq==ithnq]) / (red_dataXsec_avg_masked[thnq==ithnq]) * 100.
        d_relative_err_fsi = (1./red_dataXsec_avg_masked[thnq==ithnq] - (red_dataXsec_avg_masked[thnq==ithnq] - red_fsiXsec_avg[thnq==ithnq]) /red_dataXsec_avg_masked[thnq==ithnq]**2) * red_dataXsec_avg_tot_err[thnq==ithnq]*100.
 
        relative_err_pwia = (red_dataXsec_avg_masked[thnq==ithnq] - red_pwiaXsec_avg[thnq==ithnq]) / (red_dataXsec_avg_masked[thnq==ithnq]) * 100.
        d_relative_err_pwia = (1./red_dataXsec_avg_masked[thnq==ithnq] - (red_dataXsec_avg_masked[thnq==ithnq] - red_pwiaXsec_avg[thnq==ithnq]) /red_dataXsec_avg_masked[thnq==ithnq]**2) * red_dataXsec_avg_tot_err[thnq==ithnq]*100.

        B.plot_exp(pm[thnq==ithnq],  relative_err_fsi, d_relative_err_fsi, marker='o', color='r', label='relative error (Paris FSI)')
        B.plot_exp(pm[thnq==ithnq],  relative_err_pwia, d_relative_err_pwia, marker='s', color='b', label='relative error (Paris PWIA)')

        B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')
        B.pl.ylabel(r'Relative Error [%]')
        B.pl.ylim(-100, 100)
        B.pl.title(r'Relative Error, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/final_redXsec_relativeErrorModel_thnq%i.pdf'%(ithnq))
        
        #V18 Model to Data Comparison
        B.pl.clf()                                                                                                                                               
        B.pl.figure(i+2)                                                                                                                                                                                         
                                                                                                                                                                                                                 
        relative_err_fsi = (red_dataXsec_avg_masked[thnq==ithnq] - red_fsiXsec_avg[thnq==ithnq]) / (red_dataXsec_avg_masked[thnq==ithnq]) * 100.                                                                 
        d_relative_err_fsi = (1./red_dataXsec_avg_masked[thnq==ithnq] - (red_dataXsec_avg_masked[thnq==ithnq] - red_fsiXsec_avg[thnq==ithnq]) /red_dataXsec_avg_masked[thnq==ithnq]**2) * red_dataXsec_avg_tot_e$
                                                                                                                                                                                                                 
        relative_err_pwia = (red_dataXsec_avg_masked[thnq==ithnq] - red_pwiaXsec_avg[thnq==ithnq]) / (red_dataXsec_avg_masked[thnq==ithnq]) * 100.                                                               
        d_relative_err_pwia = (1./red_dataXsec_avg_masked[thnq==ithnq] - (red_dataXsec_avg_masked[thnq==ithnq] - red_pwiaXsec_avg[thnq==ithnq]) /red_dataXsec_avg_masked[thnq==ithnq]**2) * red_dataXsec_avg_tot$
                                                                                                                                                                                                                 
        B.plot_exp(pm[thnq==ithnq],  relative_err_fsi, d_relative_err_fsi, marker='o', color='r', label='relative error (Paris FSI)')                                                                            
        B.plot_exp(pm[thnq==ithnq],  relative_err_pwia, d_relative_err_pwia, marker='s', color='b', label='relative error (Paris PWIA)')                                                                         
                                                                                                                                                                                                                 
        B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')                                                                                                                                                            
        B.pl.ylabel(r'Relative Error [%]')                                                                                                                                                                       
        B.pl.ylim(-100, 100)                                                                                                                                                                                     
        B.pl.title(r'Relative Error, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))                                                                                                                             
        B.pl.legend()                                                                                                                                                                                            
        B.pl.savefig(dir_name+'/final_redXsec_relativeErrorModel_thnq%i.pdf'%(ithnq))   
        '''

        #-------Plot the Ratio  sig_red_exp(pm) / sig_red_exp(p0=0.5 GeV/c) for pm >=0.5 GeV/c (same for models), to compare shapes

        #Require ONLY thnq = 35, 45 deg 

        if (ithnq==35 or ithnq==45):

            #DATA
            print(pm[thnq==ithnq])
            sig_exp =  red_dataXsec_avg_masked[thnq==ithnq] 
            sig_exp_p0 = red_dataXsec_avg_masked[(thnq==ithnq)][np.where(pm[thnq==ithnq]==0.5)]
            sig_exp_err =  red_dataXsec_avg_tot_err[thnq==ithnq] 
            sig_exp_p0_err = red_dataXsec_avg_tot_err[(thnq==ithnq)][np.where(pm[thnq==ithnq]==0.5)]
            
            #Paris
            sig_paris_pwia = f_red_pwiaXsec_avg(pm[thnq==ithnq])
            sig_paris_pwia_p0 = f_red_pwiaXsec_avg(pm[thnq==ithnq][np.where(pm[thnq==ithnq]==0.5)]) 

            sig_paris_fsi = f_red_fsiXsec_avg(pm[thnq==ithnq])                                                                                                            
            sig_paris_fsi_p0 = f_red_fsiXsec_avg(pm[thnq==ithnq][np.where(pm[thnq==ithnq]==0.5)]) 


            #AV18                                                                                                                   
            sig_V18_pwia = f_red_pwiaXsec_V18(pm_bin1)        #V18 Xsec                                                                             
            sig_V18_pwia_p0 = f_red_pwiaXsec_V18(pm_bin1[np.where(pm_bin1==0.5)])  #V18 Xsec given that Pm = 0.5 GeV 
                                
            sig_V18_fsi = f_red_fsiXsec_V18(pm_bin2)        #V18 Xsec                                                                      
            sig_V18_fsi_p0 = f_red_fsiXsec_V18(pm_bin2[np.where(pm_bin2==0.5)])  #V18 Xsec given that Pm = 0.5 GeV   

            #CD-Bonn
            sig_CD_pwia = f_red_pwiaXsec_CD(pm_bin3)        #CD-Bonn Xsec
            sig_CD_pwia_p0 = f_red_pwiaXsec_CD(pm_bin3[np.where(pm_bin3==0.5)])  #CD-Bonn Xsec given that Pm = 0.5 GeV 
            
            sig_CD_fsi = f_red_fsiXsec_CD(pm_bin4)        #CD-Bonn Xsec                                                                     
            sig_CD_fsi_p0 = f_red_fsiXsec_CD(pm_bin4[np.where(pm_bin4==0.5)])  #CD-Bonn Xsec given that Pm = 0.5 GeV  

            #print('pm=',pm_bin3)
            #print('sig_CD=',sig_CD_pwia)
            #print('sig_CD_p0=',sig_CD_pwia_p0)

            #DEFINE THE RATIOS
            #DATA
            R_exp = sig_exp / sig_exp_p0
            R_exp_err = np.sqrt(((1. / sig_exp_p0)**2 *  sig_exp_err**2 )  + (sig_exp / sig_exp_p0**2)**2 * sig_exp_p0_err**2)
            #Paris
            R_paris_pwia = sig_paris_pwia / sig_paris_pwia_p0
            R_paris_fsi = sig_paris_fsi / sig_paris_fsi_p0 
            #AV18
            R_V18_pwia = sig_V18_pwia / sig_V18_pwia_p0                                                                
            R_V18_fsi = sig_V18_fsi / sig_V18_fsi_p0 
            #CD-Bonn                                                                                                                          
            R_CD_pwia = sig_CD_pwia / sig_CD_pwia_p0                                                                                            
            R_CD_fsi = sig_CD_fsi / sig_CD_fsi_p0 

            B.plot_exp(pm[thnq==ithnq], R_exp, R_exp_err, marker='o', color='k', label='DATA')

            B.plot_exp(pm[thnq==ithnq], R_paris_pwia, linestyle='--',  marker='None', color='blue', label='Paris PWIA')  
            B.plot_exp(pm[thnq==ithnq], R_paris_fsi, linestyle='-',  marker='None', color='blue', label='Paris FSI') 

            B.plot_exp(pm_bin1, R_V18_pwia, linestyle='--',  marker='None', color='green', label='V18 PWIA')                             
            B.plot_exp(pm_bin2, R_V18_fsi, linestyle='-',  marker='None', color='green', label='V18 FSI')

            B.plot_exp(pm_bin3, R_CD_pwia, linestyle='--',  marker='None', color='magenta', label='CD-Bonn PWIA')                                         
            B.plot_exp(pm_bin4, R_CD_fsi, linestyle='-',  marker='None', color='magenta', label='CD-Bonn FSI') 


            B.pl.xlim(0.490, 1.19)
            B.pl.ylim(0, 1.5)

            xlabel = 'Neutron Recoil Momenta [GeV/c]'
            ylabel = r'Cross Section Ratio, \sigma/\sigma(P_{m}=0.5)'
            title = r'Cross Section Ratio, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max)
            set_labels('x', xlabel, 15)
            set_labels('y', ylabel, 15)
            set_labels('title', title, 15)
            #B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')                                                                                                                                                            
            #B.pl.ylabel(r'Cross Section Ratio')                                                                                                                                                                       
            #B.pl.title(r'Cross Section Ratio, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))                                                                                                                             
            B.pl.legend()                                                                                                                                                                                            
            B.pl.savefig(dir_name+'/ratio_test_thnq%i.pdf'%(ithnq))   

def read_halla_data(thnq=0):

    #The code read data files containing momentum distributions from Hall A

    #1 GeV  = 1/0.1973  fm^-1  conversion factor to convert Pm from fm-1 to GeV
    fminv2GeV = 1./(1./0.1973)

    thnq_f = '%.1f' % (thnq)
    fname = '../HallA_data/theta_%s_th_corr.data' % (thnq_f)

    kin = dfile(fname)
    p_miss = kin['p_miss'] * fminv2GeV    #Pm here is not the central bin value, but an average over that bin
    red_dataXsec = kin['rho']             #units fm^3
    red_dataXsec_err = kin['delta_rho']

    return p_miss, red_dataXsec, red_dataXsec_err
    
def read_theoretical_models(theory="", model="", thnq=0):

    #This code read the averaged red.Xsec and returns arrays in pm and reduced Xsec
    #theory: V18, CD-Bonn    model: PWIA, FSI
    thnq_f = "%.2f" %(thnq)

    fname = '../theoretical_models/updated_%s_models/theoryXsec_%s%s_thnq%s_combined.data' % (model, theory, model, thnq_f)
    kin = dfile(fname)
    
    pm_bin = np.array(kin['pm_bin'])
    #print(pm_bin)
    if(model=="PWIA" and theory=="V18"):
        red_pwiaXsec_V18 = kin['red_pwiaXsec_theory']
        return pm_bin, red_pwiaXsec_V18 
    if(model=="PWIA" and theory=="CD-Bonn"):                                                                                                                          
        red_pwiaXsec_CD_Bonn = kin['red_pwiaXsec_theory']                                                                          
        return pm_bin, red_pwiaXsec_CD_Bonn
    if(model=="FSI" and theory=="V18"):                                                 
        red_fsiXsec_V18 = kin['red_fsiXsec_theory']                                               
        return pm_bin, red_fsiXsec_V18 
    if(model=="FSI" and theory=="CD-Bonn"):                                                                                            
        red_fsiXsec_CD_Bonn = kin['red_fsiXsec_theory'] 
        return pm_bin, red_fsiXsec_CD_Bonn

def main():
    print('Entering Main . . .')

    #plot_data_sets()

    #plot_theory_sets('pwia')
    #plot_theory_sets('fsi')
    #plot_Xsec_vs_thnq()
    plot_final()


if __name__=="__main__":
    main()


