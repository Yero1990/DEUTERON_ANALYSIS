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
    cmd1 = ("./../../FIELD/field03 %s >> " + hms_file) %(hmsP)   
    cmd2 = ("./../../holly/field17/getHMS %s >> " + hms_file) %(hmsP)
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

    #plt.plot(data['p'], data['q2'])
    #plt.show()
    
    #Interpolate data  Momentum (Current)
    fq1 = interp1d(data['q1'], data['p'], kind='linear')
    fq2 = interp1d(data['q2'], data['p'], kind='linear')
    fq3 = interp1d(data['q3'], data['p'], kind='linear')
    fdipole = interp1d(data['dipole'], data['p'], kind='linear')
    fnmr = interp1d(data['nmr'], data['p'], kind='linear')
    

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


















if __name__=="__main__":
    main()
