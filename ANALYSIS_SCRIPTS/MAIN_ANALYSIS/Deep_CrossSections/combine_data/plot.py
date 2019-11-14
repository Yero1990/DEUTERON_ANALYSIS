import LT.box as B
from LT.datafile import dfile
import numpy as np

kin = dfile('Em_final40MeV/redXsec_combined.txt')

pm_avg = kin['pm_avg']
thnq_bin = kin['xb']
pm_bin = kin['yb']
R = kin['R']
R_err = kin['R_err']
R_avg = kin['R_v2']
R_avg_err = kin['R_v2_err']

B.plot_exp(pm_avg[thnq_bin==35], R[thnq_bin==35], R_err[thnq_bin==35], marker='o', color='k')
B.plot_exp(pm_avg[thnq_bin==35], R_avg[thnq_bin==35], R_avg_err[thnq_bin==35], marker='^', color='r')                                               

B.pl.xlim(0, 1)
B.pl.ylim(0,1)
B.pl.show()
