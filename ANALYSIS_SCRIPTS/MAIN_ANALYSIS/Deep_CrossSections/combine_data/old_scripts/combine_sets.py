import LT.box as B
import numpy as np

#This Code:
# ** combines different data sets (for the same Pm setting) of matching 2d bins 
# ** combines overlapping 2D bins for the different kinematic settings



#------------------------------------------------------------                   
# header information for the output file    
header = """                                                                                                                                                                                                   
#\\ xb = th_nq                                                                                                    
#\\ yb = pm                                                                        
# current header line:  
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ red_dataXsec[f,5]/   red_dataXsec_err[f,6]/   red_pwiaXsec[f,7]/   red_fsiXsec[f,8]/
"""

f80 = '../bin_centering_corrections/pm80_laget_bc_corr.txt'
f580_set1 = '../bin_centering_corrections/pm580_laget_bc_corr_set1.txt'
f580_set2 = '../bin_centering_corrections/pm580_laget_bc_corr_set2.txt'
f750_set1 = '../bin_centering_corrections/pm750_laget_bc_corr_set1.txt'
f750_set2 = '../bin_centering_corrections/pm750_laget_bc_corr_set2.txt'
f750_set3 = '../bin_centering_corrections/pm750_laget_bc_corr_set3.txt'

#-------------------COMBINE PM=80 DATA SETS------------------------

#Write Combined data to file
output_file='pm80_redXsec.txt'
fout = open(output_file, 'w') 
fout.write(header)

#Read Files to be combined
f1 = B.get_file(f80)

#Get 2D Bins
ib_1 = B.get_data(f1, 'i_b')
ix_1 = B.get_data(f1, 'i_x')
iy_1 = B.get_data(f1, 'i_y')

#Get Bin Value at thnq, Pm
xb_1 = B.get_data(f1, 'xb')    #thnq
yb_1 = B.get_data(f1, 'yb')    #Pm

#Get Reduced Cross Sections to Combine
red_dataXsec_1 = B.get_data(f1, 'red_dataXsec')
red_dataXsec_err_1 = B.get_data(f1, 'red_dataXsec_err')
red_pwiaXsec_1 = B.get_data(f1, 'red_pwiaXsec')
red_fsiXsec_1 = B.get_data(f1, 'red_fsiXsec')


for i, ib in enumerate(ib_1):
             
    #Calculate the Weighted Average of Data Reduced Cross Section
    red_dataXsec_avg =  (red_dataXsec_1[i]/red_dataXsec_err_1[i]) / (1./red_dataXsec_err_1[i]) 
    red_dataXsec_avg_err =  1. / (1./red_dataXsec_err_1[i])
    
    #Calculate the Average of Laget Theory Reduced Cross Section
    red_pwiaXsec_avg = (red_pwiaXsec_1[i]) / 1.
    red_fsiXsec_avg = (red_fsiXsec_1[i]) / 1.
    #Avoid NaN
    if(red_dataXsec_avg_err==0):
        red_dataXsec_avg = 0.
        
    l="%i %i %i %f  %f %.12e %.12e %.12e %.12e\n"%(ib, ix_1[i], iy_1[i], xb_1[i], yb_1[i],red_dataXsec_avg, red_dataXsec_avg_err, red_pwiaXsec_avg,red_fsiXsec_avg )
    fout.write(l)
        
fout.close()


#-------------------END COMBINE PM=80 DATA SETS------------------------

#-------------------COMBINE PM=580 DATA SETS------------------------

#Write Combined data to file
output_file='pm580_redXsec.txt'
fout = open(output_file, 'w') 
fout.write(header)

#Read Files to be combined
f1 = B.get_file(f580_set1)
f2 = B.get_file(f580_set2)

#Get 2D Bins
ib_1 = B.get_data(f1, 'i_b')
ib_2 = B.get_data(f2, 'i_b')
ix_1 = B.get_data(f1, 'i_x')
ix_2 = B.get_data(f2, 'i_x')
iy_1 = B.get_data(f1, 'i_y')
iy_2 = B.get_data(f2, 'i_y')

#Get Bin Value at thnq, Pm
xb_1 = B.get_data(f1, 'xb')    #thnq
xb_2 = B.get_data(f2, 'xb')    #thnq
yb_1 = B.get_data(f1, 'yb')    #Pm
yb_2 = B.get_data(f2, 'yb')    #Pm

#Get Reduced Cross Sections to Combine
red_dataXsec_1 = B.get_data(f1, 'red_dataXsec')
red_dataXsec_2 = B.get_data(f2, 'red_dataXsec')

red_dataXsec_err_1 = B.get_data(f1, 'red_dataXsec_err')
red_dataXsec_err_2 = B.get_data(f2, 'red_dataXsec_err')

red_pwiaXsec_1 = B.get_data(f1, 'red_pwiaXsec')
red_pwiaXsec_2 = B.get_data(f2, 'red_pwiaXsec')

red_fsiXsec_1 = B.get_data(f1, 'red_fsiXsec')
red_fsiXsec_2 = B.get_data(f2, 'red_fsiXsec')


#Find Matching 2D Bins (ib_1 ( index i ) -> file 1,  ib_2 (index j) -> file 2)
for i, ib in enumerate(ib_1):
    for j, jb in enumerate(ib_2):
        if ((ib-jb)==0):
             print('found matching 2D bins,(',ib,',',jb,') with indices (i,j)=',i,',',j)
             
             #Calculate the Weighted Average of Data Reduced Cross Section
             red_dataXsec_avg =  (red_dataXsec_1[i]/red_dataXsec_err_1[i] + red_dataXsec_2[j]/red_dataXsec_err_2[j]) / (1./red_dataXsec_err_1[i] + 1./red_dataXsec_err_2[j]) 
             red_dataXsec_avg_err =  1. / (1./red_dataXsec_err_1[i] + 1./red_dataXsec_err_2[j])

             #Calculate the Average of Laget Theory Reduced Cross Section
             red_pwiaXsec_avg = (red_pwiaXsec_1[i] + red_pwiaXsec_2[j]) / 2.
             red_fsiXsec_avg = (red_fsiXsec_1[i] + red_fsiXsec_2[j]) / 2.
             #Avoid NaN
             if(red_dataXsec_avg_err==0):
                 red_dataXsec_avg = 0.

             l="%i %i %i %f  %f %.12e %.12e %.12e %.12e\n"%(ib, ix_1[i], iy_1[i], xb_1[i], yb_1[i],red_dataXsec_avg, red_dataXsec_avg_err, red_pwiaXsec_avg,red_fsiXsec_avg )
             fout.write(l)

fout.close()


#-------------------END COMBINE PM=580 DATA SETS------------------------


#-------------------COMBINE PM=750 DATA SETS------------------------

#Write Combined data to file
output_file='pm750_redXsec.txt'
fout = open(output_file, 'w') 
fout.write(header)

#Read Files to be combined
f1 = B.get_file(f750_set1)
f2 = B.get_file(f750_set2)
f3 = B.get_file(f750_set3)

#Get 2D Bins
ib_1 = B.get_data(f1, 'i_b')
ib_2 = B.get_data(f2, 'i_b')
ib_3 = B.get_data(f3, 'i_b')
#Get 1D X bins (th_nq)
ix_1 = B.get_data(f1, 'i_x')
ix_2 = B.get_data(f2, 'i_x')
ix_3 = B.get_data(f3, 'i_x')
#Get 1D Y bins (Pm)
iy_1 = B.get_data(f1, 'i_y')
iy_2 = B.get_data(f2, 'i_y')
iy_3 = B.get_data(f3, 'i_y')

#Get Bin Value at thnq, Pm
xb_1 = B.get_data(f1, 'xb')    #thnq
xb_2 = B.get_data(f2, 'xb')    #thnq
xb_3 = B.get_data(f3, 'xb')    #thnq
yb_1 = B.get_data(f1, 'yb')    #Pm
yb_2 = B.get_data(f2, 'yb')    #Pm
yb_3 = B.get_data(f3, 'yb')    #Pm

#Get Reduced Cross Sections to Combine
red_dataXsec_1 = B.get_data(f1, 'red_dataXsec')
red_dataXsec_2 = B.get_data(f2, 'red_dataXsec')
red_dataXsec_3 = B.get_data(f3, 'red_dataXsec')

red_dataXsec_err_1 = B.get_data(f1, 'red_dataXsec_err')
red_dataXsec_err_2 = B.get_data(f2, 'red_dataXsec_err')
red_dataXsec_err_3 = B.get_data(f3, 'red_dataXsec_err')

red_pwiaXsec_1 = B.get_data(f1, 'red_pwiaXsec')
red_pwiaXsec_2 = B.get_data(f2, 'red_pwiaXsec')
red_pwiaXsec_3 = B.get_data(f3, 'red_pwiaXsec')

red_fsiXsec_1 = B.get_data(f1, 'red_fsiXsec')
red_fsiXsec_2 = B.get_data(f2, 'red_fsiXsec')
red_fsiXsec_3 = B.get_data(f3, 'red_fsiXsec')


#Find Matching 2D Bins (ib_1 ( index i ) -> file 1,  ib_2 (index j) -> file 2, ib_3(index k) -> file 3)
for i, ib in enumerate(ib_1):
    for j, jb in enumerate(ib_2):
        for k, kb in enumerate(ib_3):
            #Find overlapping bins in the 3 files
            if ((ib-jb)==0 and (ib-kb)==0):
                print('found matching 2D bins,(',ib,',',jb,',',kb,') with indices (i,j)=',i,',',j,',',k)
             
                #Calculate the Weighted Average of Data Reduced Cross Section
                red_dataXsec_avg =  (red_dataXsec_1[i]/red_dataXsec_err_1[i] + red_dataXsec_2[j]/red_dataXsec_err_2[j] + red_dataXsec_3[k]/red_dataXsec_err_3[k]) / (1./red_dataXsec_err_1[i] + 1./red_dataXsec_err_2[j] + 1./red_dataXsec_err_3[k]) 
                red_dataXsec_avg_err =  1. / (1./red_dataXsec_err_1[i] + 1./red_dataXsec_err_2[j] + 1./red_dataXsec_err_3[k])
                
                #Calculate the Average of Laget Theory Reduced Cross Section
                red_pwiaXsec_avg = (red_pwiaXsec_1[i] + red_pwiaXsec_2[j] + red_pwiaXsec_3[k]) / 3.
                red_fsiXsec_avg = (red_fsiXsec_1[i] + red_fsiXsec_2[j] + red_fsiXsec_3[k]) / 3.
                
                #Avoid NaN
                if(red_dataXsec_avg_err==0):
                    red_dataXsec_avg = 0.
                
                l="%i %i %i %f  %f %.12e %.12e %.12e %.12e\n"%(ib, ix_1[i], iy_1[i], xb_1[i], yb_1[i], red_dataXsec_avg, red_dataXsec_avg_err, red_pwiaXsec_avg,red_fsiXsec_avg )
                fout.write(l)

fout.close()


#-------------------END COMBINE PM=750 DATA SETS------------------------
