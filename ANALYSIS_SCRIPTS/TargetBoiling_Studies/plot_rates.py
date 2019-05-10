import LT.box as B                                                                                                   
import numpy as np                                                                                                            
import matplotlib.pyplot as plt                                                                                          


#LH2
fLD2 = B.get_file('hms_LD2_yield.data')                                                                                                   
avg_current_bcm4a = B.get_data(fLD2, 'avg_current_bcm4a')    
avg_current_bcm4b = B.get_data(fLD2, 'avg_current_bcm4b')    

hs1x_rate_bcm4a = B.get_data(fLD2, 'hs1x_rate_bcm4a')
htrig1_rate_bcm4a = B.get_data(fLD2, 'htrig1_rate_bcm4a')  #3/4
htrig2_rate_bcm4a = B.get_data(fLD2, 'htrig2_rate_bcm4a')  #EL-REAL
htrig3_rate_bcm4a = B.get_data(fLD2, 'htrig3_rate_bcm4a')  #EL-CLEAN

hs1x_rate_bcm4b = B.get_data(fLD2, 'hs1x_rate_bcm4b')
htrig1_rate_bcm4b = B.get_data(fLD2, 'htrig1_rate_bcm4b')
htrig2_rate_bcm4b = B.get_data(fLD2, 'htrig2_rate_bcm4b')
htrig3_rate_bcm4b = B.get_data(fLD2, 'htrig3_rate_bcm4b')

#Convert to kHz
hs1x_rate_bcm4a = hs1x_rate_bcm4a / 1000.
htrig1_rate_bcm4a = htrig1_rate_bcm4a 
htrig2_rate_bcm4a = htrig2_rate_bcm4a 
htrig3_rate_bcm4a = htrig3_rate_bcm4a 

hs1x_rate_bcm4b = hs1x_rate_bcm4b  / 1000.
htrig1_rate_bcm4b = htrig1_rate_bcm4b 
htrig2_rate_bcm4b = htrig2_rate_bcm4b 
htrig3_rate_bcm4b = htrig3_rate_bcm4b 

cpuLT_bcm4a = B.get_data(fLD2, 'cpuLT_bcm4a')
tLT_bcm4a = B.get_data(fLD2, 'tLT_bcm4a')

cpuLT_bcm4b = B.get_data(fLD2, 'cpuLT_bcm4b')
tLT_bcm4b = B.get_data(fLD2, 'tLT_bcm4b')

h_eTrkEff_bcm4a = B.get_data(fLD2, 'h_eTrkEff_bcm4a')
h_eTrkEff_bcm4b = B.get_data(fLD2, 'h_eTrkEff_bcm4b')


#Plot S1X Rates
fig1 = B.pl.figure()
B.plot_exp(avg_current_bcm4a, hs1x_rate_bcm4a, color='black', marker='D', label='HMS S1X Rate (BCM4A)')
B.plot_exp(avg_current_bcm4b, hs1x_rate_bcm4b, color='black', markerfacecolor='none', marker='D', label='HMS S1X Rate (BCM4B)')


B.pl.title('Boiling Studies: Liquid Deuterium (LD2) S1X Rates')
B.pl.xlabel('Average Beam Current [$\mu$A]')
B.pl.ylabel('HMS Trigger Rates [kHz]')
B.pl.grid(True)
B.pl.legend()

#Plot Trigger Rates
fig2 = B.pl.figure()
B.plot_exp(avg_current_bcm4a, htrig1_rate_bcm4a, color='black', marker='^', label='HMS 3/4 Rate (BCM4A)')
B.plot_exp(avg_current_bcm4b, htrig1_rate_bcm4b, color='black', markerfacecolor='none', marker='^', label='HMS 3/4 Rate (BCM4B)')

B.plot_exp(avg_current_bcm4a, htrig2_rate_bcm4a, color='blue', marker='s', label='HMS EL-REAL Rate (BCM4A)')
B.plot_exp(avg_current_bcm4b, htrig2_rate_bcm4b, color='blue', markerfacecolor='none', marker='s', label='HMS EL-REAL Rate (BCM4B)')

B.plot_exp(avg_current_bcm4a, htrig3_rate_bcm4a, color='red', marker='o', label='HMS EL-CLEAN Rate (BCM4A)')
B.plot_exp(avg_current_bcm4b, htrig3_rate_bcm4b, color='red', markerfacecolor='none', marker='o', label='HMS EL-CLEAN Rate (BCM4B)')

B.pl.title('Boiling Studies: Liquid Deuterium (LD2) Trigger Rates')
B.pl.xlabel('Average Beam Current [$\mu$A]')
B.pl.ylabel('HMS Trigger Rates [Hz]')
B.pl.grid(True)
B.pl.legend()
B.pl.show()

#Plot Live Time
fig3 = B.pl.figure()
B.plot_exp(avg_current_bcm4a, cpuLT_bcm4a, color='black', marker='^', label='Computer Live Time (BCM4A)')
B.plot_exp(avg_current_bcm4b, cpuLT_bcm4b, color='black', markerfacecolor='none', marker='^', label='Computer Live Time (BCM4B)')
B.plot_exp(avg_current_bcm4a, tLT_bcm4a, color='red', marker='s', label='Total Live Time (BCM4A)')
B.plot_exp(avg_current_bcm4b, tLT_bcm4b, color='red', markerfacecolor='none', marker='s', label='Total Live Time (BCM4B)')

B.pl.title('Boiling Studies: Liquid Deuterium (LD2) Live Time')
B.pl.xlabel('Average Beam Current [$\mu$A]')
B.pl.ylabel('HMS Live Time')
B.pl.grid(True)
B.pl.legend()
B.pl.show()

#Plot Electron Tracking Efficiecny
fig4 = B.pl.figure()
B.plot_exp(avg_current_bcm4a, h_eTrkEff_bcm4a, color='blue', marker='v', label='HMS e- Tracking Efficiency (BCM4A)')
B.plot_exp(avg_current_bcm4b, h_eTrkEff_bcm4b, color='blue', marker='v', markerfacecolor='none', label='HMS e- Tracking Efficiency (BCM4B)')

B.pl.title('Boiling Studies: Liquid Deuterium (LD2) Tracking Efficiency')
B.pl.xlabel('Average Beam Current [$\mu$A]')
B.pl.ylabel('HMS e- Tracking Efficiency')
B.pl.grid(True)
B.pl.legend()
B.pl.show()
