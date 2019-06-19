#Calculate the Laget Theory Cross Section at the Averaged Kinematics

# select of reading binary grid data
use_binary = 1

# import laget module
if use_binary:
    import Laget_Xsec_fp_1 as LX
else:
    import Laget_Xsec_fp as LX
        
import LT.box as B
import numpy as np
import sys
from sys import argv

#------------------------------------------------------------
# header information for the output file
header = \
"""
# Laget Cross Section Results at the Averaged Kinematics
# averaged kinematic varibles used as input to calculate the cross section 
# kinematics: Ei, Q2, omega, th_pq_cm, phi_pq
#
#\\ xb = th_nq
#\\ yb = pm
# current header line:
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ nx[f,5]/ ny[f,6]/  pwiaXsec[f,7]/    
"""
#------------------------------------------------------------
#create output file to write cross section @ avg kinematics
pm_set = int(sys.argv[1])
data_set = int(sys.argv[2])

print argv
#usage: ipython calc_cross.py 580 1
if pm_set == 80:
   output_file = 'pm%i_laget_theory.txt'%(pm_set)
else:
   output_file = 'pm%i_laget_theory_set%i.txt'%(pm_set, data_set)

o = open(output_file,'w')
# write header
o.write(header)

dtr = np.pi/180.

fm2ub = 1.e4   #fm^2 to ub

# initalize arrays: there is a link in the current directory
# assume it is in the current directory
deut_data_dir = './'

# select what kind of calculation and set flags
#do_fsi = 0
#do_pwia = 1

# select linear interpolation
lin_interp = 1
# do not save the grid as binary file
save_grid = 0

# intitialize the code
#if use_binary:
#    LX.init_laget('./', do_fsi, lin_interp, save_grid, use_binary)
#else:
#    LX.init_laget('./', do_fsi, lin_interp)


#======================================DO PWIA=============================================================

# read the averaged kinematics file
if pm_set == 80:
    f = B.get_file('../average_kinematics/pm%i_pwia_norad_avgkin.txt'%(pm_set))
else: 
    f = B.get_file('../average_kinematics/pm%i_pwia_norad_avgkin_set%i.txt'%(pm_set, data_set))


#Read Headers to be written to the output Xsec file
i_b = B.get_data(f, 'i_b')      #ith (Pm, th_nq) bin number
i_x = B.get_data(f, 'i_x')      #ith th_nq bin number
i_y = B.get_data(f, 'i_y')      #ith Pm bin number
xb  = B.get_data(f, 'xb')   #theta_nq central bin value [deg]
yb  = B.get_data(f, 'yb')     #Pmiss cental bin value [GeV]
nx    = B.get_data(f, 'nx')     #total number of bins in theta_nq
ny    = B.get_data(f, 'ny')     #total number of bins in Pm


#===============================================================================
#=========  Laget_Xsec_fp_1.f,  get_sigma_laget() Input Parameters =============
#===============================================================================
#units are in MeV and deg [convert to radians, as Laget code takes MeV and radians]

th_cm = B.get_data(f, 'th_pq_cm')*dtr     #center of mass in-plane angle between proton and q-vector [rad]
omega = B.get_data(f,  'omega')           #energy transfer [MeV]
q = B.get_data(f, 'q_lab')                #magnitude of 3-momentum transfer [MeV]
Q2 = q**2 - omega**2                       #4-Momentum Transfer [MeV^2]
cphi = B.get_data(f, 'cos_phi')           #Cos(phi) 
phi = np.arccos(cphi)                      #phi, out-of-plane angle between the proton and q-vector (angle between reaction-scattering plane) [rad]
Ei = B.get_data(f, 'Ei')                  #Incident Beam Energy [MeV]


# DO PWIA
if use_binary:
    LX.init_laget('./', 0, lin_interp, save_grid, use_binary)
else:
    LX.init_laget('./', 0, lin_interp)

sigma = []
for i, e0_i in enumerate(Ei):
    # check kinematics
    print("i = ",i," e0_i= ",e0_i, " Q2= ",Q2[i]," nu= ", omega[i]," th_cm=",th_cm[i], " phi=",phi[i])
    print "p_rec = ", LX.p_recoil(Q2[i], omega[i], th_cm[i])
    # calculate cross sections (fm^2 sr^-2 mev^-1)
    sig = LX.get_sigma_laget(e0_i,Q2[i],omega[i],th_cm[i],phi[i]) * fm2ub    #convert to (ub sr^-2 MeV^-1)
    sigma.append(sig)
    print('sig = ',sig)
    # Write to File
    l = '%i %i %i %.6f %.6f %.6f %.6f %.12e\n'%(i_b[i], i_x[i], i_y[i], xb[i], yb[i], nx[i], ny[i], sig)
    o.write(l)
o.close()

#======================================DO FSI================================================

# read the averaged kinematics file, and output file to write cross sections
if pm_set == 80:
    f = B.get_file('../average_kinematics/pm%i_fsi_norad_avgkin.txt'%(pm_set))
    fname = 'pm%i_laget_theory.txt'%(pm_set)
    output_file = B.get_file(fname)
else: 
    f = B.get_file('../average_kinematics/pm%i_fsi_norad_avgkin_set%i.txt'%(pm_set, data_set))
    fname = 'pm%i_laget_theory_set%i.txt'%(pm_set, data_set)
    output_file = B.get_file(fname)

#Add Key to the output_file header
output_file.add_key('fsiXsec', 'f')

#NOTE: The PWIA and FSI avg. kin. files bin-numbering must be EXACTLY the same. THerefore, there is no need to read them a second time.

#===============================================================================
#=========  Laget_Xsec_fp_1.f,  get_sigma_laget() Input Parameters =============
#===============================================================================
#units are in MeV and deg [convert to radians, as Laget code takes MeV and radians]

th_cm = B.get_data(f, 'th_pq_cm')*dtr     #center of mass in-plane angle between proton and q-vector [rad]
omega = B.get_data(f,  'omega')           #energy transfer [MeV]
q = B.get_data(f, 'q_lab')                #magnitude of 3-momentum transfer [MeV]
Q2 = q**2 - omega**2                       #4-Momentum Transfer [MeV^2]
cphi = B.get_data(f, 'cos_phi')           #Cos(phi) 
phi = np.arccos(cphi)                      #phi, out-of-plane angle between the proton and q-vector (angle between reaction-scattering plane) [rad]
Ei = B.get_data(f, 'Ei')                  #Incident Beam Energy [MeV]


# DO FSI
if use_binary:
    LX.init_laget('./', 1, lin_interp, save_grid, use_binary)
else:
    LX.init_laget('./', 1, lin_interp)

#sigma = []
for i, e0_i in enumerate(Ei):
    # check kinematics
    print("i = ",i," e0_i= ",e0_i, " Q2= ",Q2[i]," nu= ", omega[i]," th_cm=",th_cm[i], " phi=",phi[i])
    print "p_rec = ", LX.p_recoil(Q2[i], omega[i], th_cm[i])
    # calculate cross sections (returns Xsec in fm^2 sr^-2 MeV^-1 (SIMC is in microbarn.  1 ub = 1e-4 fm^2)
    sig = LX.get_sigma_laget(e0_i,Q2[i],omega[i],th_cm[i],phi[i]) * fm2ub    #convert to (ub sr^-2 MeV^-1)
    #sigma.append(sig)

    output_file.data[i]['fsiXsec'] = float("%.12e"%(sig))

    print('sig = ',sig)
    # Write to File
output_file.save(fname)
