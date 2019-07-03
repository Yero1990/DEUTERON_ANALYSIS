#Calculate Bin-Centering Corrections by taking the ratio of theoretical to averaged laget cross sections


import LT.box as B
import numpy as np
import sys
from sys import argv

#------------------------------------------------------------
# header information for the output file
header = \
"""
# Laget Cross Section Results at the Averaged Kinematics
# averaged kinematic varibles used as input to calculate the cross section 
# kinematics: Ei, Q2, omega, th_pq_cm, phi_pq
#
#\\ xb = th_nq
#\\ yb = pm
# current header line:
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ bc_fact_fsi[f,5]/  bc_fact_fsi_err[f,6]/  dataXsec[f,7]/  dataXsec_err[f,8]/  dataXsec_bc[f,9]/  dataXsec_bc_err[f,10]/    
"""
#------------------------------------------------------------

output_file='bc_corrections.txt'
o = open(output_file,'w')
o.write(header)

#Load Theory Xsec
ft_80 = B.get_file('../theory_Xsec/pm80_laget_theory.txt')
ft_580_s1 = B.get_file('../theory_Xsec/pm580_laget_theory_set1.txt')
ft_580_s2 = B.get_file('../theory_Xsec/pm580_laget_theory_set2.txt')
ft_750_s1 = B.get_file('../theory_Xsec/pm750_laget_theory_set1.txt')
ft_750_s2 = B.get_file('../theory_Xsec/pm750_laget_theory_set2.txt')
ft_750_s3 = B.get_file('../theory_Xsec/pm750_laget_theory_set3.txt')


#Load Averaged Data and Theory Xsec
favg_80 = B.get_file('../average_Xsec/pm80_laget.txt')
favg_580_s1 = B.get_file('../average_Xsec/pm580_laget_set1.txt')
favg_580_s2 = B.get_file('../average_Xsec/pm580_laget_set2.txt')
favg_750_s1 = B.get_file('../average_Xsec/pm750_laget_set1.txt')
favg_750_s2 = B.get_file('../average_Xsec/pm750_laget_set2.txt')
favg_750_s3 = B.get_file('../average_Xsec/pm750_laget_set3.txt')

#Get Theory Xsec
ib_t80 = B.get_data(ft_80, 'i_b')             #2D Bin NUmber
pwiaXsec_t80 = B.get_data(ft_80, 'pwiaXsec')
fsiXsec_t80 = B.get_data(ft_80, 'fsiXsec')

#Get Averaged Xsec
ib_a80 = B.get_data(favg_80, 'i_b')             #2D Bin NUmber
ix_a80 = B.get_data(favg_80, 'i_x')
iy_a80 = B.get_data(favg_80, 'i_y')

pm_a80 = B.get_data(favg_80, 'yb')              #Missing Momentum Center Value
thnq_a80 = B.get_data(favg_80, 'xb')            #Theta_nq Center Value

pwiaXsec_a80 = B.get_data(favg_80, 'pwiaXsec')
fsiXsec_a80 = B.get_data(favg_80, 'fsiXsec')
dataXsec_a80 = B.get_data(favg_80, 'dataXsec')

pwiaXsec_a80_err = B.get_data(favg_80, 'pwiaXsec_err')
fsiXsec_a80_err = B.get_data(favg_80, 'fsiXsec_err')
dataXsec_a80_err = B.get_data(favg_80, 'dataXsec_err')
    

#Calculate Bin Centering Correction Factor

#Enumerate all 2D Bins
for ib, ib_a80 in enumerate(ib_a80):
   
    if fsiXsec_a80[ib]!=0:
        #pwia80_bc_factor = pwiaXsec_t80[ib] / pwiaXsec_a80[ib]    #uncertainty only on averaged (used error propagation. method of quadrature)
        #pwia80_bc_factor_err = pwiaXsec_t80[ib] * pwiaXsec_a80_err[ib] / (pwiaXsec_a80*[ib]*pwiaXsec_a80*[ib])
        #print(1/pwiaXsec_a80[ib]*pwiaXsec_a80[ib] )
        fsi80_bc_factor = fsiXsec_t80[ib] / fsiXsec_a80[ib]
        fsi80_bc_factor_err = fsiXsec_t80[ib] * fsiXsec_a80_err[ib] / (fsiXsec_a80[ib]* fsiXsec_a80[ib])


        #Apply Bin Centering Correction to Average Data Xsec
        dataXsec_a80_corr = dataXsec_a80[ib] * fsi80_bc_factor
        dataXsec_a80_corr_err = np.sqrt(fsi80_bc_factor**2 * (dataXsec_a80_err[ib]*dataXsec_a80_err[ib])  +   (dataXsec_a80[ib]*dataXsec_a80[ib]) *fsi80_bc_factor_err**2)

        l = "%i %i %i %f %f %f %f %.12e %.12e %.12e %.12e\n"%(ib_a80, ix_a80[ib], iy_a80[ib], thnq_a80[ib], pm_a80[ib], fsi80_bc_factor, fsi80_bc_factor_err, dataXsec_a80[ib],dataXsec_a80_err[ib],  dataXsec_a80_corr,  dataXsec_a80_corr_err )
        o.write(l)
o.close()

f = B.get_file(output_file)
bc_fact = B.get_data(f, 'bc_fact_fsi')
bc_fact_err = B.get_data(f, 'bc_fact_fsi_err')
xsec = B.get_data(f, 'dataXsec')
thnq = B.get_data(f, 'xb')
pm = B.get_data(f, 'yb')

#---Masking Arrays----
#bc_fact = np.ma.masked_equal(xsec, 0)
#bc_fact_err = np.ma.masked_equal(xsec, 0)
#thnq = np.ma.masked_equal(xsec, 0)
#pm = np.ma.masked_equal(xsec, 0)
print(bc_fact, bc_fact_err, thnq, pm, '\n')
print(len(bc_fact))
print(len(bc_fact_err))


B.plot_exp(pm, bc_fact, bc_fact_err, color='black', label=r'$\theta_{nq} = 10\pm5$')
#B.plot_exp(pm[thnq==20], bc_fact[thnq==20], bc_fact_err[thnq==20], color='blue', label=r'$\theta_{nq} = 20\pm5$')
#B.plot_exp(pm[thnq==30], bc_fact[thnq==30], bc_fact_err[thnq==30], color='cyan', label=r'$\theta_{nq} = 30\pm5$')
#B.plot_exp(pm[thnq==40], bc_fact[thnq==40], bc_fact_err[thnq==40], color='red', label=r'$\theta_{nq} = 40\pm5$')
#B.plot_exp(pm[thnq==50], bc_fact[thnq==50], bc_fact_err[thnq==50], color='green', label=r'$\theta_{nq} = 50\pm5$')

B.pl.legend()
B.pl.show('same')

#dataXsec_a80_corr[thnq_a80==40]
#B.plot_exp()
