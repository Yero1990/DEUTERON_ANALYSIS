import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
import sys


#Set proper paths to import ROOT
sys.path.append('../../../pyroot/')
sys.path.append('/apps/root/PRO/lib/')
sys.path.append('/apps/root/PRO/')

from ROOT import *
from ROOT import *

#from ROOT import TFile

simcW = TH1F('simcW', 'W', 100, 0.85, 1.05)

c1 = TCanvas('c1','',500,500)
c1.cd()
c1.SaveAs('empy.pdf')


#simc_file = TFile('../root_files/heep_simc_histos_3288.root')
#simc_file.GetObject('H_W', simcW)

#h1 = TH1F("h1", "", 100,-10,10)
#h1.Draw()

'''
x = [45.306,80.372,271.991,634.447]
my_xticks = ['45.306', '80.372', '271.991', '634.447']


#HMS Delta/SHMS Delta CUTS
f = B.get_file('yield_study_heep.dat')
Run = B.get_data(f, 'Run')
shms_rate = B.get_data(f, 'shms_rate')
dataY = B.get_data(f, 'dataY')    
dataY_err = B.get_data(f, 'dataY_err')     #these are absolute errors, sqrt(N)
simcY = B.get_data(f, 'simcY')
simcY_err = B.get_data(f, 'simcY_err')      #these are absolute errors, sqrt(N)
#data to simc yield ratio
R = dataY / simcY    
R_err = np.sqrt( dataY_err**2/simcY**2 + dataY**2*simcY_err**2/simcY**4 )

B.plot_exp(shms_rate, R, R_err, color='red', label='After Target Boiling Corrections')

#----------
#HMS Delta/SHMS Delta CUTS
f = B.get_file('yield_before.data')
Run = B.get_data(f, 'Run')
dataY = B.get_data(f, 'dataY')    
dataY_err = B.get_data(f, 'dataY_err')     #these are absolute errors, sqrt(N)
simcY = B.get_data(f, 'simcY')
simcY_err = B.get_data(f, 'simcY_err')      #these are absolute errors, sqrt(N)
#data to simc yield ratio
R = dataY / simcY    
R_err = np.sqrt( dataY_err**2/simcY**2 + dataY**2*simcY_err**2/simcY**4 )

B.plot_exp(shms_rate, R, R_err, color='blue', marker='^', label='Before Target Boiling Corrections')

#---------------------------

B.pl.xticks(x, my_xticks)  #label x-axis values
B.pl.title('H(e,e\'p) Elastics  Yield Ratio')

B.pl.grid(linestyle='-')
B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
B.pl.xlabel('SHMS 3/4 Rate [kHz]')
plt.axhline(y=1, color='black', linestyle='--')
B.pl.legend()
B.pl.show()
'''
