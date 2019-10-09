#!/bin/bash

run=$1
filename='/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/Macros/shms_elec_singles.dat'



#for run in $(cat $filename) ; do
CMD1="cd /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/set_REFTimeCut" 
CMD="root -l -q -b \"setTimeWindows.C($run, \\\"coin\\\")\""

eval ${CMD1}

source /site/12gev_phys/softenv.sh 2.3  

eval ${CMD}
#done
