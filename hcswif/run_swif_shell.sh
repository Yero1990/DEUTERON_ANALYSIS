#! /bin/bash

#code usage:  ./run_swif.sh [options]
#where [options] ---> status,  delete

workflow_name="heep_check_optics"

#Various optional flags to add to hcswif workflow
mode=" --mode command "
replay_script=" --command /u/group/E12-10-003/cyero/hallc_replay/UTIL_COMM_ONEPASS/hcswif/replay_script.sh "
shell="--shell bash "
disk_usage=" --disk 1000000000 "   #in bytes (or 1 Gb default)
cpu_cores="--cpu 8"   #number of cpu cores requested 
project=" --project c-comm2017 "
workflow=" --name $workflow_name"


CMD="python3 hcswif.py $mode $replay_script $disk_usage $cpu_cores $shell $project $workflow"
#echo $CMD

view_file="python3 -m json.tool ${workflow_name}.json"
#echo $view_file
import="swif import -file ${workflow_name}.json"                                                                                                                                                                              
#echo $import
run="swif run $workflow_name"
#echo $run

#Execute the commands to create and run a workflow
eval ${CMD}

#Change directories
cd_cmd="cd hcswif_output"
eval ${cd_cmd}

eval ${view_file}
eval ${import}
eval ${run}



#DELETING A WORKFLOW
DEL_CMD="swif cancel -workflow $workflow_name -delete"
#VIEWING THE WORKFLOW STATUS
STATUS_CMD="swif status $workflow_name"

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
