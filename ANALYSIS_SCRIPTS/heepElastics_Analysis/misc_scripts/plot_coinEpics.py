#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv
import sys
import pandas as pd    #used for data frame
import numpy as np
import re
from scipy import interpolate
from scipy.interpolate import interp1d
from MagInterpolate import GetP

#Script to read .csv format data into dataframes and plot
#Magnet Current and Momentum vs. Run Number

#-------------------------------------------------------------

#read csv file into data frame
df1 = pd.read_csv('hms_EPICS.csv', parse_dates=False)
df2 = pd.read_csv('shms_EPICS.csv', parse_dates=False)
df3 = pd.read_csv('coin_EPICS.csv', parse_dates=False)


#Plot Mag. CUrrents vs. Run Number


fig = plt.figure()
ax = fig.add_subplot(211)        #add_subplot(nrows, ncols, index)

#Set Limits on X-axis
plt.xlim(1757,1763)


#plot Magnet Current vs. Run Number
df1.plot(kind='scatter', x='Run', y='Q1_set', edgecolor='black', c='none', marker='o', label='Q1-set', ax=ax)
df1.plot(kind='scatter', x='Run', y='Q2_set', edgecolor='black', c='none', marker='^', label='Q2-set', ax=ax)
df1.plot(kind='scatter', x='Run', y='Q3_set', edgecolor='black', c='none', marker='v', label='Q3-set', ax=ax)

plt.xlabel('Run')
plt.ylabel('Magnet Current [A]')
plt.title('HMS Magnet Set Currents')

#create a twin y-axis with different scale on same plot
axt = ax.twinx()

df1.plot(kind='scatter', x='Run', y='NMR_set', edgecolor='red',  c='none',marker='s', label='NMR-set', ax=axt)
axt.set_ylabel('HMS Set NMR [T]')

plt.legend(loc='lower right')
plt.grid()
#plt.show()


#Determine Momentum from Set Currents

#Create lists to store set/true momentum values corresponding to magnet currents
Q1p_set_list = []
Q2p_set_list = []
Q3p_set_list = []
NMRp_set_list = []

#Loop over run list
for index, run in enumerate(df1['Run'].tolist()):

    #Call GetP() to get SET momentum from Mag Current
    Q1_P = GetP('hms', 'Q1',   df1['Q1_set'][index])
    Q2_P = GetP('hms', 'Q2',   df1['Q2_set'][index])
    Q3_P = GetP('hms', 'Q3',   df1['Q3_set'][index])
    NMR_P = GetP('hms', 'NMR', df1['NMR_set'][index])

    #Append SET momentum values to list
    Q1p_set_list.append(Q1_P)
    Q2p_set_list.append(Q2_P)
    Q3p_set_list.append(Q3_P)
    NMRp_set_list.append(NMR_P)

#Add Momentum Lists to existing dataframes
#df1['Pq1_set'] = pd.Series(Q1p_set_list, index=df1.index)
#df1['Pq2_set'] = pd.Series(Q2p_set_list, index=df1.index)
#df1['Pq3_set'] = pd.Series(Q3p_set_list, index=df1.index)
df1['Pnmr_set'] = pd.Series(NMRp_set_list, index=df1.index) 

df1 = df1.round(5)

ax = fig.add_subplot(212)        #add_subplot(nrows, ncols, index)
#Set Limits on X-axis
plt.xlim(1757,1763)
#Plot Momentum vs. Run Number
plt.scatter(df1['Run'], Q1p_set_list, color='black', facecolors='none',  marker='o', label=r'$P_{Q1-set}$' )
plt.scatter(df1['Run'], Q2p_set_list, color='blue', facecolors='none',  marker='^', label=r'$P_{Q2-set}$')
plt.scatter(df1['Run'], Q3p_set_list, color='red', facecolors='none', marker='s', label=r'$P_{Q3-set}$')
plt.scatter(df1['Run'], NMRp_set_list, color='magenta', facecolors='none', marker='v', label=r'$P_{NMR-set}$' )

plt.xlabel('Run Number')
plt.ylabel('Central Momentum [GeV/c]')
plt.title('HMS Magnet Set/True Central Momentum')

plt.legend(loc='best')
plt.grid()
plt.show()
print(df1)

df1.to_csv('hms_GoodEPICS.csv', sep='\t', index=False)




