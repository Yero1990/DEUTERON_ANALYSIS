import LT.box as B
import numpy as np
import os
import sys

def plotEm_syst(study='', stats_thrs=0.):

    print('Plotting Systematics on Emiss')

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
        print('theta_nq:',ithnq,' deg')
        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
    
        B.plot_exp(pm[thnq==ithnq], R80_em30[thnq==ithnq], color='black', marker='s', label='80 MeV Systematics (Em: 30 MeV)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_em30[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_em30[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_em30[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_em30[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_em30[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], R80_em40[thnq==ithnq], color='red', marker='s', label='80 MeV Systematics (Em: 40 MeV)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_em40[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_em40[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_em40[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_em40[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_em40[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
        
        
        B.plot_exp(pm[thnq==ithnq], R80_em45[thnq==ithnq], color='green', marker='s', label='80 MeV Systematics (Em: 45 MeV)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_em45[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_em45[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_em45[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_em45[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_em45[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], R80_em50[thnq==ithnq], color='magenta', marker='s', label='80 MeV Systematics (Em: 50 MeV)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_em50[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_em50[thnq==ithnq], color='magenta', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_em50[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_em50[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_em50[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )
        
        B.plot_exp(pm[thnq==ithnq], R80_em60[thnq==ithnq], color='blue', marker='s', label='80 MeV Systematics (Em: 60 MeV)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_em60[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_em60[thnq==ithnq], color='blue', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_em60[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_em60[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_em60[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )
            
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
            
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
            
        '''
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
        '''

#-------------------------------------------------------------------------------------------------

def plotZtar_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots the Roger Barlow Ratio R vs. Pmiss (if R>4 sig. there is a sig. difference)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fz0_name="../datafiles/"+study_dir+"systematicsZtar2.5cm.txt"
    fz1_name="../datafiles/"+study_dir+"systematicsZtar2.0cm.txt"
    fz2_name="../datafiles/"+study_dir+"systematicsZtar1.5cm.txt"
    fz3_name="../datafiles/"+study_dir+"systematicsZtar1.0cm.txt"
    fz4_name="../datafiles/"+study_dir+"systematicsZtar0.5cm.txt"

    fz0 = B.get_file(fz0_name)
    fz1 = B.get_file(fz1_name)
    fz2 = B.get_file(fz2_name)
    fz3 = B.get_file(fz3_name)
    fz4 = B.get_file(fz4_name)
        
    thnq = B.get_data(fz2, 'xb') 
    pm = B.get_data(fz2, 'yb') 
    #|Ztar|<2.5 cm
    R80_z2p5 = B.get_data(fz0,'R80')            ;  del80_z2p5 = B.get_data(fz0,'del80')             ; sig_del80_z2p5 = B.get_data(fz0,'sig_del80')          
    R580set1_z2p5 = B.get_data(fz0,'R580set1')  ;  del580set1_z2p5 = B.get_data(fz0,'del_580set1')  ; sig_del580set1_z2p5 = B.get_data(fz0,'sig_del580set1')
    R580set2_z2p5 = B.get_data(fz0,'R580set2')  ;  del580set2_z2p5 = B.get_data(fz0,'del_580set2')  ; sig_del580set2_z2p5 = B.get_data(fz0,'sig_del580set2')
    R750set1_z2p5 = B.get_data(fz0,'R750set1')  ;  del750set1_z2p5 = B.get_data(fz0,'del_750set1')  ; sig_del750set1_z2p5 = B.get_data(fz0,'sig_del750set1')
    R750set2_z2p5 = B.get_data(fz0,'R750set2')  ;  del750set2_z2p5 = B.get_data(fz0,'del_750set2')  ; sig_del750set2_z2p5 = B.get_data(fz0,'sig_del750set2')
    R750set3_z2p5 = B.get_data(fz0,'R750set3')  ;  del750set3_z2p5 = B.get_data(fz0,'del_750set3')  ; sig_del750set3_z2p5 = B.get_data(fz0,'sig_del750set3')
    #|Ztar|<2.0 cm
    R80_z2p0 = B.get_data(fz1,'R80')            ;  del80_z2p0 = B.get_data(fz1,'del80')             ; sig_del80_z2p0 = B.get_data(fz1,'sig_del80')          
    R580set1_z2p0 = B.get_data(fz1,'R580set1')  ;  del580set1_z2p0 = B.get_data(fz1,'del_580set1')  ; sig_del580set1_z2p0 = B.get_data(fz1,'sig_del580set1')
    R580set2_z2p0 = B.get_data(fz1,'R580set2')  ;  del580set2_z2p0 = B.get_data(fz1,'del_580set2')  ; sig_del580set2_z2p0 = B.get_data(fz1,'sig_del580set2')
    R750set1_z2p0 = B.get_data(fz1,'R750set1')  ;  del750set1_z2p0 = B.get_data(fz1,'del_750set1')  ; sig_del750set1_z2p0 = B.get_data(fz1,'sig_del750set1')
    R750set2_z2p0 = B.get_data(fz1,'R750set2')  ;  del750set2_z2p0 = B.get_data(fz1,'del_750set2')  ; sig_del750set2_z2p0 = B.get_data(fz1,'sig_del750set2')
    R750set3_z2p0 = B.get_data(fz1,'R750set3')  ;  del750set3_z2p0 = B.get_data(fz1,'del_750set3')  ; sig_del750set3_z2p0 = B.get_data(fz1,'sig_del750set3')
    #|Ztar|<1.5 cm
    R80_z1p5 = B.get_data(fz2,'R80')            ;  del80_z1p5 = B.get_data(fz2,'del80')             ; sig_del80_z1p5 = B.get_data(fz2,'sig_del80')          
    R580set1_z1p5 = B.get_data(fz2,'R580set1')  ;  del580set1_z1p5 = B.get_data(fz2,'del_580set1')  ; sig_del580set1_z1p5 = B.get_data(fz2,'sig_del580set1')
    R580set2_z1p5 = B.get_data(fz2,'R580set2')  ;  del580set2_z1p5 = B.get_data(fz2,'del_580set2')  ; sig_del580set2_z1p5 = B.get_data(fz2,'sig_del580set2')
    R750set1_z1p5 = B.get_data(fz2,'R750set1')  ;  del750set1_z1p5 = B.get_data(fz2,'del_750set1')  ; sig_del750set1_z1p5 = B.get_data(fz2,'sig_del750set1')
    R750set2_z1p5 = B.get_data(fz2,'R750set2')  ;  del750set2_z1p5 = B.get_data(fz2,'del_750set2')  ; sig_del750set2_z1p5 = B.get_data(fz2,'sig_del750set2')
    R750set3_z1p5 = B.get_data(fz2,'R750set3')  ;  del750set3_z1p5 = B.get_data(fz2,'del_750set3')  ; sig_del750set3_z1p5 = B.get_data(fz2,'sig_del750set3')
    #|Ztar|<1.0 cm
    R80_z1p0 = B.get_data(fz3,'R80')            ;  del80_z1p0 = B.get_data(fz3,'del80')             ; sig_del80_z1p0 = B.get_data(fz3,'sig_del80')          
    R580set1_z1p0 = B.get_data(fz3,'R580set1')  ;  del580set1_z1p0 = B.get_data(fz3,'del_580set1')  ; sig_del580set1_z1p0 = B.get_data(fz3,'sig_del580set1')
    R580set2_z1p0 = B.get_data(fz3,'R580set2')  ;  del580set2_z1p0 = B.get_data(fz3,'del_580set2')  ; sig_del580set2_z1p0 = B.get_data(fz3,'sig_del580set2')
    R750set1_z1p0 = B.get_data(fz3,'R750set1')  ;  del750set1_z1p0 = B.get_data(fz3,'del_750set1')  ; sig_del750set1_z1p0 = B.get_data(fz3,'sig_del750set1')
    R750set2_z1p0 = B.get_data(fz3,'R750set2')  ;  del750set2_z1p0 = B.get_data(fz3,'del_750set2')  ; sig_del750set2_z1p0 = B.get_data(fz3,'sig_del750set2')
    R750set3_z1p0 = B.get_data(fz3,'R750set3')  ;  del750set3_z1p0 = B.get_data(fz3,'del_750set3')  ; sig_del750set3_z1p0 = B.get_data(fz3,'sig_del750set3')
    #|Ztar|<0.5 cm
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
        print('theta_nq:',ithnq,' deg')

        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        #|Ztar| < 2.5 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z2p5[thnq==ithnq], color='magenta', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 2.5 cm)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_z2p5[thnq==ithnq], color='magenta', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z2p5[thnq==ithnq], color='magenta', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z2p5[thnq==ithnq], color='magenta', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_z2p5[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_z2p5[thnq==ithnq], color='magenta', marker='<', label='750 (set3) MeV Systematics' )    
        
       #|Ztar| < 2.0 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z2p0[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 2.0 cm)' )
      #  B.plot_exp(pm[thnq==ithnq], R580set1_z2p0[thnq==ithnq], color='black', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z2p0[thnq==ithnq], color='black', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z2p0[thnq==ithnq], color='black', marker='>', label='750 (set1) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set2_z2p0[thnq==ithnq], color='black', marker='v', label='750 (set2) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set3_z2p0[thnq==ithnq], color='black', marker='<', label='750 (set3) MeV Systematics' )    
       
      #|Ztar| < 1.5 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z1p5[thnq==ithnq], color='red', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.5 cm)' )
      #  B.plot_exp(pm[thnq==ithnq], R580set1_z1p5[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z1p5[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z1p5[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set2_z1p5[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set3_z1p5[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
       
      #|Ztar| < 1.0 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z1p0[thnq==ithnq], color='green', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 1.0 cm)' )
      #  B.plot_exp(pm[thnq==ithnq], R580set1_z1p0[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z1p0[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z1p0[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set2_z1p0[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set3_z1p0[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )
       
      #|Ztar| < 0.5 cm cut
        B.plot_exp(pm[thnq==ithnq], R80_z0p5[thnq==ithnq], color='blue', marker='s', label=r'80 MeV Systematics ($|Z_{tar}|$ < 0.5 cm)' )
      #  B.plot_exp(pm[thnq==ithnq], R580set1_z0p5[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_z0p5[thnq==ithnq], color='blue', marker='^', label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_z0p5[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set2_z0p5[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
      #  B.plot_exp(pm[thnq==ithnq], R750set3_z0p5[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )
            
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
            
        '''
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
        '''

def plothColl_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots the Roger Barlow Ratio R vs. Pmiss (if R>4 sig. there is a sig. difference)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fc0_name="../datafiles/"+study_dir+"systematicshColl1.0.txt"
    fc1_name="../datafiles/"+study_dir+"systematicshColl0.9.txt"
    fc2_name="../datafiles/"+study_dir+"systematicshColl0.8.txt"

    fc0 = B.get_file(fc0_name)
    fc1 = B.get_file(fc1_name)
    fc2 = B.get_file(fc2_name)
        
    thnq = B.get_data(fc0, 'xb') 
    pm = B.get_data(fc0, 'yb') 
    #hColl scale 1.0
    R80_h1p0 = B.get_data(fc0,'R80')            ;  del80_h1p0 = B.get_data(fc0,'del80')             ; sig_del80_h1p0 = B.get_data(fc0,'sig_del80')          
    R580set1_h1p0 = B.get_data(fc0,'R580set1')  ;  del580set1_h1p0 = B.get_data(fc0,'del_580set1')  ; sig_del580set1_h1p0 = B.get_data(fc0,'sig_del580set1')
    R580set2_h1p0 = B.get_data(fc0,'R580set2')  ;  del580set2_h1p0 = B.get_data(fc0,'del_580set2')  ; sig_del580set2_h1p0 = B.get_data(fc0,'sig_del580set2')
    R750set1_h1p0 = B.get_data(fc0,'R750set1')  ;  del750set1_h1p0 = B.get_data(fc0,'del_750set1')  ; sig_del750set1_h1p0 = B.get_data(fc0,'sig_del750set1')
    R750set2_h1p0 = B.get_data(fc0,'R750set2')  ;  del750set2_h1p0 = B.get_data(fc0,'del_750set2')  ; sig_del750set2_h1p0 = B.get_data(fc0,'sig_del750set2')
    R750set3_h1p0 = B.get_data(fc0,'R750set3')  ;  del750set3_h1p0 = B.get_data(fc0,'del_750set3')  ; sig_del750set3_h1p0 = B.get_data(fc0,'sig_del750set3')
    #hColl scale 0.9
    R80_h0p9 = B.get_data(fc1,'R80')            ;  del80_h0p9 = B.get_data(fc1,'del80')             ; sig_del80_h0p9 = B.get_data(fc1,'sig_del80')          
    R580set1_h0p9 = B.get_data(fc1,'R580set1')  ;  del580set1_h0p9 = B.get_data(fc1,'del_580set1')  ; sig_del580set1_h0p9 = B.get_data(fc1,'sig_del580set1')
    R580set2_h0p9 = B.get_data(fc1,'R580set2')  ;  del580set2_h0p9 = B.get_data(fc1,'del_580set2')  ; sig_del580set2_h0p9 = B.get_data(fc1,'sig_del580set2')
    R750set1_h0p9 = B.get_data(fc1,'R750set1')  ;  del750set1_h0p9 = B.get_data(fc1,'del_750set1')  ; sig_del750set1_h0p9 = B.get_data(fc1,'sig_del750set1')
    R750set2_h0p9 = B.get_data(fc1,'R750set2')  ;  del750set2_h0p9 = B.get_data(fc1,'del_750set2')  ; sig_del750set2_h0p9 = B.get_data(fc1,'sig_del750set2')
    R750set3_h0p9 = B.get_data(fc1,'R750set3')  ;  del750set3_h0p9 = B.get_data(fc1,'del_750set3')  ; sig_del750set3_h0p9 = B.get_data(fc1,'sig_del750set3')
    #hColl scale 0.8
    R80_h0p8 = B.get_data(fc2,'R80')            ;  del80_h0p8 = B.get_data(fc2,'del80')             ; sig_del80_h0p8 = B.get_data(fc2,'sig_del80')          
    R580set1_h0p8 = B.get_data(fc2,'R580set1')  ;  del580set1_h0p8 = B.get_data(fc2,'del_580set1')  ; sig_del580set1_h0p8 = B.get_data(fc2,'sig_del580set1')
    R580set2_h0p8 = B.get_data(fc2,'R580set2')  ;  del580set2_h0p8 = B.get_data(fc2,'del_580set2')  ; sig_del580set2_h0p8 = B.get_data(fc2,'sig_del580set2')
    R750set1_h0p8 = B.get_data(fc2,'R750set1')  ;  del750set1_h0p8 = B.get_data(fc2,'del_750set1')  ; sig_del750set1_h0p8 = B.get_data(fc2,'sig_del750set1')
    R750set2_h0p8 = B.get_data(fc2,'R750set2')  ;  del750set2_h0p8 = B.get_data(fc2,'del_750set2')  ; sig_del750set2_h0p8 = B.get_data(fc2,'sig_del750set2')
    R750set3_h0p8 = B.get_data(fc2,'R750set3')  ;  del750set3_h0p8 = B.get_data(fc2,'del_750set3')  ; sig_del750set3_h0p8 = B.get_data(fc2,'sig_del750set3')

    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        #hColl scale 1.0
        B.plot_exp(pm[thnq==ithnq], R80_h1p0[thnq==ithnq], color='blue', marker='s', label=r'80 MeV Systematics (Scale: 1.0)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_h1p0[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_h1p0[thnq==ithnq], color='blue', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_h1p0[thnq==ithnq], color='blue', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_h1p0[thnq==ithnq], color='blue', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_h1p0[thnq==ithnq], color='blue', marker='<', label='750 (set3) MeV Systematics' )    
       
       #hColl scale 0.9
        B.plot_exp(pm[thnq==ithnq], R80_h0p9[thnq==ithnq], color='green', marker='s', label=r'80 MeV Systematics (Scale 0.9)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_h0p9[thnq==ithnq], color='green', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_h0p9[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_h0p9[thnq==ithnq], color='green', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_h0p9[thnq==ithnq], color='green', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_h0p9[thnq==ithnq], color='green', marker='<', label='750 (set3) MeV Systematics' )    
       
       #hColl scale 0.8
        B.plot_exp(pm[thnq==ithnq], R80_h0p8[thnq==ithnq], color='red', marker='s', label=r'80 MeV Systematics (Scale 0.8)' )
       # B.plot_exp(pm[thnq==ithnq], R580set1_h0p8[thnq==ithnq], color='red', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_h0p8[thnq==ithnq], color='red', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_h0p8[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set2_h0p8[thnq==ithnq], color='red', marker='v', label='750 (set2) MeV Systematics' )
       # B.plot_exp(pm[thnq==ithnq], R750set3_h0p8[thnq==ithnq], color='red', marker='<', label='750 (set3) MeV Systematics' )    
    
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
            
def plotctime_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots the Roger Barlow Ratio R vs. Pmiss (if R>4 sig. there is a sig. difference)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fc1_name="../datafiles/"+study_dir+"systematicsctimeON.txt"

    fc1 = B.get_file(fc1_name)
        
    thnq = B.get_data(fc1, 'xb') 
    pm = B.get_data(fc1, 'yb') 
    
    #ctime ON
    R80_ctime = B.get_data(fc1,'R80')            ;  del80_ctime = B.get_data(fc1,'del80')             ; sig_del80_ctime = B.get_data(fc1,'sig_del80')          
    R580set1_ctime = B.get_data(fc1,'R580set1')  ;  del580set1_ctime = B.get_data(fc1,'del_580set1')  ; sig_del580set1_ctime = B.get_data(fc1,'sig_del580set1')
    R580set2_ctime = B.get_data(fc1,'R580set2')  ;  del580set2_ctime = B.get_data(fc1,'del_580set2')  ; sig_del580set2_ctime = B.get_data(fc1,'sig_del580set2')
    R750set1_ctime = B.get_data(fc1,'R750set1')  ;  del750set1_ctime = B.get_data(fc1,'del_750set1')  ; sig_del750set1_ctime = B.get_data(fc1,'sig_del750set1')
    R750set2_ctime = B.get_data(fc1,'R750set2')  ;  del750set2_ctime = B.get_data(fc1,'del_750set2')  ; sig_del750set2_ctime = B.get_data(fc1,'sig_del750set2')
    R750set3_ctime = B.get_data(fc1,'R750set3')  ;  del750set3_ctime = B.get_data(fc1,'del_750set3')  ; sig_del750set3_ctime = B.get_data(fc1,'sig_del750set3')
   

    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        #ctime ON
        B.plot_exp(pm[thnq==ithnq], R80_ctime[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics (Coin. Time)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_ctime[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_ctime[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_ctime[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_ctime[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_ctime[thnq==ithnq], color='cyan', marker='<', label='750 (set3) MeV Systematics' )    
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))
                 
def plotpcal_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots the Roger Barlow Ratio R vs. Pmiss (if R>4 sig. there is a sig. difference)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fc1_name="../datafiles/"+study_dir+"systematicsshmsCalON.txt"

    fc1 = B.get_file(fc1_name)
        
    thnq = B.get_data(fc1, 'xb') 
    pm = B.get_data(fc1, 'yb') 
    
    #ctime ON
    R80_ctime = B.get_data(fc1,'R80')            ;  del80_ctime = B.get_data(fc1,'del80')             ; sig_del80_ctime = B.get_data(fc1,'sig_del80')          
    R580set1_ctime = B.get_data(fc1,'R580set1')  ;  del580set1_ctime = B.get_data(fc1,'del_580set1')  ; sig_del580set1_ctime = B.get_data(fc1,'sig_del580set1')
    R580set2_ctime = B.get_data(fc1,'R580set2')  ;  del580set2_ctime = B.get_data(fc1,'del_580set2')  ; sig_del580set2_ctime = B.get_data(fc1,'sig_del580set2')
    R750set1_ctime = B.get_data(fc1,'R750set1')  ;  del750set1_ctime = B.get_data(fc1,'del_750set1')  ; sig_del750set1_ctime = B.get_data(fc1,'sig_del750set1')
    R750set2_ctime = B.get_data(fc1,'R750set2')  ;  del750set2_ctime = B.get_data(fc1,'del_750set2')  ; sig_del750set2_ctime = B.get_data(fc1,'sig_del750set2')
    R750set3_ctime = B.get_data(fc1,'R750set3')  ;  del750set3_ctime = B.get_data(fc1,'del_750set3')  ; sig_del750set3_ctime = B.get_data(fc1,'sig_del750set3')
   

    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        fig1 = B.pl.figure(i)
        B.pl.clf()
        #ctime ON
        B.plot_exp(pm[thnq==ithnq], R80_ctime[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics (SHMS Calorimeter)' )
        B.plot_exp(pm[thnq==ithnq], R580set1_ctime[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2_ctime[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1_ctime[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2_ctime[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3_ctime[thnq==ithnq], color='cyan', marker='<', label='750 (set3) MeV Systematics' )    
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))


#PLOTS either radiative or bin-centering corr. systemtatics
def plotRCBC_syst(study='', stats_thrs=0.):

    #Reads the systematics data files and plots the Roger Barlow Ratio R vs. Pmiss (if R>4 sig. there is a sig. difference)

    stats_thrs = stats_thrs*100.

    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "./full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


    #Set systematic file names
    fname="./datafiles/"+study_dir+"systematics%s.txt"%(study)

    f = B.get_file(fname)
        
    thnq = B.get_data(f, 'xb') 
    pm = B.get_data(f, 'yb') 
    
    #Roger Barlow Ratio for Radiative or Bin-Centering
    R80      = B.get_data(f,'R80')       ;  del80      = B.get_data(f,'del80')        ; sig_del80      = B.get_data(f,'sig_del80')          
    R580set1 = B.get_data(f,'R580set1')  ;  del580set1 = B.get_data(f,'del_580set1')  ; sig_del580set1 = B.get_data(f,'sig_del580set1')
    R580set2 = B.get_data(f,'R580set2')  ;  del580set2 = B.get_data(f,'del_580set2')  ; sig_del580set2 = B.get_data(f,'sig_del580set2')
    R750set1 = B.get_data(f,'R750set1')  ;  del750set1 = B.get_data(f,'del_750set1')  ; sig_del750set1 = B.get_data(f,'sig_del750set1')
    R750set2 = B.get_data(f,'R750set2')  ;  del750set2 = B.get_data(f,'del_750set2')  ; sig_del750set2 = B.get_data(f,'sig_del750set2')
    R750set3 = B.get_data(f,'R750set3')  ;  del750set3 = B.get_data(f,'del_750set3')  ; sig_del750set3 = B.get_data(f,'sig_del750set3')
   
    #Get the Xsec and its Error
    if(study=='radiative'):
        #Radiative Corrected Xsec (PWIA)
        dataXsec_80_pwiaRC          = B.get_data(f, 'dataXsec_80_pwiaRC') 
        dataXsec_80_err_pwiaRC      = B.get_data(f, 'dataXsec_err_80_pwiaRC') 
        dataXsec_580set1_pwiaRC     = B.get_data(f, 'dataXsec_580set1_pwiaRC') 
        dataXsec_580set1_err_pwiaRC = B.get_data(f, 'dataXsec_err_580set1_pwiaRC')
        dataXsec_580set2_pwiaRC     = B.get_data(f, 'dataXsec_580set2_pwiaRC') 
        dataXsec_580set2_err_pwiaRC = B.get_data(f, 'dataXsec_err_580set2_pwiaRC')
        dataXsec_750set1_pwiaRC     = B.get_data(f, 'dataXsec_750set1_pwiaRC') 
        dataXsec_750set1_err_pwiaRC = B.get_data(f, 'dataXsec_err_750set1_pwiaRC')
        dataXsec_750set2_pwiaRC     = B.get_data(f, 'dataXsec_750set2_pwiaRC') 
        dataXsec_750set2_err_pwiaRC = B.get_data(f, 'dataXsec_err_750set2_pwiaRC')
        dataXsec_750set3_pwiaRC     = B.get_data(f, 'dataXsec_750set3_pwiaRC') 
        dataXsec_750set3_err_pwiaRC = B.get_data(f, 'dataXsec_err_750set3_pwiaRC')
        #Radiative Corrected Xsec (FSI)
        dataXsec_80_fsiRC           = B.get_data(f, 'dataXsec_80_fsiRC') 
        dataXsec_80_err_fsiRC       = B.get_data(f, 'dataXsec_err_80_fsiRC') 
        dataXsec_580set1_fsiRC      = B.get_data(f, 'dataXsec_580set1_fsiRC') 
        dataXsec_580set1_err_fsiRC  = B.get_data(f, 'dataXsec_err_580set1_fsiRC')
        dataXsec_580set2_fsiRC      = B.get_data(f, 'dataXsec_580set2_fsiRC') 
        dataXsec_580set2_err_fsiRC  = B.get_data(f, 'dataXsec_err_580set2_fsiRC')
        dataXsec_750set1_fsiRC      = B.get_data(f, 'dataXsec_750set1_fsiRC') 
        dataXsec_750set1_err_fsiRC  = B.get_data(f, 'dataXsec_err_750set1_fsiRC')
        dataXsec_750set2_fsiRC      = B.get_data(f, 'dataXsec_750set2_fsiRC') 
        dataXsec_750set2_err_fsiRC  = B.get_data(f, 'dataXsec_err_750set2_fsiRC')
        dataXsec_750set3_fsiRC      = B.get_data(f, 'dataXsec_750set3_fsiRC') 
        dataXsec_750set3_err_fsiRC  = B.get_data(f, 'dataXsec_err_750set3_fsiRC')

    if(study=='binCentering'):
        #Bin Center Corrected Xsec (PWIA)
        dataXsec_80_pwiaBC          = B.get_data(f, 'dataXsec_80_pwiaBC') 
        dataXsec_80_err_pwiaBC      = B.get_data(f, 'dataXsec_err_80_pwiaBC') 
        dataXsec_580set1_pwiaBC     = B.get_data(f, 'dataXsec_580set1_pwiaBC') 
        dataXsec_580set1_err_pwiaBC = B.get_data(f, 'dataXsec_err_580set1_pwiaBC')
        dataXsec_580set2_pwiaBC     = B.get_data(f, 'dataXsec_580set2_pwiaBC') 
        dataXsec_580set2_err_pwiaBC = B.get_data(f, 'dataXsec_err_580set2_pwiaBC')
        dataXsec_750set1_pwiaBC     = B.get_data(f, 'dataXsec_750set1_pwiaBC') 
        dataXsec_750set1_err_pwiaBC = B.get_data(f, 'dataXsec_err_750set1_pwiaBC')
        dataXsec_750set2_pwiaBC     = B.get_data(f, 'dataXsec_750set2_pwiaBC') 
        dataXsec_750set2_err_pwiaBC = B.get_data(f, 'dataXsec_err_750set2_pwiaBC')
        dataXsec_750set3_pwiaBC     = B.get_data(f, 'dataXsec_750set3_pwiaBC') 
        dataXsec_750set3_err_pwiaBC = B.get_data(f, 'dataXsec_err_750set3_pwiaBC')
        #Bin Center Corrected Xsec (FSI)
        dataXsec_80_fsiBC           = B.get_data(f, 'dataXsec_80_fsiBC') 
        dataXsec_80_err_fsiBC       = B.get_data(f, 'dataXsec_err_80_fsiBC') 
        dataXsec_580set1_fsiBC      = B.get_data(f, 'dataXsec_580set1_fsiBC') 
        dataXsec_580set1_err_fsiBC  = B.get_data(f, 'dataXsec_err_580set1_fsiBC')
        dataXsec_580set2_fsiBC      = B.get_data(f, 'dataXsec_580set2_fsiBC') 
        dataXsec_580set2_err_fsiBC  = B.get_data(f, 'dataXsec_err_580set2_fsiBC')
        dataXsec_750set1_fsiBC      = B.get_data(f, 'dataXsec_750set1_fsiBC') 
        dataXsec_750set1_err_fsiBC  = B.get_data(f, 'dataXsec_err_750set1_fsiBC')
        dataXsec_750set2_fsiBC      = B.get_data(f, 'dataXsec_750set2_fsiBC') 
        dataXsec_750set2_err_fsiBC  = B.get_data(f, 'dataXsec_err_750set2_fsiBC')
        dataXsec_750set3_fsiBC      = B.get_data(f, 'dataXsec_750set3_fsiBC') 
        dataXsec_750set3_err_fsiBC  = B.get_data(f, 'dataXsec_err_750set3_fsiBC')

    #Define theta_nq bins to plot
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    #Loop over theta_nq angle bins
    for i, ithnq in enumerate(thnq_arr):
        print('theta_nq:',ithnq,' deg')

        
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        
        B.pl.figure(i)
        B.pl.clf()
       
        B.plot_exp(pm[thnq==ithnq], R80[thnq==ithnq], color='black', marker='s', label=r'80 MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set1[thnq==ithnq], color='blue', marker='o', label='580 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R580set2[thnq==ithnq], color='green', marker='^',label='580 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set1[thnq==ithnq], color='red', marker='>', label='750 (set1) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set2[thnq==ithnq], color='magenta', marker='v', label='750 (set2) MeV Systematics' )
        B.plot_exp(pm[thnq==ithnq], R750set3[thnq==ithnq], color='cyan', marker='<', label='750 (set3) MeV Systematics' )    
            
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Ratio, $\frac{\Delta}{\sigma_{\Delta}}$')
        B.pl.axes().grid()
        B.pl.ylim(-10, 10)
        B.pl.xlim(0, 2.0)
        
        B.pl.axhline(y=-2., color='black', linestyle='--')
        B.pl.axhline(y=2., color='black', linestyle='--')
        
        B.pl.axhline(y=-4., color='black', linestyle='-')
        B.pl.axhline(y=4., color='black', linestyle='-')
        
        
        B.pl.title(r'Ratio $\frac{\Delta}{\sigma_{\Delta}}$, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
        B.pl.legend(loc='upper right', fontsize='xx-small')
        
        B.pl.savefig(dir_name+'/full_sys_thnq%i.pdf'%(ithnq))


        if(study=='radiative'):
            B.pl.figure(i+1)
            
            B.plot_exp(pm[thnq==ithnq], dataXsec_80_pwiaRC[thnq==ithnq],       dataXsec_80_err_pwiaRC[thnq==ithnq],      color='black', marker='s',  markersize=1, label=r'PWIA Radiative Corrected Systematics)' )
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set1_pwiaRC[thnq==ithnq],  dataXsec_580set1_err_pwiaRC[thnq==ithnq], color='black', marker='o',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set2_pwiaRC[thnq==ithnq],  dataXsec_580set2_err_pwiaRC[thnq==ithnq], color='black', marker='^',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set1_pwiaRC[thnq==ithnq],  dataXsec_750set1_err_pwiaRC[thnq==ithnq], color='black', marker='>',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set2_pwiaRC[thnq==ithnq],  dataXsec_750set2_err_pwiaRC[thnq==ithnq], color='black', marker='v',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set3_pwiaRC[thnq==ithnq],  dataXsec_750set3_err_pwiaRC[thnq==ithnq], color='black', marker='<',  markersize=1)    
            
            B.plot_exp(pm[thnq==ithnq], dataXsec_80_fsiRC[thnq==ithnq],       dataXsec_80_err_fsiRC[thnq==ithnq],      color='red', marker='s', markersize=1, label=r'FSI Radiative Corrected Systematics' )
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set1_fsiRC[thnq==ithnq],  dataXsec_580set1_err_fsiRC[thnq==ithnq], color='red', marker='o', markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set2_fsiRC[thnq==ithnq],  dataXsec_580set2_err_fsiRC[thnq==ithnq], color='red', marker='^', markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set1_fsiRC[thnq==ithnq],  dataXsec_750set1_err_fsiRC[thnq==ithnq], color='red', marker='>', markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set2_fsiRC[thnq==ithnq],  dataXsec_750set2_err_fsiRC[thnq==ithnq], color='red', marker='v', markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set3_fsiRC[thnq==ithnq],  dataXsec_750set3_err_fsiRC[thnq==ithnq], color='red', marker='<', markersize=1)

            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Data Cross Section, $\frac{d\sigma}{d\Omega}$')
            B.pl.yscale('log')

            B.pl.title(r'Data Cross Section, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
            B.pl.legend(loc='upper right')
        
            B.pl.savefig(dir_name+'/dataXsecRC_thnq%i.pdf'%(ithnq))


        if(study=='binCentering'):
            B.pl.figure(i+2)
            
            B.plot_exp(pm[thnq==ithnq], dataXsec_80_pwiaBC[thnq==ithnq],       dataXsec_80_err_pwiaBC[thnq==ithnq],      color='black', marker='s',  markersize=1, label=r'PWIA BinCenter Corrected Systematics)' )
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set1_pwiaBC[thnq==ithnq],  dataXsec_580set1_err_pwiaBC[thnq==ithnq], color='black', marker='o',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set2_pwiaBC[thnq==ithnq],  dataXsec_580set2_err_pwiaBC[thnq==ithnq], color='black', marker='^',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set1_pwiaBC[thnq==ithnq],  dataXsec_750set1_err_pwiaBC[thnq==ithnq], color='black', marker='>',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set2_pwiaBC[thnq==ithnq],  dataXsec_750set2_err_pwiaBC[thnq==ithnq], color='black', marker='v',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set3_pwiaBC[thnq==ithnq],  dataXsec_750set3_err_pwiaBC[thnq==ithnq], color='black', marker='<',  markersize=1)    
            
            B.plot_exp(pm[thnq==ithnq], dataXsec_80_fsiBC[thnq==ithnq],       dataXsec_80_err_fsiBC[thnq==ithnq],      color='red', marker='s',  markersize=1, label=r'FSI BinCenter Corrected Systematics' )
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set1_fsiBC[thnq==ithnq],  dataXsec_580set1_err_fsiBC[thnq==ithnq], color='red', marker='o',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_580set2_fsiBC[thnq==ithnq],  dataXsec_580set2_err_fsiBC[thnq==ithnq], color='red', marker='^',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set1_fsiBC[thnq==ithnq],  dataXsec_750set1_err_fsiBC[thnq==ithnq], color='red', marker='>',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set2_fsiBC[thnq==ithnq],  dataXsec_750set2_err_fsiBC[thnq==ithnq], color='red', marker='v',  markersize=1)
            B.plot_exp(pm[thnq==ithnq], dataXsec_750set3_fsiBC[thnq==ithnq],  dataXsec_750set3_err_fsiBC[thnq==ithnq], color='red', marker='<',  markersize=1)

            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Data Cross Section, $\frac{d\sigma}{d\Omega}$')
            B.pl.yscale('log')

            B.pl.title(r'Data Cross Section, $\theta_{nq}:(%i, %i)$, Stats. (within %.1f %%)'%(th_nq_min, th_nq_max, stats_thrs))
        
            B.pl.legend(loc='upper right')
        
            B.pl.savefig(dir_name+'/dataXsecBC_thnq%i.pdf'%(ithnq))

#-------------------------------------------------------------------------------------------

def plotXsec_vs_Emcuts(study='', stats_thrs=0.,  thnq_bin = 0.):

    print('Plot Data Cross Sections vs. Em Cuts')
    print('theta_nq setting:', thnq_bin)

    #Plot Cross Sections vs. Emiss Cuts for multiple Pmiss bins at fixed theta_nq bin
    #theta_nq bins: 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 
    #(Purpose: Try to understand how the Xsec varies with different Emiss cut ranges)

    stats_thrs = stats_thrs*100.
 
    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Set FileNames to be read
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


    #Get the BIn Inforamtion
    thnq = B.get_data(f40, 'xb') 
    pm = B.get_data(f40, 'yb') 

    #Get the Xsec and its Error
    # Em < 30 MeV
    dataXsec_80_em30 = B.get_data(f30, 'dataXsec_80') 
    dataXsec_80_err_em30 = B.get_data(f30, 'dataXsec_err_80') 
    dataXsec_580set1_em30 = B.get_data(f30, 'dataXsec_580set1') 
    dataXsec_580set1_err_em30 = B.get_data(f30, 'dataXsec_err_580set1')
    dataXsec_580set2_em30 = B.get_data(f30, 'dataXsec_580set2') 
    dataXsec_580set2_err_em30 = B.get_data(f30, 'dataXsec_err_580set2')
    dataXsec_750set1_em30 = B.get_data(f30, 'dataXsec_750set1') 
    dataXsec_750set1_err_em30 = B.get_data(f30, 'dataXsec_err_750set1')
    dataXsec_750set2_em30 = B.get_data(f30, 'dataXsec_750set2') 
    dataXsec_750set2_err_em30 = B.get_data(f30, 'dataXsec_err_750set2')
    dataXsec_750set3_em30 = B.get_data(f30, 'dataXsec_750set3') 
    dataXsec_750set3_err_em30 = B.get_data(f30, 'dataXsec_err_750set3')
    #Em < 40
    dataXsec_80_em40 = B.get_data(f40, 'dataXsec_80') 
    dataXsec_80_err_em40 = B.get_data(f40, 'dataXsec_err_80') 
    dataXsec_580set1_em40 = B.get_data(f40, 'dataXsec_580set1') 
    dataXsec_580set1_err_em40 = B.get_data(f40, 'dataXsec_err_580set1')
    dataXsec_580set2_em40 = B.get_data(f40, 'dataXsec_580set2') 
    dataXsec_580set2_err_em40 = B.get_data(f40, 'dataXsec_err_580set2')
    dataXsec_750set1_em40 = B.get_data(f40, 'dataXsec_750set1') 
    dataXsec_750set1_err_em40 = B.get_data(f40, 'dataXsec_err_750set1')
    dataXsec_750set2_em40 = B.get_data(f40, 'dataXsec_750set2') 
    dataXsec_750set2_err_em40 = B.get_data(f40, 'dataXsec_err_750set2')
    dataXsec_750set3_em40 = B.get_data(f40, 'dataXsec_750set3') 
    dataXsec_750set3_err_em40 = B.get_data(f40, 'dataXsec_err_750set3')
    #Em < 45
    dataXsec_80_em45 = B.get_data(f45, 'dataXsec_80') 
    dataXsec_80_err_em45 = B.get_data(f45, 'dataXsec_err_80') 
    dataXsec_580set1_em45 = B.get_data(f45, 'dataXsec_580set1') 
    dataXsec_580set1_err_em45 = B.get_data(f45, 'dataXsec_err_580set1')
    dataXsec_580set2_em45 = B.get_data(f45, 'dataXsec_580set2') 
    dataXsec_580set2_err_em45 = B.get_data(f45, 'dataXsec_err_580set2')
    dataXsec_750set1_em45 = B.get_data(f45, 'dataXsec_750set1') 
    dataXsec_750set1_err_em45 = B.get_data(f45, 'dataXsec_err_750set1')
    dataXsec_750set2_em45 = B.get_data(f45, 'dataXsec_750set2') 
    dataXsec_750set2_err_em45 = B.get_data(f45, 'dataXsec_err_750set2')
    dataXsec_750set3_em45 = B.get_data(f45, 'dataXsec_750set3') 
    dataXsec_750set3_err_em45 = B.get_data(f45, 'dataXsec_err_750set3')
    #Em < 50
    dataXsec_80_em50 = B.get_data(f50, 'dataXsec_80') 
    dataXsec_80_err_em50 = B.get_data(f50, 'dataXsec_err_80') 
    dataXsec_580set1_em50 = B.get_data(f50, 'dataXsec_580set1') 
    dataXsec_580set1_err_em50 = B.get_data(f50, 'dataXsec_err_580set1')
    dataXsec_580set2_em50 = B.get_data(f50, 'dataXsec_580set2') 
    dataXsec_580set2_err_em50 = B.get_data(f50, 'dataXsec_err_580set2')
    dataXsec_750set1_em50 = B.get_data(f50, 'dataXsec_750set1') 
    dataXsec_750set1_err_em50 = B.get_data(f50, 'dataXsec_err_750set1')
    dataXsec_750set2_em50 = B.get_data(f50, 'dataXsec_750set2') 
    dataXsec_750set2_err_em50 = B.get_data(f50, 'dataXsec_err_750set2')
    dataXsec_750set3_em50 = B.get_data(f50, 'dataXsec_750set3') 
    dataXsec_750set3_err_em50 = B.get_data(f50, 'dataXsec_err_750set3')
    #Em < 60
    dataXsec_80_em60 = B.get_data(f60, 'dataXsec_80') 
    dataXsec_80_err_em60 = B.get_data(f60, 'dataXsec_err_80') 
    dataXsec_580set1_em60 = B.get_data(f60, 'dataXsec_580set1') 
    dataXsec_580set1_err_em60 = B.get_data(f60, 'dataXsec_err_580set1')
    dataXsec_580set2_em60 = B.get_data(f60, 'dataXsec_580set2') 
    dataXsec_580set2_err_em60 = B.get_data(f60, 'dataXsec_err_580set2')
    dataXsec_750set1_em60 = B.get_data(f60, 'dataXsec_750set1') 
    dataXsec_750set1_err_em60 = B.get_data(f60, 'dataXsec_err_750set1')
    dataXsec_750set2_em60 = B.get_data(f60, 'dataXsec_750set2') 
    dataXsec_750set2_err_em60 = B.get_data(f60, 'dataXsec_err_750set2')
    dataXsec_750set3_em60 = B.get_data(f60, 'dataXsec_750set3') 
    dataXsec_750set3_err_em60 = B.get_data(f60, 'dataXsec_err_750set3')
    #Em < 80
    dataXsec_80_em80 = B.get_data(f30, 'dataXsec_80_nom') 
    dataXsec_80_err_em80 = B.get_data(f30, 'dataXsec_err_80_nom') 
    dataXsec_580set1_em80 = B.get_data(f30, 'dataXsec_580set1_nom') 
    dataXsec_580set1_err_em80 = B.get_data(f30, 'dataXsec_err_580set1_nom')
    dataXsec_580set2_em80 = B.get_data(f30, 'dataXsec_580set2_nom') 
    dataXsec_580set2_err_em80 = B.get_data(f30, 'dataXsec_err_580set2_nom')
    dataXsec_750set1_em80 = B.get_data(f30, 'dataXsec_750set1_nom') 
    dataXsec_750set1_err_em80 = B.get_data(f30, 'dataXsec_err_750set1_nom')
    dataXsec_750set2_em80 = B.get_data(f30, 'dataXsec_750set2_nom') 
    dataXsec_750set2_err_em80 = B.get_data(f30, 'dataXsec_err_750set2_nom')
    dataXsec_750set3_em80 = B.get_data(f30, 'dataXsec_750set3_nom') 
    dataXsec_750set3_err_em80 = B.get_data(f30, 'dataXsec_err_750set3_nom')
  
    #Define pmiss bins to plot
    pm_arr = [0.02, 0.06, 0.100, 0.140, 0.180, 0.220, 0.260, 0.300, 0.340, 0.380, 0.420, 0.460, 0.500, 0.540, 0.580, 0.620, 0.660, 0.700, 0.740, 0.780, 0.820, 0.860, 0.900, 0.940, 0.980, 1.020, 1.060]

    #Loop over central Pmiss bins
    for i, ipm in enumerate(pm_arr):
        print('Loop over Pmiss: ', ipm, 'GeV/c')

        B.pl.figure(i)
        B.pl.clf()
        
        pm_i = ipm * 1000.    #Pmiss converter to MeV
        pmi_min = pm_i - 20.
        pmi_max = pm_i + 20.

        #PM=80 MeV
        B.plot_exp(30, dataXsec_80_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s', label=r'80 MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(40, dataXsec_80_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(45, dataXsec_80_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(50, dataXsec_80_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(60, dataXsec_80_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(80, dataXsec_80_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')

        y30min  = dataXsec_80_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_80_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_80_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_80_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_80_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_80_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_80_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_80_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_80_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_80_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_80_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_80_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')     
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/80set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 80 MeV')
        #------------------------PM=580 MeV (set1)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+1)                                                                                                                                                               
        B.pl.clf()


        B.plot_exp(30, dataXsec_580set1_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))               
        B.plot_exp(40, dataXsec_580set1_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(45, dataXsec_580set1_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(50, dataXsec_580set1_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(60, dataXsec_580set1_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(80, dataXsec_580set1_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')    

        y30min  = dataXsec_580set1_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_580set1_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_580set1_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_580set1_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_580set1_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_580set1_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_580set1_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_580set1_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_580set1_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_580set1_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_580set1_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_580set1_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 580 (set1) MeV')
        #--------------------PM=580 MeV (set2)------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+2)                                                                                                                                                               
        B.pl.clf()


        B.plot_exp(30, dataXsec_580set2_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))               
        B.plot_exp(40, dataXsec_580set2_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(45, dataXsec_580set2_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(50, dataXsec_580set2_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(60, dataXsec_580set2_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')                                                                                 
        B.plot_exp(80, dataXsec_580set2_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')    

        y30min  = dataXsec_580set2_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_580set2_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_580set2_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_580set2_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_580set2_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_580set2_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_580set2_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_580set2_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_580set2_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_580set2_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_580set2_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_580set2_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set2) MeV')

        #-------------------PM=750 MeV (set1)------------------                                                                                                                                                                                                           

        B.pl.figure(i+3)                                                                                                                                                               
        B.pl.clf()

        B.plot_exp(30, dataXsec_750set1_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^', label=r'750 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))    
        B.plot_exp(40, dataXsec_750set1_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(45, dataXsec_750set1_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(50, dataXsec_750set1_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(60, dataXsec_750set1_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(80, dataXsec_750set1_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^') 

        y30min  = dataXsec_750set1_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_750set1_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_750set1_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_750set1_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_750set1_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_750set1_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_750set1_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_750set1_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_750set1_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_750set1_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_750set1_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_750set1_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set1) MeV')

        #-------------------PM=750 MeV (set2)------------------                                                                                                                                                                                                           

        B.pl.figure(i+4)                                                                                                                                                               
        B.pl.clf()

        B.plot_exp(30, dataXsec_750set2_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^', label=r'750 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))    
        B.plot_exp(40, dataXsec_750set2_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(45, dataXsec_750set2_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(50, dataXsec_750set2_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(60, dataXsec_750set2_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(80, dataXsec_750set2_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^') 

        y30min  = dataXsec_750set2_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_750set2_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_750set2_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_750set2_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_750set2_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_750set2_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_750set2_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_750set2_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_750set2_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_750set2_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_750set2_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_750set2_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 750 (set2) MeV')
        #-------------------PM=750 MeV (set3)------------------                                                                                                                                                                                                           

        B.pl.figure(i+5)                                                                                                                                                               
        B.pl.clf()

        B.plot_exp(30, dataXsec_750set3_em30[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em30[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^', label=r'750 MeV (set3) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))    
        B.plot_exp(40, dataXsec_750set3_em40[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em40[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(45, dataXsec_750set3_em45[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em45[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(50, dataXsec_750set3_em50[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em50[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(60, dataXsec_750set3_em60[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em60[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^')                                                                        
        B.plot_exp(80, dataXsec_750set3_em80[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_em80[(pm==ipm) & (thnq==thnq_bin)], color='blue', marker='^') 

        y30min  = dataXsec_750set3_em30[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40min  = dataXsec_750set3_em40[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45min  = dataXsec_750set3_em45[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50min  = dataXsec_750set3_em50[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60min  = dataXsec_750set3_em60[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80min  = dataXsec_750set3_em80[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        y30max  = dataXsec_750set3_em30[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em30[(pm==ipm) & (thnq==thnq_bin)]
        y40max  = dataXsec_750set3_em40[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em40[(pm==ipm) & (thnq==thnq_bin)]
        y45max  = dataXsec_750set3_em45[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em45[(pm==ipm) & (thnq==thnq_bin)]
        y50max  = dataXsec_750set3_em50[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em50[(pm==ipm) & (thnq==thnq_bin)]
        y60max  = dataXsec_750set3_em60[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em60[(pm==ipm) & (thnq==thnq_bin)]
        y80max  = dataXsec_750set3_em80[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_em80[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y30min, y40min, y45min, y50min, y60min, y80min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y30max, y40max, y45max, y50max, y60max, y80max])
        

        B.pl.xlabel('Missing Energy Cut Setting [MeV]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))  
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set3_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 750 (set3) MeV')

def plotXsec_vs_Ztarcuts(study='', stats_thrs=0., thnq_bin = 0):

    print('Plot Data Cross Sections vs. Em Cuts')
    print('theta_nq setting:', thnq_bin)

    #Plot Cross Sections vs. Ztar Cuts for multiple Pmiss bins at fixed theta_nq bin 
    #theta_nq bins: 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 (Choose on for input)
    #(Purpose: Try to understand how the Xsec varies with different Ztar cut ranges)

    stats_thrs = stats_thrs*100.
 
    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Set FileNames to be read
    f2p5_name="../datafiles/"+study_dir+"systematicsZtar2.5cm.txt"
    f2p0_name="../datafiles/"+study_dir+"systematicsZtar2.0cm.txt"
    f1p5_name="../datafiles/"+study_dir+"systematicsZtar1.5cm.txt"
    f1p0_name="../datafiles/"+study_dir+"systematicsZtar1.0cm.txt"
    f0p5_name="../datafiles/"+study_dir+"systematicsZtar0.5cm.txt"

    f2p5 = B.get_file(f2p5_name)
    f2p0 = B.get_file(f2p0_name)
    f1p5 = B.get_file(f1p5_name)
    f1p0 = B.get_file(f1p0_name)
    f0p5 = B.get_file(f0p5_name)

    #Get the Bin Inforamtion
    thnq = B.get_data(f1p5, 'xb') 
    pm = B.get_data(f1p5, 'yb') 

    #Get the Xsec and its Error
    # |Ztar| < 3.0 cm  (TOTAL SET)
    dataXsec_80_ztar3p0 = B.get_data(f1p5, 'dataXsec_80_nom') 
    dataXsec_80_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_80_nom') 
    dataXsec_580set1_ztar3p0 = B.get_data(f1p5, 'dataXsec_580set1_nom') 
    dataXsec_580set1_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_580set1_nom')
    dataXsec_580set2_ztar3p0 = B.get_data(f1p5, 'dataXsec_580set2_nom') 
    dataXsec_580set2_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_580set2_nom')
    dataXsec_750set1_ztar3p0 = B.get_data(f1p5, 'dataXsec_750set1_nom') 
    dataXsec_750set1_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_750set1_nom')
    dataXsec_750set2_ztar3p0 = B.get_data(f1p5, 'dataXsec_750set2_nom') 
    dataXsec_750set2_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_750set2_nom')
    dataXsec_750set3_ztar3p0 = B.get_data(f1p5, 'dataXsec_750set3_nom') 
    dataXsec_750set3_err_ztar3p0 = B.get_data(f1p5, 'dataXsec_err_750set3_nom')
    # |Ztar| < 2.5 cm
    dataXsec_80_ztar2p5 = B.get_data(f2p5, 'dataXsec_80') 
    dataXsec_80_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_80') 
    dataXsec_580set1_ztar2p5 = B.get_data(f2p5, 'dataXsec_580set1') 
    dataXsec_580set1_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_580set1')
    dataXsec_580set2_ztar2p5 = B.get_data(f2p5, 'dataXsec_580set2') 
    dataXsec_580set2_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_580set2')
    dataXsec_750set1_ztar2p5 = B.get_data(f2p5, 'dataXsec_750set1') 
    dataXsec_750set1_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_750set1')
    dataXsec_750set2_ztar2p5 = B.get_data(f2p5, 'dataXsec_750set2') 
    dataXsec_750set2_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_750set2')
    dataXsec_750set3_ztar2p5 = B.get_data(f2p5, 'dataXsec_750set3') 
    dataXsec_750set3_err_ztar2p5 = B.get_data(f2p5, 'dataXsec_err_750set3')
    # |Ztar| < 2.0 cm
    dataXsec_80_ztar2p0 = B.get_data(f2p0, 'dataXsec_80') 
    dataXsec_80_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_80') 
    dataXsec_580set1_ztar2p0 = B.get_data(f2p0, 'dataXsec_580set1') 
    dataXsec_580set1_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_580set1')
    dataXsec_580set2_ztar2p0 = B.get_data(f2p0, 'dataXsec_580set2') 
    dataXsec_580set2_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_580set2')
    dataXsec_750set1_ztar2p0 = B.get_data(f2p0, 'dataXsec_750set1') 
    dataXsec_750set1_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_750set1')
    dataXsec_750set2_ztar2p0 = B.get_data(f2p0, 'dataXsec_750set2') 
    dataXsec_750set2_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_750set2')
    dataXsec_750set3_ztar2p0 = B.get_data(f2p0, 'dataXsec_750set3') 
    dataXsec_750set3_err_ztar2p0 = B.get_data(f2p0, 'dataXsec_err_750set3')
    # |Ztar| < 1.5 cm
    dataXsec_80_ztar1p5 = B.get_data(f1p5, 'dataXsec_80') 
    dataXsec_80_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_80') 
    dataXsec_580set1_ztar1p5 = B.get_data(f1p5, 'dataXsec_580set1') 
    dataXsec_580set1_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_580set1')
    dataXsec_580set2_ztar1p5 = B.get_data(f1p5, 'dataXsec_580set2') 
    dataXsec_580set2_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_580set2')
    dataXsec_750set1_ztar1p5 = B.get_data(f1p5, 'dataXsec_750set1') 
    dataXsec_750set1_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_750set1')
    dataXsec_750set2_ztar1p5 = B.get_data(f1p5, 'dataXsec_750set2') 
    dataXsec_750set2_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_750set2')
    dataXsec_750set3_ztar1p5 = B.get_data(f1p5, 'dataXsec_750set3') 
    dataXsec_750set3_err_ztar1p5 = B.get_data(f1p5, 'dataXsec_err_750set3')
    # |Ztar| < 1.0 cm
    dataXsec_80_ztar1p0 = B.get_data(f1p0, 'dataXsec_80') 
    dataXsec_80_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_80') 
    dataXsec_580set1_ztar1p0 = B.get_data(f1p0, 'dataXsec_580set1') 
    dataXsec_580set1_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_580set1')
    dataXsec_580set2_ztar1p0 = B.get_data(f1p0, 'dataXsec_580set2') 
    dataXsec_580set2_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_580set2')
    dataXsec_750set1_ztar1p0 = B.get_data(f1p0, 'dataXsec_750set1') 
    dataXsec_750set1_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_750set1')
    dataXsec_750set2_ztar1p0 = B.get_data(f1p0, 'dataXsec_750set2') 
    dataXsec_750set2_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_750set2')
    dataXsec_750set3_ztar1p0 = B.get_data(f1p0, 'dataXsec_750set3') 
    dataXsec_750set3_err_ztar1p0 = B.get_data(f1p0, 'dataXsec_err_750set3')
    # |Ztar| < 0.5 cm
    dataXsec_80_ztar0p5 = B.get_data(f0p5, 'dataXsec_80') 
    dataXsec_80_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_80') 
    dataXsec_580set1_ztar0p5 = B.get_data(f0p5, 'dataXsec_580set1') 
    dataXsec_580set1_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_580set1')
    dataXsec_580set2_ztar0p5 = B.get_data(f0p5, 'dataXsec_580set2') 
    dataXsec_580set2_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_580set2')
    dataXsec_750set1_ztar0p5 = B.get_data(f0p5, 'dataXsec_750set1') 
    dataXsec_750set1_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_750set1')
    dataXsec_750set2_ztar0p5 = B.get_data(f0p5, 'dataXsec_750set2') 
    dataXsec_750set2_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_750set2')
    dataXsec_750set3_ztar0p5 = B.get_data(f0p5, 'dataXsec_750set3') 
    dataXsec_750set3_err_ztar0p5 = B.get_data(f0p5, 'dataXsec_err_750set3')


    #Define pmiss bins to plot
    pm_arr = [0.02, 0.06, 0.100, 0.140, 0.180, 0.220, 0.260, 0.300, 0.340, 0.380, 0.420, 0.460, 0.500, 0.540, 0.580, 0.620, 0.660, 0.700, 0.740, 0.780, 0.820, 0.860, 0.900, 0.940, 0.980, 1.020, 1.060]

    
    #Loop over central Pmiss bins
    for i, ipm in enumerate(pm_arr):
        print('Loop over Pmiss: ', ipm, 'GeV/c')

        B.pl.figure(i)
        B.pl.clf()
        
        pm_i = ipm * 1000.    #Pmiss converter to MeV
        pmi_min = pm_i - 20.
        pmi_max = pm_i + 20.

        #PM=80 MeV
        B.plot_exp(3.0, dataXsec_80_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s', label=r'80 MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_80_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(2.0, dataXsec_80_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(1.5, dataXsec_80_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(1.0, dataXsec_80_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(0.5, dataXsec_80_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_80_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_80_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_80_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_80_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_80_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_80_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
         
        y3p0max  = dataXsec_80_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_80_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_80_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_80_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_80_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_80_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/80set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 80 MeV')

        #------------------------PM=580 MeV (set1)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+1)
        B.pl.clf()


        #PM=580 MeV
        B.plot_exp(3.0, dataXsec_580set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_580set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(2.0, dataXsec_580set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(1.5, dataXsec_580set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(1.0, dataXsec_580set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.5, dataXsec_580set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_580set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_580set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_580set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_580set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_580set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_580set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
        
        y3p0max  = dataXsec_580set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_580set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_580set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_580set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_580set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_580set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set1) MeV')

        #------------------------PM=580 MeV (set2)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+2)
        B.pl.clf()


        #PM=580 MeV
        B.plot_exp(3.0, dataXsec_580set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_580set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(2.0, dataXsec_580set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(1.5, dataXsec_580set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(1.0, dataXsec_580set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.5, dataXsec_580set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_580set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_580set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_580set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_580set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_580set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_580set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
        
        y3p0max  = dataXsec_580set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_580set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_580set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_580set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_580set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_580set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 580 (set2) MeV')
        #------------------------PM=750 MeV (set1)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+3)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(3.0, dataXsec_750set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_750set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(2.0, dataXsec_750set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.5, dataXsec_750set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.0, dataXsec_750set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.5, dataXsec_750set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_750set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_750set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_750set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_750set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_750set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
        
        y3p0max  = dataXsec_750set1_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_750set1_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_750set1_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_750set1_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set1_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_750set1_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        

        B.pl.close()
        print('Finished 750 (set1) MeV')
        #------------------------PM=750 MeV (set2)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+4)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(3.0, dataXsec_750set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_750set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(2.0, dataXsec_750set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.5, dataXsec_750set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.0, dataXsec_750set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.5, dataXsec_750set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_750set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_750set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_750set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_750set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_750set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
        
        y3p0max  = dataXsec_750set2_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_750set2_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_750set2_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_750set2_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set2_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_750set2_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set2) MeV')
        #------------------------PM=750 MeV (set3)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+5)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(3.0, dataXsec_750set3_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set3) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(2.5, dataXsec_750set3_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(2.0, dataXsec_750set3_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.5, dataXsec_750set3_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(1.0, dataXsec_750set3_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.5, dataXsec_750set3_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y3p0min  = dataXsec_750set3_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5min  = dataXsec_750set3_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0min  = dataXsec_750set3_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5min  = dataXsec_750set3_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set3_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5min  = dataXsec_750set3_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]
        
        y3p0max  = dataXsec_750set3_ztar3p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar3p0[(pm==ipm) & (thnq==thnq_bin)]
        y2p5max  = dataXsec_750set3_ztar2p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar2p5[(pm==ipm) & (thnq==thnq_bin)]
        y2p0max  = dataXsec_750set3_ztar2p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar2p0[(pm==ipm) & (thnq==thnq_bin)]
        y1p5max  = dataXsec_750set3_ztar1p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar1p5[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set3_ztar1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p5max  = dataXsec_750set3_ztar0p5[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ztar0p5[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y3p0min, y2p5min, y2p0min, y1p5min,  y1p0min, y0p5min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y3p0max, y2p5max, y2p0max, y1p5max,  y1p0max, y0p5max])
        

        B.pl.xlabel(r'$Z_{tar}$ Difference Cut Setting [cm]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set3_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set3) MeV')

def plotXsec_vs_hCollcuts(study='', stats_thrs=0., thnq_bin = 0):
    
    print('Plot Data Cross Sections vs. Em Cuts')
    print('theta_nq setting:', thnq_bin)
    
    #Plot Cross Sections vs. Ztar Cuts for multiple Pmiss bins at fixed theta_nq bin 
    #theta_nq bins: 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 (Choose on for input)
    #(Purpose: Try to understand how the Xsec varies with different Ztar cut ranges)

    stats_thrs = stats_thrs*100.
 
    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Set FileNames to be read
    f1p0_name="../datafiles/"+study_dir+"systematicshColl1.0.txt"
    f0p9_name="../datafiles/"+study_dir+"systematicshColl0.9.txt"
    f0p8_name="../datafiles/"+study_dir+"systematicshColl0.8.txt"


    f1p0 = B.get_file(f1p0_name)
    f0p9 = B.get_file(f0p9_name)
    f0p8 = B.get_file(f0p8_name)


    #Get the Bin Inforamtion
    thnq = B.get_data(f1p0, 'xb') 
    pm = B.get_data(f1p0, 'yb') 

    #Get the Xsec and its Error
    # hColl Scale: 1.1  (TOTAL SET)
    dataXsec_80_hColl1p1 = B.get_data(f1p0, 'dataXsec_80_nom') 
    dataXsec_80_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_80_nom') 
    dataXsec_580set1_hColl1p1 = B.get_data(f1p0, 'dataXsec_580set1_nom') 
    dataXsec_580set1_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_580set1_nom')
    dataXsec_580set2_hColl1p1 = B.get_data(f1p0, 'dataXsec_580set2_nom') 
    dataXsec_580set2_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_580set2_nom')
    dataXsec_750set1_hColl1p1 = B.get_data(f1p0, 'dataXsec_750set1_nom') 
    dataXsec_750set1_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_750set1_nom')
    dataXsec_750set2_hColl1p1 = B.get_data(f1p0, 'dataXsec_750set2_nom') 
    dataXsec_750set2_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_750set2_nom')
    dataXsec_750set3_hColl1p1 = B.get_data(f1p0, 'dataXsec_750set3_nom') 
    dataXsec_750set3_err_hColl1p1 = B.get_data(f1p0, 'dataXsec_err_750set3_nom')
    # hColl Scale 1.0
    dataXsec_80_hColl1p0 = B.get_data(f1p0, 'dataXsec_80') 
    dataXsec_80_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_80') 
    dataXsec_580set1_hColl1p0 = B.get_data(f1p0, 'dataXsec_580set1') 
    dataXsec_580set1_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_580set1')
    dataXsec_580set2_hColl1p0 = B.get_data(f1p0, 'dataXsec_580set2') 
    dataXsec_580set2_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_580set2')
    dataXsec_750set1_hColl1p0 = B.get_data(f1p0, 'dataXsec_750set1') 
    dataXsec_750set1_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_750set1')
    dataXsec_750set2_hColl1p0 = B.get_data(f1p0, 'dataXsec_750set2') 
    dataXsec_750set2_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_750set2')
    dataXsec_750set3_hColl1p0 = B.get_data(f1p0, 'dataXsec_750set3') 
    dataXsec_750set3_err_hColl1p0 = B.get_data(f1p0, 'dataXsec_err_750set3')
    # hColl Scale 0.9
    dataXsec_80_hColl0p9 = B.get_data(f0p9, 'dataXsec_80') 
    dataXsec_80_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_80') 
    dataXsec_580set1_hColl0p9 = B.get_data(f0p9, 'dataXsec_580set1') 
    dataXsec_580set1_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_580set1')
    dataXsec_580set2_hColl0p9 = B.get_data(f0p9, 'dataXsec_580set2') 
    dataXsec_580set2_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_580set2')
    dataXsec_750set1_hColl0p9 = B.get_data(f0p9, 'dataXsec_750set1') 
    dataXsec_750set1_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_750set1')
    dataXsec_750set2_hColl0p9 = B.get_data(f0p9, 'dataXsec_750set2') 
    dataXsec_750set2_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_750set2')
    dataXsec_750set3_hColl0p9 = B.get_data(f0p9, 'dataXsec_750set3') 
    dataXsec_750set3_err_hColl0p9 = B.get_data(f0p9, 'dataXsec_err_750set3')
    # hColl Scale 0.8
    dataXsec_80_hColl0p8 = B.get_data(f0p8, 'dataXsec_80') 
    dataXsec_80_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_80') 
    dataXsec_580set1_hColl0p8 = B.get_data(f0p8, 'dataXsec_580set1') 
    dataXsec_580set1_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_580set1')
    dataXsec_580set2_hColl0p8 = B.get_data(f0p8, 'dataXsec_580set2') 
    dataXsec_580set2_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_580set2')
    dataXsec_750set1_hColl0p8 = B.get_data(f0p8, 'dataXsec_750set1') 
    dataXsec_750set1_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_750set1')
    dataXsec_750set2_hColl0p8 = B.get_data(f0p8, 'dataXsec_750set2') 
    dataXsec_750set2_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_750set2')
    dataXsec_750set3_hColl0p8 = B.get_data(f0p8, 'dataXsec_750set3') 
    dataXsec_750set3_err_hColl0p8 = B.get_data(f0p8, 'dataXsec_err_750set3')


    #Define pmiss bins to plot
    pm_arr = [0.02, 0.06, 0.100, 0.140, 0.180, 0.220, 0.260, 0.300, 0.340, 0.380, 0.420, 0.460, 0.500, 0.540, 0.580, 0.620, 0.660, 0.700, 0.740, 0.780, 0.820, 0.860, 0.900, 0.940, 0.980, 1.020, 1.060]

    
    #Loop over central Pmiss bins
    for i, ipm in enumerate(pm_arr):
        print('Loop over Pmiss: ', ipm, 'GeV/c')

        B.pl.figure(i)
        B.pl.clf()
        
        pm_i = ipm * 1000.    #Pmiss converter to MeV
        pmi_min = pm_i - 20.
        pmi_max = pm_i + 20.

        #PM=80 MeV
        B.plot_exp(1.1, dataXsec_80_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s', label=r'80 MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_80_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(0.9, dataXsec_80_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')
        B.plot_exp(0.8, dataXsec_80_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_80_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_80_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_80_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_80_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

         
        y1p1max  = dataXsec_80_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_80_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_80_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_80_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/80set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 80 MeV')

        #------------------------PM=580 MeV (set1)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+1)
        B.pl.clf()


        #PM=580 MeV
        B.plot_exp(1.1, dataXsec_580set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_580set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.9, dataXsec_580set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.8, dataXsec_580set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_580set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_580set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_580set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_580set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]
 
        y1p1max  = dataXsec_580set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_580set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_580set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_580set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set1) MeV')

        #------------------------PM=580 MeV (set2)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+2)
        B.pl.clf()


        #PM=580 MeV
        B.plot_exp(1.1, dataXsec_580set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_580set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.9, dataXsec_580set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')
        B.plot_exp(0.8, dataXsec_580set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_580set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_580set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_580set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_580set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]
  
        y1p1max  = dataXsec_580set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_580set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_580set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_580set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))

        B.pl.close()
        print('Finished 580 (set2) MeV')
        #------------------------PM=750 MeV (set1)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+3)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(1.1, dataXsec_750set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set1) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_750set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.9, dataXsec_750set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.8, dataXsec_750set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_750set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_750set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_750set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        y1p1max  = dataXsec_750set1_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set1_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_750set1_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_750set1_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        

        B.pl.close()
        print('Finished 750 (set1) MeV')
        #------------------------PM=750 MeV (set2)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+4)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(1.1, dataXsec_750set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set2) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_750set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.9, dataXsec_750set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.8, dataXsec_750set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_750set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_750set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_750set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        y1p1max  = dataXsec_750set2_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set2_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_750set2_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_750set2_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set2) MeV')
        #------------------------PM=750 MeV (set3)-------------------------                                                                                                                                                                                                                    

        B.pl.figure(i+5)
        B.pl.clf()


        #PM=750 MeV
        B.plot_exp(1.1, dataXsec_750set3_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 MeV (set3) Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1.0, dataXsec_750set3_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.9, dataXsec_750set3_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')
        B.plot_exp(0.8, dataXsec_750set3_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        y1p1min  = dataXsec_750set3_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0min  = dataXsec_750set3_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9min  = dataXsec_750set3_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8min  = dataXsec_750set3_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        y1p1max  = dataXsec_750set3_hColl1p1[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_hColl1p1[(pm==ipm) & (thnq==thnq_bin)]
        y1p0max  = dataXsec_750set3_hColl1p0[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_hColl1p0[(pm==ipm) & (thnq==thnq_bin)]
        y0p9max  = dataXsec_750set3_hColl0p9[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_hColl0p9[(pm==ipm) & (thnq==thnq_bin)]
        y0p8max  = dataXsec_750set3_hColl0p8[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_hColl0p8[(pm==ipm) & (thnq==thnq_bin)]

        ymin_arr = np.array([y1p1min, y1p0min, y0p9min, y0p8min])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([y1p1max, y1p0max, y0p9max, y0p8max])
        

        B.pl.xlabel(r'HMS Collimator Scale')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 
        
        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin))
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set3_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set3) MeV')

def plotXsec_vs_ctimecuts(study='', stats_thrs=0., thnq_bin = 0):

    print('Plot Data Cross Sections vs. Em Cuts')
    print('theta_nq setting:', thnq_bin)

    #Plot Cross Sections vs. Ztar Cuts for multiple Pmiss bins at fixed theta_nq bin 
    #theta_nq bins: 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 (Choose on for input)
    #(Purpose: Try to understand how the Xsec varies with different Ztar cut ranges)

    stats_thrs = stats_thrs*100.
 
    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Set FileNames to be read
    fc1_name="../datafiles/"+study_dir+"systematicsctimeON.txt"
    fc1 = B.get_file(fc1_name)

    #Get the Bin Inforamtion
    thnq = B.get_data(fc1, 'xb') 
    pm = B.get_data(fc1, 'yb') 

    #Get the Xsec and its Error
    # CTIME OFF  (TOTAL SET)
    dataXsec_80_ctimeOFF = B.get_data(fc1, 'dataXsec_80_nom') 
    dataXsec_80_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_80_nom') 
    dataXsec_580set1_ctimeOFF = B.get_data(fc1, 'dataXsec_580set1_nom') 
    dataXsec_580set1_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_580set1_nom')
    dataXsec_580set2_ctimeOFF = B.get_data(fc1, 'dataXsec_580set2_nom') 
    dataXsec_580set2_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_580set2_nom')
    dataXsec_750set1_ctimeOFF = B.get_data(fc1, 'dataXsec_750set1_nom') 
    dataXsec_750set1_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_750set1_nom')
    dataXsec_750set2_ctimeOFF = B.get_data(fc1, 'dataXsec_750set2_nom') 
    dataXsec_750set2_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_750set2_nom')
    dataXsec_750set3_ctimeOFF = B.get_data(fc1, 'dataXsec_750set3_nom') 
    dataXsec_750set3_err_ctimeOFF = B.get_data(fc1, 'dataXsec_err_750set3_nom')
    # CTIME ON
    dataXsec_80_ctimeON = B.get_data(fc1, 'dataXsec_80') 
    dataXsec_80_err_ctimeON = B.get_data(fc1, 'dataXsec_err_80') 
    dataXsec_580set1_ctimeON = B.get_data(fc1, 'dataXsec_580set1') 
    dataXsec_580set1_err_ctimeON = B.get_data(fc1, 'dataXsec_err_580set1')
    dataXsec_580set2_ctimeON = B.get_data(fc1, 'dataXsec_580set2') 
    dataXsec_580set2_err_ctimeON = B.get_data(fc1, 'dataXsec_err_580set2')
    dataXsec_750set1_ctimeON = B.get_data(fc1, 'dataXsec_750set1') 
    dataXsec_750set1_err_ctimeON = B.get_data(fc1, 'dataXsec_err_750set1')
    dataXsec_750set2_ctimeON = B.get_data(fc1, 'dataXsec_750set2') 
    dataXsec_750set2_err_ctimeON = B.get_data(fc1, 'dataXsec_err_750set2')
    dataXsec_750set3_ctimeON = B.get_data(fc1, 'dataXsec_750set3') 
    dataXsec_750set3_err_ctimeON = B.get_data(fc1, 'dataXsec_err_750set3')

    #Define pmiss bins to plot
    pm_arr = [0.02, 0.06, 0.100, 0.140, 0.180, 0.220, 0.260, 0.300, 0.340, 0.380, 0.420, 0.460, 0.500, 0.540, 0.580, 0.620, 0.660, 0.700, 0.740, 0.780, 0.820, 0.860, 0.900, 0.940, 0.980, 1.020, 1.060]
    
    #Loop over central Pmiss bins
    for i, ipm in enumerate(pm_arr):
        print('Loop over Pmiss: ', ipm, 'GeV/c')

        B.pl.figure(i)
        B.pl.clf()
        
        pm_i = ipm * 1000.    #Pmiss converter to MeV
        pmi_min = pm_i - 20.
        pmi_max = pm_i + 20.

        #PM=80 MeV
        B.plot_exp(0, dataXsec_80_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s', label=r'80 MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_80_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_80_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_80_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_80_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_80_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/80set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 80 MeV')

        
        #PM=580 (set1)
        B.pl.figure(i+1)
        B.pl.clf()

        B.plot_exp(0, dataXsec_580set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 (set1) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_580set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_580set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_580set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_580set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_580set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set1) MeV')

        #PM=580 (set2)
        B.pl.figure(i+2)
        B.pl.clf()

        B.plot_exp(0, dataXsec_580set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 (set2) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_580set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_580set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_580set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_580set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_580set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set2) MeV')

        #PM=750 (set1)
        B.pl.figure(i+3)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set1) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set1_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set1_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set1) MeV')

        #PM=750 (set2)
        B.pl.figure(i+4)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set2) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set2_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set2_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set2) MeV')

        #PM=750 (set3)
        B.pl.figure(i+5)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set3_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set3) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set3_ctimeON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set3_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set3_ctimeON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set3_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ctimeOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set3_ctimeON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_ctimeON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'Coincidence Time Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set3_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set3) MeV')


def plotXsec_vs_pcalcuts(study='', stats_thrs=0., thnq_bin = 0):

    print('Plot Data Cross Sections vs. SHMS Calorimeter Cuts')
    print('theta_nq setting:', thnq_bin)

    #Plot Cross Sections vs. Ztar Cuts for multiple Pmiss bins at fixed theta_nq bin 
    #theta_nq bins: 5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105 (Choose on for input)
    #(Purpose: Try to understand how the Xsec varies with different Ztar cut ranges)

    stats_thrs = stats_thrs*100.
 
    #check if directory to store systematics exists, else creates it.
    study_dir = study+"_study/"
    dir_name = "../full_systematics_plots/"+study_dir
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    #Set FileNames to be read
    fc1_name="../datafiles/"+study_dir+"systematicsshmsCalON.txt"
    fc1 = B.get_file(fc1_name)

    #Get the Bin Inforamtion
    thnq = B.get_data(fc1, 'xb') 
    pm = B.get_data(fc1, 'yb') 

    #Get the Xsec and its Error
    # PCAL OFF  (TOTAL SET)
    dataXsec_80_pcalOFF = B.get_data(fc1, 'dataXsec_80_nom') 
    dataXsec_80_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_80_nom') 
    dataXsec_580set1_pcalOFF = B.get_data(fc1, 'dataXsec_580set1_nom') 
    dataXsec_580set1_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_580set1_nom')
    dataXsec_580set2_pcalOFF = B.get_data(fc1, 'dataXsec_580set2_nom') 
    dataXsec_580set2_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_580set2_nom')
    dataXsec_750set1_pcalOFF = B.get_data(fc1, 'dataXsec_750set1_nom') 
    dataXsec_750set1_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_750set1_nom')
    dataXsec_750set2_pcalOFF = B.get_data(fc1, 'dataXsec_750set2_nom') 
    dataXsec_750set2_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_750set2_nom')
    dataXsec_750set3_pcalOFF = B.get_data(fc1, 'dataXsec_750set3_nom') 
    dataXsec_750set3_err_pcalOFF = B.get_data(fc1, 'dataXsec_err_750set3_nom')
    # PCAL ON
    dataXsec_80_pcalON = B.get_data(fc1, 'dataXsec_80') 
    dataXsec_80_err_pcalON = B.get_data(fc1, 'dataXsec_err_80') 
    dataXsec_580set1_pcalON = B.get_data(fc1, 'dataXsec_580set1') 
    dataXsec_580set1_err_pcalON = B.get_data(fc1, 'dataXsec_err_580set1')
    dataXsec_580set2_pcalON = B.get_data(fc1, 'dataXsec_580set2') 
    dataXsec_580set2_err_pcalON = B.get_data(fc1, 'dataXsec_err_580set2')
    dataXsec_750set1_pcalON = B.get_data(fc1, 'dataXsec_750set1') 
    dataXsec_750set1_err_pcalON = B.get_data(fc1, 'dataXsec_err_750set1')
    dataXsec_750set2_pcalON = B.get_data(fc1, 'dataXsec_750set2') 
    dataXsec_750set2_err_pcalON = B.get_data(fc1, 'dataXsec_err_750set2')
    dataXsec_750set3_pcalON = B.get_data(fc1, 'dataXsec_750set3') 
    dataXsec_750set3_err_pcalON = B.get_data(fc1, 'dataXsec_err_750set3')

    #Define pmiss bins to plot
    pm_arr = [0.02, 0.06, 0.100, 0.140, 0.180, 0.220, 0.260, 0.300, 0.340, 0.380, 0.420, 0.460, 0.500, 0.540, 0.580, 0.620, 0.660, 0.700, 0.740, 0.780, 0.820, 0.860, 0.900, 0.940, 0.980, 1.020, 1.060]
    
    #Loop over central Pmiss bins
    for i, ipm in enumerate(pm_arr):
        print('Loop over Pmiss: ', ipm, 'GeV/c')

        B.pl.figure(i)
        B.pl.clf()
        
        pm_i = ipm * 1000.    #Pmiss converter to MeV
        pmi_min = pm_i - 20.
        pmi_max = pm_i + 20.

        #PM=80 MeV
        B.plot_exp(0, dataXsec_80_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s', label=r'80 MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_80_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_80_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='black', marker='s')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_80_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_80_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_80_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_80_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_80_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_80_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/80set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 80 MeV')

        
        #PM=580 (set1)
        B.pl.figure(i+1)
        B.pl.clf()

        B.plot_exp(0, dataXsec_580set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 (set1) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_580set1_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_580set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_580set1_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_580set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_580set1_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set1) MeV')

        #PM=580 (set2)
        B.pl.figure(i+2)
        B.pl.clf()

        B.plot_exp(0, dataXsec_580set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o', label=r'580 (set2) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_580set2_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_580set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='red', marker='o')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_580set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_580set2_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_580set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_580set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_580set2_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_580set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/580set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 580 (set2) MeV')

        #PM=750 (set1)
        B.pl.figure(i+3)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set1) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set1_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set1_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set1_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set1_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set1_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set1_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set1) MeV')

        #PM=750 (set2)
        B.pl.figure(i+4)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set2) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set2_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set2_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set2_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set2_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set2_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set2_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set2) MeV')

        #PM=750 (set3)
        B.pl.figure(i+5)
        B.pl.clf()

        B.plot_exp(0, dataXsec_750set3_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^', label=r'750 (set3) MeV Systematics ($P_{m}$=%i, $\theta_{nq}$=%i)'%(pm_i, thnq_bin))
        B.plot_exp(1, dataXsec_750set3_pcalON[(pm==ipm) & (thnq==thnq_bin)], dataXsec_750set3_err_pcalON[(pm==ipm) & (thnq==thnq_bin)], color='green', marker='^')

        #Set Min,Max Y for plotting
        yOFFmin  = dataXsec_750set3_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmin  = dataXsec_750set3_pcalON[(pm==ipm) & (thnq==thnq_bin)] - 2.*dataXsec_750set3_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]

        yOFFmax  = dataXsec_750set3_pcalOFF[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_pcalOFF[(pm==ipm) & (thnq==thnq_bin)]
        yONmax  = dataXsec_750set3_pcalON[(pm==ipm) & (thnq==thnq_bin)] + 2.*dataXsec_750set3_err_pcalON[(pm==ipm) & (thnq==thnq_bin)]
       

        ymin_arr = np.array([yOFFmin,yONmin])
        ymin_arr = np.ma.array(ymin_arr, mask=(ymin_arr<0))   #mask negative min. values

        ymax_arr = np.array([yOFFmax, yONmax])
        

        B.pl.xlabel(r'SHMS Calorimeter Cut [ON=1, OFF=0]')                                                                                                                                     
        B.pl.ylabel(r'$\frac{d\sigma}{d\Omega}$')                                                                                                                                          
        ymin=np.ma.MaskedArray.min(ymin_arr)
        ymax=max(ymax_arr)
        B.pl.ylim(ymin, ymax) 

        B.pl.title(r'Data Xsec: Pm:(%i $\pm$ 20) MeV, $\theta_{nq}$:(%i $\pm$ 5$^{\circ}$)'%(pm_i, thnq_bin)) 
        B.pl.legend(loc='upper right', fontsize='xx-small')  
        if(max(ymax_arr) > 0.0):
            B.pl.savefig(dir_name+'/750set3_pmBin%i_thnqBin%i.pdf'%(pm_i, thnq_bin))
        
        B.pl.close()
        print('Finished 750 (set3) MeV')


