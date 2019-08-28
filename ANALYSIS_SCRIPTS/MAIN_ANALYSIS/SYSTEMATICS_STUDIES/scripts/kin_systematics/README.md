This directory contains useful code to determine the systematic uncertainty
on kinematic variables such as beam energy, spectrometer angles and momenta.

How to run the code:

differ3.f  --> main code ( DO NOT TOUCH !)

run_differ_general.py ---> run differ3.py (steering scripts. might need to modify to read avg. kin. files)

analyze_differ.py (need to edit. input the estimated uncertainties),  
sig_thb (vertical beam direction uncertainty)
sig_phb (horizontal beam direction uncertainty)

sig_th_e (in-plane electron angle uncertainty)
sig_ph_e (out-of-plane electron angle uncertainty)

sig_ef: how well do we know final electron energy
sig_E:  how well do we know the beam energy


Compile the code to get differ3 executable
1) make -f differ3.mak    

The steering script will read the avg. kin file line by line and
overwrite the differ.in / differ.out for each (thnq, pm) bin in each line of avg. kin. file
look in differ.in for input of average kinematics.
look in differ.out for the derivatives  (systematics results)

