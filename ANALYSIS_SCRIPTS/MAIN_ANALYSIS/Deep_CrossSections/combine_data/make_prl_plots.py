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
from matplotlib import rc
from matplotlib import *
from mpl_toolkits.axes_grid.inset_locator import (inset_axes, InsetPosition, mark_inset)


matplotlib.use('Agg')

#Use latex commands (e.g. \textit ot \textbf)
rc('text', usetex=True)
#Set default font to times new roman
font = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 12
}
plt.rc('font', **font)

#Set font
csfont = {'fontname':'Times New Roman'}

def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)
    
    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr


#Conversion factor:  1 fm = 1/ (197 MeV),   
#The reduced cross section is in MeV^-3 units
MeV2fm = 197.3**3    #convert MeV^-3 to fm^3

#User Input (Dir. Name to store output)
sys_ext = sys.argv[1]   
    
dir_name = sys_ext+"_plots"
dir_name_misc = dir_name + "/misc_plots"        #directory to store miscellaneous plots (trigger rates, live time, etc. . .) #obtained from the report files
print(dir_name)
#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)
if not os.path.exists(dir_name_misc):
    os.makedirs(dir_name_misc)
     

#Get Reduced Xsec Data File
fname = './%s/redXsec_combined.txt'%(sys_ext)
f = B.get_file(fname)

#Get Bin Information (Same info for all files)                                                                                                  
i_b = B.get_data(f, 'i_b')    #2D bin number                                                                    
i_x = B.get_data(f, 'i_x')    #x (th_nq) bin number                                                                                    
i_y = B.get_data(f, 'i_y')    #y (pmiss) bin number                                        
thnq = B.get_data(f, 'xb')      #th_nq value at bin center                                                          
pm =  B.get_data(f, 'yb')      #pmiss value at bin center   
pm_avg = B.get_data(f, 'pm_avg')

#Get Combined Final Red Xsec for all kinematics
red_dataXsec_avg     = B.get_data(f,'red_dataXsec_avg')
red_dataXsec_avg_err = B.get_data(f,'red_dataXsec_avg_err')
red_dataXsec_avg_syst_err = B.get_data(f,'red_dataXsec_avg_syst_err')
red_dataXsec_avg_tot_err = B.get_data(f,'red_dataXsec_avg_tot_err')
red_pwiaXsec_avg     = B.get_data(f,'red_pwiaXsec_avg')
red_fsiXsec_avg      = B.get_data(f,'red_fsiXsec_avg')

#Get total relative errors / (Pm, thnq) bin for plotting (probably also write to table)
kin_syst_tot = dfile(fname)['kin_syst_tot']    #kinematic systematics
norm_syst_tot = dfile(fname)['norm_syst_tot']  #normalization systematics
tot_syst_err = dfile(fname)['tot_syst_err']    #total systematics
tot_stats_err = dfile(fname)['tot_stats_err']  #total statistical
tot_err = dfile(fname)['tot_err']              #overall error

def read_halla_data(thnq=0):

    #The code read data files containing momentum distributions from Hall A

    #Conversion factor: 1 fm = 1 / (0.1973 GeV)  or  1 fm^-1 = 0.1973 GeV
    fminv2GeV = 1./(1./0.1973)
    ifm2GeV = 0.1973  #inverse fermi to GeV

    thnq_f = '%.1f' % (thnq)
    fname = '../HallA_data/theta_%s_th_corr.data' % (thnq_f)

    kin = dfile(fname)
    p_miss = kin['p_miss'] * ifm2GeV    #Pm here is not the central bin value, but an average over that bin
    red_dataXsec = kin['rho']             #units fm^3
    red_dataXsec_err = kin['delta_rho']

    return p_miss, red_dataXsec, red_dataXsec_err
    
def read_theoretical_models(theory="", model="", thnq=0):

    #This code read the averaged red.Xsec and returns arrays in pm and reduced Xsec
    #theory: V18, CD-Bonn    model: PWIA, FSI
    thnq_f = "%.2f" %(thnq)

    fname = '../theoretical_models/updated_%s_models/theoryXsec_%s%s_thnq%s_combined.data' % (model, theory, model, thnq_f)
    kin = dfile(fname)
    
    pm_bin = np.array(kin['pm_avg'])
    

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


def make_prl_plots():
    #Make PRL paper plots

    #Read This Experiment (Hall C) Data, and require better than 50% statistics
    red_dataXsec_avg_masked = np.ma.array(red_dataXsec_avg, mask=(red_dataXsec_avg_err>0.5*red_dataXsec_avg))
    red_dataXsec_avg_masked = np.ma.filled(red_dataXsec_avg_masked.astype(float), np.nan)

    #Read Hall A data (reduced Xsec already in fm^3 units, and Precoil in GeV)
    pm_ha35, red_dataXsec_ha35, red_dataXsec_err_ha35 = read_halla_data(35)
    pm_ha45, red_dataXsec_ha45, red_dataXsec_err_ha45 = read_halla_data(45)  
    pm_ha75, red_dataXsec_ha75, red_dataXsec_err_ha75 = read_halla_data(75)  

    #Read Models 35, 45 75 (for PRL plot)
    #Read Other Theoretical Models (V18, CD-BONN)

    pm_avg1, red_pwiaXsec_V18_35 = read_theoretical_models("V18", "PWIA", 35)   
    pm_avg2, red_fsiXsec_V18_35 = read_theoretical_models("V18", "FSI", 35)      
    pm_avg3, red_pwiaXsec_CD_35 = read_theoretical_models("CD-Bonn", "PWIA", 35)                                 
    pm_avg4, red_fsiXsec_CD_35 = read_theoretical_models("CD-Bonn", "FSI", 35)   
    
    pm_avg5, red_pwiaXsec_V18_45 = read_theoretical_models("V18", "PWIA", 45)   
    pm_avg6, red_fsiXsec_V18_45 = read_theoretical_models("V18", "FSI", 45)      
    pm_avg7, red_pwiaXsec_CD_45 = read_theoretical_models("CD-Bonn", "PWIA", 45)                                 
    pm_avg8, red_fsiXsec_CD_45 = read_theoretical_models("CD-Bonn", "FSI", 45)

    pm_avg9, red_pwiaXsec_V18_75 = read_theoretical_models("V18", "PWIA", 75)   
    pm_avg10, red_fsiXsec_V18_75 = read_theoretical_models("V18", "FSI", 75)      
    pm_avg11, red_pwiaXsec_CD_75 = read_theoretical_models("CD-Bonn", "PWIA", 75)                                 
    pm_avg12, red_fsiXsec_CD_75 = read_theoretical_models("CD-Bonn", "FSI", 75)

    #Convert to sig_reduced from MeV^-3 to fm^3
    red_pwiaXsec_avg_35 = red_pwiaXsec_avg[thnq==35]*MeV2fm    #Laget PWIA
    red_fsiXsec_avg_35 = red_fsiXsec_avg[thnq==35]*MeV2fm      #Laget FSI
    red_pwiaXsec_V18_35 = red_pwiaXsec_V18_35*MeV2fm
    red_fsiXsec_V18_35 = red_fsiXsec_V18_35*MeV2fm
    red_pwiaXsec_CD_35 = red_pwiaXsec_CD_35*MeV2fm
    red_fsiXsec_CD_35 = red_fsiXsec_CD_35*MeV2fm

    red_pwiaXsec_avg_45 = red_pwiaXsec_avg[thnq==45]*MeV2fm    #Laget PWIA
    red_fsiXsec_avg_45 = red_fsiXsec_avg[thnq==45]*MeV2fm      #Laget FSI
    red_pwiaXsec_V18_45 = red_pwiaXsec_V18_45*MeV2fm
    red_fsiXsec_V18_45 = red_fsiXsec_V18_45*MeV2fm
    red_pwiaXsec_CD_45 = red_pwiaXsec_CD_45*MeV2fm
    red_fsiXsec_CD_45 = red_fsiXsec_CD_45*MeV2fm

    red_pwiaXsec_avg_75 = red_pwiaXsec_avg[thnq==75]*MeV2fm    #Laget PWIA
    red_fsiXsec_avg_75 = red_fsiXsec_avg[thnq==75]*MeV2fm      #Laget FSI
    red_pwiaXsec_V18_75 = red_pwiaXsec_V18_75*MeV2fm
    red_fsiXsec_V18_75 = red_fsiXsec_V18_75*MeV2fm
    red_pwiaXsec_CD_75 = red_pwiaXsec_CD_75*MeV2fm
    red_fsiXsec_CD_75 = red_fsiXsec_CD_75*MeV2fm

    #Do Interpolation to make theory curves smooth
    #35 deg
    f_red_pwiaXsec_avg_35 = interp1d(pm_avg[thnq==35], red_pwiaXsec_avg_35,fill_value='extrapolate')   #Paris (J.M. Laget Calculation)
    f_red_fsiXsec_avg_35 = interp1d(pm_avg[thnq==35], red_fsiXsec_avg_35,fill_value='extrapolate')    
    
    f_red_pwiaXsec_V18_35 = interp1d(pm_avg1, red_pwiaXsec_V18_35,fill_value='extrapolate')                        #AV18 (M. Sargsian calculation)
    f_red_fsiXsec_V18_35 = interp1d(pm_avg2, red_fsiXsec_V18_35,fill_value='extrapolate')
    
    f_red_pwiaXsec_CD_35 = interp1d(pm_avg3, red_pwiaXsec_CD_35,fill_value='extrapolate')                          #CD-Bonn (M. Sargsian calculation)
    f_red_fsiXsec_CD_35 = interp1d(pm_avg4, red_fsiXsec_CD_35,fill_value='extrapolate')
    #45 eg
    f_red_pwiaXsec_avg_45 = interp1d(pm_avg[thnq==45], red_pwiaXsec_avg_45,fill_value='extrapolate')   #Paris (J.M. Laget Calculation)
    f_red_fsiXsec_avg_45 = interp1d(pm_avg[thnq==45], red_fsiXsec_avg_45,fill_value='extrapolate')    
    
    f_red_pwiaXsec_V18_45 = interp1d(pm_avg5, red_pwiaXsec_V18_45,fill_value='extrapolate')                        #AV18 (M. Sargsian calculation)
    f_red_fsiXsec_V18_45 = interp1d(pm_avg6, red_fsiXsec_V18_45,fill_value='extrapolate')
    
    f_red_pwiaXsec_CD_45 = interp1d(pm_avg7, red_pwiaXsec_CD_45,fill_value='extrapolate')                          #CD-Bonn (M. Sargsian calculation)
    f_red_fsiXsec_CD_45 = interp1d(pm_avg8, red_fsiXsec_CD_45,fill_value='extrapolate')
    #75 eg
    f_red_pwiaXsec_avg_75 = interp1d(pm_avg[thnq==75], red_pwiaXsec_avg_75,fill_value='extrapolate')   #Paris (J.M. Laget Calculation)
    f_red_fsiXsec_avg_75 = interp1d(pm_avg[thnq==75], red_fsiXsec_avg_75,fill_value='extrapolate')    
    
    f_red_pwiaXsec_V18_75 = interp1d(pm_avg9, red_pwiaXsec_V18_75,fill_value='extrapolate')                        #AV18 (M. Sargsian calculation)
    f_red_fsiXsec_V18_75 = interp1d(pm_avg10, red_fsiXsec_V18_75,fill_value='extrapolate')
    
    f_red_pwiaXsec_CD_75 = interp1d(pm_avg11, red_pwiaXsec_CD_75,fill_value='extrapolate')                          #CD-Bonn (M. Sargsian calculation)
    f_red_fsiXsec_CD_75 = interp1d(pm_avg12, red_fsiXsec_CD_75,fill_value='extrapolate')
    
    #------Get Averaged Missing Momentum-----
    pmiss_avg_35 = pm_avg[thnq==35]
    pmiss_avg_45 = pm_avg[thnq==45]
    pmiss_avg_75 = pm_avg[thnq==75]
            


    #====================================================PRL PLOT 1=============================================================
    
    #-----Create Subplots-----
    fig = B.pl.subplots(3, sharex=True, sharey=True, figsize=(13.4, 6)) 
    gs = gridspec.GridSpec(1, 3) 

    
    #THETA_NQ = 35 DEG
    ax0 = B.pl.subplot(gs[0])

    B.pl.text(0.25, 1e-7, r'$\theta_{nq}=35\pm5^{o}$', fontsize=19)
    B.pl.text(1.0, 1e0, r'(a)', fontsize=19)

    l1 = B.plot_exp(pm_avg[thnq==35], red_dataXsec_avg_masked[thnq==35]*MeV2fm, red_dataXsec_avg_tot_err[thnq==35]*MeV2fm, marker='o', markersize=5, color='k', markerfacecolor='k', logy=True, label='This Experiment (Hall C)' )
    l2 = B.plot_exp(pm_ha35, red_dataXsec_ha35, red_dataXsec_err_ha35, marker='o', markersize=5, color='c', logy=True,  label='Hall A Data')

    #Plot theoretical curves
    l3, = B.plot_exp(pm_avg[thnq==35], f_red_pwiaXsec_avg_35(pm_avg[thnq==35]), linestyle='--', marker='None', color='blue', logy=True, label='Paris PWIA')
    l4, = B.plot_exp(pm_avg[thnq==35], f_red_fsiXsec_avg_35(pm_avg[thnq==35]), linestyle='-', marker='None', color='blue', logy=True, label='Paris FSI')
    
    l5, = B.plot_exp(pm_avg1, f_red_pwiaXsec_V18_35(pm_avg1), linestyle='--', marker='None', color='green', logy=True, label='AV18 PWIA')   
    l6, = B.plot_exp(pm_avg2, f_red_fsiXsec_V18_35(pm_avg2), linestyle='-', marker='None', color='green', logy=True, label='AV18 FSI') 
    
    l7, = B.plot_exp(pm_avg3, f_red_pwiaXsec_CD_35(pm_avg3), linestyle='--', marker='None', color='magenta', logy=True, label='CD-Bonn PWIA')     
    l8, = B.plot_exp(pm_avg4, f_red_fsiXsec_CD_35(pm_avg4), linestyle='-', marker='None', color='magenta', logy=True, label='CD-Bonn FSI') 

    #Set axis limits
    B.pl.xlim(0.0, 1.18)

    #Set Tick Marks
    ax0.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)

    #Set Axes Labels for subplot 0
    B.pl.xlabel('')                                                                                                                                                                                                   
    B.pl.ylabel(r'$\sigma_{red}$ ($fm^{3}$) ', fontsize=22,  labelpad=10)                                                                                                                                                                        
    B.pl.title('') 

    #THETA_NQ = 45 DEG
    ax1 = plt.subplot(gs[1], sharey=ax0)
    
    B.pl.text(0.25, 1e-7, r'$\theta_{nq}=45\pm5^{o}$', fontsize=19)
    B.pl.text(1.0, 1e0, r'(b)', fontsize=19)

    #Remove un-necessary Y tick labels from subplot
    B.pl.setp(ax1.get_yticklabels(), visible=False)

    B.plot_exp(pm_avg[thnq==45], red_dataXsec_avg_masked[thnq==45]*MeV2fm, red_dataXsec_avg_tot_err[thnq==45]*MeV2fm, marker='o', markersize=5, color='k', markerfacecolor='k', logy=True, label='This Experiment (Hall C)' )
    B.plot_exp(pm_ha45, red_dataXsec_ha45, red_dataXsec_err_ha45, marker='o', markersize=5, color='c', logy=True, label='Hall A Data')
    
    #Plot theoretical curves
    B.plot_exp(pm_avg[thnq==45], f_red_pwiaXsec_avg_45(pm_avg[thnq==45]), linestyle='--', marker='None', color='blue', logy=True, label='Paris PWIA')
    B.plot_exp(pm_avg[thnq==45], f_red_fsiXsec_avg_45(pm_avg[thnq==45]), linestyle='-', marker='None', color='blue', logy=True, label='Paris FSI')
    
    B.plot_exp(pm_avg5, f_red_pwiaXsec_V18_45(pm_avg5), linestyle='--', marker='None', color='green', logy=True, label='AV18 PWIA')   
    B.plot_exp(pm_avg6, f_red_fsiXsec_V18_45(pm_avg6), linestyle='-', marker='None', color='green', logy=True, label='AV18 FSI') 
    
    B.plot_exp(pm_avg7, f_red_pwiaXsec_CD_45(pm_avg7), linestyle='--', marker='None', color='magenta', logy=True, label='CD-Bonn PWIA')     
    B.plot_exp(pm_avg8, f_red_fsiXsec_CD_45(pm_avg8), linestyle='-', marker='None', color='magenta', logy=True, label='CD-Bonn FSI') 

    #Set axis limits
    B.pl.xlim(0.0, 1.18)

    #Set Tick Marks
    ax1.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)

    #Set Axes Labels for subplot 1
    B.pl.xlabel(r'$p_{r}$ (GeV/c)', fontsize=22,  labelpad=10)                                                                                                                                                                                                   
    B.pl.ylabel('')                                                                                                                                                                        
    B.pl.title('')

    #THETA_NQ = 75
    ax2 = plt.subplot(gs[2], sharey=ax0)

    B.pl.text(0.25, 1e-7, r'$\theta_{nq}=75\pm5^{o}$', fontsize=19)
    B.pl.text(1.0, 1e0, r'(c)', fontsize=19)

    #Remove un-necessary Y tick labels from subplot
    B.pl.setp(ax2.get_yticklabels(), visible=False)

    B.plot_exp(pm_avg[thnq==75], red_dataXsec_avg_masked[thnq==75]*MeV2fm, red_dataXsec_avg_tot_err[thnq==75]*MeV2fm, marker='o', markersize=5, color='k', markerfacecolor='k', logy=True, label='This Experiment (Hall C)' )
    B.plot_exp(pm_ha75, red_dataXsec_ha75, red_dataXsec_err_ha75, marker='o', markersize=5, color='c', logy=True, label='Hall A Data')

    #Plot theoretical curves
    B.plot_exp(pm_avg[thnq==75], f_red_pwiaXsec_avg_75(pm_avg[thnq==75]), linestyle='--', marker='None', color='blue', logy=True, label='Paris PWIA')
    B.plot_exp(pm_avg[thnq==75], f_red_fsiXsec_avg_75(pm_avg[thnq==75]), linestyle='-', marker='None', color='blue', logy=True, label='Paris FSI')
    
    B.plot_exp(pm_avg9, f_red_pwiaXsec_V18_75(pm_avg9), linestyle='--', marker='None', color='green', logy=True, label='AV18 PWIA')   
    B.plot_exp(pm_avg10, f_red_fsiXsec_V18_75(pm_avg10), linestyle='-', marker='None', color='green', logy=True, label='AV18 FSI') 
    
    B.plot_exp(pm_avg11, f_red_pwiaXsec_CD_75(pm_avg11), linestyle='--', marker='None', color='magenta', logy=True, label='CD-Bonn PWIA')     
    B.plot_exp(pm_avg12, f_red_fsiXsec_CD_75(pm_avg12), linestyle='-', marker='None', color='magenta', logy=True, label='CD-Bonn FSI') 

    #Set axis limits
    B.pl.xlim(0.0, 1.18)

    #Set Tick Marks
    ax2.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)

    #Set Axes Labels for subplot 2
    B.pl.xlabel('')                                                                                                                                                                                                   
    B.pl.ylabel('')                                                                                                                                                                        
    B.pl.title('')
  
    #Remove spacing between subplots
    plt.subplots_adjust(wspace = 0.0000000001, bottom=0.13, top=0.98, left=0.085, right=0.98) #, hspace = 0.001, wspace = 0.001)
    
    #Create labels for specified plots in given order
    line_labels=['This Experiment (Hall C)', 'Hall A Data', 'Paris PWIA', 'Paris FSI', 'AV18 PWIA', 'AV18 FSI', 'CD-Bonn PWIA', 'CD-Bonn FSI']   #define legend labels
    ax2.legend([l1, l2, l3, l4, l5, l6, l7, l8], line_labels, loc='upper right', frameon=False, fontsize=14)      #subplot to use for common legend
      

    B.pl.show()
    
    #===========================================================================================================================


    #====================================================PRL PLOT 2=============================================================
    '''
    #Define the Data (and all models) to CD-Bonn PWIA Ratio
    #theta_nq = 35 deg
    R_ref35 = f_red_pwiaXsec_CD_35(pmiss_avg_35) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_data35 = red_dataXsec_avg_masked[thnq==35]*MeV2fm / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_data_err35 = red_dataXsec_avg_tot_err[thnq==35]*MeV2fm / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_CDBonn_fsi35 = f_red_fsiXsec_CD_35(pmiss_avg_35) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_Paris_pwia35 = f_red_pwiaXsec_avg_35(pm_avg[thnq==35]) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_Paris_fsi35 = f_red_fsiXsec_avg_35(pm_avg[thnq==35]) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_AV18_pwia35 = f_red_pwiaXsec_V18_35(pmiss_avg_35) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    R_AV18_fsi35 = f_red_fsiXsec_V18_35(pmiss_avg_35) / f_red_pwiaXsec_CD_35(pmiss_avg_35)
    #theta_nq = 45 deg    
    R_ref45 = f_red_pwiaXsec_CD_45(pmiss_avg_45) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_data45 = red_dataXsec_avg_masked[thnq==45]*MeV2fm / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_data_err45 = red_dataXsec_avg_tot_err[thnq==45]*MeV2fm / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_CDBonn_fsi45 = f_red_fsiXsec_CD_45(pmiss_avg_45) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_Paris_pwia45 = f_red_pwiaXsec_avg_45(pm_avg[thnq==45]) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_Paris_fsi45 = f_red_fsiXsec_avg_45(pm_avg[thnq==45]) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_AV18_pwia45 = f_red_pwiaXsec_V18_45(pmiss_avg_45) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    R_AV18_fsi45 = f_red_fsiXsec_V18_45(pmiss_avg_45) / f_red_pwiaXsec_CD_45(pmiss_avg_45)
    #theta_nq = 75 deg    
    R_ref75 = f_red_pwiaXsec_CD_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_data75 = red_dataXsec_avg_masked[thnq==75]*MeV2fm / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_data_err75 = red_dataXsec_avg_tot_err[thnq==75]*MeV2fm / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_CDBonn_fsi75 = f_red_fsiXsec_CD_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_Paris_pwia75 = f_red_pwiaXsec_avg_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_Paris_fsi75 = f_red_fsiXsec_avg_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_AV18_pwia75 = f_red_pwiaXsec_V18_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)
    R_AV18_fsi75 = f_red_fsiXsec_V18_75(pmiss_avg_75) / f_red_pwiaXsec_CD_75(pmiss_avg_75)

    #-----Create Subplots-----
    fig = B.pl.subplots(3, sharex=True, sharey=True, figsize=(6.7, 10)) 
    gs = gridspec.GridSpec(3, 1) 

    #THETA_NQ = 35 DEG
    ax0 = B.pl.subplot(gs[0])

    B.pl.text(0.1, 8, r'(a)', fontsize=19)

    #Remove un-necessary X tick labels from subplot
    B.pl.setp(ax0.get_xticklabels(), visible=False)

    #Plot the Data (and all models) to CD-Bonn PWIA model
    B.plot_exp(pm_avg[thnq==35], R_ref35,  marker='None', linestyle='--', color='magenta', label='CD-Bonn PWIA (reference)')
    B.plot_exp(pm_avg[thnq==35], R_data35, R_data_err35, marker='o', color='k', label='Data')
    
    B.plot_exp(pm_avg[thnq==35], R_CDBonn_fsi35, marker='None', linestyle='-', color='magenta', label='CD-Bon FSI')

    B.plot_exp(pm_avg[thnq==35], R_Paris_pwia35, marker='None', linestyle='--', color='blue', label='Paris PWIA')
    B.plot_exp(pm_avg[thnq==35], R_Paris_fsi35, marker='None', linestyle='-', color='blue', label='Paris FSI')
    
    B.plot_exp(pm_avg[thnq==35], R_AV18_pwia35, marker='None', linestyle='--', color='green', label='AV18 PWIA')
    B.plot_exp(pm_avg[thnq==35], R_AV18_fsi35, marker='None', linestyle='-', color='green', label='AV18 FSI')
 
    #Set axis limits
    B.pl.xlim(0.0, 1.18)
    B.pl.ylim(-0.5, 10.9)

    #Set Tick Marks
    ax0.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)    

    #Set Axes Labels for subplot 0
    B.pl.xlabel('')                                                                                                                                                                                                   
    B.pl.ylabel('')                                                                                                                                                                        
    B.pl.title('') 

    #THETA_NQ = 45 DEG
    ax1 = B.pl.subplot(gs[1])

    B.pl.text(0.1, 8, r'(b)', fontsize=19)

    #Remove un-necessary X tick labels from subplot
    B.pl.setp(ax1.get_xticklabels(), visible=False)
    
    #Plot the Data (and all models) to CD-Bonn PWIA model
    B.plot_exp(pm_avg[thnq==45], R_ref45,  marker='None', linestyle='--', color='magenta', label='CD-Bonn PWIA (reference)')
    B.plot_exp(pm_avg[thnq==45], R_data45, R_data_err45, marker='o', color='k', label='Data')
    
    B.plot_exp(pm_avg[thnq==45], R_CDBonn_fsi45, marker='None', linestyle='-', color='magenta', label='CD-Bon FSI')

    B.plot_exp(pm_avg[thnq==45], R_Paris_pwia45, marker='None', linestyle='--', color='blue', label='Paris PWIA')
    B.plot_exp(pm_avg[thnq==45], R_Paris_fsi45, marker='None', linestyle='-', color='blue', label='Paris FSI')
    
    B.plot_exp(pm_avg[thnq==45], R_AV18_pwia45, marker='None', linestyle='--', color='green', label='AV18 PWIA')
    B.plot_exp(pm_avg[thnq==45], R_AV18_fsi45, marker='None', linestyle='-', color='green', label='AV18 FSI')
 
    #Set axis limits
    B.pl.xlim(0.0, 1.18)
    B.pl.ylim(-0.5, 10.9)

    #Set Tick Marks
    ax1.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)

    #Set Axes Labels for subplot 0
    B.pl.xlabel('')                                                                                                                                                                                                   
    B.pl.ylabel(r'R = $\sigma_{red}$ / n($p_{r}$)', fontsize=22,  labelpad=10)                                                                                                                                                                        
    B.pl.title('') 

    #THETA_NQ = 75 DEG
    ax2 = B.pl.subplot(gs[2])

    B.pl.text(0.1, 8, r'(c)', fontsize=19)

    #Plot the Data (and all models) to CD-Bonn PWIA model
    B.plot_exp(pm_avg[thnq==35], R_ref35,  marker='None', linestyle='--', color='magenta', label='(reference)')
    B.plot_exp(pm_avg[thnq==75], R_data75, R_data_err75, marker='o', color='k', label='Data')
    
    B.plot_exp(pm_avg[thnq==75], R_CDBonn_fsi75, marker='None', linestyle='-', color='magenta', label='CD-Bon FSI')

    B.plot_exp(pm_avg[thnq==75], R_Paris_pwia75, marker='None', linestyle='--', color='blue', label='Paris PWIA')
    B.plot_exp(pm_avg[thnq==75], R_Paris_fsi75, marker='None', linestyle='-', color='blue', label='Paris FSI')
    
    B.plot_exp(pm_avg[thnq==75], R_AV18_pwia75, marker='None', linestyle='--', color='green', label='AV18 PWIA')
    B.plot_exp(pm_avg[thnq==75], R_AV18_fsi75, marker='None', linestyle='-', color='green', label='AV18 FSI')
 
    #Set axis limits
    B.pl.xlim(0.0, 1.18)
    B.pl.ylim(-0.5, 10.9)

    #Set Tick Marks
    ax2.tick_params(axis='both', which='both', direction='in', top=True, bottom=True, left=True, right=True, labelsize=19)

    #Set Axes Labels for subplot 0
    B.pl.xlabel(r'$p_{r}$ (GeV/c)', fontsize=22,  labelpad=10)                                                                               
    B.pl.ylabel('')                                                                                 
    B.pl.title('') 
    
    #Remove spacing between subplots
    plt.subplots_adjust(hspace = 0.00000001, bottom=0.09, top=0.98, right=0.95, left=0.18) #, hspace = 0.001, wspace = 0.001)
    
    B.pl.legend(loc='upper right', fontsize=14, frameon=False)
    #B.pl.show()
    B.pl.savefig('./PRL_plot2.pdf')
    '''
    #===========================================================================================================================

    
def main():
    print('Entering Main . . .')

    #plot_data_sets()

    #plot_theory_sets('pwia')
    #plot_theory_sets('fsi')
    #plot_Xsec_vs_thnq()
    #plot_final()
    make_prl_plots()

if __name__=="__main__":
    main()


