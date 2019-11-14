import numpy as np
from LT.datafile import dfile
import LT.box as B
import os

#This code calculates the systematics due to the correction factors 
#in the data yield for each data set

#If, FullWeight = f_tgt * f_pAbs * f_tLT  * f_eTrkEff * f_pTrkEff * f_Qtot
#Experimental Xsec: sig_exp = Y_corr / P.S. = (Y_uncorr / P.S.) *  f_tgt * f_pAbs * f_tLT  * f_eTrkEff * f_pTrkEff * f_Qtot

#Each of the corrections has an associated uncertainty, df/f, therefore, the
#systematic error on the cross section (sig_exp ) is:  dsig_exp_syst2 = [sig_exp**2 * (df/f)**2 ]_tgtBoil + . . . +  [sig_exp**2 * (df/f)**2 ]_pAbs + ...
#A derivative has to be takem to determine the uncertainty in f.


#Tracking efficiencies
def get_trkEff_syst(fname_syst, pm_set=0, data_set=0):
    
    #This code reads the tracking efficiency and its uncertainty
    #for all runs of a given data set, and calculate the weighted 
    #average and calculated the systematic uncertanity on the Xsec.
    

    #open report 
    fname='../../root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)
    r = dfile(fname)

    #Get Tracking Eff. and its error
    htrk_eff = r['hTrkEff']
    htrk_eff_err = r['hTrkEff_err']

    etrk_eff = r['eTrkEff']
    etrk_eff_err = r['eTrkEff_err']

    #determine corr. factor and its error for each run of the data set
    f_htrk = 1. / htrk_eff
    f_etrk = 1. / etrk_eff

    df_htrk = -(1./ htrk_eff**2 ) *  htrk_eff_err
    df_etrk = -(1./ etrk_eff**2 ) *  etrk_eff_err

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

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from tracking efficiencies
    dsig2_htrk = sig_exp**2 * df_f_htrkEff **2
    dsig2_etrk = sig_exp**2 * df_f_etrkEff **2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_htrk', 'f')
    fsyst.add_key('dsig2_etrk', 'f')

    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_htrk'] =  dsig2_htrk[i]
        fsyst.data[i]['dsig2_etrk'] =  dsig2_etrk[i]
    fsyst.save(fname_syst)
    #if(particle=='e'):
    #    return dsig2_htrk
    #if(particle=='p'):
    #    return dsig2_etrk

def get_tgtboil_syst(fname_syst, pm_set, data_set):
  

    #open report
    fname='../../root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)
    r = dfile(fname)

    I = r['avg_current']     #in uA  (is an array if there are multiple runs per data set)
    tgt_boil = r['tgtBoil_factor']

    #Code to determine the target boiling factor systematic effect on the cross section.
    m =  0.00080029          #LD2 slope from fit [fract. yield loss / uA]
    sig_m = 0.00007037       #uncertainty for LD2 target boiling fit slope
    dI_I = 2.0/100.          #relative uncertainty in average current

    sig_I = dI_I * I             

    #f = 1 / (1. - m*I)       #correction factor to data yield 
    f = 1./ tgt_boil
    
    #derivatives of corr. factor
    df_dm = -I/(1. - m*I)**2
    df_dI = -m/(1. - m*I)**2
    
    df2 = (df_dm**2) * sig_m**2 + (df_dI**2) * sig_I**2     #error by quadrature
    df = np.sqrt(df2)    #uncertainty in correction factor

    
    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = df_w / f_w
    
    #----calculate systematic contribution---

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from target boiling
    dsig2_tgtBoil = sig_exp**2 * df_f **2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_tgtBoil', 'f')

    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_tgtBoil'] =  dsig2_tgtBoil[i]
    fsyst.save(fname_syst)

    #return df_f

def get_pT_syst(fname_syst, pm_set, data_set):
    
    #code to get systematics on proton absorption
    #The proton absorption for E12-10-003 was determined to 
    #be: 4.66 +/- 0.472 %,  the transmission is: (100-4.66 or 95.34) +/- 0.472%
    #It is assumed that this factor is relatively constant over a range of angles/momenta

    pT = 0.9534           #proton transmission factor (what fraction of coin. protons made it to form the trigger) --See docDB proton absorption Under Yero.
    d_pT = 0.472/100.     

    #correction factor to the data yield
    f = 1./pT
    df = -1/pT**2 * d_pT
    
    #relative error
    df_f = abs(df)/f
    
    #----calculate systematic contribution---

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from proton transmission factor
    dsig2_pT = sig_exp**2 * df_f **2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_pT', 'f')

    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_pT'] =  dsig2_pT[i]
    fsyst.save(fname_syst)

    #return df_f
    
def get_tLT_syst(fname_syst, pm_set, data_set):

    #code to get the total live time (from EDTM) systematics
    
    #open report
    fname='../../root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)
    r = dfile(fname)

    tLT = r['tLT']     #total live time [fraction or %/100]
    d_tLT = 1e-5          #assume uncertainty in total live time is negligible for now.
    
    f = 1./tLT                #correction factor
    df = -1./tLT**2 * d_tLT   #uncertainty in corr. factor
    
    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = df_w / f_w
    
    #----calculate systematic contribution---

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from total live time
    dsig2_tLT = sig_exp**2 * df_f **2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_tLT', 'f')

    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_tLT'] =  dsig2_tLT[i]
    fsyst.save(fname_syst)

    #return df_f
    
def get_Qtot_syst(fname_syst, pm_set, data_set):
    
    #code to get the systematics of the total accumulated charge (related to BCMs uncertainty)
      
    #open report
    fname='../../root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)
    r = dfile(fname)

    Q = r['charge']          #total accumulated charge (mC)
    dQ_Q = 2.0/100           #uncertainty in total charge (take 2% for now, conservative)

    dQ = dQ_Q * Q

    f =  1./Q             #correction factor
    df = -1/Q**2 * dQ     #uncertainty in corr. factor

    #Define the weight
    w = 1 / df**2

    #Calculate the weighted average
    f_w = np.sum(f*w) / np.sum(w)
    df_w = np.sqrt(1./np.sum(w))    #systematics [fractional, not in %] (uncertainty in weighted average of corr. factor)

    #relative error
    df_f = df_w / f_w
    
    #----calculate systematic contribution---

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from total charge
    dsig2_Qtot = sig_exp**2 * df_f **2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_Qtot', 'f')

    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_Qtot'] =  dsig2_Qtot[i]
    fsyst.save(fname_syst)

    #return df_f

def get_radbc_syst(fname_syst, pm_set, data_set):
    
    
    #code to estimate the systematics due to radiative corrections and bin-centering corrections
    #This code compares the pwia to fsi rad. corr. data Xsec, and 
    #estimate the relative error for each (Pm, th_nq) bin
    if(pm_set==80):
        fname='../../Deep_CrossSections/bin_centering_corrections/Em_nom40MeV/pm%i_laget_bc_corr.txt' % (pm_set)
        r = dfile(fname)
    else:    
        fname='../../Deep_CrossSections/bin_centering_corrections/Em_nom40MeV/pm%i_laget_bc_corr_set%i.txt' % (pm_set, data_set)
        r = dfile(fname)

    
    #Radiative Corrected Data Xsec
    dataXsec_pwiaRC = r['pwiaRC_dataXsec']
    dataXsec_pwiaRC_err = r['pwiaRC_dataXsec_err']
    
    dataXsec_fsiRC = r['fsiRC_dataXsec']
    dataXsec_fsiRC_err = r['fsiRC_dataXsec_err']

    #Bin Centered Corrected Data Xsec (Radiative Corrected Using FSI model)
    dataXsec_pwiaBC = r['fsiRC_dataXsec_pwiabc_corr']
    dataXsec_pwiaBC_err = r['fsiRC_dataXsec_pwiabc_corr_err']
    
    dataXsec_fsiBC = r['fsiRC_dataXsec_fsibc_corr']
    dataXsec_fsiBC_err = r['fsiRC_dataXsec_fsibc_corr_err']

    #Relative Differences and their associated errors
    relDiff_RC = (dataXsec_fsiRC - dataXsec_pwiaRC) / dataXsec_fsiRC    #relative difference in Radiative Corr. Xsec
    relDiff_RC_err = np.sqrt(  (dataXsec_pwiaRC/dataXsec_fsiRC**2)**2 *  dataXsec_fsiRC_err**2 + dataXsec_pwiaRC_err**2/dataXsec_fsiRC**2 )
    
    relDiff_BC = (dataXsec_fsiBC - dataXsec_pwiaBC) / dataXsec_fsiBC    #relative difference in Bin-Center Corr. Xsec
    relDiff_BC_err = np.sqrt( (dataXsec_pwiaBC/dataXsec_fsiBC**2)**2 *  dataXsec_fsiBC_err**2 + dataXsec_pwiaBC_err**2/dataXsec_fsiBC**2 )

    #----calculate systematic contribution---

    fsyst = dfile(fname_syst)                       #open systematic file name
    sig_exp = fsyst['fsiRC_dataXsec_fsibc_corr']    #data experimental cross section to be plotted
    
    #square of the systematic error contribution from radiative correction & bin centering correction
    dsig2_RC = sig_exp**2 * relDiff_RC**2
    dsig2_BC = sig_exp**2 * relDiff_BC**2

    #write contributions to the systematic data file
    fsyst.add_key('dsig2_RC', 'f')
    fsyst.add_key('dsig2_BC', 'f')

    fsyst.add_key('relDiff_RC', 'f')
    fsyst.add_key('relDiff_RC_err', 'f')
    fsyst.add_key('relDiff_BC', 'f')
    fsyst.add_key('relDiff_BC_err', 'f')


    #get 2d bin
    ib = fsyst['i_b']
    
    #loop over all bins
    for i, ib_i in enumerate(ib):
        fsyst.data[i]['dsig2_RC'] =  dsig2_RC[i]
        fsyst.data[i]['dsig2_BC'] =  dsig2_BC[i]
 
        fsyst.data[i]['relDiff_RC'] =  relDiff_RC[i]
        fsyst.data[i]['relDiff_RC_err'] =  relDiff_RC_err[i]
       
        fsyst.data[i]['relDiff_BC'] =  relDiff_BC[i]
        fsyst.data[i]['relDiff_BC_err'] =  relDiff_BC_err[i]

    fsyst.save(fname_syst)

       
def make_syst_copy(pm_set, data_set):

    #This code makes a copy of the bin centered corrected data file. To this new copy, (with extension '_syst'), the systematic
    #errors from the correction factors and kinematic factors will be added as new columns. These can then be added in quadrature to
    #get a final systematic error.

    #Make a copy of the bin-centerd corrected Xsec data file
    path = '/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/Deep_CrossSections/bin_centering_corrections/Em_nom40MeV/'
    if(pm_set==80):
        datafile = path + 'pm%i_laget_bc_corr.txt'%(pm_set)
        copyfile = path + 'pm%i_laget_bc_corr_syst.txt'%(pm_set)
    else:
        datafile = path + 'pm%i_laget_bc_corr_set%i.txt'%(pm_set, data_set)
        copyfile = path + 'pm%i_laget_bc_corr_set%i_syst.txt'%(pm_set, data_set)
    #Copy datafile
    os.system("cp "+datafile+" "+copyfile)

    return copyfile

def plot_relative_error(fname_syst, pm_set, data_set):
    
    #This code reads the '_syst.txt' data file with the newly added systematic contributions
    #The relative error, sqrt(dsig2) / sig_exp are plotted for each contribution to the systematics.

    fsyst = dfile(fname_syst)
    
    #Read the final data Xsec and the systematics contributions
    thnq         = fsyst['xb']
    pm           = fsyst['yb']
    dataXsec     = fsyst['fsiRC_dataXsec_fsibc_corr']
    dataXsec_err = fsyst['fsiRC_dataXsec_fsibc_corr_err']
     
    relDiff_RC = fsyst['relDiff_RC'] 
    relDiff_RC_err = fsyst['relDiff_RC_err'] 
    relDiff_BC = fsyst['relDiff_BC'] 
    relDiff_BC_err = fsyst['relDiff_BC_err']

    
    convert2NaN(dataXsec, value=-1)

    #Get Relative Errors
    dsig_stats   = dataXsec_err                    / dataXsec * 100.
    dsig_htrk    = np.sqrt(fsyst['dsig2_htrk'])    / dataXsec * 100.   #systematic errors from individual contributions
    dsig_etrk    = np.sqrt(fsyst['dsig2_etrk'])    / dataXsec * 100.
    dsig_tgtBoil = np.sqrt(fsyst['dsig2_tgtBoil']) / dataXsec * 100.
    dsig_pT      = np.sqrt(fsyst['dsig2_pT'])      / dataXsec * 100.
    dsig_tLT     = np.sqrt(fsyst['dsig2_tLT'])     / dataXsec * 100.
    dsig_Qtot    = np.sqrt(fsyst['dsig2_Qtot'])    / dataXsec * 100.
    dsig_RC      = np.sqrt(fsyst['dsig2_RC'])      / dataXsec * 100.
    dsig_BC      = np.sqrt(fsyst['dsig2_BC'])      / dataXsec * 100.
    
    

    dsig_tot2 = fsyst['dsig2_htrk'] + fsyst['dsig2_etrk'] + fsyst['dsig2_tgtBoil'] + fsyst['dsig2_pT'] + fsyst['dsig2_tLT'] + fsyst['dsig2_Qtot'] + fsyst['dsig2_RC'] + fsyst['dsig2_BC']
    dsig_tot2_v2 = fsyst['dsig2_htrk'] + fsyst['dsig2_etrk'] + fsyst['dsig2_tgtBoil'] + fsyst['dsig2_pT'] + fsyst['dsig2_tLT'] + fsyst['dsig2_Qtot'] 

    
    dsig_tot = np.sqrt(dsig_tot2) / dataXsec * 100.
    dsig_tot_v2 = np.sqrt(dsig_tot2_v2) / dataXsec * 100.

    #print('dsig_tot2=',dsig_tot2)
    #print('dsig_tot=',dsig_tot)

    #theta_nq array
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]



    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        y = np.array([0 for i in range(len(pm[thnq==ithnq]))])

        #Plot relative statistical error
        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.pl.xlim(0, 0.3)

        B.plot_exp(pm[thnq==ithnq], y, dsig_stats[thnq==ithnq], color='black', marker='D', label=r'statistical') #,  marker='D', color='black', label=r'statistics')      
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Relative Error [%]')
        B.pl.title(r'Relative Statistical Error $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('../norm_systematics_plots/dsig_stats_pm%i_thnq%i_eAng.pdf'%(pm_set, ithnq))
              
        #Plot relative systematic error
        fig2 = B.pl.figure(i+1)
        B.pl.clf()
        
        B.pl.xlim(0, 0.3)
        B.pl.ylim(-50, 50)
       
        B.plot_exp(pm[thnq==ithnq], relDiff_RC[thnq==ithnq]*100., relDiff_RC_err[thnq==ithnq]*100., color='black', marker='o', label=r'Rad. Corr Rel Err')   
        B.plot_exp(pm[thnq==ithnq], relDiff_BC[thnq==ithnq]*100., relDiff_BC_err[thnq==ithnq]*100., color='red', marker='s', label=r'BC. Corr Rel Err')   


        #B.plot_exp(pm[thnq==ithnq], y, dsig_htrk[thnq==ithnq], color='gray', marker='o', label=r'$h_{trk}$ syst.')   
        #B.plot_exp(pm[thnq==ithnq], y, dsig_etrk[thnq==ithnq], color='brown', marker='o', label=r'$e_{trk}$ syst.') 
        #B.plot_exp(pm[thnq==ithnq], y, dsig_tgtBoil[thnq==ithnq], color='red', marker='o', label=r'$tgt_{Boil}$ syst.')       
        #B.plot_exp(pm[thnq==ithnq], y, dsig_pT[thnq==ithnq], color='blue', marker='o', label=r'$p_{Abs}$ syst.')       
        #B.plot_exp(pm[thnq==ithnq], y, dsig_tLT[thnq==ithnq], color='green', marker='o', label=r'total live time syst.')       
        #B.plot_exp(pm[thnq==ithnq], y, dsig_Qtot[thnq==ithnq], color='magenta', marker='o', label=r'total charge syst..')       
        
        #B.plot_exp(pm[thnq==ithnq], y, dsig_RC[thnq==ithnq], color='darkviolet', marker='o', label=r'radiative corr. syst..')       
        #B.plot_exp(pm[thnq==ithnq], y, dsig_BC[thnq==ithnq], color='cyan', marker='o', label=r'bin center corr. syst..')       
        
        #B.plot_exp(pm[thnq==ithnq], y, dsig_tot[thnq==ithnq], color='black', marker='o', label=r'total syst..')       
        #B.plot_exp(pm[thnq==ithnq], y, dsig_tot_v2[thnq==ithnq], color='black', marker='o', label=r'total syst..')       


        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Relative Error [%]')
        B.pl.title(r'Relative Systematic Error $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('../norm_systematics_plots/RCBC_pm%i_thnq%i.pdf'%(pm_set, ithnq))




def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)
    
    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr

def plot_Xsec_Ratio(fname_syst, pm_set, data_set):
    

    #This code plots the ratio of dataXsec to PWIA
    fsyst = dfile(fname_syst)
    
    #Read the final data Xsec and the systematics contributions
    thnq         = fsyst['xb']
    pm           = fsyst['yb']
    dataXsec     = fsyst['fsiRC_dataXsec_fsibc_corr']
    dataXsec_err = fsyst['fsiRC_dataXsec_fsibc_corr_err']
    pwiaXsec     = fsyst['pwiaXsec_theory']

    R = dataXsec / pwiaXsec
    R_err = dataXsec_err / pwiaXsec

    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]


    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        #Plot relative statistical error
        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.pl.xlim(0, 0.3)
        B.pl.ylim(0., 2.0)

        B.plot_exp(pm[thnq==ithnq], R[thnq==ithnq], R_err[thnq==ithnq], color='black', marker='o', label=r'Ratio') #,  marker='D', color='black', label=r'statistics')      
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio')
        B.pl.title(r'Data to PWIA Xsec Ratio $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('../Xsec_Ratio/sig_ratio_pm%i_thnq%i.pdf'%(pm_set, ithnq))

def main():

    #filename of copied data file (this will be used to write systematics)
    #fname = make_syst_copy(80, 1)
    
    avg_kin_dir = "../../Deep_CrossSections/average_kinematics/Em_final40MeV/"
    final_Xsec_dir = "../../Deep_CrossSections/bin_centering_corrections/Em_final40MeV/"

    if(pm_set==80):
        avg_kin_file = 'pm%i_%s_norad_avgkin_systematics.txt'%(pm_set, model) 
        final_Xsec_file = 
    else:
        avg_kin_file = 'pm%i_%s_norad_avgkin_set%i_systematics.txt'%(pm_set, model, data_set)

    #get_trkEff_syst(fname, 80, 1)
    #get_tgtboil_syst(fname, 80, 1)
    #get_pT_syst(fname, 80, 1)
    #get_tLT_syst(fname, 80, 1)
    #get_Qtot_syst(fname, 80, 1)
    #get_radbc_syst(fname, 80, 1)

    #plot_relative_error(fname, 80, 1)
    #plot_Xsec_Ratio(fname, 80, 1)

if __name__=="__main__":
    main()
