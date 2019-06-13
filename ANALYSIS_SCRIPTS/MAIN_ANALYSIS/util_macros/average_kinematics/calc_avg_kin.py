#
# calculate averaged kinematics from SIMC analysis (Hari's thesis)
#
# some input variables needed to be scaled to the correct units 
#
# use the same kinematics file that has been used to produce
# the mceep input files
#
# this is for thnq_pm 2d histos
#

#!/usr/bin/python
#
# python script to analyze a range of kinematics and runs
#

#
# use only those bins that have a non-zero content -> smaller files
#

import sys
import getopt

from LT import datafile

# do the root operations directly here
import ROOT as R
import numpy as np

# from math import *
# import everything for handling 2d histograms
# import bin_info as BI
# use a corrected version (this ignores the overflow bins)
# import bin_info1 as BI
import bin_info2 as BI

# some constants
dtr = np.pi/180.

MP = 938.272
MN = 939.566
#MD = 1875.6127
MD = 1875.61

'''
# directory for results of simc av kin analysis
dir = "./results/"
# filename of result files (except kinematics)
simc_file_ext = ".pwia.rfn_norad.root"
simc_head = ""
# extension for output files
output_ext = ".data"
output_dir = "./"
#------------------------------------------------------------
def usage():   # describe the usage of this program
   print "\nusage: calc_av_kin.py [-options] kinematics file \n"
   print "options:      -h,? this message "
   print "              -d directory of simc result files"
   print "                 (../results/)"
   print "              -e filename extension (kin.extension) "
   print "                 (.pwia.rfn_norad.root)"
   print "              -H filename head "
   print "                 ()"
   print "              -D output directory"
   print "                 (./)"
   print "              -o output filename extension () "

#------------------------------------------------------------

#------------------------------------------------------------
# Commandline arguments

args = sys.argv[1:]  # argument list w/o program name
#------------------------------------------------------------
# handle options
options = "h?e:o:d:D:H:"  # the ones following the colon require an argument

try:
   options, arguments = getopt.getopt(args, options)

except getopt.GetoptError, (msg, opt) :   
   
   # print help information and exit:
   print "ERROR in option : ",  opt, " reason: ", msg
   usage()
   sys.exit(2)

# handle the option values
for o, v in options:

    if o == "-h" or o == "-?":
        # help
        usage()
        sys.exit(2)
    if o == "-d":
        dir = v
    if o == "-e":
        simc_file_ext = v
    if o == "-o":
        output_ext = v
    if o == "-D":
        output_dir = v
    if o == "-H":
        simc_head = v
        
#------------------------------------------------------------
# old and new database names must be given
if (len(arguments) != 1):
     print 'you need to enter the name of the kinematics file ! \n'
     usage()
     sys.exit(-1)

kinematics_file = arguments[0]
print "will analyze all in : ", kinematics_file

kin_file=datafile.dfile(kinematics_file)
'''
#------------------------------------------------------------
# header information for the output file
header = \
"""
# averaged kinematics results
# averaged kinematic varibles used as input to calculate the averaged 
# kinematics: Ei, omega, th_e, pf
#
# variables with _mc attached are from histograms not calculated
# alpha is the spectatror (neutron) alpha
#\\ xb = th_nq
#\\ yb = pm
# current header line:
#! i_bin[f,0]/ th_nq_bin[f,1]/ pm_bin[f,2]/ Ei[f,3]/ kf[f,4]/ th_e[f,5]/ Pf[f,6]/ th_p[f,7]/ q[f,8]/ th_q[f,9]/ Q2[f,10]/ nu[f,11]/ xbj[f,12]/ Pm[f,13]/ th_pq[f,14]/ th_nq[f,15]/ cphi_pq[f,16]/ sphi_pq[i,17]/ beta_cm[i,18]/ gamma_cm[i,19]/
"""
#------------------------------------------------------------

# list of histograms

#This is only for multiple kinematics
#n=0
#for l in kin_file.data:
#    n += 1
#    kin_n = l['kin']
#    kin = kin_n.split('_').pop()

#create output file to write avg kin
output_file = 'pm580_fsi_norad_avgkin.dat'
o = open(output_file,'w')

#Open root file to read avg kin histos
root_file = 'deep_simc_histos_pm580_lagetfsi_norad_set1.root'
# open file
rf = R.TFile(root_file)
#if rf.IsOpen() == 0:
#   print "problem opening : ", root_file
#continue
# get contens
# use only those that are filled


# start with 2D yield histo, Fill(Pm, thnq, FullWeight)
all = BI.get_histo_data_arrays(rf.H_Pm_vs_thnq_v) 
# write the necessary header parameters
o.write('# histogram parameters \n')
o.write('#\ dx = {0:}\n'.format(repr(all.dx)))
o.write('#\ dy = {0:}\n'.format(repr(all.dy)))
o.write('#\ nx = {0:}\n'.format(repr(all.nx)))
o.write('#\ ny = {0:}\n'.format(repr(all.ny)))
o.write('#\ xmin = {0:}\n'.format(repr(all.xmin)))
o.write('#\ ymin = {0:}\n'.format(repr(all.ymin)))
# write header
o.write(header)

#Get 2D Histogram Bin Info (Avg. kin)
bin_info_Ei        = BI.get_histo_data_arrays(rf.H_Ein_2Davg)          #inc. beam energy [GeV]
bin_info_kf        = BI.get_histo_data_arrays(rf.H_kf_2Davg)           #final e- momentum [GeV]
bin_info_the       = BI.get_histo_data_arrays(rf.H_theta_elec_2Davg)   #final e- angle [deg]
bin_info_Pf        = BI.get_histo_data_arrays(rf.H_Pf_2Davg)           #final p momentum [GeV]
bin_info_thp       = BI.get_histo_data_arrays(rf.H_theta_prot_2Davg)   #final p angle [deg]
bin_info_q         = BI.get_histo_data_arrays(rf.H_q_2Davg)            # |q| momentum transfer
bin_info_thq       = BI.get_histo_data_arrays(rf.H_theta_q_2Davg)      # q-angle with +z beam
bin_info_Q2        = BI.get_histo_data_arrays(rf.H_Q2_2Davg)           # Q2 4-momentum transfer
bin_info_nu        = BI.get_histo_data_arrays(rf.H_omega_2Davg)        # omega, energy transfer
bin_info_xbj       = BI.get_histo_data_arrays(rf.H_xbj_2Davg)          # Xbj, Bjorken
bin_info_Pm        = BI.get_histo_data_arrays(rf.H_Pm_2Davg)           # Missing Momentum
bin_info_thpq      = BI.get_histo_data_arrays(rf.H_theta_pq_2Davg)     # theta_pq [deg]
bin_info_thnq      = BI.get_histo_data_arrays(rf.H_theta_nq_2Davg)     # theta_nq [deg]
bin_info_cphi_pq   = BI.get_histo_data_arrays(rf.H_cphi_pq_2Davg)      # cos(phi_pq) (-1,1)
bin_info_sphi_pq   = BI.get_histo_data_arrays(rf.H_sphi_pq_2Davg)      # sin(phi_pq) (-1,1)


#Loop over bin number (xbin, ybin)->(th_nq_bin, Pm_bin)
for i,acont in enumerate(all.cont):

   # get bin values
   i_bin = all.i[i]
   thnq_b = all.xb[i]
   pm_b = all.yb[i]
   if (acont == 0.):
      # skip zero content bins
      continue

   else:
      print()
      # convert rad to deg and GeV to MeV 
      Ei        = bin_info_Ei.cont[i]*1000.      
      kf        = bin_info_kf.cont[i]*1000.
      the       = bin_info_the.cont[i]
      Pf        = bin_info_Pf.cont[i]*1000.
      thp       = bin_info_thp.cont[i]
      q         = bin_info_q.cont[i]*1000.
      thq       = bin_info_thq.cont[i]
      Q2        = bin_info_Q2.cont[i]*1.e6
      nu        = bin_info_nu.cont[i]*1000.
      xbj       = bin_info_xbj.cont[i]
      Pm        = bin_info_Pm.cont[i]*1000.
      thpq      = bin_info_thpq.cont[i]
      thnq      = bin_info_thnq.cont[i]
      cphi_pq   = bin_info_cphi_pq.cont[i]
      sphi_pq   = bin_info_sphi_pq.cont[i]
      
         
      # center of mass motion
      beta_cm = q/(MD+nu)
      gamma_cm = 1./np.sqrt(1. - beta_cm**2)

      
      # write output file
  

      l = "%d %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n"%( \
                                                                                                                                  # 0
                                                                                                                                  i_bin, \
                                                                                                                                  # 1
                                                                                                                                  thnq_b, \
                                                                                                                                  # 2
                                                                                                                                  pm_b, \
                                                                                                                                  # 3
                                                                                                                                  Ei, \
                                                                                                                                  # 4
                                                                                                                                  kf, \
                                                                                                                                  # 5
                                                                                                                                  the, \
                                                                                                                                  # 6
                                                                                                                                  Pf, \
                                                                                                                                  # 7
                                                                                                                                  thp, \
                                                                                                                                  # 8
                                                                                                                                  q, \
                                                                                                                                  # 9
                                                                                                                                  thq, \
                                                                                                                                  # 10
                                                                                                                                  Q2, \
                                                                                                                                  # 11
                                                                                                                                  nu, \
                                                                                                                                  # 12
                                                                                                                                  xbj, \
                                                                                                                                  # 13
                                                                                                                                  Pm, \
                                                                                                                                  # 14
                                                                                                                                  thpq, \
                                                                                                                                  # 15
                                                                                                                                  thnq, \
                                                                                                                                  # 16
                                                                                                                                  cphi_pq, \
                                                                                                                                  # 17
                                                                                                                                  sphi_pq, \
                                                                                                                                  # 18
                                                                                                                                  beta_cm, \
                                                                                                                                  # 19
                                                                                                                                  gamma_cm)
                                                                          
      o.write(l)
o.close()

