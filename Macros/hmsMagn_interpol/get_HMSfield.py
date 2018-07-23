#!/usr/bin/env python
import sys
import os
import subprocess as sp
import re
import csv
#import pandas as pd

#import ROOT
#from ROOT import gROOT

startP = 0.01
endP = 7.44

#create an empty file to store data
#hms_file = "hms_magnet.data"
#os.system("touch " + hms_file)
 

#write the output to the file

#open the file
#f = open(hms_file)

q1 = []
q2 = []
q3 = []
dp = []
nmr = []

lst = []

lst.append(['p','q1','q2','q3','dipole','nmr'])


#loop over hms central  momenta
while (startP <= endP):


    hms_file = "hms_magnet_%f.data" %startP
    os.system("touch " + hms_file) 
    
    
    cmd1 = "./../executables/field03 %f >> ./hms_magnet_%f.data" %(startP, startP)            #get quads current
    cmd2 = "./../executables/getHMS %f >> ./hms_magnet_%f.data" %(startP, startP)     #get dipole current/nmr
    sp.call(cmd1, shell=True) 
    sp.call(cmd2, shell=True)   

    f = open(hms_file) # open file

    cnt = 0 #reset line counter

#Read each line
    for line in f:
        prefix = line.split(". MOL")[0]
        #print prefix
        if (("Iset:" in prefix)):
            #print cnt
            quads = prefix.split()
            #print quads
            if (cnt==0): 
                q1_val = quads[1].strip()
                q1_unit = quads[2].strip()
            if (cnt==1): 
                q2_val = quads[1].strip()
                q2_unit = quads[2].strip()
            if (cnt==2):
                q3_val = quads[1].strip()
                q3_unit = quads[2].strip()
            if (cnt==3):
                #print cnt
                #print quads
                dp_val = (quads[3:6])[1]
                dp_unit = quads[5].strip('.')
            
            cnt = cnt + 1 #increment line count

        if (("NMR B:" in prefix)):
            nmr_val = prefix.split()
            nmr_unit = nmr_val[4]
            
    lst.append([round(startP,5),float(q1_val),float(q2_val),float(q3_val), float(dp_val), float(nmr_val[3])])     # make a list of lists (each of the lists will be one momentum setting, and the corresponding magnet settings)
    os.system("rm hms_magnet_%f.data" %(startP)) #remove temporary data file
    print (startP)
    startP = startP + 0.001                     #increment momentum step
    


with open("hms_magnet_datav2.csv", "w") as f:
    wr = csv.writer(f)
    wr.writerows(lst)
