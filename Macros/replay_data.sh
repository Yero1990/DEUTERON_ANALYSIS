#! /bin/bash 

#---Make your own run list and loov over it----
filename='d2_580.dat'

for run in $(cat $filename) ; do
    cmd="./hcana -q \"DEUTERON_ANALYSIS/SCRIPTS/COIN/replay_production_coin_pElec_hProt.C($run,-1)\""
    echo $cmd
    eval $cmd
done
