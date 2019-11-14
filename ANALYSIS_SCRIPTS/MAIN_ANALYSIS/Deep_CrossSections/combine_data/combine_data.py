import LT.box as B
from LT.datafile import dfile
import numpy as np
import numpy.ma as ma
import sys           
import os                                                      
from sys import argv  

#This Code:
#This code assumes the systematics errors have been calculated on the Xsec and red Xsec, and reads them 
#to combine the data. When combining data, ONLY used statistical weight.  To combine the systematic errors
#from different data sets, take the normal average of the systematic errors for now (Mark Jones)
#When plotting combined reduced Xsec, plot statistical and total error bars (two error bars per data point)

# **NOTE** ONLY Reduced Cross Sections (Momentum Distributions) can be combined. Cross Sections CANNOT be combined, 
#          as they depend on spectrometer the kinematic setting, whereas in momentum distribution, that depenency has
#          been factored out by dividing by K*sig_cc1(GEp, GMp)
# ** combines (takes average) different data sets of a given kinematic setting and writes to file
# ** combines different kinematic settings

def convert2NaN(arr=np.array([]), value=0):
    #method to convert a specified value in a array to nan (not a number)

    for i in enumerate(arr):
        if arr[i[0]]==value:
            arr[i[0]] = np.nan
    return arr

MeV2fm = 197**3    #convert MeV^-3 to fm^3

#User Input (Dir. Name to store output)
sys_ext = sys.argv[1]   

#check if directory exists, else creates it.
if not os.path.exists(sys_ext):
    os.makedirs(sys_ext)

output_file='./%s/redXsec_combined.txt'%(sys_ext)

fout = open(output_file, 'w') 

#------------------------------------------------------------                   
# header information for the output file    
header = """        
#This file contains combined Reduced Cross Sections from all data sets of the same kinematic bin. pm80 + pm580 (sets 1 and 2) +  pm750 (sets 1, 2 and 3)                                                                                                                                                                                           
#\\ xb = th_nq                                                                                                    
#\\ yb = pm                                                                        
#relative errors df/f=dsig/sig: kin_syst_tot (kinematic systematics),  norm_syst_tot (constant, norm. syst.)
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  pm_avg[f,5]/  kin_syst_tot[f,6]/  norm_syst_tot[f,7]/  tot_syst_err[f,8]/  tot_stats_err[f,9]/  tot_err[f,10]/   red_dataXsec_avg[f,11]/   red_dataXsec_avg_err[f,12]/  red_dataXsec_avg_syst_err[f,13]/   red_dataXsec_avg_tot_err[f,14]/  red_pwiaXsec_avg[f,15]/ red_fsiXsec_avg[f,16]/  
"""
fout.write(header)

def get_sys_fname(pm_set, data_set):
    if(pm_set==80):
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin_systematics.txt' %(sys_ext, pm_set)
    else:
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin_set%i_systematics.txt' %(sys_ext, pm_set, data_set)

    return fname

def get_fname(pm_set, data_set):
    if(pm_set==80):
        fname = '../bin_centering_corrections/%s/pm%i_laget_bc_corr.txt' %(sys_ext, pm_set)
    else:
        fname = '../bin_centering_corrections/%s/pm%i_laget_bc_corr_set%i.txt' %(sys_ext, pm_set, data_set)

    return fname

def get_pm_avg(pm_set, data_set):
    #Code to get the average momentum from the avg. kin. file
    if(pm_set==80):
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin.txt' %(sys_ext, pm_set)
    else:
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin_set%i.txt' %(sys_ext, pm_set, data_set)

    kin = dfile(fname)
    pm = kin['pm']
    pm_bin = kin['yb']
    return pm_bin, pm

def get_sig_red(header_name, pm_set, data_set):
    #Code to get any header and data array from bin-center corrected data files

    #Get file containing red. Xsec and its stats. error
    f = dfile(get_fname(pm_set, data_set))
    
    #Get data array with desired header name
    data = f[header_name]
    return data

def get_kin_syst(header_name, pm_set, data_set):
    #Code to get any header and data array from the kin. systematic data files

    #Get file containing kin. systematics
    f = dfile(get_sys_fname(pm_set, data_set))
    
    #Get data array with desired header name (kin. syst are in %)
    data = f[header_name] / 100.   #coonvert to fractional relative error
    return data

def get_norm_syst(header_name):
    #Code to get any header and data array from the normalization. systematic data file

    #Get file containing kin. systematics
    f = dfile('../average_kinematics/Em_final40MeV/normalization_systematics.txt')
    
    #Get data array with desired header name (norm. syst are in fractional rel. error)
    data = f[header_name]   
    return data

#Get bin information from each file
f1  = dfile(get_fname(80, 1))
i_b = f1['i_b']
i_x = f1['i_x']
i_y = f1['i_y']
xb  = f1['xb']
yb  = f1['yb']

#Get Average Pmiss
pm1_b, pm80 = get_pm_avg(80, 1)
pm2_b, pm580_set1 = get_pm_avg(580, 1)
pm3_b, pm580_set2 = get_pm_avg(580, 2)
pm4_b, pm750_set1 = get_pm_avg(750, 1)
pm5_b, pm750_set2 = get_pm_avg(750, 2)
pm6_b, pm750_set3 = get_pm_avg(750, 3)

#Get reduced Xsec
sig_red_80 = get_sig_red('red_dataXsec', 80, 1)
sig_red_580_set1 = get_sig_red('red_dataXsec', 580, 1)
sig_red_580_set2 = get_sig_red('red_dataXsec', 580, 2)
sig_red_750_set1 = get_sig_red('red_dataXsec', 750, 1)
sig_red_750_set2 = get_sig_red('red_dataXsec', 750, 2)
sig_red_750_set3 = get_sig_red('red_dataXsec', 750, 3)

#Get reduced Xsec stats. err
sig_red_80_err = get_sig_red('red_dataXsec_err', 80, 1)
sig_red_580_set1_err = get_sig_red('red_dataXsec_err', 580, 1)
sig_red_580_set2_err = get_sig_red('red_dataXsec_err', 580, 2)
sig_red_750_set1_err = get_sig_red('red_dataXsec_err', 750, 1)
sig_red_750_set2_err = get_sig_red('red_dataXsec_err', 750, 2)
sig_red_750_set3_err = get_sig_red('red_dataXsec_err', 750, 3)

#Get theoretical red. Xsec
red_pwiaXsec_80 = get_sig_red('red_pwiaXsec', 80, 1)
red_pwiaXsec_580_set1 = get_sig_red('red_pwiaXsec', 580, 1)
red_pwiaXsec_580_set2 = get_sig_red('red_pwiaXsec', 580, 2)
red_pwiaXsec_750_set1 = get_sig_red('red_pwiaXsec', 750, 1)
red_pwiaXsec_750_set2 = get_sig_red('red_pwiaXsec', 750, 2)
red_pwiaXsec_750_set3 = get_sig_red('red_pwiaXsec', 750, 3)

red_fsiXsec_80 = get_sig_red('red_fsiXsec', 80, 1)
red_fsiXsec_580_set1 = get_sig_red('red_fsiXsec', 580, 1)
red_fsiXsec_580_set2 = get_sig_red('red_fsiXsec', 580, 2)
red_fsiXsec_750_set1 = get_sig_red('red_fsiXsec', 750, 1)
red_fsiXsec_750_set2 = get_sig_red('red_fsiXsec', 750, 2)
red_fsiXsec_750_set3 = get_sig_red('red_fsiXsec', 750, 3)

#Get Kinematic Systematics Relative error
kin_syst_80 = get_kin_syst('sig_kin_tot', 80, 1)
kin_syst_580_set1 = get_kin_syst('sig_kin_tot', 580, 1)
kin_syst_580_set2 = get_kin_syst('sig_kin_tot', 580, 2)
kin_syst_750_set1 = get_kin_syst('sig_kin_tot', 750, 1)
kin_syst_750_set2 = get_kin_syst('sig_kin_tot', 750, 2)
kin_syst_750_set3 = get_kin_syst('sig_kin_tot', 750, 3)

norm_syst_tot = get_norm_syst('total_norm_syst')

#Loop over all 2d bins
for ib in range(len(i_b)):

    
    #----------Calculate the Data Reduced Xsec Weighted Average for a given (Pm, th_nq) bin of a given kin. set------------
    red_dataXsec_arr = np.array([sig_red_80[ib], sig_red_580_set1[ib], sig_red_580_set2[ib], sig_red_750_set1[ib], sig_red_750_set2[ib], sig_red_750_set3[ib]])
    red_dataXsec_m = ma.masked_values(red_dataXsec_arr, -1.)  #maske invalid values (-1)
    
    #Define the weights (Use ONLY statistical)
    red_dataXsec_weights = np.array([1./sig_red_80_err[ib]**2, 1./sig_red_580_set1_err[ib]**2, 1./sig_red_580_set2_err[ib]**2, 1./sig_red_750_set1_err[ib]**2, 1./sig_red_750_set2_err[ib]**2, 1./sig_red_750_set3_err[ib]**2])
    red_dataXsec_weights_m = ma.masked_values(red_dataXsec_weights, 1.)


    #=======DATA REDUCED CROSS SECTION WEIGHTED AVERAGE==========
    red_dataXsec_avg = ma.average(red_dataXsec_m, weights=red_dataXsec_weights)
    red_dataXsec_avg_err = 1. / np.sqrt(np.sum(red_dataXsec_weights_m))    #combined data sets statistical uncertainty per (Pm, thnq) bin

    kin_syst_arr = np.array([kin_syst_80[ib], kin_syst_580_set1[ib], kin_syst_580_set2[ib], kin_syst_750_set1[ib], kin_syst_750_set2[ib], kin_syst_750_set3[ib]])
    #mask elements corresponding to masked dataXsec (We do not want to add in quadrature elements for which there is no Xsec)
    kin_syst_arr_m = ma.masked_array(kin_syst_arr, ma.getmask(red_dataXsec_m))

    #Add kinematic systematics in quadrature
    kin_syst_tot2 = np.sum(kin_syst_arr_m**2)
    kin_syst_tot = np.sqrt( np.sum(kin_syst_arr_m**2) )

    #Add total systematic error in quadrature
    tot_syst_err = np.sqrt(kin_syst_tot**2 + norm_syst_tot**2)

    #Define relative statistical relative error
    tot_stats_err = red_dataXsec_avg_err/red_dataXsec_avg 
    
    #Add statistical and systematics relative error in quadrature
    tot_err = np.sqrt(tot_stats_err**2 + tot_syst_err**2)
    
    #===Calculate Absolute Error on the Reduced Cross Section===
    red_dataXsec_avg_syst_err = red_dataXsec_avg*tot_syst_err
    red_dataXsec_avg_tot_err = red_dataXsec_avg*tot_err


    #================
    # THEORY AVERAGE
    #================
    
    red_pwiaXsec_arr = np.array([red_pwiaXsec_80[ib], red_pwiaXsec_580_set1[ib], red_pwiaXsec_580_set2[ib], red_pwiaXsec_750_set1[ib], red_pwiaXsec_750_set2[ib], red_pwiaXsec_750_set3[ib]])
    red_pwiaXsec_arr_m = np.ma.masked_values(red_pwiaXsec_arr, -1.)
    red_pwiaXsec_avg = np.ma.average(red_pwiaXsec_arr_m)
   
    red_fsiXsec_arr = np.array([red_fsiXsec_80[ib], red_fsiXsec_580_set1[ib], red_fsiXsec_580_set2[ib], red_fsiXsec_750_set1[ib], red_fsiXsec_750_set2[ib], red_fsiXsec_750_set3[ib]])
    red_fsiXsec_arr_m = np.ma.masked_values(red_fsiXsec_arr, -1.)
    red_fsiXsec_avg = np.ma.average(red_fsiXsec_arr_m)

    #==================================
    # Get the Average Missing Momentum
    #==================================

    pm_arr = np.array([pm80[ib], pm580_set1[ib], pm580_set2[ib], pm750_set1[ib], pm750_set2[ib], pm750_set3[ib]])
    pm_arr_m = np.ma.masked_values(pm_arr, 0.)

    pm_avg = np.ma.average(pm_arr_m) / 1000.  #Convert to GeV

    print(xb[ib])

    l="%i  %i  %i  %f   %f   %f   %f   %f   %f   %f   %f   %.12e  %.12e  %.12e  %.12e  %.12e  %.12e \n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], pm_avg, kin_syst_tot, norm_syst_tot, tot_syst_err, tot_stats_err, tot_err, red_dataXsec_avg, red_dataXsec_avg_err, red_dataXsec_avg_syst_err, red_dataXsec_avg_tot_err, red_pwiaXsec_avg, red_fsiXsec_avg )
    fout.write(l)
    
    

fout.close()


