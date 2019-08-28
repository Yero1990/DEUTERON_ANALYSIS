import LT.box as B                                                                                                   
import numpy as np                                                                                                            
import matplotlib.pyplot as plt                                                                                          


#C12
fC12 = B.get_file('hms_C12_yield.data')                                                                                                   
avg_current_bcm4b_C12 = B.get_data(fC12, 'avg_current_bcm4b')    
sclY4b_C12 = B.get_data(fC12, 'sclY4b')                                                                                                                        
sclY_err4b_C12 = B.get_data(fC12, 'sclY_err4b')                                                                                                 
ntrkY4b_C12 = B.get_data(fC12, 'ntrkY4b')                                                                                                    
ntrkY_err4b_C12 = B.get_data(fC12, 'ntrkY_err4b')                                                                                               
trkY4b_C12 = B.get_data(fC12, 'trkY4b')                                                                                          
trkY_err4b_C12 = B.get_data(fC12, 'trkY_err4b')

#LH2
fLH2 = B.get_file('hms_LH2_yield.data')                                                                                                   
avg_current_bcm4b_LH2 = B.get_data(fLH2, 'avg_current_bcm4b')    
sclY4b_LH2 = B.get_data(fLH2, 'sclY4b')                                                                                                                        
sclY_err4b_LH2 = B.get_data(fLH2, 'sclY_err4b')                                                                                                 
ntrkY4b_LH2 = B.get_data(fLH2, 'ntrkY4b')                                                                                                    
ntrkY_err4b_LH2 = B.get_data(fLH2, 'ntrkY_err4b')                                                                                               
trkY4b_LH2 = B.get_data(fLH2, 'trkY4b')                                                                                          
trkY_err4b_LH2 = B.get_data(fLH2, 'trkY_err4b')

#LD2
fLD2 = B.get_file('hms_LD2_yield.data')                                                                                                   
avg_current_bcm4b_LD2 = B.get_data(fLD2, 'avg_current_bcm4b')    
sclY4b_LD2 = B.get_data(fLD2, 'sclY4b')                                                                                                                        
sclY_err4b_LD2 = B.get_data(fLD2, 'sclY_err4b')                                                                                                 
ntrkY4b_LD2 = B.get_data(fLD2, 'ntrkY4b')                                                                                                    
ntrkY_err4b_LD2 = B.get_data(fLD2, 'ntrkY_err4b')                                                                                               
trkY4b_LD2 = B.get_data(fLD2, 'trkY4b')                                                                                          
trkY_err4b_LD2 = B.get_data(fLD2, 'trkY_err4b')



#--------------------------------------------

#FIT A LINE y = a + bI  (Using BCM4B, which seems to not saturate at higher currents)

#C12
sclY_fit_C12 = B.linefit(avg_current_bcm4b_C12, sclY4b_C12, sclY_err4b_C12)
ntrkY_fit_C12 = B.linefit(avg_current_bcm4b_C12, ntrkY4b_C12, ntrkY_err4b_C12)
trkY_fit_C12 = B.linefit(avg_current_bcm4b_C12, trkY4b_C12, trkY_err4b_C12)

#LH2
sclY_fit_LH2 = B.linefit(avg_current_bcm4b_LH2, sclY4b_LH2, sclY_err4b_LH2)
ntrkY_fit_LH2 = B.linefit(avg_current_bcm4b_LH2, ntrkY4b_LH2, ntrkY_err4b_LH2)
trkY_fit_LH2 = B.linefit(avg_current_bcm4b_LH2, trkY4b_LH2, trkY_err4b_LH2)

#LD2
sclY_fit_LD2 = B.linefit(avg_current_bcm4b_LD2, sclY4b_LD2, sclY_err4b_LD2)
ntrkY_fit_LD2 = B.linefit(avg_current_bcm4b_LD2, ntrkY4b_LD2, ntrkY_err4b_LD2)
trkY_fit_LD2 = B.linefit(avg_current_bcm4b_LD2, trkY4b_LD2, trkY_err4b_LD2)


#Get Fit Parameters C12
scl_slope_C12 = sclY_fit_C12.slope
scl_offset_C12 = sclY_fit_C12.offset   
scl_slope_err_C12 = sclY_fit_C12.sigma_s
scl_offset_err_C12 = sclY_fit_C12.sigma_o 

ntrk_slope_C12 = ntrkY_fit_C12.slope
ntrk_offset_C12 = ntrkY_fit_C12.offset   
ntrk_slope_err_C12 = ntrkY_fit_C12.sigma_s
ntrk_offset_err_C12 = ntrkY_fit_C12.sigma_o 

trk_slope_C12 = trkY_fit_C12.slope
trk_offset_C12 = trkY_fit_C12.offset   
trk_slope_err_C12 = trkY_fit_C12.sigma_s
trk_offset_err_C12 = trkY_fit_C12.sigma_o 

#Get Fit Parameters LH2
scl_slope_LH2 = sclY_fit_LH2.slope
scl_offset_LH2 = sclY_fit_LH2.offset   
scl_slope_err_LH2 = sclY_fit_LH2.sigma_s
scl_offset_err_LH2 = sclY_fit_LH2.sigma_o 

ntrk_slope_LH2 = ntrkY_fit_LH2.slope
ntrk_offset_LH2 = ntrkY_fit_LH2.offset   
ntrk_slope_err_LH2 = ntrkY_fit_LH2.sigma_s
ntrk_offset_err_LH2 = ntrkY_fit_LH2.sigma_o 

trk_slope_LH2 = trkY_fit_LH2.slope
trk_offset_LH2 = trkY_fit_LH2.offset   
trk_slope_err_LH2 = trkY_fit_LH2.sigma_s
trk_offset_err_LH2 = trkY_fit_LH2.sigma_o 

#Get Fit Parameters LD2
scl_slope_LD2 = sclY_fit_LD2.slope
scl_offset_LD2 = sclY_fit_LD2.offset   
scl_slope_err_LD2 = sclY_fit_LD2.sigma_s
scl_offset_err_LD2 = sclY_fit_LD2.sigma_o 

ntrk_slope_LD2 = ntrkY_fit_LD2.slope
ntrk_offset_LD2 = ntrkY_fit_LD2.offset   
ntrk_slope_err_LD2 = ntrkY_fit_LD2.sigma_s
ntrk_offset_err_LD2 = ntrkY_fit_LD2.sigma_o 

trk_slope_LD2 = trkY_fit_LD2.slope
trk_offset_LD2 = trkY_fit_LD2.offset   
trk_slope_err_LD2 = trkY_fit_LD2.sigma_s
trk_offset_err_LD2 = trkY_fit_LD2.sigma_o 

#SCALE THE DATA/FIT BY THE OFFSET FROM THE FIT TO OBTAIN A FRACTIONAL YIELD

#C12
trkY4b_C12 = trkY4b_C12 / trk_offset_C12
trkY_err4b_C12 = trkY_err4b_C12 / trk_offset_C12
trkY_fit_C12.ypl =  trkY_fit_C12.ypl / trk_offset_C12

trk_slope_C12 = trk_slope_C12 / trk_offset_C12
trk_slope_err_C12 = trk_slope_err_C12 / trk_offset_C12
trk_offset_err_C12 = trk_offset_err_C12 / trk_offset_C12   
trk_offset_C12 = trk_offset_C12 / trk_offset_C12  

#LH2
trkY4b_LH2 = trkY4b_LH2 / trk_offset_LH2
trkY_err4b_LH2 = trkY_err4b_LH2 / trk_offset_LH2
trkY_fit_LH2.ypl =  trkY_fit_LH2.ypl / trk_offset_LH2

trk_slope_LH2 = trk_slope_LH2 / trk_offset_LH2
trk_slope_err_LH2 = trk_slope_err_LH2 / trk_offset_LH2
trk_offset_err_LH2 = trk_offset_err_LH2 / trk_offset_LH2   
trk_offset_LH2 = trk_offset_LH2 / trk_offset_LH2   

#LD2
trkY4b_LD2 = trkY4b_LD2 / trk_offset_LD2
trkY_err4b_LD2 = trkY_err4b_LD2 / trk_offset_LD2
trkY_fit_LD2.ypl =  trkY_fit_LD2.ypl / trk_offset_LD2

trk_slope_LD2 = trk_slope_LD2 / trk_offset_LD2
trk_slope_err_LD2 = trk_slope_err_LD2 / trk_offset_LD2
trk_offset_err_LD2 = trk_offset_err_LD2 / trk_offset_LD2   
trk_offset_LD2 = trk_offset_LD2 / trk_offset_LD2   


fig1 = B.pl.figure()

#PLOT C12
B.plot_exp(avg_current_bcm4b_C12, trkY4b_C12, trkY_err4b_C12, color='black', marker='o', label='data: C12 tracking Yield')
B.plot_line(trkY_fit_C12.xpl, trkY_fit_C12.ypl, color='black', label='fit: slope = %.8f +/- %.8f \n     offset = %.2f +/- %.2f' % (trk_slope_C12, trk_slope_err_C12, trk_offset_C12, trk_offset_err_C12))

#PLOT LH2
B.plot_exp(avg_current_bcm4b_LH2, trkY4b_LH2, trkY_err4b_LH2, color='blue', marker='s', label='data: LH2 tracking Yield')
B.plot_line(trkY_fit_LH2.xpl, trkY_fit_LH2.ypl, color='blue', label='fit: slope = %.8f +/- %.8f \n     offset = %.2f +/- %.2f' % (trk_slope_LH2, trk_slope_err_LH2, trk_offset_LH2, trk_offset_err_LH2))

#PLOT LD2
B.plot_exp(avg_current_bcm4b_LD2, trkY4b_LD2, trkY_err4b_LD2, color='red', marker='^', label='data: LD2 tracking Yield')
B.plot_line(trkY_fit_LD2.xpl, trkY_fit_LD2.ypl, color='red', label='fit: slope = %.8f +/- %.8f \n     offset = %.2f +/- %.2f' % (trk_slope_LD2, trk_slope_err_LD2, trk_offset_LD2, trk_offset_err_LD2))



B.pl.title('HMS Boiling Studies (April 02, 2018)')                                                   
B.pl.xlabel('BCM4B Avg. Current [uA]')
B.pl.ylabel('Fractional Normalized Yield')
B.pl.legend(loc='upper right', prop={'size':10}, frameon=False)

B.pl.show()
