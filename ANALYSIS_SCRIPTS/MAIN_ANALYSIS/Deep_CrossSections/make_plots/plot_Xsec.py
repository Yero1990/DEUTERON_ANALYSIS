import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d


#Conversion factor:  1 fm = 1/ (197 MeV),   
#The reduced cross section is in MeV^-3 units
MeV2fm = 197**3    #convert MeV^-3 to fm^3

#Get Bin-Centerd Corrected DATA FILES
f80 = B.get_file('../bin_centering_corrections/pm80_laget_bc_corr.txt')
f580_set1 = B.get_file('../bin_centering_corrections/pm580_laget_bc_corr_set1.txt')
f580_set2 = B.get_file('../bin_centering_corrections/pm580_laget_bc_corr_set2.txt')
f750_set1 = B.get_file('../bin_centering_corrections/pm750_laget_bc_corr_set1.txt')
f750_set2 = B.get_file('../bin_centering_corrections/pm750_laget_bc_corr_set2.txt')
f750_set3 = B.get_file('../bin_centering_corrections/pm750_laget_bc_corr_set3.txt')


#Get Bin-Conrr. Data Xsec, and theory
thnq80 = B.get_data(f80, 'xb')  #thnq bin center value (deg)
pm80 = B.get_data(f80, 'yb')    #pm bin cernter calue (GeV)
dataXsec80 = B.get_data(f80, 'dataXsec_bc')
dataXsec80_err = B.get_data(f80, 'dataXsec_bc_err')
pwiaXsec80_theory = B.get_data(f80, 'pwiaXsec_theory')
fsiXsec80_theory = B.get_data(f80, 'fsiXsec_theory')
red_dataXsec80 = B.get_data(f80, 'red_dataXsec')
red_dataXsec80_err = B.get_data(f80, 'red_dataXsec_err')
red_pwiaXsec80_theory = B.get_data(f80, 'red_pwiaXsec')
red_fsiXsec80_theory = B.get_data(f80, 'red_fsiXsec')

thnq580_set1 = B.get_data(f580_set1, 'xb')  
pm580_set1 = B.get_data(f580_set1, 'yb')   
dataXsec580_set1 = B.get_data(f580_set1, 'dataXsec_bc')
dataXsec580_err_set1 = B.get_data(f580_set1, 'dataXsec_bc_err')
pwiaXsec580_theory_set1 = B.get_data(f580_set1, 'pwiaXsec_theory')
fsiXsec580_theory_set1 = B.get_data(f580_set1, 'fsiXsec_theory')
red_dataXsec580_set1 = B.get_data(f580_set1, 'red_dataXsec')
red_dataXsec580_err_set1 = B.get_data(f580_set1, 'red_dataXsec_err')
red_pwiaXsec580_theory_set1 = B.get_data(f580_set1, 'red_pwiaXsec')
red_fsiXsec580_theory_set1 = B.get_data(f580_set1, 'red_fsiXsec')

thnq580_set2 = B.get_data(f580_set2, 'xb')  
pm580_set2 = B.get_data(f580_set2, 'yb')  
dataXsec580_set2 = B.get_data(f580_set2, 'dataXsec_bc')
dataXsec580_err_set2 = B.get_data(f580_set2, 'dataXsec_bc_err')
pwiaXsec580_theory_set2 = B.get_data(f580_set2, 'pwiaXsec_theory')
fsiXsec580_theory_set2 = B.get_data(f580_set2, 'fsiXsec_theory')
red_dataXsec580_set2 = B.get_data(f580_set2, 'red_dataXsec')
red_dataXsec580_err_set2 = B.get_data(f580_set2, 'red_dataXsec_err')
red_pwiaXsec580_theory_set2 = B.get_data(f580_set2, 'red_pwiaXsec')
red_fsiXsec580_theory_set2 = B.get_data(f580_set2, 'red_fsiXsec')

thnq750_set1 = B.get_data(f750_set1, 'xb')  
pm750_set1 = B.get_data(f750_set1, 'yb')  
dataXsec750_set1 = B.get_data(f750_set1, 'dataXsec_bc')
dataXsec750_err_set1 = B.get_data(f750_set1, 'dataXsec_bc_err')
pwiaXsec750_theory_set1 = B.get_data(f750_set1, 'pwiaXsec_theory')
fsiXsec750_theory_set1 = B.get_data(f750_set1, 'fsiXsec_theory')
red_dataXsec750_set1 = B.get_data(f750_set1, 'red_dataXsec')
red_dataXsec750_err_set1 = B.get_data(f750_set1, 'red_dataXsec_err')
red_pwiaXsec750_theory_set1 = B.get_data(f750_set1, 'red_pwiaXsec')
red_fsiXsec750_theory_set1 = B.get_data(f750_set1, 'red_fsiXsec')

thnq750_set2 = B.get_data(f750_set2, 'xb')  
pm750_set2 = B.get_data(f750_set2, 'yb')  
dataXsec750_set2 = B.get_data(f750_set2, 'dataXsec_bc')
dataXsec750_err_set2 = B.get_data(f750_set2, 'dataXsec_bc_err')
pwiaXsec750_theory_set2 = B.get_data(f750_set2, 'pwiaXsec_theory')
fsiXsec750_theory_set2 = B.get_data(f750_set2, 'fsiXsec_theory')
red_dataXsec750_set2 = B.get_data(f750_set2, 'red_dataXsec')
red_dataXsec750_err_set2 = B.get_data(f750_set2, 'red_dataXsec_err')
red_pwiaXsec750_theory_set2 = B.get_data(f750_set2, 'red_pwiaXsec')
red_fsiXsec750_theory_set2 = B.get_data(f750_set2, 'red_fsiXsec')

thnq750_set3 = B.get_data(f750_set3, 'xb')  
pm750_set3 = B.get_data(f750_set3, 'yb')  
dataXsec750_set3 = B.get_data(f750_set3, 'dataXsec_bc')
dataXsec750_err_set3 = B.get_data(f750_set3, 'dataXsec_bc_err')
pwiaXsec750_theory_set3 = B.get_data(f750_set3, 'pwiaXsec_theory')
fsiXsec750_theory_set3 = B.get_data(f750_set3, 'fsiXsec_theory')
red_dataXsec750_set3 = B.get_data(f750_set3, 'red_dataXsec')
red_dataXsec750_err_set3 = B.get_data(f750_set3, 'red_dataXsec_err')
red_pwiaXsec750_theory_set3 = B.get_data(f750_set3, 'red_pwiaXsec')
red_fsiXsec750_theory_set3 = B.get_data(f750_set3, 'red_fsiXsec')


#Plot Data
#B.plot_exp(pm80[thnq80==40], dataXsec80[thnq80==40], dataXsec80_err[thnq80==40], marker='s', color='r', label='DATA (80 MeV)', logy=True)
#B.plot_exp(pm580_set1[thnq580_set1==40], dataXsec580_set1[thnq580_set1==40], dataXsec580_err_set1[thnq580_set1==40], marker='s', color='b', label='DATA (580 MeV)', logy=True)
#B.plot_exp(pm750_set1[thnq750_set1==40], dataXsec750_set1[thnq750_set1==40], dataXsec750_err_set1[thnq750_set1==40], marker='s', color='g', label='DATA (750 MeV)', logy=True)

#Reduced Cross Section

#Convert from MeV^-3 to fm^3
red_dataXsec80 = red_dataXsec80 * MeV2fm
red_dataXsec580_set1 = red_dataXsec580_set1 * MeV2fm
red_dataXsec750_set1 = red_dataXsec750_set1 * MeV2fm
red_dataXsec580_set2 = red_dataXsec580_set2 * MeV2fm
red_dataXsec750_set2 = red_dataXsec750_set2 * MeV2fm
red_dataXsec750_set3 = red_dataXsec750_set3 * MeV2fm

red_dataXsec80_err = red_dataXsec80_err * MeV2fm
red_dataXsec580_err_set1 = red_dataXsec580_err_set1 * MeV2fm
red_dataXsec750_err_set1 = red_dataXsec750_err_set1 * MeV2fm
red_dataXsec580_err_set2 = red_dataXsec580_err_set2 * MeV2fm
red_dataXsec750_err_set2 = red_dataXsec750_err_set2 * MeV2fm
red_dataXsec750_err_set3 = red_dataXsec750_err_set3 * MeV2fm

#Theory
red_pwiaXsec80_theory = red_pwiaXsec80_theory * MeV2fm
red_fsiXsec80_theory = red_fsiXsec80_theory * MeV2fm
red_pwiaXsec580_theory_set1 = red_pwiaXsec580_theory_set1 * MeV2fm
red_fsiXsec580_theory_set1 = red_fsiXsec580_theory_set1 * MeV2fm
red_pwiaXsec750_theory_set1 = red_pwiaXsec750_theory_set1 * MeV2fm
red_fsiXsec750_theory_set1 = red_fsiXsec750_theory_set1 * MeV2fm


#Plot Data
B.plot_exp(pm80[thnq80==40], red_dataXsec80[thnq80==40], red_dataXsec80_err[thnq80==40], marker='s', color='r', label='DataSet1 (80 MeV)', logy=True)
B.plot_exp(pm580_set1[thnq580_set1==40], red_dataXsec580_set1[thnq580_set1==40], red_dataXsec580_err_set1[thnq580_set1==40], marker='s', color='b', label='DataSet1 (580 MeV)', logy=True)
B.plot_exp(pm580_set2[thnq580_set2==40], red_dataXsec580_set2[thnq580_set2==40], red_dataXsec580_err_set2[thnq580_set2==40], marker='^', color='b', label='DataSet2 (580 MeV)', logy=True)
B.plot_exp(pm750_set1[thnq750_set1==40], red_dataXsec750_set1[thnq750_set1==40], red_dataXsec750_err_set1[thnq750_set1==40], marker='s', color='g', label='DataSet1 (750 MeV)', logy=True)
B.plot_exp(pm750_set2[thnq750_set2==40], red_dataXsec750_set2[thnq750_set2==40], red_dataXsec750_err_set2[thnq750_set2==40], marker='^', color='g', label='DataSet2 (750 MeV)', logy=True)
B.plot_exp(pm750_set3[thnq750_set3==40], red_dataXsec750_set3[thnq750_set3==40], red_dataXsec750_err_set3[thnq750_set3==40], marker='o', color='g', label='DataSet3 (750 MeV)', logy=True)

#Plot Theory
B.plot_exp(pm80[thnq80==40], red_pwiaXsec80_theory[thnq80==40], linestyle='--', color='r', label='Laget PWIA (80 MeV)', logy=True)
B.plot_exp(pm80[thnq80==40], red_fsiXsec80_theory[thnq80==40], linestyle='-', color='r', label='Laget FSI (80 MeV)', logy=True)

B.plot_exp(pm580_set1[thnq580_set1==40], red_pwiaXsec580_theory_set1[thnq580_set1==40], linestyle='--', color='b', label='Laget PWIA (580 MeV)', logy=True)
B.plot_exp(pm580_set1[thnq580_set1==40], red_fsiXsec580_theory_set1[thnq580_set1==40], linestyle='-', color='b', label='Laget FSI (580 MeV)', logy=True)

B.plot_exp(pm750_set1[thnq750_set1==40], red_pwiaXsec750_theory_set1[thnq750_set1==40], linestyle='--', color='g', label='Laget PWIA (750 MeV)', logy=True)
B.plot_exp(pm750_set1[thnq750_set1==40], red_fsiXsec750_theory_set1[thnq750_set1==40], linestyle='-', color='g', label='Laget FSI (750 MeV)', logy=True)

B.pl.xlabel('Recoil Momenta [GeV/c]', fontsize=15)
B.pl.ylabel(r'$\sigma_{red}$ [fm$^{3}$]', fontsize=15)

B.pl.legend()
B.pl.show('same')
