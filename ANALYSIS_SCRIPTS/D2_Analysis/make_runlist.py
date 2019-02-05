#!/usr/bin/env python                                                          
import matplotlib.pyplot as plt                                                
import csv                                                                     
import sys                                                                     
import pandas as pd    #used for data frame                                    
import numpy as np                                                             
import re                                                                      
from scipy import interpolate                                                  
from scipy.interpolate import interp1d                                         
import LT.box as B                                                             


#read kin file
f = B.get_file('coin_kin.dat')


#create outfiles

#---before run 3288 
foutd0 = open("pre_Aldummy.dat", "w")  
fout0 = open("pre_Optics.dat", "w")  
fout1 = open("pre_LH2_singles.dat", "w") 
fout2 = open("pre_LH2_coin.dat", "w")
fout3 = open("pre_LD2_singles.dat", "w")  
fout4 = open("pre_LD2_coin_pm80.dat", "w") 
fout5 = open("pre_LD2_coin_pm580.dat", "w")
fout6 = open("pre_LD2_coin_pm750.dat", "w")

#----including and after run 3288 (SHMS Q3 correction was removed)
foutd1 = open("post_Aldummy.dat", "w")  
fout7 = open("post_Optics.dat", "w")    
fout8 = open("post_LH2_singles.dat", "w")     
fout9 = open("post_LH2_coin.dat", "w")           
fout10 = open("post_LD2_singles.dat", "w")                 
fout11 = open("post_LD2_coin_pm80.dat", "w")                                
fout12 = open("post_LD2_coin_pm580.dat", "w")                          
fout13 = open("post_LD2_coin_pm750.dat", "w")

#get headers
run = B.get_data(f, 'Run')  
hmsP = B.get_data(f, 'hNMR_P')
shmsP = B.get_data(f, 'sD_P')
hms_Angle = B.get_data(f, 'hms_Angle')
shms_Angle = B.get_data(f, 'shms_Angle')
target = B.get_data(f, 'Target')
Ps1 = B.get_data(f, 'Ps1')     #SHMS 3/4
Ps2 = B.get_data(f, 'Ps2')     #SHMS EL-REAL
Ps3 = B.get_data(f, 'Ps3')     #SHMS EL-CLEAN
Ps4 = B.get_data(f, 'Ps4')     #HMS 3/4
Ps6 = B.get_data(f, 'Ps6')    #coincidence


for index, irun in enumerate(run):
    if target[index]=='Al_Dummy_10cm' and irun<3288:
        foutd0.write('%s\n' % int(irun))
    if target[index]=='Optics-1' and irun<3288:
        fout0.write('%s\n' % int(irun))
    if target[index]=='LH2' and Ps6[index]==-1 and irun<3288:
        fout1.write('%s\n' % int(irun))
    if target[index]=='LH2' and Ps6[index]!=-1 and irun<3288:
        fout2.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]==-1 and irun<3288:
        fout3.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]<42. and irun<3288:
        fout4.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]>50 and hms_Angle[index]<56 and irun<3288:
        fout5.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]>57 and hms_Angle[index]<60 and irun<3288:
        fout6.write('%s\n' % int(irun))

    if target[index]=='Al_Dummy_10cm' and irun>=3288:
        foutd1.write('%s\n' % int(irun))
    if target[index]=='Optics-1' and irun>=3288:
        fout7.write('%s\n' % int(irun))
    if target[index]=='LH2' and Ps6[index]==-1 and irun>=3288:
        fout8.write('%s\n' % int(irun))
    if target[index]=='LH2' and Ps6[index]!=-1 and irun>=3288:
        fout9.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]==-1 and irun>=3288:
        fout10.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]<42. and irun>=3288:
        fout11.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]>50 and hms_Angle[index]<56 and irun>=3288:
        fout12.write('%s\n' % int(irun))
    if target[index]=='LD2' and Ps6[index]!=-1 and hms_Angle[index]>57 and hms_Angle[index]<60 and irun>=3288:
        fout13.write('%s\n' % int(irun))
