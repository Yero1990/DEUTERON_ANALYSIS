#!/usr/bin/env python


#User-defined functions useful for LiveTime Calculations
#Author: Carlos Yero

import sys
import os.path
import subprocess as sp
import re
import csv
import math 
import numpy as np
import matplotlib.pyplot as plt
import datetime

#record the current time
now = datetime.datetime.now()


#Replace a set of multiple sub strings with a new string in main string.

def replaceMultiple(mainString, toBeReplaces, newString):
    # Iterate over the strings to be replaced
    for elem in toBeReplaces :
        # Check if string is in the main string
        if elem in mainString :
            # Replace the string
            mainString = mainString.replace(elem, newString)
    
    return  (mainString)


#dat_list.append(['Run', 'PS1_factor', 'PS4_factor', 'PS6_factor', 'PS1_CLT', 'PS4_CLT', 'PS6_CLT', 'PS1_TLT', 'PS4_TLT', 'PS6_TLT',  'pT1_rate', 'hT1_rate', 'edtm_rate'])
#dat_list.append(['Run', 'PS1_factor', 'PS1_CLT', 'PS1_TLT', 'hT1_rate', 'edtm_rate'])

def singles_LT(runlist = [], datlist = [], spec=""):
     for i in runlist:

        reportFile = "../../../REPORT_OUTPUT/%s/SCALERS/replay_hms_scalers_%d_-1.report"% (spec,i)
        #print (reportFile)
        #Open report file
        f = open(reportFile)

        #Read each line in the report file
        for line in f:
            #split each line using ':' delimiter
            data = re.split('=|:|\[',line)
            #specify which variables to read data[0]: contains the name data[1] contains the value
            if (("Run #" in data[0])):
                run=data[1].strip()
                #print (run)
            if (("Ps1_factor" in data[0])):
                ps1_fact=data[1].strip()
                #print (ps1_fact)
            if (("Pre-Scaled Ps1 %s Computer Live Time"% (spec) in data[0])):
                ps1_CLT=(data[1].split())[0]
                #print(ps1_CLT)
            if (("Pre-Scaled Ps1 Total Live Time" in data[0])):                
                ps1_TLT=(data[1].split())[0]
                #print(ps1_TLT) 
            if (("%s 3/4 Trigger Rate"% (spec) in data[0])):                
                h34_rate=(data[1].split())[0]
                #print('hms3/4 rate = ',hms_34_rate)    
            if (("EDTM Trigger Rate" in data[0])):                
                edtm_rate=(data[1].split())[0]

        datlist.append([int(run), int(ps1_fact), float(ps1_CLT), float(ps1_TLT), float(h34_rate), float(edtm_rate)]) 


        #write livetimes into a csv file
        output_file = "%s_livetime_"+ now.strftime("%Y-%m-%d")+ ".csv"%(spec)
        with open(output_file, "w") as f:  
             wr = csv.writer(f)                                                                                                           
             wr.writerows(datlist)              


def coin_LT(runlist = [], datlist = []):
     for i in runlist:

        reportFile = "../../../REPORT_OUTPUT/COIN/SCALERS/replay_coin_scalers_%d_-1.report"% (i)
        print (reportFile)
        #Open report file
        f = open(reportFile)

        #Read each line in the report file
        for line in f:
            #split each line using ':' delimiter
            data = re.split('=|:|\[',line)
            #specify which variables to read data[0]: contains the name data[1] contains the value
            if (("Run number" in data[0])):
                run=data[1].strip()
                #print (run)
            if (("Ps1_factor" in data[0])):
                ps1_fact=data[1].strip()
                #print (ps1_fact)
            if (("Ps4_factor" in data[0])):
                ps4_fact=data[1].strip()
                #print (ps4_fact)
            if (("Ps6_factor" in data[0])):
                ps6_fact=data[1].strip()
                #print (ps6_fact)
            if (("ROC2 Pre-Scaled Ps1 ROC2 Computer Live Time" in data[0])):
                ps1_CLT=(data[1].split())[0]
                #print(ps1_CLT)
            if (("ROC2 Pre-Scaled Ps4 ROC2 Computer Live Time" in data[0])):
                ps4_CLT=(data[1].split())[0]
                #print(ps4_CLT)        
            if (("ROC2 Pre-Scaled Ps6 ROC2 Computer Live Time" in data[0])):
                ps6_CLT=(data[1].split())[0]
                #print(ps6_CLT)
            if (("ROC2 Pre-Scaled Ps1 Total Live Time" in data[0])):                
                ps1_TLT=(data[1].split())[0]
                #print(ps1_TLT) 
            if (("ROC2 Pre-Scaled Ps4 Total Live Time" in data[0])):                
                ps4_TLT=(data[1].split())[0]
                #print(ps4_TLT) 
            if (("ROC2 Pre-Scaled Ps6 Total Live Time" in data[0])):                
                ps6_TLT=(data[1].split())[0]
                #print(ps6_TLT)
            if (("SHMS_pTRIG1" in data[0])):                
                 if('0.0' not in data[2]):
                      data[2] = replaceMultiple(data[2],['kHz',']'],"").strip()
                      shms_34_rate=data[2]
                      #print('shms3/4 rate = ',shms_34_rate)     
            if (("SHMS_pTRIG4" in data[0])):                
                 if('0.0' not in data[2]):
                      data[2] = replaceMultiple(data[2],['kHz',']'],"").strip()
                      hms_34_rate=data[2]
                      #print('shms3/4 rate = ',shms_34_rate) 
            if (("SHMS_pTRIG6" in data[0])):                
                 if('0.0' not in data[2]):
                      data[2] = replaceMultiple(data[2],['kHz',']'],"").strip()
                      coin_rate=data[2]
                      #print('shms3/4 rate = ',shms_34_rate) 
            if (("HMS EDTM Trigger Rate" in data[0])):                
                edtm_rate=(data[1].split())[0]
                #print('edtm rate = ',edtm_rate)

        datlist.append([int(run), int(ps1_fact), int(ps4_fact), int(ps6_fact), float(ps1_CLT), float(ps4_CLT), float(ps6_CLT), 
                        float(ps1_TLT), float(ps4_TLT), float(ps6_TLT), float(shms_34_rate), float(hms_34_rate), float(coin_rate), float(edtm_rate)]) 


        #write livetimes into a csv file
        output_file = "coin_livetime_"+ now.strftime("%Y-%m-%d")+ ".csv"
        with open(output_file, "w") as f:  
             wr = csv.writer(f)                                                                                                           
             wr.writerows(datlist) 

