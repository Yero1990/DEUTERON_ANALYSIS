import LT.box as B
import numpy as np
import sys                             
from sys import argv    
import getopt       


#------------------------------------------------------------                   
# header information for the output file    
header = """                                            
# averaged kinematics results                                                                              
# averaged kinematic varibles used as input to calculate the averaged                                
# kinematics: Ei, omega, th_e, pf                                                                     
#                                                                                                  
# variables with _mc attached are from histograms not calculated                                                                
#\\ xb = th_nq                                                                                                    
#\\ yb = pm                                                                        
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ bc_fact_pwia[f,5]/  bc_fact_pwia_err[f,6]/  bc_fact_fsi[f,7]/  bc_fact_fsi_err[f,8]/  dataXsec[f,9]/  dataXsec_err[f,10]/  dataXsec_bc[f,11]/  dataXsec_bc_err[f,12]/  pwiaXsec_theory[f,13]/   fsiXsec_theory[f,14]/ 
"""

#create output file to write avg kin                                                                                      
pm_set = int(sys.argv[1])                                                                            
data_set = int(sys.argv[2])                                                                                                            
print argv                                                                                   
         
#usage: /apps/python/2.7.12/bin/python.py calc_bc_corr.py 580  1           
if pm_set == 80:                                                                                                       
    output_file = 'pm%i_laget_bc_corr.txt'%(pm_set)                
else:
    output_file = 'pm%i_laget_bc_corr_set%i.txt'%(pm_set, data_set)

o = open(output_file,'w')  
o.write(header)

#Load Theory Xsec
if pm_set == 80:
    ft = B.get_file('../theory_Xsec/pm%i_laget_theory.txt'%(pm_set))
else:
    ft = B.get_file('../theory_Xsec/pm%i_laget_theory_set%i.txt'%(pm_set, data_set)) 

#Load Averaged Xsec
if pm_set == 80:                                       
    fa = B.get_file('../average_Xsec/pm%i_laget.txt'%(pm_set))                                   
else:                                                                                                                                                       
    fa = B.get_file('../average_Xsec/pm%i_laget_set%i.txt'%(pm_set, data_set)) 


#Get Theory Xsec 
ib_t = B.get_data(ft, 'i_b')             #2D Bin NUmber 
ix_t = B.get_data(ft, 'i_x')             #X-Bin Number (thnq bin number)
iy_t = B.get_data(ft, 'i_y')             #Y-Bin Number (Pm bin number)
thnq_t = B.get_data(ft, 'xb')
pm_t = B.get_data(ft, 'yb')
pwiaXsec_theory = B.get_data(ft, 'pwiaXsec') 
fsiXsec_theory = B.get_data(ft, 'fsiXsec') 

#Get Average Xsec                                                                                                                         
ib_a = B.get_data(fa, 'i_b')             #2D Bin Number
ix_a = B.get_data(fa, 'i_x')             #X-Bin Number (thnq bin number)
iy_a = B.get_data(fa, 'i_y')             #Y-Bin Number (Pm bin number)
thnq_a = B.get_data(fa, 'xb')                                                                                                                                                           
pm_a = B.get_data(fa, 'yb')                                                                 
pwiaXsec_avg = B.get_data(fa, 'pwiaXsec')                                                                                  
fsiXsec_avg = B.get_data(fa, 'fsiXsec')  
dataXsec_avg = B.get_data(fa, 'dataXsec')
pwiaXsec_avg_err = B.get_data(fa, 'pwiaXsec_err')                                                                                
fsiXsec_avg_err = B.get_data(fa, 'fsiXsec_err') 
dataXsec_avg_err = B.get_data(fa, 'dataXsec_err')


#Some thoughts while writing this code
#To match 2D bins between any two files, do a nested loop over the 2D bins of files f1, f2
#For each 2D bin in f1, loop over all 2D bins in f2, take the difference between ith bin in f1
#and the jth bin in f2. If the difference is ZERO, you have found a matching 2D bin, then proceed to do
#the calculations for the matching bins.

#Calculate Bin Centering Factor
#Loop over ith theory bin
for i, ib in enumerate(ib_t):
    #Loop over jth avg bin
    for j, jb in enumerate(ib_a):
        #print('ib=',ib,' : jb=',jb, ' diff=',ib-jb)
        if ((ib-jb)==0):
            print('found matching 2D bins,(',ib,',',jb,') with indices (i,j)=',i,',',j)
            print('ix_t=',ix_t[i],'ix_a=',ix_a[j])
            #Set initial values to -1 unless the bin passes the condition
            bc_factor_fsi = -1
            bc_factor_pwia = -1
            dataXsec_bc_corr = -1
            bc_factor_fsi_err= -1
            bc_factor_pwia_err = -1
            dataXsec_bc_corr_err = -1
            #Proceed if bin in denominator in bin_centering factor is zero
            if pwiaXsec_avg[j]!=0 and fsiXsec_avg[j]!=0:
                            
                bc_factor_fsi = fsiXsec_theory[i] / fsiXsec_avg[j]
                bc_factor_fsi_err = fsiXsec_theory[i] / (fsiXsec_avg[j] * fsiXsec_avg[j]) * fsiXsec_avg_err[j]

                bc_factor_pwia = pwiaXsec_theory[i] / pwiaXsec_avg[j]
                bc_factor_pwia_err = pwiaXsec_theory[i] / (pwiaXsec_avg[j] * pwiaXsec_avg[j]) * pwiaXsec_avg_err[j]
                
                #Apply the correction factor
                dataXsec_bc_corr = dataXsec_avg[j] *  bc_factor_fsi
                dataXsec_bc_corr_err = np.sqrt(bc_factor_fsi**2 * (dataXsec_avg_err[j]*dataXsec_avg_err[j])  +   (dataXsec_avg[j]*dataXsec_avg[j]) *bc_factor_fsi_err**2)   
                
                l= "%i %i %i %f %f %f %f %f %f %.12e %.12e %.12e %.12e %.12e %.12e\n"%(ib, ix_t[i], iy_t[i], thnq_t[i], pm_t[i], bc_factor_pwia, bc_factor_pwia_err, bc_factor_fsi, bc_factor_fsi_err, dataXsec_avg[i], dataXsec_avg_err[i],  dataXsec_bc_corr,  dataXsec_bc_corr_err,  pwiaXsec_theory[i],  fsiXsec_theory[i]  ) 
                o.write(l)
o.close()
                        
print('Done')

