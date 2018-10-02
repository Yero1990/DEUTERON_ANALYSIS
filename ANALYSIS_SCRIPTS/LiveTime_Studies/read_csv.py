#!/usr/bin/env python
from LTfunctions import *
import sys
import os.path
import subprocess as sp
import re
import pandas as pd
import csv
import math 
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate
from scipy.interpolate import interp1d



df = pd.read_csv('kaon_LT.csv', delim_whitespace=True, index_col=False)  
#useful_columns = ['Run']
#print(df[useful_columns])

print(df['comment'])
