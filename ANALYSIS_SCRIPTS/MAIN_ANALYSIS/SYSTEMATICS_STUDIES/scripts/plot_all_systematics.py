import numpy as np
import LT.box as B
import os
import sys
from sys import argv

#Script that reads the systematics datafiles produced, and plots Roger Barlow's Ratio, R vs. pm

#check if directory to store systematics exists, else creates it.
dir_name = "../full_systematics_plots/"
if not os.path.exists(dir_name):
    os.makedirs(dir_name)
        
#Load the various Emiss systematics (each is compared to the nominal 40 MeV)
#f30_name="../datafiles/noBC_50perc_stats/systematicsEm30MeV.txt"
#f40_name="../datafiles/noBC_50perc_stats/systematicsEm40MeV.txt"
#f45_name="../datafiles/noBC_50perc_stats/systematicsEm45MeV.txt"
#f50_name="../datafiles/noBC_50perc_stats/systematicsEm50MeV.txt"
#f60_name="../datafiles/noBC_50perc_stats/systematicsEm60MeV.txt"

f30_name="../datafiles/systematicsEm30MeV.txt"
f40_name="../datafiles/systematicsEm40MeV.txt"
f45_name="../datafiles/systematicsEm45MeV.txt"
f50_name="../datafiles/systematicsEm50MeV.txt"
f60_name="../datafiles/systematicsEm60MeV.txt"

f30 = B.get_file(f30_name)
f40 = B.get_file(f40_name)
f45 = B.get_file(f45_name)
f50 = B.get_file(f50_name)
f60 = B.get_file(f60_name)

thnq = B.get_data(f40, 'xb') 
pm = B.get_data(f40, 'yb') 

R80_em30 = B.get_data(f30,'R80')
R580set1_em30 = B.get_data(f30,'R580set1')
R580set2_em30 = B.get_data(f30,'R580set2')
R750set1_em30 = B.get_data(f30,'R750set1')
R750set2_em30 = B.get_data(f30,'R750set2')
R750set3_em30 = B.get_data(f30,'R750set3')

R80_em40 = B.get_data(f40,'R80')
R580set1_em40 = B.get_data(f40,'R580set1')
R580set2_em40 = B.get_data(f40,'R580set2')
R750set1_em40 = B.get_data(f40,'R750set1')
R750set2_em40 = B.get_data(f40,'R750set2')
R750set3_em40 = B.get_data(f40,'R750set3')

R80_em45 = B.get_data(f45,'R80')
R580set1_em45 = B.get_data(f45,'R580set1')
R580set2_em45 = B.get_data(f45,'R580set2')
R750set1_em45 = B.get_data(f45,'R750set1')
R750set2_em45 = B.get_data(f45,'R750set2')
R750set3_em45 = B.get_data(f45,'R750set3')

R80_em50 = B.get_data(f50,'R80')
R580set1_em50 = B.get_data(f50,'R580set1')
R580set2_em50 = B.get_data(f50,'R580set2')
R750set1_em50 = B.get_data(f50,'R750set1')
R750set2_em50 = B.get_data(f50,'R750set2')
R750set3_em50 = B.get_data(f50,'R750set3')

R80_em60 = B.get_data(f60,'R80')
R580set1_em60 = B.get_data(f60,'R580set1')
R580set2_em60 = B.get_data(f60,'R580set2')
R750set1_em60 = B.get_data(f60,'R750set1')
R750set2_em60 = B.get_data(f60,'R750set2')
R750set3_em60 = B.get_data(f60,'R750set3')


#Define theta_nq bins to plot
thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

#Loop over theta_nq angle bins
for i, ithnq in enumerate(thnq_arr):
    print(ithnq)
        
    th_nq_min = ithnq - 5
    th_nq_max = ithnq + 5
        
    fig1 = B.pl.figure(i)
    B.pl.clf()
    
    B.plot_exp(pm[thnq==ithnq], R80_em30[thnq==ithnq], color='black', marker='s', label='80 MeV Systematics (Em: 30 MeV)' )
    B.plot_exp(pm[thnq==ithnq], R580set1_em30[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R580set2_em30[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set1_em30[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set2_em30[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set3_em30[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
    
    B.plot_exp(pm[thnq==ithnq], R80_em40[thnq==ithnq], color='red', marker='s', label='80 MeV Systematics (Em: 40 MeV)' )
    B.plot_exp(pm[thnq==ithnq], R580set1_em40[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R580set2_em40[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set1_em40[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set2_em40[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set3_em40[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    

    
    B.plot_exp(pm[thnq==ithnq], R80_em45[thnq==ithnq], color='green', marker='s', label='80 MeV Systematics (Em: 45 MeV)' )
    B.plot_exp(pm[thnq==ithnq], R580set1_em45[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R580set2_em45[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set1_em45[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set2_em45[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set3_em45[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )

    B.plot_exp(pm[thnq==ithnq], R80_em50[thnq==ithnq], color='magenta', marker='s', label='80 MeV Systematics (Em: 50 MeV)' )
    B.plot_exp(pm[thnq==ithnq], R580set1_em50[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R580set2_em50[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set1_em50[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set2_em50[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set3_em50[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )

    B.plot_exp(pm[thnq==ithnq], R80_em60[thnq==ithnq], color='blue', marker='s', label='80 MeV Systematics (Em: 60 MeV)' )
    B.plot_exp(pm[thnq==ithnq], R580set1_em60[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R580set2_em60[thnq==ithnq], color='blue', marker='^', label='580 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set1_em60[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set2_em60[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
    B.plot_exp(pm[thnq==ithnq], R750set3_em60[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )
    

    B.pl.xlabel('Neutron Recoil Momenta [GeV]')
    B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
    B.pl.ylim(-10, 10)
    B.pl.xlim(0, 2.0)

    B.pl.axhline(y=-2., color='black', linestyle='--')
    B.pl.axhline(y=2., color='black', linestyle='--')
       
    B.pl.axhline(y=-4., color='black', linestyle='-')
    B.pl.axhline(y=4., color='black', linestyle='-')
    
    B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within 50 %%)'%(th_nq_min, th_nq_max))
    
    B.pl.legend(loc='upper right', fontsize='xx-small')
    
    B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))

    fig2 = B.pl.figure(i+1)
    B.pl.clf()
