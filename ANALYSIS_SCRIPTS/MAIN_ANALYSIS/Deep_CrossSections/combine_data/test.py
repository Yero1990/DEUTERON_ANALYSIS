import numpy as np
from LT.datafile import dfile
import LT.box as B
import matplotlib.pyplot as plt
from matplotlib import rc
from matplotlib.legend_handler import HandlerLine2D, HandlerTuple


#Use latex commands (e.g. \textit ot \textbf)
rc('text', usetex=True)

#Set default font to times new roman
font = {'family' : 'Times New Roman',
        'weight' : 'normal',
        'size'   : 12
}
plt.rc('font', **font)

#Set font
csfont = {'fontname':'Times New Roman'}

def plot_report():

    #-------Plot the report file quantities: trigger rates, efficiencies (detector, live time, etc.), 
    def get_fname(pm_set, data_set):
        fname='../../root_files/pm%i_fsiXsec_set%i_Em_final40MeV/report_deep_pm%i_set%i.dat'%(pm_set, data_set, pm_set, data_set)
        return fname

    def get_var(pm_set=0, data_set=0, var=''):
        fvar = np.array(dfile(get_fname(pm_set,data_set))[var])
        return fvar
         
    def get_heep_var(var=''):
        fname='../../root_files/HEEP_ELASTICS/report_heep.dat'
        fvar = np.array(dfile(fname)[var])
        return fvar

    
    #---------------Plot Accepted COin. Triggers Counts per charge---------------
    CPQ80_set1 = get_var(80,1,'ptrig6_accp')/get_var(80,1,'charge') ; CPQ80_set1_err = get_var(80,1,'ptrig6_accp')/get_var(80,1,'charge')**2 * (0.02*get_var(80,1,'charge'))
    CPQ580_set1 = get_var(580,1,'ptrig6_accp')/get_var(580,1,'charge') ; CPQ580_set1_err = get_var(580,1,'ptrig6_accp')/get_var(580,1,'charge')**2 * (0.02*get_var(580,1,'charge'))
    CPQ580_set2 = get_var(580,2,'ptrig6_accp')/get_var(580,2,'charge') ; CPQ580_set2_err = get_var(580,2,'ptrig6_accp')/get_var(580,2,'charge')**2 * (0.02*get_var(580,2,'charge'))
    CPQ750_set1 = get_var(750,1,'ptrig6_accp')/get_var(750,1,'charge') ; CPQ750_set1_err = get_var(750,1,'ptrig6_accp')/get_var(750,1,'charge')**2 * (0.02*get_var(750,1,'charge'))
    CPQ750_set2 = get_var(750,2,'ptrig6_accp')/get_var(750,2,'charge') ; CPQ750_set2_err = get_var(750,2,'ptrig6_accp')/get_var(750,2,'charge')**2 * (0.02*get_var(750,2,'charge'))
    CPQ750_set3 = get_var(750,3,'ptrig6_accp')/get_var(750,3,'charge') ; CPQ750_set3_err = get_var(750,3,'ptrig6_accp')/get_var(750,3,'charge')**2 * (0.02*get_var(750,3,'charge'))

    B.plot_exp(get_var(80,1,'Run'),   CPQ80_set1*0.06,   CPQ80_set1_err*0.06,  marker='^', color='k', label='80 (set1), scaled x0.06' )
    B.plot_exp(get_var(580,1,'Run'),  CPQ580_set1,  CPQ580_set1_err, marker='^', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  CPQ580_set2,  CPQ580_set2_err, marker='^', color='g', label='580 (set2)' )
    B.plot_exp(get_var(750,1,'Run'),  CPQ750_set1,  CPQ750_set1_err, marker='^', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  CPQ750_set2,  CPQ750_set2_err, marker='^', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  CPQ750_set3,  CPQ750_set3_err, marker='^', color='c', label='750 (set3)' )

    B.pl.xlabel('Run Number')
    B.pl.ylabel('Accepted Coin. Triggers / mC')
    B.pl.title('Accepted Coincidence Triggers / Charge vs. Run Number')

    B.pl.legend(loc='upper right')
    B.pl.show()
    #-------------------------------------------------------
    
    #---------------Plot Run vs Total Live Time---------------
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'tLT'), get_var(80,1,'tLT')*0.05,  marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'tLT'), get_var(580,1,'tLT')*0.05,  marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'tLT'), get_var(580,2,'tLT')*0.05,  marker='s', color='g', label='580 (set2)' )
  
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'tLT'), get_var(750,1,'tLT')*0.05,  marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'tLT'), get_var(750,2,'tLT')*0.05,  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'tLT'), get_var(750,3,'tLT')*0.05,  marker='s', color='c', label='750 (set3)' )
    B.pl.xlim(3288, 3410)
    B.pl.ylim(0.80, 1.05)
    B.pl.xlabel('Run Number')
    B.pl.ylabel('Total Live Time')
    B.pl.title('Total EDMT Live Time vs. Run Number')

    B.pl.legend(loc='upper right')
    B.pl.show()
    #-------------------------------------------------------
    
    
    #---------------Plot Run vs Tracking Efficiencies---------------
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'hTrkEff'), get_var(80,1,'hTrkEff_err'),  marker='s', color='k', label='HMS' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'hTrkEff'), get_var(580,1,'hTrkEff_err'),  marker='s', color='b', label='HMS ' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'hTrkEff'), get_var(580,2,'hTrkEff_err'),  marker='s', color='g', label='HMS  ' )
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'hTrkEff'), get_var(750,1,'hTrkEff_err'),  marker='s', color='r', label='HMS   ' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'hTrkEff'), get_var(750,2,'hTrkEff_err'),  marker='s', color='m', label='HMS     ' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'hTrkEff'), get_var(750,3,'hTrkEff_err'),  marker='s', color='c', label='HMS      ' )

    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'eTrkEff'), get_var(80,1,'eTrkEff_err'),  marker='s', mec='k', mfc='white', ecolor='k', label='SHMS ---- 80(set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'eTrkEff'), get_var(580,1,'eTrkEff_err'),  marker='s', mec='b', mfc='white', ecolor='b', label='SHMS ---- 580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'eTrkEff'), get_var(580,2,'eTrkEff_err'),  marker='s', mec='g', mfc='white', ecolor='g', label='SHMS ---- 580 (set2)' )
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'eTrkEff'), get_var(750,1,'eTrkEff_err'),  marker='s', mec='r', mfc='white', ecolor='r', label='SHMS ---- 750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'eTrkEff'), get_var(750,2,'eTrkEff_err'),  marker='s', mec='m', mfc='white', ecolor='m', label='SHMS ---- 750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'eTrkEff'), get_var(750,3,'eTrkEff_err'),  marker='s', mec='c', mfc='white', ecolor='c', label='SHMS ---- 750 (set3)' )
    
    B.pl.xlabel('Run Number')
    B.pl.ylabel('Tracking Efficiency')
    B.pl.title('Tracking Efficiency vs. Run Number')
    B.pl.ylim(0.9, 1.05)
    B.pl.xlim(3285, 3400)

    B.pl.legend(ncol=2, loc='upper right')
    B.pl.show()
    
    
    #---------------Plot Run vs Target Boiling Factor---------------
    #tgt_Boil = 1 - m*I  ; apply errror propagation
    m =  0.00080029      #LD2 slope
    sig_m = 0.00007037   
    dI_I = 2.0/100.      #relative error in current (assume 2%)
    sig_I_80 = dI_I * get_var(80,1,'avg_current') 
    sig_I_580set1 = dI_I * get_var(580,1,'avg_current') ;  sig_I_580set2 = dI_I * get_var(580,2,'avg_current')
    sig_I_750set1 = dI_I * get_var(750,1,'avg_current') ;  sig_I_750set2 = dI_I * get_var(750,2,'avg_current') ;  sig_I_750set3 = dI_I * get_var(750,3,'avg_current')

    tb_80_err = np.sqrt(  get_var(80,1,'avg_current')**2 * sig_m**2 + m**2 * sig_I_80**2  ) 
    tb_580set1_err = np.sqrt(  get_var(580,1,'avg_current')**2 * sig_m**2 + m**2 * sig_I_580set1**2  ) 
    tb_580set2_err = np.sqrt(  get_var(580,2,'avg_current')**2 * sig_m**2 + m**2 * sig_I_580set2**2  ) 
    tb_750set1_err = np.sqrt(  get_var(750,1,'avg_current')**2 * sig_m**2 + m**2 * sig_I_750set1**2  ) 
    tb_750set2_err = np.sqrt(  get_var(750,2,'avg_current')**2 * sig_m**2 + m**2 * sig_I_750set2**2  ) 
    tb_750set3_err = np.sqrt(  get_var(750,3,'avg_current')**2 * sig_m**2 + m**2 * sig_I_750set3**2  ) 


    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'tgtBoil_factor'), tb_80_err,  marker='s', mec='k', mfc='None', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'tgtBoil_factor'), tb_580set1_err,  marker='s', mec='b', mfc='None',label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'tgtBoil_factor'), tb_580set2_err,  marker='s', mec='g', mfc='None',label='580 (set2)' )
  
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'tgtBoil_factor'), tb_750set1_err,  marker='s', mec='r', mfc='None',label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'tgtBoil_factor'), tb_750set2_err,  marker='s', mec='m', mfc='None',label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'tgtBoil_factor'), tb_750set3_err,  marker='s', mec='c', mfc='None',label='750 (set3)' )

    B.pl.xlabel('Run Number')
    B.pl.ylabel('Target Boiling Factor')
    B.pl.title('LD2 Boiling Factor vs. Run Number')
    B.pl.ylim(0.9, 1.05)
    B.pl.xlim(3285, 3400)

    B.pl.legend(loc='upper right')
    B.pl.show()
    #---------------------------------------------------------------
    
    
    #---------------Plot Run vs Average Beam Current---------------
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'avg_current'), get_var(80,1,'avg_current')*0.02,  marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'avg_current'), get_var(580,1,'avg_current')*0.02,  marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'avg_current'), get_var(580,2,'avg_current')*0.02,  marker='s', color='g', label='580 (set2)' )
  
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'avg_current'), get_var(750,1,'avg_current')*0.02,  marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'avg_current'), get_var(750,2,'avg_current')*0.02,  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'avg_current'), get_var(750,3,'avg_current')*0.02,  marker='s', color='c', label='750 (set3)' )

    B.pl.xlabel('Run Number')
    B.pl.ylabel(r'Average Beam Current [\mu A]')
    B.pl.title('Average Beam Current vs. Run Number')
    B.pl.ylim(40, 70)
    B.pl.xlim(3285, 3400)

    B.pl.legend(loc='upper right')
    B.pl.show()
    #-------------------------------------------------------
    

    
    #---------------Plot Run vs Trigger Rates---------------   
    B.pl.subplot(311)
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'ptrig1_rate'),   marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'ptrig1_rate'),   marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'ptrig1_rate'),  marker='s', color='g', label='580 (set2)' )
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'ptrig1_rate'),   marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'ptrig1_rate'),  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'ptrig1_rate'),   marker='s', color='c', label='750 (set3)' )
    B.pl.title('Trigger Rates vs. Run Number')
    B.pl.ylabel(r'SHMS Trigger Rate [kHz]')
    B.pl.xlim(3285, 3410)
    B.pl.legend(loc='upper right')

    #---------------------------
    B.pl.subplot(312)
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'ptrig4_rate')*0.2,   marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'ptrig4_rate'),   marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'ptrig4_rate'),  marker='s', color='g', label='580 (set2)' )
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'ptrig4_rate'),   marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'ptrig4_rate'),  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'ptrig4_rate'),   marker='s', color='c', label='750 (set3)' )
    B.pl.ylabel(r'HMS Trigger Rate [kHz]')
    B.pl.text(3400, 0.165, '$P_{m}=80$ MeV/c \n Scaled $x0.2$')
    B.pl.title('')
    B.pl.xlim(3285, 3410)
    #---------------------------
    B.pl.subplot(313)
    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'ptrig6_rate')*1000*0.02,   marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'ptrig6_rate')*1000,   marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'ptrig6_rate')*1000,  marker='s', color='g', label='580 (set2)' )
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'ptrig6_rate')*1000,   marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'ptrig6_rate')*1000,  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'ptrig6_rate')*1000,   marker='s', color='c', label='750 (set3)' )
    B.pl.ylabel(r'Coincidence Trigger Rate [Hz]')
    B.pl.text(3400, 3.0, '$P_{m}=80$ MeV/c \nScaled $x0.02$')
    B.pl.title('')

    B.pl.subplots_adjust(hspace=.001)
    B.pl.xlabel('Run Number')
    #B.pl.ylabel(r'Trigger Rate [kHz]')
    B.pl.xlim(3285, 3410)
    B.pl.show()
    
    #-------------------------------------------------------

    
    
    #---------------Plot Run vs BPM position---------------
    B.plot_exp(get_heep_var('Run'),  get_heep_var('xBPM'),  marker='D', color='gray', label='H(e,e\'p)' )

    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'xBPM'),  marker='s', color='k', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'xBPM'),  marker='s', color='b', label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'xBPM'),  marker='s', color='g', label='580 (set2)' )
  
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'xBPM'),  marker='s', color='r', label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'xBPM'),  marker='s', color='m', label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'xBPM'),  marker='s', color='c', label='750 (set3)' )
    #-------------
    B.plot_exp(get_heep_var('Run'),  get_heep_var('yBPM'),  marker='D', color='gray', mfc='none', label='H(e,e\'p)' )

    B.plot_exp(get_var(80,1,'Run'),  get_var(80,1,'yBPM'),  marker='s', color='k', mfc='none', label='80 (set1)' )
    B.plot_exp(get_var(580,1,'Run'),  get_var(580,1,'yBPM'),  marker='s', color='b',  mfc='none',label='580 (set1)' )
    B.plot_exp(get_var(580,2,'Run'),  get_var(580,2,'yBPM'),  marker='s', color='g', mfc='none', label='580 (set2)' )
  
    B.plot_exp(get_var(750,1,'Run'),  get_var(750,1,'yBPM'),  marker='s', color='r',  mfc='none',label='750 (set1)' )
    B.plot_exp(get_var(750,2,'Run'),  get_var(750,2,'yBPM'),  marker='s', color='m',  mfc='none',label='750 (set2)' )
    B.plot_exp(get_var(750,3,'Run'),  get_var(750,3,'yBPM'),  marker='s', color='c',  mfc='none',label='750 (set3)' )


    B.pl.xlabel('Run Number')
    B.pl.ylabel(r'BPM Position [cm]')
    B.pl.title('Beam Position Monitor vs. Run Number')
    B.pl.text(3290, 0.0325, r'X BPMs')
    B.pl.text(3290, 0.02, r'Y BPMs')
    B.pl.xlim(3285, 3410)

    B.pl.legend()
    B.pl.show()
    
    #-------------------------------------------------------
    
plot_report()