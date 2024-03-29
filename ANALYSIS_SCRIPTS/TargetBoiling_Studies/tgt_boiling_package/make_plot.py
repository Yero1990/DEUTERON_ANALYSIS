import LT.box as B                                                                                                   
import numpy as np                                                                                                            
import matplotlib.pyplot as plt                                                                                          
from matplotlib import rc

rc('text', usetex=True)
#Set default font to times new roman
font = {'family' : 'Times New Roman',
        'weight' : 'bold',
        'size'   : 14
}
plt.rc('font', **font)

#USER INPUT
target='C12'     #C12,  LH2  or LD2

f = B.get_file('hms_%s_yield.data' % (target))                                                                                                   
run = B.get_data(f, 'Run')                                                                                                                
current = B.get_data(f, 'set_current')  
                  
avg_current_bcm4a = B.get_data(f, 'avg_current_bcm4a')  
sclY4a = B.get_data(f, 'sclY4a')                                                                                                                   
sclY_err4a = B.get_data(f, 'sclY_err4a')                                                                                                            
ntrkY4a = B.get_data(f, 'ntrkY4a')                                                                                                              
ntrkY_err4a = B.get_data(f, 'ntrkY_err4a')                                                                                                            
trkY4a = B.get_data(f, 'trkY4a')                                                                                                               
trkY_err4a = B.get_data(f, 'trkY_err4a') 

avg_current_bcm4b = B.get_data(f, 'avg_current_bcm4b')    
sclY4b = B.get_data(f, 'sclY4b')                                                                                                                        
sclY_err4b = B.get_data(f, 'sclY_err4b')                                                                                                 
ntrkY4b = B.get_data(f, 'ntrkY4b')                                                                                                    
ntrkY_err4b = B.get_data(f, 'ntrkY_err4b')                                                                                               
trkY4b = B.get_data(f, 'trkY4b')                                                                                          
trkY_err4b = B.get_data(f, 'trkY_err4b')

#Al. Dummy Run @ 40 uA
fAl = B.get_file('hms_Al_yield.data')                                                                                                   
Al_run = B.get_data(fAl, 'Run')                                                                                                                
Al_current = B.get_data(fAl, 'set_current')                                                                                                          
Al_sclY4a = B.get_data(fAl, 'sclY4a')                                                                                                                   
Al_sclY_err4a = B.get_data(fAl, 'sclY_err4a')                                                                                                            
Al_ntrkY4a = B.get_data(fAl, 'ntrkY4a')                                                                                                              
Al_ntrkY_err4a = B.get_data(fAl, 'ntrkY_err4a')                                                                                                            
Al_trkY4a = B.get_data(fAl, 'trkY4a')                                                                                                               
Al_trkY_err4a = B.get_data(fAl, 'trkY_err4a')    

Al_sclY4b = B.get_data(fAl, 'sclY4b')                                                                                                                        
Al_sclY_err4b = B.get_data(fAl, 'sclY_err4b')                                                                                                 
Al_ntrkY4b = B.get_data(fAl, 'ntrkY4b')                                                                                                    
Al_ntrkY_err4b = B.get_data(fAl, 'ntrkY_err4b')                                                                                               
Al_trkY4b = B.get_data(fAl, 'trkY4b')                                                                                          
Al_trkY_err4b = B.get_data(fAl, 'trkY_err4b')

#Al. dummy loop factors to account for the fact that cell walls are different thickness in dummy and cruogenic loops
#yield_corr = yield - Al_yield*Loop_factor, Loop factor = L_cryo / L_Al

C12_factor = 1.0
Loop2_factor = 0.262  #LH2, obtained from C. Morean
Loop3_factor = 0.244  #LD2

#uSER Should adjust this factor acordingly with the target chosen
factor = C12_factor

#Corrected Al. Yield for BCM4A using either LH2 and LD2 loop fators     
Al_sclY4a = Al_sclY4a*factor                                                                                              
Al_sclY_err4a = Al_sclY_err4a*factor                                                                                           
Al_ntrkY4a = Al_ntrkY4a*factor                                                                                                             
Al_ntrkY_err4a = Al_ntrkY_err4a*factor                                                                                                        
Al_trkY4a = Al_trkY4a*factor                                      
Al_trkY_err4a = Al_trkY_err4a*factor                   

#Corrected Al. Yield for BCM4B using either LH2 and LD2 loop fators     
Al_sclY4b = Al_sclY4b*factor                            
Al_sclY_err4b = Al_sclY_err4b*factor                    
Al_ntrkY4b = Al_ntrkY4b*factor                          
Al_ntrkY_err4b = Al_ntrkY_err4b*factor                  
Al_trkY4b = Al_trkY4b*factor                            
Al_trkY_err4b = Al_trkY_err4b*factor                    


#Subtract Al. Dummy from either Carbon Target (NO LOOP Factors), LH2 or LD2
#BCM4A
sclY4a_corr = sclY4a - Al_sclY4a
sclY_err4a_corr = np.sqrt(sclY_err4a**2 + Al_sclY_err4a**2)
ntrkY4a_corr = ntrkY4a - Al_ntrkY4a
ntrkY_err4a_corr = np.sqrt(ntrkY_err4a**2 + Al_ntrkY_err4a**2)
trkY4a_corr = trkY4a - Al_trkY4a
trkY_err4a_corr = np.sqrt(trkY_err4a**2 + Al_trkY_err4a**2)

#BCM4B
sclY4b_corr = sclY4b - Al_sclY4b
sclY_err4b_corr = np.sqrt(sclY_err4b**2 + Al_sclY_err4b**2)
ntrkY4b_corr = ntrkY4b - Al_ntrkY4b
ntrkY_err4b_corr = np.sqrt(ntrkY_err4b**2 + Al_ntrkY_err4b**2)
trkY4b_corr = trkY4b - Al_trkY4b
trkY_err4b_corr = np.sqrt(trkY_err4b**2 + Al_trkY_err4b**2)   


#--------------------------------------------

#FIT A LINE y = a + bI  (Using BCM4B, which seems to not saturate at higher currents)
sclY_fit = B.linefit(avg_current_bcm4b, sclY4b_corr, sclY_err4b_corr)
ntrkY_fit = B.linefit(avg_current_bcm4b, ntrkY4b_corr, ntrkY_err4b_corr)
trkY_fit = B.linefit(avg_current_bcm4b, trkY4b_corr, trkY_err4b_corr)


#Get Fit Parameters
scl_slope = sclY_fit.slope
scl_offset = sclY_fit.offset   
scl_slope_err = sclY_fit.sigma_s
scl_offset_err = sclY_fit.sigma_o 
scl_redChi2 = sclY_fit.chi_red

ntrk_slope = ntrkY_fit.slope
ntrk_offset = ntrkY_fit.offset   
ntrk_slope_err = ntrkY_fit.sigma_s
ntrk_offset_err = ntrkY_fit.sigma_o 
ntrk_redChi2 = ntrkY_fit.chi_red

trk_slope = trkY_fit.slope
trk_offset = trkY_fit.offset   
trk_slope_err = trkY_fit.sigma_s
trk_offset_err = trkY_fit.sigma_o 
trk_redChi2 = trkY_fit.chi_red


#-------------------
B.pl.subplot(3,1,1) #(nrows, ncol, index)

B.plot_exp(avg_current_bcm4b, sclY4b_corr, sclY_err4b_corr, color='black', marker='o', label='data: %s Scaler Yield'%(target))
#B.plot_line(sclY_fit.xpl, sclY_fit.ypl, color='red', label='fit: slope = %.4f +/- %.4f \n     offset = %.2f +/- %.2f  \n    $\chi^{2}_{red} = % f$' % (scl_slope, scl_slope_err, scl_offset, scl_offset_err, scl_redChi2))
B.plot_line(sclY_fit.xpl, sclY_fit.ypl, color='red', label='fit: slope = %.2E +/- %.1E \n     offset = %.2E +/- %.1E  \n    $\chi^{2}_{red} = % .2E$' % (scl_slope, scl_slope_err, scl_offset, scl_offset_err, scl_redChi2))

B.pl.xlabel('')
B.pl.ylabel('')
#B.pl.ylim(2270,2310)  #C12
B.pl.ylim(600,1000)  #C12
#B.pl.ylim(B.pl.ylim()[0], 4150)  #LH2
#B.pl.ylim(B.pl.ylim()[0], 7425)  #LD2

B.pl.title('HMS Boiling Studies (April 02, 2018)')                                                   
B.pl.legend(loc='upper right', prop={'size':12}, frameon=False)

#-------------------

B.pl.subplot(3,1,2) #(nrows, ncol, index)

B.plot_exp(avg_current_bcm4b, ntrkY4b_corr, ntrkY_err4b_corr, color='black', marker='o', label='data: %s no-tracking Yield'%(target))
#B.plot_line(ntrkY_fit.xpl, ntrkY_fit.ypl, color='red', label='fit: slope = %.4f +/- %.4f \n     offset = %.2f +/- %.2f  \n    $\chi^{2}_{red} = % f$' % (ntrk_slope, ntrk_slope_err, ntrk_offset, ntrk_offset_err, ntrk_redChi2))
B.plot_line(ntrkY_fit.xpl, ntrkY_fit.ypl, color='red', label='fit: slope = %.2E +/- %.1E \n     offset = %.2E +/- %.1E  \n    $\chi^{2}_{red} = % .2E$' % (ntrk_slope, ntrk_slope_err, ntrk_offset, ntrk_offset_err, ntrk_redChi2))     

B.pl.xlabel('')
B.pl.ylabel('Normalized Yield [Counts/mC]')
#B.pl.ylim(1055,1100) #C12
B.pl.ylim(200,1000)  #C12
#B.pl.ylim(B.pl.ylim()[0], 2325)  #LH2
#B.pl.ylim(B.pl.ylim()[0], 3825) #LD2

B.pl.title('')                                                   
B.pl.legend(loc='upper right', prop={'size':12}, frameon=False)

#---------------------

B.pl.subplot(3,1,3) #(nrows, ncol, index)

B.plot_exp(avg_current_bcm4b, trkY4b_corr, trkY_err4b_corr, color='black', marker='o', label='data: %s tracking Yield'%(target))
#B.plot_line(trkY_fit.xpl, trkY_fit.ypl, color='red', label='fit: slope = %.4f +/- %.4f \n     offset = %.2f +/- %.2f  \n    $\chi^{2}_{red} = % f$' % (trk_slope, trk_slope_err, trk_offset, trk_offset_err, trk_redChi2))
B.plot_line(trkY_fit.xpl, trkY_fit.ypl, color='red', label='fit: slope = %.2E +/- %.1E \n     offset = %.2E +/- %.1E  \n    $\chi^{2}_{red} = % .2E$' % (trk_slope, trk_slope_err, trk_offset, trk_offset_err, trk_redChi2)) 

B.pl.xlabel('BCM4B Avg. Current [uA]')
B.pl.ylabel('')
#B.pl.ylim(850,900) #C12
B.pl.ylim(200,1000)  #C12
#B.pl.ylim(B.pl.ylim()[0], 1855)  #LH2
#B.pl.ylim(B.pl.ylim()[0], 3050) #LD2
B.pl.title('')                                                   
B.pl.legend(loc='upper right', prop={'size':12},frameon=False)

#B.pl.show()


fig1 = B.pl.figure()
trkY4b = trkY4b / trk_offset
trkY_err4b = trkY_err4b / trk_offset
trkY_fit.ypl =  trkY_fit.ypl / trk_offset

B.plot_exp(avg_current_bcm4b, trkY4b_corr, trkY_err4b_corr, color='black', marker='o', label='data: %s tracking Yield'%(target))
#B.plot_line(trkY_fit.xpl, trkY_fit.ypl, color='red', label='fit: slope = %.4f +/- %.4f \n     offset = %.2f +/- %.2f  \n    $\chi^{2}_{red} = % f$' % (trk_slope, trk_slope_err, trk_offset, trk_offset_err, trk_redChi2))
B.plot_line(trkY_fit.xpl, trkY_fit.ypl, color='red', label='fit: slope = %.3E +/- %.2E \n     offset = %.3E +/- %.2E  \n    $\chi^{2}_{red} = %.2f$' % (trk_slope, trk_slope_err, trk_offset, trk_offset_err, trk_redChi2))                    



B.pl.show()


#------Normalize to 1-----
#B.pl.subplot(2,1,2)   #(nrows, ncol, index)
#sclY4b = sclY4b/offset   #normalize offset to 1
#B.plot_exp(avg_current_bcm4b, sclY4b, sclY_err4b, color='black', marker='o', label='C12 Scaler Yield')


#B.plot_line(ntrkY_fit.xpl, ntrkY_fit.ypl)
#B.plot_line(trkY_fit.xpl, trkY_fit.ypl)


