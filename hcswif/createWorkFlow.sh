#! /bin/bash

workflow="hallc_epicsCheck"

#Various optional flags to add to hcswif workflow
mode=" --mode replay "
spec=" --spectrometer HMS_ALL "
run="--run 1149-1154 1157-1171"
events="--events -1"
filelist=" --filelist filelist "
replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/UTIL_COMM_ONEPASS/SCRIPTS/HMS/replay_hms.C "
disk_usage=" --disk 1000000000 "   #in bytes (or 1 Gb)
project=" --project c-comm2017 "
workflow_name=" --name $workflow"


CMD="./hcswif.py $mode $spec $run $events $filelist $replay_script $disk_usage $project $workflow_name"
echo $CMD

view_file="python3 -m json.tool $workflow.json"
#echo $view_file
import="swif import -file $workflow.json"                                                                                                                                                                              
#echo $import
run="swif run $workflow"
#echo $run

#Execute the commands to create and run a workflow
eval ${CMD}
#eval ${view_file}
#eval ${import}
#eval ${run}



#DELETING A WORKFLOW
DEL_CMD="swif cancel -workflow $workflow -delete"
#VIEWING THE WORKFLOW STATUS
STATUS_CMD="swif status $workflow"

usr_flag=$1
#echo $DEL_FLOW
if [ "$usr_flag" = "delete" ]
then 
    eval ${DEL_CMD}

elif [ "$usr_flag" = "status" ]
then
    eval ${STATUS_CMD}
    
else
    echo Everything OK!
fi
