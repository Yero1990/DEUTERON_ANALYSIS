#This code reads in the binInfo_*.txt files containing the Pm yield ratios and 
#determines whether the difference between tight/nominal and loose/nominal cuts
#is significant contribution to systematic.

import LT.box as B
import numpy as np
import matplotlib.pyplot as plt

f_Em_nominal = B.get_file('binInfo_sysEm_nominal.txt')
f_Em_loose = B.get_file('binInfo_sysEm_loose.txt')
f_Em_tight = B.get_file('binInfo_sysEm_tight.txt')

xval_nominal = B.get_data(f_Em_nominal, 'xbin')
pm_nominal = B.get_data(f_Em_nominal, 'binCont')          #Pm yield ratio for nominal Em cut
sig_pm_nominal = B.get_data(f_Em_nominal, 'binCont_err')  #Pm yield ratio err. for nominal Em cut    

xval_loose = B.get_data(f_Em_loose, 'xbin')
pm_loose = B.get_data(f_Em_loose, 'binCont') 
sig_pm_loose = B.get_data(f_Em_loose, 'binCont_err')

xval_tight = B.get_data(f_Em_tight, 'xbin')
pm_tight = B.get_data(f_Em_tight, 'binCont') 
sig_pm_tight = B.get_data(f_Em_tight, 'binCont_err')

#PLot the Yield Ratio for nominal, loose, and tight cuts on the kin. variable. Overlayed
B.plot_exp(xval_nominal, pm_nominal, sig_pm_nominal, color='black', marker='o', label=r'$E_{miss}$: nominal cut')
B.plot_exp(xval_loose, pm_loose, sig_pm_loose, color='blue', marker='^', label=r'$E_{miss}$: loose cut')
B.plot_exp(xval_tight, pm_tight, sig_pm_tight, color='red', marker='s', label=r'$E_{miss}$: tight cut')
B.pl.xlabel(r'Missing Momentum, $P_{m}$ [GeV]')
B.pl.ylabel('Data/SIMC Yield Ratio')
B.pl.title(r'Yield Ratio: Missing Energy ($E_{miss}$) Systematics Studies')
B.pl.legend()
B.pl.xlim(0, 0.350)
B.pl.ylim(0, 2.)

B.pl.show("same")

'''

:: Calculate whether the difference observed in the ratios is significant. Use Roger Barlow's approach
:: Are the Systematic Effects Significant?   Use Roger Barlow approach in: Systematics: Facts and Fictions

(Consider a measurement done two different ways (e.g. apply different cuts). Let the measurements and its uncertainty be:
(a1, sig_1) and (a2, sig_2) where 'sig' is the error bar or standard deviation of the measurement 'a'.
The difference, delta = a1 - a2 then has an associated uncertainty, (sig_delta)**2 = sig_1**2 - sig_2**2  (this is the difference of their variances)
Then, if delta / sig_delta > 2 (or the measurement difference is greater than two standard deviations) then it is considere a significant difference.
'''

delta_loose = pm_nominal - pm_loose
sig_delta_loose = np.sqrt(np.abs(sig_pm_nominal**2 - sig_pm_loose**2))
ratio_l = delta_loose / sig_delta_loose

delta_tight = pm_nominal - pm_tight
sig_delta_tight = np.sqrt(np.abs(sig_pm_nominal**2 - sig_pm_tight**2))
ratio_t = delta_tight / sig_delta_tight

print('delta_loose = ',delta_loose)
print('sig_delta_loose = ',sig_delta_loose)

print('delta_tight = ',delta_tight)
print('sig_delta_tight = ',sig_delta_tight)

B.plot_exp(xval_nominal, delta_loose, sig_delta_loose, marker='^', color='blue', label=r'$\Delta_{loose} \pm \sqrt{|\sigma^{2}_{nominal} - \sigma^{2}_{loose}|}$')
B.plot_exp(xval_nominal, delta_tight, sig_delta_tight, marker='s', color='red', label=r'$\Delta_{tight} \pm \sqrt{|\sigma^{2}_{nominal} - \sigma^{2}_{tight}|}$')
B.pl.legend()
B.pl.xlim(0, 0.350)
B.pl.ylim(-1, 1)
B.pl.show()


#Plot the ratio of the delta / sig_delta. If |delta / sig_delta|<2 ( within 2) standard deviations, then it is insignificant contribution to systematics
B.plot_exp(xval_nominal, ratio_l, marker='^', color='blue', label=r'$ \Delta_{loose} / \sigma_{\Delta_{loose}}$' )
B.plot_exp(xval_nominal, ratio_t, marker='s', color='red', label=r'$ \Delta_{tight} / \sigma_{\Delta_{tight}}$')
B.pl.legend()
B.pl.ylim(-20, 20)
plt.axhline(y=-2, color='black', linestyle='--')
plt.axhline(y= 2, color='black', linestyle='--')
B.pl.show()
