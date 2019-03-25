#! /bin/bash

#code usage:  ./run_swif.sh [options]
#where [options] ---> status,  delete

workflow_name="D2_heep"
#workflow_name="D2_750MeV"

#runlist_name="current_elec.data"
#runlist_name="current_prot.data"
#runlist_name="d2_80.dat"
#runlist_name="d2_580.dat"
#runlist_name="d2_750.dat"
runlist_name="h2.dat"

#Various optional flags to add to hcswif workflow
mode=" --mode replay "
spec=" --spectrometer COIN "
#spec=" --spectrometer SHMS_ALL "
events="--events -1"
#range="--run 3286"
filelist=" --run file $runlist_name "
replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_coin_pElec_hProt.C"     
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_shms_coin.C" 
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_coin_hElec_pProt.C "
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/SHMS/replay_shms.C " 
disk_usage=" --disk 3000000000 "   #in bytes (or 1 Gb default)
ram="--ram 1000000000 "
cpu_cores="--cpu 1"   #number of cpu cores requested 
project=" --project c-comm2017 "
workflow=" --name $workflow_name"


CMD="python3 hcswif.py $mode $filelist $replay_script $disk_usage $cpu_cores $spec $events $project $workflow"
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
