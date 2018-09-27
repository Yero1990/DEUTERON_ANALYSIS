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
df1 = pd.read_csv('HMS_MagnI_set.csv', parse_dates=False)
df2 = pd.read_csv('HMS_MagnI_true.csv', parse_dates=False)

#PLOT Magnet Currents vs. Run Number, as read from EPICS tree

fig = plt.figure()
ax = fig.add_subplot(211)

#plot Magnet Current vs. Run Number
df1.plot(kind='scatter', x='Run', y='Q1', edgecolor='black', c='none', marker='o', label='Q1-set', ax=ax)
df1.plot(kind='scatter', x='Run', y='Q2', edgecolor='black', c='none',marker='^', label='Q2-set', ax=ax)
df1.plot(kind='scatter', x='Run', y='Q3', edgecolor='black', c='none',marker='v', label='Q3-set', ax=ax)
df1.plot(kind='scatter', x='Run', y='D', edgecolor='black',  c='none',marker='s', label='D-set', ax=ax)

df2.plot(kind='scatter', x='Run', y='Q1', edgecolor='red', c='none',marker='o', label='Q1-true', ax=ax)
df2.plot(kind='scatter', x='Run', y='Q2', edgecolor='red', c='none',marker='^', label='Q2-true', ax=ax)
df2.plot(kind='scatter', x='Run', y='Q3', edgecolor='red', c='none',marker='v', label='Q3-true', ax=ax)
plt.grid()
plt.xlabel('')
plt.ylabel('Magnet Current [A]')
plt.title('HMS Magnet Set/True Currents')

#plot NMR vs. Run Number
ax = fig.add_subplot(212)
df1.plot(kind='scatter', x='Run', y='NMR', edgecolor='black', c='none',marker='>', label='NMR-set', ax=ax)
df2.plot(kind='scatter', x='Run', y='NMR', edgecolor='red', c='none',marker='>', label='NMR-true', ax=ax)

plt.title('HMS Dipole Set/True NMR Field')
plt.xlabel('Run Number')
plt.ylabel('HMS NMR Field [T]')

plt.legend(loc='best')
plt.grid()

plt.show()


#Create lists to store set/true momentum values corresponding to magnet currents
Q1p_set_list = []
Q1p_true_list = []
Q2p_set_list = []
Q2p_true_list = []
Q3p_set_list = []
Q3p_true_list = []
Dp_set_list = []
NMRp_set_list = []
NMRp_true_list = []



#Loop over run list
for index, run in enumerate(df1['Run'].tolist()):

    #Call GetP() to get SET momentum from Mag Current
    Q1_P = GetP('Q1',   df1['Q1'][index])
    Q2_P = GetP('Q2',   df1['Q2'][index])
    Q3_P = GetP('Q3',   df1['Q3'][index])
    D_P = GetP( 'D',    df1['D'][index])
    NMR_P = GetP('NMR', df1['NMR'][index])

    #Append SET momentum values to list
    Q1p_set_list.append(Q1_P)
    Q2p_set_list.append(Q2_P)
    Q3p_set_list.append(Q3_P)
    Dp_set_list.append(D_P)
    NMRp_set_list.append(NMR_P)

    
    #Call GetP() to get TRUE momentum from Mag Current
    Q1_P = GetP('Q1',   df2['Q1'][index])
    Q2_P = GetP('Q2',   df2['Q2'][index])
    Q3_P = GetP('Q3',   df2['Q3'][index])
    NMR_P = GetP('NMR', df2['NMR'][index])
    
    #Append TRUE momentum values to list
    Q1p_true_list.append(Q1_P)
    Q2p_true_list.append(Q2_P)
    Q3p_true_list.append(Q3_P)
    NMRp_true_list.append(NMR_P)

#Add Momentum Lists to existing dataframes
df1['Pq1_set'] = pd.Series(Q1p_set_list, index=df1.index)
df1['Pq2_set'] = pd.Series(Q2p_set_list, index=df1.index)
df1['Pq3_set'] = pd.Series(Q3p_set_list, index=df1.index)
df1['Pnmr_set'] = pd.Series(NMRp_set_list, index=df1.index)

df2['Pq1_true'] = pd.Series(Q1p_true_list, index=df2.index)
df2['Pq2_true'] = pd.Series(Q2p_true_list, index=df2.index)
df2['Pq3_true'] = pd.Series(Q3p_true_list, index=df2.index)
df2['Pnmr_true'] = pd.Series(NMRp_true_list, index=df2.index)

df1 = df1.round(5)
df2 = df2.round(5)

df2 = df2.drop(columns=['D'])

df1.to_csv('HMS_SetPValues.csv', sep='\t')
df2.to_csv('HMS_TruePValues.csv', sep='\t')                                     



#Plot Momentum vs. Run Number
plt.scatter(df1['Run'], Q1p_set_list, color='black', facecolors='none',  marker='o', label=r'$P_{Q1-set}$' )
plt.scatter(df1['Run'], Q1p_true_list, color='red', facecolors='none',  marker='o', label=r'$P_{Q1-true}$' )

plt.scatter(df1['Run'], Q2p_set_list, color='black', facecolors='none',  marker='^', label=r'$P_{Q2-set}$')
plt.scatter(df1['Run'], Q2p_true_list, color='red', facecolors='none',  marker='^', label=r'$P_{Q2-true}$')

plt.scatter(df1['Run'], Q3p_set_list, color='black', facecolors='none', marker='s', label=r'$P_{Q3-set}$')
plt.scatter(df1['Run'], Q3p_true_list, color='red', facecolors='none',  marker='s', label=r'$P_{Q3-true}$')

plt.scatter(df1['Run'], NMRp_set_list, color='black', facecolors='none', marker='v', label=r'$P_{NMR-set}$' )
plt.scatter(df1['Run'], NMRp_true_list, color='red', facecolors='none',  marker='v', label=r'$P_{NMR-true}$' )

plt.xlabel('Run Number')
plt.ylabel('Central Momentum [GeV/c]')
plt.title('HMS Magnet Set/True Central Momentum')

plt.legend(loc='best')
plt.grid()

plt.show()




