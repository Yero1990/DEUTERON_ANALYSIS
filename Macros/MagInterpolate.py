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
def GetP(spec, Mag, I):
  
    if(spec is 'hms'):
        #Read .csv file containing magnet currents data
        hdata = np.genfromtxt('/u/group/E12-10-003/cyero/hallc_replay/UTIL_COMM_ONEPASS/Macros/hmsMagn_interpol/hms_magnet_data.csv', delimiter=',', names=True)
    
        #Interpolate data  Momentum (Current)
        fq1 = interp1d(hdata['q1'], hdata['p'], kind='linear')
        fq2 = interp1d(hdata['q2'], hdata['p'], kind='linear')
        fq3 = interp1d(hdata['q3'], hdata['p'], kind='linear')
        fdipole = interp1d(hdata['dipole'], hdata['p'], kind='linear')
        fnmr = interp1d(hdata['nmr'], hdata['p'], kind='linear')

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

    if(spec is 'shms'):

        #Read .csv file containing magnet currents data
        pdata = np.genfromtxt('/u/group/E12-10-003/cyero/hallc_replay/UTIL_COMM_ONEPASS/Macros/shmsMagn_interpol/shms_magnet_data.csv', delimiter=',', names=True)

        #Interpolate data  Momentum (Current)
        fhb = interp1d(pdata['hb'], pdata['p'], kind='linear')
        fq1 = interp1d(pdata['q1'], pdata['p'], kind='linear')
        fq2 = interp1d(pdata['q2'], pdata['p'], kind='linear')
        fq3 = interp1d(pdata['q3'], pdata['p'], kind='linear')
        fdipole = interp1d(pdata['dipole'], pdata['p'], kind='linear')

        #magnes maximum allowable current (approx.)
        hb_max = 3843.
        q1_max = 2270.
        q2_max = 3813.
        q3_max = 2509.
        D_max = 3459.
   
        if(Mag is 'HB'):
            return (fhb(I))
        if(Mag is 'Q1'):
            return (fq1(I))
        if(Mag is 'Q2'):
            return (fq2(I))
        if(Mag is 'Q3'):
            return (fq3(I))
        if(Mag is 'D'):
            return (fdipole(I))
