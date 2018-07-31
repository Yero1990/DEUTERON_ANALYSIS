#!/usr/bin/env python
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


#Ps1_factor = 1
#Pre-Scaled Ps1 HMS Computer Live Time : 2.8247 %
#Pre-Scaled Ps1 Total Live Time (EDTM) : 0.0000 %

def getLiveTimes():
    ignore_run = [2176, 2179,2181,2182,2183,2184,2185,2186,2196,2197,2198,2199,2200,2205,2210,2211,2212, 2217, 2218, 2223, 2224,
              2229, 2230, 2231, 2232, 2233, 2234, 2235, 2236, 2237, 2238, 2239, 2240, 2241, 2242, 2243, 2244, 2245, 2246, 2247, 2248, 2249,
              2250, 2251, 2260, 2261, 2262]
    lst = []
    lst.append(['Run', 'PS1_factor', 'PS1_CPU_LT', 'PS1_Total_LT', 'hT1_rate', 'edtm_rate', 'phy_rate' ])

    #Loop over hms delta scan runs
    for i in range(2173,2266,1):
        #ignore some runs
        if (i in ignore_run): continue
        #print ('Run: ',i)
        reportFile = "../hallc_replay/REPORT_OUTPUT/HMS/SCALERS/replay_hms_scalers_%d_-1.report"% (i)
        print (reportFile)
        #Open report file
        f = open(reportFile)

        #Read each line in the report file
        for line in f:
            #split each line using ':' delimiter
            data = re.split('=|:',line)
            #specify which variables to read data[0]: contains the name data[1] contains the value
            if (("Run #" in data[0])):
                run=data[1].strip()
                #print (run)
            if (("Ps1_factor" in data[0])):
                ps1_fact=data[1].strip()
                #print (ps1_fact)
            if (("Pre-Scaled Ps1 HMS Computer Live Time" in data[0])):
                ps1_CLT=(data[1].split())[0]
                #print(ps1_CLT)
            if (("Pre-Scaled Ps1 Total Live Time" in data[0])):                
                ps1_TLT=(data[1].split())[0]
                #print(ps1_TLT) 
            if (("HMS 3/4 Trigger Rate" in data[0])):                
                hms_34_rate=(data[1].split())[0]
                #print('hms3/4 rate = ',hms_34_rate)    
            if (("EDTM Trigger Rate" in data[0])):                
                edtm_rate=(data[1].split())[0]
                #print('edtm rate = ',edtm_rate)
            if (("Physics 3/4 Trigger Rate" in data[0])):                
                phy_34_rate=(data[1].split())[0]
                #print('phy3/4 rate = ',phy_34_rate)

        lst.append([int(run), int(ps1_fact), float(ps1_CLT), float(ps1_TLT), float(hms_34_rate), float(edtm_rate), float(phy_34_rate)]) 
    #print (lst)


    #write livetimes into a csv file
    with open("hms_livetime.csv", "w") as f:  
        wr = csv.writer(f)                                                                                                           
        wr.writerows(lst)                                     


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
    df = pd.read_csv('hms_livetime.csv')
    
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
    
    #print (df.loc[0:6, 'Run'])
    #print (df.loc[0:6, 'phy_rate'])

    #TESTING
    x = np.linspace(0, 11, 100)  

    plt.plot(x, dt_extended(x,3,155,5), linestyle='--', color='black', label='Buffer L3, Max=5')                                        
    plt.plot(x, dt_extended(x,3,155,10), linestyle='--', color='blue', label='Buffer L3, Max=10') 
    plt.plot(x, dt_extended(x,3,155,15), linestyle='--', color='red', label='Buffer L3, Max=15') 
    plt.plot(x, dt_extended(x,3,155,100), linestyle='--', color='cyan', label='Buffer L3, Max=20')

    plt.legend(loc='best')
    plt.show()
'''

    #Plot Data: Buffer Level 1
    plt.scatter(df.loc[0:6, 'phy_rate'], df.loc[0:6, 'PS1_CPU_LT'], color='black', label='HMS CLT, Buffer 1' )
    plt.scatter(df.loc[7:10, 'phy_rate'], df.loc[7:10, 'PS1_CPU_LT'], color='red', label='HMS CLT, Buffer 2' ) 
    plt.scatter(df.loc[11:14, 'phy_rate'], df.loc[11:14, 'PS1_CPU_LT'], color='blue', label='HMS CLT, Buffer 3' ) 
    plt.scatter(df.loc[15:18, 'phy_rate'], df.loc[15:18, 'PS1_CPU_LT'], color='magenta', label='HMS CLT, Buffer 4' ) 

    #set xaxis (in kHz)
    x = np.linspace(0, 11, 100)

    #Set Busy MIN/MAX corresponding to different Buffer Levels

    #***Buffer Level 1****
    L1_BUSY_MIN = 155.         #micro-sec unit          
    L1_BUSY_MAX = 165.
    
    #Plot Buffer Level 1: Live Time Theory Curves
    plt.plot(x, dt_nonextended(x,L1_BUSY_MIN), linestyle='--', color='black', label='Buffer L1 Busy MIN=155us')
    plt.plot(x, dt_nonextended(x,L1_BUSY_MAX), linestyle=':', color='black', label='Buffer L1 Busy Max=165us')

    plt.plot(x, dt_extended(x,2,155), linestyle='--', color='red', label='Buffer L2 Busy Min=155 us')  
    plt.plot(x, dt_extended(x,2,165), linestyle=':', color='red', label='Buffer L2 Busy Min=165 us') 

    plt.plot(x, dt_extended(x,3,155), linestyle='--', color='blue', label='Buffer L3 Busy Min=155 us') 
    plt.plot(x, dt_extended(x,3,165), linestyle=':', color='blue', label='Buffer L3 Busy Min=165 us') 

    plt.plot(x, dt_extended(x,4,155), linestyle='--', color='magenta', label='Buffer L4 Busy Min=155 us')  
    plt.plot(x, dt_extended(x,4,165), linestyle=':', color='magenta', label='Buffer L4 Busy Min=165 us')     
   
    #Set Axes Labels
    plt.xlabel('Trigger Rate (kHz)')
    plt.ylabel('Live Time (%)')
    plt.title('HMS Live Time Measurements: Buffer Level 1-4')

    #Show theory curves
    plt.legend(loc='best')
    plt.show()

    plt.figure()
   

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
