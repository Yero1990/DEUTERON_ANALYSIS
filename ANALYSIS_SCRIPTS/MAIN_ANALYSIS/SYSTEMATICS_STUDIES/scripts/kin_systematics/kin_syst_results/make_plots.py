import LT.box as B
from LT.datafile import dfile
import numpy as np
import os
import sys
from sys import argv
import numpy.ma as ma



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
        B.plot_exp(pm80_stat[thnq80_stat==ithnq], y80, stat_err_80[thnq80_stat==ithnq], marker='s', color='black', label='statistical error')
    
        B.pl.xlim(0, 0.3)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Relative Error')
        B.pl.title(r'Relative Error (80MeV) $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()
        B.pl.savefig('plots/kin_sys_pm80_thnq%i.pdf'%(ithnq))


def plot_derivative(pm_set=0, model='', data_set=0):
    #Code that reads table of derivatives of Xsec w.r.to kinematics variables, 
    #(angles, momentum, beam energy) for each kinematic bin and plots vs Pmiss
    #The relative systematic errors are plotted as well

    #open derivative table in read mode.  (Units are in '%/mr' or '%/MeV')
    fname = '../summary_files/DervTable_pm%i_%s_set%i.txt'%(pm_set, model, data_set)
    derv_file = dfile(fname)

    pm = derv_file['pm_bin']
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
    sig_tot = derv_file['sig_tot']    #total systematics (added in quadrature)

    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        y = np.array([0 for i in range(len(pm[thnq==ithnq]))])


        #============Plot Xsec Derivatives==================
        
        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], ds_dthe[thnq==ithnq], marker='o', color='black', label=r'$\frac{d\sigma}{d\theta_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dphe[thnq==ithnq], marker='s', color='red', label=r'$\frac{d\sigma}{d\phi_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthp[thnq==ithnq], marker='^', color='blue', label=r'$\frac{d\sigma}{d\theta_{p}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dphp[thnq==ithnq], marker='<', color='green', label=r'$\frac{d\sigma}{d\phi_{p}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthb[thnq==ithnq], marker='v', color='cyan', label=r'$\frac{d\sigma}{d\theta_{b}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dphb[thnq==ithnq], marker='>', color='magenta', label=r'$\frac{d\sigma}{d\phi_{b}}$')
        
        B.plot_exp(pm[thnq==ithnq], ds_def[thnq==ithnq], marker='d', color='blueviolet', label=r'$\frac{d\sigma}{dE_{f}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dE[thnq==ithnq], marker='h', color='orange', label=r'$\frac{d\sigma}{dE_{b}}$')
       

        if(pm_set==80):
            B.pl.xlim(0, 0.4)
        else:
            B.pl.xlim(0.4, 1.1)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Cross Section Variations [%/mrad or %/MeV]')
        B.pl.title(r'Xsec Derivatives $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        if(pm_set==80):
            B.pl.savefig('plots/kin_derv_pm%i_thnq%i.pdf'%(pm_set, ithnq))
        else:
            B.pl.savefig('plots/kin_derv_pm%iset%i_thnq%i.pdf'%(pm_set, data_set, ithnq))

       
        #============Plot Individual Systematic Relative Errors==================
        
        fig2 = B.pl.figure(i+1)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], y, sig_the[thnq==ithnq], marker='o', color='black', label=r'$d\sigma_{\theta_{e}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_phe[thnq==ithnq], marker='s', color='red', label=r'$d\sigma_{\phi_{e}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_thp[thnq==ithnq], marker='^', color='blue', label=r'$d\sigma_{\theta_{p}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_php[thnq==ithnq], marker='<', color='green', label=r'$d\sigma_{\phi_{p}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_thb[thnq==ithnq], marker='v', color='cyan', label=r'$d\sigma_{\theta_{b}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_phb[thnq==ithnq], marker='>', color='magenta', label=r'$d\sigma_{\phi_{b}}$')
        
        B.plot_exp(pm[thnq==ithnq], y, sig_ef[thnq==ithnq], marker='d', color='blueviolet', label=r'$d\sigma_{E_{f}}$')
        B.plot_exp(pm[thnq==ithnq], y, sig_E[thnq==ithnq], marker='h', color='orange', label=r'$d\sigma_{E_{b}}$')
        
        eb = B.plot_exp(pm[thnq==ithnq], y, sig_tot[thnq==ithnq], marker='8', color='grey', label=r'$d\sigma_{total}$')
        eb[-1][0].set_linestyle('--')
        
        if(pm_set==80):
            B.pl.xlim(0, 0.4)
        else:
            B.pl.xlim(0.4, 1.1)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Kinematics Systematic Errors [%]')
        B.pl.title(r'Systematic Errors: $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='xx-small', markerscale=0.2)
        if(pm_set==80):
            B.pl.savefig('plots/kin_syst_pm%i_thnq%i.pdf'%(pm_set, ithnq))
        else:
            B.pl.savefig('plots/kin_syst_pm%iset%i_thnq%i.pdf'%(pm_set, data_set, ithnq))

       

      

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
    #code that compares change in the data Xsec / mr  (comparing two different files in which the SHMS e' angle was changed by +1mr)
    # [(Xsec_nom - Xsec_+1mr) / Xsec_nom ] / 1mr  --> relative change in Xsec when angle is changed by 1 mr.

    f1      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_nom40MeV/pm80_laget_bc_corr.txt')
    f2      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_yptarp1mr40MeV/pm80_laget_bc_corr.txt')
    f3      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_yptarm1mr40MeV/pm80_laget_bc_corr.txt')
    f4      = dfile('../../../../Deep_CrossSections/bin_centering_corrections/Em_the_p1mr40MeV/pm80_laget_bc_corr.txt')

    fwb_fsi = dfile('../summary_files/DervTable_pm80_fsi_set1.txt')
    #fwb_pwia = dfile('../summary_files/DervTable_pm80_pwia_set1.txt')

    thnq = f1['xb']
    pm   = f1['yb']


    wb_ds_dthe_fsi = fwb_fsi['ds_dthe']
    #wb_ds_dthe_pwia = fwb_pwia['ds_dthe']

    dataXsec_nom_bc = f1['fsiRC_dataXsec_fsibc_corr']
    dataXsec_p1mr_bc = f2['fsiRC_dataXsec_fsibc_corr']
    dataXsec_m1mr_bc = f3['fsiRC_dataXsec_fsibc_corr']
    dataXsec_the_p1mr_bc = f4['fsiRC_dataXsec_fsibc_corr']

    #dataXsec_nom = f1['fsiRC_dataXsec']
    #dataXsec_p1mr = f2['fsiRC_dataXsec']
    #dataXsec_m1mr = f3['fsiRC_dataXsec']
   
    fsiXsec_nom = f1['fsiXsec_theory']
    fsiXsec_p1mr = f2['fsiXsec_theory']
    fsiXsec_m1mr = f3['fsiXsec_theory']



    pwiaXsec_nom = f1['pwiaXsec_theory']
    pwiaXsec_p1mr = f2['pwiaXsec_theory']
    pwiaXsec_m1mr = f3['pwiaXsec_theory']

    #convert to NaN if value is found to be -1. (this way, plotting is ignored for NaN, while it is not for -1.)
    #convert2NaN(dataXsec_nom, value=-1.)
    #convert2NaN(dataXsec_p1mr, value=-1.)
    #convert2NaN(dataXsec_m1mr, value=-1.)
        
    convert2NaN(dataXsec_nom_bc, value=-1.)
    convert2NaN(dataXsec_p1mr_bc, value=-1.)
    convert2NaN(dataXsec_m1mr_bc, value=-1.)
    convert2NaN(dataXsec_the_p1mr_bc, value=-1.)

    convert2NaN(fsiXsec_nom,  value=-1.)
    convert2NaN(fsiXsec_p1mr,  value=-1.)
    convert2NaN(fsiXsec_m1mr,  value=-1.)

    convert2NaN(pwiaXsec_nom, value=-1.)
    convert2NaN(pwiaXsec_p1mr, value=-1.)
    convert2NaN(pwiaXsec_m1mr, value=-1.)



    
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
               
        y = np.array([0 for i in range(len(pm[thnq==ithnq]))])

        ds_dthe_data_bc_p1mr = (dataXsec_nom_bc[thnq==ithnq] -  dataXsec_p1mr_bc[thnq==ithnq])/dataXsec_nom_bc[thnq==ithnq] * 100.  # % / mr  change in XSec
        ds_dthe_data_bc_m1mr = (dataXsec_nom_bc[thnq==ithnq] -  dataXsec_m1mr_bc[thnq==ithnq])/dataXsec_nom_bc[thnq==ithnq] * 100.  # % / mr  change in XSec
        
        ds_dthe_data_bc_the_p1mr = (dataXsec_nom_bc[thnq==ithnq] -  dataXsec_the_p1mr_bc[thnq==ithnq])/dataXsec_nom_bc[thnq==ithnq] * 100.  # % / mr  change in XSec

        ds_dthe_pwia = (pwiaXsec_nom[thnq==ithnq] -  pwiaXsec_p1mr[thnq==ithnq])/pwiaXsec_nom[thnq==ithnq] * 100.  # % / mr  change in XSec
        ds_dthe_fsi = (fsiXsec_nom[thnq==ithnq] -  fsiXsec_p1mr[thnq==ithnq])/fsiXsec_nom[thnq==ithnq] * 100.  # % / mr  change in XSec


        #============Plot Xsec Derivatives==================
        
        fig1 = B.pl.figure(i)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], wb_ds_dthe_fsi[thnq==ithnq], marker='D', color='black', label=r'WB FSI: $\frac{d\sigma}{d\theta_{e}}$')

        #B.plot_exp(pm[thnq==ithnq], ds_dthe_data, marker='s', color='red', label=r'DATA (rad corr.): $\frac{d\sigma}{d\theta_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthe_data_bc_p1mr, marker='s', markerfacecolor='None', color='red', label=r'DATA (yptar+1mr).: $\frac{d\sigma}{d\theta_{e}}$')

        #B.plot_exp(pm[thnq==ithnq], ds_dthe_data_bc_the_p1mr, marker='s', color='red', label=r'DATA ($\theta_{e}$+1mr).: $\frac{d\sigma}{d\theta_{e}}$')

        B.plot_exp(pm[thnq==ithnq], ds_dthe_data_bc_m1mr, marker='o', markerfacecolor='None', color='blue', label=r'DATA (yptar-1mr).: $\frac{d\sigma}{d\theta_{e}}$')

        B.plot_exp(pm[thnq==ithnq], ds_dthe_fsi, marker='^', color='green', label=r'theory FSI (yptar+1mr): $\frac{d\sigma}{d\theta_{e}}$')
        B.plot_exp(pm[thnq==ithnq], ds_dthe_pwia, marker='v', color='magenta', label=r'theory PWIA (yptar+1mr): $\frac{d\sigma}{d\theta_{e}}$')

        B.pl.xlim(0, 0.5)
        B.pl.ylim(-100,100)

        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Cross Section Variations [%/mrad or %/MeV]')
        B.pl.title(r'Xsec Derivatives $P_{m}$=%i (set%i) MeV, $\theta_{nq}:(%i, %i)$'%(pm_set, data_set, th_nq_min, th_nq_max))
        B.pl.legend(loc='upper right', fontsize='x-small', markerscale=1.0)
        B.pl.savefig('plots/kin_derv_pm%i_thnq%i_compare.pdf'%(pm_set, ithnq))
    

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


    #plot_derivative(80, 'pwia', 1)

    compare_Xsec(80, 1)
    #plot_derivative(580, 'fsi', 2)
    #plot_derivative(750, 'fsi', 1)

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
