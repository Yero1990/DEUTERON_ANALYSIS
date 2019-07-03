#!/usr/bin/python

# creates an input file used by differ3 in order to calculate
# the error in the final cross section due to uncertainties in kinematic variables.

# this version is for the averaged kinematics for 1d and 2d histograms. 

# controleed by options run with -h 

# the total error is in %

#----------------------------------------------------------------------
# produce input files from averaged kinematics and run differ3
#----------------------------------------------------------------------


# import sys, os, string, math, re
# from math import pi, acos, asin
# from numpy import *
import numpy as np
import run_command as rc

# to read the MC data
import ROOT as R
import bin_info2 as BI

import analyze_differ as ad

# import pdb

from LT.datafile import dfile


import argparse as AG

dtr = np.pi/180.

# handle command line arguments
parser = AG.ArgumentParser()

# kinematics file
parser.add_argument("kin_file", help="kinematics file") # this enforces an argument
# optional arguments
parser.add_argument('-d', '--data_dir', help="avg. kin data directory", default = './results/')
parser.add_argument('-f', '--input_file_header', help="input file header", default = 'kin_av_')
parser.add_argument('-e', '--input_file_ext', help="input file tail", default = '.data')
parser.add_argument('-D', '--output_dir', help="output directory", default = './')
parser.add_argument('-F', '--output_file_header', help="output file header", default = 'kin_av_')
parser.add_argument('-E', '--output_file_ext', help="output file tail", default = '.data')


args = parser.parse_args()

# range of kinematics

kinematics = dfile(args.kin_file)



# setup the file names
# old calc
# kin_dir = './kin_av_APt/'
# new calc
kin_dir = args.data_dir
kin_head = args.input_file_header
kin_tail = args.input_file_ext

# old calc
# differ_dir = './differ_Apt/'
# new calc
differ_dir = args.output_dir
differ_head = args.output_file_header
differ_tail = args.output_file_ext

differ_file = 'differ.in'

add_MC_err = False
#add_MC_err = True

if add_MC_err:
    # setup for additional MC error
    MC_dir = '/data/boeglin.1/HallA/analysis/luminita_analysis/results_q3_1/mc_laget_ph_space/'
    MC_head = 'q3_'
    MC_tail = '.root'
    # ROOT histogram with the MC entries (weight = 1)
    # Alpha_t_mc_err

for k in kinematics.data:
   # get kinematics and remove blanks
   kin = k['kin'].strip()
   kin_file = kin_dir + kin_head + kin + kin_tail
   # new output file
   res_file = differ_dir + differ_head + kin + differ_tail
   print "save results in : ", res_file
   results = open(res_file,"w")
   # get the averaged kinematics for each bin
   print 'working on : ', kin_file
   kin_d = dfile(kin_file)
   # add MC error if so selected
   if add_MC_err:
      MC_file = MC_dir + MC_head + kin + MC_tail
      #load the root file
      fmc = R.TFile(MC_file)
      # get the histo data
      mcd = BI.get_histo_data(fmc.Alpha_t_mc_err)
      # create arrays
      mcd.make_arrays()
      # select content > 0
      nz = mcd.cont > 0.
      # create the array with relative MC error (in %)
      err_percent = np.zeros_like(mcd.cont)
      err_percent[nz] = 100./mcd.dcont[nz]
      kin_d.add_key('mc_err')
   # add a new data value
   kin_d.add_key('tot_err')
   # get average of cos(phi)
   cphi = np.array( kin_d.get_data('cos_phi') )
   cphi_av = np.average(cphi)
   phi_off = 0.
   if cphi_av >= 0 :
      phi_off = np.pi
   for ik, ka in enumerate(kin_d.data):
      ib = ka['ib']
      Ei = ka['Ei']
      Ef = Ei - ka['omega']
      # create differ input file name
      outf = open(differ_file,"w")
      # 
      # now write output file
      #
      outf.write('theta_e, phi_e, final electron energy, second line:step sizes in mr and MeV \n')
      l = '%f , 0., %f \n'%(ka['th_e'], Ef)
      outf.write(l)
      outf.write('1.,1.,0.1\n')
      outf.write('theta_p, phi_p (dont change sign for other side) theta=hor, phi = vert \n')
      # calculate php for the proton. Use the average value of phi
      # an offst of pi (or 180 degrees) needs to be subtracted for phi centered around 0 degrees
      # coordinate system used: beam direction: z
      #                         left side     : x
      #                         vertical up   : y
      # this currently wotks only for in-plane settings
      # calculations in calc_kin.C
      #
      # Double_t p_par = ( pow(pf,2) + pow(q_lab,2) - pow(pmc, 2))/ (2.*q_lab) ;
      # Double_t p_perp2 = abs(pow(pf, 2) - pow(p_par, 2));
      # Double_t p_perp = sqrt(p_perp2);
      pf = ka['pf']
      q_lab = ka['q_lab']
      pmc = ka['pm_mc']
      # angle of q with resp. to beam
      cthq = (Ei - Ef*np.cos( ka['th_e']*dtr ) )/q_lab
      theta_q = np.arccos(cthq)
         # direction of the proton
      phi_v = ka['phi']*dtr - phi_off
      p_par = (pf**2 + q_lab**2 - pmc**2)/(2.*q_lab)
      p_per = np.sqrt(pf**2 - p_par**2)
         # find phi
      py = p_per*np.sin(phi_v)
      sphp = py/pf
      php = np.arcsin(sphp)/dtr
         # find theta
      p_xz = np.sqrt(pf**2 - py**2)
      if (p_par == 0.):
         cthpp = 0.
      else:
         cthpp = p_par/p_xz
      thpp = np.arccos(cthpp)
      if phi_v == np.pi/2.:
         thp = theta_q/dtr
      elif phi_v < np.pi/2.:
         thp = (theta_q - thpp)/dtr
      else:
         thp = (theta_q + thpp)/dtr
      l = '%f, %f \n'%(thp, php)
      outf.write(l)
      outf.write('1.,1.\n')
      outf.write('theta_b, phi_b, Incident Energy (theta = vertical, phi = hor !)\n')
      l = '0., 0., %f \n'%(ka['Ei'])
      outf.write(l)
      outf.write('1., 1., .1 \n')
      outf.write('omega independent of E i=1 (energy loss), i=0 otherwise \n')
      outf.write('0\n')
      # output files
      outf.close()
      #ready to run differ
      run_differ = './differ3'
      rc.run_command(run_differ, 'differ_out','differ_err')
      # now analyze differ, output tot_err is in %
      tot_err = ad.get_sig_tot('differ.out', print_all = False)
      if np.isnan(tot_err):
          print 'total_err could not be calculated, it is set to 100% for kinematics : ', kin, ' bin ib = ', ib
          tot_err = 100.      
      # make sure to take the correct value
      if add_MC_err:
         ka['mc_err'] = err_percent[mcd.i == ib][0]
      ka['tot_err'] = tot_err
      # write the new data into a file
   kin_d.add_header_comment(' ------------------------- ')
   kin_d.add_header_comment(' tot_err is in % !')
   kin_d.add_header_comment(' ------------------------- ')
   kin_d.write_all(results, complete_header = True)
# end loop over kinematics

