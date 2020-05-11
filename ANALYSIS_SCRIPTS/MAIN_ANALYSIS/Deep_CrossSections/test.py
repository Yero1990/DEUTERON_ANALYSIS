import LT.box as B
from LT.datafile import dfile
import numpy as np
from scipy.interpolate import interp1d

MeV2fm = 197.3**3    #convert MeV^-3 to fm^3
GeV2fm = 0.1973**3    #convert GeV^-3 to fm^3


kin1 = dfile('combine_data/Em_final40MeV/redXsec_combined.txt')
kin2 = dfile('theoretical_models/updated_PWIA_models/theoryXsec_CD-BonnPWIA_thnq45.00_combined.data')
kin3 = dfile('theoretical_models/updated_PWIA_models/theoryXsec_V18PWIA_thnq45.00_combined.data')

pm1 = kin1['yb']    #GeV
thnq1 = kin1['xb']  #deg
#Ksigcc1_1 = kin1['pwia_Ksigcc1']   #Ksigcc1 Units: (ub * MeV^2 * sr^-2
paris = kin1['red_pwiaXsec_avg'] *1.e9        #convert MeV^-3 TO GeV^-3

pm2 = kin2['pm_avg']#GeV
#Ksigcc1_2 = kin2['Ksigcc1']       #Ksigcc1 Units: (ub * MeV^2 * sr^-2
#setting2 = kin2['setting']
cd_bonn = kin2['red_pwiaXsec_theory'] * 1.e9   #Red Xsec Units: GeV^-3

pm3 = kin3['pm_avg']#GeV
#Ksigcc1_3 = kin3['Ksigcc1'] #Ksigcc1 Units: (ub * MeV^2 * sr^-2
#setting3 = kin3['setting']
av18 = kin3['red_pwiaXsec_theory']  * 1.e9 #GeV^-3

#----------------------

kinMS1 = dfile('HallA_data/mom_dist_paris_mevc.data')   #pm[MeV], redXsec[GeV^-3]
kinMS2 = dfile('HallA_data/mom_dist_cdbonn_mevc.data')
kinMS3 = dfile('HallA_data/mom_dist_v18_mevc.data')

kinHA = dfile('HallA_data/pm_distribution_results_q3_1_45.0.data')
pm_ha = kinHA['p_miss_av'] * 0.1973
rho_a = kinHA['rho'] / 0.1973**3
rho_a_err = kinHA['delta_rho'] / 0.1973**3
print(pm_ha)


pm_ms1 = kinMS1['pm'] / 1000.   # GeV
rho_paris = kinMS1['rho']   #GeV^-3

pm_ms2 = kinMS2['pm'] / 1000.   # GeV
rho_cdbonn = kinMS2['rho']   #GeV^-3

pm_ms3 = kinMS3['pm'] / 1000.   # GeV
rho_v18 = kinMS3['rho']   #GeV^-3



#Interpolate Misak's calculations
f_ms_paris = interp1d(pm_ms1, rho_paris, fill_value='extrapolate')  
f_ms_cdbonn = interp1d(pm_ms2, rho_cdbonn)  
f_ms_v18 = interp1d(pm_ms3, rho_v18, fill_value='extrapolate')  


#Interpolate Carlos
f_cy_paris = interp1d(pm1, paris, fill_value='extrapolate')  
f_cy_cdbonn_linear = interp1d(pm2, cd_bonn, fill_value='extrapolate', kind='linear')  
f_cy_cdbonn_cubic = interp1d(pm2, cd_bonn, fill_value='extrapolate', kind='cubic')  
f_cy_v18 = interp1d(pm3, av18, fill_value='extrapolate')  

R = rho_a / f_ms_cdbonn(pm_ha)
R_err = rho_a_err / f_ms_cdbonn(pm_ha)

#Take Ratio of Hall A to CD-Bonn
R_cy_linear = rho_a / f_cy_cdbonn_linear(pm_ha)
R_cy_linear_err = rho_a_err / f_cy_cdbonn_linear(pm_ha)

R_cy_cubic = rho_a / f_cy_cdbonn_cubic(pm_ha)
R_cy_cubic_err = rho_a_err / f_cy_cdbonn_cubic(pm_ha)

B.plot_exp(pm_ha, R, R_err, marker='o', color='r', label='CD-Bonn (Misak)')
B.plot_exp(pm_ha, R_cy_linear, R_cy_linear_err, marker='s', color='b', label='CD-Bonn (Carlos, Linear Interpol)')
B.plot_exp(pm_ha, R_cy_cubic, R_cy_cubic_err, marker='^', color='g', label='CD-Bonn (Carlos, Cubic Interpol)')


#Take Ratio of Interpolate Carlos / Interpolated Misak
#R_paris = f_cy_paris(pm2) / f_ms_paris(pm2)
#R_cd = f_cy_cdbonn(pm1) / f_ms_cdbonn(pm1)
#R_v18 = f_cy_v18(pm1) / f_ms_v18(pm1)

#B.plot_exp(pm2, R_paris, marker='o', color='r', label='Paris')
#B.plot_exp(pm1, R_cd, marker='^', color='b', label='CD-Bonn')
#B.plot_exp(pm1, R_v18, marker='s', color='g', label='AV 18')

#B.plot_exp(pm_ha, R, R_err, marker='o', color='r', label='CD-Bonn (Misak)')
#B.plot_exp(pm_ha, R_cy_cd, R_cy_cd_err, marker='s', color='b', label='CD-Bonn (Carlos)')

#B.plot_exp(pm_ms2, rho_cdbonn, marker='o', color='r', label='')
#B.plot_exp(pm_ha, f_ms_cdbonn(pm_ha), marker='None', linestyle='--', color='r')

#B.plot_exp(pm2, cd_bonn, marker='s', color='b')
#B.plot_exp(pm_ms2, f_cy_cdbonn(pm_ms2), marker='None', linestyle='--', color='b')

#B.plot_exp(pm_ha, rho_a, rho_a_err, marker='^', color='k', label='Hall A')
#B.pl.yscale('log')

#B.plot_exp(pm_ms2, rho_cdbonn, marker='o', color='r', label='CD-Bonn (Misak)')
#B.plot_exp(pm_ha, f_ms_cdbonn(pm_ha), marker='None', linestyle='--', color='r', label='Linear Interpolation')

#B.plot_exp(pm2, cd_bonn, marker='s', color='b', label='CD-Bonn (Carlos)')
#B.plot_exp(pm_ha, f_cy_cdbonn_linear(pm_ha), marker='None', linestyle='--', color='b', label='Linear Interpolation')
#B.plot_exp(pm_ha, f_cy_cdbonn_cubic(pm_ha), marker='None', linestyle='-', color='b', label='Cubic Interpolation')

#B.pl.yscale('log')
B.pl.legend()
B.pl.xlabel(r'$P_{m}$ [GeV/c]')
B.pl.ylabel(r'$\sigma_{red}/\sigma^{CD-Bonn}_{red}$')

B.pl.show()
#-------------------------------

#Plot reduced Xsec
#B.plot_exp(pm1[thnq1==45.], paris[thnq1==45.0], marker='o', color='r', label='Paris')
#B.plot_exp(pm2[setting2=='80'], cd_bonn[setting2=='80'], marker='^', color='b', label='CD-Bonn')
#B.plot_exp(pm3[setting3=='80'], av18[setting3=='80'], marker='s', color='g', label='AV18')

#Calculate Ratio of redXsec / redXsec_misak
#R_paris = paris[thnq1==45.0] / f_ms_paris(pm1[thnq1==45.])
#R_cdbonn = cd_bonn[setting2=='80'] / f_ms_cdbonn(pm2[setting2=='80'])
#R_v18 = av18[setting3=='80'] / f_ms_v18(pm3[setting3=='80'])

#print('paris_cy=',paris[thnq1==45.0])
#print('paris_ms=',f_ms_paris(pm1[thnq1==45.]))
'''
B.plot_exp(pm1[thnq1==45.], R_paris,  marker='o', color='r', label='Paris', logy=True)
B.plot_exp(pm2[setting2=='80'], R_cdbonn,  marker='^', color='b', label='CD-Bonn', logy=True)
B.plot_exp(pm3[setting3=='80'], R_v18,  marker='s', color='g', label='AV18', logy=True)
B.pl.legend()
B.pl.show()


#PLot Ksigcc1 for Pm= 80, thn1=45 deg for data and all models (shows that we are using the exact same Ksigcc1 factor.)
B.plot_exp(pm1[thnq1==45.], Ksigcc1_1[thnq1==45.0], marker='o', color='r', label='Hall C data')
B.plot_exp(pm2[setting2=='80'], Ksigcc1_2[setting2=='80'], marker='^', color='b', label='CD-Bonn PWIA')
B.plot_exp(pm3[setting3=='80'], Ksigcc1_3[setting3=='80'], marker='s', color='g', label='AV18 PWIA')
B.pl.ylabel(r'$Ksig_{cc1}$')
B.pl.xlabel(r'$P_{m}[GeV/c]$')

B.pl.legend()
B.pl.show()
'''
