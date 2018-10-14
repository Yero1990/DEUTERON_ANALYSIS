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
    raw data files from tape.  DONE.

2.  Do Scaler replay over the run list. Preferably via ifarm-job submission 
    since it might take a longer time to do locally.   DONE

3.  Run checkEpics.C on the hms/shms/coin run lists to get EPICS variables from the ROOTfiles
    produced in STEP 2. Loop over run lists to get camera angles as well.   DONE

4.  Run make_kinFile.py on the hms/shms/coin run lists to produce:
    **  standard.kinematics files 
    **  spec_kin.dat files containing all the relevant information for each run (target, coll., raster, momentum, angles, . . .)
    **  good run lists (file with only run numbers) to be read by hcswif to submit jobs
    
5.  With a solid knowledge of the spectrometer momentum/angles, one can start looking at kinematics
    variables such as the invariant mass W.

