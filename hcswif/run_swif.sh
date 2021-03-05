#!/bin/bash

#code usage:  ./run_swif.sh [options]
#where [options] ---> status,  delete

#workflow_name="d2_highPmiss_FULL"
#workflow_name="SHMS_LH2_boiling_studies"
workflow_name="HMS_boiling_studies"
#workflow_name="deuteron_3289"
#workflow_name="Al_dummy"

#runlist_name="current_prot.data"

#runlist_name="h2_Pabs_shms.dat"
#runlist_name="runlists/Al.dat"
runlist_name="runlists/boiling_runs.txt"

#-------April 2018, Boiling STudies-----
#runlist_name="LH2_boiling_hms_Apr_02_2018.dat"
#runlist_name="LD2_boiling_hms_Apr_02_2018.dat"
#runlist_name="LH2_boiling_shms_Apr_02_2018.dat"
#runlist_name="LD2_boiling_shms_Apr_02_2018.dat"
#runlist_name="Carbon_boiling_hms_Apr_02_2018.dat"

#-----------POST 3288--------- 
#runlist_name="runlists/d2580_set1.dat"
#runlist_name="runlists/d2580_set2.dat"
#runlist_name="runlists/d2750_set1.dat"
#runlist_name="runlists/d2750_set2.dat"
#runlist_name="runlists/d2750_set3.dat"
#runlist_name="runlists/d2_full.dat"

#-------------Elastic Data----------
#runlist_name="runlists/shms_elec_singles.dat"


#Various optional flags to add to hcswif workflow
mode=" --mode replay "
#spec=" --spectrometer COIN "
#spec=" --spectrometer SHMS_COIN "
spec=" --spectrometer HMS_ALL "
#spec=" --spectrometer SHMS_ALL "
time=" --time 172800"
events="--events -1"
range="--run 3377"
filelist=" --run file $runlist_name "
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_coin_pElec_hProt.C"     
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_shms_coin.C" 
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_coin_hElec_pProt.C "
replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/HMS/replay_hms.C" 
#replay_script=" --replay /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/SHMS/replay_shms.C " 
disk_usage=" --disk 1000000000 "   #in bytes (or 1 Gb default)
ram="--ram 1000000000 "
cpu_cores="--cpu 8"   #number of cpu cores requested 
project=" --project c-comm2017 "
workflow=" --name $workflow_name"

#Create A workflow
create_workflow="python3 hcswif.py $mode $filelist $replay_script $disk_usage $cpu_cores $spec $ram $project $workflow"

#Add job to existing workflow
#add_job="swif add-job  -workflow $workflow_name -project c-comm2017 -track analysis -name LD2_boiling -script /u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/SCRIPTS/HMS/replay_hms.C -disk 3000000000"

view_file="python3 -m json.tool ${workflow_name}.json"

import="swif import -file ${workflow_name}.json"                
                                                                                                                                                              
run="swif run $workflow_name"
#echo $run

#Execute the commands to create and run a workflow
eval ${create_workflow}

#Add a job
#eval ${add_job}

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
