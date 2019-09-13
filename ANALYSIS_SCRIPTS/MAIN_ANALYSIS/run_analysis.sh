#!/bin/bash
 

#CHANGE TO MAIN_ANALYSIS DIRECTORY FOR DEUTERON ANALYSIS
CMD1="cd /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/"

#ARGUMENT is description of cut being varied. Ex. Em40MeV, Em50MeV, ztar2cm, etc. (this is for systematic studies)
#Make sure to make the appropiate changes to the cut ranges in the input file of run_full_analysis.py

#CMD2="/apps/python/2.7.12/bin/python run_full_analysis.py Em_ep1mr_thr"        
CMD2="root -l -q -b \"main_analysis.C(1)\""                                                                           

eval ${CMD1}

source /site/12gev_phys/softenv.sh 2.3
    
eval ${CMD2}

