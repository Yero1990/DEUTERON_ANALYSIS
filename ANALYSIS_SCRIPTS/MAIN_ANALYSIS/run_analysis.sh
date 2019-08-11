#!/bin/bash


#filename='/u/group/E12-10-003/cyero/simc_deep/input_kinematics.dat'

#for fname in $(cat $filename) ; do    

#RUN SIMC
CMD1="cd /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/"
#CMD2="root -l -q -b \"run_simc_d2.C(\\\"${fname}\\\")\""
CMD2="/apps/python/2.7.12/bin/python run_full_analysis.py nominal"

#echo "Changing Directory to $CMD1"
eval ${CMD1}

#echo "**********************************************"
#echo "level 0"
#echo "**********************************************"
#echo
#echo
#eval "echo $ROOTSYS"

#echo "**********************************************"
#echo "level 1"
#echo "**********************************************"
source /site/12gev_phys/softenv.sh 2.3
    
#eval "echo $ROOTSYS"

eval ${CMD2}

#echo "**********************************************"
#echo "Finished!"

#done
