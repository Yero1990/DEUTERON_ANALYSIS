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
from sys import argv
import getopt

from LT import datafile
import bin_info2 as BI

#Set proper paths to import ROOT
#sys.path.append('../../../../pyroot/')
#sys.path.append('/apps/root/PRO/lib/')
#sys.path.append('/apps/root/PRO/')

# do the root operations directly here
import ROOT as R
from ROOT import *
#from ROOT import *

import numpy as np

# from math import *
# import everything for handling 2d histograms
# import bin_info as BI
# use a corrected version (this ignores the overflow bins)
# import bin_info1 as BI

# some constants
dtr = np.pi/180.

#MeV
MP = 938.272
MN = 939.566
#MD = 1875.6127
MD = 1875.61
me = 0.51099; 


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
#! i_b[i,0]/ i_x[i,1]/ i_y[i,2]/ xb[f,3]/ yb[f,4]/ nx[f,5]/ ny[f,6]/  dataXsec[f,7]/  dataXsec_err[f,8]/  fsiXsec[f,9]/   fsiXsec_err[f,10]/  pwiaXsec[f,11]/  pwiaXsec_err[f,12]/      
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
pm_set = int(sys.argv[1])
data_set = int(sys.argv[2])

print argv
#usage: /apps/python/2.7.12/bin/python calc_avg_kin_v2.py 580 fsi 1
if pm_set == 80:
   output_file = 'pm%i_laget.txt'%(pm_set)
else:
   output_file = 'pm%i_laget_set%i.txt'%(pm_set, data_set)


o = open(output_file,'w')

#Open root file to read cross sections from 2D Pm vs. thnq
root_file_pwia = 'pm%i/Xsec_pm%i_lagetpwia_dataset%i.root'%(pm_set, pm_set, data_set)
root_file_fsi = 'pm%i/Xsec_pm%i_lagetfsi_dataset%i.root'%(pm_set, pm_set, data_set)

# open PWIA file
rf_pwia = R.TFile(root_file_pwia)
# open FSI file
rf_fsi = R.TFile(root_file_fsi)

#Change to FSI file
rf_fsi.cd()

# start with 2D yield histo, Fill(Pm, thnq, FullWeight)
all = BI.get_histo_data_arrays(rf_fsi.H_data2DXsec) 
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


#Get 2D Histogram Bin Info (Pm, thnq) Cross Section 
bin_info_dataXsec        = BI.get_histo_data_arrays(rf_fsi.H_data2DXsec)         
bin_info_fsiXsec         = BI.get_histo_data_arrays(rf_fsi.H_simc2DXsec)         

rf_fsi.Close()

#change to PWIA file and get simc histo
rf_pwia.cd()
bin_info_pwiaXsec        = BI.get_histo_data_arrays(rf_pwia.H_simc2DXsec) 

rf_pwia.Close()

#Loop over bin number (xbin, ybin)->(th_nq_bin, Pm_bin)
for i,acont in enumerate(all.cont):

   # get bin values
   i_bin = all.i[i]
   i_xbin = all.ix[i]
   i_ybin = all.iy[i]
   thnq_b = all.xb[i]
   pm_b = all.yb[i]
   
   if (acont == 0.):
      continue

   else:
      
      #Get data, model cross sections from 2D Hists
      dataXsec        = bin_info_dataXsec.cont[i]      
      dataXsec_err    = bin_info_dataXsec.dcont[i]      
      fsiXsec        = bin_info_fsiXsec.cont[i]      
      fsiXsec_err    = bin_info_fsiXsec.dcont[i] 
      pwiaXsec        = bin_info_pwiaXsec.cont[i]      
      pwiaXsec_err    = bin_info_pwiaXsec.dcont[i] 
      
      #print(dataXsec)
      


   l = "%i %i %i %f %f %f %f %.12e %.12e %.12e %.12e %.12e %.12e\n"%(i_bin, i_xbin, i_ybin, thnq_b, pm_b, all.nx, all.ny, dataXsec, dataXsec_err, fsiXsec, fsiXsec_err, pwiaXsec, pwiaXsec_err)
             
                                                                          
   o.write(l)
o.close()


