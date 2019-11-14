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

def calc_systematics(study='', stats_thrs=0.):

    print('Calculating Systematics for %s' % (study))

    #study: 'radiative' or 'binCentering'

    #check if directory to store systematics datafiles exists, else creates it.
    study_dir = "../datafiles/"+study+"_study"
    if not os.path.exists(study_dir):
        os.makedirs(study_dir)
        
    #Open .txt file to write systematics
    output_file='%s/systematics%s.txt'%(study_dir, study)
    fout = open(output_file, 'w') 

    #------------------------------------------------------------                   
    # header information for the output file 

    #radiative systematics
    header_rad = """        
    #This file contains the del = XSec_1 - Xsec2 (diff. between cross sections with PWIA or FSI),  sig_del: sqrt(sigXsec1**2 - sigXsec2**2), R = del / sig_del
    #If R > 4, there is a significant difference which must be taken into account in the systemtaics
    #In this file, there are also the cross sections with FSI/PWIA models for radiative corrections ONLY for comparison plots
    #xb = th_nq [central bin value]                                                                                                    
    #yb = pm [central bin value]                                                                       
    # current header line:  
    #!i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  del80[f,5]/   sig_del80[f,6]/    R80[f,7]/    del_580set1[f,8]/   sig_del580set1[f,9]/    R580set1[f,10]/   del_580set2[f,11]/   sig_del580set2[f,12]/    R580set2[f,13]/   del_750set1[f,14]/   sig_del750set1[f,15]/    R750set1[f,16]/  del_750set2[f,17]/   sig_del750set2[f,18]/    R750set2[f,19]/  del_750set3[f,20]/   sig_del750set3[f,21]/    R750set3[f,22]/  dataXsec_80_pwiaRC[f,23]/   dataXsec_err_80_pwiaRC[f,24]/   dataXsec_80_fsiRC[f,25]/   dataXsec_err_80_fsiRC[f,26]/  dataXsec_580set1_pwiaRC[f,27]/   dataXsec_err_580set1_pwiaRC[f,28]/   dataXsec_580set1_fsiRC[f,29]/   dataXsec_err_580set1_fsiRC[f,30]/  dataXsec_580set2_pwiaRC[f,31]/   dataXsec_err_580set2_pwiaRC[f,32]/   dataXsec_580set2_fsiRC[f,33]/   dataXsec_err_580set2_fsiRC[f,34]/ dataXsec_750set1_pwiaRC[f,35]/   dataXsec_err_750set1_pwiaRC[f,36]/   dataXsec_750set1_fsiRC[f,37]/   dataXsec_err_750set1_fsiRC[f,38]/  dataXsec_750set2_pwiaRC[f,39]/   dataXsec_err_750set2_pwiaRC[f,40]/   dataXsec_750set2_fsiRC[f,41]/   dataXsec_err_750set2_fsiRC[f,42]/  dataXsec_750set3_pwiaRC[f,43]/   dataXsec_err_750set3_pwiaRC[f,44]/   dataXsec_750set3_fsiRC[f,45]/   dataXsec_err_750set3_fsiRC[f,46]/ 
    """
    #bin-centering systematics
    header_bc = """        
    #This file contains the del = XSec_1 - Xsec2 (diff. between cross sections with PWIA or FSI),  sig_del: sqrt(sigXsec1**2 - sigXsec2**2), R = del / sig_del
    #If R > 4, there is a significant difference which must be taken into account in the systemtaics
    #In this file, there are also the cross sections with FSI/PWIA models for radiative corrections using FSI + Bin-Centering Corrections using (PWIA or FSI) for comparison plots
    #xb = th_nq [central bin value]                                                                                                    
    #yb = pm [central bin value]                                                                       
    # current header line:  
    #!i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/  del80[f,5]/   sig_del80[f,6]/    R80[f,7]/    del_580set1[f,8]/   sig_del580set1[f,9]/    R580set1[f,10]/   del_580set2[f,11]/   sig_del580set2[f,12]/    R580set2[f,13]/   del_750set1[f,14]/   sig_del750set1[f,15]/    R750set1[f,16]/  del_750set2[f,17]/   sig_del750set2[f,18]/    R750set2[f,19]/  del_750set3[f,20]/   sig_del750set3[f,21]/    R750set3[f,22]/  dataXsec_80_pwiaBC[f,23]/   dataXsec_err_80_pwiaBC[f,24]/   dataXsec_80_fsiBC[f,25]/   dataXsec_err_80_fsiBC[f,26]/  dataXsec_580set1_pwiaBC[f,27]/   dataXsec_err_580set1_pwiaBC[f,28]/   dataXsec_580set1_fsiBC[f,29]/   dataXsec_err_580set1_fsiBC[f,30]/  dataXsec_580set2_pwiaBC[f,31]/   dataXsec_err_580set2_pwiaBC[f,32]/   dataXsec_580set2_fsiBC[f,33]/   dataXsec_err_580set2_fsiBC[f,34]/ dataXsec_750set1_pwiaBC[f,35]/   dataXsec_err_750set1_pwiaBC[f,36]/   dataXsec_750set1_fsiBC[f,37]/   dataXsec_err_750set1_fsiBC[f,38]/  dataXsec_750set2_pwiaBC[f,39]/   dataXsec_err_750set2_pwiaBC[f,40]/   dataXsec_750set2_fsiBC[f,41]/   dataXsec_err_750set2_fsiBC[f,42]/  dataXsec_750set3_pwiaBC[f,43]/   dataXsec_err_750set3_pwiaBC[f,44]/   dataXsec_750set3_fsiBC[f,45]/   dataXsec_err_750set3_fsiBC[f,46]/ 
    """

    if (study=='radiative'):
        fout.write(header_rad)
    elif (study=='binCentering'):
        fout.write(header_bc)


    #Open File Containing Cross Sections with radiative corrections / radiative + bin-centering corrections
    fname80       = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm80_laget_bc_corr.txt'
    fname580_set1 = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm580_laget_bc_corr_set1.txt'
    fname580_set2 = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm580_laget_bc_corr_set2.txt'
    fname750_set1 = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm750_laget_bc_corr_set1.txt'
    fname750_set2 = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm750_laget_bc_corr_set2.txt'
    fname750_set3 = '../../Deep_CrossSections/bin_centering_corrections/Em40MeV/pm750_laget_bc_corr_set3.txt'
    
    #Get Data Files
    f80 = B.get_file(fname80)
    f580set1 = B.get_file(fname580_set1)
    f580set2 = B.get_file(fname580_set2)
    f750set1 = B.get_file(fname750_set1)
    f750set2 = B.get_file(fname750_set2)
    f750set3 = B.get_file(fname750_set3)

    #Get bin information 
    i_b = B.get_data(f80, 'i_b')
    i_x = B.get_data(f80, 'i_x')
    i_y = B.get_data(f80, 'i_y')
    xb  = B.get_data(f80, 'xb')
    yb  = B.get_data(f80, 'yb')
    
    
    #--------Get Experimental Cross Sections (Already Radiative/Bin-Center corrected)----
    
    #===Pm: 80 MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_80_pwiaRC     = B.get_data(f80, 'pwiaRC_dataXsec')              
    dataXsec_err_80_pwiaRC = B.get_data(f80, 'pwiaRC_dataXsec_err')              
    dataXsec_80_fsiRC      = B.get_data(f80, 'fsiRC_dataXsec')              
    dataXsec_err_80_fsiRC  = B.get_data(f80, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_80_pwiaBC     = B.get_data(f80, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_80_pwiaBC = B.get_data(f80, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_80_fsiBC      = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_80_fsiBC  = B.get_data(f80, 'fsiRC_dataXsec_fsibc_corr_err') 
    
    #===Pm: 580 (set1) MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_580set1_pwiaRC     = B.get_data(f580set1, 'pwiaRC_dataXsec')              
    dataXsec_err_580set1_pwiaRC = B.get_data(f580set1, 'pwiaRC_dataXsec_err')              
    dataXsec_580set1_fsiRC      = B.get_data(f580set1, 'fsiRC_dataXsec')              
    dataXsec_err_580set1_fsiRC  = B.get_data(f580set1, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_580set1_pwiaBC     = B.get_data(f580set1, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_580set1_pwiaBC = B.get_data(f580set1, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_580set1_fsiBC      = B.get_data(f580set1, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_580set1_fsiBC  = B.get_data(f580set1, 'fsiRC_dataXsec_fsibc_corr_err') 
    
    #===Pm: 580 (set2) MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_580set2_pwiaRC     = B.get_data(f580set2, 'pwiaRC_dataXsec')              
    dataXsec_err_580set2_pwiaRC = B.get_data(f580set2, 'pwiaRC_dataXsec_err')              
    dataXsec_580set2_fsiRC      = B.get_data(f580set2, 'fsiRC_dataXsec')              
    dataXsec_err_580set2_fsiRC  = B.get_data(f580set2, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_580set2_pwiaBC     = B.get_data(f580set2, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_580set2_pwiaBC = B.get_data(f580set2, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_580set2_fsiBC      = B.get_data(f580set2, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_580set2_fsiBC  = B.get_data(f580set2, 'fsiRC_dataXsec_fsibc_corr_err') 

    #===Pm: 750 (set1) MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_750set1_pwiaRC     = B.get_data(f750set1, 'pwiaRC_dataXsec')              
    dataXsec_err_750set1_pwiaRC = B.get_data(f750set1, 'pwiaRC_dataXsec_err')              
    dataXsec_750set1_fsiRC      = B.get_data(f750set1, 'fsiRC_dataXsec')              
    dataXsec_err_750set1_fsiRC  = B.get_data(f750set1, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_750set1_pwiaBC     = B.get_data(f750set1, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_750set1_pwiaBC = B.get_data(f750set1, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_750set1_fsiBC      = B.get_data(f750set1, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set1_fsiBC  = B.get_data(f750set1, 'fsiRC_dataXsec_fsibc_corr_err') 
 
    #===Pm: 750 (set2) MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_750set2_pwiaRC     = B.get_data(f750set2, 'pwiaRC_dataXsec')              
    dataXsec_err_750set2_pwiaRC = B.get_data(f750set2, 'pwiaRC_dataXsec_err')              
    dataXsec_750set2_fsiRC      = B.get_data(f750set2, 'fsiRC_dataXsec')              
    dataXsec_err_750set2_fsiRC  = B.get_data(f750set2, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_750set2_pwiaBC     = B.get_data(f750set2, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_750set2_pwiaBC = B.get_data(f750set2, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_750set2_fsiBC      = B.get_data(f750set2, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set2_fsiBC  = B.get_data(f750set2, 'fsiRC_dataXsec_fsibc_corr_err') 
    
    #===Pm: 750 (set3) MeV===
    #Radiative corrected ONLY (using PWIA or FSI)
    dataXsec_750set3_pwiaRC     = B.get_data(f750set3, 'pwiaRC_dataXsec')              
    dataXsec_err_750set3_pwiaRC = B.get_data(f750set3, 'pwiaRC_dataXsec_err')              
    dataXsec_750set3_fsiRC      = B.get_data(f750set3, 'fsiRC_dataXsec')              
    dataXsec_err_750set3_fsiRC  = B.get_data(f750set3, 'fsiRC_dataXsec_err')   
    #Radiative corrected (using FSI) and bin-center corrected using (PWIA or FSI)
    dataXsec_750set3_pwiaBC     = B.get_data(f750set3, 'fsiRC_dataXsec_pwiabc_corr')              
    dataXsec_err_750set3_pwiaBC = B.get_data(f750set3, 'fsiRC_dataXsec_pwiabc_corr_err')              
    dataXsec_750set3_fsiBC      = B.get_data(f750set3, 'fsiRC_dataXsec_fsibc_corr')              
    dataXsec_err_750set3_fsiBC  = B.get_data(f750set3, 'fsiRC_dataXsec_fsibc_corr_err') 


    #Mask Xsec and Ratio Arrays given a statistical uncertainty > threshold

    #Radiative Corrected (PWIA MODEL)
    dataXsec_80_pwiaRC_masked = np.ma.array(dataXsec_80_pwiaRC, mask=(dataXsec_err_80_pwiaRC>stats_thrs*dataXsec_80_pwiaRC))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_pwiaRC_masked = np.ma.filled(dataXsec_80_pwiaRC_masked.astype(float), -1.)   #assign the mask a value of "-1"
   
    dataXsec_580set1_pwiaRC_masked = np.ma.array(dataXsec_580set1_pwiaRC, mask=(dataXsec_err_580set1_pwiaRC>stats_thrs*dataXsec_580set1_pwiaRC))  
    dataXsec_580set1_pwiaRC_masked = np.ma.filled(dataXsec_580set1_pwiaRC_masked.astype(float), -1.)

    dataXsec_580set2_pwiaRC_masked = np.ma.array(dataXsec_580set2_pwiaRC, mask=(dataXsec_err_580set2_pwiaRC>stats_thrs*dataXsec_580set2_pwiaRC))  
    dataXsec_580set2_pwiaRC_masked = np.ma.filled(dataXsec_580set2_pwiaRC_masked.astype(float), -1.)

    dataXsec_750set1_pwiaRC_masked = np.ma.array(dataXsec_750set1_pwiaRC, mask=(dataXsec_err_750set1_pwiaRC>stats_thrs*dataXsec_750set1_pwiaRC))  
    dataXsec_750set1_pwiaRC_masked = np.ma.filled(dataXsec_750set1_pwiaRC_masked.astype(float), -1.)

    dataXsec_750set2_pwiaRC_masked = np.ma.array(dataXsec_750set2_pwiaRC, mask=(dataXsec_err_750set2_pwiaRC>stats_thrs*dataXsec_750set2_pwiaRC))  
    dataXsec_750set2_pwiaRC_masked = np.ma.filled(dataXsec_750set2_pwiaRC_masked.astype(float), -1.)

    dataXsec_750set3_pwiaRC_masked = np.ma.array(dataXsec_750set3_pwiaRC, mask=(dataXsec_err_750set3_pwiaRC>stats_thrs*dataXsec_750set3_pwiaRC))  
    dataXsec_750set3_pwiaRC_masked = np.ma.filled(dataXsec_750set3_pwiaRC_masked.astype(float), -1.)

    #Bin-Center Corrected (PWIA MODEL)
    dataXsec_80_pwiaBC_masked = np.ma.array(dataXsec_80_pwiaBC, mask=(dataXsec_err_80_pwiaBC>stats_thrs*dataXsec_80_pwiaBC))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_pwiaBC_masked = np.ma.filled(dataXsec_80_pwiaBC_masked.astype(float), -1.)   #assign the mask a value of "-1"
   
    dataXsec_580set1_pwiaBC_masked = np.ma.array(dataXsec_580set1_pwiaBC, mask=(dataXsec_err_580set1_pwiaBC>stats_thrs*dataXsec_580set1_pwiaBC))  
    dataXsec_580set1_pwiaBC_masked = np.ma.filled(dataXsec_580set1_pwiaBC_masked.astype(float), -1.)

    dataXsec_580set2_pwiaBC_masked = np.ma.array(dataXsec_580set2_pwiaBC, mask=(dataXsec_err_580set2_pwiaBC>stats_thrs*dataXsec_580set2_pwiaBC))  
    dataXsec_580set2_pwiaBC_masked = np.ma.filled(dataXsec_580set2_pwiaBC_masked.astype(float), -1.)

    dataXsec_750set1_pwiaBC_masked = np.ma.array(dataXsec_750set1_pwiaBC, mask=(dataXsec_err_750set1_pwiaBC>stats_thrs*dataXsec_750set1_pwiaBC))  
    dataXsec_750set1_pwiaBC_masked = np.ma.filled(dataXsec_750set1_pwiaBC_masked.astype(float), -1.)

    dataXsec_750set2_pwiaBC_masked = np.ma.array(dataXsec_750set2_pwiaBC, mask=(dataXsec_err_750set2_pwiaBC>stats_thrs*dataXsec_750set2_pwiaBC))  
    dataXsec_750set2_pwiaBC_masked = np.ma.filled(dataXsec_750set2_pwiaBC_masked.astype(float), -1.)

    dataXsec_750set3_pwiaBC_masked = np.ma.array(dataXsec_750set3_pwiaBC, mask=(dataXsec_err_750set3_pwiaBC>stats_thrs*dataXsec_750set3_pwiaBC))  
    dataXsec_750set3_pwiaBC_masked = np.ma.filled(dataXsec_750set3_pwiaBC_masked.astype(float), -1.)


    #Radiative Corrected (FSI MODEL)
    dataXsec_80_fsiRC_masked = np.ma.array(dataXsec_80_fsiRC, mask=(dataXsec_err_80_fsiRC>stats_thrs*dataXsec_80_fsiRC))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_fsiRC_masked = np.ma.filled(dataXsec_80_fsiRC_masked.astype(float), -1.)
   
    dataXsec_580set1_fsiRC_masked = np.ma.array(dataXsec_580set1_fsiRC, mask=(dataXsec_err_580set1_fsiRC>stats_thrs*dataXsec_580set1_fsiRC))  
    dataXsec_580set1_fsiRC_masked = np.ma.filled(dataXsec_580set1_fsiRC_masked.astype(float), -1.)

    dataXsec_580set2_fsiRC_masked = np.ma.array(dataXsec_580set2_fsiRC, mask=(dataXsec_err_580set2_fsiRC>stats_thrs*dataXsec_580set2_fsiRC))  
    dataXsec_580set2_fsiRC_masked = np.ma.filled(dataXsec_580set2_fsiRC_masked.astype(float), -1.)

    dataXsec_750set1_fsiRC_masked = np.ma.array(dataXsec_750set1_fsiRC, mask=(dataXsec_err_750set1_fsiRC>stats_thrs*dataXsec_750set1_fsiRC))  
    dataXsec_750set1_fsiRC_masked = np.ma.filled(dataXsec_750set1_fsiRC_masked.astype(float), -1.)

    dataXsec_750set2_fsiRC_masked = np.ma.array(dataXsec_750set2_fsiRC, mask=(dataXsec_err_750set2_fsiRC>stats_thrs*dataXsec_750set2_fsiRC))  
    dataXsec_750set2_fsiRC_masked = np.ma.filled(dataXsec_750set2_fsiRC_masked.astype(float), -1.)

    dataXsec_750set3_fsiRC_masked = np.ma.array(dataXsec_750set3_fsiRC, mask=(dataXsec_err_750set3_fsiRC>stats_thrs*dataXsec_750set3_fsiRC))  
    dataXsec_750set3_fsiRC_masked = np.ma.filled(dataXsec_750set3_fsiRC_masked.astype(float), -1.)
    

    #Bin-Centered Corrected (FSI MODEL)
    dataXsec_80_fsiBC_masked = np.ma.array(dataXsec_80_fsiBC, mask=(dataXsec_err_80_fsiBC>stats_thrs*dataXsec_80_fsiBC))  #mask if (sig>stats_thrs %) of mean
    dataXsec_80_fsiBC_masked = np.ma.filled(dataXsec_80_fsiBC_masked.astype(float), -1.)
   
    dataXsec_580set1_fsiBC_masked = np.ma.array(dataXsec_580set1_fsiBC, mask=(dataXsec_err_580set1_fsiBC>stats_thrs*dataXsec_580set1_fsiBC))  
    dataXsec_580set1_fsiBC_masked = np.ma.filled(dataXsec_580set1_fsiBC_masked.astype(float), -1.)

    dataXsec_580set2_fsiBC_masked = np.ma.array(dataXsec_580set2_fsiBC, mask=(dataXsec_err_580set2_fsiBC>stats_thrs*dataXsec_580set2_fsiBC))  
    dataXsec_580set2_fsiBC_masked = np.ma.filled(dataXsec_580set2_fsiBC_masked.astype(float), -1.)

    dataXsec_750set1_fsiBC_masked = np.ma.array(dataXsec_750set1_fsiBC, mask=(dataXsec_err_750set1_fsiBC>stats_thrs*dataXsec_750set1_fsiBC))  
    dataXsec_750set1_fsiBC_masked = np.ma.filled(dataXsec_750set1_fsiBC_masked.astype(float), -1.)

    dataXsec_750set2_fsiBC_masked = np.ma.array(dataXsec_750set2_fsiBC, mask=(dataXsec_err_750set2_fsiBC>stats_thrs*dataXsec_750set2_fsiBC))  
    dataXsec_750set2_fsiBC_masked = np.ma.filled(dataXsec_750set2_fsiBC_masked.astype(float), -1.)

    dataXsec_750set3_fsiBC_masked = np.ma.array(dataXsec_750set3_fsiBC, mask=(dataXsec_err_750set3_fsiBC>stats_thrs*dataXsec_750set3_fsiBC))  
    dataXsec_750set3_fsiBC_masked = np.ma.filled(dataXsec_750set3_fsiBC_masked.astype(float), -1.)

    #Loop over all 2d bins
    for ib in range(len(i_b)):
    
        
        if (study=='radiative'):
        
            #=============RADIATIVE CORRECTIONS SYSTEMATICS (COMPARE PWIA TO FSI rad. Corr ratios on dataXsec)=================

            #--------------------80 MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_80_pwiaRC_masked[ib]>0 and dataXsec_80_fsiRC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del80 = dataXsec_80_fsiRC[ib] - dataXsec_80_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del80 = dataXsec_err_80_fsiRC[ib]**2 - dataXsec_err_80_pwiaRC[ib]**2      #difference of the variances
                sig_del80 = np.sqrt(abs(var_del80))                                           #standard deviation
                if(sig_del80>0):
                    R80 =  del80 / sig_del80                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
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
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_580set1_pwiaRC_masked[ib]>0 and dataXsec_580set1_fsiRC_masked[ib]>0):
   
                #Calculate differences between cross sections
                del580set1 = dataXsec_580set1_fsiRC[ib] - dataXsec_580set1_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del580set1 = dataXsec_err_580set1_fsiRC[ib]**2 - dataXsec_err_580set1_pwiaRC[ib]**2      #difference of the variances
                sig_del580set1 = np.sqrt(abs(var_del580set1))                                                #standard deviation
                if(sig_del580set1>0):
                    R580set1 =  del580set1 / sig_del580set1                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R580set1 = -1000.
            else:
                del580set1 = -1000.
                var_del580set1 = -1000.
                sig_del580set1 = -1000.
                R580set1 = -1000.  

            #--------------------580 (set2) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_580set2_pwiaRC_masked[ib]>0 and dataXsec_580set2_fsiRC_masked[ib]>0):
                    
                #Calculate differences between cross sections
                del580set2 = dataXsec_580set2_fsiRC[ib] - dataXsec_580set2_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del580set2 = dataXsec_err_580set2_fsiRC[ib]**2 - dataXsec_err_580set2_pwiaRC[ib]**2      #difference of the variances
                sig_del580set2 = np.sqrt(abs(var_del580set2))                                                #standard deviation
                if(sig_del580set2>0):
                    R580set2 =  del580set2 / sig_del580set2                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R580set2 = -1000.
            else:
                del580set2 = -1000.
                var_del580set2 = -1000.
                sig_del580set2 = -1000.
                R580set2 = -1000.  
                
            #--------------------750 (set1) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set1_pwiaRC_masked[ib]>0 and dataXsec_750set1_fsiRC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del750set1 = dataXsec_750set1_fsiRC[ib] - dataXsec_750set1_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set1 = dataXsec_err_750set1_fsiRC[ib]**2 - dataXsec_err_750set1_pwiaRC[ib]**2      #difference of the variances
                sig_del750set1 = np.sqrt(abs(var_del750set1))                                                #standard deviation
                if(sig_del750set1>0):
                    R750set1 =  del750set1 / sig_del750set1                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set1 = -1000.
            else:
                del750set1 = -1000.
                var_del750set1 = -1000.
                sig_del750set1 = -1000.
                R750set1 = -1000.  

            #--------------------750 (set2) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set2_pwiaRC_masked[ib]>0 and dataXsec_750set2_fsiRC_masked[ib]>0):

                #Calculate differences between cross sections
                del750set2 = dataXsec_750set2_fsiRC[ib] - dataXsec_750set2_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set2 = dataXsec_err_750set2_fsiRC[ib]**2 - dataXsec_err_750set2_pwiaRC[ib]**2      #difference of the variances
                sig_del750set2 = np.sqrt(abs(var_del750set2))                                                #standard deviation
                if(sig_del750set2>0):
                    R750set2 =  del750set2 / sig_del750set2                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set2 = -1000.
            else:
                del750set2 = -1000.
                var_del750set2 = -1000.
                sig_del750set2 = -1000.
                R750set2 = -1000. 

            #--------------------750 (set3) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set3_pwiaRC_masked[ib]>0 and dataXsec_750set3_fsiRC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del750set3 = dataXsec_750set3_fsiRC[ib] - dataXsec_750set3_pwiaRC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set3 = dataXsec_err_750set3_fsiRC[ib]**2 - dataXsec_err_750set3_pwiaRC[ib]**2      #difference of the variances
                sig_del750set3 = np.sqrt(abs(var_del750set3))                                                #standard deviation
                if(sig_del750set3>0):
                    R750set3 =  del750set3 / sig_del750set3                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set3 = -1000.
            else:
                del750set3 = -1000.
                var_del750set3 = -1000.
                sig_del750set3 = -1000.
                R750set3 = -1000.  
       
        
            fout.write("%i %i %i %f %f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e\n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], del80, sig_del80, R80, del580set1, sig_del580set1, R580set1, del580set2, sig_del580set2, R580set2, del750set1, sig_del750set1, R750set1,  del750set2, sig_del750set2, R750set2,  del750set3, sig_del750set3, R750set3, dataXsec_80_pwiaRC_masked[ib], dataXsec_err_80_pwiaRC[ib], dataXsec_80_fsiRC_masked[ib], dataXsec_err_80_fsiRC[ib], dataXsec_580set1_pwiaRC_masked[ib], dataXsec_err_580set1_pwiaRC[ib], dataXsec_580set1_fsiRC_masked[ib], dataXsec_err_580set1_fsiRC[ib], dataXsec_580set2_pwiaRC_masked[ib], dataXsec_err_580set2_pwiaRC[ib], dataXsec_580set2_fsiRC_masked[ib], dataXsec_err_580set2_fsiRC[ib],  dataXsec_750set1_pwiaRC_masked[ib], dataXsec_err_750set1_pwiaRC[ib], dataXsec_750set1_fsiRC_masked[ib], dataXsec_err_750set1_fsiRC[ib], dataXsec_750set2_pwiaRC_masked[ib], dataXsec_err_750set2_pwiaRC[ib], dataXsec_750set2_fsiRC_masked[ib], dataXsec_err_750set2_fsiRC[ib], dataXsec_750set3_pwiaRC_masked[ib], dataXsec_err_750set3_pwiaRC[ib], dataXsec_750set3_fsiRC_masked[ib], dataXsec_err_750set3_fsiRC[ib]))
        

        if (study=='binCentering'):
        
            #=============Bin Centering CORRECTIONS SYSTEMATICS (COMPARE PWIA TO FSI rad. Corr ratios on dataXsec)=================

            #--------------------80 MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_80_pwiaBC_masked[ib]>0 and dataXsec_80_fsiBC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del80 = dataXsec_80_fsiBC[ib] - dataXsec_80_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del80 = dataXsec_err_80_fsiBC[ib]**2 - dataXsec_err_80_pwiaBC[ib]**2      #difference of the variances
                sig_del80 = np.sqrt(abs(var_del80))                                           #standard deviation
                if(sig_del80>0):
                    R80 =  del80 / sig_del80                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
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
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_580set1_pwiaBC_masked[ib]>0 and dataXsec_580set1_fsiBC_masked[ib]>0):
   
                #Calculate differences between cross sections
                del580set1 = dataXsec_580set1_fsiBC[ib] - dataXsec_580set1_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del580set1 = dataXsec_err_580set1_fsiBC[ib]**2 - dataXsec_err_580set1_pwiaBC[ib]**2      #difference of the variances
                sig_del580set1 = np.sqrt(abs(var_del580set1))                                                #standard deviation
                if(sig_del580set1>0):
                    R580set1 =  del580set1 / sig_del580set1                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R580set1 = -1000.
            else:
                del580set1 = -1000.
                var_del580set1 = -1000.
                sig_del580set1 = -1000.
                R580set1 = -1000.  

            #--------------------580 (set2) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_580set2_pwiaBC_masked[ib]>0 and dataXsec_580set2_fsiBC_masked[ib]>0):
                    
                #Calculate differences between cross sections
                del580set2 = dataXsec_580set2_fsiBC[ib] - dataXsec_580set2_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del580set2 = dataXsec_err_580set2_fsiBC[ib]**2 - dataXsec_err_580set2_pwiaBC[ib]**2      #difference of the variances
                sig_del580set2 = np.sqrt(abs(var_del580set2))                                                #standard deviation
                if(sig_del580set2>0):
                    R580set2 =  del580set2 / sig_del580set2                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R580set2 = -1000.
            else:
                del580set2 = -1000.
                var_del580set2 = -1000.
                sig_del580set2 = -1000.
                R580set2 = -1000.  
                
            #--------------------750 (set1) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set1_pwiaBC_masked[ib]>0 and dataXsec_750set1_fsiBC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del750set1 = dataXsec_750set1_fsiBC[ib] - dataXsec_750set1_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set1 = dataXsec_err_750set1_fsiBC[ib]**2 - dataXsec_err_750set1_pwiaBC[ib]**2      #difference of the variances
                sig_del750set1 = np.sqrt(abs(var_del750set1))                                                #standard deviation
                if(sig_del750set1>0):
                    R750set1 =  del750set1 / sig_del750set1                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set1 = -1000.
            else:
                del750set1 = -1000.
                var_del750set1 = -1000.
                sig_del750set1 = -1000.
                R750set1 = -1000.  

            #--------------------750 (set2) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set2_pwiaBC_masked[ib]>0 and dataXsec_750set2_fsiBC_masked[ib]>0):

                #Calculate differences between cross sections
                del750set2 = dataXsec_750set2_fsiBC[ib] - dataXsec_750set2_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set2 = dataXsec_err_750set2_fsiBC[ib]**2 - dataXsec_err_750set2_pwiaBC[ib]**2      #difference of the variances
                sig_del750set2 = np.sqrt(abs(var_del750set2))                                                #standard deviation
                if(sig_del750set2>0):
                    R750set2 =  del750set2 / sig_del750set2                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set2 = -1000.
            else:
                del750set2 = -1000.
                var_del750set2 = -1000.
                sig_del750set2 = -1000.
                R750set2 = -1000. 

            #--------------------750 (set3) MeV Setting------------------------
            #Check if bin has Xsec for both, (the total set[nom] and subset files)
            if(dataXsec_750set3_pwiaBC_masked[ib]>0 and dataXsec_750set3_fsiBC_masked[ib]>0):
                
                #Calculate differences between cross sections
                del750set3 = dataXsec_750set3_fsiBC[ib] - dataXsec_750set3_pwiaBC[ib]                        #difference between cross sections using diff. rad. corr models
                var_del750set3 = dataXsec_err_750set3_fsiBC[ib]**2 - dataXsec_err_750set3_pwiaBC[ib]**2      #difference of the variances
                sig_del750set3 = np.sqrt(abs(var_del750set3))                                                #standard deviation
                if(sig_del750set3>0):
                    R750set3 =  del750set3 / sig_del750set3                                                  #Ratio of diffences in Xsec to std. dev (if R>4, there is significant difference)
                else:
                    R750set3 = -1000.
            else:
                del750set3 = -1000.
                var_del750set3 = -1000.
                sig_del750set3 = -1000.
                R750set3 = -1000.  
       
        
            fout.write("%i %i %i %f %f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.6f %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e\n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib], del80, sig_del80, R80, del580set1, sig_del580set1, R580set1, del580set2, sig_del580set2, R580set2, del750set1, sig_del750set1, R750set1,  del750set2, sig_del750set2, R750set2,  del750set3, sig_del750set3, R750set3, dataXsec_80_pwiaBC_masked[ib], dataXsec_err_80_pwiaBC[ib], dataXsec_80_fsiBC_masked[ib], dataXsec_err_80_fsiBC[ib], dataXsec_580set1_pwiaBC_masked[ib], dataXsec_err_580set1_pwiaBC[ib], dataXsec_580set1_fsiBC_masked[ib], dataXsec_err_580set1_fsiBC[ib], dataXsec_580set2_pwiaBC_masked[ib], dataXsec_err_580set2_pwiaBC[ib], dataXsec_580set2_fsiBC_masked[ib], dataXsec_err_580set2_fsiBC[ib],  dataXsec_750set1_pwiaBC_masked[ib], dataXsec_err_750set1_pwiaBC[ib], dataXsec_750set1_fsiBC_masked[ib], dataXsec_err_750set1_fsiBC[ib], dataXsec_750set2_pwiaBC_masked[ib], dataXsec_err_750set2_pwiaBC[ib], dataXsec_750set2_fsiBC_masked[ib], dataXsec_err_750set2_fsiBC[ib], dataXsec_750set3_pwiaBC_masked[ib], dataXsec_err_750set3_pwiaBC[ib], dataXsec_750set3_fsiBC_masked[ib], dataXsec_err_750set3_fsiBC[ib]))
    print('Ended %s Systematics Analysis'%(study))


def main():
    print('Entering Main . . .')

    stats_thrs = 0.5  #Statistics Threshold (ONLY use data Xsec which are withih the statistical uncertainty of the mean Xsec)
    
    #Calculate systematics for rad. corr factor
    study= "radiative"     
    calc_systematics(study, stats_thrs)

    #Calculate systematics for bin-centering factor
    study= "binCentering"     
    calc_systematics(study, stats_thrs)

    #Plot Rad./BC Corr Roger Barlow Ratios
    pu.plotRCBC_syst('radiative', stats_thrs)
    pu.plotRCBC_syst('binCentering', stats_thrs)

if __name__=="__main__":
    main()
                       
 
