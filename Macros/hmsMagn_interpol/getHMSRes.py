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


#------------------DEFINE FUNCTION TO Get Magnet CUrrents/NMR from a given Momentum--------------
#Usage: in main funciton, call:  getQ('mag', hmP)     #where mag = 'Q1', 'Q2', 'Q3', 'D', 'NMR', hmsP: momentum

def getQ(mag, hmsP):
    hms_file = "hms_tmp.data"

    #check if file exists (if it does, empty it . . .)
    if (os.path.exists(hms_file)):
        sp.call(("truncate -s 0 " + hms_file),shell=True)
    else:
    #create and append magnet 
        os.system("touch " + hms_file)

    #command to append field03 output currents to a dat file
    cmd1 = ("./../executables/field03 %s >> " + hms_file) %(hmsP)   
    cmd2 = ("./../executables/getHMS %s >> " + hms_file) %(hmsP)
    sp.call(cmd1, shell=True)
    sp.call(cmd2, shell=True)
    
    f = open(hms_file)    #open file
    cnt = 0               #reset line counter

    #read each line
    for line in f:
        prefix = line.split(". MOL")[0]
        if (("Iset:" in prefix)):
            quads = prefix.split()
            if (cnt==0):
                q1_val = quads[1].strip()
                #print (q1_val)
            if (cnt==1):
                q2_val = quads[1].strip()
                #print (q2_val)
            if (cnt==2):
                q3_val = quads[1].strip()
                #print (q3_val)
            if (cnt==3):
                dipole_val = (quads[3:6])[1].strip()
                #print (dipole_val)
             
            cnt = cnt + 1
        if (("NMR B:" in prefix)):
            nmr_val = ((prefix).split())[3]
            #print (nmr_val)
                
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
        return float(dipole_val)
    if (mag is 'NMR'):
        #print float(nmr_val)
        return float(nmr_val)

    #delete the file 
    os.system("rm hms_tmp.data")


def main():
    print ('Entering main() . . . ')

    #Read .csv file containing magnet currents data
    data = np.genfromtxt('hms_magnet_data.csv', delimiter=',', names=True)

    #Plot Momentum vs. Current from the .csv file
    plt.plot(data['q1'], data['p'], label='Q1', linewidth=2.0)
    plt.plot(data['q2'], data['p'], label='Q2', linewidth=2.0)
    plt.plot(data['q3'], data['p'], label='Q3', linewidth=2.0) 
    plt.plot(data['dipole'], data['p'], label='D', linewidth=2.0) 
      
    plt.xlabel('HMS Magnets Current [A]')
    plt.ylabel('HMS Momentum [GeV/c]')
    
    #Interpolate data  Momentum (Current)
    fq1 = interp1d(data['q1'], data['p'], kind='linear')
    fq2 = interp1d(data['q2'], data['p'], kind='linear')
    fq3 = interp1d(data['q3'], data['p'], kind='linear')
    fdipole = interp1d(data['dipole'], data['p'], kind='linear')
    fnmr = interp1d(data['nmr'], data['p'], kind='linear')
    
    
    #Set Min/Max Current Range for plotting interpolation range
    xq1_min = getQ('Q1', 0.01)
    xq1_max = getQ('Q1', 7.439)
    xq1 = np.linspace(xq1_min, xq1_max, 10)
    xq2_min = getQ('Q2', 0.01)                                         
    xq2_max = getQ('Q2', 7.439)                                           
    xq2 = np.linspace(xq2_min, xq2_max, 10)
    xq3_min = getQ('Q3', 0.01)                                       
    xq3_max = getQ('Q3', 7.439)                                       
    xq3 = np.linspace(xq3_min, xq3_max, 10)
    xd_min = getQ('D', 0.01)                                            
    xd_max = getQ('D', 7.439)                                            
    xd = np.linspace(xd_min, xd_max, 10)
    xnmr_min = getQ('NMR', 0.01)                                            
    xnmr_max = getQ('NMR', 7.439)                                            
    xnmr = np.linspace(xnmr_min, xnmr_max, 10)
    
    plt.scatter(xq1, fq1(xq1), color='black', marker='o', label='interpolation')
    plt.scatter(xq2, fq2(xq2), color='black', marker='o')
    plt.scatter(xq3, fq3(xq3), color='black', marker='o') 
    plt.scatter(xd, fdipole(xd), color='black', marker='o') 

    plt.legend(loc='best')                        
    plt.savefig('hms_mag_interpol.pdf')

    #Plot NMR 
    plt.figure()
    plt.plot(data['nmr'], data['p'], label='NMR', linewidth=2.0) 
    plt.scatter(xnmr, fnmr(xnmr), color='black', marker='o') 
      
    plt.xlabel('HMS NMR Field [T]')
    plt.ylabel('HMS Momentum [GeV/c]')
    
    plt.legend(loc='best')                        
    plt.savefig('hms_nmr_interpol.pdf')

'''   RESIDUAL CALCULATION 
    #Make lists to store residuals

    q1res_list = []
    q2res_list = []
    q3res_list = []
    Dres_list = []
    NMRres_list = []

    #magnes maximum allowable current (approx.)
    q1_max = 985.
    q2_max = 836.
    q3_max = 374.
    D_max = 3000.
    NMR_max = 2.08

    #Calculate Residuals (fq_interpolated - fq_data)
    Q1test = 250.0                 #initial quad current [A]
    while Q1test <= 255.:        #Loop over current
        Ptest = fq1(Q1test)      #interpolated fq1 (get momentum for each current)
        resq1 = Q1test - getQ('Q1', Ptest)  #determine residuals (diff. between current value and current from field03 (momentum))
        q1res_list.append([round(Ptest,5), resq1])
        print Q1test
        Q1test = Q1test + 0.05             #increment current by small amount
    
    Q2test = 830.0 
    while Q2test <= 836.:
        Ptest = fq2(Q2test)      #interpolated fq2
        resq2 = Q2test - getQ('Q2', Ptest)
        q2res_list.append([round(Ptest,5), resq2])
        print Q2test
        Q2test = Q2test + 0.05

    Q3test = 295.0
    while Q3test <= 300.:
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

    NMRtest = 2.05                 #NMR starting field [T]
    while NMRtest <= 2.06:          #loop over NMR field setting [T]
        Ptest = fnmr(NMRtest)      #interpolated fnmr
        resNMR = NMRtest - getQ('NMR', Ptest)
        NMRres_list.append([round(Ptest,5), resNMR])
        print NMRtest
        NMRtest = NMRtest + 0.00015
        
    


    with open("hms_q1Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q1res_list)


    with open("hms_q2Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q2res_list)


    with open("hms_q3Res_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(q3res_list)


    with open("hms_DRes_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(Dres_list)


    with open("hms_NMRRes_data.csv", "w") as f:
        wr = csv.writer(f)
        wr.writerows(NMRres_list)

'''
















if __name__=="__main__":
    main()
