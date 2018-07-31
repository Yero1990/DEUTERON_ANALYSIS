#!/usr/bin/env python      
import sys                                                             
import os.path                                                     
import subprocess as sp                              
import re                                                             
import pandas as pd                                                  
import csv                                                      
import numpy as np                                       
import matplotlib.pyplot as plt                      

#list of runs to ignore in Buffer Level run list [2173 - 2228] --July 26, 2018
ignore_run = [2176, 2179,2181,2182,2183,2184,2185,2186,2196,2197,2198,2199,2200,2205,2210,2211,2212, 2217, 2218, 2223, 2224,
              2229, 2230, 2231, 2232, 2233, 2234, 2235, 2236, 2237, 2238, 2239, 2240, 2241, 2242, 2243, 2244, 2245, 2246, 2247, 2248, 2249,
              2250, 2251, 2260, 2261, 2262]

for run in range(2252,2266):

    if(run in ignore_run): 
        continue

    os.chdir('../hallc_replay/')

    cmd = "./hcana -q \"../hallc_replay/SCRIPTS/HMS/SCALERS/replay_hms_scalers.C(%d,-1)\""  %run
    os.system(cmd)
