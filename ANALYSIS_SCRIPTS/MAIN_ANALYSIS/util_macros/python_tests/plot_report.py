import LT.box as B
import numpy as np

pm_set='580 MeV'

f = B.get_file('../report_deep_pm580_set1.dat')

run = B.get_data(f, 'Run')
charge = B.get_data(f, 'charge')
tLT = B.get_data(f, 'tLT')
h_trkeff = B.get_data(f, 'hTrkEff')
h_trkeff_err = B.get_data(f, 'hTrkEff_err')
e_trkeff = B.get_data(f, 'eTrkEff')                              
e_trkeff_err = B.get_data(f, 'eTrkEff_err')  
tgtBoil_factor = B.get_data(f, 'tgtBoil_factor')
avg_current = B.get_data(f, 'avg_current')
ps1x_rate = B.get_data(f, 'pS1X_rate')
ptrig1_rate = B.get_data(f, 'ptrig1_rate')
ptrig4_rate = B.get_data(f, 'ptrig4_rate') 
ptrig6_rate = B.get_data(f, 'ptrig6_rate') 
coin_scaler = B.get_data(f, 'coin_scaler')
xBPM = B.get_data(f, 'xBPM')
yBPM = B.get_data(f, 'yBPM')

Qnorm = coin_scaler / (charge*tgtBoil_factor)                                                                      
Qnorm_err = np.sqrt(coin_scaler) / charge 

fig1 = B.pl.figure()
B.pl.subplot(221)
B.plot_exp(run, Qnorm, Qnorm_err, marker='o', color='red', linestyle='-', label='Norm. Coin Scaler, Pm=%s'%(pm_set))
B.pl.xlabel('Run')
B.pl.ylabel('Coin. Scaler Counts / mC ')
B.pl.title('Charge Normalized Coincidence Scaler Counts')

#fig2 = B.pl.figure()
B.pl.subplot(222)
B.plot_exp(run, e_trkeff, e_trkeff_err, marker='^', color='green', linestyle='-', label='SHMS Tracking Efficiency, Pm=%s'%(pm_set)) 
B.pl.xlabel('Run')
B.pl.ylabel('SHMS Tracking Efficiency')
B.pl.title('SHMS Tracking Efficiency')

#fig3 = B.pl.figure()
B.pl.subplot(223)
B.plot_exp(run, h_trkeff, h_trkeff_err, marker='s', color='blue', linestyle='-', label='HMS Tracking Efficiency, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('HMS Tracking Efficiency') 
B.pl.title('HMS Tracking Efficiency') 

#fig4 = B.pl.figure()
B.pl.subplot(224)
B.plot_exp(run,tLT, marker='o', color='r', linestyle='-',  label='Total Live Time, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('Total Live Time') 
B.pl.title('Total Live Time') 

fig2 = B.pl.figure()
B.pl.subplot(221)
B.plot_exp(run, tgtBoil_factor, marker='s', color='blue', linestyle='-', label='LD2 Target Boiling Factor, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('LD2 Target Boiling Factor') 
B.pl.title('LD2 Target Boiling Factor') 

#fig6 = B.pl.figure()
B.pl.subplot(222)
B.plot_exp(run, avg_current, marker='^', color='green', linestyle='-', label='Average Beam Current, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('Average Beam Current [uA]') 
B.pl.title('Average Beam Current')

#fig7 = B.pl.figure()
B.pl.subplot(223)
B.plot_exp(run, ptrig1_rate, marker='s', color='blue', linestyle='-', label='SHMS 3/4 Rate, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('SHMS 3/4 Rate [kHz]') 
B.pl.title('SHMS 3/4 Rate') 

#fig8 = B.pl.figure()
B.pl.subplot(224)
B.plot_exp(run, ptrig4_rate, marker='o', color='r', linestyle='-', label='HMS 3/4 Rate, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('HMS 3/4 Rate [kHz]') 
B.pl.title('HMS 3/4 Rate') 

fig3 = B.pl.figure()
B.plot_exp(run, ptrig6_rate, marker='^', color='green', linestyle='-', label='Coincidence Rate, Pm=%s'%(pm_set))
B.pl.xlabel('Run')                                                              
B.pl.ylabel('Coincidence Rate [kHz]') 
B.pl.title('Coincidence Rate')    

B.pl.legend()
B.pl.show()
