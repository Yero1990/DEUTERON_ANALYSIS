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

MP = 938.27200
MN = 939.56533
MD = 1875.6127


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
#! th_nq_mc[f,0]/ th_nq_calc[f,1]/ pm[f,2]/ Ei[f,3]/ omega[f,4]/ th_e[f,5]/ q_lab[f,6]/ pf[f,7]/ pm_mc[f,8]/ q_mc[f,9]/ th_pq_cm[f,10]/ beta_cm[f,11]/ phi[f,12]/ cos_phi[f,13]/ cos_2phi[f,14]/ xb[f,15]/ yb[f,16]/ ib[i,17]/ ix[i,18]/ iy[i,19]/ phei[f,20]/ thei[f,21]/ phpi[f,22]/ thpi[f,23]/ sin_phi[f,24]/ nx[i,25]/ ny[i,26]/ cont[f,27]/ alpha_c[f,28]/ theta_pq[f,29]/ theta_pq_calc[f,30]/
"""
#------------------------------------------------------------

# list of histograms

n=0
for l in kin_file.data:
    n += 1
    kin_n = l['kin']
    kin = kin_n.split('_').pop()
    output_file = output_dir+"kin_av_thnq_pm_"+kin+output_ext
    o = open(output_file,'w')
    print "Setting number ", kin," Kinematics = ", kin, " output file : ", output_file
    # create simc results file name
    simc_result_file = simc_head+kin+simc_file_ext
    #
    root_file = dir+simc_result_file
    # open file
    rf = R.TFile(root_file)
    if rf.IsOpen() == 0:
       print "problem opening : ", root_file
       continue
    # get contens
    # use only those that are filled
    # start with yield histo
    all = BI.get_histo_data_arrays(rf.histo_yield)
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
    #
    bin_info_Ei        = BI.get_histo_data_arrays(rf.avg_Ein)
    bin_info_Ef        = BI.get_histo_data_arrays(rf.avg_eaf)
    bin_info_the       = BI.get_histo_data_arrays(rf.avg_theta_e)
    bin_info_pm        = BI.get_histo_data_arrays(rf.avg_pmiss)
    bin_info_qmu2      = BI.get_histo_data_arrays(rf.avg_Q2)
    bin_info_omega     = BI.get_histo_data_arrays(rf.avg_omega)
    bin_info_theta_pq  = BI.get_histo_data_arrays(rf.avg_theta_pq)
    bin_info_thet_prq  = BI.get_histo_data_arrays(rf.avg_th_nq)
    bin_info_q         = BI.get_histo_data_arrays(rf.avg_q3)
    bin_info_phix      = BI.get_histo_data_arrays(rf.avg_ph_pq)
    bin_info_sinphix  = BI.get_histo_data_arrays(rf.avg_sph_pq)
    bin_info_cosphix  = BI.get_histo_data_arrays(rf.avg_cph_pq)
    # bin_info_cos2phix = BI.get_histo_data_arrays(rf.APcos2phix)
    bin_info_pf        = BI.get_histo_data_arrays(rf.avg_pf)
    # direction information used for differ
    # these need to be the horizontal and verticla angles and NOT the target/transport angles

    # not used here
    
    # bin_info_phei        = BI.get_histo_data_arrays(rf.avg_ph_e_tg)
    # bin_info_thei        = BI.get_histo_data_arrays(rf.avg_th_e_tg)
    # bin_info_phpi        = BI.get_histo_data_arrays(rf.avg_ph_p_tg)
    # bin_info_thpi        = BI.get_histo_data_arrays(rf.avg_ph_e_tg)
    
    # loop over all data
    #
    for i,acont in enumerate(all.cont):
       # get bin values
       i_bin = all.i[i]
       thnq_b = all.xb[i]
       pm_b = all.yb[i]
       if (acont == 0.):
          # skip zero content bins
          continue
       else:
          # convert rad to deg and GeV to MeV 
          Ei        = bin_info_Ei.cont[i]*1000.
          Ef        = bin_info_Ef.cont[i]*1000.
          the       = bin_info_the.cont[i]/dtr
          pm_mc     = bin_info_pm.cont[i]
          qmu2      = bin_info_qmu2.cont[i]*1.e6
          omega_h   = bin_info_omega.cont[i]*1000.
          theta_pq  = bin_info_theta_pq.cont[i]/dtr
          thet_prq  = bin_info_thet_prq.cont[i]
          q_mc      = bin_info_q.cont[i]*1000.
          phi       = bin_info_phix.cont[i]/dtr
          sin_phi   = bin_info_sinphix.cont[i]
          cos_phi   = bin_info_cosphix.cont[i]
          # cos_2phi  = bin_info_cos2phix.cont[i]
          pf        = bin_info_pf.cont[i]*1000.
          # phei      = bin_info_phei.cont[i]
          # thei      = bin_info_thei.cont[i]
          # phpi      = bin_info_phpi.cont[i]
          # thpi      = bin_info_thpi.cont[i]
          #
          # calculate electron kinematics from measured, averaged quantities
          omega = Ei - Ef
          q2 = 4.*Ei*Ef*np.sin(the*dtr/2.)**2
          q_lab = np.sqrt(q2 + omega*omega)
          if q_lab==0.:
             # unphysical, skip
             continue
          # calculate hadron kinematics
          Ep = np.sqrt( MP**2 + pf**2)
          # calculated missing momentum
          pmc2 = (omega+MD-Ep)**2 - MN**2
          if (pmc2 < 0.):
             print 'calculated pm**2 < 0. ', pmc2, ' use pm_mc : ', pm_mc
             pmc = pm_mc
          else:
             pmc = np.sqrt ( pmc2 )
          En = np.sqrt(MN**2 + pmc**2);
          
          # center of mass motion
          beta_cm = q_lab/(MD+omega)
          gamma_cm = 1./np.sqrt(1. - beta_cm**2)

          # momentum components
          p_par = ( pf**2 + q_lab**2 - pmc**2)/ (2.*q_lab)
          p_perp2 = pf**2 - p_par**2
          if (p_perp2 < 0.):
             print 'calculated p_perp**2<0. : ', p_perp2,' --->   estimate it using theta_pq :', theta_pq
             print 'p_par = ', p_par, ', p_perp(pf) = ', pf*np.sin(dtr*theta_pq), ', p_perp(pm) = ', pm_mc*np.sin(dtr*thet_prq)
             p_perp = pf*np.sin(dtr*theta_pq)
             theta_pq_calc = theta_pq
          else:
             p_perp = np.sqrt(p_perp2)
             cthpq = p_par/pf
             theta_pq_calc = np.arccos(cthpq)/dtr             
          p_par_cm = gamma_cm*p_par - gamma_cm*beta_cm*Ep
          # angle in the cm
          th_p_cm = 0.
       
          if p_par_cm == 0. :
             th_p_cm = np.pi
          if p_par_cm > 0. :
             th_p_cm = np.arctan(p_perp/p_par_cm)
          if p_par_cm < 0. :
             th_p_cm = np.pi+np.arctan(p_perp/p_par_cm)
       
          theta_pq_cm = th_p_cm/dtr
          
          # calculate angles using calculated pm
          denom = q_lab**2 + pmc**2 - pf**2
          num = (2.*q_lab*pmc)
          
          cth_nq = -2.;
          if num > 0. : 
             cth_nq = denom/num
             theta_nq = 0.
          if abs(cth_nq) <=1.:
             theta_nq = np.arccos(cth_nq)/dtr;
          # calculate alpha
          pz_n = pmc*np.cos(theta_nq*dtr)
          p_n_minus = En - pz_n
          alpha_calc = p_n_minus/MN
          # write output file
          # current header line:
          #! th_nq_mc[f,0]/ th_nq_calc[f,1]/ pm[f,2]/ Ei[f,3]/ omega[f,4]/ th_e[f,5]/ q_lab[f,6]/ pf[f,7]/ pm_mc[f,8]/ q_mc[f,9]/ th_pq_cm[f,10]/ beta_cm[f,11]/ phi[f,12]/ cos_phi[f,13]/ cos_2phi[f,14]/ xb[f,15]/ yb[f,16]/ ib[i,17] ix[i,18]/  iy[i,19]/ phei[f,20]/ thei[f,21]/ phpi[f,22]/ thpi[f,23]/ sin_phi[f,24]/ nx[i,25]/ ny[i,26]/ cont[f,27]/ theta_pq[f,28]/ theta_pq_calc[f,29]/"
          l = "%r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %d %d %d %r %r %r %r %r %d %d %r %r %r %r\n"%( \
             # 0
             thet_prq, \
             # 1
             theta_nq, \
             # 2
             pmc, \
             # 3
             Ei, \
             # 4
             omega, \
             # 5
             the, \
             # 6
             q_lab, \
             # 7
             pf, \
             # 8
             pm_mc, \
             # 9
             q_mc, \
             # 10
             theta_pq_cm, \
             # 11
             beta_cm, \
             # 12
             phi, \
             # 13
             cos_phi, \
             # 14
             # cos_2phi,\
             -9999.,\
             # 15
             all.xb[i], \
             # 16
             all.yb[i], \
             # 17
             i_bin, \
             # 18
             all.ix[i], \
             # 19
             all.iy[i], \
             #20 
             # phei, \
             -9999.,\
             #21
             # thei, \
             -9999.,\
             #22
             # phpi, \
             -9999.,\
             #23
             # thpi, \
             -9999.,\
             # 24
             sin_phi, \
             # 25
             all.nx, \
             # 26
             all.ny, \
             # 27
             all.cont[i], \
             # 28
             alpha_calc, \
             # 29
             theta_pq, \
             #30
             theta_pq_calc)
          o.write(l)
    # end of the loop over all data
    o.close()
#    
