#!/usr/bin/env python

#Script to get relevant report file quantities and store them in a data frame
import sys
import subprocess as sp
import pandas as pd    #used for data frame
import numpy as np
import re

#User Command Line Input
exp = sys.argv[1]   #user cmd-line input 'hms', 'shms', or 'coin' 
                    #Usage: python3 jcacheGet.py hms

#run_list = "heep_%s_runlist.dat" %(exp) 
run_list = "boiling_runs.txt"

f = open(run_list, 'r')

for run in (f):
    if (run[0]!='#'):
        #specify raw data file
        mss="/mss/hallc/spring17/raw/%s_all_0%s.dat" % (exp, run.strip())
        jcacheCMD="jcache get %s -e cyero002@fiu.edu -x" %(mss)
        
        #execute the command from shell
        sp.call(jcacheCMD, shell=True)
