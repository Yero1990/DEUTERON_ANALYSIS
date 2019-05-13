#!/usr/bin/env python
import LT.box as B
import sys
import os.path
import subprocess as sp
import re
import math 
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate
from scipy.interpolate import interp1d

#Buffer Level 1 (No Buffering)
def dt_nonextended(x, a):      #x [kHz],  a [u.sec]
    x = x*1e3   #covert to Hz
    a = a*1e-6  #convert to s
    dt = 100.*(x*a/(1. + x*a))
    lt = (100. - dt)
    return lt

#In Coin Mode, BUSY MIN = 220 us,  BUSY_MAX = 332 us 
x = np.linspace(0, 1.5, 100)


cpuLT = [98.0857, 98.8501, 93.67, 85.3053]

cpuLT_new = [98.2623, 99.1912, 93.8622, 84.9579]

coin_rate = [0.107, 0.050, 0.387, 0.952]

coin_rate_new = [0.1109, 0.0512, 0.38722, 1.015]

B.pl.plot(x, dt_nonextended(x,220.), linestyle='--', color='black', label='BUSY_MIN: 220 us')
B.pl.plot(x, dt_nonextended(x,332.), linestyle='--', color='blue', label='BUSY_MAX: 332 us') 
B.plot_exp(coin_rate, cpuLT, marker='s', color='red', label='data')
B.plot_exp(coin_rate_new, cpuLT_new, marker='^', color='red', markerfacecolor='none', label='data: edtm corrected')  

B.pl.legend()
B.pl.xlabel('Trigger Rate [kHz]')
B.pl.ylabel('Live Time')

B.pl.show()
