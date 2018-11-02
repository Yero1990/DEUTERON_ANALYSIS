#Code to determine the variations in E, E' theta_e from the variations
#measured in W_simc - W_data

import LT.box as B
import numpy as np
from numpy import ndarray
f = B.get_file('hms_heep_summary_FINAL.data')

#Define masses
Mp = 0.938272   #proton mass GeV
me = 0.00051099 #electron mass GeV

#converion factor from deg to radians
dtr = np.pi / 180.


#Get the data from datafile
run = B.get_data(f, 'Run')
nmr_true = B.get_data(f, 'nmr_true')
kf = B.get_data(f, 'nmr_P')                   #central electron momentum
theta_e = B.get_data(f, 'hms_Angle')          #e- arm central angle
Pf = B.get_data(f, 'shms_P')                  #central proton arm momentum
theta_p = B.get_data(f, 'shms_Angle')         #p arm central angle
Eb = B.get_data(f, 'beam_e')                  #beam energy          
data_W_mean = B.get_data(f, 'data_W_mean')
data_W_mean_err = B.get_data(f, 'data_W_mean_err')
data_W_sigma = B.get_data(f, 'data_W_sigma')
simc_W_mean = B.get_data(f, 'simc_W_mean')
simc_W_mean_err = B.get_data(f, 'simc_W_mean_err')
simc_W_sigma = B.get_data(f, 'simc_W_sigma')

#Declare arrays
dW_mean = ndarray(22)                #W_simc_fit - W_data_fit
dW_mean_err = ndarray(22)             #error in dW_mean
dE_beam = ndarray(22)                 #beam energy variation
d_kf = ndarray(22)                    #central momentum variation
d_theta = ndarray(22)                 #central spec. angle variation                 
corr_factor = ndarray(22)             #momentum corr. factor
kf_corr = ndarray(22)                 #corrected momentum

dW_dkf = ndarray(22)                  #derivative dW/dkf = -Eb / kf
dkf_kf = ndarray(22)                   #relative uncertainty in cent. momentum dkf / kf


index = [0] * 22                      #index to keep track of runs


#Add keys to the existing kin file
f.add_key('dW_meas', 'f')
f.add_key('dW_meas_err', 'f')
f.add_key('dW_dkf', 'f')
f.add_key('dkf', 'f')
f.add_key('dkf_kf', 'f')
f.add_key('kf_corr_factor', 'f')
f.add_key('kf_corr', 'f')

#Loop over all kin groups
for i, run in enumerate(run):

    #Calculate variations and errors in W
    dW_mean[i] = simc_W_mean[i] - data_W_mean[i]
    dW_mean_err[i] = np.sqrt( (simc_W_mean_err[i])**2 + (data_W_mean_err[i])**2 )


    #Formulas for variations in beam energy, e- angle and e- momentum
    dE_beam[i] = Eb[i] / kf[i]  * dW_mean[i]                                                                     #variation in beam energy
    d_kf[i] = - kf[i] / Eb[i] * dW_mean[i]                                                                      #variation in electron arm momentum
    d_theta[i] = -1. / (2.*Eb[i]*kf[i]*np.sin(0.5*theta_e[i]*dtr)*np.cos(0.5*theta_e[i]*dtr) / Mp ) * dW_mean[i]       #variation in electron arm angle

    dW_dkf[i] = - Eb[i] / kf[i]
    dkf_kf[i] = - dW_mean[i] / Eb[i]

    #Assume the correction is from momentum ONLY
    corr_factor[i] = 1. - (dW_mean[i]/Eb[i])
    kf_corr[i] = kf[i]*corr_factor[i]

    f.data[i]['dW_meas'] = round(dW_mean[i],5)
    f.data[i]['dW_meas_err'] = round(dW_mean_err[i],5)
    f.data[i]['dW_dkf'] = round(dW_dkf[i],5)
    f.data[i]['dkf'] = round(d_kf[i],5)
    f.data[i]['dkf_kf'] = round(dkf_kf[i],5)
    f.data[i]['kf_corr_factor'] = round(corr_factor[i],5)
    f.data[i]['kf_corr'] = round(kf_corr[i],5)

    index[i] = i + 1

f.save('hms_heep_summary_FINAL_v2.data')
#    print('dW_mean = ', round(dW_mean[i],4), 'dE_beam = ', round(dE_beam[i],4), 'd_kf = ', round(d_kf[i],4), 'd_theta = ', round(d_theta[i],4), 'kf = ', round(kf[i],4),  'corr_fac = ',round(corr_factor[i],4), 'kf_corr = ', round(kf_corr[i],4) )

#B.plot_exp(nmr_true, kf_corr)
#B.plot_exp(dW_mean, corr_factor)

#B.plot_exp(dE_beam, dW_mean, dW_mean_err ) 
#B.plot.xlabel('Beam Energy Variation [GeV]')
#B.plot.ylabel('Invariant Mass W Variation [GeV]')                                                                                           

#B.plot_exp(d_kf, dW_mean, dW_mean_err )
#B.plot_exp(d_theta/dtr, dW_mean, dW_mean_err )

#B.plot_exp(kf, dkf_kf)                                                                                                                                                   
#B.pl.xlabel('HMS Un-Corrected Central Momentum, E\'  [GeV]')                                                                                            
#B.pl.ylabel('Relative Uncertainty dE\' / E\' ')   
#B.pl.title('HMS dE\'/E\' vs E\' ')
#B.pl.grid(True)

#B.pl.show()
