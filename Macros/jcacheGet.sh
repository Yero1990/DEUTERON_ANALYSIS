#! /bin/bash


#arguments pass to this bash script
<<<<<<< HEAD
#Use: on terminal type (for example) >> ./jcacheGet.sh shms 1791
spec=$1 
runNUM=$2

#for run in {1149..1171}
#do
    
    mss="/mss/hallc/spring17/raw/${spec}_all_0${runNUM}.dat"
=======
#Use: on terminal type (for example) >> jcacheGet.sh shms 1791
spec=$1 
#runNUM=$2

for run in {1149..1171}
do
    
    mss="/mss/hallc/spring17/raw/${spec}_all_0${run}.dat"
>>>>>>> 7c4e99886e1465fdfecf12f5b429c60777054fae
    #lustre="/lustre/expphy/cache/hallc/spring17/raw"
    
    jcacheCMD="jcache get ${mss} -e cyero002@fiu.edu -x"
    
    echo "Executing command: ${jcacheCMD}" 
    eval ${jcacheCMD}    

<<<<<<< HEAD
#done
=======
done
>>>>>>> 7c4e99886e1465fdfecf12f5b429c60777054fae
  
