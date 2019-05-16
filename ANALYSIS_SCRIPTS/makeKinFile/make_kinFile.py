#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv
import sys
import pandas as pd    #used for data frame
import numpy as np
import re
from scipy import interpolate
from scipy.interpolate import interp1d
import LT.box as B
sys.path.insert(0, '../../Macros')  #Add path to search for modules
from MagInterpolate import GetP


#User Command Line Input
spec = sys.argv[1]   #user cmd-line input 'hms', 'shms', or 'coin' 
                    #Usage: python make_kinFile.py hms

#Script to produce a kinematics file and data file with useful kinematics variables run-by-run
f = B.get_file('epics_data/%s_epics.data' % (spec))

if(spec=='hms'):
    #Read in the run setting into an array
    run = B.get_data(f, 'Run')
    hQ1_set = B.get_data(f, 'hQ1_set')
    hQ2_set = B.get_data(f, 'hQ2_set')
    hQ3_set = B.get_data(f, 'hQ3_set')
    NMR_true = B.get_data(f, 'NMR_true')
    angle = B.get_data(f, 'Angle')
    coll = B.get_data(f, 'Collimator')
    targ = B.get_data(f, 'Target')
    raster = B.get_data(f, 'Raster')
    TFE = B.get_data(f, 'TFE')


elif(spec=='shms'):
  #Read in the run setting into an array
    run = B.get_data(f, 'Run')
    sHB_set = B.get_data(f, 'sHB_set')
    sQ1_set = B.get_data(f, 'sQ1_set')
    sQ2_set = B.get_data(f, 'sQ2_set')
    sQ3_set = B.get_data(f, 'sQ3_set')
    sD_set = B.get_data(f, 'sD_set')
    angle = B.get_data(f, 'Angle')
    coll = B.get_data(f, 'Collimator')
    targ = B.get_data(f, 'Target')
    raster = B.get_data(f, 'Raster')
    TFE = B.get_data(f, 'TFE')

elif(spec=='coin'):
  #Read in the run setting into an array
    run = B.get_data(f, 'Run')
    hQ1_set = B.get_data(f, 'hQ1_set')
    hQ2_set = B.get_data(f, 'hQ2_set')
    hQ3_set = B.get_data(f, 'hQ3_set')
    NMR_true = B.get_data(f, 'NMR_true')
    sHB_set = B.get_data(f, 'sHB_set')
    sQ1_set = B.get_data(f, 'sQ1_set')
    sQ2_set = B.get_data(f, 'sQ2_set')
    sQ3_set = B.get_data(f, 'sQ3_set')
    sD_set = B.get_data(f, 'sD_set')
    hcoll = B.get_data(f, 'hms_Collimator')
    scoll = B.get_data(f, 'shms_Collimator')
    targ = B.get_data(f, 'Target')
    raster = B.get_data(f, 'Raster')
    TFE = B.get_data(f, 'TFE')
    hangle = B.get_data(f, 'hms_Angle')
    sangle = B.get_data(f, 'shms_Angle')
    
   

#Open a file to write kinematics summary file
fout = open('%s_kin.dat'%(spec), 'w')

if(spec=='hms'):
    fout.write('#! Run[i,0]/       hQ1_P[f,1]/       hQ2_P[f,2]/       hQ3_P[f,3]/       hNMR_P[f,4]/       Angle[f,5]/       Target[s,6]/       Target_Mass[f,7]/      hpartmass[f,8]/       Raster[s,9]/       Collimator[s,10]/       TFE[f,11]/ \n')

elif(spec=='shms'):
    fout.write('#! Run[i,0]/  sHB_P[f,1]/  sQ1_P[f,2]/  sQ2_P[f,3]/  sQ3_P[f,4]/  sD_P[f,5]/  Angle[f,6]/  Target[s,7]/  Target_Mass[f,8]/ ppartmass[f,9]/  Raster[s,10]/  Collimator[s,11]/  TFE[f,12]/ \n')

elif(spec=='coin'):
      fout.write('#! Run[i,0]/     hQ1_P[f,1]/     hQ2_P[f,2]/     hQ3_P[f,3]/     hNMR_P[f,4]/    sHB_P[f,5]/     sQ1_P[f,6]/     sQ2_P[f,7]/     sQ3_P[f,8]/     sD_P[f,9]/      hms_Angle[f,10]/       shms_Angle[f,11]/      hms_Collimator[s,12]/      shms_Collimator[s,13]/      Target[s,14]/     Target_Mass[f,15]/     hpartmass[f,16]/     ppartmass[f,17]/      Raster[s,18]/      TFE[f,19]/ \n')  

#Create the standard.kinematics file specific for these studies
f_std = open('standard.kinematics.good_D2Exp', 'w')
f_std.write('#E12-10-003 Experiment Kinematics Data File\n')

#Loop over run list
for index, run in enumerate(run):
    #print 'index = ', index, ' Run = ', run, ' Collimator = ', coll[index]
    
    if(spec=='hms'):
        #Call GetP() to get SET momentum from Mag Current
        Q1_P  = GetP('hms', 'Q1',   hQ1_set[index])
        Q2_P  = GetP('hms', 'Q2',   hQ2_set[index])
        Q3_P  = GetP('hms', 'Q3',   hQ3_set[index])
        NMR_P_true = GetP('hms', 'NMR',  NMR_true[index])
        hpartmass = 0.938272;

    elif(spec=='shms'):
        #Call GetP() to get SET momentum from Mag Current
        HB_P = GetP('shms', 'HB',   sHB_set[index])
        Q1_P = GetP('shms', 'Q1',   sQ1_set[index])
        Q2_P = GetP('shms',  'Q2',   sQ2_set[index])
        Q3_P = GetP('shms',  'Q3',   sQ3_set[index])
        D_P  = GetP('shms', 'D',    sD_set[index])
        ppartmass = 0.00051099;

    elif(spec=='coin'):
        hQ1_P  = GetP('hms', 'Q1',   hQ1_set[index])
        hQ2_P  = GetP('hms', 'Q2',   hQ2_set[index])
        hQ3_P  = GetP('hms', 'Q3',   hQ3_set[index])
        NMR_P_true = GetP('hms', 'NMR',  NMR_true[index])
        sHB_P = GetP('shms', 'HB',   sHB_set[index])
        sQ1_P = GetP('shms', 'Q1',   sQ1_set[index])
        sQ2_P = GetP('shms',  'Q2',   sQ2_set[index])
        sQ3_P = GetP('shms',  'Q3',   sQ3_set[index])
        sD_P  = GetP('shms', 'D',    sD_set[index])
        hpartmass = 0.938272;
        ppartmass = 0.00051099;

    #Get Correct Target Mass
    if(targ[index]=='LH2'):
        targ_mass = 1.00794
    elif(targ[index]=='LD2'):
        targ_mass = 2.014101
    elif(targ[index]=='Al_Dummy_10cm'):
        targ_mass = 26.98;
    elif(targ[index]=='C-Hole'):
        targ_mass = 12.0107;
    elif(targ[index]=='Optics-1'):
        targ_mass = 12.0107;
    #Get Correct Beam Energy from TFE
    gpbeam = 10.6005           #updated from MArk, 11/2/2018 (Measured on April 2018 --should be used up to Spring 2018 Run)
    gpbeam_err = 0.00415



    #Write to File
    if(spec=='hms'):
#        print('Run = ', run,  ' NMR_P_set = ', round(NMR_P,4),  ' NMR_P_true = ', round(NMR_P_true,4), 'NMR_P_%Diff = ',  ( (NMR_P_true - NMR_P)/(NMR_P_true)  ) )
        fout.write('%s      %s           %s             %s             %s              %s            %s          %s           %s           %s             %s           %s\n' % 
                   (int(run), round(Q1_P,4), round(Q2_P,4), round(Q3_P,4),  round(NMR_P_true,4), angle[index], targ[index], targ_mass, hpartmass, raster[index], coll[index], TFE[index] ))

    elif(spec=='shms'):
#        print('Run = ', run,  ' NMR_P_set = ', round(NMR_P,4),  ' NMR_P_true = ', round(NMR_P_true,4), 'NMR_P_Diff = ',  ( (NMR_P_true - NMR_P)/(NMR_P_true)  ) )
        fout.write('%s        %s           %s            %s            %s             %s            %s            %s           %s           %s           %s            %s          %s\n' % 
                   (int(run), round(HB_P,4), round(Q1_P,4), round(Q2_P,4), round(Q3_P,4), round(D_P,4), angle[index], targ[index], targ_mass, ppartmass, raster[index], coll[index], TFE[index] ))

    elif(spec=='coin'):
#        print('Run = ', run,  ' NMR_P_set = ', round(NMR_P,4),  ' NMR_P_true = ', round(NMR_P_true,4), 'NMR_P_Diff = ',  ( (NMR_P_true - NMR_P)/(NMR_P_true)  ) )
        fout.write('%s      %s            %s              %s              %s               %s              %s             %s               %s              %s            %s             %s              %s              %s             %s           %s          %s          %s            %s             %s \n' % 
                   (int(run), round(hQ1_P,4), round(hQ2_P,4), round(hQ3_P,4), round(NMR_P_true,4), round(sHB_P,4), round(sQ1_P,4), round(sQ2_P,4), round(sQ3_P,4), round(sD_P,4), hangle[index], sangle[index],  hcoll[index],  scoll[index],  targ[index], targ_mass,  hpartmass,  ppartmass,  raster[index],  TFE[index] ))                                                             
   

    #Write each run to the standard.kinematics file

    if(spec=='hms'):
        f_std.write('%s\n' % int(run))
        f_std.write('gpbeam = %s\n' % (gpbeam))
        f_std.write('gtargmass_amu = %s\n' % (targ_mass))
        f_std.write('hpartmass = %s\n' % (hpartmass))    #This value should be generalized once I know how to get the particle type we want in the spectrometer
        f_std.write('htheta_lab = -%s\n' % (angle[index]))
        f_std.write('hpcentral = %s\n' % round(NMR_P_true,4) )
        f_std.write('\n')
    elif(spec=='shms'):
        f_std.write('%s\n' % int(run))
        f_std.write('gpbeam = %s\n' % (gpbeam))
        f_std.write('gtargmass_amu = %s\n' % (targ_mass))
        f_std.write('ppartmass = %s\n' % (ppartmass))   
        f_std.write('ptheta_lab = %s\n' % (angle[index]))
        f_std.write('ppcentral = %s\n' % round(D_P,4) )
        f_std.write('\n')
    elif(spec=='coin'):
        f_std.write('%s\n' % int(run))
        f_std.write('gpbeam = %s\n' % (gpbeam))
        f_std.write('gtargmass_amu = %s\n' % (targ_mass))
        f_std.write('hpartmass = %s\n' % (hpartmass))   
        f_std.write('ppartmass = %s\n' % (ppartmass))   
        f_std.write('htheta_lab = -%s\n' % (hangle[index]))
        f_std.write('ptheta_lab = %s\n' % (sangle[index]))
        f_std.write('hpcentral = %s\n' % round(NMR_P_true,4) )
        f_std.write('ppcentral = %s\n' % round(sD_P,4) )
        f_std.write('\n')

#close files
f_std.close()
fout.close()


#Add data from report file to kin. data file

#Read kinematics data
kd = B.get_file('./%s_kin.dat' % (spec))

#add keys to header
kd.add_key('Ps1','f')     #shms 3/4
kd.add_key('Ps2','f')     #shms EL-REAL
kd.add_key('Ps3','f')     #shms EL-CLEAN
kd.add_key('Ps4','f')     #hms 3/4
kd.add_key('Ps5','f')     #None
kd.add_key('Ps6','f')     #Coincidence

if(spec=='hms'):
    kd.add_key('hms_xMisPoint','f')
    kd.add_key('hms_yMisPoint','f')
    kd.add_key('hms_xBPM', 'f')
    kd.add_key('hms_yBPM', 'f')
elif(spec=='shms'):
    kd.add_key('shms_xMisPoint','f')
    kd.add_key('shms_yMisPoint','f')
    kd.add_key('shms_xBPM', 'f')
    kd.add_key('shms_yBPM', 'f')
elif(spec=='coin'):
    kd.add_key('hms_xMisPoint','f')
    kd.add_key('hms_yMisPoint','f')
    kd.add_key('shms_xMisPoint','f')
    kd.add_key('shms_yMisPoint','f')
    kd.add_key('hms_xBPM', 'f')
    kd.add_key('hms_yBPM', 'f')
    kd.add_key('shms_xBPM', 'f')
    kd.add_key('shms_yBPM', 'f')
#Loop over scaler report file from heep runs
for i, run in enumerate(kd['Run']):
    reportFile = "../../../REPORT_OUTPUT/%s/PRODUCTION/replay_%s_scaler_%s_%s.report"% (spec.upper(), spec, run, -1)

    #print(reportFile)
    #Open report file
    f = open(reportFile)

    #Read each line in the report file
    for line in f:
        line = re.split('= | : |\n',line)
        #print (line)
    
        if (("Ps1_factor" in line[0])):
            #print('run: ', run, 'Ps1 = ',line[1])
            kd.data[i]['Ps1'] = int(line[1])
        elif (("Ps2_factor" in line[0])):
            kd.data[i]['Ps2'] = int(line[1])    
        elif (("Ps3_factor" in line[0])):
            kd.data[i]['Ps3'] = int(line[1])
        elif (("Ps4_factor" in line[0])):
            kd.data[i]['Ps4'] = int(line[1])    
        elif (("Ps5_factor" in line[0])):
            kd.data[i]['Ps5'] = int(line[1])
        elif (("Ps6_factor" in line[0])):
            kd.data[i]['Ps6'] = int(line[1])
            
        if(spec=='hms'):    
            if("HMS X Mispointing" in line[0]):
                kd.data[i]['hms_xMisPoint'] = float(line[1].strip('cm'))
            elif("HMS Y Mispointing" in line[0]):
                kd.data[i]['hms_yMisPoint'] = float(line[1].strip('cm'))
            elif("HMS X BPM" in line[0]):
                kd.data[i]['hms_xBPM'] = float(line[1].strip('cm'))
            elif("HMS Y BPM" in line[0]):
                kd.data[i]['hms_yBPM'] = float(line[1].strip('cm'))


        elif(spec=='shms'):
            if("SHMS X Mispointing" in line[0]):
                kd.data[i]['shms_xMisPoint'] = float(line[1].strip('cm'))
            elif("SHMS Y Mispointing" in line[0]):
                kd.data[i]['shms_yMisPoint'] = float(line[1].strip('cm'))
            elif("SHMS X BPM" in line[0]):
                kd.data[i]['shms_xBPM'] = float(line[1].strip('cm'))
            elif("SHMS Y BPM" in line[0]):
                kd.data[i]['shms_yBPM'] = float(line[1].strip('cm'))

        elif(spec=='coin'):
            if("HMS X Mispointing" in line[0] and "SHMS X Mispointing" not in line[0]):
                kd.data[i]['hms_xMisPoint'] = float(line[1].strip('cm'))
            elif("HMS Y Mispointing" in line[0] and "SHMS Y Mispointing" not in line[0]):
                kd.data[i]['hms_yMisPoint'] = float(line[1].strip('cm'))
            elif("SHMS X Mispointing" in line[0]):
                kd.data[i]['shms_xMisPoint'] = float(line[1].strip('cm'))
            elif("SHMS Y Mispointing" in line[0]):
                kd.data[i]['shms_yMisPoint'] = float(line[1].strip('cm'))
            elif("HMS X BPM" in line[0] and "SHMS X BPM" not in line[0]):
                kd.data[i]['hms_xBPM'] = float(line[1].strip('cm'))
            elif("HMS Y BPM" in line[0] and "SHMS Y BPM" not in line[0]):
                kd.data[i]['hms_yBPM'] = float(line[1].strip('cm'))
            elif("SHMS X BPM" in line[0]):
                kd.data[i]['shms_xBPM'] = float(line[1].strip('cm'))
            elif("SHMS Y BPM" in line[0]):
                kd.data[i]['shms_yBPM'] = float(line[1].strip('cm'))


print('End Loop')

kd.save('%s_kin.dat' % (spec))


#Create good run lists based on singles, coincidences, or singles in coin. mode
#these are to be used by hcswif to submit jobs to ifarm

#get the pre-scale factors
 
Ps1 = B.get_data(kd, 'Ps1')
Ps2 = B.get_data(kd, 'Ps2')
Ps3 = B.get_data(kd, 'Ps3')
Ps4 = B.get_data(kd, 'Ps4')
Ps5 = B.get_data(kd, 'Ps5')
Ps6 = B.get_data(kd, 'Ps6')
if(spec=='hms'):
    hpartmass = B.get_data(kd, 'hpartmass')
if(spec=='shms'):
    ppartmass = B.get_data(kd, 'ppartmass')
if(spec=='coin'):
    hpartmass = B.get_data(kd, 'hpartmass')                                                                                                                   
    ppartmass = B.get_data(kd, 'ppartmass')

#Create output files to put good run list
if(spec=='coin'):
    fD2_Optics = open('CarbonHole_list.dat', 'w')      
    fD2_AlDummy = open('AlDummy_list.dat', 'w')     

    fD2_heepSingles = open('good_D2_heepSingles_list.dat', 'w')     
    fD2_heepCoin = open('good_D2_heepCoin_list.dat', 'w')     
    
    fD2_pm80Coin = open('good_coin_D2_pm80_list.dat', 'w')    
    fD2_pm580Coin = open('good_coin_D2_pm580_list.dat', 'w')    
    fD2_pm750Coin = open('good_coin_D2_pm750_list.dat', 'w')    
    
    fD2_pm80Singles = open('good_sing_D2_pm80_list.dat', 'w')    
    fD2_pm580Singles = open('good_sing_D2_pm580_list.dat', 'w')    
    fD2_pm750Singles = open('good_sing_D2_pm750_list.dat', 'w')    


#loop over all runs to separate them based on pre-sacle factors into singles/coincidence
for i, run in enumerate(kd['Run']):
    if(spec=='coin'):
        if(targ_mass==12.0107):
            fD2_Optics.write('%s\n'%(run))
        if(targ_mass==26.98):
            fD2_AlDummy.write('%s\n'%(run))

        if(targ_mass==1.00794 and int(Ps6[i])==-1):
            fD2_heepSingles.write('%s\n'%(run))
        if(targ_mass==1.00794 and int(Ps6[i])!=-1):
            fD2_heepCoin.write('%s\n'%(run))
   
        if(targ_mass==2.014101 and int(Ps6[i])!=-1 and hangle[i]<45):
            fD2_pm80Coin.write('%s\n'%(run))
     
        if(targ_mass==2.014101 and int(Ps6[i])!=-1 and hangle[i]>50 and hangle[i]<56):
            fD2_pm580Coin.write('%s\n'%(run))
   
        if(targ_mass==2.014101 and int(Ps6[i])!=-1 and hangle[i]>57 and hangle[i]<60):
            fD2_pm750Coin.write('%s\n'%(run))


        if(targ_mass==2.014101 and int(Ps6[i])==-1 and hangle[i]<45):
            fD2_pm80Singles.write('%s\n'%(run))
     
        if(targ_mass==2.014101 and int(Ps6[i])==-1 and hangle[i]>50 and hangle[i]<56):
            fD2_pm580Singles.write('%s\n'%(run))
   
        if(targ_mass==2.014101 and int(Ps6[i])==-1 and hangle[i]>57 and hangle[i]<60):
            fD2_pm750Singles.write('%s\n'%(run))

print('End Loop')
