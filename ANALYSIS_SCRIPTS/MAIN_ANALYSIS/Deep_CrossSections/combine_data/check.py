import LT.box as B
import numpy as np
from LT.datafile import dfile

jra = dfile('Em_final40MeV/redXsec_combined.txt')
bosted = dfile('Em_final40MeV_fofaBosted/redXsec_combined.txt')

pm = jra['yb']
thnq = jra['xb']

jra_red_dataXsec = jra['red_dataXsec_avg']
jra_red_pwiaXsec = jra['red_pwiaXsec_avg']
jra_red_fsiXsec = jra['red_fsiXsec_avg']

bosted_red_dataXsec = bosted['red_dataXsec_avg']
bosted_red_pwiaXsec = bosted['red_pwiaXsec_avg']
bosted_red_fsiXsec = bosted['red_fsiXsec_avg']


#print('ratio_data=',jra_red_dataXsec/bosted_red_dataXsec)
jra_ratio=jra_red_fsiXsec/jra_red_pwiaXsec
bosted_ratio=bosted_red_fsiXsec/bosted_red_pwiaXsec

B.plot_exp(pm[thnq==35], jra_red_pwiaXsec[thnq==35], marker='None', linestyle='--', color='b', label='JRA FOFA Param: Laget PWIA')
B.plot_exp(pm[thnq==35], jra_red_fsiXsec[thnq==35], marker='None', linestyle='-', color='b', label='JRA FSI')

B.plot_exp(pm[thnq==35], bosted_red_pwiaXsec[thnq==35], marker='None', linestyle='--', color='r', label='Bosted FOFA Param: Laget PWIA')
B.plot_exp(pm[thnq==35], bosted_red_fsiXsec[thnq==35], marker='None', linestyle='-', color='r', label='Bosted FSI')

B.pl.legend()
B.pl.yscale('Log')
B.pl.title('Reduced Cross Sections')
B.pl.xlabel(r'$P_{m} (GeV/c)$')
B.pl.ylabel(r'$\sigma_{red}$')

B.pl.show()
