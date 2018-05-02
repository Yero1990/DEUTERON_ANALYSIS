#!/usr/bin/env python
import time,sys,os,argparse,atexit,subprocess,math
def main():

   for nrun in range (1657,1676):
     FName="cache/shms_all_0{0:4d}.dat".format(nrun)
     if os.path.isfile(FName) :
       command=" ../hcana/hcana -q \"UTIL_COMM_ONEPASS/SCRIPTS/SHMS/replay_shms.C({0:4d},-1)\"".format(nrun)
       print(command)
       process = subprocess.Popen(command,shell=True)
       process.wait()
       print(' File exist : {0}'.format(FName))
     else:
       print(' File does not exist : {0}'.format(FName))
   

if __name__=='__main__': main()
