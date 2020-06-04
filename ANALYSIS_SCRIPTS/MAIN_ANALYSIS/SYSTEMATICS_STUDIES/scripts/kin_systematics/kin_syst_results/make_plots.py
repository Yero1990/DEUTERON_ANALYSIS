import LT.box as B
from LT.datafile import dfile
import numpy as np
import os
import sys
from sys import argv
import numpy.ma as ma
import matplotlib.pyplot as plt
from matplotlib import rc

#Use latex commands (e.g. \textit ot \textbf)                                                                                                                 
rc('text', usetex=True)                                                                                                                                       
#Set default font to times new roman                                                                                                                          
font = {'family' : 'Times New Roman',                                                                                                                         
        'weight' : 'normal',                                                                                                                                  
        'size'   : 12                                                                                                                                       
}                                                                                                                                                           
plt.rc('font', **font) 


def plot_kin_syst():
    print('Plotting Kinematic Systematics')
    fname_80 = 'pm80_fsi_results.txt'

    pm80_sys, thnq80_sys, syst_err_80 = get_syst_error(80, 'fsi', 1)
    pm80_stat, thnq80_stat, stat_err_80 = get_stats_error(80, 1)
    stat_err_80 = stat_err_80 * 100.
    
    
    
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]
    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        y80 = np.array([0 for i in range(len(pm80_sys[thnq80_sys==ithnq]))])
        #y580set1 = np.array([0 for i in range(len(pm580set1_sys[thnq580set1_sys==ithnq]))])

        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.plot_exp(pm80_sys[thnq80_sys==ithnq], y80, syst_err_80[thnq80_sys==ithnq], marker='o', color='red', label='systematics error')
        #B.plot_exp(pm80_stat[thnq80_stat==ithnq], y80, stat_err_80[thnq80_stat==ithnq], marker='s', color='black', label='statistical error')
    
        B.pl.xlim(0, 0.3)
        B.pl.ylim(-20,20)
        B.pl.xlabel('Neutron Recoil Momenta [GeV/c]')
        B.pl.ylabel(r'Relative Error')
        B.pl.title(r'Relative Error (80MeV) $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()
        B.pl.savefig('./kin_sys_pm80_thnq%i.pdf'%(ithnq))


def plot_derivative(pm_set=0, model='', data_set=0):
    #Code that reads table of derivatives of Xsec w.r.to kinematics variables, 
    #(angles, momentum, beam energy) for each kinematic bin and plots vs Pmiss
    #The individual systematic errors are plotted as well

    #open derivative table in read mode.  (Units are in '%/mr' or '%/MeV')
    fname = '../summary_files/DervTable_pm%i_%s_set%i.txt'%(pm_set, model, data_set)
    derv_file = dfile(fname)

    pm = (derv_file['pm_bin'])
    
    thnq = derv_file['thnq_bin']
    #Get Xsec derivative w.r.to kin. variables (%/mrad or %/MeV)
    ds_dthe = derv_file['ds_dthe']
    ds_dphe = derv_file['ds_dphe']
    ds_dthp = derv_file['ds_dthp']
    ds_dphp = derv_file['ds_dphp']
    ds_dthb = derv_file['ds_dthb']   #out-of-plane beam direction
    ds_dphb = derv_file['ds_dphb']   #in-plane beam direction
    ds_def = derv_file['ds_def']
    ds_dE = derv_file['ds_dE']
    #Get Xsec Systematic Individual Relative Errors
    sig_the = derv_file['sig_the']
    sig_phe = derv_file['sig_phe']
    sig_thp = derv_file['sig_thp']
    sig_php = derv_file['sig_php']
    sig_thb = derv_file['sig_thb']   #out-of-plane beam direction
    sig_phb = derv_file['sig_phb']   #in-plane beam direction
    sig_ef = derv_file['sig_ef']
    sig_E = derv_file['sig_E']
    #Get Xsec Systematic Individual Correlated Relative Errors
    sig_the_thp = derv_file['sig_the_thp']
    sig_the_Ef = derv_file['sig_the_Ef']
    sig_the_Eb = derv_file['sig_the_Eb']
    sig_thp_Ef = derv_file['sig_thp_Ef']
    sig_thp_Eb = derv_file['sig_thp_Eb']
    sig_Ef_Eb = derv_file['sig_Ef_Eb']

    sig_tot = derv_file['sig_tot']    #total systematics (added in quadrature)

    #thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]
    thnq_arr = [35]
    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        y = np.array([0 for i in range(len(pm[thnq==ithnq]))])


        #============Plot Xsec Derivatives==================
        
        fig1 = B.pl.figure(i, figsize=(7,6))
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], ds_dthe[thnq==ithnq], marker='o', color='red', label=r'$\frac{d\sigma}{d\theta_{e}}$')
        #B.plot_exp(pm[thnq==ithnq], ds_dphe[thnq==ithnq], marker='s', color='red', label=r'$\frac{d\sigma}{d\phi_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthp[thnq==ithnq], marker='s', color='black', label=r'$\frac{d\sigma}{d\theta_{p}}$')
        #B.plot_exp(pm[thnq==ithnq], ds_dphp[thnq==ithnq], marker='<', color='green', label=r'$\frac{d\sigma}{d\phi_{p}}$')
        #B.plot_exp(pm[thnq==ithnq], ds_dthb[thnq==ithnq], marker='v', color='cyan', label=r'$\frac{d\sigma}{d\theta_{b}}$')
        #B.plot_exp(pm[thnq==ithnq], ds_dphb[thnq==ithnq], marker='>', color='magenta', label=r'$\frac{d\sigma}{d\phi_{b}}$')
        
        B.plot_exp(pm[thnq==ithnq], ds_def[thnq==ithnq], marker='^', color='blue', label=r'$\frac{d\sigma}{dE_{f}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dE[thnq==ithnq], marker='v', color='green', label=r'$\frac{d\sigma}{dE_{b}}$')
       

        if(pm_set==80):
            B.pl.xlim(0, 0.5)
        else:
            B.pl.xlim(0.4, 1.2)
        B.pl.xlabel(r'$p_{\mathrm{r}}$ [GeV/c]', fontsize=16)
        B.pl.ylabel(r'$\delta\sigma_{\mathrm{Laget,fsi}}$ [\%/mrad or \%/MeV]', fontsize=16)
        B.pl.title(r'Cross Section Derivatives: %i MeV (set%i), $\theta_{nq}=%i\pm5^{\circ}$'%(pm_set, data_set, ithnq), fontsize=15)
        B.pl.xticks(fontsize=14)
        B.pl.yticks(fontsize=14)
        B.pl.legend(loc='lower right', prop={'size':15}, fontsize=16, markerscale=1.5, frameon=True, framealpha=1.0)
        if(pm_set==80):
            B.pl.savefig('./kin_derv_pm%i_thnq%i.pdf'%(pm_set, ithnq))
        else:
            B.pl.savefig('./kin_derv_pm%iset%i_thnq%i.pdf'%(pm_set, data_set, ithnq))

       
        #============Plot Individual Systematic Relative Errors==================
        
        fig2 = B.pl.figure(i+1, figsize=(8,6))
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], y, sig_the[thnq==ithnq], marker='o', color='black', label=r'$d\sigma_{\theta_{e}}$', zorder=2)
        #B.plot_exp(pm[thnq==ithnq], y, sig_phe[thnq==ithnq], marker='s', color='red', label=r'$d\sigma_{\phi_{e}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_thp[thnq==ithnq], marker='o', color='blue', label=r'$d\sigma_{\theta_{p}}$', zorder=2)
        #B.plot_exp(pm[thnq==ithnq], y, sig_php[thnq==ithnq], marker='<', color='green', label=r'$d\sigma_{\phi_{p}}$')
        #B.plot_exp(pm[thnq==ithnq], y, sig_thb[thnq==ithnq], marker='v', color='cyan', label=r'$d\sigma_{\theta_{b}}$')
        #B.plot_exp(pm[thnq==ithnq], y, sig_phb[thnq==ithnq], marker='>', color='magenta', label=r'$d\sigma_{\phi_{b}}$')
        
        B.plot_exp(pm[thnq==ithnq], y, sig_ef[thnq==ithnq], marker='o', color='blueviolet', label=r'$d\sigma_{k_{\mathrm{f}}}$', zorder=2)
        B.plot_exp(pm[thnq==ithnq], y, sig_E[thnq==ithnq], marker='o', color='orange', label=r'$d\sigma_{E_{\mathrm{b}}}$', zorder=2)

        #Plot COrrelated Errors
        B.plot_exp(pm[thnq==ithnq], y, sig_the_thp[thnq==ithnq], marker='o', color='grey', label=r'$[d\sigma_{\theta_{e}},d\sigma_{\theta_{p}}]$', zorder=3)
        B.plot_exp(pm[thnq==ithnq], y, sig_the_Ef[thnq==ithnq], marker='o', color='green', label=r'$[d\sigma_{\theta_{e}}, dk_{\mathrm{f}}]$', zorder=3)
        B.plot_exp(pm[thnq==ithnq], y, sig_the_Eb[thnq==ithnq], marker='o', color='cyan', label=r'$[d\sigma_{\theta_{e}}, dE_{\mathrm{b}}]$', zorder=3)
        B.plot_exp(pm[thnq==ithnq], y, sig_thp_Ef[thnq==ithnq], marker='o', color='magenta', label=r'$[d\sigma_{\theta_{p}}, dk_{\mathrm{f}}]$', zorder=3)
        B.plot_exp(pm[thnq==ithnq], y, sig_thp_Eb[thnq==ithnq], marker='o', color='Maroon', label=r'$[d\sigma_{\theta_{p}}, dE_{\mathrm{b}}]$', zorder=3)
        B.plot_exp(pm[thnq==ithnq], y, sig_Ef_Eb[thnq==ithnq], marker='o', color='navy', label=r'$[dk_{\mathrm{f}}, dE_{\mathrm{b}}]$', zorder=3)


        eb = B.plot_exp(pm[thnq==ithnq], y, sig_tot[thnq==ithnq], marker='8', color='red', label=r'$d\sigma^{\mathrm{kin}}_{\mathrm{tot}}$', zorder=4)
        eb[-1][0].set_linestyle('--')
        
        if(pm_set==80):
            B.pl.xlim(0, 0.5)
            B.pl.ylim(-65, 65)
        else:
            B.pl.xlim(0.4, 1.2)
            B.pl.ylim(-15, 15)
        B.pl.xlabel('$p_{\mathrm{r}}$ [GeV/c]', fontsize=16)
        B.pl.ylabel(r'$\delta\sigma^{\mathrm{kin}}$ [\%]', fontsize=16)
        B.pl.title(r'Kinematic Systematic Errors: %i MeV (set%i), $\theta_{nq}=%i\pm5^{\circ}$'%(pm_set, data_set, ithnq), fontsize=15)
        B.pl.xticks(fontsize=14)
        B.pl.yticks(fontsize=14)
        B.pl.legend(ncol=3, loc='upper left', fontsize=14, prop={'size': 12}, markerscale=1.5, frameon=True, framealpha=1.0)
        #if(pm_set==80):
        #    B.pl.savefig('./kin_syst_contributions_pm%i_thnq%i.pdf'%(pm_set, ithnq))
        #else:
        #    B.pl.savefig('./kin_syst_contributions_pm%iset%i_thnq%i.pdf'%(pm_set, data_set, ithnq))
        B.pl.show()
       

      

def get_syst_error(pm_set=0, model='',data_set=0):
    #code that returns numpy array of kinematic systematics errors
    #stored in the average kin. files

    if (pm_set==80):
        fname = 'pm%s_%s_results.txt'%(pm_set, model)
    else:
        fname = 'pm%s_%s_set%i_results.txt'%(pm_set, model, data_set)

    kin_file = dfile(fname)
    thnq = kin_file['xb']
    pm = kin_file['yb']

    syst_err = kin_file['tot_err']

    return pm, thnq, syst_err


def get_stats_error(pm_set=0, data_set=0):
    #code that returns numpy array of statistical errors
    #stored in the bin0centered corrected data

    file_path='../../../../Deep_CrossSections/bin_centering_corrections/Em40MeV/'
    if (pm_set==80):
        fname = file_path+'pm%s_laget_bc_corr.txt'%(pm_set)
    else:
        fname = file_path+'pm%s_laget_bc_corr_set%i.txt'%(pm_set, data_set)

    kin_file = dfile(fname)
    thnq = kin_file['xb']
    pm = kin_file['yb']
        
    Xsec = kin_file['fsiRC_dataXsec_fsibc_corr']
    stats_err = kin_file['fsiRC_dataXsec_fsibc_corr_err']   #absolute cross section error
    stats_err = stats_err / Xsec                            #error relative to cross section
    return pm, thnq, stats_err


def compare_Xsec(pm_set=0, data_set=0):
    
    #Brief:  This code compares the derivatives of 

    #Read Derivatives From Werner's Code
    fwb_fsi_the = dfile('../summary_files/+1mr_eAngle/DervTable_pm80_fsi_set1.txt')      #assume +1mr eAngle uncertainty
    fwb_fsi_Pe = dfile('../summary_files/1e-3_eMomentum/DervTable_pm80_fsi_set1.txt')    #assume +1e-3 eMomentum relative uncertainty, dEf/Ef

    #Read Data Files Containing Pseudo-Data Cross Sections
    f1      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_nom40MeV/pm80_laget_bc_corr.txt')
    f2      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_ep1mr_thr40MeV/pm80_laget_bc_corr.txt')
    f3      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_ep1mr_rec40MeV/pm80_laget_bc_corr.txt')   #e- agnle offset in input file, but corrected in recon.
    f4      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_ep1MeV_thr40MeV/pm80_laget_bc_corr.txt')    #e- momentum varied by +1 MeV in input file, but corrected in recon (-1 MeV)
    f5      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_ep1MeV_rec40MeV/pm80_laget_bc_corr.txt')  #e- momentum varied by +1 MeV

    #Get Bin Center Values
    thnq = f1['xb']
    pm   = f1['yb']

    #Get Werner's Derivatives
    wb_ds_dthe_fsi = fwb_fsi_the['ds_dthe']   # % change in Xsec / 1mr in eAngle
    wb_ds_dPe_fsi = fwb_fsi_Pe['ds_def']         # % change in Xsec / 1MeV in eMomentum                                                                       

    #---Get Pseudo-Data Radiative Corrected Xsec---

    #nominal Xsec (nominal kinematics)
    dataXsec_fsi_nom = f1['fsiRC_dataXsec']
    dataXsec_fsi_nom_err = f1['fsiRC_dataXsec_err']

    #XSec with SHMS e- angle: +1mr offset on input file (thrown), but corrected (-1 mr) in SIMC reconstruced 
    dataXsec_ep1mr_thr_fsi = f2['fsiRC_dataXsec']
    dataXsec_ep1mr_thr_fsi_err = f2['fsiRC_dataXsec_err']

    #XSec with SHMS e- angle: +1mr offset on SIMC reconstruced 
    dataXsec_ep1mr_rec_fsi = f3['fsiRC_dataXsec']
    dataXsec_ep1mr_rec_fsi_err = f3['fsiRC_dataXsec_err']

    #XSec with SHMS e- momentum: +1MeV offset on input file (thrown), but corrected (-1 MeV) in SIMC reconstruced 
    dataXsec_ep1MeV_thr_fsi = f4['fsiRC_dataXsec']
    dataXsec_ep1MeV_thr_fsi_err = f4['fsiRC_dataXsec_err']
 
    #XSec with SHMS e- momentum: +1MeV offset on SIMC reconstruced 
    dataXsec_ep1MeV_rec_fsi = f5['fsiRC_dataXsec']
    dataXsec_ep1MeV_rec_fsi_err = f5['fsiRC_dataXsec_err']

    convert2NaN(dataXsec_fsi_nom, value=-1.)
    convert2NaN(dataXsec_ep1mr_thr_fsi, value=-1.)
    convert2NaN(dataXsec_ep1mr_rec_fsi, value=-1.)
    convert2NaN(dataXsec_ep1MeV_thr_fsi, value=-1.)
    convert2NaN(dataXsec_ep1MeV_rec_fsi, value=-1.)
    
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        #y = np.array([0 for i in range(len(pm[thnq==ithnq]))])

        
        #============eAngle Derivatives===============
      
        #Define Derivatives of Xsec w.r.to electron angle
        ds_dthe_ep1mr_thr_fsi = (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1mr_thr_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq] * 100.  # % / mr  change in XSec
        ds_dthe_ep1mr_rec_fsi = (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1mr_rec_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq] * 100.  

        #Error Propagation on relative error (thown):  r = (a-b)/a -->  dr2 = (dr_da)**2 *sig_a**2 + (dr_db)**2 *sig_b**2  (assuming 'a' and 'b' are un-correlated)
        dr_da_1 = 1./(dataXsec_fsi_nom[thnq==ithnq]) - (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1mr_thr_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq]**2
        dr_db_1 = -1./dataXsec_fsi_nom[thnq==ithnq]
        dr_err_eAng_thr = np.sqrt( (dr_da_1 *  dataXsec_fsi_nom_err[thnq==ithnq])**2 + (dr_db_1 * dataXsec_ep1mr_thr_fsi_err[thnq==ithnq])**2 ) * 100.
        
        #Error Propagation on relative error (rec)
        dr_da_2 = 1./(dataXsec_fsi_nom[thnq==ithnq]) - (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1mr_rec_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq]**2
        dr_db_2 = -1./dataXsec_fsi_nom[thnq==ithnq]
        dr_err_eAng_rec = np.sqrt( (dr_da_2 *  dataXsec_fsi_nom_err[thnq==ithnq])**2 + (dr_db_2 * dataXsec_ep1mr_rec_fsi_err[thnq==ithnq])**2 ) * 100.
        
        #==========eMomentum Derivatives================

        #Define Derivatives of Xsec w.r.to electron Momentum
        ds_dPe_ep1MeV_thr_fsi = (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1MeV_thr_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq] * 100.  # % / mr  change in XSec
        ds_dPe_ep1MeV_rec_fsi = (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1MeV_rec_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq] * 100.  # % / mr  change in XSec
        
        #Error Propagation on relative error (thown):  r = (a-b)/a -->  dr2 = (dr_da)**2 *sig_a**2 + (dr_db)**2 *sig_b**2  (assuming 'a' and 'b' are un-correlated)
        dr_da_3 = 1./(dataXsec_fsi_nom[thnq==ithnq]) - (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1MeV_thr_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq]**2
        dr_db_3 = -1./dataXsec_fsi_nom[thnq==ithnq]
        dr_err_eMom_thr = np.sqrt( (dr_da_3 *  dataXsec_fsi_nom_err[thnq==ithnq])**2 + (dr_db_3 * dataXsec_ep1MeV_thr_fsi_err[thnq==ithnq])**2 ) * 100.
      
        #Error Propagation on relative error (rec)
        dr_da_4 = 1./(dataXsec_fsi_nom[thnq==ithnq]) - (dataXsec_fsi_nom[thnq==ithnq] -  dataXsec_ep1MeV_rec_fsi[thnq==ithnq])/dataXsec_fsi_nom[thnq==ithnq]**2
        dr_db_4 = -1./dataXsec_fsi_nom[thnq==ithnq]
        dr_err_eMom_rec = np.sqrt( (dr_da_4 *  dataXsec_fsi_nom_err[thnq==ithnq])**2 + (dr_db_4 * dataXsec_ep1MeV_rec_fsi_err[thnq==ithnq])**2 ) * 100.
            


        #============Plot Xsec e- Angle Derivatives==================
        
        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], wb_ds_dthe_fsi[thnq==ithnq], marker='D', color='black', label=r'WB FSI: $\frac{d\sigma}{d\theta_{e}}$')      
        B.plot_exp(pm[thnq==ithnq], ds_dthe_ep1mr_rec_fsi, dr_err_eAng_rec,  marker='o', markerfacecolor='red', color='red', label=r'pseudo DATA FSI (+1 mr recon.).: $\frac{d\sigma}{d\theta_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthe_ep1mr_thr_fsi, dr_err_eAng_thr,  marker='o', markerfacecolor='blue', color='blue', label=r'pseudo DATA FSI (+1 mr thrown).: $\frac{d\sigma}{d\theta_{e}}$')

        B.pl.xlim(0, 0.5)
        B.pl.ylim(-50,50)

        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Cross Section Variations [%/mrad or %/MeV]')
        B.pl.title(r'Xsec Derivatives $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('plots/kin_derv_pm%i_thnq%i_eAng.pdf'%(pm_set, ithnq))
    
        fig2 = B.pl.figure(i)
        B.pl.clf()
        
        B.plot_exp(pm[thnq==ithnq], wb_ds_dPe_fsi[thnq==ithnq], marker='D', color='black', label=r'WB FSI: $\frac{d\sigma}{dP_{e}}$')                        
        B.plot_exp(pm[thnq==ithnq], ds_dPe_ep1MeV_rec_fsi, dr_err_eMom_rec,  marker='o', markerfacecolor='red', color='red', label=r'pseudo DATA FSI (+1 MeV recon.): $\frac{d\sigma}{dP_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dPe_ep1MeV_thr_fsi, dr_err_eMom_thr,  marker='o', markerfacecolor='blue', color='blue', label=r'pseudo DATA FSI (+1 MeV thrown): $\frac{d\sigma}{dP_{e}}$')

        B.pl.xlim(0, 0.5)
        B.pl.ylim(-50,50)

        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Cross Section Variations [%/mrad or %/MeV]')
        B.pl.title(r'Xsec Derivatives $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('plots/kin_derv_pm%i_thnq%i_eMom.pdf'%(pm_set, ithnq))

def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)
    
    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr

def main():
    print('Entering Main . . .')

    stats_thrs = 0.5  #Statistics Threshold (ONLY use data Xsec which are withih the statistical uncertainty of the mean Xsec)
    #plot_kin_syst()


    plot_derivative(80, 'fsi', 1)

    #compare_Xsec(80, 1)
    plot_derivative(580, 'fsi', 2)
    plot_derivative(750, 'fsi', 1)

    '''
    pm80_sys, thnq80_sys, syst_err_80 = get_syst_error(80, 'fsi', 1)
    pm80_stat, thnq80_stat, stat_err_80 = get_stats_error(80, 1)
    stat_err_80 = stat_err_80 * 100.
    
    
    #pm580set1_sys, thnq580set1_sys, syst_err_580set1 = get_syst_error(580, 'fsi', 1)
    #pm580set1_stat, thnq580set1_stat, stat_err_580set1 = get_stats_error(580, 1)
    #stat_err_580set1 = stat_err_580set1 * 100.
    '''
    
    '''
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]
    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        y80 = np.array([0 for i in range(len(pm80_sys[thnq80_sys==ithnq]))])
        #y580set1 = np.array([0 for i in range(len(pm580set1_sys[thnq580set1_sys==ithnq]))])

        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.plot_exp(pm80_sys[thnq80_sys==ithnq], y80, syst_err_80[thnq80_sys==ithnq], marker='o', color='red', label='systematics error')
        B.plot_exp(pm80_stat[thnq80_stat==ithnq], y80, stat_err_80[thnq80_stat==ithnq], marker='s', color='black', label='statistical error')
    
        B.pl.xlim(0, 0.3)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Relative Error')
        B.pl.title(r'Relative Error (80MeV) $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()
        B.pl.savefig('plots/kin_sys_pm80_thnq%i.pdf'%(ithnq))
        
        
        #----------------------
        fig2 = B.pl.figure(i+1)
        B.pl.clf()

        B.plot_exp(pm580set1_sys[thnq580set1_sys==ithnq], y580set1, syst_err_580set1[thnq580set1_sys==ithnq], marker='o', color='red', label='systematics error')
        B.plot_exp(pm580set1_stat[thnq580set1_stat==ithnq], y580set1, stat_err_580set1[thnq580set1_stat==ithnq], marker='s', color='black', label='statistical error')
    
        B.pl.xlim(0.4, 0.9)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Relative Error')
        B.pl.title(r'Relative Error (580 MeV, set1): $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()
        B.pl.savefig('plots/kin_sys_pm580set1_thnq%i.pdf'%(ithnq))
        

        
        syst_err_580set1 = get_syst_error(580, 'fsi', 1)
        stat_err_580set1 = get_stats_error(580, 1)
        
        syst_err_580set2 = get_syst_error(580, 'fsi', 2)
        stat_err_580set2 = get_stats_error(580, 2)
        
        syst_err_750set1 = get_syst_error(750, 'fsi', 1)
        stat_err_750set1 = get_stats_error(750, 1)
        
        syst_err_750set2 = get_syst_error(750, 'fsi', 2)
        stat_err_750set2 = get_stats_error(750, 2)
        
        syst_err_750set3 = get_syst_error(750, 'fsi', 2)
        stat_err_750set3 = get_stats_error(750, 2)
        '''


if __name__=="__main__":
    main()
