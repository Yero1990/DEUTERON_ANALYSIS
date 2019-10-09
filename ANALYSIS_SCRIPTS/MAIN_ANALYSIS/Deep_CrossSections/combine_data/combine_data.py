import LT.box as B
from LT.datafile import dfile
import numpy as np
import sys           
import os                                                      
from sys import argv  

#This Code:
# **NOTE** ONLY Reduced Cross Sections (Momentum Distributions) can be combined. Cross Sections CANNOT be combined, 
#          as they depend on spectrometer the kinematic setting, whereas in momentum distribution, that depenency has
#          been factored out by dividing by K*sig_cc1(GEp, GMp)
# ** combines (takes average) different data sets of a given kinematic setting and writes to file
# ** combines different kinematic settings


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
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ red_dataXsec_80[f,5]/  red_dataXsec_err_80[f,6]/   red_dataXsec_580set1[f,7]/  red_dataXsec_err_580set1[f,8]/   red_dataXsec_580set2[f,9]/  red_dataXsec_err_580set2[f,10]/   red_dataXsec_750set1[f,11]/  red_dataXsec_err_750set1[f,12]/ red_dataXsec_750set2[f,13]/  red_dataXsec_err_750set2[f,14]/  red_dataXsec_750set3[f,15]/  red_dataXsec_err_750set3[f,16]/    red_dataXsec_580avg[f,17]/   red_dataXsec_580avg_err[f,18]/   red_dataXsec_750avg[f,19]/   red_dataXsec_750avg_err[f,20]/  red_dataXsec_avg[f,21]/   red_dataXsec_avg_err[f,22]/  red_pwiaXsec_80[f,23]/  red_pwiaXsec_580set1[f,24]/ red_pwiaXsec_580set2[f,25]/ red_pwiaXsec_750set1[f,26]/ red_pwiaXsec_750set2[f,27]/ red_pwiaXsec_750set3[f,28]/  red_pwiaXsec_580avg[f,29]/  red_pwiaXsec_750avg[f,30]/ red_fsiXsec_80[f,31]/  red_fsiXsec_580set1[f,32]/ red_fsiXsec_580set2[f,33]/ red_fsiXsec_750set1[f,34]/ red_fsiXsec_750set2[f,35]/ red_fsiXsec_750set3[f,36]/  red_fsiXsec_580avg[f,37]/  red_fsiXsec_750avg[f,38]/  red_pwiaXsec_avg[f,39]/ red_fsiXsec_avg[f,40]/
"""
fout.write(header)


#Open File Containing Reduced Cross Sections
fname80 = '../bin_centering_corrections/%s/pm80_laget_bc_corr.txt'%(sys_ext)
fname580_set1 = '../bin_centering_corrections/%s/pm580_laget_bc_corr_set1.txt'%(sys_ext)
fname580_set2 = '../bin_centering_corrections/%s/pm580_laget_bc_corr_set2.txt'%(sys_ext)
fname750_set1 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set1.txt'%(sys_ext)
fname750_set2 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set2.txt'%(sys_ext)
fname750_set3 = '../bin_centering_corrections/%s/pm750_laget_bc_corr_set3.txt'%(sys_ext)


#Get bin information from each file
f1 = B.get_file(fname80)
i_b = B.get_data(f1, 'i_b')
i_x = B.get_data(f1, 'i_x')
i_y = B.get_data(f1, 'i_y')
xb = B.get_data(f1, 'xb')
yb = B.get_data(f1, 'yb')

#80 MeV
red_dataXsec_1 = B.get_data(f1, 'red_dataXsec')              
red_dataXsec_err_1 = B.get_data(f1, 'red_dataXsec_err')  
red_pwiaXsec_1 = B.get_data(f1, 'red_pwiaXsec')          
red_fsiXsec_1 = B.get_data(f1, 'red_fsiXsec')            

#580 MeV (set 1)
f2 = B.get_file(fname580_set1)
red_dataXsec_2 = B.get_data(f2, 'red_dataXsec')            
red_dataXsec_err_2 = B.get_data(f2, 'red_dataXsec_err')    
red_pwiaXsec_2 = B.get_data(f2, 'red_pwiaXsec')            
red_fsiXsec_2 = B.get_data(f2, 'red_fsiXsec')              

#580 MeV (set 2)
f3 = B.get_file(fname580_set2)
red_dataXsec_3 = B.get_data(f3, 'red_dataXsec')             
red_dataXsec_err_3 = B.get_data(f3, 'red_dataXsec_err')     
red_pwiaXsec_3 = B.get_data(f3, 'red_pwiaXsec')             
red_fsiXsec_3 = B.get_data(f3, 'red_fsiXsec')               

#750 MeV (set 1)
f4 = B.get_file(fname750_set1)
red_dataXsec_4 = B.get_data(f4, 'red_dataXsec')              
red_dataXsec_err_4 = B.get_data(f4, 'red_dataXsec_err')      
red_pwiaXsec_4 = B.get_data(f4, 'red_pwiaXsec')              
red_fsiXsec_4 = B.get_data(f4, 'red_fsiXsec')                

#750 MeV (set 2)
f5 = B.get_file(fname750_set2)
red_dataXsec_5 = B.get_data(f5, 'red_dataXsec')              
red_dataXsec_err_5 = B.get_data(f5, 'red_dataXsec_err')      
red_pwiaXsec_5 = B.get_data(f5, 'red_pwiaXsec')              
red_fsiXsec_5 = B.get_data(f5, 'red_fsiXsec')                

#750 MeV (set 3)
f6 = B.get_file(fname750_set3)
red_dataXsec_6 = B.get_data(f6, 'red_dataXsec')              
red_dataXsec_err_6 = B.get_data(f6, 'red_dataXsec_err')      
red_pwiaXsec_6 = B.get_data(f6, 'red_pwiaXsec')              
red_fsiXsec_6 = B.get_data(f6, 'red_fsiXsec')                


#Loop over all 2d bins
for ib in range(len(i_b)):
    
    #----------Calculate the Data Reduced Xsec Weighted Average for a given (Pm, th_nq) bin of a given kin. set------------
     
    #Define the weight as 1/sig_i**2, and the measured quantities, xi
    #580 MeV (sets 1, 2)
    w2 = 1. / red_dataXsec_err_2[ib]**2; x2 = red_dataXsec_2[ib]
    w3 = 1. / red_dataXsec_err_3[ib]**2; x3 = red_dataXsec_3[ib]

    #Check if data Xsec exists (if not, set weight to zero so it does not count in the weighted average)
    if(x2==-1.):
        x2=0.; w2=0.
    if(x3==-1.):
        x3=0.; w3=0.   

    if(w2==0 and w3==0):
        red_dataXsec_avg_580 = -1.
        red_dataXsec_avg_err_580 = -1.

    else:
        red_dataXsec_avg_580 = (x2*w2 + x3*w3) / (w2 + w3)
        red_dataXsec_avg_err_580 = 1 / np.sqrt(w2 + w3)

    #Define the weight as 1/sig_i**2, and the measured quantities, xi
    #750 MeV (sets 1, 2, 3)
    w4 = 1. / red_dataXsec_err_4[ib]**2; x4 = red_dataXsec_4[ib]
    w5 = 1. / red_dataXsec_err_5[ib]**2; x5 = red_dataXsec_5[ib]
    w6 = 1. / red_dataXsec_err_6[ib]**2; x6 = red_dataXsec_6[ib]

    #Check if data Xsec exists (if not, set weight to zero so it does not count in the weighted average)
    if(x4==-1.):
        x4=0.; w4=0.
    if(x5==-1.):
        x5=0.; w5=0.   
    if(x6==-1.):
        x6=0.; w6=0.

    if(w4==0 and w5==0 and w6==0):
        red_dataXsec_avg_750 = -1.
        red_dataXsec_avg_err_750 = -1.

    else:
        red_dataXsec_avg_750 = (x4*w4 + x5*w5 + x6*w6) / (w4 + w5 + w6)
        red_dataXsec_avg_err_750 = 1 / np.sqrt(w4 + w5 + w6)
 

    #Calculate the Theoretical Reduced Xsec Arithmetic Mean for a given (Pm, th_nq) bin of a given kin. set
    
    #580 MeV (PWIA)
    c2p = 1.; x2p = red_pwiaXsec_2[ib]
    c3p = 1.; x3p = red_pwiaXsec_3[ib]

    if(x2p==-1.):
        x2p=0; c2p=0
    if(x3p==-1.):
        x3p=0; c3p=0

    if(x2p==0 and x3p==0):
        red_pwiaXsec_580avg = -1
    else:
        red_pwiaXsec_580avg = (x2p + x3p) / (c2p + c3p)

    #580 MeV (FSI)
    c2f = 1.; x2f = red_fsiXsec_2[ib]
    c3f = 1.; x3f = red_fsiXsec_3[ib]

    if(x2f==-1.):
        x2f=0; c2f=0
    if(x3f==-1.):
        x3f=0; c3f=0

    if(x2f==0 and x3f==0):
        red_fsiXsec_580avg = -1
    else:
        red_fsiXsec_580avg = (x2f + x3f) / (c2f + c3f)

    #750 MeV (PWIA)
    c4p = 1.; x4p = red_pwiaXsec_4[ib]
    c5p = 1.; x5p = red_pwiaXsec_5[ib]
    c6p = 1.; x6p = red_pwiaXsec_6[ib]

    if(x4p==-1.):
        x4p=0; c4p=0
    if(x5p==-1.):
        x5p=0; c5p=0
    if(x6p==-1.):
        x6p=0; c6p=0

    if(x4p==0 and x5p==0 and x6p==0):
        red_pwiaXsec_750avg = -1
    else:
        red_pwiaXsec_750avg = (x4p + x5p + x6p) / (c4p + c5p + c6p)


    #750 MeV (FSI)
    c4f = 1.; x4f = red_fsiXsec_4[ib]
    c5f = 1.; x5f = red_fsiXsec_5[ib]
    c6f = 1.; x6f = red_fsiXsec_6[ib]

    if(x4f==-1.):
        x4f=0; c4f=0
    if(x5f==-1.):
        x5f=0; c5f=0
    if(x6f==-1.):
        x6f=0; c6f=0

    if(x4f==0 and x5f==0 and x6f==0):
        red_fsiXsec_750avg = -1
    else:
        red_fsiXsec_750avg = (x4f + x5f + x6f) / (c4f + c5f + c6f)


    #--------------Determine Weighted Average of  Different Kinematics (DATA)----------------

    #Define the weights and red. Xsec values for the averaged data sets (determined above)
    w80  = 1. / red_dataXsec_err_1[ib]**2   ;  x80 = red_dataXsec_1[ib]
    w580 = 1. / red_dataXsec_avg_err_580**2 ;  x580 = red_dataXsec_avg_580
    w750 = 1. / red_dataXsec_avg_err_750**2 ;  x750 = red_dataXsec_avg_750

    if(x80==-1):
        x80 = 0;   w80  = 0
    if(x580==-1):
        x580 = 0;  w580 = 0
    if(x750==-1):
        x750 = 0;  w750 = 0

    if(x80==0 and x580==0 and x750==0):
        red_dataXsec_avg = -1
        red_dataXsec_avg_err = -1
    else:
        red_dataXsec_avg = (x80*w80 + x580*w580 + x750*w750) / (w80 + w580 + w750)
        red_dataXsec_avg_err = 1. / np.sqrt(w80 + w580 + w750)

    #---------------Determine Arithmetic Average of  Different Kinematics ( THEORY)---------------
    
    #PWIA
    c80p  = 1.   ;  x80p = red_pwiaXsec_1[ib]
    c580p = 1.   ;  x580p = red_pwiaXsec_580avg
    c750p = 1.   ;  x750p = red_pwiaXsec_750avg

    if(x80p==-1):
        c80p = 0  ; x80p  = 0
    if(x580p==-1):
        c580p = 0 ; x580p = 0
    if(x750p==-1):
        c750p = 0 ; x750p = 0

    if(x80p==0 and x580p==0 and x750p==0):
        red_pwiaXsec_avg = -1
    else:
        red_pwiaXsec_avg = ( x80p + x580p + x750p) / (c80p + c580p + c750p)

    #FSI
    c80f  = 1.   ;  x80f = red_fsiXsec_1[ib]
    c580f = 1.   ;  x580f = red_fsiXsec_580avg
    c750f = 1.   ;  x750f = red_fsiXsec_750avg

    if(x80f==-1):
        c80f = 0  ; x80f  = 0
    if(x580f==-1):
        c580f = 0 ; x580f = 0
    if(x750f==-1):
        c750f = 0 ; x750f = 0

    if(x80f==0 and x580f==0 and x750f==0):
        red_fsiXsec_avg = -1
    else:
        red_fsiXsec_avg = ( x80f + x580f + x750f) / (c80f + c580f + c750f)

    
    l="%i %i %i %f  %f %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e %.12e\n" % (i_b[ib], i_x[ib], i_y[ib], xb[ib], yb[ib],red_dataXsec_1[ib], red_dataXsec_err_1[ib], red_dataXsec_2[ib], red_dataXsec_err_2[ib], red_dataXsec_3[ib], red_dataXsec_err_3[ib], red_dataXsec_4[ib], red_dataXsec_err_4[ib], red_dataXsec_5[ib], red_dataXsec_err_5[ib], red_dataXsec_6[ib], red_dataXsec_err_6[ib], red_dataXsec_avg_580, red_dataXsec_avg_err_580, red_dataXsec_avg_750, red_dataXsec_avg_err_750, red_dataXsec_avg, red_dataXsec_avg_err, red_pwiaXsec_1[ib], red_pwiaXsec_2[ib], red_pwiaXsec_3[ib], red_pwiaXsec_4[ib], red_pwiaXsec_5[ib], red_pwiaXsec_6[ib], red_pwiaXsec_580avg, red_pwiaXsec_750avg, red_fsiXsec_1[ib], red_fsiXsec_2[ib], red_fsiXsec_3[ib], red_fsiXsec_4[ib], red_fsiXsec_5[ib], red_fsiXsec_6[ib], red_fsiXsec_580avg, red_fsiXsec_750avg, red_pwiaXsec_avg, red_fsiXsec_avg )
    fout.write(l)
fout.close()
