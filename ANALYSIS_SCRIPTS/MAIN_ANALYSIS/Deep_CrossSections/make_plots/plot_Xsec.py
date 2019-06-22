import LT.box as B
import numpy as np
from scipy.interpolate import interp1d


#Get Bin-Centerd Corrected DATA
f80 = B.get_file('pm80_laget_bc_corr.txt')
f580_set1 = B.get_file('pm580_laget_bc_corr_set1.txt')
f580_set2 = B.get_file('pm580_laget_bc_corr_set2.txt')
f750_set1 = B.get_file('pm750_laget_bc_corr_set1.txt')
f750_set2 = B.get_file('pm750_laget_bc_corr_set2.txt')
f750_set3 = B.get_file('pm750_laget_bc_corr_set3.txt')


#Get Bin-Conrr. Data Xsec, and theory
thnq80 = B.get_data(f80, 'xb')  #thnq bin center value (deg)
pm80 = B.get_data(f80, 'yb')    #pm bin cernter calue (GeV)
dataXsec80 = B.get_data(f80, 'dataXsec_bc')
dataXsec80_err = B.get_data(f80, 'dataXsec_bc_err')
pwiaXsec80_theory = B.get_data(f80, 'pwiaXsec_theory')
fsiXsec80_theory = B.get_data(f80, 'fsiXsec_theory')

thnq580_set1 = B.get_data(f580_set1, 'xb')  
pm580_set1 = B.get_data(f580_set1, 'yb')   
dataXsec580_set1 = B.get_data(f580_set1, 'dataXsec_bc')
dataXsec580_err_set1 = B.get_data(f580_set1, 'dataXsec_bc_err')
pwiaXsec580_theory_set1 = B.get_data(f580_set1, 'pwiaXsec_theory')
fsiXsec580_theory_set1 = B.get_data(f580_set1, 'fsiXsec_theory')

thnq580_set2 = B.get_data(f580_set2, 'xb')  
pm580_set2 = B.get_data(f580_set2, 'yb')  
dataXsec580_set2 = B.get_data(f580_set2, 'dataXsec_bc')
dataXsec580_err_set2 = B.get_data(f580_set2, 'dataXsec_bc_err')
pwiaXsec580_theory_set2 = B.get_data(f580_set2, 'pwiaXsec_theory')
fsiXsec580_theory_set2 = B.get_data(f580_set2, 'fsiXsec_theory')

thnq750_set1 = B.get_data(f750_set1, 'xb')  
pm750_set1 = B.get_data(f750_set1, 'yb')  
dataXsec750_set1 = B.get_data(f750_set1, 'dataXsec_bc')
dataXsec750_err_set1 = B.get_data(f750_set1, 'dataXsec_bc_err')
pwiaXsec750_theory_set1 = B.get_data(f750_set1, 'pwiaXsec_theory')
fsiXsec750_theory_set1 = B.get_data(f750_set1, 'fsiXsec_theory')

thnq750_set2 = B.get_data(f750_set2, 'xb')  
pm750_set2 = B.get_data(f750_set2, 'yb')  
dataXsec750_set2 = B.get_data(f750_set2, 'dataXsec_bc')
dataXsec750_err_set2 = B.get_data(f750_set2, 'dataXsec_bc_err')
pwiaXsec750_theory_set2 = B.get_data(f750_set2, 'pwiaXsec_theory')
fsiXsec750_theory_set2 = B.get_data(f750_set2, 'fsiXsec_theory')

thnq750_set3 = B.get_data(f750_set3, 'xb')  
pm750_set3 = B.get_data(f750_set3, 'yb')  
dataXsec750_set3 = B.get_data(f750_set3, 'dataXsec_bc')
dataXsec750_err_set3 = B.get_data(f750_set3, 'dataXsec_bc_err')
pwiaXsec750_theory_set3 = B.get_data(f750_set3, 'pwiaXsec_theory')
fsiXsec750_theory_set3 = B.get_data(f750_set3, 'fsiXsec_theory')



#Plot Data
B.plot_exp(pm80[thnq80==40], dataXsec80[thnq80==40], dataXsec80_err[thnq80==40], marker='s', color='r', label='DATA (80 MeV)', logy=True)
B.plot_exp(pm580_set1[thnq580_set1==40], dataXsec580_set1[thnq580_set1==40], dataXsec580_err_set1[thnq580_set1==40], marker='s', color='b', label='DATA (580 MeV)', logy=True)
B.plot_exp(pm750_set1[thnq750_set1==40], dataXsec750_set1[thnq750_set1==40], dataXsec750_err_set1[thnq750_set1==40], marker='s', color='g', label='DATA (750 MeV)', logy=True)


#Create Interpolation Function
f_pwia80 = interp1d(pm80, pwiaXsec80_theory, kind='linear')
f_fsi80 = interp1d(pm80[thnq80==40],  fsiXsec80_theory[thnq80==40], kind='linear')
x = np.linspace(0,10, num=41)
print(f_pwia80(x))
#B.pl.plot(pm80[thnq80==40], f_pwia80)
#B.pl.show()

#B.pl.plot(pm80[thnq80==40], f_pwia80, color='r', linestyle='--', label='PWIA')
#B.pl.plot(pm80[thnq80==40], f_fsi80, color='r', linestyle='-', label='FSI')

#B.pl.legend()
#B.pl.show('same')
