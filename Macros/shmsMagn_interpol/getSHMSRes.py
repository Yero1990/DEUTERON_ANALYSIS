#!/usr/bin/env python
import sys
import os.path
import subprocess as sp
import re
import csv
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate
from scipy.interpolate import interp1d


#------------------DEFINE FUNCTION TO Get Magnet CUrrents from a given Momentum--------------
#Usage: in main funciton, call:  getQ('mag', hmP)     #where mag = 'Q1', 'Q2', 'Q3', 'D', 'NMR', hmsP: momentum


def getQ(mag, shmsP):
    shms_file = "shms_tmp.data"

    #check if file exists (if it does, empty it . . .)
    if (os.path.exists(shms_file)):
        sp.call(("truncate -s 0 " + shms_file),shell=True)
    else:
    #create and append magnet 
        os.system("touch " + shms_file)

    #command to append field03 output currents to a dat file
    cmd = ("./../executables/getSHMS %s >> " + shms_file) %(shmsP)
    sp.call(cmd, shell=True)
    
    f = open(shms_file)    #open file
    cnt = 0               #reset line counter

 #Read each line
    for line in f:
        prefix = line.split(". MOL")[0]
        if (("Iset:" in prefix)):
            magnet = prefix.split()
            if (cnt==3):
                hb_val = magnet[1].strip()
          #      print (hb_val)
            if (cnt==6):  
                q1_val = magnet[1].strip()
          #      print (q1_val)
            if (cnt==9):
                q2_val = magnet[1].strip() 
          #      print (q2_val) 
            if (cnt==12):
                q3_val = magnet[1].strip()
          #      print (q3_val) 
            if (cnt==15):
                d_val = magnet[1].strip()
          #      print (d_val)
             
        cnt = cnt + 1
    
    if (mag is 'HB'):
#        print float(hb_val)
        return float(hb_val)
    if (mag is 'Q1'):
        #print float(q1_val)
        return float(q1_val)
    if (mag is 'Q2'):
        #print float(q2_val)
        return float(q2_val)
    if (mag is 'Q3'):
        #print float(q3_val)
        return float(q3_val)
    if (mag is 'D'):
        #print float(dipole_val)
        return float(d_val)
    
    #delete the file 
    os.system("rm shms_tmp.data")


def main():
    print ('Entering main() . . . ')


    #Read .csv file containing magnet currents data
    data = np.genfromtxt('shms_magnet_data.csv', delimiter=',', names=True)

    plt.plot(data['HB'], data['p'], label='HB', linewidth=2.0)
    plt.plot(data['Q1'], data['p'], label='Q1', linewidth=2.0)
    plt.plot(data['Q2'], data['p'], label='Q2', linewidth=2.0) 
    plt.plot(data['Q3'], data['p'], label='Q3', linewidth=2.0) 
    plt.plot(data['D'], data['p'], label='D', linewidth=2.0) 

    plt.title('SHMS Magnets Current Interpolation')
    plt.xlabel('SHMS Magnets Current [A]')
    plt.ylabel('SHMS Momentum [GeV/c]')
    
    
        
    #Interpolate data  Momentum (Current)
    fhb = interp1d(data['HB'], data['p'], kind='linear') 
    fq1 = interp1d(data['Q1'], data['p'], kind='linear')
    fq2 = interp1d(data['Q2'], data['p'], kind='linear')
    fq3 = interp1d(data['Q3'], data['p'], kind='linear')
    fdipole = interp1d(data['D'], data['p'], kind='linear')
    
    
    #plot interpolation
    xhb_min = getQ('HB', 2.0)                              
    xhb_max = getQ('HB', 11.0)                             
    xhb = np.linspace(xhb_min, xhb_max, 10)
    xq1_min = getQ('Q1', 2.0)
    xq1_max = getQ('Q1', 11.0)
    xq1 = np.linspace(xq1_min, xq1_max, 10)
    xq2_min = getQ('Q2', 2.0)                                         
    xq2_max = getQ('Q2', 11.0)                        
    xq2 = np.linspace(xq2_min, xq2_max, 10)
    xq3_min = getQ('Q3', 2.0)                     
    xq3_max = getQ('Q3', 11.0)                                   
    xq3 = np.linspace(xq3_min, xq3_max, 10)
    xd_min = getQ('D', 2.0)                                            
    xd_max = getQ('D', 11.0)                                            
    xd = np.linspace(xd_min, xd_max, 10)

    plt.scatter(xhb, fhb(xhb), color='black', marker='o', label='interpolation')
    plt.scatter(xq1, fq1(xq1), color='black', marker='o')
    plt.scatter(xq2, fq2(xq2), color='black', marker='o') 
    plt.scatter(xq3, fq3(xq3), color='black', marker='o') 
    plt.scatter(xd, fdipole(xd), color='black', marker='o') 

    plt.legend(loc='best')                        
    plt.savefig('shms_mag_interpol.pdf')
   
    # plt.show() 
'''
    #Make lists to store residuals
    HBres_list = []
    q1res_list = []
    q2res_list = []
    q3res_list = []
    Dres_list = []
   
    #magnes maximum allowable current (approx.)
    hb_max = getQ('HB', 11.0)
    q1_max = getQ('Q1', 11.0)
    q2_max = getQ('Q2', 11.0)
    q3_max = getQ('Q3', 11.0)
    D_max = getQ('D', 11.0)

    #Calculate Residuals (fq_interpolated - fq_data)
#    HBtest = 250.0                 #initial quad current [A]                                                                   
#    while HBtest <= 255.:        #Loop over current                                                                                           
#        Ptest = fhb(HBtest)      #interpolated fq1 (get momentum for each current)                                                              
 #       resHB = HBtest - getQ('HB', Ptest)  #determine residuals (diff. between current value and current from field03 (momentum))                               
#        HBres_list.append([round(Ptest,5), resHB])                                                                       print HBtest                                                                                                  

    Q1test = 1250.0                 #initial quad current [A]
    while Q1test <= 1255.:        #Loop over current
        Ptest = fq1(Q1test)      #interpolated fq1 (get momentum for each current)
        resq1 = Q1test - getQ('Q1', Ptest)  #determine residuals (diff. between current value and current from field03 (momentum))
        q1res_list.append([round(Ptest,5), resq1])
        print Q1test
        Q1test = Q1test + 0.05             #increment current by small amount
    
    Q2test = 1830.0 
    while Q2test <= 1835.:
        Ptest = fq2(Q2test)      #interpolated fq2
        resq2 = Q2test - getQ('Q2', Ptest)
        q2res_list.append([round(Ptest,5), resq2])
        print Q2test
        Q2test = Q2test + 0.05

    Q3test = 1295.0
    while Q3test <= 1300.:
        Ptest = fq3(Q3test)      #interpolated fq3
        resq3 = Q3test - getQ('Q3', Ptest)
        q3res_list.append([round(Ptest,5), resq3])
        print Q3test
        Q3test = Q3test + 0.05


    Dtest = 2995
    while Dtest <= 3000.:
        Ptest = fdipole(Dtest)      #interpolated fdipole
        resD = Dtest - getQ('D', Ptest)
        Dres_list.append([round(Ptest,5), resD])
        print Dtest
        Dtest = Dtest + 0.05

    HBtest = 1545                 #NMR starting field [T]
    while HBtest <= 1550:          #loop over NMR field setting [T]
        Ptest = fhb(HBtest)      #interpolated fnmr
        resHB = HBtest - getQ('HB', Ptest)
        HBres_list.append([round(Ptest,5), resHB])
        print HBtest
        HBtest = HBtest + 0.05
        
    


    with open("shms_q1Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q1res_list)


    with open("shms_q2Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q2res_list)


    with open("shms_q3Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q3res_list)


    with open("shms_DRes_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(Dres_list)


    with open("shms_HBRes_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(HBres_list)


'''














if __name__=="__main__":
    main()
