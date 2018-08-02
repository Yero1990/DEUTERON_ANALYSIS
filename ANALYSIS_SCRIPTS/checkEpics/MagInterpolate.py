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

#Function to get the HMS momentum from the given input current
#Usage: GetP('Q1', 1243)  ---> hmsI: Magnet set or readback current from EPICS
def GetP(Mag, I):
  
    #Read .csv file containing magnet currents data
    data = np.genfromtxt('hms_magnet_data.csv', delimiter=',', names=True)

    
    #Interpolate data  Momentum (Current)
    fq1 = interp1d(data['q1'], data['p'], kind='linear')
    fq2 = interp1d(data['q2'], data['p'], kind='linear')
    fq3 = interp1d(data['q3'], data['p'], kind='linear')
    fdipole = interp1d(data['dipole'], data['p'], kind='linear')
    fnmr = interp1d(data['nmr'], data['p'], kind='linear')


    #magnes maximum allowable current (approx.)
    q1_max = 985.
    q2_max = 836.
    q3_max = 374.
    D_max = 3000.
    NMR_max = 2.08
   
    if(Mag is 'Q1'):
        return (fq1(I))
    if(Mag is 'Q2'):
        return (fq2(I))
    if(Mag is 'Q3'):
        return (fq3(I))
    if(Mag is 'D'):
        return (fdipole(I))
    if(Mag is 'NMR'):
        return (fnmr(I))  #in this context, I is the probe field in Tesla
