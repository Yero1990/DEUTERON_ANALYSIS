import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy.ma as ma
import sys                                     
import os                                                                                                       
from sys import argv  
import matplotlib
matplotlib.use('Agg')

#This code uses data from the 80 MeV setting to make cross check plots such as data Xsec ratios to SIMC, or Xsec vs. thetanq (or pm)

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

dir_name = sys_ext+"_crossCheck_plots"
print(dir_name)
#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)
 
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

def plot_Xsec_vs_thnq():

    #Code to plot the data Xsec (before combining) versus theta_nq for different Pm bins (used as a cross check with previous data)    
    dataXsec80_masked = np.ma.array(dataXsec_80, mask=(dataXsec_err_80>0.5*dataXsec_80))
    dataXsec80_masked = np.ma.filled(dataXsec80_masked.astype(float), np.nan)

    #Cross Sectio Ratio to PWIA
    XsecR80_mask =  dataXsec80_masked / pwiaXsec_80
    XsecR80_err =  dataXsec_err_80 / pwiaXsec_80
    XsecR80_theory =  fsiXsec_80 / pwiaXsec_80
 
    #Plot momentum distribution vs. theta_nq for different Pmiss bins
    pm_arr = [0.02, 0.06, 0.1, 0.14, 0.18, 0.220]
    
    for i, ipm in enumerate(pm_arr):
        print(ipm)
        ith_p = int(ipm*1000)
        B.pl.clf()
        B.pl.figure(i+1)

        B.plot_exp(thnq[pm==ipm], XsecR80_mask[pm==ipm], XsecR80_err[pm==ipm], color='black', marker='o', label='80 MeV Data (< 50 % stats)' )
        B.plot_exp(thnq[pm==ipm], XsecR80_theory[pm==ipm], linestyle='--', color='red', label='Laget')


        B.pl.xlabel('Neutron Recoil Angle [deg]')
        B.pl.ylabel(r'$\sigma_{exp}/\sigma_{PWIA}$')
        B.pl.ylim(0, 3)
        B.pl.xlim(0, 140)
        pm_min = int(ipm*1000 - 20.) 
        pm_max = int(ipm*1000 + 20.)
        B.pl.title(r'Cross Section Ratio, $P_{m}$ = %i $\pm$ 20 MeV/c'%(ith_p))
        B.pl.legend()
        #B.pl.show()
        B.pl.savefig(dir_name+'/XsecR80_pm%i.pdf'%(ith_p))


def plot_relative_diff():
    
    #Code to plot the relative difference between PWIA and dataXsec for nominal
    #and after chaning data kinematic by small offset 

    #Get Xsec Data Files
    f80_nom = B.get_file('../bin_centering_corrections/Em_nom_test40MeV/pm80_laget_bc_corr.txt')
    f80 = B.get_file('../bin_centering_corrections/%s/pm80_laget_bc_corr.txt'%(sys_ext))

    #Get Bin Information (Same info for all files)
    i_b = B.get_data(f80_nom, 'i_b')    #2D bin number
    i_x = B.get_data(f80_nom, 'i_x')    #x (th_nq) bin number
    i_y = B.get_data(f80_nom, 'i_y')    #y (pmiss) bin number
    thnq = B.get_data(f80_nom, 'xb')      #th_nq value at bin center
    pm =  B.get_data(f80_nom, 'yb')      #pmiss value at bin center
    
    #Get 80 MeV Xsec
    dataXsec_80_nom     = B.get_data(f80_nom, 'fsiRC_dataXsec_fsibc_corr')
    dataXsec_err_80_nom = B.get_data(f80_nom, 'fsiRC_dataXsec_fsibc_corr_err')
    pwiaXsec_80_nom     = B.get_data(f80_nom, 'pwiaXsec_theory')
    fsiXsec_80_nom      = B.get_data(f80_nom, 'fsiXsec_theory')
    
    dataXsec_80     = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr')
    dataXsec_err_80 = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr_err')
    pwiaXsec_80     = B.get_data(f80, 'pwiaXsec_theory')
    fsiXsec_80      = B.get_data(f80, 'fsiXsec_theory')
    
    #convert '-1' to nan (better for plotting,as plots ignore nan)
    convert2NaN(dataXsec_80_nom, value=-1)
    convert2NaN(dataXsec_err_80_nom, value=-1)
    convert2NaN(pwiaXsec_80_nom, value=-1)
    convert2NaN(fsiXsec_80_nom, value=-1)
    
    convert2NaN(dataXsec_80, value=-1)
    convert2NaN(dataXsec_err_80, value=-1)
    convert2NaN(pwiaXsec_80, value=-1)
    convert2NaN(fsiXsec_80, value=-1)

    #Code to plot the data Xsec (before combining) versus theta_nq for different Pm bins (used as a cross check with previous data)    
    dataXsec80_nom_masked = np.ma.array(dataXsec_80_nom, mask=(dataXsec_err_80_nom>0.5*dataXsec_80_nom))
    dataXsec80_nom_masked = np.ma.filled(dataXsec80_nom_masked.astype(float), np.nan)

    dataXsec80_masked = np.ma.array(dataXsec_80, mask=(dataXsec_err_80>0.5*dataXsec_80))
    dataXsec80_masked = np.ma.filled(dataXsec80_masked.astype(float), np.nan)

    #Relative difference between data and PWIA 
    R_nom = (pwiaXsec_80_nom - dataXsec80_nom_masked) / pwiaXsec_80_nom * 100.
    R_nom_err = dataXsec_err_80_nom / pwiaXsec_80_nom * 100.
    
    R = (pwiaXsec_80 - dataXsec80_masked) / pwiaXsec_80 * 100.
    R_err = dataXsec_err_80 / pwiaXsec_80 * 100.
    
    R_theory = (pwiaXsec_80_nom - fsiXsec_80_nom) / pwiaXsec_80_nom * 100.

    #DATA/PWIA Ratios
    ratio_nom = dataXsec80_nom_masked / pwiaXsec_80_nom
    ratio_nom_err = dataXsec_err_80_nom / pwiaXsec_80_nom
    
    ratio = dataXsec80_masked / pwiaXsec_80
    ratio_err = dataXsec_err_80 / pwiaXsec_80
    ratio_theory = fsiXsec_80 / pwiaXsec_80
    

    #Plot Relative Error vs. theta_nq for different Pmiss bins
    pm_arr = [0.02, 0.06, 0.1, 0.14, 0.18, 0.220]
    
    for i, ipm in enumerate(pm_arr):
        print(ipm)
        ith_p = int(ipm*1000)
        B.pl.clf()
        B.pl.figure(i+1)
        

        B.plot_exp(thnq[pm==ipm], R_nom[pm==ipm], R_nom_err[pm==ipm], color='black', marker='o', label=r'80 MeV Data (< 50 % stats)' )
        B.plot_exp(thnq[pm==ipm], R[pm==ipm], R_err[pm==ipm], color='red', marker='s', label=r'80 MeV Data (< 50 % stats), $\theta_{e}$ - 0.2 mr')
        B.plot_exp(thnq[pm==ipm], R_theory[pm==ipm], color='red', linestyle='--', label=r'80 MeV Laget Theory, $(\sigma^{fsi} - \sigma^{pwia})/\sigma^{pwia}$')


        B.pl.xlabel('Neutron Recoil Angle [deg]')
        B.pl.ylabel(r'Relative Difference [%]')
        B.pl.ylim(-100, 100)
        B.pl.xlim(0, 140)
        pm_min = int(ipm*1000 - 20.) 
        pm_max = int(ipm*1000 + 20.)
        B.pl.title(r'Relative Error $\frac{\sigma^{data} - \sigma^{pwia}}{\sigma^{pwia}}$, $P_{m}$ = %i $\pm$ 20 MeV/c'%(ith_p))
        B.pl.legend()
        #B.pl.show()
        B.pl.savefig(dir_name+'/relDiff_R80_pm%i.pdf'%(ith_p))
 
        #-------------------------------------------

        B.pl.clf()
        B.pl.figure(i+2)


            
        B.plot_exp(thnq[pm==ipm], ratio_nom[pm==ipm], ratio_nom_err[pm==ipm], color='black', marker='o', label=r'80 MeV Data (< 50 % stats)' )
        B.plot_exp(thnq[pm==ipm], ratio[pm==ipm], ratio_err[pm==ipm], color='red', marker='s', label=r'80 MeV Data (< 50 % stats), $\theta_{e}$ - 0.2 mr')
        B.plot_exp(thnq[pm==ipm], ratio_theory[pm==ipm], color='red', linestyle='--', label=r'Laget Theory, $\sigma^{fsi}/\sigma^{pwia}$')

        B.pl.xlabel('Neutron Recoil Angle [deg]')
        B.pl.ylabel(r'$\sigma_{exp}/\sigma_{PWIA}$')
        B.pl.ylim(0, 3)
        B.pl.xlim(0, 140)
        pm_min = int(ipm*1000 - 20.) 
        pm_max = int(ipm*1000 + 20.)
        B.pl.title(r'Cross Section Ratio, $P_{m}$ = %i $\pm$ 20 MeV/c'%(ith_p))
        B.pl.legend()
        #B.pl.show()
        B.pl.savefig(dir_name+'/XsecR80_compare_pm%i.pdf'%(ith_p))


def main():
    print('Entering Main . . .')

    #plot_Xsec_vs_thnq()
    plot_relative_diff()

if __name__=="__main__":
    main()
