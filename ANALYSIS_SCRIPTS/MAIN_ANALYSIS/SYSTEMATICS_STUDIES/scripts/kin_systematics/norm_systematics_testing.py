import numpy as np
from LT.datafile import dfile
import LT.box as B
import shutil as sh
import os

#This code has utilities functions that calculates the systematics 
#due to the correction factors in the data yield for each data set

#If, FullWeight = f_tgt * f_pAbs * f_tLT  * f_eTrkEff * f_pTrkEff * f_Qtot
#Experimental Xsec: sig_exp = Y_corr / P.S. = (Y_uncorr / P.S.) *  f_tgt * f_pAbs * f_tLT  * f_eTrkEff * f_pTrkEff * f_Qtot

#Each of the corrections has an associated uncertainty, df/f, therefore, the
#systematic error on the cross section (sig_exp ) is:  dsig_exp_syst2 = [sig_exp**2 * (df/f)**2 ]_tgtBoil + . . . +  [sig_exp**2 * (df/f)**2 ]_pAbs + ...
#A derivative has to be takem to determine the uncertainty in f.

#***IMPORTANT***: Each of the utilities functions saves a copy of the average kinematics file with the dsig_i (contributions to the cross section systematics error)
#                 The errors are written to file as relative error, df/f. To get the absolute error, one would multiply by the cross section to get: df = (df/f)*f
#                 A special utility function calculates the total dsig2 from the sum in quadrature of the norm systematics: dsig2_norm_tot = dsig2_hEtrk + dsig2_Qtot + dsig2_tLT + . . .
#                 The utilities functions also return their respective the dsig_2 contributions as well as the relative error df/f, which gives an idea of how large is the error relative to the Xsec
                  #(The model='' input parameter refers to the model used for the radiative corrections. We use Laget FSI, as it closely represents data in all kinematical regions)

#Tracking efficiencies
def get_trkEff_syst(pm_set=0, model='', data_set=0):
    
    #This code reads the tracking efficiency and its uncertainty
    #for all runs of a given data set, and calculates the weighted 
    #average. The systematic uncertanity on the data Xsec is determined from the relative
    #uncertainty on the tracking efficiencies.
    
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    
    #open report 
    r = dfile(report_file)                 #open report file
    
    #Get Tracking Eff. and its error
    htrk_eff = r['hTrkEff']
    htrk_eff_err = r['hTrkEff_err']

    etrk_eff = r['eTrkEff']
    etrk_eff_err = r['eTrkEff_err']

    #determine corr. factor and its error for each run of the data set
    f_htrk = 1. / htrk_eff[htrk_eff_err!=0]
    f_etrk = 1. / etrk_eff

    df_htrk = -(1./ htrk_eff[htrk_eff_err!=0]**2 ) *  htrk_eff_err[htrk_eff_err!=0]
    df_etrk = -(1./ etrk_eff**2 ) *  etrk_eff_err

    #relative systematic error (run-by-run) array
    df_f_htrk_syst = np.abs(df_htrk)/f_htrk
    df_f_etrk_syst = np.abs(df_etrk)/f_etrk

    #average of relative systematic error (per data set)
    df_f_htrk_avg = np.average(np.abs(df_htrk)/f_htrk)
    df_f_etrk_avg = np.average(np.abs(df_etrk)/f_etrk)
   
    #run-by-run systematic added in quadrature
    df_f_htrk_quad = np.sqrt( np.sum(df_f_htrk_syst**2) )  #sqrt of sum of squares of errors
    df_f_etrk_quad = np.sqrt( np.sum(df_f_etrk_syst**2) )

    '''#DEBUG
    print('====Pm: %i (set %i) :: Tracking Eff.======'%(pm_set, data_set))
    print('hms_df/f=',df_f_htrk_syst)
    print('shms_df/f=',df_f_etrk_syst)

    print('hms_df/f_avg=', df_f_htrk_avg)
    print('shms_df/f_avg=', df_f_etrk_avg)
          
    print('hms_df/f_quad=', df_f_htrk_quad)
    print('shms_df/f_quad=', df_f_etrk_quad)
    '''

    return[df_f_htrk_avg, df_f_etrk_avg]

def get_tgtboil_syst(pm_set=0, model='', data_set=0):

    #This code calculated the systematic uncertainty on the data Xsec from the uncertainty in
    #the target boiling factor.

    
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file

    I = r['avg_current']     #in uA  (is an array if there are multiple runs per data set)
    tgt_boil = r['tgtBoil_factor']

    #Code to determine the target boiling factor systematic effect on the cross section.
    m =  0.00080029          #LD2 slope from fit [fract. yield loss / uA]
    sig_m = 0.00007037       #uncertainty for LD2 target boiling fit slope
    dI_I = 2.0/100.          #relative uncertainty in average current ( 2 % to be conservative. Suggested by D. Mack)

    sig_I = dI_I * I             

    #f = 1 / (1. - m*I)       #correction factor to data yield 
    f = 1./ tgt_boil
    
    #derivatives of corr. factor
    df_dm = -I/(1. - m*I)**2
    df_dI = -m/(1. - m*I)**2
    
    df2 = (df_dm**2) * sig_m**2 + (df_dI**2) * sig_I**2     #error by quadrature
    df = np.sqrt(df2)    #uncertainty in correction factor

    #relative systematic error (run-by-run) array
    df_f_syst = df / f
    
    #average of relative systematic error (per data set)
    df_f_avg = np.average(df_f_syst)

    #run-by-run systematic added in quadrature
    df_f_quad = np.sqrt(np.sum(df_f_syst**2))
    
    '''#DEBUG
    print('====Pm: %i (set %i) :: Target Boiling======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)
    '''
    
    return df_f_avg

def get_pT_syst(pm_set=0, model='', data_set=0):
    
    #code to get systematics on proton absorption
    #The proton absorption for E12-10-003 was determined to 
    #be: 4.66 +/- 0.472 %,  the transmission is: (100-4.66 or 95.34) +/- 0.472%
    #It is assumed that this factor is relatively constant over a range of angles/momenta

    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file
    
    pT = 0.9534           #proton transmission factor (what fraction of coin. protons made it to form the trigger) --See docDB proton absorption Under Yero.
    d_pT = 0.472/100.     

    #correction factor to the data yield
    f = 1./pT
    df = -1/pT**2 * d_pT
    
    #relative systematic error (run-by-run)
    df_f_syst = abs(df)/f
    
    #average of relative systematic error (per data set)
    df_f_avg = np.average( df_f_syst )

    #run-by-run systematic added in quadrature
    df_f_quad = np.sqrt(np.sum(df_f_syst**2))

    '''#DEBUG
    print('====Pm: %i (set %i) : Proton Transmission======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)
    '''

    return df_f_avg
    
def get_tLT_syst(pm_set=0, model='', data_set=0):

    #code to get the total live time (from EDTM) systematics
    
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file

    tLT = r['tLT']     #total live time [fraction or %/100]
    shms_3of4 = r['ptrig1_rate']    #shms 3/4 trigger tae in kHz.  Used to crudely estimate relative error on Xsec

    df_f_approx = shms_3of4 * 1000. * (100 * 1e-9)   #this is prob. of how many 3/4 triggers would be blocked given 100 ns window.
    df_f_approx_avg = np.average(df_f_approx)

    print('total_live_time_rel_err=',df_f_approx_avg)

    d_tLT = 0.03 * tLT          #assume uncertainty in total live time contributes to 3 % systematics (conservative estimate)
    
    f = 1./tLT                #correction factor
    df = -1./tLT**2 * d_tLT   #uncertainty in corr. factor
    
    #relative systematic error (run-by-run) array
    df_f_syst = np.abs(df) / f
    
    #average of relative systematic error (per data set)
    df_f_avg = np.average(df_f_syst)

    #run-by-run systematic added in quadrature
    df_f_quad = np.sqrt(np.sum(df_f_syst**2))
     
    '''#DEBUG
    print('====Pm: %i (set %i) :: Total Live Time======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_approx_avg=',df_f_approx_avg)
    print('df/f_quad=',df_f_quad)
    '''

    return round(df_f_avg,3)
    
def get_Qtot_syst(pm_set=0, model='', data_set=0):
    
    #code to get the systematics of the total accumulated charge (related to BCMs uncertainty)
      
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file

    Q = r['charge']          #total accumulated charge (mC)
    dQ_Q = 0.02           #uncertainty in total charge (take 2% for now, conservative)

    dQ = dQ_Q * Q

    f =  1./Q             #correction factor
    df = -1/Q**2 * dQ     #uncertainty in corr. factor
    
    #relative systematic error (run-by-run) array
    df_f_syst = np.abs(df) / f
    
    #average of relative systematic error (per data set)
    df_f_avg = np.average(df_f_syst)

    #run-by-run systematic added in quadrature
    df_f_quad = np.sqrt(np.sum(df_f_syst**2))
     
    '''#DEBUG
    print('====Pm: %i (set %i) :: Total Charge======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)
    '''

    return round(df_f_avg, 3)


def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)
    
    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr


def get_filenames(pm_set, model, data_set):
    #This code returns the filename paths for the average kinematics, final Xsec results and report file
    #for the determination of systematics.

    d2_dir = "/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/"
    avg_kin_dir = d2_dir+"Deep_CrossSections/average_kinematics/Em_final40MeV/"
    final_Xsec_dir = d2_dir+"Deep_CrossSections/bin_centering_corrections/Em_final40MeV/"
    
    if(pm_set==80):
        init_file= avg_kin_dir+'pm%i_%s_norad_avgkin.txt'%(pm_set, model) 
        avg_kin_file = avg_kin_dir+'pm%i_%s_norad_avgkin_systematics.txt'%(pm_set, model) 
        final_Xsec_file = final_Xsec_dir+'pm%i_laget_bc_corr_systematics.txt'%(pm_set)
        #Check if file to store systematics exists, else create it
        if not os.path.exists(avg_kin_file):
            sh.copyfile(init_file, avg_kin_file)
   
    
    else:
        init_file= avg_kin_dir+'pm%i_%s_norad_avgkin_set%i.txt'%(pm_set, model, data_set) 
        avg_kin_file = avg_kin_dir+'pm%i_%s_norad_avgkin_set%i_systematics.txt'%(pm_set, model, data_set)
        final_Xsec_file = final_Xsec_dir+'pm%i_laget_bc_corr_set%i_systematics.txt'%(pm_set, data_set)
        #Check if file to store systematics exists, else create it
        if not os.path.exists(avg_kin_file):
            sh.copyfile(init_file, avg_kin_file)

    report_file=d2_dir+'root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)


    return [avg_kin_file, final_Xsec_file, report_file]


def get_average_systematics():
    
    #This code calls functions to get systematics (that have been already averaged per run)
    #and averages them over different data sets to get an overall final systeamtic value

    #Pm = 80 (set1)
    df_f_htrkEff_80s1, df_f_etrkEff_80s1 = get_trkEff_syst(80, 'fsi', 1)
    df_f_tgtBoil_80s1 = get_tgtboil_syst(80, 'fsi', 1)
    df_f_pT_80s1 = get_pT_syst(80, 'fsi', 1)
    df_f_tLT_80s1 = get_tLT_syst(80, 'fsi', 1)
    df_f_Qtot_80s1 = get_Qtot_syst(80, 'fsi', 1)
    
    #Pm = 580 (set1)
    df_f_htrkEff_580s1, df_f_etrkEff_580s1 = get_trkEff_syst(580, 'fsi', 1)
    df_f_tgtBoil_580s1 = get_tgtboil_syst(580, 'fsi', 1)
    df_f_pT_580s1 = get_pT_syst(580, 'fsi', 1)
    df_f_tLT_580s1 = get_tLT_syst(580, 'fsi', 1)
    df_f_Qtot_580s1 = get_Qtot_syst(580, 'fsi', 1)
        
    #Pm = 580 (set2)
    df_f_htrkEff_580s2, df_f_etrkEff_580s2 = get_trkEff_syst(580, 'fsi', 2)
    df_f_tgtBoil_580s2 = get_tgtboil_syst(580, 'fsi', 2)
    df_f_pT_580s2 = get_pT_syst(580, 'fsi', 2)
    df_f_tLT_580s2 = get_tLT_syst(580, 'fsi', 2)
    df_f_Qtot_580s2 = get_Qtot_syst(580, 'fsi', 2)
    
    #Pm = 750 (set1)
    df_f_htrkEff_750s1, df_f_etrkEff_750s1 = get_trkEff_syst(750, 'fsi', 1)
    df_f_tgtBoil_750s1 = get_tgtboil_syst(750, 'fsi', 1)
    df_f_pT_750s1 = get_pT_syst(750, 'fsi', 1)
    df_f_tLT_750s1 = get_tLT_syst(750, 'fsi', 1)
    df_f_Qtot_750s1 = get_Qtot_syst(750, 'fsi', 1)
        
    #Pm = 750 (set2)
    df_f_htrkEff_750s2, df_f_etrkEff_750s2 = get_trkEff_syst(750, 'fsi', 2)
    df_f_tgtBoil_750s2 = get_tgtboil_syst(750, 'fsi', 2)
    df_f_pT_750s2 = get_pT_syst(750, 'fsi', 2)
    df_f_tLT_750s2 = get_tLT_syst(750, 'fsi', 2)
    df_f_Qtot_750s2 = get_Qtot_syst(750, 'fsi', 2)
    
    #Pm = 750 (set3)
    df_f_htrkEff_750s3, df_f_etrkEff_750s3 = get_trkEff_syst(750, 'fsi', 3)
    df_f_tgtBoil_750s3 = get_tgtboil_syst(750, 'fsi', 3)
    df_f_pT_750s3 = get_pT_syst(750, 'fsi', 3)
    df_f_tLT_750s3 = get_tLT_syst(750, 'fsi', 3)
    df_f_Qtot_750s3 = get_Qtot_syst(750, 'fsi', 3)

    df_f_htrkEff_arr = np.array([df_f_htrkEff_80s1, df_f_htrkEff_580s1, df_f_htrkEff_580s2, df_f_htrkEff_750s1, df_f_htrkEff_750s2, df_f_htrkEff_750s3])
    df_f_etrkEff_arr = np.array([df_f_etrkEff_80s1, df_f_etrkEff_580s1, df_f_etrkEff_580s2, df_f_etrkEff_750s1, df_f_etrkEff_750s2, df_f_etrkEff_750s3])
    df_f_tgtBoil_arr = np.array([df_f_tgtBoil_80s1, df_f_tgtBoil_580s1, df_f_tgtBoil_580s2, df_f_tgtBoil_750s1, df_f_tgtBoil_750s2, df_f_tgtBoil_750s3])
    df_f_pT_arr = np.array([df_f_pT_80s1, df_f_pT_580s1, df_f_pT_580s2, df_f_pT_750s1, df_f_pT_750s2, df_f_pT_750s3])
    df_f_tLT_arr = np.array([df_f_tLT_80s1, df_f_tLT_580s1, df_f_tLT_580s2, df_f_tLT_750s1, df_f_tLT_750s2, df_f_tLT_750s3])
    df_f_Qtot_arr = np.array([df_f_Qtot_80s1, df_f_Qtot_580s1, df_f_Qtot_580s2, df_f_Qtot_750s1, df_f_Qtot_750s2, df_f_Qtot_750s3])

    #Average of correction factors
    df_f_htrkEff_avg = np.average(df_f_htrkEff_arr)
    df_f_etrkEff_avg = np.average(df_f_etrkEff_arr)
    df_f_tgtBoil_avg = np.average(df_f_tgtBoil_arr)
    df_f_pT_avg = np.average(df_f_pT_arr)
    df_f_tLT_avg = np.average(df_f_tLT_arr)
    df_f_Qtot_avg = np.average(df_f_Qtot_arr)
    
    #Add correction factors quadratically (assuming they are uncorrelated)
    df_f_total = np.sqrt( df_f_htrkEff_avg**2 +  df_f_etrkEff_avg**2 + df_f_tgtBoil_avg**2 + df_f_pT_avg**2 + df_f_tLT_avg**2 + df_f_Qtot_avg**2 )

    fout_path='../../../Deep_CrossSections/average_kinematics/Em_final40MeV/normalization_systematics.txt'
    fout = open(fout_path, 'w')
    fout.write('#This file contains the run-by-run averaged (for all data sets) correction factor systematics on the cross section\n')
    fout.write('#These are relative errors, dsig / dig. Units: Multiply by 100 to convert to %%\n')
    fout.write('The last header is the quadrature sum of the headers, 0-6.  \n')
    fout.write('#! htrk_eff_syst[f,0]/  etrk_eff_syst[f,1]/  tgtBoil_syst[f,3]/  pAbs_syst[f,4]/  tLT_syst[f,5]/   Qtot_syst[f,6]/  total_norm_syst[f,7]/ \n')
    fout.write('%f  %f  %f  %f  %f  %f  %f '%(df_f_htrkEff_avg, df_f_etrkEff_avg, df_f_tgtBoil_avg, df_f_pT_avg, df_f_tLT_avg, df_f_Qtot_avg, df_f_total))
    fout.close()

    print('=====Relative Errors=====')
    print('hms_trfEff = ',df_f_htrkEff_avg*100.,' [%]')
    print('shms_trfEff = ',df_f_etrkEff_avg*100.,' [%]')
    print('tgt_boil = ',df_f_tgtBoil_avg*100.,' [%]')
    print('proton_abs = ',df_f_pT_avg*100.,' [%]')
    print('total_LT= ',df_f_tLT_avg*100.,' [%]')
    print('Qtot= ',df_f_Qtot_avg*100.,' [%]')
    print('df_f_total= ',df_f_total*100.,' [%]')
        

    '''
    avg_kin.add_header_comment('=====Relative Systematic Errors (from Normalization Factors)=====')
    avg_kin.add_header_comment('hms_trkEff = %.4f [%%]' % (df_f_htrkEff*100.))
    avg_kin.add_header_comment('shms_trkEff = %.4f [%%]' % (df_f_etrkEff*100.))
    avg_kin.add_header_comment('tgt_boil = %.4f [%%]' % (df_f_tgtBoil*100.))
    avg_kin.add_header_comment('proton_abs = %.4f [%%]' % (df_f_pT*100.))
    avg_kin.add_header_comment('total_LT= %.4f [%%]' % (df_f_tLT*100.))
    avg_kin.add_header_comment('Qtot= %.4f [%%]' % (df_f_Qtot*100.))
    avg_kin.add_header_comment('tot_norm_err= %.4f [%%]' % (relative_err_tot*100.))
    avg_kin.add_header_comment('=================================================================')
    avg_kin.save(avg_kin_file)
    '''

def main():

    print('Main')
    #Call method to calculate and combine normalization systematic errors

    #combine_norm_systematics(80, 'fsi', 1)
    #get_radbc_syst(fname, 80, 1)
    #plot_relative_error(fname, 80, 1)
    #plot_Xsec_Ratio(fname, 80, 1)
    #get_average_systematics()

if __name__=="__main__":
    main()

