import LT.box as B
import numpy as np


f1 = B.get_file('pm80_redXsec.txt')
f2 = B.get_file('pm580_redXsec.txt')
f3 = B.get_file('pm750_redXsec.txt')

pm80 = B.get_data(f1, 'yb')
pm580 = B.get_data(f2, 'yb')
pm750 = B.get_data(f3, 'yb')

thnq80 = B.get_data(f1, 'xb')
thnq580 = B.get_data(f2, 'xb')
thnq750 = B.get_data(f3, 'xb')

red_dataXsec_80 = B.get_data(f1, 'red_dataXsec')
red_dataXsec_err_80 = B.get_data(f1, 'red_dataXsec_err')

red_dataXsec_err_580 = B.get_data(f2, 'red_dataXsec_err')
red_dataXsec_580 = B.get_data(f2, 'red_dataXsec')

red_dataXsec_750 = B.get_data(f3, 'red_dataXsec')
red_dataXsec_err_750 = B.get_data(f3, 'red_dataXsec_err')


#B.plot_exp(pm80[thnq80==60], red_dataXsec_80[thnq80==60], red_dataXsec_err_80[thnq80==60], color='r', marker='o', label='DATA (80 MeV)', logy=True)
#B.plot_exp(pm580[thnq580==50], red_dataXsec_580[thnq580==50], red_dataXsec_err_580[thnq580==50], color='b', marker='^', label='DATA (580 MeV)', logy=True)
#B.plot_exp(pm750[thnq750==60], red_dataXsec_750[thnq750==60], red_dataXsec_err_750[thnq750==60], color='g', marker='s', label='DATA (750 MeV)', logy=True)

B.pl.legend()
B.pl.show()
