import LT.box as B
import numpy as np
import os
import sys
from sys import argv
import numpy.ma as ma

#Code to estimate systematic effects from cut variations of different variables. The
#Xsec variations using different cuts is measured, and we use Roger Barlow's approach
#to determine whether the systematic effect is significant enough to be considered a 
#systematic error. 

def calc_systematics(sys_ext1='',sys_ext2='', stats_thrs=0.):
 
    #Argument: sys_ext1,2 are the extension name of the systematics studies files to be read. sys_ext1 = 'nominal' by default (see main)
    #stats_thrs is the satistics threshold for which to calculate the systematics effects.

    #check if directory to store systematics exists, else creates it.
    dir_name = "../datafiles/"
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
        

    output_file='%s/systematics%s.txt'%(dir_name, sys_ext2)

    fout = open(output_file, 'w') 

    #------------------------------------------------------------                   
    # header information for the output file    
    header = """        
    #This file contains the del = XSec_1 - Xsec2 (diff. between cross sections with diff. cuts),  sig_del: sqrt(sigXsec1**2 - sigXsec2**2), R = del / sig_del
    #If R > 2, there is a significant difference between the cuts.
    #In this file, there are also the cross sections with nominal cuts, and the new cuts for direct comparisons
    #\\ xb = th_nq                                                                                                    
    #\\ yb = pm                                                                        
    # current header line:  
    #!i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  del80[f,5]/   sig_del80[f,6]/    R80[f,7]/    del_580set1[f,8]/   sig_del580set1[f,9]/    R580set1[f,10]/   del_580set2[f,11]/   sig_del580set2[f,12]/    R580set2[f,13]/   del_750set1[f,14]/   sig_del750set1[f,15]/    R750set1[f,16]/  del_750set2[f,17]/   sig_del750set2[f,18]/    R750set2[f,19]/  del_750set3[f,20]/   sig_del750set3[f,21]/    R750set3[f,22]/  dataXsec_80_nom[f,23]/   dataXsec_err_80_nom[f,24]/   dataXsec_580set1_nom[f,25]/   dataXsec_err_580set1_nom[f,26]/  dataXsec_580set2_nom[f,27]/   dataXsec_err_580set2_nom[f,28]/  dataXsec_750set1_nom[f,29]/   dataXsec_err_750set1_nom[f,30]/  dataXsec_750set2_nom[f,31]/   dataXsec_err_750set2_nom[f,32]/   dataXsec_750set3_nom[f,33]/   dataXsec_err_750set3_nom[f,34]/   dataXsec_80[f,35]/   dataXsec_err_80[f,36]/   dataXsec_580set1[f,37]/   dataXsec_err_580set1[f,38]/  dataXsec_580set2[f,39]/   dataXsec_err_580set2[f,40]/  dataXsec_750set1[f,41]/   dataXsec_err_750set1[f,42]/  dataXsec_750set2[f,43]/   dataXsec_err_750set2[f,44]/   dataXsec_750set3[f,45]/   dataXsec_err_750set3[f,46]/
    """
    fout.write(header)


    #Open File Containing Cross Sections with the largest set (would be Em < 80 MeV )
    fname80_nom = '../../Deep_CrossSections/average_Xsec/%s/pm80_laget.txt'%(sys_ext1)
    fname580_set1_nom = '../../Deep_CrossSections/average_Xsec/%s/pm580_laget_set1.txt'%(sys_ext1)
    fname580_set2_nom = '../../Deep_CrossSections/average_Xsec/%s/pm580_laget_set2.txt'%(sys_ext1)
    fname750_set1_nom = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set1.txt'%(sys_ext1)
    fname750_set2_nom = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set2.txt'%(sys_ext1)
    fname750_set3_nom = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set3.txt'%(sys_ext1)
    
    #Open File Containing Cross Sections with variational Emiss cuts (or any other cuts, depends on what sys_ext2 is)
    fname80 = '../../Deep_CrossSections/average_Xsec/%s/pm80_laget.txt'%(sys_ext2)
    fname580_set1 = '../../Deep_CrossSections/average_Xsec/%s/pm580_laget_set1.txt'%(sys_ext2)
    fname580_set2 = '../../Deep_CrossSections/average_Xsec/%s/pm580_laget_set2.txt'%(sys_ext2)
    fname750_set1 = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set1.txt'%(sys_ext2)
    fname750_set2 = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set2.txt'%(sys_ext2)
    fname750_set3 = '../../Deep_CrossSections/average_Xsec/%s/pm750_laget_set3.txt'%(sys_ext2)
    
    #Get bin information 
    f1_nom = B.get_file(fname80_nom)
    i_b = B.get_data(f1_nom, 'i_b')
    i_x = B.get_data(f1_nom, 'i_x')
    i_y = B.get_data(f1_nom, 'i_y')
    xb = B.get_data(f1_nom, 'xb')
    yb = B.get_data(f1_nom, 'yb')
    
    #--------Get Nominal(largest Em cut set) Experimental Cross Sections (Already Radiative/Bin-Center corrected)----
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
    
    #Mask Xsec and Ratio Arrays given a statistical uncertainty > threshold

    #NOMINAL Xsec (80 MeV setting)
    dataXsec_80_nom_masked = np.ma.array(dataXsec_80_nom, mask=(dataXsec_err_80_nom>stats_thrs*dataXsec_80_nom))  #mask if (sig>30 %) of mean
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

    #Variational Xsec (after changing cut)
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
        #Check if bin has Xsec for both files
        if(dataXsec_80_nom_masked[ib]>0 and dataXsec_80_masked[ib]>0):
            #Calculate differences between cross sections
            del80 = dataXsec_80_nom[ib] - dataXsec_80[ib]                        #difference between cross sections (sig_totalSet - sig_subSet)
            var_del80 = dataXsec_err_80_nom[ib]**2 - dataXsec_err_80[ib]**2      #difference of the variances
            sig_del80 = np.sqrt(abs(var_del80))                               #standard deviation
            if(sig_del80>0):
                R80 =  del80 / sig_del80                                     #Ratio of diffences in Xsec to std. dev (if >2, is sig. difference
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
        #Else, set to -1
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
        #Else, set to -1
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
        #Else, set to -1
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
        #Else, set to -1
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
        #Else, set to -1
        else:
            del_750set3 = -1000.
            var_del750set3 = -1000.
            sig_del750set3 = -1000.
            R750set3 = -1000.

        fout.write("%i %i %i %f %f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e\n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], del80, sig_del80, R80, del_580set1, sig_del580set1, R580set1, del_580set2, sig_del580set2, R580set2, del_750set1, sig_del750set1, R750set1,  del_750set2, sig_del750set2, R750set2,  del_750set3, sig_del750set3, R750set3, dataXsec_80_nom_masked[ib], dataXsec_err_80_nom[ib], dataXsec_580set1_nom_masked[ib], dataXsec_err_580set1_nom[ib], dataXsec_580set2_nom_masked[ib], dataXsec_err_580set2_nom[ib], dataXsec_750set1_nom_masked[ib], dataXsec_err_750set1_nom[ib], dataXsec_750set2_nom_masked[ib], dataXsec_err_750set2_nom[ib], dataXsec_750set3_nom_masked[ib], dataXsec_err_750set3_nom[ib], dataXsec_80_masked[ib], dataXsec_err_80[ib], dataXsec_580set1_masked[ib], dataXsec_err_580set1[ib], dataXsec_580set2_masked[ib], dataXsec_err_580set2[ib], dataXsec_750set1_masked[ib], dataXsec_err_750set1[ib], dataXsec_750set2_masked[ib], dataXsec_err_750set2[ib], dataXsec_750set3_masked[ib], dataXsec_err_750set3[ib]))


    print('Loop Done')
    fout.close()


def plot_data_sets(sys_ext1='',sys_ext2=''):

    #----------------PLOT SYSTEMATICS RESULTS------------------
    
    #Create Directory to store plots
    dir_name = "../systematic_plots_%s"%(sys_ext2)
    #check if directory exists, else creates it.
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Read Data Files
    fsys = "../datafiles/systematics%s.txt"%(sys_ext2)
    
    f = B.get_file(fsys)

    #Get Bin Info
    i_b = B.get_data(f, 'i_b')
    i_x = B.get_data(f, 'i_x')
    i_y = B.get_data(f, 'i_y')
    thnq = B.get_data(f, 'xb')
    pm = B.get_data(f, 'yb')
    
    #Get Roger Barlow's Delta, Sigma and the Ratio R = Delta / sig_Delta
    del80 = B.get_data(f, 'del80')
    sig_del80 = B.get_data(f, 'sig_del80')
    R80 = B.get_data(f, 'R80')
    
    del_580set1 = B.get_data(f, 'del_580set1')
    sig_del580set1 = B.get_data(f, 'sig_del580set1')
    R580set1 = B.get_data(f, 'R580set1')
    
    del_580set2 = B.get_data(f, 'del_580set2')
    sig_del580set2 = B.get_data(f, 'sig_del580set2')
    R580set2 = B.get_data(f, 'R580set2')
    
    del_750set1 = B.get_data(f, 'del_750set1')
    sig_del750set1 = B.get_data(f, 'sig_del750set1')
    R750set1 = B.get_data(f, 'R750set1')

    del_750set2 = B.get_data(f, 'del_750set2')
    sig_del750set2 = B.get_data(f, 'sig_del750set2')
    R750set2 = B.get_data(f, 'R750set2')
    
    del_750set3 = B.get_data(f, 'del_750set3')
    sig_del750set3 = B.get_data(f, 'sig_del750set3')
    R750set3 = B.get_data(f, 'R750set3')
    

    #Get the Cross Sections with Nominal Cuts
    dataXsec_80_nom           = B.get_data(f, 'dataXsec_80_nom')              
    dataXsec_err_80_nom       = B.get_data(f, 'dataXsec_err_80_nom')  
    dataXsec_580set1_nom      = B.get_data(f, 'dataXsec_580set1_nom')              
    dataXsec_err_580set1_nom  = B.get_data(f, 'dataXsec_err_580set1_nom') 
    dataXsec_580set2_nom      = B.get_data(f, 'dataXsec_580set2_nom')              
    dataXsec_err_580set2_nom  = B.get_data(f, 'dataXsec_err_580set2_nom') 
    dataXsec_750set1_nom      = B.get_data(f, 'dataXsec_750set1_nom')              
    dataXsec_err_750set1_nom  = B.get_data(f, 'dataXsec_err_750set1_nom') 
    dataXsec_750set2_nom      = B.get_data(f, 'dataXsec_750set2_nom')              
    dataXsec_err_750set2_nom  = B.get_data(f, 'dataXsec_err_750set2_nom') 
    dataXsec_750set3_nom      = B.get_data(f, 'dataXsec_750set3_nom')              
    dataXsec_err_750set3_nom  = B.get_data(f, 'dataXsec_err_750set3_nom') 

    #Get the Cross Sections with new Cuts
    dataXsec_80           = B.get_data(f, 'dataXsec_80')              
    dataXsec_err_80       = B.get_data(f, 'dataXsec_err_80')  
    dataXsec_580set1      = B.get_data(f, 'dataXsec_580set1')              
    dataXsec_err_580set1  = B.get_data(f, 'dataXsec_err_580set1') 
    dataXsec_580set2      = B.get_data(f, 'dataXsec_580set2')              
    dataXsec_err_580set2  = B.get_data(f, 'dataXsec_err_580set2') 
    dataXsec_750set1      = B.get_data(f, 'dataXsec_750set1')              
    dataXsec_err_750set1  = B.get_data(f, 'dataXsec_err_750set1') 
    dataXsec_750set2      = B.get_data(f, 'dataXsec_750set2')              
    dataXsec_err_750set2  = B.get_data(f, 'dataXsec_err_750set2') 
    dataXsec_750set3      = B.get_data(f, 'dataXsec_750set3')              
    dataXsec_err_750set3  = B.get_data(f, 'dataXsec_err_750set3') 


    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print(ithnq)
        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        B.plot_exp(pm[thnq==ithnq], R80[thnq==ithnq], color='black', marker='s', label='80 MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set1[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2[thnq==ithnq], color='green', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3[thnq==ithnq], color='cyan', marker='<', label='750 (set3) MeV Systematics' )


        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.ylim(-10, 10)

        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')


        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        
        B.pl.legend()
            
        B.pl.savefig(dir_name+'/sys_thnq%i.pdf'%(ithnq))

        #-------------Plot the Overlay of Nominal and New Cuts Cross Sections to Observe any differences------

        #80 MeV
        fig2 = B.pl.figure(i+1)
        B.pl.clf()
        #Take the Xsec Ratio
        #R = dataXsec_80_nom[thnq==ithnq] / dataXsec_80[thnq==ithnq]
        #R_err = np.sqrt(dataXsec_err_80_nom[thnq==ithnq]**2/dataXsec_80[thnq==ithnq]**2 + dataXsec_80_nom[thnq==ithnq]**2 * dataXsec_err_80[thnq==ithnq]**2/ dataXsec_80[thnq==ithnq]**4)
        #B.plot_exp(pm[thnq==ithnq], R, R_err, color='black',  marker='s', label='80 (Nominal)')
        
        B.plot_exp(pm[thnq==ithnq], dataXsec_80_nom[thnq==ithnq], dataXsec_err_80_nom[thnq==ithnq], color='black',  marker='s', label='80 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_80[thnq==ithnq], dataXsec_err_80[thnq==ithnq], color='red',  marker='o', label='80 (Em Cut:[-20,60] MeV)')

        B.pl.yscale('log')
        #B.pl.xlim(0, 0.4)
        #B.pl.ylim(0.8, 1.2)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        #B.pl.ylabel(r'Data Cross Section Ratio')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        #B.pl.title(r'Cross Section Ratio$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec80_thnq%i.pdf'%(ithnq))


        #580 MeV (set1)
        fig3 = B.pl.figure(i+2)
        B.pl.clf()
        B.plot_exp(pm[thnq==ithnq], dataXsec_580set1_nom[thnq==ithnq], dataXsec_err_580set1_nom[thnq==ithnq], color='black',  marker='s', label='580 set1 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_580set1[thnq==ithnq], dataXsec_err_580set1[thnq==ithnq], color='red',  marker='o', label='580 set1 (Em Cut:[-20,60] MeV)')
        B.pl.yscale('log')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec580set1_thnq%i.pdf'%(ithnq))


        #580 MeV (set2)
        fig4 = B.pl.figure(i+3)
        B.pl.clf()     
        B.plot_exp(pm[thnq==ithnq], dataXsec_580set2_nom[thnq==ithnq], dataXsec_err_580set2_nom[thnq==ithnq], color='black',  marker='s', label='580 set2 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_580set2[thnq==ithnq], dataXsec_err_580set2[thnq==ithnq], color='red',  marker='o', label='580 set2(Em Cut:[-20,60] MeV)')
        B.pl.yscale('log')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec580set2_thnq%i.pdf'%(ithnq))


        #750 MeV (set1)
        fig5 = B.pl.figure(i+4)
        B.pl.clf()
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set1_nom[thnq==ithnq], dataXsec_err_750set1_nom[thnq==ithnq], color='black',  marker='s', label='750 set1 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set1[thnq==ithnq], dataXsec_err_750set1[thnq==ithnq], color='red',  marker='o', label='750 set1 (Em Cut:[-20,60] MeV)')
        B.pl.yscale('log')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec750set1_thnq%i.pdf'%(ithnq))


        #750 MeV (set2)
        fig6 = B.pl.figure(i+5)
        B.pl.clf()
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set2_nom[thnq==ithnq], dataXsec_err_750set2_nom[thnq==ithnq], color='black',  marker='s', label='750 set2 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set2[thnq==ithnq], dataXsec_err_750set2[thnq==ithnq], color='red',  marker='o', label='750 set2(Em Cut:[-20,60] MeV)')
        B.pl.yscale('log')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec750set2_thnq%i.pdf'%(ithnq))

        #750 MeV (set3)
        fig7 = B.pl.figure(i+6)
        B.pl.clf()
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set3_nom[thnq==ithnq], dataXsec_err_750set3_nom[thnq==ithnq], color='black',  marker='s', label='750 set3 (Nominal)')
        B.plot_exp(pm[thnq==ithnq], dataXsec_750set3[thnq==ithnq], dataXsec_err_750set3[thnq==ithnq], color='red',  marker='o', label='750 set3(Em Cut:[-20,60] MeV)')
        B.pl.yscale('log')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Data Cross Section, $\frac{d^{5}\sigma}{d\omega d\Omega_{e} d\Omega_{p}} [\frac{\mu b}{sr^{2} MeV}]$')
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.legend()            
        B.pl.savefig(dir_name+'/dataXsec750set3_thnq%i.pdf'%(ithnq))
        

def main():
    print('Entering Main . . .')
   
    #User Input (what type of systematics? Enter two descriptions)
    #We want to compare the largest set with any other subsets variable cuts. (Ex. Em80MeV-Em40MeV, or Em80MeV-Em50MeV,  . . . )
    
    sys_ext1 = "Em80MeV"  #sys.argv[1], set to the largest set

    #---------Specific for User Input ONLY---------------
    #sys_ext2 = sys.argv[1] #"Em30MeV"   #second systematics name to compare with nominal 
    #stats_thrs = float(sys.argv[2])  #Statistical Uncertainty threshold (in fractional percent, e.x. 0.5 (would mean 50%)

    #Calculate systematics
    #calc_systematics(sys_ext1, sys_ext2, stats_thrs)

    #Plot Results
    #plot_data_sets(sys_ext1, sys_ext2)
    #-----------------------------------------------------

    #Calc. ALl 
    #calc_systematics(sys_ext1, "Em30MeV", 0.5)
    calc_systematics(sys_ext1, "Em40MeV", 0.5)
    #calc_systematics(sys_ext1, "Em45MeV", 0.5)
    #calc_systematics(sys_ext1, "Em50MeV", 0.5)
    #calc_systematics(sys_ext1, "Em60MeV", 0.5)
    




if __name__=="__main__":
    main()
