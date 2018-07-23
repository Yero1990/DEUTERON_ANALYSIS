#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv
import sys
import pandas as pd    #used for data frame
import numpy as np
import re
from scipy import interpolate
from scipy.interpolate import interp1d


#Program Usage:  >> python3 getI.py Q1 Q2 Q3 D B 

#p = sys.argv[1]
#Q1 = sys.argv[1]
#Q2 = sys.argv[2]
#Q3 = sys.argv[3]
#D = sys.argv[4]
#B = sys.argv[5]


#Script to read .csv format data into dataframes and interpolate/plot

#-------------------------------------------------------------

#read csv file into data frame
df = pd.read_csv('hms_magnet_data_test.csv', parse_dates=False)

#plot any two columns in the data-frame
#df.plot(kind='scatter', x='q1', y='p', marker='.', color='red', linestyle='dashed', label='q1' ,s=2)
#df.plot(kind='scatter', x='q2', y='p', marker='*', color='blue', linestyle='dashed', label='q2' ,s=2)
#plt.plot(df['q1'], df['p'], label='Q1') 
#plt.plot(df['q2'], df['p'], label='Q2') 
#plt.plot(df['q3'], df['p'], label='Q3') 
#plt.plot(df['dipole'], df['p'], label='D')
#plt.plot(df['nmr'], df['p'], label='NMR') 

#plt.legend()
#plt.show()

#access a df column array
#print (df['p'])

#access specific element of a column 'p'
#print (df.at[20, 'p'])

#interpolate any two columns (p, q1, q2, q3 . . . etc.) in the csv file 
#Current (Momentum)
#fq1 = interp1d(df['p'], df['q1'], kind='linear')  
#fq2 = interp1d(df['p'], df['q2'], kind='quadratic')
#fq3 = interp1d(df['p'], df['q3'], kind='linear')
#fdipole = interp1d(df['p'], df['dipole'], kind='quadratic')
#fnmr = interp1d(df['p'], df['nmr'], kind='linear')

#print (fq1)

#print ('HMS Q1  = ' , np.round(fq1(p), 5),     ' [A]')
#print ('HMS Q2  = ' , np.round(fq2(p), 5),     ' [A]')
#print ('HMS Q3  = ' , np.round(fq3(p), 5),     ' [A]')
#print ('HMS D   = ' , np.round(fdipole(p), 5), '   [A]')
#print ('HMS NMR = ', np.round(fnmr(p), 5),     '   [T]')

#--------------------------------------------------

#Q1, Q2, Q3, D, NMR must be sorted

#Invert function to get Momentum (Current)
#fq1 = interp1d(df['q1'], df['p'], kind='linear')
#fq2 = interp1d(df['q2'], df['p'], kind='quadratic')
#fq3 = interp1d(df['q3'], df['p'], kind='linear')
#fdipole = interp1d(df['dipole'], df['p'], kind='quadratic')
#fnmr = interp1d(df['nmr'], df['p'], kind='linear')


#print ('HMS Q1: P  = ' , np.round(fq1(Q1), 5),     ' [GeV]')
#print ('HMS Q2: P  = ' , np.round(fq2(Q2), 5),     ' [GeV]')
#print ('HMS Q3: P  = ' , np.round(fq3(Q3), 5),     ' [GeV]')
#print ('HMS D:  P  = ' , np.round(fdipole(D), 5), '   [GeV]')
#print ('HMS NMR: P = ', np.round(fnmr(B), 5),     '   [GeV]')

#xq1 = np.linspace(10, 980, num=20, endpoint=True)
#xq2 = np.linspace(10, 830, num=20, endpoint=True)
#xq3 = np.linspace(10, 370, num=20, endpoint=True)
#xdi = np.linspace(10, 3000, num=50, endpoint=True)
#xnmr = np.linspace(0.03, 2.07, num=50, endpoint=True)


#plt.plot(xq1, fq1(xq1), '.', color='black', label='interpolation')
#plt.plot(xq2, fq2(xq2), '.', color='black', label='interpolation')
#plt.plot(xq3, fq3(xq3), '.', color='black', label='interpolation')
#plt.plot(xdi, fdipole(xdi), '.', color='black', label='interpolation')
#plt.plot(xnmr, fnmr(xnmr), '.', color='black', label='interpolation')
#plt.xlabel('HMS Dipole NMR [T]')
#plt.ylabel('HMS Central Momentum [GeV]')
#plt.title('Interpolation of HMS Dipole NMR')
#plt.legend()

#plt.show()


#-------------------------------------------------------------



#------------------------------------------------------------
#create numpy arrays to store data
#p_arr = np.array([])

#read csv file row-by-row 
#with open('hms_magnet_data.csv', 'r') as csvfile:
#    csvreader = csv.reader(csvfile)

    #igonore the first row which contins columns headers
#    next(csvreader)

    #loop over each row of the csv file
#    for row in csvreader:
#        print (row[0])
#------------------------------------------------------------

