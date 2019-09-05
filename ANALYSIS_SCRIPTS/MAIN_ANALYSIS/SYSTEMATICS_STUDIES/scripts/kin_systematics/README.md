This directory contains useful code to determine the systematic uncertainty
on kinematic variables such as beam energy, spectrometer angles and momenta.

How to run the code:

differ3.f  --> main code ( DO NOT TOUCH !)

run_differ_general_v2.py ---> run differ3.py (steering scripts. might need to modify to read avg. kin. files)

analyze_differ.py (the relative errors on the beam, spectrometer momenta and angles are input here!),  
sig_thb (vertical beam direction uncertainty)
sig_phb (horizontal beam direction uncertainty)

sig_th_e (in-plane electron angle uncertainty)
sig_ph_e (out-of-plane electron angle uncertainty)

sig_ef: how well do we know final electron energy
sig_E:  how well do we know the beam energy


Compile the code to get differ3 executable (ONLY NEED TO DO THIS ONCE!)
1) make -f differ3.mak   #this will produce an executable, ./differ3, which is run by
   the steering script

The steering script will read the avg. kin file line by line and
overwrite the differ.in / differ.out for each (thnq, pm) bin in each line of avg. kin. file
look in differ.in for input of average kinematics.
look in differ.out for the derivatives  (systematics results)

2) To run the code, do:
   ipython run_differ_general_v2.py pm_set model data_set
   (example: ipython run_differ_general_v2.py 580 fsi 2)

At the end, the average kinematics file will be sent to ./kin_syst_results with an additional header at the
end called 'tot_err'.  This represents the systematic uncertainty on the the kinematic variables added in
quadrature.  An additional summary files will be sent to ./summary_files, representing the input/output
files used to calcuate the systematics. These are the kinematics for each bin (input) and the derivatives
of the cross sections with respect to each of the kinematics (output). In the /summary_files dir. there is also 
a .txt file containing the individual Xsec derivatives for each (thnq, Pm) bin, as well as the individual Xsec
relative error for each kinematic variable. The advantage of this .txt file is that it wan be used to plot
quickly the derivatives or relative systematics errors vs. Pmiss.

