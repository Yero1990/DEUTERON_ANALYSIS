#!/usr/bin/env python
import sys
import os
import subprocess as sp
import re
import csv
#import pandas as pd

#import ROOT
#from ROOT import gROOT

startP = 2.0
endP = 11.0

#create an empty file to store data
#hms_file = "hms_magnet.data"
#os.system("touch " + hms_file)
 

#write the output to the file

#open the file
#f = open(hms_file)

lst = []

lst.append(['HB', 'Q1', 'Q2', 'Q3', 'D'])


#loop over hms central  momenta
while (startP <= endP):

    print (startP)

    shms_file = "shms_magnet_%f.data" %startP
    os.system("touch " + shms_file) 
    
    cmd = "./../../holly/field17/getSHMS %f >> ./shms_magnet_%f.data" %(startP, startP)     #get dipole current/nmr


    sp.call(cmd, shell=True) 
    f = open(shms_file) # open file

    cnt = 0 #reset line counter

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

                lst.append([round(startP, 5), float(hb_val), float(q1_val), float(q2_val), float(q3_val), float(d_val)])

        cnt = cnt + 1 #increment line count

    

    os.system("rm shms_magnet_%f.data" %(startP)) #remove temporary data file


    startP = startP + 0.001                      #increment momentum step
    

with open("shms_magnet_data.csv", "w") as f:
    wr = csv.writer(f)
    wr.writerows(lst)
