import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
import sys
import time


#Set proper paths to import ROOT
sys.path.append('../../../../pyroot/')
sys.path.append('/apps/root/PRO/lib/')
sys.path.append('/apps/root/PRO/')

#FIXME: For some reason, the 1st import does NOT work. It has to be done a 2nd time.
import ROOT as R
from ROOT import *
from ROOT import *

#import ROOT as R

print('OK')

#rf = ROOT.TFile('../worksim_voli/d2_pm580_lagetfsi_rad_set1.root')

#print(rf.H_kf_avg)

'''
f1 = TFile.Open('../root_files/collimator_study/scale_1/heep_data_histos_3288.root', 'read');
f2 = TFile.Open('../root_files/collimator_study/scale_1/heep_simc_histos_3288.root', 'read');

#Open TBrowser
b = TBrowser()

#Get Histograms To Plot
data_hytar = f1.Get('H_hytar')
simc_hytar = f2.Get('H_hytar')

data_hyptar = f1.Get('H_hyptar')
simc_hyptar = f2.Get('H_hyptar')

data_hxptar = f1.Get('H_hxptar')
simc_hxptar = f2.Get('H_hxptar')

data_hdelta = f1.Get('H_hdelta')
simc_hdelta = f2.Get('H_hdelta')


#Take DATA / SIMC Ratio
data_hytar.Divide(simc_hytar)
data_hytar.SetMarkerStyle(21)
data_hytar.SetMarkerSize(0.5)
data_hytar.SetMarkerColor(kRed)
data_hytar.SetLineColor(kRed)
data_hytar.SetLineWidth(2)
data_hytar.SetTitle('HMS Y_{tar} Yield Ratio')
data_hytar.GetXaxis().SetTitle('HMS dataY_{tar}/simcY_{tar}')
data_hytar.GetYaxis().SetTitle('Charge Normalized Yield Ratio}')


#Create Canvas and Draw
c1 = TCanvas('c1', '', 500, 500)
c1.Divide(2,2)

data_hytar.Draw("EP")
c1.SaveAs('H_W.pdf')


wait = input('PRESS ENTER TO EXIT BROWSER . . . ')
'''
