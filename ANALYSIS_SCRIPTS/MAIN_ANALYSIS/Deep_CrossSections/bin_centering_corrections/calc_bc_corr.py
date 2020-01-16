import LT.box as B
import numpy as np
import os
import sys                             
from sys import argv    
import getopt       
from LT.datafile import dfile

'''
Code that reads averaged Xsec(data and simc) and theory cross sections.  
The ratio (sig_theory_FSI(or PWIA)/sig_avg_FSI(or PWIA) is taken to determine the bin centering
correction factor, for either model, which enables one to do systematics on model dependency of bin-centering correction. 
The bin-centering factor is then applied to the FSI radiative corrected data ONLY. The bin-centering factor using FSI
is used to determine the momentum distributions
'''


#------------------------------------------------------------                   
# header information for the output file    
header = """                                            
# averaged kinematics results                                                                              
# averaged kinematic varibles used as input to calculate the averaged                                
# kinematics: Ei, omega, th_e, pf                                                                     
#
#---Useful Header Definitions---
#bc_fact_pwia(fsi):  bin-centering correction factor using PWIA or FSI model
#pwia(fsi)RC_dataXsec: average data Xsec radiative corrected using PWIA(FSI) model --> study rad. corr systematics  __
#fsiRC_dataXsec_pwiabc_corr: data Xsec radiative corrected using FSI model and Bin-Center corrected using PWIA model  | these can be used to study bin-centering corr. systematics from model dependency
#fsiRC_dataXsec_fsibc_corr: data Xsec radiative corrected using FSI model and Bin-Center corrected using FSI model  __|  
#red_dataXsec: reduced data Xsec radiative corrected and bin-center corrected using FSI model (K_sig_cc1 evaluated at FSI avg. kin is used)
#red_pwiaXsec: reduced theoretical Xsec (K_sig_cc1 evaluated at PWIA avg. kin is used)
#red_fsiXsec: reduced theoretical Xsec (K_sig_cc1 evaluated at FSI avg. kin is used)                    
#i_b = 2D bin id number
#xb = th_nq value at bin center                                                                                                   
#yb = pmiss value at bin center                                                                        
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ bc_fact_pwia[f,5]/  bc_fact_pwia_err[f,6]/  bc_fact_fsi[f,7]/  bc_fact_fsi_err[f,8]/  pwiaRC_dataXsec[f,9]/  pwiaRC_dataXsec_err[f,10]/  fsiRC_dataXsec[f,11]/   fsiRC_dataXsec_err[f,12]/    fsiRC_dataXsec_pwiabc_corr[f,13]/   fsiRC_dataXsec_pwiabc_corr_err[f,14]/  fsiRC_dataXsec_fsibc_corr[f,15]/  fsiRC_dataXsec_fsibc_corr_err[f,16]/   pwiaXsec_theory[f,17]/   fsiXsec_theory[f,18]/   red_dataXsec[f,19]/   red_dataXsec_err[f,20]/   red_pwiaXsec[f,21]/   red_fsiXsec[f,22]/
"""

#User Input
pm_set = int(sys.argv[1])                                                                            
data_set = int(sys.argv[2])
sys_ext = sys.argv[3]
                                                                                                            
print argv                                                                                   
         
#usage: /apps/python/2.7.12/bin/python.py calc_bc_corr.py 580  1  syst_ext          

#check if directory exists, else creates it.
if not os.path.exists(sys_ext):
    os.makedirs(sys_ext)

if pm_set == 80:     
    output_file = './%s/pm%i_laget_bc_corr.txt'%(sys_ext, pm_set)                                      #create output file to write avg kin                                   
    ft = B.get_file('../theory_Xsec/%s/pm%i_laget_theory.txt'%(sys_ext, pm_set))                       #Load Theory Xsec @ Avg. Kin.
    fa = B.get_file('../average_Xsec/%s/pm%i_laget.txt'%(sys_ext, pm_set))                             #Load Averaged Xsec
else:
    output_file = './%s/pm%i_laget_bc_corr_set%i.txt'%(sys_ext, pm_set, data_set)
    ft = B.get_file('../theory_Xsec/%s/pm%i_laget_theory_set%i.txt'%(sys_ext, pm_set, data_set))  #Load Theory Xsec @ Avg. Kin.
    fa = B.get_file('../average_Xsec/%s/pm%i_laget_set%i.txt'%(sys_ext, pm_set, data_set))        #Load Averaged Xsec


o = open(output_file,'w')  
o.write(header)


#Get Bin Information (Does no matter which file, as they have the same binning scheme)
ib_t = B.get_data(ft, 'i_b')             #2D Bin NUmber 
ix_t = B.get_data(ft, 'i_x')             #X-Bin Number (thnq bin number)
iy_t = B.get_data(ft, 'i_y')             #Y-Bin Number (Pm bin number)
thnq_t = B.get_data(ft, 'xb')            #bin-center value of theta_nq
pm_t = B.get_data(ft, 'yb')              #bin-center value of pmiss

#Get Theory Xsec 
pwiaXsec_theory = B.get_data(ft, 'pwiaXsec') 
fsiXsec_theory = B.get_data(ft, 'fsiXsec') 
pwia_Ksig_cc1 = B.get_data(ft, 'pwia_Ksig_cc1')    #deForest K*sig_cc1 factor for calculating the reduced cross section
fsi_Ksig_cc1 = B.get_data(ft, 'fsi_Ksig_cc1')


#Get Average Xsec  
pwiaXsec_avg = B.get_data(fa, 'pwiaXsec')                             #PWIA Model Average Xsec (from SIMC)                                                          
pwiaXsec_avg_err = B.get_data(fa, 'pwiaXsec_err')                                                                                

fsiXsec_avg = B.get_data(fa, 'fsiXsec')                               #FSI Model Average Xsec (from SIMC)
fsiXsec_avg_err = B.get_data(fa, 'fsiXsec_err') 

pwiaRC_dataXsec_avg = B.get_data(fa, 'pwiaRC_dataXsec')               #Radiative Corrected Data Xsec Using PWIA model
pwiaRC_dataXsec_avg_err = B.get_data(fa, 'pwiaRC_dataXsec_err')

fsiRC_dataXsec_avg = B.get_data(fa, 'fsiRC_dataXsec')                 #Radiative Corrected Data Xsec Using FSI model
fsiRC_dataXsec_avg_err = B.get_data(fa, 'fsiRC_dataXsec_err')


#The bin scheme is exactly the same for all data sets and settings. That is, the same number of 2D bins

#Loop over ith 2Dbin
for i, ib in enumerate(ib_t):

    #--------Set initial values to -1 unless the bin passes the condition-----------
    bc_factor_fsi      = -1                  #bin-centering corr. factor (using FSI model)
    bc_factor_pwia     = -1                  #bin-centering corr. factor (using PWIA model)
    bc_factor_fsi_err  = -1
    bc_factor_pwia_err = -1

    #--------Declare Bin Centering Corrected Data Xsec (that has already been Radiative Crrected by using FSI Model)----------
    fsiRC_dataXsec_fsibc_corr      = -1            #bin-centered corr. data Xsec (using FSI model for bc corr.)
    fsiRC_dataXsec_fsibc_corr_err  = -1

    fsiRC_dataXsec_pwiabc_corr     = -1            #bin-centered corr. data Xsec (using PWIA model for bc corr.)
    fsiRC_dataXsec_pwiabc_corr_err = -1

    #Reduced Xsec (Intitial set to -1)
    red_dataXsec     = -1.                #reduced dataXsec is determined from FSI radiative corrected, FSI bin-center corrected data_Xsec_avg (so use Ksig_cc1 determined from FSI avg. kinematics)
    red_dataXsec_err = -1.
    red_fsiXsec      = -1.                #theoretical FSI redXsec is determined from FSI_Xsec_theory / FSI_Ksig_cc1
    red_pwiaXsec     = -1.                #theoretical PWIA redXsec is determined from PWIA_Xsec_theory / PWIA_Ksig_cc1

    #--------------------------------------Calculate Bin Centering Correction Factor and Reduced Xsec--------------------------------------
   
    if fsiXsec_theory[i]>0. and fsiXsec_avg[i]>0.:
        bc_factor_fsi = fsiXsec_theory[i] / fsiXsec_avg[i]                                                       #FSI Bin Centering Correction Factor
        bc_factor_fsi_err = fsiXsec_theory[i] / (fsiXsec_avg[i] * fsiXsec_avg[i]) * fsiXsec_avg_err[i]

        if fsiRC_dataXsec_avg[i]>0.:
            #Apply FSI Bin Centering Correction Factor to Data Xsec (to ONLY FSI radiative corrected data, as this is what will be used in the final result, since FSI is closest to data)
            fsiRC_dataXsec_fsibc_corr = fsiRC_dataXsec_avg[i] *  bc_factor_fsi                                   #FSI Bin Centering Correction Applied (for FSI rad. corr data Xsec)
            fsiRC_dataXsec_fsibc_corr_err = np.sqrt(bc_factor_fsi**2 * (fsiRC_dataXsec_avg_err[i]*fsiRC_dataXsec_avg_err[i])  +   (fsiRC_dataXsec_avg[i]*fsiRC_dataXsec_avg[i]) *bc_factor_fsi_err**2)   
     
            #Calculate the Experimental Reduced Xsec (Momentum Distributions given the right kinematic region, thnq:(35,45) deg and Q2>4)
            if fsi_Ksig_cc1[i]>0.:
                red_dataXsec = fsiRC_dataXsec_fsibc_corr / fsi_Ksig_cc1[i]
                red_dataXsec_err = fsiRC_dataXsec_fsibc_corr_err/fsi_Ksig_cc1[i]

    if pwiaXsec_theory[i]>0. and pwiaXsec_avg[i]>0.:
        bc_factor_pwia = pwiaXsec_theory[i] / pwiaXsec_avg[i]                                                   #PWIA Bin Centering Correction Factor
        bc_factor_pwia_err = pwiaXsec_theory[i] / (pwiaXsec_avg[i] * pwiaXsec_avg[i]) * pwiaXsec_avg_err[i]

        if fsiRC_dataXsec_avg[i]>0.:
            #Apply PWIA Bin Centering Correction Factor to Data Xsec
            fsiRC_dataXsec_pwiabc_corr = fsiRC_dataXsec_avg[i] *  bc_factor_pwia                               #PWIA Bin Centering Correction Applied (for FSI rad. corr data Xsec)
            fsiRC_dataXsec_pwiabc_corr_err = np.sqrt(bc_factor_pwia**2 * (fsiRC_dataXsec_avg_err[i]*fsiRC_dataXsec_avg_err[i])  +   (fsiRC_dataXsec_avg[i]*fsiRC_dataXsec_avg[i]) *bc_factor_pwia_err**2)   
            


    #Calculate the Theoretical Reduced Cross Sections (Momentum Distributions in PWIA)
    if fsiXsec_theory[i]>0. and fsi_Ksig_cc1[i]>0.:
        red_fsiXsec =  fsiXsec_theory[i] / fsi_Ksig_cc1[i]

    if pwiaXsec_theory[i]>0. and pwia_Ksig_cc1[i]>0.:
        red_pwiaXsec =  pwiaXsec_theory[i] / pwia_Ksig_cc1[i]

    l= "%i %i %i %f %f %f %f %f %f %.12e %.12e %.12e %.12e %.12e %12e %.12e  %.12e  %.12e  %.12e   %.12e   %.12e   %.12e    %.12e\n"%(ib, ix_t[i], iy_t[i], thnq_t[i], pm_t[i], bc_factor_pwia, bc_factor_pwia_err, bc_factor_fsi, bc_factor_fsi_err, pwiaRC_dataXsec_avg[i], pwiaRC_dataXsec_avg_err[i], fsiRC_dataXsec_avg[i], fsiRC_dataXsec_avg_err[i],  fsiRC_dataXsec_pwiabc_corr,  fsiRC_dataXsec_pwiabc_corr_err,  fsiRC_dataXsec_fsibc_corr,  fsiRC_dataXsec_fsibc_corr_err,  pwiaXsec_theory[i],  fsiXsec_theory[i], red_dataXsec, red_dataXsec_err,  red_pwiaXsec, red_fsiXsec) 
    o.write(l)

o.close()
                        
print('Done')


