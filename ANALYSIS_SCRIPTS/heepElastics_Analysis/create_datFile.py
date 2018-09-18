#!/usr/bin/env python

import sys
import subprocess as sp
import pandas as pd    #used for data frame
import numpy as np
import re

#User Command Line Input
exp = sys.argv[1]   #user cmd-line input 'hms', 'shms', or 'coin' 
                    #Usage: python3 create_datFile.py hms

run_list = "heep_%s_runlist.dat" %(exp) 

new_run_list = "heep_%s_runlist_hcswif.dat" %(exp) 

f = open(run_list, 'r')

#Open file to write 
fout = open(new_run_list, 'w')

for run in (f):
    if (run[0]!='#'):
        #specify raw data file
        mss="/mss/hallc/spring17/raw/%s_all_0%s.dat\n" % (exp, run.strip())
        fout.write(mss)
	
fout.close()
