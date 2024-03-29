import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
import sys


#Set proper paths to import ROOT
sys.path.append('../../../pyroot/')
sys.path.append('/apps/root/PRO/lib/')
sys.path.append('/apps/root/PRO/')

#FIXME: For some reason, the 1st import does NOT work. It has to be done a 2nd time.
import ROOT
from ROOT import *
from ROOT import *


def getYield():
    
    #Declare empty numpy arrays to store yield and error
    simcY = np.empty(0)
    simcY_err = np.empty(0)
    dataY = np.empty(0)
    dataY_err = np.empty(0)
    
    #Declare Histograms to Read from ROOTfile
    H_simcW = TH1F('simcW', '', 100, 0.85, 1.05)
    H_dataW = TH1F('dataW', '', 100, 0.85, 1.05)
        
    H_simcEm = TH1F('simcEm', '', 100, -0.05, 0.1)
    H_dataEm = TH1F('dataEm', '', 100, -0.05, 0.1)
   
    #Declare temporary variables to store integral and error
    simcW =  ROOT.Double(0)
    simcW_err = ROOT.Double(0) #declare ROOT type double to store error
    
    dataW =  ROOT.Double(0)
    dataW_err = ROOT.Double(0) #declare ROOT type double to store error
        
    simcEm =  ROOT.Double(0)
    simcEm_err = ROOT.Double(0) #declare ROOT type double to store error
    
    dataEm =  ROOT.Double(0)
    dataEm_err = ROOT.Double(0) #declare ROOT type double to store error
    
    #Read Report
    f = B.get_file('../../report_heep.dat')
    run = B.get_data(f, 'Run')
    shms_rate = B.get_data(f, 'ptrig1_rate')  #SHMS 3/4 Rate
    eTrkEff = B.get_data(f, 'eTrkEff')

    
    #Open output txt file to store yields
    fout = open('heep_yield.dat', 'w')

    fout.write('#!Run[i,0]/    dataY[f,1]/      dataY_err[f,2]/    simcY[f,3]/       simcY_err[f,4]/    R[f,5]/            R_err[f,6]/      dataY_Em[f,7]/      dataY_Emerr[f,8]/    simcY_Em[f,9]/       simcY_Emerr[f,10]/    R_Em[f,11]/            R_Emerr[f,12]/      shms_3of4_rate[f,13]/  \n')

    
    #Loop over runlist
    for irun in enumerate(run):
        
        #irun: (0, run1) -> irun[0] = 0, irun[1] = run1
        #      (1, run2) -> irun[0] = 1, irun[1] = run2 
        # . . .
        
        print('RUN=',irun)
        
        #Set ROOTfile Names
        simc_fname = '../../root_files/HEEP_ELASTICS/heep_simc_histos_%i_rad.root' % (irun[1])
        data_fname = '../../heep_data_histos_%i_combined.root' % (irun[1])
        
        #Read ROOTfile and Get Histogram Objects
        simc_file = TFile(simc_fname)
        simc_file.GetObject('H_W', H_simcW)
        simc_file.GetObject('H_Emiss', H_simcEm)

        data_file = TFile(data_fname)
        data_file.GetObject('H_W', H_dataW)
        data_file.GetObject('H_Emiss', H_dataEm)

        
        #Integrate Histograms to Get Yield and Error
        simcW = H_simcW.IntegralAndError(H_simcW.FindBin(0.85), H_simcW.FindBin(1.05), simcW_err) #simcW becomes a value
        dataW = H_dataW.IntegralAndError(H_dataW.FindBin(0.85), H_dataW.FindBin(1.05), dataW_err) #simcW becomes a value
        
        simcEm = H_simcEm.IntegralAndError(H_simcEm.FindBin(-0.02), H_simcEm.FindBin(0.04), simcEm_err) #simcEm becomes a value
        dataEm = H_dataEm.IntegralAndError(H_dataEm.FindBin(-0.02), H_dataEm.FindBin(0.04), dataEm_err) #simcEm becomes a value
     
        R =  dataW /  simcW
        R_err = np.sqrt( dataW_err**2/simcW**2 + dataW**2*simcW_err**2/simcW**4 )
        
        R_Em =  dataEm /  simcEm
        R_Emerr = np.sqrt( dataEm_err**2/simcEm**2 + dataEm**2*simcEm_err**2/simcEm**4 )

        print (irun[1], 'RATIO=', R)
        fout.write('{}           {}     {}      {}     {}      {}     {}     {}     {}      {}     {}      {}     {}   {}\n'.format(irun[1],  simcW, simcW_err, dataW, dataW_err, R, R_err, simcEm, simcEm_err, dataEm, dataEm_err, R_Em, R_Emerr, shms_rate[irun[0]]) )

        #append(array_to_append, value_to_add)
        simcY = np.append(simcY, simcW)
        simcY_err = np.append(simcY_err, simcW_err)
        dataY = np.append(dataY, dataW)
        dataY_err = np.append(dataY_err, dataW_err)
    

    fout.close()

def make_plot():
         
    hscale = 'noscale'
    
    #Read Report
    #f = B.get_file('heep_yield_noCoinCut.dat')
    f = B.get_file('heep_yield.dat')

    Run = B.get_data(f, 'Run')
    shms_rate = B.get_data(f, 'shms_3of4_rate')  #SHMS 3/4 Rate
    R = B.get_data(f, 'R')
    R_err = B.get_data(f, 'R_err')
    
    R_Em = B.get_data(f, 'R_Em')
    R_Emerr = B.get_data(f, 'R_Emerr')

    B.plot_exp(shms_rate, R, R_err, color='blue', marker='o', label='W inegrated')
    B.plot_exp(shms_rate, R_Em, R_Emerr, color='red', marker='s', label='Em integrated')

    my_xticks = ['44.64', '77.70', '271.989', '590.267']
    
    B.pl.xticks(shms_rate, my_xticks)  #label x-axis values
    B.pl.title('H(e,e\'p) Elastics  Yield Ratio')
    
    B.pl.grid(linestyle='-')
    B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
    B.pl.xlabel('SHMS 3/4 Rate [kHz]')
    plt.axhline(y=1, color='black', linestyle='--')
    B.pl.legend()
    B.pl.show()

    '''
    hscale = ['1', '0.95', '0.90', '0.85', '0.80', '0.75', '0.70']
    color_arr = ['green', 'blue', 'black', 'magenta', 'fuchsia', 'darkviolet','brown']   
    
    for iscale in enumerate (hscale):

        print(iscale)

        #Read Report
        f = B.get_file('heep_yield_hscale_%s.dat'%(iscale[1]))
        Run = B.get_data(f, 'Run')
        shms_rate = B.get_data(f, 'shms_3of4_rate')  #SHMS 3/4 Rate
        R = B.get_data(f, 'R')
        R_err = B.get_data(f, 'R_err')
        
        B.plot_exp(shms_rate, R, R_err, color=color_arr[iscale[0]], marker='^', label='scale=%s'%(iscale[1]))
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

def heep_analysis():
    
    print('Starting Main Analysis: ')
    
    #hscale = ['noscale', '1', '0.95', '0.90', '0.85', '0.80', '0.75', '0.70']

    #for iscale in hscale:
    #    iscale_name = 'scale_%s'%(iscale)
    #    print (iscale_name)
        #Call Method to output a .dat file with H(e,e'p) Yield 
    
    getYield()
    make_plot()



heep_analysis()


'''
R =  dataY /  simcY
R_err = np.sqrt( dataY_err**2/simcY**2 + dataY**2*simcY_err**2/simcY**4 )



#Read Report
f = B.get_file('../report_heep.dat')
Run = B.get_data(f, 'Run')
shms_rate = B.get_data(f, 'ptrig1_rate')  #SHMS 3/4 Rate
eTrkEff = B.get_data(f, 'eTrkEff')

B.plot_exp(shms_rate, R, R_err, color='red', marker='^', label='Full Corrections')
my_xticks = ['45.306', '80.372', '271.991', '634.447']

B.pl.xticks(shms_rate, my_xticks)  #label x-axis values
B.pl.title('H(e,e\'p) Elastics  Yield Ratio')

B.pl.grid(linestyle='-')
B.pl.ylabel(r'Yield$_{data}$ / Yield$_{simc}$')
B.pl.xlabel('SHMS 3/4 Rate [kHz]')
plt.axhline(y=1, color='black', linestyle='--')
B.pl.legend()
B.pl.show()

'''
