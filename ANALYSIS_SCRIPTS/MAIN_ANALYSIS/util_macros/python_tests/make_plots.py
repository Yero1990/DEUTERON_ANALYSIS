#This pyROOT code containes subroutines for making plots from specific sudies made. For example, H(e,e') Yield Ratio
#Study, or collimator cuts study.

import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
import sys
import time

#Set proper paths to import ROOT
sys.path.append('../../../pyroot/')
sys.path.append('/apps/root/PRO/lib/')
sys.path.append('/apps/root/PRO/')

#FIXME: For some reason, the 1st import does NOT work. It has to be done a 2nd time.
import ROOT
from ROOT import *
from ROOT import *

def plot_hRecon_CollElossCompare():
    
    #This function reads SIMC Rootfile with / without Eloss in HMS Collimator.  The ratio of data / simc yield is taken for
    #the reconstructed quantities to compare the ratios before and after ELoss is simulated in HMS Collimator.
    
    scale = ['noscale', '1', '0.95', '0.90', '0.85', '0.80', '0.75', '0.70']

    for iscale in scale:
        #Setting Fonts (FIXME. NEED TO UNDERSTAND HOW TO SET GLOBALLY)
        #data_hytar.SetTitleFont(22, "t");
        #data_hytar.SetTitleFont(22, "XYZ");
        #data_hytar.SetLabelFont(22, "XYZ");
        
        gStyle.SetOptStat(0)
    
        fdata = TFile.Open('../root_files/collimator_study/scale_%s/heep_data_histos_3288.root'%(iscale), 'read');
        fsimc_noeloss = TFile.Open('../root_files/collimator_study/scale_%s/heep_simc_histos_3288.root'%(iscale), 'read'); #No Eloss in HMS Coll
        fsimc_eloss = TFile.Open('../root_files/collimator_study/Collimator_Eloss/scale_%s/heep_simc_histos_3288.root'%(iscale), 'read'); #Eloss in HMS Coll

        #Open TBrowser
        #b = TBrowser()
        #wait = input('PRESS ENTER TO EXIT BROWSER . . . ')
    

        #Get Histograms To Plot
        data_hytar = fdata.Get('H_hytar')
        data_hytar_eloss = data_hytar.Clone("H_hytar_eloss")
        simc_hytar = fsimc_noeloss.Get('H_hytar')
        simc_hytar_eloss = fsimc_eloss.Get('H_hytar')
        
        data_hyptar = fdata.Get('H_hyptar')
        data_hyptar_eloss = data_hyptar.Clone("H_hyptar_eloss")
        simc_hyptar = fsimc_noeloss.Get('H_hyptar')
        simc_hyptar_eloss = fsimc_eloss.Get('H_hyptar')
        
        data_hxptar = fdata.Get('H_hxptar')
        data_hxptar_eloss = data_hxptar.Clone("H_hxptar_eloss")
        simc_hxptar = fsimc_noeloss.Get('H_hxptar')
        simc_hxptar_eloss = fsimc_eloss.Get('H_hxptar')
        
        data_hdelta = fdata.Get('H_hdelta')
        data_hdelta_eloss = data_hdelta.Clone("H_hdelta_eloss")
        simc_hdelta = fsimc_noeloss.Get('H_hdelta')
        simc_hdelta_eloss = fsimc_eloss.Get('H_hdelta')
    
    
    
        #Take DATA / SIMC Ratio for SIMC_HMS_Collimator with and without Eloss
        
        #HMS Ytar
        data_hytar.Divide(simc_hytar)
        data_hytar.SetMarkerStyle(21)
        data_hytar.SetMarkerSize(0.8)
        data_hytar.SetMarkerColor(kRed)
        data_hytar.SetLineColor(kRed)
        data_hytar.SetLineWidth(2)
        #Divide DATA by SIMC (with HMS Collimator Eloss turne ON)
        data_hytar_eloss.Divide(simc_hytar_eloss)
        data_hytar_eloss.SetMarkerStyle(21)
        data_hytar_eloss.SetMarkerSize(0.8)
        data_hytar_eloss.SetMarkerColor(kBlue)
        data_hytar_eloss.SetLineColor(kBlue)
        data_hytar_eloss.SetLineWidth(2)
        #SetHisto Titles
        data_hytar.SetTitle('HMS Y_{tar} Yield Ratio')
        data_hytar.GetXaxis().SetTitle('HMS dataY_{tar}/simcY_{tar}')
        data_hytar.GetYaxis().SetTitle('Charge Normalized Yield Ratio')
        data_hytar.GetXaxis().SetTitleOffset(1.5)
        data_hytar.GetYaxis().SetTitleOffset(1.2)
        data_hytar.GetXaxis().CenterTitle()
        data_hytar.GetYaxis().CenterTitle()
        
        #HMS Yptar
        data_hyptar.Divide(simc_hyptar)
        data_hyptar.SetMarkerStyle(21)
        data_hyptar.SetMarkerSize(0.8)
        data_hyptar.SetMarkerColor(kRed)
        data_hyptar.SetLineColor(kRed)
        data_hyptar.SetLineWidth(2)
        #Divide DATA by SIMC (with HMS Collimator Eloss turne ON)
        data_hyptar_eloss.Divide(simc_hyptar_eloss)
        data_hyptar_eloss.SetMarkerStyle(21)
        data_hyptar_eloss.SetMarkerSize(0.8)
        data_hyptar_eloss.SetMarkerColor(kBlue)
        data_hyptar_eloss.SetLineColor(kBlue)
        data_hyptar_eloss.SetLineWidth(2)
        #SetHisto Titles
        data_hyptar.SetTitle('HMS Y\'_{tar} Yield Ratio')
        data_hyptar.GetXaxis().SetTitle('HMS dataY\'_{tar}/simcY\'_{tar}')
        data_hyptar.GetYaxis().SetTitle('Charge Normalized Yield Ratio')
        data_hyptar.GetXaxis().SetTitleOffset(1.5)
        data_hyptar.GetYaxis().SetTitleOffset(1.2)
        data_hyptar.GetXaxis().CenterTitle()
        data_hyptar.GetYaxis().CenterTitle()
        
        #HMS Xptar
        data_hxptar.Divide(simc_hxptar)
        data_hxptar.SetMarkerStyle(21)
        data_hxptar.SetMarkerSize(0.8)
        data_hxptar.SetMarkerColor(kRed)
        data_hxptar.SetLineColor(kRed)
        data_hxptar.SetLineWidth(2)
        #Divide DATA by SIMC (with HMS Collimator Eloss turne ON)
        data_hxptar_eloss.Divide(simc_hxptar_eloss)
        data_hxptar_eloss.SetMarkerStyle(21)
        data_hxptar_eloss.SetMarkerSize(0.8)
        data_hxptar_eloss.SetMarkerColor(kBlue)
        data_hxptar_eloss.SetLineColor(kBlue)
        data_hxptar_eloss.SetLineWidth(2)
        #SetHisto Titles
        data_hxptar.SetTitle('HMS X\'_{tar} Yield Ratio')
        data_hxptar.GetXaxis().SetTitle('HMS dataX\'_{tar}/simcX\'_{tar}')
        data_hxptar.GetYaxis().SetTitle('Charge Normalized Yield Ratio')
        data_hxptar.GetXaxis().SetTitleOffset(1.5)
        data_hxptar.GetYaxis().SetTitleOffset(1.2)
        data_hxptar.GetXaxis().CenterTitle()
        data_hxptar.GetYaxis().CenterTitle()
        
        #HMS Delta
        data_hdelta.Divide(simc_hdelta)
        data_hdelta.SetMarkerStyle(21)
        data_hdelta.SetMarkerSize(0.8)
        data_hdelta.SetMarkerColor(kRed)
        data_hdelta.SetLineColor(kRed)
        data_hdelta.SetLineWidth(2)
        #Divide DATA by SIMC (with HMS Collimator Eloss turne ON)
        data_hdelta_eloss.Divide(simc_hdelta_eloss)
        data_hdelta_eloss.SetMarkerStyle(21)
        data_hdelta_eloss.SetMarkerSize(0.8)
        data_hdelta_eloss.SetMarkerColor(kBlue)
        data_hdelta_eloss.SetLineColor(kBlue)
        data_hdelta_eloss.SetLineWidth(2)
        #SetHisto Titles
        data_hdelta.SetTitle('HMS Delta Yield Ratio')
        data_hdelta.GetXaxis().SetTitle('HMS data #delta/simc #delta')
        data_hdelta.GetYaxis().SetTitle('Charge Normalized Yield Ratio')
        data_hdelta.GetXaxis().SetTitleOffset(1.5)
        data_hdelta.GetYaxis().SetTitleOffset(1.2)
        data_hdelta.GetXaxis().CenterTitle()
        data_hdelta.GetYaxis().CenterTitle()
        
        
        #Create Canvas and Draw
        c1 = TCanvas('c1', '', 1500, 1000)
        c1.Divide(2,2)
        
        c1.cd(1)
        data_hytar.Draw("EP")
        data_hytar_eloss.Draw("EPsames")
        data_hytar.SetAxisRange(0.8,1.2, "Y")
        line1 = TLine(-5, 1.0, 5, 1.0)
        line1.SetLineColor(kBlack)
        line1.SetLineWidth(2)
        line1.SetLineStyle(2)
        line1.Draw()
        
        c1.cd(2)
        data_hyptar.Draw("EP")
        data_hyptar_eloss.Draw("EPsames")
        data_hyptar.SetAxisRange(0.8,1.2, "Y")
        line2 = TLine(-0.05, 1.0, 0.05, 1.0)
        line2.SetLineColor(kBlack)
        line2.SetLineWidth(2)
        line2.SetLineStyle(2)
        line2.Draw()
        
        
        c1.cd(3)
        data_hxptar.Draw("EP")
        data_hxptar_eloss.Draw("EPsames")
        data_hxptar.SetAxisRange(0.8,1.2, "Y")
        line3 = TLine(-0.1, 1.0, 0.1, 1.0)
        line3.SetLineColor(kBlack)
        line3.SetLineWidth(2)
        line3.SetLineStyle(2)
        line3.Draw()
        
        c1.cd(4)
        data_hdelta.Draw("EP")
        data_hdelta_eloss.Draw("EPsames")
        data_hdelta.SetAxisRange(0.8,1.2, "Y")
        line4 = TLine(-9, 1.0, 9, 1.0)
        line4.SetLineColor(kBlack)
        line4.SetLineWidth(2)
        line4.SetLineStyle(2)
        line4.Draw()
        
        
        c1.SaveAs('HMS_ReconYield_scale_%s.pdf'%(iscale))
    

def getYield():

    em_cut = ['hCollCut', 'NOhCollCut']

    for icut in em_cut:
    
        #Declare empty numpy arrays to store yield and error
        simcY = np.empty(0)
        simcY_err = np.empty(0)
        dataY = np.empty(0)
        dataY_err = np.empty(0)
        
        #Declare temporary variables to store integral and error
        simcW =  ROOT.Double(0)
        simcW_err = ROOT.Double(0) #declare ROOT type double to store error
        
        dataW =  ROOT.Double(0)
        dataW_err = ROOT.Double(0) #declare ROOT type double to store error
        
        #Read Report
        f = B.get_file('../report_heep.dat')
        run = B.get_data(f, 'Run')
        shms_rate = B.get_data(f, 'ptrig1_rate')  #SHMS 3/4 Rate
        eTrkEff = B.get_data(f, 'eTrkEff')
        
        
        #Open output txt file to store yields
        fout = open('Yield_hCollEloss_%s.dat'%(icut), 'w')
        
        fout.write('#!Run[i,0]/    dataY[f,1]/      dataY_err[f,2]/    simcY[f,3]/       simcY_err[f,4]/    R[f,5]/            R_err[f,6]/          shms_3of4_rate[f,7]/  \n')

    
        #Loop over runlist
        for irun in enumerate(run):
        
            #irun: (0, run1) -> irun[0] = 0, irun[1] = run1
            #      (1, run2) -> irun[0] = 1, irun[1] = run2 
            # . . .
            
            
            #Set ROOTfile Names
            simc_fname = '../heep_simc_histos_%i_%s.root' % (irun[1], icut)
            data_fname = '../heep_data_histos_%i_%s.root' % (irun[1], icut)
            
            #Read ROOTfile and Get Histogram Objects
            simc_file = TFile(simc_fname)
            H_simcW = simc_file.Get('H_W')
        
            data_file = TFile(data_fname)
            H_dataW = data_file.Get('H_W')
            
            
            #Integrate Histograms to Get Yield and Error
            simcW = H_simcW.IntegralAndError(H_simcW.FindBin(0.85), H_simcW.FindBin(1.05), simcW_err) #simcW becomes a value
            dataW = H_dataW.IntegralAndError(H_dataW.FindBin(0.85), H_dataW.FindBin(1.05), dataW_err) #simcW becomes a value
            
            R =  dataW /  simcW
            R_err = np.sqrt( dataW_err**2/simcW**2 + dataW**2*simcW_err**2/simcW**4 )
            print (irun[1])
            fout.write('{}           {}     {}      {}     {}      {}     {}     {}\n'.format(irun[1],  simcW, simcW_err, dataW, dataW_err, R, R_err, shms_rate[irun[0]]) )

            #append(array_to_append, value_to_add)
            simcY = np.append(simcY, simcW)
            simcY_err = np.append(simcY_err, simcW_err)
            dataY = np.append(dataY, dataW)
            dataY_err = np.append(dataY_err, dataW_err)
            
            
        fout.close()

def plotYield():
         
    
    #Read Report
    f = B.get_file('Yield_hCollEloss_hCollCut.dat')
    Run = B.get_data(f, 'Run')
    shms_rate = B.get_data(f, 'shms_3of4_rate')  #SHMS 3/4 Rate
    R = B.get_data(f, 'R')
    R_err = B.get_data(f, 'R_err')
    
    B.plot_exp(shms_rate, R, R_err, color='red', marker='^', label='HMS Collimator Cut')
    my_xticks = ['45.306', '80.372', '271.991', '634.447']
    
    B.pl.xticks(shms_rate, my_xticks)  #label x-axis values
    B.pl.title('H(e,e\'p) Elastics  Yield Ratio')
    
    B.pl.grid(linestyle='-')
    B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
    B.pl.xlabel('SHMS 3/4 Rate [kHz]')
    plt.axhline(y=1, color='black', linestyle='--')
    B.pl.legend()
    #B.pl.show()
    
    f = B.get_file('Yield_hCollEloss_NOhCollCut.dat')
    Run = B.get_data(f, 'Run')
    shms_rate = B.get_data(f, 'shms_3of4_rate')  #SHMS 3/4 Rate
    R = B.get_data(f, 'R')
    R_err = B.get_data(f, 'R_err')
    
    B.plot_exp(shms_rate, R, R_err, color='blue', marker='^', label='NO HMS Collimator Cut')
    my_xticks = ['45.306', '80.372', '271.991', '634.447']
    B.pl.xticks(shms_rate, my_xticks)  #label x-axis values
    B.pl.title('H(e,e\'p) Elastics  Yield Ratio')
    
    B.pl.grid(linestyle='-')
    B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
    B.pl.xlabel('SHMS 3/4 Rate [kHz]')
    plt.axhline(y=1, color='black', linestyle='--')
    B.pl.legend()
    B.pl.show('same')

    '''
    em_cut = ['40']
    color_arr = ['red'] 
    
    for icut in enumerate (em_cut):

        #Read Report
        f = B.get_file('Yield_NO_hColl_Eloss_emcut_%s.dat'%(icut[1]))

        Run = B.get_data(f, 'Run')
        shms_rate = B.get_data(f, 'shms_3of4_rate')  #SHMS 3/4 Rate
        R = B.get_data(f, 'R')
        R_err = B.get_data(f, 'R_err')
        
        B.plot_exp(shms_rate, R, R_err, color=color_arr[icut[0]], marker='^', label='em_cut = %s MeV'%(icut[1]))
        my_xticks = ['45.306', '80.372', '271.991', '634.447']
        
        B.pl.xticks(shms_rate, my_xticks)  #label x-axis values
        B.pl.title('H(e,e\'p) Elastics  Yield Ratio')
        
        B.pl.grid(linestyle='-')
        B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
        B.pl.xlabel('SHMS 3/4 Rate [kHz]')
        plt.axhline(y=1, color='black', linestyle='--')
        B.pl.legend()

    B.pl.show('same')
    '''

def make_plots():
    
    print('Calling make_plots() . . . ')
    getYield()
    plotYield()

make_plots()

if __name__=="make_plots__":
    make_plots()

