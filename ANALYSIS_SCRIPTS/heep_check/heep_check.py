import os
import subprocess as sp
import sys
from sys import argv
import numpy as np



#----------------USER INPUT---------------


#Electron Kinematics
Eb = 10600.5       #Beam Eenrgy [MeV]
Ef = 8534.2488     #final electron energy or momentum ... same thing [MeV] 

#3288
th_e = 12.194      #electron angle [deg] from central spectrometer camera
#3371
#th_e = 13.93      #electron angle [deg] from central spectrometer camera
#3374
#th_e = 9.928
#3377
#th_e = 8.495

#Relative Uncertainties
p1 = dEb_Eb = 0.001    #dEb / Eb 0.0003914909
p2 = dEf_Ef = -0.001    #dEf / Ef
p3 = dthe = -0.0005      #dthe [rad]

#-------------------------------------------

#Define constants
dtr = np.pi / 180.
Mp = 938.272   #proton mass [MeV]



# nu = Eb - Ef 
# Q2 = 4.*Eb*Ef*np.sin(th_e/2)**2
# W2 = Mp**2 + 2*Mp*nu - Q2 


#derivative of W with respect to beam energy
dW_dEb = Ef / Eb      

#derivative of W with respect to final e- energy
dW_dEf = -Eb / Ef     

#derivative of W with respect to e- angle
dW_dthe = -2.*Eb*Ef/Mp * np.sin(th_e*dtr/2.) * np.cos(th_e*dtr/2.)



dEb = p1 * Eb
dEf = p2 * Ef
dthe = p3

#Variations 
dW_1 = dW_dEb * dEb
dW_2 = dW_dEf * dEf
dW_3 = dW_dthe * dthe
dW_tot = dW_1 + dW_2 + dW_3

print('------------------------\n')
print('----H(e,e\'p) Check-----\n')
print('------------------------\n')
print('The changes are in Wshift[in MeV] / MeV in Eb or Ef or Wshift[in MeV]/mr shift in e- angle  \n')
print('          dW    \n')
print('dEb       %f    \n'%(dW_1))
print('dEf       %f    \n'%(dW_2))
print('dth_e     %f    \n'%(dW_3)) 
print('-------------------\n')
print('dW_total: %f'%(dW_tot))
