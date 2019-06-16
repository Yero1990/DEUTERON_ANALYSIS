import LT.box as B
import numpy as np

f = B.get_file('pm580_laget_set1.txt')

thnq = B.get_data(f, 'xb')
pm = B.get_data(f, 'yb')

dataXsec = B.get_data(f, 'dataXsec')
dataXsec_err = B.get_data(f, 'dataXsec_err')

fsiXsec = B.get_data(f, 'fsiXsec')
fsiXsec_err = B.get_data(f, 'fsiXsec_err')

pwiaXsec = B.get_data(f, 'pwiaXsec')
pwiaXsec_err = B.get_data(f, 'pwiaXsec_err')


print ('pm = ',pm[thnq==40.], ' thnq = ', thnq[thnq==40], 'dataXsec = ', dataXsec[thnq==40], ' dataXsec_err = ', dataXsec_err[thnq==40])

B.plot_exp(pm[thnq==40.], dataXsec[thnq==40.], dataXsec_err[thnq==40.], color='black', marker='s', logy=True)
#B.plot_exp(pm[thnq==thnq_bin], fsiXsec[thnq==thnq_bin], fsiXsec_err[thnq==thnq_bin], color='red', marker='s', label='FSI')
#B.plot_exp(pm[thnq==thnq_bin], pwiaXsec[thnq==thnq_bin], pwiaXsec_err[thnq==thnq_bin], color='blue', marker='s', label='PWIA')
#B.pl.yscale('log')

#B.pl.legend()
B.pl.show()
