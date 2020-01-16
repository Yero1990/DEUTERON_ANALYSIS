import numpy as np
import LT.box as B
from LT.datafile import dfile

pm_set = 580
data_set = 1

if pm_set == 80:
    kin = dfile('pm80_laget_bc_corr.txt')                                                                                                                    
    kin2 = dfile('../../average_kinematics/Em_final40MeV/pm80_fsi_norad_avgkin.txt') 
else:
    kin = dfile('pm%i_laget_bc_corr_set%i.txt'%(pm_set, data_set))
    kin2 = dfile('../../average_kinematics/Em_final40MeV/pm%i_fsi_norad_avgkin_set%i.txt'%(pm_set, data_set))

dataXsec = kin['fsiRC_dataXsec_fsibc_corr']
dataXsec_err = kin['fsiRC_dataXsec_fsibc_corr_err']

red_dataXsec = kin['red_dataXsec']                                                                                       
red_dataXsec_err = kin['red_dataXsec_err'] 

red_pwiaXsec = kin['red_pwiaXsec']                                                                                             
red_fsiXsec = kin['red_fsiXsec'] 

Ksigcc1 = kin2['Ksig_cc1']
pm_bin = kin2['yb']
thnq_bin = kin2['xb']
Q2 = kin2['Q2_calc']

#Q2_b = Q2[thnq_bin==35]
#print (Q2_b)
#print(pm_bin[(Q2>4.0*1e6) & (Q2<4.1*1e6)])
thnq0 = 35
pm0 = 0.540
Qmax = 4.35

#--------BIN in Pmiss ONLY: ---------------
dataXsec_b = dataXsec[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)]
dataXsec_b_err =  dataXsec_err[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)] 
red_dataXsec_b = red_dataXsec[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)]                                                        
red_dataXsec_err_b = red_dataXsec_err[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)]
red_pwiaXsec_b = red_pwiaXsec[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)] 
red_fsiXsec_b = red_fsiXsec[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)] 
Q2_b = Q2[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)]
Ksigcc1_b = Ksigcc1[(Q2>4.0*1e6) & (Q2<Qmax*1e6) & (pm_bin==pm0)] 
red_Xsec_b = (dataXsec_b / Ksigcc1_b) 
red_Xsec_b_err = (dataXsec_b_err / Ksigcc1_b)  

#print(dataXsec_b)
#print(dataXsec_b_err)
#print(Q2_b)
#print(Ksigcc1_b)
#print(red_Xsec_b)
#print(red_Xsec_b_err)
print('sig_red=',red_dataXsec_b)
print('sig_red_err=',red_dataXsec_err_b)
print('sig_red_pwia=',red_pwiaXsec_b)
print('sig_red_fsi=',red_fsiXsec_b) 


Rdata = B.linefit(Q2_b/1e6, dataXsec_b, dataXsec_b_err)
Rksig = B.linefit(Q2_b/1e6, Ksigcc1_b)
Rred = B.linefit(Q2_b/1e6, red_dataXsec_b, red_dataXsec_err_b)
#Rred_pwia = B.linefit(Q2_b/1e6, red_pwiaXsec_b) 
#Rred_fsi = B.linefit(Q2_b/1e6, red_fsiXsec_b) 

norm_data = Rdata.line(4.1915)
norm_ksig = Rksig.line(4.1915)
norm_red = Rred.line(4.1915)

B.plot_exp(Q2_b/1e6, dataXsec_b/norm_data, dataXsec_b_err/norm_data, marker='o', color='k', logy=False, label=r'$\sigma_{exp}$')      
B.plot_exp(Q2_b/1e6, Ksigcc1_b/norm_ksig, marker='^', color='r', logy=False, label=r'$K\sigma_{cc1}$')                                     
B.plot_exp(Q2_b/1e6, red_dataXsec_b/norm_red, red_dataXsec_err_b/norm_red, marker='s', color='b', logy=False, label=r'$\sigma_{exp}/K\sigma_{cc1}$')     
                          
data_slope = Rdata.res['parameters'][1]
ksig_slope = Rksig.res['parameters'][1]
red_slope = Rred.res['parameters'][1]
print(Rdata.res.keys())

B.pl.title('$Q^{2}$ Dependence on Cross Sections: $P_{miss}$ = 540 $\pm$ 20 MeV')
B.plot_line(Rdata.xpl, Rdata.ypl/norm_data, color='k', label=r'$\sigma_{exp} $FIT: slope = %.4e'%(data_slope))
B.plot_line(Rksig.xpl, Rksig.ypl/norm_ksig, color='r', label=r'$K\sigma_{cc1} $FIT: slope = %.4e'%(ksig_slope))
B.plot_line(Rred.xpl, Rred.ypl/norm_red, color='b', label=r'$\sigma_{red}$ FIT: slope = %.4e'%(red_slope))


B.pl.xlabel(r'$Q^{2} (GeV/c^{2})$')
B.pl.ylabel(r'$\sigma_{exp}/\sigma_{exp}(Q^{2}=4.1915)$')

#B.pl.xlim(3.9,5.1)
B.pl.ylim(0,2)

B.pl.legend(loc='upper right')
B.pl.show()

'''
