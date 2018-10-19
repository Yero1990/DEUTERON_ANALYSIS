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
    
5.  Combined runs with the same kinematics in /combined_data dir. Put individual runs in /single_runs_data dir.




Why do we have NMR in HMS dipole, but NOT in SHMS dipole?  Could NOT get the NMR to work because the field was not homogeneous enough in SHMS. 
NO saturation in the SHMS dipole, so we can rely on the set current to relate to a momentum.

What is NMR calibrated against? In 6 GeV Era, the relation was empirically determined from a series of H(e,e'p) checks

Initial Field--->Momentum Mapping from Model:

Measure the NMR field from TOSCA MODEL integrated field tell you what bent angle ---> what momentum

TOSCA: A code to calculate magnetic fields