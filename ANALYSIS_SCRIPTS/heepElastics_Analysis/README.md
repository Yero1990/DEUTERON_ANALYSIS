********************************
** H(e,e'p) Elastics Analysis **
********************************


This directory is intended to be used for analyzing all H(e,e'p) runs
taken during the December-2017/Spring-2018 Run Period. A run list with 
potential H(e,e'p) runs was completed, and needs to be narrowed down as 
a first step in this analysis.


*****************************************
**STEP 1: Narrow Down the H(e,e'p) List**
*****************************************

1.  Use the jcacheGet.py script to read the H(e,e')p run list and get the
    raw data files from tape.

2.  Do Scaler replay over the run list. Preferably via ifarm-job submission 
    since it might take a longer time to do locally.

3.  Run checkEpics.C on the hms/shms/coin run lists to get EPICS variables from the ROOTfiles
    produced in STEP 2. Loop over run lists to get camera angles as well.

4.  Run plotEpics.C on the hms/shms/coin run lists to plot Magnet Currents and Momentum as
    a function of Run Number, as well as generate a .csv file with the correct spectrometer
    momentum to check against the kinematics file. The camera angles will also be checked against
    the kinematics file.

5.  With a solid knowledge of the spectrometer momentum/angles, one can start looking at kinematics
    variables such as the invariant mass W.

