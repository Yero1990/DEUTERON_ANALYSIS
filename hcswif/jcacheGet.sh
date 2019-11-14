#! /bin/bash


#arguments pass to this bash script
#Use: on terminal type (for example) >> ./jcacheGet.sh shms 1791
spec=$1 #for coincidence run, it should be coin
#run=$2

filename='runlists/h2.dat'

for run in $(cat $filename) ; do    
    mss="/mss/hallc/spring17/raw/${spec}_all_0${run}.dat"
    #lustre="/lustre/expphy/cache/hallc/spring17/raw"
    
    jcacheCMD="jcache get ${mss} -e cyero002@fiu.edu -x"
    
    echo "Executing command: ${jcacheCMD}" 
    eval ${jcacheCMD}    

done

  
