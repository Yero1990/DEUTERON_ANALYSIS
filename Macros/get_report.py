#!/usr/bin/env python

#Script to get relevant report file quantities and store them in a data frame
import sys
import pandas as pd    #used for data frame
import numpy as np
import re

#create a row list to store values: list[Run#, BCM4a_Charge, ...]
cols = ['Run', 'BCM4a Current']
lst=[]
lst2=[]

#Loop over hms delta scan runs
for i in range(1149, 1172):

    #ignore some runs
    if (i == 1155 or i == 1156 or i == 1158): continue

    reportFile = "../hallc_replay/REPORT_OUTPUT/HMS/PRODUCTION/replay_hms_delta_scan_%s_%s.report"% (i, -1)
    
    #Open report file
    f = open(reportFile)
    #print ("Opening file: " + reportFile)
    #Read each line in the report file
    for line in f:
        #split each line using ':' delimiter
        data = line.split(':')
        #specify which variables to read data[0]: contains the name data[1] contains the value
        if (("Run #" in data[0])):
            run = data[1]
        if (("BCM4a Current" in data[0])):
            current = re.sub('[uA]', '', data[1])   #substitute regular expression in brackets
            current.strip()    #remove leading/trailing spaces
            
    lst.append([int(run.strip()),float(current.strip())])
 
print (lst)

df = pd.DataFrame(lst,columns=cols)
print (df)
