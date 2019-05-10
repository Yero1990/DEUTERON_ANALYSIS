#!/usr/bin/bash

#RUN SIMC
CMD1="cd /u/group/E12-10-003/cyero/simc_deep"
CMD2="root -l test.C "

eval ${CMD1}
#eval ${CMD2}


#!/usr/bin/bash

echo "**********************************************"
echo "level 0"
echo "**********************************************"
echo
echo
eval "echo $ROOTSYS"

echo "**********************************************"
echo "level 1"
echo "**********************************************"
source /site/12gev_phys/softenv.sh 2.3

eval "echo $ROOTSYS"

#simc_dir="/u/group/E12-10-003/cyero/simc_deep"

#root -l -q -b "test.C"
eval ${CMD2}
echo "**********************************************"
echo "Finished!"
