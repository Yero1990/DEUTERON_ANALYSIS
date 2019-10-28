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
#This file contains combined Reduced Cross Sections from data sets of the same kinematic. pm580 (sets 1 and 2), pm750 (sets 1, 2 and 3)                                                                                                                                                                                           
#\\ xb = th_nq                                                                                                    
#\\ yb = pm                                                                        
#relative errors df/f=dsig/sig: kin_syst_tot (kinematic systematics), norm_syst_tot(Yield normalization factor systematics), tot_syst_err(kin+norm added in quad.), tot_err(tot_syst+stats added in quad.)
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  pm_avg[f,5]/  kin_syst_tot[f,6]/  norm_syst_tot[f,7]/  tot_syst_err[f,8]/  tot_stats_err[f,9]/  tot_err[f,10]/   red_dataXsec_avg[f,11]/   red_dataXsec_avg_err[f,12]/  red_dataXsec_avg_syst_err[f,13]/   red_dataXsec_avg_tot_err[f,14]/  red_pwiaXsec_avg[f,15]/ red_fsiXsec_avg[f,16]/  
"""
fout.write(header)


#Open File Containing Reduced Cross Sections with systematics included
#fname80 = '../bin_centering_corrections/%s/pm80_laget_bc_corr_systematics.txt'%(sys_ext)
#fname580_set1 = '../bin_centering_corrections/%s/pm580_laget_bc_corr_set1_systematics.txt'%(sys_ext)
#fname580_set2 = '../bin_centering_corrections/%s/pm580_laget_bc_corr_set2_systematics.txt'%(sys_ext)
#fname750_set1 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set1_systematics.txt'%(sys_ext)
#fname750_set2 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set2_systematics.txt'%(sys_ext)
#fname750_set3 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set3_systematics.txt'%(sys_ext)



def get_sys_fname(pm_set, data_set):
    if(pm_set==80):
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin_systematics.txt' %(sys_ext, pm_set)
    else:
        fname = '../average_kinematics/%s/pm%i_fsi_norad_avgkin_set%i_systematics.txt' %(sys_ext, pm_set, data_set)

    return fname

def get_fname(pm_set, data_set):
    if(pm_set==80):
        fname = '../bin_centering_corrections/%s/pm%i_laget_bc_corr_systematics.txt' %(sys_ext, pm_set)
    else:
        fname = '../bin_centering_corrections/%s/pm%i_laget_bc_corr_set%i_systematics.txt' %(sys_ext, pm_set, data_set)

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

#Get bin information from each file
f1  = dfile(get_fname(80, 1))
i_b = f1['i_b']
i_x = f1['i_x']
i_y = f1['i_y']
xb  = f1['xb']
yb  = f1['yb']

#80 MeV
red_dataXsec_1 = f1['red_dataXsec']
red_dataXsec_err_1 = f1['red_dataXsec_err']
red_dataXsec_syst_err_1 = f1['red_dataXsec_syst_err']
red_dataXsec_tot_err_1 = f1['red_dataXsec_tot_err'] 
red_pwiaXsec_1 = f1['red_pwiaXsec']        
red_fsiXsec_1 = f1['red_fsiXsec']
#convert2NaN(red_dataXsec_syst_err_1, value=-1.)

#580 MeV (set 1)
f2 = B.get_file(get_fname(580, 1))
red_dataXsec_2 = f2['red_dataXsec']          
red_dataXsec_err_2 = f2['red_dataXsec_err']  
red_dataXsec_syst_err_2 = f2['red_dataXsec_syst_err'] 
red_dataXsec_tot_err_2 = f2['red_dataXsec_tot_err']  
red_pwiaXsec_2 = f2['red_pwiaXsec']            
red_fsiXsec_2 = f2['red_fsiXsec']              
#convert2NaN(red_dataXsec_syst_err_2, value=-1.)

#580 MeV (set 2)
f3 = B.get_file(get_fname(580, 2))
red_dataXsec_3 = f3['red_dataXsec']
red_dataXsec_err_3 = f3['red_dataXsec_err']    
red_dataXsec_syst_err_3 = f3['red_dataXsec_syst_err']  
red_dataXsec_tot_err_3 = f3['red_dataXsec_tot_err']
red_pwiaXsec_3 = f3['red_pwiaXsec']         
red_fsiXsec_3 = f3['red_fsiXsec']              
#convert2NaN(red_dataXsec_syst_err_3, value=-1.)

#750 MeV (set 1)
f4 = B.get_file(get_fname(750, 1))
red_dataXsec_4 = f4['red_dataXsec']          
red_dataXsec_err_4 = f4['red_dataXsec_err']
red_dataXsec_syst_err_4 = f4['red_dataXsec_syst_err'] 
red_dataXsec_tot_err_4 = f4['red_dataXsec_tot_err']
red_pwiaXsec_4 = f4['red_pwiaXsec']          
red_fsiXsec_4 = f4['red_fsiXsec']                
#convert2NaN(red_dataXsec_syst_err_4, value=-1.)

#750 MeV (set 2)
f5 = B.get_file(get_fname(750, 2))
red_dataXsec_5 = f5['red_dataXsec']            
red_dataXsec_err_5 = f5['red_dataXsec_err']
red_dataXsec_syst_err_5 = f5['red_dataXsec_syst_err']
red_dataXsec_tot_err_5 = f5['red_dataXsec_tot_err']
red_pwiaXsec_5 = f5['red_pwiaXsec']            
red_fsiXsec_5 = f5['red_fsiXsec']              
#convert2NaN(red_dataXsec_syst_err_5, value=-1.)

#750 MeV (set 3)
f6 = B.get_file(get_fname(750, 3))
red_dataXsec_6 = f6['red_dataXsec']            
red_dataXsec_err_6 = f6['red_dataXsec_err']
red_dataXsec_syst_err_6 = f6['red_dataXsec_syst_err'] 
red_dataXsec_tot_err_6 = f6['red_dataXsec_tot_err']  
red_pwiaXsec_6 = f6['red_pwiaXsec']              
red_fsiXsec_6 = f6['red_fsiXsec']               
#convert2NaN(red_dataXsec_syst_err_6, value=-1.)

#Get Average Pmiss
pm1_b, pm80 = get_pm_avg(80, 1)
pm2_b, pm580_set1 = get_pm_avg(580, 1)
pm3_b, pm580_set2 = get_pm_avg(580, 2)
pm4_b, pm750_set1 = get_pm_avg(750, 1)
pm5_b, pm750_set2 = get_pm_avg(750, 2)
pm6_b, pm750_set3 = get_pm_avg(750, 3)


#Get Normalization and Kinematic systematics (from individual sets)
#to combine them and determine the overall final contributions from each
#For the systematics arrays, replace elements in which the redXsec = -1, with zero        
#for the corresponding systematic bin (Pm, thnq) bins                                        
kin80 = np.where(red_dataXsec_1==-1., 0., dfile(get_sys_fname(80, 1))['dsig_kin_tot'])
kin580_set1 = np.where(red_dataXsec_2==-1., 0., dfile(get_sys_fname(580, 1))['dsig_kin_tot'])
kin580_set2 = np.where(red_dataXsec_3==-1., 0., dfile(get_sys_fname(580, 2))['dsig_kin_tot'])
kin750_set1 = np.where(red_dataXsec_4==-1., 0., dfile(get_sys_fname(750, 1))['dsig_kin_tot'])
kin750_set2 = np.where(red_dataXsec_5==-1., 0., dfile(get_sys_fname(750, 2))['dsig_kin_tot'])
kin750_set3 = np.where(red_dataXsec_6==-1., 0., dfile(get_sys_fname(750, 3))['dsig_kin_tot'])

norm80 = np.where(red_dataXsec_1==-1., 0., dfile(get_sys_fname(80, 1))['dsig_norm_tot'])
norm580_set1 = np.where(red_dataXsec_2==-1., 0., dfile(get_sys_fname(580, 1))['dsig_norm_tot'])
norm580_set2 = np.where(red_dataXsec_3==-1., 0., dfile(get_sys_fname(580, 2))['dsig_norm_tot'])
norm750_set1 = np.where(red_dataXsec_4==-1., 0., dfile(get_sys_fname(750, 1))['dsig_norm_tot'])
norm750_set2 = np.where(red_dataXsec_5==-1., 0., dfile(get_sys_fname(750, 2))['dsig_norm_tot'])
norm750_set3 = np.where(red_dataXsec_6==-1., 0., dfile(get_sys_fname(750, 3))['dsig_norm_tot'])

#For the systematics arrays, mask elements in which the redXsec = -1,
#as when this array was created, systemaics were calculated for all (Pm, thnq) bins


#Loop over all 2d bins
for ib in range(len(i_b)):
    
    #----------Calculate the Data Reduced Xsec Weighted Average for a given (Pm, th_nq) bin of a given kin. set------------

    #array of redcued cross section for each (Pm, tnq) bin :: (80, 580_set1, 580_set2, . . .)
    red_dataXsec_arr = np.array([red_dataXsec_1[ib], red_dataXsec_2[ib], red_dataXsec_3[ib], red_dataXsec_4[ib], red_dataXsec_5[ib], red_dataXsec_6[ib]])
    red_dataXsec_m = ma.masked_values(red_dataXsec_arr, -1.)

    #Define the weights (Use ONLY statistical)
    red_dataXsec_weights = np.array([1./red_dataXsec_err_1[ib]**2, 1./red_dataXsec_err_2[ib]**2, 1./red_dataXsec_err_3[ib]**2, 1./red_dataXsec_err_4[ib]**2, 1./red_dataXsec_err_5[ib]**2, 1./red_dataXsec_err_6[ib]**2 ])
    red_dataXsec_weights_m = ma.masked_values(red_dataXsec_weights, 1.)


    #=======DATA REDUCED CROSS SECTION WEIGHTED AVERAGE==========
    red_dataXsec_avg = np.ma.average(red_dataXsec_m, weights=red_dataXsec_weights)
    red_dataXsec_avg_err = 1. / np.sqrt(np.sum(red_dataXsec_weights_m))    #combined data sets statistical uncertainty per (Pm, thnq) bin

    #================AVERAGE SYSTEMATIC ERROR================
    #systematics error array per (Pm, thnq) bin :: (80_syst, 580_set1_syst, . . .)
    #red_dataXsec_syst_err_arr = np.array([red_dataXsec_syst_err_1[ib], red_dataXsec_syst_err_2[ib], red_dataXsec_syst_err_3[ib], red_dataXsec_syst_err_4[ib], red_dataXsec_syst_err_5[ib], red_dataXsec_syst_err_6[ib]])
    #red_dataXsec_syst_err_m = ma.masked_values(red_dataXsec_syst_err_arr, -1.)
    #red_dataXsec_avg_syst_err = np.sqrt(ma.sum(red_dataXsec_syst_err_m**2))   #square-root of the sum of the squares (added systematics in quadrature, since each pm setting is independent)

    #========ADD AVERAGED STATISTICAL & SYSTEMATIC ERRORS IN QUADRATURE=========
    #red_dataXsec_avg_tot_err = np.sqrt(red_dataXsec_avg_err**2 + red_dataXsec_avg_syst_err**2)

    #ALTERNATIVELY:  ADD RELATIVE ERRORS IN QUADRATURE FIRST
    #1) Add Kinematic systematics
    kin_syst_tot = np.sqrt(kin80[ib]**2 + kin580_set1[ib]**2 + kin580_set2[ib]**2 + kin750_set1[ib]**2 + kin750_set2[ib]**2 + kin750_set3[ib]**2)
    #2) Add normalization systematics
    norm_syst_tot = np.sqrt(norm80[ib]**2 + norm580_set1[ib]**2 + norm580_set2[ib]**2 + norm750_set1[ib]**2 + norm750_set2[ib]**2 + norm750_set3[ib]**2)
    
    if(xb[ib]==35):
        print('80=',norm80[ib], '580_set1=',norm580_set1[ib], '580_set2=',norm580_set2[ib], '750_set1=',norm750_set1[ib], '750_set2=',norm750_set2[ib], '750_set3=',norm750_set3[ib])
    #3) Add systematics in quadrature
    tot_syst_err = np.sqrt(kin_syst_tot**2 + norm_syst_tot**2)

    #DEfine statistical relative error
    tot_stats_err = red_dataXsec_avg_err/red_dataXsec_avg 
    
    #4) Add statistical and systematics relative error in quadrature
    tot_err = np.sqrt(tot_stats_err**2 + tot_syst_err**2)
    

    #===Calculate Absolute Error on the Reduced Cross Section===
    red_dataXsec_avg_syst_err = red_dataXsec_avg*tot_syst_err
    red_dataXsec_avg_tot_err = red_dataXsec_avg*tot_err


    
    #================
    # THEORY AVERAGE
    #================
    red_pwiaXsec_arr = np.array([red_pwiaXsec_1[ib], red_pwiaXsec_2[ib], red_pwiaXsec_3[ib], red_pwiaXsec_4[ib], red_pwiaXsec_5[ib], red_pwiaXsec_6[ib]])
    red_pwiaXsec_arr_m = np.ma.masked_values(red_pwiaXsec_arr, -1.)
    red_pwiaXsec_avg = np.ma.average(red_pwiaXsec_arr_m)
   
    red_fsiXsec_arr = np.array([red_fsiXsec_1[ib], red_fsiXsec_2[ib], red_fsiXsec_3[ib], red_fsiXsec_4[ib], red_fsiXsec_5[ib], red_fsiXsec_6[ib]])
    red_fsiXsec_arr_m = np.ma.masked_values(red_fsiXsec_arr, -1.)
    red_fsiXsec_avg = np.ma.average(red_fsiXsec_arr_m)

    #==================================
    # Get the Average Missing Momentum
    #==================================

    pm_arr = np.array([pm80[ib], pm580_set1[ib], pm580_set2[ib], pm750_set1[ib], pm750_set2[ib], pm750_set3[ib]])
    pm_arr_m = np.ma.masked_values(pm_arr, 0.)

    pm_avg = np.ma.average(pm_arr_m) / 1000.  #Convert to GeV


    l="%i  %i  %i  %f   %f   %f   %f   %f   %f   %f   %f   %.12e  %.12e  %.12e  %.12e  %.12e  %.12e \n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], pm_avg, kin_syst_tot, norm_syst_tot, tot_syst_err, tot_stats_err, tot_err, red_dataXsec_avg, red_dataXsec_avg_err, red_dataXsec_avg_syst_err, red_dataXsec_avg_tot_err, red_pwiaXsec_avg, red_fsiXsec_avg )
    fout.write(l)

    

fout.close()

