#!/bin/bash

#cmd="source /apps/root/PRO/setroot_CUE.csh"


#RUN DATA
#CMD1_data="cd /u/group/E12-10-003/cyero/hallc_replay"
#CMD2_data="./hcana -q \"UTIL_COMM_ONEPASS/SCRIPTS/COIN/replay_production_coin_pElec_hProt.C(3288, -1)\" "
#eval ${CMD1_data}
#eval ${CMD2_data}

#RUN SIMC
CMD1="cd /u/group/E12-10-003/cyero/simc_heep"
CMD2="/apps/root/PRO/bin/root.exe run_simc_h2.C"

eval ${CMD1}
eval ${CMD2}


