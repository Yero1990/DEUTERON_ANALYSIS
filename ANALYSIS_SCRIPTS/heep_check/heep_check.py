import os
import subprocess as sp
import sys
from sys import argv
import numpy as np


#Define constants
dtr = np.pi / 180.
Mp = 938.272   #proton mass [MeV]


#Define W and its derivatives for H(e,e'p) elastic Hydrogen
Eb = 10600.5       #Beam Eenrgy [MeV]
Ef = 8534.2488     #final electron energy [MeV]
th_e = 12.194      #electron angle [deg] from central spectrometer camera

# nu = Eb - Ef 
# Q2 = 4.*Eb*Ef*np.sin(th_e/2)**2
# W2 = Mp**2 + 2*Mp*nu - Q2 


#derivative of W with respect to beam energy
dW_dEb = Ef / Eb      

#derivative of W with respect to final e- energy
dW_dEf = -Eb / Ef     

#derivative of W with respect to e- angle
dW_the = -2.*Eb*Ef/Mp * np.sin(th_e*dtr/2.) * np.cos(th_e*dtr/2.)
