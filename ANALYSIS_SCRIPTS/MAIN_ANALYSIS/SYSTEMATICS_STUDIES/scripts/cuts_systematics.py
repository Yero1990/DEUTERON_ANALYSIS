import LT.box as B
import numpy as np
import os
import sys
from sys import argv
import numpy.ma as ma
import plot_utils as pu   #module with my defined fucntions for plotting

#Code to estimate systematic effects from cut variations of different variables. The
#Xsec variations using different cuts is measured, and we use Roger Barlow's approach
#to determine whether the systematic effect is significant enough to be considered a 
#systematic error. 

def calc_systematics(study='', sys_ext1='',sys_ext2='', stats_thrs=0.):

    print('Calculating Systematics for %s,  Cut Setting:%s'%(study, sys_ext2))

    #Argument: sys_ext1,2 are the extension name of the systematics studies files to be read. sys_ext1 = 'Em80MeV' by default (see main)
    #The sys_ext2 (assume to be subset of the cut varied) is subtracted from sys_ext1 (assumed to be total set of the cut varied),
    #stats_thrs is the satistics threshold to set on the measued cross section. (only plot XSec below ceratin stats. uncertainty)

    #check if directory to store systematics datafiles exists, else creates it.
    study_dir = "../datafiles/"+study+"_study"
    if not os.path.exists(study_dir):
        os.makedirs(study_dir)
        
    #Open .txt file to write systematics
    output_file='%s/systematics%s.txt'%(study_dir, sys_ext2)
    fout = open(output_file, 'w') 

    #------------------------------------------------------------                   
    # header information for the output file    
    header = """        
    #This file contains the del = XSec_1 - Xsec2 (diff. between cross sections with diff. cuts),  sig_del: sqrt(sigXsec1**2 - sigXsec2**2), R = del / sig_del
    #If R > 2, there is a significant difference between the cuts.
    #In this file, there are also the cross sections with nominal cuts, and the new cuts for direct comparisons
    #xb = th_nq [central bin value]                                                                                                    
    #yb = pm [central bin value]                                                                       
    # current header line:  
    #!i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  del80[f,5]/   sig_del80[f,6]/    R80[f,7]/    del_580set1[f,8]/   sig_del580set1[f,9]/    R580set1[f,10]/   del_580set2[f,11]/   sig_del580set2[f,12]/    R580set2[f,13]/   del_750set1[f,14]/   sig_del750set1[f,15]/    R750set1[f,16]/  del_750set2[f,17]/   sig_del750set2[f,18]/    R750set2[f,19]/  del_750set3[f,20]/   sig_del750set3[f,21]/    R750set3[f,22]/  dataXsec_80_nom[f,23]/   dataXsec_err_80_nom[f,24]/   dataXsec_580set1_nom[f,25]/   dataXsec_err_580set1_nom[f,26]/  dataXsec_580set2_nom[f,27]/   dataXsec_err_580set2_nom[f,28]/  dataXsec_750set1_nom[f,29]/   dataXsec_err_750set1_nom[f,30]/  dataXsec_750set2_nom[f,31]/   dataXsec_err_750set2_nom[f,32]/   dataXsec_750set3_nom[f,33]/   dataXsec_err_750set3_nom[f,34]/   dataXsec_80[f,35]/   dataXsec_err_80[f,36]/   dataXsec_580set1[f,37]/   dataXsec_err_580set1[f,38]/  dataXsec_580set2[f,39]/   dataXsec_err_580set2[f,40]/  dataXsec_750set1[f,41]/   dataXsec_err_750set1[f,42]/  dataXsec_750set2[f,43]/   dataXsec_err_750set2[f,44]/   dataXsec_750set3[f,45]/   dataXsec_err_750set3[f,46]/
    """
    fout.write(header)

    
    #Open File Containing Cross Sections with the largest set (would be widest cut. For Emiss, it is Em < 80 MeV ) -- TOTAL SET
    fname80_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm80_laget_bc_corr.txt'%(sys_ext1)
    fname580_set1_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm580_laget_bc_corr_set1.txt'%(sys_ext1)
    fname580_set2_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm580_laget_bc_corr_set2.txt'%(sys_ext1)
    fname750_set1_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set1.txt'%(sys_ext1)
    fname750_set2_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set2.txt'%(sys_ext1)
    fname750_set3_nom = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set3.txt'%(sys_ext1)
    
    #Open File Containing Cross Sections with variational Emiss cuts (or any other cuts, depends on what sys_ext2 is) --SUBSET
    fname80 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm80_laget_bc_corr.txt'%(sys_ext2)
    fname580_set1 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm580_laget_bc_corr_set1.txt'%(sys_ext2)
    fname580_set2 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm580_laget_bc_corr_set2.txt'%(sys_ext2)
    fname750_set1 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set1.txt'%(sys_ext2)
    fname750_set2 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set2.txt'%(sys_ext2)
    fname750_set3 = '../../Deep_CrossSections/bin_centering_corrections/%s/pm750_laget_bc_corr_set3.txt'%(sys_ext2)

    #Get bin information 
    f1_nom = B.get_file(fname80_nom)
    i_b = B.get_data(f1_nom, 'i_b')
    i_x = B.get_data(f1_nom, 'i_x')
    i_y = B.get_data(f1_nom, 'i_y')
    xb = B.get_data(f1_nom, 'xb')
    yb = B.get_data(f1_nom, 'yb')
    
    
    #--------Get Nominal(largest Em cut set) Experimental Cross Sections (Already Radiative/Bin-Center corrected)----
    #80 MeV
    dataXsec_80_nom = B.get_data(f1_nom, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_80_nom = B.get_data(f1_nom, 'fsiRC_dataXsec_fsibc_corr_err')              
    
    #580 MeV (set 1)
    f2_nom = B.get_file(fname580_set1_nom)
    dataXsec_580set1_nom = B.get_data(f2_nom, 'fsiRC_dataXsec_fsibc_corr')            
    dataXsec_err_580set1_nom = B.get_data(f2_nom, 'fsiRC_dataXsec_fsibc_corr_err')                
    
    #580 MeV (set 2)
    f3_nom = B.get_file(fname580_set2_nom)
    dataXsec_580set2_nom = B.get_data(f3_nom, 'fsiRC_dataXsec_fsibc_corr')             
    dataXsec_err_580set2_nom = B.get_data(f3_nom, 'fsiRC_dataXsec_fsibc_corr_err')                   
    
    #750 MeV (set 1)
    f4_nom = B.get_file(fname750_set1_nom)
    dataXsec_750set1_nom = B.get_data(f4_nom, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set1_nom = B.get_data(f4_nom, 'fsiRC_dataXsec_fsibc_corr_err')                   
    
    #750 MeV (set 2)
    f5_nom = B.get_file(fname750_set2_nom)
    dataXsec_750set2_nom = B.get_data(f5_nom, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set2_nom = B.get_data(f5_nom, 'fsiRC_dataXsec_fsibc_corr_err')                 
    
    #750 MeV (set 3)
    f6_nom = B.get_file(fname750_set3_nom)
    dataXsec_750set3_nom = B.get_data(f6_nom, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set3_nom = B.get_data(f6_nom, 'fsiRC_dataXsec_fsibc_corr_err')      
    
    #--------Get Experimental Cross Sections with Variation on a Cut (Already Radiative/Bin-Center corrected)--------
    #80 MeV
    f1 = B.get_file(fname80)
    dataXsec_80 = B.get_data(f1, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_80 = B.get_data(f1, 'fsiRC_dataXsec_fsibc_corr_err')              
    
    #580 MeV (set 1)
    f2 = B.get_file(fname580_set1)
    dataXsec_580set1 = B.get_data(f2, 'fsiRC_dataXsec_fsibc_corr')            
    dataXsec_err_580set1 = B.get_data(f2, 'fsiRC_dataXsec_fsibc_corr_err')                
    
    #580 MeV (set 2)
    f3 = B.get_file(fname580_set2)
    dataXsec_580set2 = B.get_data(f3, 'fsiRC_dataXsec_fsibc_corr')             
    dataXsec_err_580set2 = B.get_data(f3, 'fsiRC_dataXsec_fsibc_corr_err')                   
    
    #750 MeV (set 1)
    f4 = B.get_file(fname750_set1)
    dataXsec_750set1 = B.get_data(f4, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set1 = B.get_data(f4, 'fsiRC_dataXsec_fsibc_corr_err')                   
    
    #750 MeV (set 2)
    f5 = B.get_file(fname750_set2)
    dataXsec_750set2 = B.get_data(f5, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set2 = B.get_data(f5, 'fsiRC_dataXsec_fsibc_corr_err')                 
    
    #750 MeV (set 3)
    f6 = B.get_file(fname750_set3)
    dataXsec_750set3 = B.get_data(f6, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set3 = B.get_data(f6, 'fsiRC_dataXsec_fsibc_corr_err')     
    

    '''
    #--------Get Nominal(largest Em cut set) Experimental Cross Sections (Already Radiative/ NO Bin-Center corrected)----
    #80 MeV
    dataXsec_80_nom = B.get_data(f1_nom, 'fsiRC_dataXsec')              
    dataXsec_err_80_nom = B.get_data(f1_nom, 'fsiRC_dataXsec_err')              
    
    #580 MeV (set 1)
    f2_nom = B.get_file(fname580_set1_nom)
    dataXsec_580set1_nom = B.get_data(f2_nom, 'fsiRC_dataXsec')            
    dataXsec_err_580set1_nom = B.get_data(f2_nom, 'fsiRC_dataXsec_err')                
    
    #580 MeV (set 2)
    f3_nom = B.get_file(fname580_set2_nom)
    dataXsec_580set2_nom = B.get_data(f3_nom, 'fsiRC_dataXsec')             
    dataXsec_err_580set2_nom = B.get_data(f3_nom, 'fsiRC_dataXsec_err')                   
    
    #750 MeV (set 1)
    f4_nom = B.get_file(fname750_set1_nom)
    dataXsec_750set1_nom = B.get_data(f4_nom, 'fsiRC_dataXsec')              
    dataXsec_err_750set1_nom = B.get_data(f4_nom, 'fsiRC_dataXsec_err')                   
    
    #750 MeV (set 2)
    f5_nom = B.get_file(fname750_set2_nom)
    dataXsec_750set2_nom = B.get_data(f5_nom, 'fsiRC_dataXsec')              
    dataXsec_err_750set2_nom = B.get_data(f5_nom, 'fsiRC_dataXsec_err')                 
    
    #750 MeV (set 3)
    f6_nom = B.get_file(fname750_set3_nom)
    dataXsec_750set3_nom = B.get_data(f6_nom, 'fsiRC_dataXsec')              
    dataXsec_err_750set3_nom = B.get_data(f6_nom, 'fsiRC_dataXsec_err')      
    
    #--------Get Experimental Cross Sections with Variation on a Cut (Already Radiative/Bin-Center corrected)--------
    #80 MeV
    f1 = B.get_file(fname80)
    dataXsec_80 = B.get_data(f1, 'fsiRC_dataXsec')              
    dataXsec_err_80 = B.get_data(f1, 'fsiRC_dataXsec_err')              
    
    #580 MeV (set 1)
    f2 = B.get_file(fname580_set1)
    dataXsec_580set1 = B.get_data(f2, 'fsiRC_dataXsec')            
    dataXsec_err_580set1 = B.get_data(f2, 'fsiRC_dataXsec_err')                
    
    #580 MeV (set 2)
    f3 = B.get_file(fname580_set2)
    dataXsec_580set2 = B.get_data(f3, 'fsiRC_dataXsec')             
    dataXsec_err_580set2 = B.get_data(f3, 'fsiRC_dataXsec_err')                   
    
    #750 MeV (set 1)
    f4 = B.get_file(fname750_set1)
    dataXsec_750set1 = B.get_data(f4, 'fsiRC_dataXsec')              
    dataXsec_err_750set1 = B.get_data(f4, 'fsiRC_dataXsec_err')                   
    
    #750 MeV (set 2)
    f5 = B.get_file(fname750_set2)
    dataXsec_750set2 = B.get_data(f5, 'fsiRC_dataXsec')              
    dataXsec_err_750set2 = B.get_data(f5, 'fsiRC_dataXsec_err')                 
    
    #750 MeV (set 3)
    f6 = B.get_file(fname750_set3)
    dataXsec_750set3 = B.get_data(f6, 'fsiRC_dataXsec')              
    dataXsec_err_750set3 = B.get_data(f6, 'fsiRC_dataXsec_err')  
    '''

    #Mask Xsec and Ratio Arrays given a statistical uncertainty > threshold

    #NOMINAL Xsec (Cut with the largest set)
    dataXsec_80_nom_masked = np.ma.array(dataXsec_80_nom, mask=(dataXsec_err_80_nom>stats_thrs*dataXsec_80_nom))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_nom_masked = np.ma.filled(dataXsec_80_nom_masked.astype(float), -1.)   #assign the mask a value of "-1"
   
    dataXsec_580set1_nom_masked = np.ma.array(dataXsec_580set1_nom, mask=(dataXsec_err_580set1_nom>stats_thrs*dataXsec_580set1_nom))  
    dataXsec_580set1_nom_masked = np.ma.filled(dataXsec_580set1_nom_masked.astype(float), -1.)

    dataXsec_580set2_nom_masked = np.ma.array(dataXsec_580set2_nom, mask=(dataXsec_err_580set2_nom>stats_thrs*dataXsec_580set2_nom))  
    dataXsec_580set2_nom_masked = np.ma.filled(dataXsec_580set2_nom_masked.astype(float), -1.)

    dataXsec_750set1_nom_masked = np.ma.array(dataXsec_750set1_nom, mask=(dataXsec_err_750set1_nom>stats_thrs*dataXsec_750set1_nom))  
    dataXsec_750set1_nom_masked = np.ma.filled(dataXsec_750set1_nom_masked.astype(float), -1.)

    dataXsec_750set2_nom_masked = np.ma.array(dataXsec_750set2_nom, mask=(dataXsec_err_750set2_nom>stats_thrs*dataXsec_750set2_nom))  
    dataXsec_750set2_nom_masked = np.ma.filled(dataXsec_750set2_nom_masked.astype(float), -1.)

    dataXsec_750set3_nom_masked = np.ma.array(dataXsec_750set3_nom, mask=(dataXsec_err_750set3_nom>stats_thrs*dataXsec_750set3_nom))  
    dataXsec_750set3_nom_masked = np.ma.filled(dataXsec_750set3_nom_masked.astype(float), -1.)

    #Variational Xsec (Subset cut)
    dataXsec_80_masked = np.ma.array(dataXsec_80, mask=(dataXsec_err_80>stats_thrs*dataXsec_80))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_masked = np.ma.filled(dataXsec_80_masked.astype(float), -1.)
   
    dataXsec_580set1_masked = np.ma.array(dataXsec_580set1, mask=(dataXsec_err_580set1>stats_thrs*dataXsec_580set1))  
    dataXsec_580set1_masked = np.ma.filled(dataXsec_580set1_masked.astype(float), -1.)

    dataXsec_580set2_masked = np.ma.array(dataXsec_580set2, mask=(dataXsec_err_580set2>stats_thrs*dataXsec_580set2))  
    dataXsec_580set2_masked = np.ma.filled(dataXsec_580set2_masked.astype(float), -1.)

    dataXsec_750set1_masked = np.ma.array(dataXsec_750set1, mask=(dataXsec_err_750set1>stats_thrs*dataXsec_750set1))  
    dataXsec_750set1_masked = np.ma.filled(dataXsec_750set1_masked.astype(float), -1.)

    dataXsec_750set2_masked = np.ma.array(dataXsec_750set2, mask=(dataXsec_err_750set2>stats_thrs*dataXsec_750set2))  
    dataXsec_750set2_masked = np.ma.filled(dataXsec_750set2_masked.astype(float), -1.)

    dataXsec_750set3_masked = np.ma.array(dataXsec_750set3, mask=(dataXsec_err_750set3>stats_thrs*dataXsec_750set3))  
    dataXsec_750set3_masked = np.ma.filled(dataXsec_750set3_masked.astype(float), -1.)
    

    #Loop over all 2d bins
    for ib in range(len(i_b)):
    

        #--------------------80 MeV Setting------------------------
        #Check if bin has Xsec for both, (the total set[nom] and subset files)
        if(dataXsec_80_nom_masked[ib]>0 and dataXsec_80_masked[ib]>0):
            #Calculate differences between cross sections
            del80 = dataXsec_80_nom[ib] - dataXsec_80[ib]                        #difference between cross sections (sig_totalSet - sig_subSet)
            var_del80 = dataXsec_err_80_nom[ib]**2 - dataXsec_err_80[ib]**2      #difference of the variances
            sig_del80 = np.sqrt(abs(var_del80))                               #standard deviation
            if(sig_del80>0):
                R80 =  del80 / sig_del80                                     #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                #print('----------------------------------')
                #print('dataXsec80=',dataXsec_80_masked[ib],'dataXsec80_err=',dataXsec_err_80[ib])
                #print('dataXsec80_nom=',dataXsec_80_nom_masked[ib],'dataXsec80_err_nom=',dataXsec_err_80_nom[ib])
                #print('ib=',i_b[ib],' pm=',yb[ib],' thnq=',xb[ib],' del80=',del80,' var_del80=',var_del80,' sig_del80=',sig_del80,' R80=',R80)
                #print('----------------------------------')

            else:
                R80 = -1000.
        else:
            del80 = -1000.
            var_del80 = -1000.
            sig_del80 = -1000.
            R80 = -1000.
    
        #--------------------580 (set1) MeV Setting------------------------
        #Check if bin has Xsec for both files
        if(dataXsec_580set1_nom_masked[ib]>0 and dataXsec_580set1_masked[ib]>0):
            #Calculate differences between cross sections
            del_580set1 = dataXsec_580set1_nom[ib] - dataXsec_580set1[ib]                        #difference between cross sections
            var_del580set1 = dataXsec_err_580set1_nom[ib]**2 - dataXsec_err_580set1[ib]**2       #difference of the variances
            sig_del580set1 = np.sqrt(abs(var_del580set1))                                        #standard deviation
            if(sig_del580set1>0):
                R580set1 =  del_580set1 / sig_del580set1                                         #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
            else:
                R580set1 = -1000.
        #Else, set to -1000.
        else:
            del_580set1 = -1000.
            var_del580set1 = -1000.
            sig_del580set1 = -1000.
            R580set1 = -1000.
   
        #--------------------580 (set2) MeV Setting------------------------
        #Check if bin has Xsec for both files
        if(dataXsec_580set2_nom_masked[ib]>0 and dataXsec_580set2_masked[ib]>0):
            #Calculate differences between cross sections
            del_580set2 = dataXsec_580set2_nom[ib] - dataXsec_580set2[ib]                        #difference between cross sections
            var_del580set2 = dataXsec_err_580set2_nom[ib]**2 - dataXsec_err_580set2[ib]**2       #difference of the variances
            sig_del580set2 = np.sqrt(abs(var_del580set2))                                        #standard deviation
            if(sig_del580set2>0):
                R580set2 =  del_580set2 / sig_del580set2                                         #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
            else:
                R580set2 = -1000.
        #Else, set to -1000.
        else:
            del_580set2 = -1000.
            var_del580set2 = -1000.
            sig_del580set2 = -1000.
            R580set2 = -1000.


        #--------------------750 (set1) MeV Setting------------------------
        #Check if bin has Xsec for both files
        if(dataXsec_750set1_nom_masked[ib]>0 and dataXsec_750set1_masked[ib]>0):
            #Calculate differences between cross sections
            del_750set1 = dataXsec_750set1_nom[ib] - dataXsec_750set1[ib]                        #difference between cross sections
            var_del750set1 = dataXsec_err_750set1_nom[ib]**2 - dataXsec_err_750set1[ib]**2       #difference of the variances
            sig_del750set1 = np.sqrt(abs(var_del750set1))                                        #standard deviation
            if(sig_del750set1>0):
                R750set1 =  del_750set1 / sig_del750set1                                         #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
            else:
                R750set1 = -1000.
        #Else, set to -1000.
        else:
            del_750set1 = -1000.
            var_del750set1 = -1000.
            sig_del750set1 = -1000.
            R750set1 = -1000.
   
        #--------------------750 (set2) MeV Setting------------------------
        #Check if bin has Xsec for both files
        if(dataXsec_750set2_nom_masked[ib]>0 and dataXsec_750set2_masked[ib]>0):
            #Calculate differences between cross sections
            del_750set2 = dataXsec_750set2_nom[ib] - dataXsec_750set2[ib]                        #difference between cross sections
            var_del750set2 = dataXsec_err_750set2_nom[ib]**2 - dataXsec_err_750set2[ib]**2       #difference of the variances
            sig_del750set2 = np.sqrt(abs(var_del750set2))                                        #standard deviation
            if(sig_del750set2>0):
                R750set2 =  del_750set2 / sig_del750set2                                         #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
            else:
                R750set2 = -1000.
        #Else, set to -1000.
        else:
            del_750set2 = -1000.
            var_del750set2 = -1000.
            sig_del750set2 = -1000.
            R750set2 = -1000.

        #--------------------750 (set3) MeV Setting------------------------
        #Check if bin has Xsec for both files
        if(dataXsec_750set3_nom_masked[ib]>0 and dataXsec_750set3_masked[ib]>0):
            #Calculate differences between cross sections
            del_750set3 = dataXsec_750set3_nom[ib] - dataXsec_750set3[ib]                        #difference between cross sections
            var_del750set3 = dataXsec_err_750set3_nom[ib]**2 - dataXsec_err_750set3[ib]**2       #difference of the variances
            sig_del750set3 = np.sqrt(abs(var_del750set3))                                        #standard deviation
            if(sig_del750set3>0):
                R750set3 =  del_750set3 / sig_del750set3                                         #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
            else:
                R750set3 = -1000.
        #Else, set to -1000.
        else:
            del_750set3 = -1000.
            var_del750set3 = -1000.
            sig_del750set3 = -1000.
            R750set3 = -1000.

        fout.write("%i %i %i %f %f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e\n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], del80, sig_del80, R80, del_580set1, sig_del580set1, R580set1, del_580set2, sig_del580set2, R580set2, del_750set1, sig_del750set1, R750set1,  del_750set2, sig_del750set2, R750set2,  del_750set3, sig_del750set3, R750set3, dataXsec_80_nom_masked[ib], dataXsec_err_80_nom[ib], dataXsec_580set1_nom_masked[ib], dataXsec_err_580set1_nom[ib], dataXsec_580set2_nom_masked[ib], dataXsec_err_580set2_nom[ib], dataXsec_750set1_nom_masked[ib], dataXsec_err_750set1_nom[ib], dataXsec_750set2_nom_masked[ib], dataXsec_err_750set2_nom[ib], dataXsec_750set3_nom_masked[ib], dataXsec_err_750set3_nom[ib], dataXsec_80_masked[ib], dataXsec_err_80[ib], dataXsec_580set1_masked[ib], dataXsec_err_580set1[ib], dataXsec_580set2_masked[ib], dataXsec_err_580set2[ib], dataXsec_750set1_masked[ib], dataXsec_err_750set1[ib], dataXsec_750set2_masked[ib], dataXsec_err_750set2[ib], dataXsec_750set3_masked[ib], dataXsec_err_750set3[ib]))


    print('Finished!')
    fout.close()


def main():
    print('Entering Main . . .')

    #User Input (what type of systematics? Enter two descriptions)
    #We want to compare the largest set with any other subsets variable cuts. (Ex. Em80MeV-Em40MeV, or Em80MeV-Em50MeV,  . . . )
    
    stats_thrs = 0.5  #Statistics Threshold (ONLY use data Xsec which are withih the statistical uncertainty of the mean Xsec)



    #---------Specific for User Input ONLY---------------
    #sys_ext2 = sys.argv[1] #"Em30MeV"   #second systematics name to compare with nominal 
    #stats_thrs = float(sys.argv[2])  #Statistical Uncertainty threshold (in fractional percent, e.x. 0.5 (would mean 50%)

    #Calculate systematics
    #calc_systematics(sys_ext1, sys_ext2, stats_thrs)

    #Plot Results
    #plot_data_sets(sys_ext1, sys_ext2)
    #-----------------------------------------------------

    
    #--------Calc. ALl Systematics for Missing Energy Cut Variation-----------
    
    #Emiss Systematics
    study= "Em"      #What Systematic Study to be done? "Em", "Ztar", "hColl", 
    sys_ext1 = "Em_70MeV"  # the largest (total) set

    calc_systematics(study, sys_ext1, "Em_30MeV", stats_thrs)
    calc_systematics(study, sys_ext1, "Em_40MeV", stats_thrs)
    #calc_systematics(study, sys_ext1, "Em_45MeV", stats_thrs)
    calc_systematics(study, sys_ext1, "Em_50MeV", stats_thrs)
    calc_systematics(study, sys_ext1, "Em_60MeV", stats_thrs)
    #calc_systematics(study, sys_ext1, "Em_70MeV", stats_thrs)

    #Call Plotting Functions
    pu.plotEm_syst(study, stats_thrs)
    #pu.plotXsec_vs_Emcuts(study, stats_thrs, 45) #the last argument is the theta_nq central bin value

    
    '''
    #--------Calc. ALl Systematics for ZtarDiff Cut Variation------------
    #Ztar Systematics
    study= "Ztar"      #What Systematic Study to be done? "Em", "Ztar", "hColl", 
    sys_ext1 = "Ztar3.0cm"  # the largest (total) set

    #calc_systematics(study, sys_ext1, "Ztar2.5cm", stats_thrs)
    #calc_systematics(study, sys_ext1, "Ztar2.0cm", stats_thrs)
    #calc_systematics(study, sys_ext1, "Ztar1.5cm", stats_thrs)
    #calc_systematics(study, sys_ext1, "Ztar1.0cm", stats_thrs)
    #calc_systematics(study, sys_ext1, "Ztar0.5cm", stats_thrs)
    
    pu.plotZtar_syst(study, stats_thrs)
    #pu.plotXsec_vs_Ztarcuts(study, stats_thrs, 45)

    
    #--------Calc. All Systematics for HMS Collimator Cut Variation------------
    #hColl Systematics
    study= "hColl"      #What Systematic Study to be done? "Em", "Ztar", "hColl", 
    sys_ext1 = "hColl1.1"  # the largest (total) set

    #calc_systematics(study, sys_ext1, "hColl1.0", stats_thrs)
    #calc_systematics(study, sys_ext1, "hColl0.9", stats_thrs)
    #calc_systematics(study, sys_ext1, "hColl0.8", stats_thrs)
    
    pu.plothColl_syst(study, stats_thrs)
    #pu.plotXsec_vs_hCollcuts(study, stats_thrs, 45)

    
    #--------Calc. All Systematics for Coincidence Time  Cut Variation------------
    #ctime Systematics
    study= "ctime"      #What Systematic Study to be done? "Em", "Ztar", "hColl", 
    sys_ext1 = "ctimeOFF"  # the largest (total) set

    #calc_systematics(study, sys_ext1, "ctimeON", stats_thrs)

    pu.plotctime_syst(study, stats_thrs)
    #pu.plotXsec_vs_ctimecuts(study, stats_thrs, 45)

    
    #--------Calc. All Systematics for SHMS Cal  Cut Variation------------
    #ctime Systematics
    study= "shmsCal"      #What Systematic Study to be done? "Em", "Ztar", "hColl", 
    sys_ext1 = "shmsCalOFF"  # the largest (total) set

    #calc_systematics(study, sys_ext1, "shmsCalON", stats_thrs)

    pu.plotpcal_syst(study, stats_thrs)
    #pu.plotXsec_vs_pcalcuts(study, stats_thrs, 45)
    '''

if __name__=="__main__":
    main()
