#!/usr/bin/env python
from LTfunctions import *
import sys
import os.path
import subprocess as sp
import re
import pandas as pd
import csv
import math 
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate
from scipy.interpolate import interp1d

def getLiveTimes():

    hms_run_list = []
    shms_run_list = []
    coin_run_list = []

    #HMS
    #f = open('hms_runlist_Aug-18-2018.txt', 'r')
    #for line in f:
    #    if('#' in line): continue
    #    hms_run_list.append(int(line))
    #f.close()
    #SHMS
    #f = open('shms_runlist_Aug-18-2018.txt', 'r')
    #for line in f:
    #    if('#' in line): continue
    #    shms_run_list.append(int(line))
    #f.close()

    #COIN
    f = open('coin_runlist_Aug-18-2018.txt', 'r')
    for line in f:
        if('#' in line): continue
        coin_run_list.append(int(line))
    f.close()
    
    hms_dat_list = []
    shms_dat_list = []
    coin_dat_list = []

    hms_dat_list.append(['Run', 'PS1_factor', 'PS1_CLT', 'PS1_TLT', 'hT1_rate', 'edtm_rate'])
    shms_dat_list.append(['Run', 'PS1_factor', 'PS1_CLT', 'PS1_TLT', 'pT1_rate', 'edtm_rate'])
    coin_dat_list.append(['Run', 'PS1_factor', 'PS4_factor', 'PS6_factor', 'PS1_CLT', 'PS4_CLT', 'PS6_CLT', 'PS1_TLT', 'PS4_TLT', 'PS6_TLT',  'pT1_rate', 'hT1_rate', 'coin_rate', 'edtm_rate'])
    
    #Call function to parse data from REPORT FILE
    coin_LT(coin_run_list, coin_dat_list)

#Buffer Level 1 (No Buffering)
def dt_nonextended(x, a):      #x [kHz],  a [u.sec]
    x = x*1e3   #covert to Hz
    a = a*1e-6  #convert to s
    dt = 100.*(x*a/(1. + x*a))
    lt = (100. - dt)
    return lt

#Buffer Level > 1
def dt_extended(x, buff_level, b, maxbuff):     #Definitions: x: rate [kHz], a: buffer level 1, 2, 3, ..., b: smallest TI busy [ns] (~100s ns in buffer > 1)
    dt = 0                      #deadtime
    a = buff_level
    x = x*1e3                 #convert to Hz
    b = b*1e-6                 #convert to seconds
    mu = b*x
    for i in range(a, maxbuff, 1):
        temp = np.power(mu,i) * np.exp(-1.0*mu) / float(math.factorial(i))
        dt = dt + temp
    dt = 100.*dt    #convert deadtime to percent
    lt = (100. - dt)
    return lt          #return live time



def main():
    print ('Entering main() . . . ')



    #write csv file with live time /trigger information
    #getLiveTimes()

    #Read .csv file containing magnet currents data     
    #data = np.genfromtxt('hms_livetime.csv', delimiter=',', names=True)       
    
    #Read .csv file into dataframe
    df1 = pd.read_csv('hms_livetime_aug14.csv')
    #print(df1)
    df2 = pd.read_csv('shms_livetime_aug14.csv')
    #print(df2)
    df3 = pd.read_csv('coin_livetime_2018-08-19.csv')                                                                                                                          


    #select rows 0:6, and column named 'Run'
    #print (df.loc[0:6, 'Run'])   #Buffer Level 1
    #print (df.loc[7:10, 'Run'])   #Buffer Level 2
    #print (df.loc[11:14, 'Run'])   #Buffer Level 3
    #print (df.loc[15:18, 'Run'])   #Buffer Level 4
    #print (df.loc[19:22, 'Run'])   #Buffer Level 5
    #print (df.loc[23:26, ['Run','phy_rate'] ])   #Buffer Level 6  select rows 23:26 and select multiple columns
    #print (df.loc[27:30, 'Run'])   #Buffer Level 7
    #print (df.loc[31:34, 'Run'])   #Buffer Level 8
    #print (df.loc[35:38, 'Run'])   #Buffer Level 9
    #print (df.loc[39:42, 'Run'])   #Buffer Level 10
    #print (df.loc[43:45, 'Run'])   #Buffer Level 20
    
    #print (df1['Run'].ix[[0,2,4]])   #select only specific indices in rows (row 0, 2, 4) for a given column 'Run'
  
    #print (df1['phy_rate']) #list of values in specified column


    #create figure 1
    #plt.figure()
    
    #plot HMS computer livetime with DAQ in SINGLES mode
    plt.scatter(df1['phy_rate'].ix[[0,2,4]], df1['PS1_CPU_LT'].ix[[0,2,4]], color='black', label='HMS CLT, Buffer 1' )
    plt.scatter(df1['phy_rate'].ix[[1,3,5]], df1['PS1_CPU_LT'].ix[[1,3,5]], color='red', label='HMS CLT, Buffer 10')

    #plot HMS computer livetime with DAQ in COIN mode
    plt.scatter(df3['hT1_rate'].ix[[6,8,10]], df3['PS4_CLT'].ix[[6,8,10]], marker='v', facecolors='none', edgecolors='black', s=80, label='COIN. Mode: HMS CLT, Buffer 1' ) 
    plt.scatter(df3['hT1_rate'].ix[[7,9,11]], df3['PS4_CLT'].ix[[7,9,11]], marker='v', facecolors='none', edgecolors='red', s=80, label='COIN. Mode: HMS CLT, Buffer 10') 

    
    

    x = np.linspace(0, 11, 100)

    #Set Busy MIN/MAX corresponding to different Buffer Levels

    #***Buffer Level 1****
    L1_BUSY_MIN = 155.         #micro-sec unit          
    L1_BUSY_MAX = 165.
    
    #Plot Buffer Level 1, 10: Live Time Theory Curves
    plt.plot(x, dt_nonextended(x,154), linestyle='--', color='black', label='Buffer L1 Busy MIN=154us')
    plt.plot(x, dt_nonextended(x,165), linestyle=':', color='black', label='Buffer L1 Busy Max=165us')

    #COIN MODE, BUffer 1 (HMS SINGLES)
    plt.plot(x, dt_nonextended(x,154), linestyle='--', color='black', label='Coin. Buffer L1 Busy MIN=154us')                            
    plt.plot(x, dt_nonextended(x,270), linestyle='-', color='black', label='Coin. Buffer L1 Busy Max=270us')     

    #HMS SINGLES MODE, BUffer 10
    plt.plot(x, dt_extended(x,10,154,40), linestyle='--', color='red', label='Buffer L10 Busy Min=154 us')                                                    
    plt.plot(x, dt_extended(x,10,165,40), linestyle=':', color='red', label='Buffer L10 Busy Min=165 us')   

    #COIN MODE, BUffer 10
    plt.plot(x, dt_extended(x,10,154,40), linestyle='--', color='red', label='Coin. Buffer L10 Busy Min=154 us') 
    plt.plot(x, dt_extended(x,10,270,40), linestyle='-', color='red', label='Coin. Buffer L10 Busy Min=270 us')  

    #Set Axes Labels
    plt.xlabel('Trigger Rate (kHz)')
    plt.ylabel('Live Time (%)')
    plt.title('HMS Live Time Measurements: Buffer Levels 1 and 10')

    plt.legend(loc='best')
    #plt.show()
   
    #create figure 2
    #plt.figure()
     
    #plot SHMS Computer Livetime with DAQ in SINGLES mode
    plt.scatter(df2['phy_rate'].ix[[0,2,4]], df2['PS1_CPU_LT'].ix[[0,2,4]], color='black', label='SHMS CLT, Buffer 1' )
    plt.scatter(df2['phy_rate'].ix[[1,3,5]], df2['PS1_CPU_LT'].ix[[1,3,5]], color='red', label='SHMS CLT, Buffer 10')

    #plot SHMS computer livetime with DAQ in COIN mode            
    plt.scatter(df3['pT1_rate'].ix[[12,14,16]], df3['PS1_CLT'].ix[[12,14,16]], marker='v', facecolors='none', edgecolors='black', s=80, label='COIN. Mode: SHMS CLT, Buffer 1' ) 
    plt.scatter(df3['pT1_rate'].ix[[13,15,17]], df3['PS1_CLT'].ix[[13,15,17]], marker='v', facecolors='none', edgecolors='red', s=80, label='COIN. Mode: SHMS CLT, Buffer 10')    

    x = np.linspace(0, 11, 100)

    #Set Busy MIN/MAX corresponding to different Buffer Levels

    #***Buffer Level 1****
    L1_BUSY_MIN = 152.         #micro-sec unit          
    L1_BUSY_MAX = 270.
    
    #Plot Buffer Level 1, 10: Live Time Theory Curves (Same BUSY for SHMS single as for COIN. mode since ROC02 is the master)
    plt.plot(x, dt_nonextended(x,154), linestyle='--', color='black', label='Buffer L1 Busy MIN=154us')
    plt.plot(x, dt_nonextended(x,270), linestyle='-', color='black', label='Buffer L1 Busy Max=270us')
    
    plt.plot(x, dt_extended(x,10,154,40), linestyle='--', color='red', label='Buffer L10 Busy Min=154 us')                                                    
    plt.plot(x, dt_extended(x,10,270,40), linestyle='-', color='red', label='Buffer L10 Busy Min=270 us')   

    #Set Axes Labels
    plt.xlabel('Trigger Rate (kHz)')
    plt.ylabel('Live Time (%)')
    plt.title('SHMS Live Time Measurements: Buffer Levels 1 and 10')

    plt.legend(loc='best')

    #plt.show()

    #create figure 3 --COIN LIVE TIME PLOTS                                                                                                                  
    plt.figure()                                                                                                                                                       

    #plot SHMS computer livetime with DAQ in COIN mode                                                                                     
    plt.scatter(df3['coin_rate'].ix[[0,2,4]], df3['PS6_CLT'].ix[[0,2,4]], marker='v', facecolors='none', edgecolors='black', s=80, label='COIN. CLT, Buffer 1' )  
    plt.scatter(df3['coin_rate'].ix[[1,3,5]], df3['PS6_CLT'].ix[[1,3,5]], marker='v', facecolors='none', edgecolors='red', s=80, label='COIN. CLT, Buffer 10')   

    x = np.linspace(0, 11, 100)                                                                                                                            
    #Set Busy MIN/MAX corresponding to different Buffer Levels                                                                        

    #Plot Buffer Level 1, 10: Live Time Theory Curves (Same BUSY for SHMS single as for COIN. mode since ROC02 is the master)      
    plt.plot(x, dt_nonextended(x,154), linestyle='--', color='black', label='Buffer L1 Busy MIN=154us')                                                             
    plt.plot(x, dt_nonextended(x,270), linestyle='-', color='black', label='Buffer L1 Busy Max=270us')               
                                                
    plt.plot(x, dt_extended(x,10,154,40), linestyle='--', color='red', label='Buffer L10 Busy Min=154 us')                                                  
    plt.plot(x, dt_extended(x,10,270,40), linestyle='-', color='red', label='Buffer L10 Busy Min=270 us')                            

    #Set Axes Labels                                                                                                                                            
    plt.xlabel('Trigger Rate (kHz)')                                                                                               
    plt.ylabel('Live Time (%)')                                                       
    plt.title('Coincidence Live Time Measurements: Buffer Levels 1 and 10')                                                                                                   
    plt.legend(loc='best')                                                                                                                                               
    plt.show() 

    #Plot Data: Buffer Level 1-5
    #plt.scatter(df.loc[0:6, 'phy_rate'], df.loc[0:6, 'PS1_CPU_LT'], color='black', label='HMS CLT, Buffer 1' )
    #plt.scatter(df.loc[7:10, 'phy_rate'], df.loc[7:10, 'PS1_CPU_LT'], color='red', label='HMS CLT, Buffer 2' ) 
    #plt.scatter(df.loc[11:14, 'phy_rate'], df.loc[11:14, 'PS1_CPU_LT'], color='blue', label='HMS CLT, Buffer 3' ) 
    #plt.scatter(df.loc[15:18, 'phy_rate'], df.loc[15:18, 'PS1_CPU_LT'], color='magenta', label='HMS CLT, Buffer 4' ) 
    #plt.scatter(df.loc[19:22, 'phy_rate'], df.loc[19:22, 'PS1_CPU_LT'], color='green', label='HMS CLT, Buffer 5' )                                             
    #set xaxis (in kHz)
    
    #Plot Data: Buffer Level 6-10
    #plt.scatter(df.loc[23:26, 'phy_rate'], df.loc[23:26, 'PS1_CPU_LT'], color='black', label='HMS CLT, Buffer 6' )     
    #plt.scatter(df.loc[27:30, 'phy_rate'], df.loc[27:30, 'PS1_CPU_LT'], color='red', label='HMS CLT, Buffer 7' )    
    #plt.scatter(df.loc[31:34, 'phy_rate'], df.loc[31:34, 'PS1_CPU_LT'], color='blue', label='HMS CLT, Buffer 8' )    
    #plt.scatter(df.loc[35:38, 'phy_rate'], df.loc[35:38, 'PS1_CPU_LT'], color='magenta', label='HMS CLT, Buffer 9' ) 
    #plt.scatter(df.loc[39:42, 'phy_rate'], df.loc[39:42, 'PS1_CPU_LT'], color='green', label='HMS CLT, Buffer 10' )    
    #set xaxis (in kHz)  



    #x = np.linspace(0, 11, 100)

    #Set Busy MIN/MAX corresponding to different Buffer Levels

    #***Buffer Level 1****
    #L1_BUSY_MIN = 155.         #micro-sec unit          
    #L1_BUSY_MAX = 165.
    
    #Plot Buffer Level 1-5: Live Time Theory Curves
    #plt.plot(x, dt_nonextended(x,L1_BUSY_MIN), linestyle='--', color='black', label='Buffer L1 Busy MIN=155us')
    #plt.plot(x, dt_nonextended(x,L1_BUSY_MAX), linestyle=':', color='black', label='Buffer L1 Busy Max=165us')

    #plt.plot(x, dt_extended(x,2,155,40), linestyle='--', color='red', label='Buffer L2 Busy Min=155 us')  
    #plt.plot(x, dt_extended(x,2,165,40), linestyle=':', color='red', label='Buffer L2 Busy Min=165 us') 

    #plt.plot(x, dt_extended(x,3,155,40), linestyle='--', color='blue', label='Buffer L3 Busy Min=155 us') 
    #plt.plot(x, dt_extended(x,3,165,40), linestyle=':', color='blue', label='Buffer L3 Busy Min=165 us') 

    #plt.plot(x, dt_extended(x,4,155,40), linestyle='--', color='magenta', label='Buffer L4 Busy Min=155 us')  
    #plt.plot(x, dt_extended(x,4,165,40), linestyle=':', color='magenta', label='Buffer L4 Busy Min=165 us')     

    #plt.plot(x, dt_extended(x,5,155,40), linestyle='--', color='green', label='Buffer L5 Busy Min=155 us')                            
    #plt.plot(x, dt_extended(x,5,165,40), linestyle=':', color='green', label='Buffer L5 Busy Min=165 us')    


    #Plot Buffer Level 6-10: Live Time Theory Curves    
    #plt.plot(x, dt_extended(x,6,155,40), linestyle='--', color='black', label='Buffer L6 Busy MIN=155us')   
    #plt.plot(x, dt_extended(x,6,165,40), linestyle=':', color='black', label='Buffer L6 Busy Max=165us')                                     
    
    #plt.plot(x, dt_extended(x,7,155,40), linestyle='--', color='red', label='Buffer L7 Busy Min=155 us')                                   
    #plt.plot(x, dt_extended(x,7,165,40), linestyle=':', color='red', label='Buffer L7 Busy Min=165 us')  
    
    #plt.plot(x, dt_extended(x,8,155,40), linestyle='--', color='blue', label='Buffer L8 Busy Min=155 us')                    
    #plt.plot(x, dt_extended(x,8,165,40), linestyle=':', color='blue', label='Buffer L8 Busy Min=165 us')       
    
    #plt.plot(x, dt_extended(x,9,155,40), linestyle='--', color='magenta', label='Buffer L9 Busy Min=155 us')                
    #plt.plot(x, dt_extended(x,9,165,40), linestyle=':', color='magenta', label='Buffer L9 Busy Min=165 us')            
    
    #plt.plot(x, dt_extended(x,10,155,40), linestyle='--', color='green', label='Buffer L10 Busy Min=155 us')                                                    
    #plt.plot(x, dt_extended(x,10,165,40), linestyle=':', color='green', label='Buffer L10 Busy Min=165 us')   

    #Set Axes Labels
    #plt.xlabel('Trigger Rate (kHz)')
    #plt.ylabel('Live Time (%)')
    #plt.title('HMS Live Time Measurements: Buffer Level 6-10')

    #Show theory curves
    #plt.legend(loc='best')
    #plt.show()


'''   

    #-------------------------BUFFER LEVEL = 2---------------------------

    bf = 2  #set buffer level counter to start at 2
    for i in range(7, 43, 4):
        print(i, i+3, bf)
        plt.figure()
        #Plot Data: Buffer Level > 1
        plt.scatter(df.loc[i:i+3, 'phy_rate'], df.loc[i:i+3, 'PS1_CPU_LT'], color='black', label='HMS Computer Live Time' )
        
        #Set Busy MIN/MAX corresponding to different Buffer Levels
        
        #Plot Buffer Level > 1: Live Time Theory Curves
        plt.plot(x, dt_extended(x,bf,190), linestyle='--', color='blue', label='Buffer L1 Busy = 190 ns')
        #plt.plot(x, dt_extended(x,bf,165), linestyle=':', color='blue', label='Buffer L1 Busy = 165 us')

        #Set Axes Labels
        plt.xlabel('Trigger Rate (kHz)')
        plt.ylabel('Live Time (%)')
        plt.title('HMS Live Time Measurements: Buffer Level %d' %(bf))
        
        #Show theory curves
        plt.legend(loc='best')
        plt.show()
        bf = bf+1
'''






if __name__=="__main__":
    main()
