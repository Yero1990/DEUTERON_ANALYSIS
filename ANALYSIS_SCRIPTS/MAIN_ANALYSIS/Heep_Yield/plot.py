import LT.box as B
import numpy as np
from LT.datafile import dfile

jra = dfile('./JRA_fofa/heep_yield_study.dat')
bosted = dfile('./Bosted_fofa/heep_yield_study.dat')

R_jra = jra['R']
R_err_jra = jra['R_err']
R_bosted = bosted['R']
R_err_bosted = bosted['R_err']
Q2 = np.array([4.0, 4.9, 2.87, 2.13])
B.plot_exp(Q2, R_jra, R_err_jra, marker='o', color='r', label='JRA')
B.plot_exp(Q2, R_bosted, R_err_bosted, marker='s', color='b', label='Bosted')
B.pl.ylim(0.75, 1.05)
B.pl.axhline(y=1.0, color='k', linestyle='--')

B.pl.legend()
B.pl.xlabel('$Q^{2} [GeV^{2}$]')
B.pl.ylabel('Yield Ratio')
B.pl.title('Heep Data Yield')
B.pl.show()
