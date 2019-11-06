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
    fXsec = dfile(final_Xsec_file)         #open final Xsec data file 
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'                   
    
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

    print('====Pm: %i (set %i) :: Tracking Eff.======'%(pm_set, data_set))
    print('hms_df/f=',df_f_htrk_syst)
    print('shms_df/f=',df_f_etrk_syst)

    print('hms_df/f_avg=', df_f_htrk_avg)
    print('shms_df/f_avg=', df_f_etrk_avg)
          
    print('hms_df/f_quad=', df_f_htrk_quad)
    print('shms_df/f_quad=', df_f_etrk_quad)
      

    #Determine Weighted Average of correction factor
    
    #define the weights
    w_htrk =  1. / df_htrk**2
    w_etrk =  1. / df_etrk**2
    

    #weighted average of corr. factor
    fw_htrkEff = np.sum(f_htrk * w_htrk)/np.sum(w_htrk)
    fw_etrkEff = np.sum(f_etrk * w_etrk)/np.sum(w_etrk)
    

    dfw_htrkEff = np.sqrt(1./np.sum(w_htrk)) 
    dfw_etrkEff = np.sqrt(1./np.sum(w_etrk)) 

    trk_eff_syst = np.array([dfw_etrkEff, dfw_htrkEff])

    #relative error, df / f
    df_f_htrkEff =  dfw_htrkEff / fw_htrkEff
    df_f_etrkEff =  dfw_etrkEff / fw_etrkEff
    
    #----calculate systematic contribution---

    sig_exp = fXsec['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    sig_exp = convert2NaN(sig_exp, value=-1.0)

    #square of the systematic error contribution from tracking efficiencies
    dsig2_htrk = sig_exp**2 * df_f_htrkEff**2
    dsig2_etrk = sig_exp**2 * df_f_etrkEff**2

    #write contributions to the systematic data file
    avg_kin.add_key('dsig_syst_htrk', 'f')
    avg_kin.add_key('dsig_syst_etrk', 'f')

    #get 2d bin
    ib = avg_kin['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_syst_htrk'] =  df_f_htrkEff
        avg_kin.data[i]['dsig_syst_etrk'] =  df_f_etrkEff
    avg_kin.save(avg_kin_file)

    return [df_f_htrk_avg, dsig2_htrk, df_f_etrk_avg, dsig2_etrk]

def get_tgtboil_syst(pm_set=0, model='', data_set=0):

    #This code calculated the systematic uncertainty on the data Xsec from the uncertainty in
    #the target boiling factor.

    
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file
    fXsec = dfile(final_Xsec_file)         #open final Xsec data file 
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'                   
    
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
    
    print('====Pm: %i (set %i) :: Target Boiling======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)


    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = df_w / f_w
    
    #----calculate systematic contribution---

    sig_exp = fXsec['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    sig_exp = convert2NaN(sig_exp, value=-1.0)

    #square of the systematic error contribution from target boiling
    dsig2_tgtBoil = sig_exp**2 * df_f**2

    #write contributions to the systematic data file
    avg_kin.add_key('dsig_syst_tgtBoil', 'f')

    #get 2d bin
    ib = avg_kin['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_syst_tgtBoil'] =  df_f
    avg_kin.save(avg_kin_file)
    
    return [df_f_avg, dsig2_tgtBoil]

def get_pT_syst(pm_set=0, model='', data_set=0):
    
    #code to get systematics on proton absorption
    #The proton absorption for E12-10-003 was determined to 
    #be: 4.66 +/- 0.472 %,  the transmission is: (100-4.66 or 95.34) +/- 0.472%
    #It is assumed that this factor is relatively constant over a range of angles/momenta

    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file
    fXsec = dfile(final_Xsec_file)         #open final Xsec data file 
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'                   
 
    
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

    print('====Pm: %i (set %i) : Proton Transmission======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)

    #----calculate systematic contribution---
    sig_exp = fXsec['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    sig_exp = convert2NaN(sig_exp, value=-1.0)

    #square of the systematic error contribution from proton transmission factor
    dsig2_pT = sig_exp**2 * df_f_syst **2

    #write contributions to the systematic data file
    avg_kin.add_key('dsig_syst_pT', 'f')

    #get 2d bin
    ib = avg_kin['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_syst_pT'] =  df_f_avg
    avg_kin.save(avg_kin_file)
    
    return [df_f_avg, dsig2_pT]
    
def get_tLT_syst(pm_set=0, model='', data_set=0):

    #code to get the total live time (from EDTM) systematics
    
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file
    fXsec = dfile(final_Xsec_file)         #open final Xsec data file 
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'  

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
    
    print('====Pm: %i (set %i) :: Total Live Time======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)

    
    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = df_w / f_w     
    
    #----calculate systematic contribution---
    sig_exp = fXsec['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    sig_exp = convert2NaN(sig_exp, value=-1.0)

    #square of the systematic error contribution from total live time
    dsig2_tLT = sig_exp**2 * df_f **2

    #write contributions to the systematic data file
    avg_kin.add_key('dsig_syst_tLT', 'f')

    #get 2d bin
    ib = avg_kin['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_syst_tLT'] =  df_f    #5% systematics or squared (0.05**2 = 0.0025)
    avg_kin.save(avg_kin_file)

    return [df_f_avg, dsig2_tLT]
    
def get_Qtot_syst(pm_set=0, model='', data_set=0):
    
    #code to get the systematics of the total accumulated charge (related to BCMs uncertainty)
      
    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open report 
    r = dfile(report_file)                 #open report file
    fXsec = dfile(final_Xsec_file)         #open final Xsec data file 
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'   

    r = dfile(report_file)

    Q = r['charge']          #total accumulated charge (mC)
    dQ_Q = 2.0/100           #uncertainty in total charge (take 2% for now, conservative)

    dQ = dQ_Q * Q

    f =  1./Q             #correction factor
    df = -1/Q**2 * dQ     #uncertainty in corr. factor
    
    #relative systematic error (run-by-run) array
    df_f_syst = np.abs(df) / f
    
    #average of relative systematic error (per data set)
    df_f_avg = np.average(df_f_syst)

    #run-by-run systematic added in quadrature
    df_f_quad = np.sqrt(np.sum(df_f_syst**2))
    
    print('====Pm: %i (set %i) :: Total Charge======'%(pm_set, data_set))
    print('df/f=',df_f_syst)
    print('df/f_avg=',df_f_avg)
    print('df/f_quad=',df_f_quad)
    

    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = 0.02 #for now, assume total relative uncertainty in charge is 2% :: df_w / f_w


    #----calculate systematic contribution---
    sig_exp = fXsec['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    sig_exp = convert2NaN(sig_exp, value=-1.0)

    #square of the systematic error contribution from total charge
    dsig2_Qtot = sig_exp**2 * df_f**2

    #write contributions to the systematic data file
    avg_kin.add_key('dsig_syst_Qtot', 'f')

    #get 2d bin
    ib = avg_kin['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_syst_Qtot'] =  df_f
    avg_kin.save(avg_kin_file)
    
    return [df_f_avg, dsig2_Qtot]


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


def combine_norm_systematics(pm_set=0, model='', data_set=0):
    
    #This code call all the utilities function to write their systematics to file as well as 
    #combines the systematic contributions to the cross sections in quadrature

    get_trkEff_syst(pm_set, model, data_set)
    get_tgtboil_syst(pm_set, model, data_set)
    get_pT_syst(pm_set, model, data_set)
    get_tLT_syst(pm_set, model, data_set)
    get_Qtot_syst(pm_set, model, data_set)

    avg_kin_file, final_Xsec_file, report_file = get_filenames(pm_set, model, data_set)

    #open average kin. file to write systematics
    avg_kin = dfile(avg_kin_file)          #open avg kin file (assumed to have '_systematics.txt extension'   
        
    #Call utilities functions
    df_f_htrkEff, dsig2_htrk, df_f_etrkEff, dsig2_etrk = get_trkEff_syst(pm_set, model, data_set)
    df_f_tgtBoil, dsig2_tgtBoil = get_tgtboil_syst(pm_set, model, data_set)
    df_f_pT, dsig2_pT = get_pT_syst(pm_set, model, data_set)
    df_f_tLT, dsig2_tLT = get_tLT_syst(pm_set, model, data_set)
    df_f_Qtot, dsig2_Qtot = get_Qtot_syst(pm_set, model, data_set)

    #Add absolute Xsec systematic errors in quadrature
    dsig2_norm_tot = dsig2_htrk + dsig2_etrk + dsig2_tgtBoil + dsig2_pT + dsig2_tLT + dsig2_Qtot

    #Add relative errors in quadrature
    relative_err2_tot = df_f_htrkEff**2 + df_f_etrkEff**2 + df_f_tgtBoil**2 + df_f_pT**2 +  df_f_tLT**2 + df_f_Qtot**2
    relative_err_tot = np.sqrt(relative_err2_tot)

    #write total contribution to the systematic data file
    avg_kin.add_key('dsig_norm_tot', 'f')

    #loop over all bins
    ib = avg_kin['i_b']    
    for i, ib_i in enumerate(ib):
        avg_kin.data[i]['dsig_norm_tot'] = relative_err_tot   
    avg_kin.save(avg_kin_file)

    print('=====Relative Errors=====')
    print('hms_trfEff = ',df_f_htrkEff*100.,' [%]')
    print('shms_trfEff = ',df_f_etrkEff*100.,' [%]')
    print('tgt_boil = ',df_f_tgtBoil*100.,' [%]')
    print('proton_abs = ',df_f_pT*100.,' [%]')
    print('total_LT= ',df_f_tLT*100.,' [%]')
    print('Qtot= ',df_f_Qtot*100.,' [%]')
    print('tot_norm_err= ',relative_err_tot*100,' [%]')

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

def main():

    #Call method to calculate and combine normalization systematic errors

    #combine_norm_systematics(80, 'fsi', 1)
    #get_radbc_syst(fname, 80, 1)
    #plot_relative_error(fname, 80, 1)
    #plot_Xsec_Ratio(fname, 80, 1)

    get_trkEff_syst(580, 'fsi', 1)
    get_tgtboil_syst(580, 'fsi', 1)
    get_pT_syst(580, 'fsi', 1)
    get_tLT_syst(580, 'fsi', 1)
    get_Qtot_syst(580, 'fsi', 1)

if __name__=="__main__":
    main()

