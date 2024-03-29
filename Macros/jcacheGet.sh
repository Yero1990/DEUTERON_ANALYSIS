#! /bin/bash


#arguments pass to this bash script
#Use: on terminal type (for example) >> ./jcacheGet.sh shms 1791

#User input
spec=$1    #hms, shms or coin
run=$2


#for run in {1149..1171}
#do
    

#Use: on terminal type (for example) >> jcacheGet.sh shms 1791
#spec=$1 
#runNUM=$2

#for run in {1149..1171}
#do
#filename='h2_3259.dat'
#filename='shms_elec_singles.dat'
#filename='target_boiling_study/Al_boiling_hms_Apr_02_2018.dat'

filename='SHMS_Lumi_Oct22_2018.txt'

for run in $(cat $filename) ; do    
    
    #echo ${run[0]}
    mss="/mss/hallc/spring17/raw/${spec}_all_0${run}.dat"
    #lustre="/lustre/expphy/cache/hallc/spring17/raw"
    
    jcacheCMD="jcache get ${mss} -e cyero002@fiu.edu -x"
    
    echo "Executing command: ${jcacheCMD}" 
    eval ${jcacheCMD}    

done

  
