import LT.box as B
import numpy as np
import os
import sys


def plotEm_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots Ratio, Del, and sigDel vs. Pmiss
    #The Ratio is the (Xsec_totalSet - Xsec_subset) / sqrt(sigXsec_totalSet**2 - sigXsec_subset**2)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    f30_name="../datafiles/"+study_dir+"systematicsEm30MeV.txt"
    f40_name="../datafiles/"+study_dir+"systematicsEm40MeV.txt"
    f45_name="../datafiles/"+study_dir+"systematicsEm45MeV.txt"
    f50_name="../datafiles/"+study_dir+"systematicsEm50MeV.txt"
    f60_name="../datafiles/"+study_dir+"systematicsEm60MeV.txt"
    
    f30 = B.get_file(f30_name)
    f40 = B.get_file(f40_name)
    f45 = B.get_file(f45_name)
    f50 = B.get_file(f50_name)
    f60 = B.get_file(f60_name)
    
    thnq = B.get_data(f40, 'xb') 
    pm = B.get_data(f40, 'yb') 
    
    R80_em30 = B.get_data(f30,'R80')            ;  del80_em30 = B.get_data(f30,'del80')             ; sig_del80_em30 = B.get_data(f30,'sig_del80')          
    R580set1_em30 = B.get_data(f30,'R580set1')  ;  del580set1_em30 = B.get_data(f30,'del_580set1')  ; sig_del580set1_em30 = B.get_data(f30,'sig_del580set1')
    R580set2_em30 = B.get_data(f30,'R580set2')  ;  del580set2_em30 = B.get_data(f30,'del_580set2')  ; sig_del580set2_em30 = B.get_data(f30,'sig_del580set2')
    R750set1_em30 = B.get_data(f30,'R750set1')  ;  del750set1_em30 = B.get_data(f30,'del_750set1')  ; sig_del750set1_em30 = B.get_data(f30,'sig_del750set1')
    R750set2_em30 = B.get_data(f30,'R750set2')  ;  del750set2_em30 = B.get_data(f30,'del_750set2')  ; sig_del750set2_em30 = B.get_data(f30,'sig_del750set2')
    R750set3_em30 = B.get_data(f30,'R750set3')  ;  del750set3_em30 = B.get_data(f30,'del_750set3')  ; sig_del750set3_em30 = B.get_data(f30,'sig_del750set3')
    
    R80_em40 = B.get_data(f40,'R80')            ;  del80_em40 = B.get_data(f40,'del80')             ; sig_del80_em40 = B.get_data(f40,'sig_del80')          
    R580set1_em40 = B.get_data(f40,'R580set1')  ;  del580set1_em40 = B.get_data(f40,'del_580set1')  ; sig_del580set1_em40 = B.get_data(f40,'sig_del580set1')
    R580set2_em40 = B.get_data(f40,'R580set2')  ;  del580set2_em40 = B.get_data(f40,'del_580set2')  ; sig_del580set2_em40 = B.get_data(f40,'sig_del580set2')
    R750set1_em40 = B.get_data(f40,'R750set1')  ;  del750set1_em40 = B.get_data(f40,'del_750set1')  ; sig_del750set1_em40 = B.get_data(f40,'sig_del750set1')
    R750set2_em40 = B.get_data(f40,'R750set2')  ;  del750set2_em40 = B.get_data(f40,'del_750set2')  ; sig_del750set2_em40 = B.get_data(f40,'sig_del750set2')
    R750set3_em40 = B.get_data(f40,'R750set3')  ;  del750set3_em40 = B.get_data(f40,'del_750set3')  ; sig_del750set3_em40 = B.get_data(f40,'sig_del750set3')
    
    R80_em45 = B.get_data(f45,'R80')            ;  del80_em45 = B.get_data(f45,'del80')             ; sig_del80_em45 = B.get_data(f45,'sig_del80')          
    R580set1_em45 = B.get_data(f45,'R580set1')  ;  del580set1_em45 = B.get_data(f45,'del_580set1')  ; sig_del580set1_em45 = B.get_data(f45,'sig_del580set1')
    R580set2_em45 = B.get_data(f45,'R580set2')  ;  del580set2_em45 = B.get_data(f45,'del_580set2')  ; sig_del580set2_em45 = B.get_data(f45,'sig_del580set2')
    R750set1_em45 = B.get_data(f45,'R750set1')  ;  del750set1_em45 = B.get_data(f45,'del_750set1')  ; sig_del750set1_em45 = B.get_data(f45,'sig_del750set1')
    R750set2_em45 = B.get_data(f45,'R750set2')  ;  del750set2_em45 = B.get_data(f45,'del_750set2')  ; sig_del750set2_em45 = B.get_data(f45,'sig_del750set2')
    R750set3_em45 = B.get_data(f45,'R750set3')  ;  del750set3_em45 = B.get_data(f45,'del_750set3')  ; sig_del750set3_em45 = B.get_data(f45,'sig_del750set3')
    
    R80_em50 = B.get_data(f50,'R80')            ;  del80_em50 = B.get_data(f50,'del80')             ; sig_del80_em50 = B.get_data(f50,'sig_del80')          
    R580set1_em50 = B.get_data(f50,'R580set1')  ;  del580set1_em50 = B.get_data(f50,'del_580set1')  ; sig_del580set1_em50 = B.get_data(f50,'sig_del580set1')
    R580set2_em50 = B.get_data(f50,'R580set2')  ;  del580set2_em50 = B.get_data(f50,'del_580set2')  ; sig_del580set2_em50 = B.get_data(f50,'sig_del580set2')
    R750set1_em50 = B.get_data(f50,'R750set1')  ;  del750set1_em50 = B.get_data(f50,'del_750set1')  ; sig_del750set1_em50 = B.get_data(f50,'sig_del750set1')
    R750set2_em50 = B.get_data(f50,'R750set2')  ;  del750set2_em50 = B.get_data(f50,'del_750set2')  ; sig_del750set2_em50 = B.get_data(f50,'sig_del750set2')
    R750set3_em50 = B.get_data(f50,'R750set3')  ;  del750set3_em50 = B.get_data(f50,'del_750set3')  ; sig_del750set3_em50 = B.get_data(f50,'sig_del750set3')
    
    R80_em60 = B.get_data(f60,'R80')            ;  del80_em60 = B.get_data(f60,'del80')             ; sig_del80_em60 = B.get_data(f60,'sig_del80')          
    R580set1_em60 = B.get_data(f60,'R580set1')  ;  del580set1_em60 = B.get_data(f60,'del_580set1')  ; sig_del580set1_em60 = B.get_data(f60,'sig_del580set1')
    R580set2_em60 = B.get_data(f60,'R580set2')  ;  del580set2_em60 = B.get_data(f60,'del_580set2')  ; sig_del580set2_em60 = B.get_data(f60,'sig_del580set2')
    R750set1_em60 = B.get_data(f60,'R750set1')  ;  del750set1_em60 = B.get_data(f60,'del_750set1')  ; sig_del750set1_em60 = B.get_data(f60,'sig_del750set1')
    R750set2_em60 = B.get_data(f60,'R750set2')  ;  del750set2_em60 = B.get_data(f60,'del_750set2')  ; sig_del750set2_em60 = B.get_data(f60,'sig_del750set2')
    R750set3_em60 = B.get_data(f60,'R750set3')  ;  del750set3_em60 = B.get_data(f60,'del_750set3')  ; sig_del750set3_em60 = B.get_data(f60,'sig_del750set3')


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
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
            
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
            
        #Plot Delta vs. Pm,  where Delta = XSec (total_set) - Xsec (subset)
        fig2 = B.pl.figure(i+1)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], del80_em30[thnq==ithnq], color='black', marker='s', label='80 MeV Systematics (Em: 30 MeV)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_em30[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_em30[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_em30[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_em30[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_em30[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
        
        
        B.plot_exp(pm[thnq==ithnq], del80_em40[thnq==ithnq], color='red', marker='s', label='80 MeV Systematics (Em: 40 MeV)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_em40[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_em40[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_em40[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_em40[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_em40[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
        
        
        B.plot_exp(pm[thnq==ithnq], del80_em45[thnq==ithnq], color='green', marker='s', label='80 MeV Systematics (Em: 45 MeV)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_em45[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_em45[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_em45[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_em45[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_em45[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], del80_em50[thnq==ithnq], color='magenta', marker='s', label='80 MeV Systematics (Em: 50 MeV)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_em50[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_em50[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_em50[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_em50[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_em50[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], del80_em60[thnq==ithnq], color='blue', marker='s', label='80 MeV Systematics (Em: 60 MeV)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_em60[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_em60[thnq==ithnq], color='blue', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_em60[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_em60[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_em60[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )
        
        
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'$\Delta$')
        B.pl.ylim(-0.3e-4, 0.3e-4)
        B.pl.xlim(0, 2.0)

        B.pl.title(r'$\Delta, \theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
            
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/delta_sys_thnq%i.pdf'%(ithnq))
            

        #Plot Sig_{Delta} vs. Pm,  where Sig_{Delta} = sqrt(sigXSec**2 (total_set) - sigXsec**2 (subset))
        fig3 = B.pl.figure(i+2)
        B.pl.clf()

        B.plot_exp(pm[thnq==ithnq], sig_del80_em30[thnq==ithnq], color='black', marker='s', label='80 MeV Systematics (Em: 30 MeV)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_em30[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_em30[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_em30[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_em30[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_em30[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
            
        
        B.plot_exp(pm[thnq==ithnq], sig_del80_em40[thnq==ithnq], color='red', marker='s', label='80 MeV Systematics (Em: 40 MeV)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_em40[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_em40[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_em40[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_em40[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_em40[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
            
            
        B.plot_exp(pm[thnq==ithnq], sig_del80_em45[thnq==ithnq], color='green', marker='s', label='80 MeV Systematics (Em: 45 MeV)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_em45[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_em45[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_em45[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_em45[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_em45[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], sig_del80_em50[thnq==ithnq], color='magenta', marker='s', label='80 MeV Systematics (Em: 50 MeV)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_em50[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_em50[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_em50[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_em50[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_em50[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], sig_del80_em60[thnq==ithnq], color='blue', marker='s', label='80 MeV Systematics (Em: 60 MeV)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_em60[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_em60[thnq==ithnq], color='blue', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_em60[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_em60[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_em60[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )
            
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'$\sigma_{\Delta}$')
        B.pl.ylim(-0.3e-4, 0.3e-4)
        B.pl.xlim(0, 2.0)
            
            
        B.pl.title(r'$\sigma_{\Delta}, \theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/sigDelta_sys_thnq%i.pdf'%(ithnq))


#-------------------------------------------------------------------------------------------------

def plotZtar_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots them vs. Pmiss (for ZtarDifference Systematics)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fz1_name="../datafiles/"+study_dir+"systematicsZtar2.0cm.txt"
    fz2_name="../datafiles/"+study_dir+"systematicsZtar1.5cm.txt"
    fz3_name="../datafiles/"+study_dir+"systematicsZtar1.0cm.txt"
    fz4_name="../datafiles/"+study_dir+"systematicsZtar0.5cm.txt"
    
    fz1 = B.get_file(fz1_name)
    fz2 = B.get_file(fz2_name)
    fz3 = B.get_file(fz3_name)
    fz4 = B.get_file(fz4_name)
        
    thnq = B.get_data(fz1, 'xb') 
    pm = B.get_data(fz1, 'yb') 

    #Ztar Diff Cut: 2.0 cm (2p0)
    R80_z2p0 = B.get_data(fz1,'R80')            ;  del80_z2p0 = B.get_data(fz1,'del80')             ; sig_del80_z2p0 = B.get_data(fz1,'sig_del80')          
    R580set1_z2p0 = B.get_data(fz1,'R580set1')  ;  del580set1_z2p0 = B.get_data(fz1,'del_580set1')  ; sig_del580set1_z2p0 = B.get_data(fz1,'sig_del580set1')
    R580set2_z2p0 = B.get_data(fz1,'R580set2')  ;  del580set2_z2p0 = B.get_data(fz1,'del_580set2')  ; sig_del580set2_z2p0 = B.get_data(fz1,'sig_del580set2')
    R750set1_z2p0 = B.get_data(fz1,'R750set1')  ;  del750set1_z2p0 = B.get_data(fz1,'del_750set1')  ; sig_del750set1_z2p0 = B.get_data(fz1,'sig_del750set1')
    R750set2_z2p0 = B.get_data(fz1,'R750set2')  ;  del750set2_z2p0 = B.get_data(fz1,'del_750set2')  ; sig_del750set2_z2p0 = B.get_data(fz1,'sig_del750set2')
    R750set3_z2p0 = B.get_data(fz1,'R750set3')  ;  del750set3_z2p0 = B.get_data(fz1,'del_750set3')  ; sig_del750set3_z2p0 = B.get_data(fz1,'sig_del750set3')
    #1.5 cm
    R80_z1p5 = B.get_data(fz2,'R80')            ;  del80_z1p5 = B.get_data(fz2,'del80')             ; sig_del80_z1p5 = B.get_data(fz2,'sig_del80')          
    R580set1_z1p5 = B.get_data(fz2,'R580set1')  ;  del580set1_z1p5 = B.get_data(fz2,'del_580set1')  ; sig_del580set1_z1p5 = B.get_data(fz2,'sig_del580set1')
    R580set2_z1p5 = B.get_data(fz2,'R580set2')  ;  del580set2_z1p5 = B.get_data(fz2,'del_580set2')  ; sig_del580set2_z1p5 = B.get_data(fz2,'sig_del580set2')
    R750set1_z1p5 = B.get_data(fz2,'R750set1')  ;  del750set1_z1p5 = B.get_data(fz2,'del_750set1')  ; sig_del750set1_z1p5 = B.get_data(fz2,'sig_del750set1')
    R750set2_z1p5 = B.get_data(fz2,'R750set2')  ;  del750set2_z1p5 = B.get_data(fz2,'del_750set2')  ; sig_del750set2_z1p5 = B.get_data(fz2,'sig_del750set2')
    R750set3_z1p5 = B.get_data(fz2,'R750set3')  ;  del750set3_z1p5 = B.get_data(fz2,'del_750set3')  ; sig_del750set3_z1p5 = B.get_data(fz2,'sig_del750set3')
    #1.0 cm
    R80_z1p0 = B.get_data(fz3,'R80')            ;  del80_z1p0 = B.get_data(fz3,'del80')             ; sig_del80_z1p0 = B.get_data(fz3,'sig_del80')          
    R580set1_z1p0 = B.get_data(fz3,'R580set1')  ;  del580set1_z1p0 = B.get_data(fz3,'del_580set1')  ; sig_del580set1_z1p0 = B.get_data(fz3,'sig_del580set1')
    R580set2_z1p0 = B.get_data(fz3,'R580set2')  ;  del580set2_z1p0 = B.get_data(fz3,'del_580set2')  ; sig_del580set2_z1p0 = B.get_data(fz3,'sig_del580set2')
    R750set1_z1p0 = B.get_data(fz3,'R750set1')  ;  del750set1_z1p0 = B.get_data(fz3,'del_750set1')  ; sig_del750set1_z1p0 = B.get_data(fz3,'sig_del750set1')
    R750set2_z1p0 = B.get_data(fz3,'R750set2')  ;  del750set2_z1p0 = B.get_data(fz3,'del_750set2')  ; sig_del750set2_z1p0 = B.get_data(fz3,'sig_del750set2')
    R750set3_z1p0 = B.get_data(fz3,'R750set3')  ;  del750set3_z1p0 = B.get_data(fz3,'del_750set3')  ; sig_del750set3_z1p0 = B.get_data(fz3,'sig_del750set3')
    #0.5 cm
    R80_z0p5 = B.get_data(fz4,'R80')            ;  del80_z0p5 = B.get_data(fz4,'del80')             ; sig_del80_z0p5 = B.get_data(fz4,'sig_del80')          
    R580set1_z0p5 = B.get_data(fz4,'R580set1')  ;  del580set1_z0p5 = B.get_data(fz4,'del_580set1')  ; sig_del580set1_z0p5 = B.get_data(fz4,'sig_del580set1')
    R580set2_z0p5 = B.get_data(fz4,'R580set2')  ;  del580set2_z0p5 = B.get_data(fz4,'del_580set2')  ; sig_del580set2_z0p5 = B.get_data(fz4,'sig_del580set2')
    R750set1_z0p5 = B.get_data(fz4,'R750set1')  ;  del750set1_z0p5 = B.get_data(fz4,'del_750set1')  ; sig_del750set1_z0p5 = B.get_data(fz4,'sig_del750set1')
    R750set2_z0p5 = B.get_data(fz4,'R750set2')  ;  del750set2_z0p5 = B.get_data(fz4,'del_750set2')  ; sig_del750set2_z0p5 = B.get_data(fz4,'sig_del750set2')
    R750set3_z0p5 = B.get_data(fz4,'R750set3')  ;  del750set3_z0p5 = B.get_data(fz4,'del_750set3')  ; sig_del750set3_z0p5 = B.get_data(fz4,'sig_del750set3')
        

    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print(ithnq)
        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        #|Ztar| < 2.0 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z2p0[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 2.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_z2p0[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z2p0[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z2p0[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_z2p0[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_z2p0[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 1.5 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z1p5[thnq==ithnq], color='red', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_z1p5[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z1p5[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z1p5[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_z1p5[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_z1p5[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
        #|Ztar| < 1.0 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z1p0[thnq==ithnq], color='green', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_z1p0[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z1p0[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z1p0[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_z1p0[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_z1p0[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 0.5 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z0p5[thnq==ithnq], color='magenta', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 0.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_z0p5[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z0p5[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z0p5[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_z0p5[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_z0p5[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
            
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
            
        #Plot Delta vs. Pm,  where Delta = XSec (total_set) - Xsec (subset)
        fig2 = B.pl.figure(i+1)
        B.pl.clf()
        #|Ztar| < 2.0 cm cut
        B.plot_exp(pm[thnq==ithnq], del80_z2p0[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 2.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_z2p0[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_z2p0[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_z2p0[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_z2p0[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_z2p0[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 1.5 cm cut
        B.plot_exp(pm[thnq==ithnq], del80_z1p5[thnq==ithnq], color='red', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_z1p5[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_z1p5[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_z1p5[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_z1p5[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_z1p5[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
        #|Ztar| < 1.0 cm cut
        B.plot_exp(pm[thnq==ithnq], del80_z1p0[thnq==ithnq], color='green', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_z1p0[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_z1p0[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_z1p0[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_z1p0[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_z1p0[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 0.5 cm cut
        B.plot_exp(pm[thnq==ithnq], del80_z0p5[thnq==ithnq], color='magenta', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 0.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], del580set1_z0p5[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del580set2_z0p5[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set1_z0p5[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set2_z0p5[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], del750set3_z0p5[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'$\Delta$')
        B.pl.ylim(-0.3e-4, 0.3e-4)
        B.pl.xlim(0, 2.0)
        
        
        B.pl.title(r'$\Delta, \theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/delta_sys_thnq%i.pdf'%(ithnq))
            

        #Plot Sig_{Delta} vs. Pm,  where Sig_{Delta} = sqrt(sigXSec**2 (total_set) - sigXsec**2 (subset))
        fig3 = B.pl.figure(i+2)
        B.pl.clf()
        #|Ztar| < 2.0 cm cut
        B.plot_exp(pm[thnq==ithnq], sig_del80_z2p0[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 2.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_z2p0[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_z2p0[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_z2p0[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_z2p0[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_z2p0[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 1.5 cm cut
        B.plot_exp(pm[thnq==ithnq], sig_del80_z1p5[thnq==ithnq], color='red', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_z1p5[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_z1p5[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_z1p5[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_z1p5[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_z1p5[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
        #|Ztar| < 1.0 cm cut
        B.plot_exp(pm[thnq==ithnq], sig_del80_z1p0[thnq==ithnq], color='green', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.0 cm)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_z1p0[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_z1p0[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_z1p0[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_z1p0[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_z1p0[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        #|Ztar| < 0.5 cm cut
        B.plot_exp(pm[thnq==ithnq], sig_del80_z0p5[thnq==ithnq], color='magenta', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 0.5 cm)' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set1_z0p5[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del580set2_z0p5[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set1_z0p5[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set2_z0p5[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], sig_del750set3_z0p5[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
        
        
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'$\sigma_{\Delta}$')
        B.pl.ylim(-0.3e-4, 0.3e-4)
        B.pl.xlim(0, 2.0)
            
            
        B.pl.title(r'$\sigma_{\Delta}, \theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/sigDelta_sys_thnq%i.pdf'%(ithnq))
