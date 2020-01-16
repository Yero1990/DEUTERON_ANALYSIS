import numpy as np
import LT.box as B
from LT.datafile import dfile


jra80 = dfile('Em_final40MeV/pm80_fsi_norad_avgkin.txt')
jra580 = dfile('Em_final40MeV/pm580_fsi_norad_avgkin_set1.txt')
jra750 = dfile('Em_final40MeV/pm750_fsi_norad_avgkin_set1.txt')

pm_80 = jra80['yb']
thnq_80 = jra80['xb']
Q2_80 = jra80['Q2_calc']
q_80 = jra80['q_lab']
thpq_80 = jra80['theta_pq_calc']
pm_580 = jra580['yb']
thnq_580 = jra580['xb']
Q2_580 = jra580['Q2_calc']
q_580 = jra580['q_lab']
thpq_580 = jra580['theta_pq_calc']
pm_750 = jra750['yb']
thnq_750 = jra750['xb']
Q2_750 = jra750['Q2_calc']
q_750 = jra750['q_lab']
thpq_750 = jra750['theta_pq_calc']

#---PLOT thpq vs. Pm----
#B.plot_exp(pm_80[thnq_80==35], thpq_80[thnq_80==35], marker='o', color='r', logy=False, label=r' $\theta_{nq}=35^{o}$')
#B.plot_exp(pm_580[thnq_580==35], thpq_580[thnq_580==35], marker='^', color='r', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==35], thpq_750[thnq_750==35], marker='s', color='r', logy=False, label=r'')
#B.plot_exp(pm_80[thnq_80==45], thpq_80[thnq_80==45], marker='o', color='b', logy=False, label=r' $\theta_{nq}=45^{o}$')
#B.plot_exp(pm_580[thnq_580==45], thpq_580[thnq_580==45], marker='^', color='b', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==45], thpq_750[thnq_750==45], marker='s', color='b', logy=False, label=r'')
#B.plot_exp(pm_80[thnq_80==75], thpq_80[thnq_80==75], marker='o', color='g', logy=False, label=r' $\theta_{nq}=75^{o}$')
#B.plot_exp(pm_580[thnq_580==75], thpq_580[thnq_580==75], marker='^', color='g', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==75], thpq_750[thnq_750==75], marker='s', color='g', logy=False, label=r'')

#B.pl.title(r'$\theta_{pq} vs. P_{r}$')
#B.pl.xlabel(r'$P_{r}$ (GeV/c)$')
#B.pl.ylabel(r'$\theta_{pq}$ (deg)')
#B.pl.legend()
#B.pl.show()

#---PLOT Q2 vs. Pm----
#B.plot_exp(pm_80[thnq_80==35], Q2_80[thnq_80==35], marker='o', color='r', logy=False, label=r' $\theta_{nq}=35^{o}$')
#B.plot_exp(pm_580[thnq_580==35], Q2_580[thnq_580==35], marker='^', color='r', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==35], Q2_750[thnq_750==35], marker='s', color='r', logy=False, label=r'')
#B.plot_exp(pm_80[thnq_80==45], Q2_80[thnq_80==45], marker='o', color='b', logy=False, label=r' $\theta_{nq}=45^{o}$')
#B.plot_exp(pm_580[thnq_580==45], Q2_580[thnq_580==45], marker='^', color='b', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==45], Q2_750[thnq_750==45], marker='s', color='b', logy=False, label=r'')
#B.plot_exp(pm_80[thnq_80==75], Q2_80[thnq_80==75], marker='o', color='g', logy=False, label=r' $\theta_{nq}=75^{o}$')
#B.plot_exp(pm_580[thnq_580==75], Q2_580[thnq_580==75], marker='^', color='g', logy=False, label=r'')
#B.plot_exp(pm_750[thnq_750==75], Q2_750[thnq_750==75], marker='s', color='g', logy=False, label=r'')

#B.pl.title(r'$Q^{2} vs. P_{r}$')
#B.pl.xlabel(r'$P_{r}$ (GeV/c)$')
#B.pl.ylabel(r'$Q^{2}$ (GeV^{2})')
#B.pl.legend()
#B.pl.show()

#---PLOT q_lab vs. Pm----
B.plot_exp(pm_80[thnq_80==35], q_80[thnq_80==35], marker='o', color='r', logy=False, label=r' $\theta_{nq}=35^{o}$')
B.plot_exp(pm_580[thnq_580==35], q_580[thnq_580==35], marker='^', color='r', logy=False, label=r'')
B.plot_exp(pm_750[thnq_750==35], q_750[thnq_750==35], marker='s', color='r', logy=False, label=r'')
B.plot_exp(pm_80[thnq_80==45], q_80[thnq_80==45], marker='o', color='b', logy=False, label=r' $\theta_{nq}=45^{o}$')
B.plot_exp(pm_580[thnq_580==45], q_580[thnq_580==45], marker='^', color='b', logy=False, label=r'')
B.plot_exp(pm_750[thnq_750==45], q_750[thnq_750==45], marker='s', color='b', logy=False, label=r'')
B.plot_exp(pm_80[thnq_80==75], q_80[thnq_80==75], marker='o', color='g', logy=False, label=r' $\theta_{nq}=75^{o}$')
B.plot_exp(pm_580[thnq_580==75], q_580[thnq_580==75], marker='^', color='g', logy=False, label=r'')
B.plot_exp(pm_750[thnq_750==75], q_750[thnq_750==75], marker='s', color='g', logy=False, label=r'')

B.pl.title(r'$q$ vs. $P_{r}$')
B.pl.xlabel(r'$P_{r}$ (GeV/c)$')
B.pl.ylabel(r'$q_{lab}$ (GeV)')
B.pl.legend()
B.pl.show()

'''
thpq80 = jra80['theta_pq_calc']
thpq580_set1 = jra580_set1['theta_pq_calc']
thpq580_set2 = jra580_set2['theta_pq_calc']
thpq750_set1 = jra750_set1['theta_pq_calc']
thpq750_set2 = jra750_set2['theta_pq_calc']
thpq750_set3 = jra750_set3['theta_pq_calc']

print('min Pm:',min(pm[thnq==75]))
print('min thpq 80(set1):',thpq80[thnq==75])
print('min thpq 580(set1):',min(thpq580_set1[thnq==75]))
print('min thpq 580(set2):',min(thpq580_set2[thnq==75]))
print('min thpq 750(set1):',min(thpq750_set1[thnq==75]))
print('min thpq 750(set2):',min(thpq750_set2[thnq==75]))
print('min thpq 750(set3):',min(thpq750_set3[thnq==75]))

#--------------
print('max Pm:',max(pm[thnq==75]))
print('max thpq 80(set1):',max(thpq80[thnq==75]))
print('max thpq 580(set1):',max(thpq580_set1[thnq==75]))
print('max thpq 580(set2):',max(thpq580_set2[thnq==75]))
print('max thpq 750(set1):',max(thpq750_set1[thnq==75]))
print('max thpq 750(set2):',max(thpq750_set2[thnq==75]))
print('max thpq 750(set3):',max(thpq750_set3[thnq==75]))


jraKsig_cc1 = jra['Ksig_cc1']
bostedKsig_cc1 = bosted['Ksig_cc1']

jraGEp = jra['GEp']
jraGMp = jra['GMp']

bostedGEp = bosted['GEp']
bostedGMp = bosted['GMp']

B.plot_exp(Q2[thnq==35], jraGEp[thnq==35], marker='s', color='b', logy=True, label='GEp (JRA)')
B.plot_exp(Q2[thnq==35], jraGMp[thnq==35], marker='s', color='r', logy=True, label='GMp (JRA)')

B.plot_exp(Q2[thnq==35], bostedGEp[thnq==35], marker='o', color='b', logy=True, label='GEp (Bosted)')
B.plot_exp(Q2[thnq==35], bostedGMp[thnq==35], marker='o', color='r', logy=True, label='GMp (Bosted)')

B.pl.legend()
B.pl.xlabel('Q2 [MeV$^{2}$]')
B.pl.title(r'Form Factor Parametrization At $Q^{2}$ of $\theta_{nq}$=35$^{o}$')

B.pl.show()

#------------------
B.plot_exp(pm[thnq==35], jraKsig_cc1[thnq==35], marker='s', color='b', logy=False, label='K$f_{rec}\sigma_{cc1}$ (JRA)')
B.plot_exp(pm[thnq==35], bostedKsig_cc1[thnq==35], marker='o', color='r', logy=False, label='K$f_{rec}\sigma_{cc1}$ (Bosted)')
B.pl.xlabel('$P_{m} [GeV/c]$')
B.pl.ylabel('K$f_{rec}\sigma_{cc1}$')
B.pl.legend()
B.pl.show()

B.plot_exp(pm[thnq==35], th_pq_calc[thnq==35], marker='o', color='r', logy=False, label=r'$\theta_{pq}$, $\theta_{nq}=35^{o}$ calc')
B.plot_exp(pm[thnq==45], th_pq_calc[thnq==45], marker='^', color='b', logy=False, label=r'$\theta_{pq}$, $\theta_{nq}=45^{o}$ calc')
B.plot_exp(pm[thnq==75], th_pq_calc[thnq==75], marker='s', color='g', logy=False, label=r'$\theta_{pq}$, $\theta_{nq}=75^{o}$ calc')

B.pl.legend()
B.pl.show()
'''
