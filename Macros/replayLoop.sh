#! /bin/bash
 
#$1 is the first argument and takes the run number as input: example-> ./replayLoop.sh 1161
#runNUM=$1 
#numEvents=$2

#Add optional parameters to run code as ./replayLoop.sh -run 1161 -evt 1000

while getopts run:evt: option
do
    case "${option}"
	in
	run) runNUM=${OPTARG};;
	echo $runNUM
	evt) numEvents=${OPTARG}
	    


	    script="./UTIL_COMM_ONEPASS/SCRIPTS/HMS/replay_hms.C"
	    
	    run_hcana="./hcana -q \"${script}(${runNUM}, ${numEvents})\""
	    
	    eval ${run_hcana}
	    
    esac
done	    
