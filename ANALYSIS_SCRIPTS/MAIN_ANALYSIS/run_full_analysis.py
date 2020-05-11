import os
import shutil
import glob
import subprocess as sp
import sys
from sys import argv
import numpy as np


#Extension name given for specified systematic study, for ex. Em30MeV means we put a cut on Emiss of < 30 MeV, and run the full code
#Usage: ipython run_full_analysis nominal (or Em30MeV, Em50MeV, Em60MeV, Em80MeV)

study = sys.argv[1]   
#sys_ext="all_thnq_Q2_4to5"


def main():
    print('Entering Main . . .')

    #Emiss Systematic Study
    if(study=="Em"):
        cut_arr = np.array([30, 40, 50, 60, 70, 80])  #Missing Energy in MeV
    #Ztar Difference Systematic Study
    if(study=="Ztar"):
        cut_arr = np.array([3.0, 2.5])
    #HMS Collimator Systematic Study
    if(study=="hColl"):
        cut_arr = np.array([1.0, 1.1])
    #Coincidence Time Systematic Study
    if(study=="ctime"):
        cut_arr = np.array([0, 1])  #ON / OFF
    #SHMS Cal Cut Systematic Study
    if(study=="shmsCal"):
        cut_arr = np.array([0, 1])  #ON / OFF

    for i in range(len(cut_arr)):

        if(study=="Em"):
            cut_value = cut_arr[i] / 1000.   #convert to GeV
            sys_ext = study+"_%sMeV"%(cut_arr[i])  #descriptive name of systematic study
            #sys_ext = study  #descriptive name of systematic study
        if(study=="Ztar"):
            cut_value = cut_arr[i]
            sys_ext = study+"%scm"%(cut_arr[i])  #descriptive name of systematic study
        if(study=="hColl"):
            cut_value = cut_arr[i]
            sys_ext = study+"%s"%(cut_arr[i])  #descriptive name of systematic study
        if(study=="ctime"):
            cut_value = cut_arr[i]
            if(cut_arr[i]==1):
                sys_ext = study+"ON"  #descriptive name of systematic study
            if(cut_arr[i]==0):
                sys_ext = study+"OFF"
        if(study=="shmsCal"):
            cut_value = cut_arr[i]
            if(cut_arr[i]==1):
                sys_ext = study+"ON"  #descriptive name of systematic study
            if(cut_arr[i]==0):
                sys_ext = study+"OFF"

        print('Analyzing '+sys_ext+'\n')
        print('cut_value=',cut_value)

        
        
        #Analyze Calibrated ROOTfiles to get Charge Norm. Corrected Yield
        analyze_ROOTfiles('pwia', 80, 1, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 80, 1, sys_ext, study, cut_value)        
        
        analyze_ROOTfiles('pwia', 580, 1, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 580, 1, sys_ext, study, cut_value)
        
        analyze_ROOTfiles('pwia', 580, 2, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 580, 2, sys_ext, study, cut_value)
        
        analyze_ROOTfiles('pwia', 750, 1, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 750, 1, sys_ext, study, cut_value)
        
        analyze_ROOTfiles('pwia', 750, 2, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 750, 2, sys_ext, study, cut_value)
        
        analyze_ROOTfiles('pwia', 750, 3, sys_ext, study, cut_value)
        analyze_ROOTfiles('fsi', 750, 3, sys_ext, study, cut_value)
        
        
        #Assumes all ROOTfiles with Histos Objects have been created
        calc_all_Xsec(sys_ext)
        
    print('Done')
        
def analyze_ROOTfiles(model='', pm_set=0, data_set=0, sys_ext='', study='', cut_value=0):

    #Input: model='fsi' or 'pwia',  pm_set=80, 580, 750,  data_set=1,2,3
    #the sys_ext: any chosen name for the specific systematic study, for example, 'nominal'
    #or 'Em_0.40'

    #Make sure the current directory does not have *.root or report_* files before running
    
    #------------PART1: GENERATE ROOT FILES------------

    #Change to relevant directory (full path)                                                                                                                 
    dir_name="/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/"  
    os.chdir(dir_name) 

    #print('Calling ',model,' ',pm_set,' ',data_set,' ',cut_value)
    #Generate Input File for D(e,e'p)
    #os.system("python gen_inp.py %s %i %i" % (model, pm_set, data_set))
    gen_inp(model, pm_set, data_set, study, cut_value)

    #Run main_analysis script ( the 2 means to use set_deep_cuts.inp )
    os.system("root -l -q -b \"main_analysis.C(2)\"")

    #declare directory name to store ALL root_files and report_files
    dir_name="./root_files/pm%i_%sXsec_set%i_%s" % (pm_set, model, data_set, sys_ext)

    #declare directory name to store average kin. root_files
    dir_name_kin="./root_files/average_kinematics/%s" % (sys_ext)


    #check if directory exists, else creates it.
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)
   
    #check if kin. avg directory exists, else creates it.
    if not os.path.exists(dir_name_kin):
        os.makedirs(dir_name_kin)

    #copy SIMC *norad* to avg. kin dir (for calculation of avg. kin. later on)
    os.system("cp deep_simc_*norad*.root "+dir_name_kin)

    #move ouput root_file, report and input_cut file to relevant directory
    os.system("mv *.root report_deep* set_deep* "+dir_name)


def calc_all_Xsec(sys_ext=''):

    #----------PART2: CALCULATE AVERAGE KINEMATICS-------------
    
    #Change to relevant directory (full path)
    dir_name="/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/Deep_CrossSections/average_kinematics/"
    os.chdir(dir_name)

    #80 MeV
    os.system("python calc_avg_kin.py 80 pwia 1 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 80 fsi 1 %s"%(sys_ext))
    
    
    #580 MeV
    os.system("python calc_avg_kin.py 580 pwia 1 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 580 fsi 1 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 580 pwia 2 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 580 fsi 2 %s"%(sys_ext))
    #750 MeV
    os.system("python calc_avg_kin.py 750 pwia 1 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 750 fsi 1 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 750 pwia 2 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 750 fsi 2 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 750 pwia 3 %s"%(sys_ext))
    os.system("python calc_avg_kin.py 750 fsi 3 %s"%(sys_ext))
    
    
    #----------PART3: EXTRACT THEORY XSEC FROM AVERAGE KINEMATICS-------------
    dir_name="../theory_Xsec/"
    os.chdir(dir_name)

    #80 MeV
    os.system("ipython calc_theory_Xsec.py 80 1 %s"%(sys_ext))
    
    #580 MeV
    os.system("ipython calc_theory_Xsec.py 580 1 %s"%(sys_ext))
    os.system("ipython calc_theory_Xsec.py 580 2 %s"%(sys_ext))
    #750 MeV
    os.system("ipython calc_theory_Xsec.py 750 1 %s"%(sys_ext))
    os.system("ipython calc_theory_Xsec.py 750 2 %s"%(sys_ext))
    os.system("ipython calc_theory_Xsec.py 750 3 %s"%(sys_ext))
    

    #----------PART4: EXTRACT AVERAGE DATA/MODEL XSEC FROM SIMC -------------
    dir_name="../average_Xsec/"
    os.chdir(dir_name)
     
    #80 MeV
    os.system("python calc_Xsec.py 80 1 %s"%(sys_ext))
    
    #580 MeV
    os.system("python calc_Xsec.py 580 1 %s"%(sys_ext))
    os.system("python calc_Xsec.py 580 2 %s"%(sys_ext))
    #750 MeV
    os.system("python calc_Xsec.py 750 1 %s"%(sys_ext))
    os.system("python calc_Xsec.py 750 2 %s"%(sys_ext))
    os.system("python calc_Xsec.py 750 3 %s"%(sys_ext))
    

    #----------PART5: APPLY BIN-CENTERING CORRECTIONS -------------
    #This part produces a file with all the Xsec and red. Xsec for all kinematics/sets

    dir_name="../bin_centering_corrections/"
    os.chdir(dir_name)
    
    #80 MeV
    os.system("ipython calc_bc_corr.py 80 1 %s"%(sys_ext))
    
    #580 MeV
    os.system("ipython calc_bc_corr.py 580 1 %s"%(sys_ext))
    os.system("ipython calc_bc_corr.py 580 2 %s"%(sys_ext))
    #750 MeV
    os.system("ipython calc_bc_corr.py 750 1 %s"%(sys_ext))
    os.system("ipython calc_bc_corr.py 750 2 %s"%(sys_ext))
    os.system("ipython calc_bc_corr.py 750 3 %s"%(sys_ext))
    
    '''
    #----------PART6: COMBINE Red. Xsec -------------
    #Combine reduced cross sections from all kin. / sets (NOT Cross Sections)
    
    
    dir_name="../combine_data/"
    os.chdir(dir_name)
    
    os.system("python combine_data.py %s"%(sys_ext))  #produces a .txt files with all the combined Xsec from theory and data
    os.system("python make_plot.py %s"%(sys_ext))
    
    
    #-------PART6: CALCULATE SYSTEMATICS EFFECTS (assumes nominal cuts Xsec already exits)---------
    dir_name="/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/SYSTEMATICS_STUDIES/scripts/kin_systematics"
    os.chdir(dir_name)

    os.system("ipython run_differ_general_v2.py 80 fsi 1 %s"%(sys_ext))
    os.system("ipython run_differ_general_v2.py 580 fsi 1 %s"%(sys_ext))
    os.system("ipython run_differ_general_v2.py 580 fsi 2 %s"%(sys_ext))
    os.system("ipython run_differ_general_v2.py 750 fsi 1 %s"%(sys_ext))
    os.system("ipython run_differ_general_v2.py 750 fsi 2 %s"%(sys_ext))
    os.system("ipython run_differ_general_v2.py 750 fsi 3 %s"%(sys_ext))
    
    #----------PART7: COMBINE Red. Xsec ------------- 
    #Combine reduced cross sections from all kin. / sets (NOT Cross Sections) 
    dir_name="/u/group/E12-10-003/cyero/hallc_replay/DEUTERON_ANALYSIS/ANALYSIS_SCRIPTS/MAIN_ANALYSIS/Deep_CrossSections/combine_data"
    os.chdir(dir_name)
    os.system("ipython combine_data.py %s"%(sys_ext))
    '''

def gen_inp(model='', pm_set=0, data_set=0, study='', cut_value=0):
    
    if(study=="Em"):

        #Generate the D(e,e'p)n Input File Based on User Input 
        f = open('set_deep_cuts.inp', 'w')                               
        f.write('#-------Single Run Analysis---------                                                                          \n')                                          
        f.write(';Use this option if you only want to look at a single file in data/simc                                       \n')
        f.write('single_run_flag: 0                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Specify filenames                                                                                            \n')
        f.write('data_fname: ROOTfiles/pm580_set1.root                                                                         \n')
        f.write('data_report_fname: REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_deep_check_3291_-1.report                        \n')
        f.write('simc_fname: worksim_voli/d2_pm580_lagetfsi_rad_set1.root                                                      \n')
        f.write('                                                                                                              \n')
        f.write('#--------Analyze DATA or SIMC-------                                                                          \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write('RUN_SIMC: 1                                                                                                   \n')
        f.write('RUN_DATA: 1                                                                                                   \n')
        f.write('RUN_PSEUDO: 0                                                                                                 \n')
        f.write(';Analyze Radiative(1) or NonRadiative(0) SIMC?                                                                \n')
        f.write(';IMPORTANT: If doing radiative corrections, set to -1                                                         \n')
        f.write('radiate: -1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Do Radiative Corrections (1) (Will analyze both rad/no-rad simc. Also, assumes data file exists)             \n')
        f.write(';IMPORTANT: If doing radiative corrections, set radiate: -1 (see above)                                       \n')
        f.write('rad_corr_flag: 1                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------ D(e,e''p)n Missing Momentum Settings -------                                                          \n')
        f.write('#Units: Enegy/Momentum/W [GeV], spec_delta [%]                                                                \n')
        f.write('                                                                                                              \n')
        f.write(';80 MeV, 580 MeV, 750 MeV                                                                                     \n')
        f.write('pm_setting : %d                                                                                               \n'%(pm_set))
        f.write('                                                                                                              \n')
        f.write(';Theoretical Calculation: laget,  misak, . . .                                                                \n')
        f.write('theory     : laget                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Theoretical Model: pwia, fsi                                                                                 \n')
        f.write('model      : %s                                                                                               \n'%(model))
        f.write('                                                                                                              \n')
        f.write(';DataSet 1, 2, 3                                                                                              \n')
        f.write('data_set   : %d                                                                                               \n'%(data_set))
        f.write('                                                                                                              \n')
        f.write('#------TURN CUTS ON/OFF------                                                                                 \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Basic Kinematics Cuts                                                                                        \n')
        f.write('bool Em      = 1                                                                                              \n')
        f.write('bool W       = 0                                                                                              \n')
        f.write('bool h_delta = 1                                                                                              \n')
        f.write('bool e_delta = 1                                                                                              \n')
        f.write('bool ztar_diff = 1                                                                                            \n')
        f.write('bool Q2 = 1                                                                                                   \n')
        f.write('bool th_nq = 0                                                                                                \n')
        f.write('bool MM = 0                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';PID Cuts                                                                                                     \n')
        f.write('bool shmsCal_EtotTrackNorm  = 1                                                                               \n')
        f.write('bool coin_time              = 1                                                                               \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts                                                                                              \n')
        f.write('bool hmsCollCut   =  1                                                                                        \n')
        f.write('bool shmsCollCut  =  0                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts Scale                                                                                        \n')
        f.write('hms_scale         =  1                                                                                        \n')
        f.write('shms_scale        =  1                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------Set DATA/SIMC CUTS LIMITS ------                                                                       \n')
        f.write('Em_min: -0.02                                                                                                \n')  
        f.write('Em_max: %f                                                                                                   \n'%(cut_value))  
        f.write('                                                                                                              \n')
        f.write('h_delta_min: -8.                                                                                              \n')
        f.write('h_delta_max:  8.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('e_delta_min: -10                                                                                              \n')
        f.write('e_delta_max: 22                                                                                               \n')
        f.write('                                                                                                              \n')
        f.write('W_min: 0.85                                                                                                   \n')
        f.write('W_max: 1.05                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write('ztarDiff_min: -2.                                                                                             \n')
        f.write('ztarDiff_max: 2.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('Q2_min: 4.                                                                                                    \n')
        f.write('Q2_max: 5.                                                                                                    \n')
        f.write('                                                                                                              \n')
        f.write('thnq_min: 70.                                                                                                 \n')
        f.write('thnq_max: 80.                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write('MM_min: 0.9                                                                                                   \n')
        f.write('MM_max: 0.985                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write(';SHMS Cal EtotTrackNorm Cut                                                                                   \n')
        f.write('shms_cal_min: 0.7                                                                                             \n')
        f.write('shms_cal_max: 5.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('coin_time_min: 10.5                                                                                           \n')
        f.write('coin_time_max: 14.5                                                                                           \n')
        f.write('                                                                                                              \n')
        f.close()

    if(study=="Ztar"):

        #Generate the D(e,e'p)n Input File Based on User Input 
        f = open('set_deep_cuts.inp', 'w')                               
        f.write('#-------Single Run Analysis---------                                                                          \n')                                          
        f.write(';Use this option if you only want to look at a single file in data/simc                                       \n')
        f.write('single_run_flag: 0                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Specify filenames                                                                                            \n')
        f.write('data_fname: ROOTfiles/pm580_set1.root                                                                         \n')
        f.write('data_report_fname: REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_deep_check_3291_-1.report                        \n')
        f.write('simc_fname: worksim_voli/d2_pm580_lagetfsi_rad_set1.root                                                      \n')
        f.write('                                                                                                              \n')
        f.write('#--------Analyze DATA or SIMC-------                                                                          \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write('RUN_SIMC: 1                                                                                                   \n')
        f.write('RUN_DATA: 1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Analyze Radiative(1) or NonRadiative(0) SIMC?                                                                \n')
        f.write(';IMPORTANT: If doing radiative corrections, set to -1                                                         \n')
        f.write('radiate: -1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Do Radiative Corrections (1) (Will analyze both rad/no-rad simc. Also, assumes data file exists)             \n')
        f.write(';IMPORTANT: If doing radiative corrections, set radiate: -1 (see above)                                       \n')
        f.write('rad_corr_flag: 1                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------ D(e,e''p)n Missing Momentum Settings -------                                                          \n')
        f.write('#Units: Enegy/Momentum/W [GeV], spec_delta [%]                                                                \n')
        f.write('                                                                                                              \n')
        f.write(';80 MeV, 580 MeV, 750 MeV                                                                                     \n')
        f.write('pm_setting : %d                                                                                               \n'%(pm_set))
        f.write('                                                                                                              \n')
        f.write(';Theoretical Calculation: laget,  misak, . . .                                                                \n')
        f.write('theory     : laget                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Theoretical Model: pwia, fsi                                                                                 \n')
        f.write('model      : %s                                                                                               \n'%(model))
        f.write('                                                                                                              \n')
        f.write(';DataSet 1, 2, 3                                                                                              \n')
        f.write('data_set   : %d                                                                                               \n'%(data_set))
        f.write('                                                                                                              \n')
        f.write('#------TURN CUTS ON/OFF------                                                                                 \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Basic Kinematics Cuts                                                                                        \n')
        f.write('bool Em      = 1                                                                                              \n')
        f.write('bool W       = 0                                                                                              \n')
        f.write('bool h_delta = 1                                                                                              \n')
        f.write('bool e_delta = 1                                                                                              \n')
        f.write('bool ztar_diff = 1                                                                                            \n')
        f.write('bool Q2 = 1                                                                                                   \n')
        f.write('bool th_nq = 1                                                                                                \n')
        f.write('bool MM = 0                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';PID Cuts                                                                                                     \n')
        f.write('bool shmsCal_EtotTrackNorm  = 1                                                                               \n')
        f.write('bool coin_time              = 1                                                                               \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts                                                                                              \n')
        f.write('bool hmsCollCut   =  1                                                                                        \n')
        f.write('bool shmsCollCut  =  0                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts Scale                                                                                        \n')
        f.write('hms_scale         =  1                                                                                        \n')
        f.write('shms_scale        =  1                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------Set DATA/SIMC CUTS LIMITS ------                                                                       \n')
        f.write('Em_min : -0.02                                                                                                \n')  
        f.write('Em_max : 0.04                                                                                                 \n')  
        f.write('                                                                                                              \n')
        f.write('h_delta_min: -8.                                                                                              \n')
        f.write('h_delta_max:  8.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('e_delta_min: -10                                                                                              \n')
        f.write('e_delta_max: 22                                                                                               \n')
        f.write('                                                                                                              \n')
        f.write('W_min: 0.85                                                                                                   \n')
        f.write('W_max: 1.05                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write('ztarDiff_min: -%f                                                                                             \n'%(cut_value))
        f.write('ztarDiff_max:  %f                                                                                             \n'%(cut_value))
        f.write('                                                                                                              \n')
        f.write('Q2_min: 4.                                                                                                    \n')
        f.write('Q2_max: 5.                                                                                                    \n')
        f.write('                                                                                                              \n')
        f.write('thnq_min: 35.                                                                                                 \n')
        f.write('thnq_max: 45.                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write('MM_min: 0.9                                                                                                   \n')
        f.write('MM_max: 0.985                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write(';SHMS Cal EtotTrackNorm Cut                                                                                   \n')
        f.write('shms_cal_min: 0.7                                                                                             \n')
        f.write('shms_cal_max: 5.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('coin_time_min: 10.5                                                                                           \n')
        f.write('coin_time_max: 14.5                                                                                           \n')
        f.write('                                                                                                              \n')
        f.close()

    if(study=="hColl"):

        #Generate the D(e,e'p)n Input File Based on User Input 
        f = open('set_deep_cuts.inp', 'w')                               
        f.write('#-------Single Run Analysis---------                                                                          \n')                                          
        f.write(';Use this option if you only want to look at a single file in data/simc                                       \n')
        f.write('single_run_flag: 0                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Specify filenames                                                                                            \n')
        f.write('data_fname: ROOTfiles/pm580_set1.root                                                                         \n')
        f.write('data_report_fname: REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_deep_check_3291_-1.report                        \n')
        f.write('simc_fname: worksim_voli/d2_pm580_lagetfsi_rad_set1.root                                                      \n')
        f.write('                                                                                                              \n')
        f.write('#--------Analyze DATA or SIMC-------                                                                          \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write('RUN_SIMC: 1                                                                                                   \n')
        f.write('RUN_DATA: 1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Analyze Radiative(1) or NonRadiative(0) SIMC?                                                                \n')
        f.write(';IMPORTANT: If doing radiative corrections, set to -1                                                         \n')
        f.write('radiate: -1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Do Radiative Corrections (1) (Will analyze both rad/no-rad simc. Also, assumes data file exists)             \n')
        f.write(';IMPORTANT: If doing radiative corrections, set radiate: -1 (see above)                                       \n')
        f.write('rad_corr_flag: 1                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------ D(e,e''p)n Missing Momentum Settings -------                                                          \n')
        f.write('#Units: Enegy/Momentum/W [GeV], spec_delta [%]                                                                \n')
        f.write('                                                                                                              \n')
        f.write(';80 MeV, 580 MeV, 750 MeV                                                                                     \n')
        f.write('pm_setting : %d                                                                                               \n'%(pm_set))
        f.write('                                                                                                              \n')
        f.write(';Theoretical Calculation: laget,  misak, . . .                                                                \n')
        f.write('theory     : laget                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Theoretical Model: pwia, fsi                                                                                 \n')
        f.write('model      : %s                                                                                               \n'%(model))
        f.write('                                                                                                              \n')
        f.write(';DataSet 1, 2, 3                                                                                              \n')
        f.write('data_set   : %d                                                                                               \n'%(data_set))
        f.write('                                                                                                              \n')
        f.write('#------TURN CUTS ON/OFF------                                                                                 \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Basic Kinematics Cuts                                                                                        \n')
        f.write('bool Em      = 1                                                                                              \n')
        f.write('bool W       = 0                                                                                              \n')
        f.write('bool h_delta = 1                                                                                              \n')
        f.write('bool e_delta = 1                                                                                              \n')
        f.write('bool ztar_diff = 1                                                                                            \n')
        f.write('bool Q2 = 1                                                                                                   \n')
        f.write('bool th_nq = 1                                                                                                \n')
        f.write('bool MM = 0                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';PID Cuts                                                                                                     \n')
        f.write('bool shmsCal_EtotTrackNorm  = 1                                                                               \n')
        f.write('bool coin_time              = 1                                                                               \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts                                                                                              \n')
        f.write('bool hmsCollCut   =  1                                                                                        \n')
        f.write('bool shmsCollCut  =  0                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts Scale                                                                                        \n')
        f.write('hms_scale         =  %s                                                                                        \n'%(cut_value))
        f.write('shms_scale        =  1                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------Set DATA/SIMC CUTS LIMITS ------                                                                       \n')
        f.write('Em_min : -0.02                                                                                                \n')  
        f.write('Em_max : 0.04                                                                                                 \n')  
        f.write('                                                                                                              \n')
        f.write('h_delta_min: -8.                                                                                              \n')
        f.write('h_delta_max:  8.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('e_delta_min: -10                                                                                              \n')
        f.write('e_delta_max: 22                                                                                               \n')
        f.write('                                                                                                              \n')
        f.write('W_min: 0.85                                                                                                   \n')
        f.write('W_max: 1.05                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write('ztarDiff_min: -2.                                                                                             \n')
        f.write('ztarDiff_max: 2.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('Q2_min: 4.                                                                                                    \n')
        f.write('Q2_max: 5.                                                                                                    \n')
        f.write('                                                                                                              \n')
        f.write('thnq_min: 35.                                                                                                 \n')
        f.write('thnq_max: 45.                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write('MM_min: 0.9                                                                                                   \n')
        f.write('MM_max: 0.985                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write(';SHMS Cal EtotTrackNorm Cut                                                                                   \n')
        f.write('shms_cal_min: 0.7                                                                                             \n')
        f.write('shms_cal_max: 5.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('coin_time_min: 10.5                                                                                           \n')
        f.write('coin_time_max: 14.5                                                                                           \n')
        f.write('                                                                                                              \n')
        f.close()

    if(study=="ctime"):

        #Generate the D(e,e'p)n Input File Based on User Input 
        f = open('set_deep_cuts.inp', 'w')                               
        f.write('#-------Single Run Analysis---------                                                                          \n')                                          
        f.write(';Use this option if you only want to look at a single file in data/simc                                       \n')
        f.write('single_run_flag: 0                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Specify filenames                                                                                            \n')
        f.write('data_fname: ROOTfiles/pm580_set1.root                                                                         \n')
        f.write('data_report_fname: REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_deep_check_3291_-1.report                        \n')
        f.write('simc_fname: worksim_voli/d2_pm580_lagetfsi_rad_set1.root                                                      \n')
        f.write('                                                                                                              \n')
        f.write('#--------Analyze DATA or SIMC-------                                                                          \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write('RUN_SIMC: 1                                                                                                   \n')
        f.write('RUN_DATA: 1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Analyze Radiative(1) or NonRadiative(0) SIMC?                                                                \n')
        f.write(';IMPORTANT: If doing radiative corrections, set to -1                                                         \n')
        f.write('radiate: -1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Do Radiative Corrections (1) (Will analyze both rad/no-rad simc. Also, assumes data file exists)             \n')
        f.write(';IMPORTANT: If doing radiative corrections, set radiate: -1 (see above)                                       \n')
        f.write('rad_corr_flag: 1                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------ D(e,e''p)n Missing Momentum Settings -------                                                          \n')
        f.write('#Units: Enegy/Momentum/W [GeV], spec_delta [%]                                                                \n')
        f.write('                                                                                                              \n')
        f.write(';80 MeV, 580 MeV, 750 MeV                                                                                     \n')
        f.write('pm_setting : %d                                                                                               \n'%(pm_set))
        f.write('                                                                                                              \n')
        f.write(';Theoretical Calculation: laget,  misak, . . .                                                                \n')
        f.write('theory     : laget                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Theoretical Model: pwia, fsi                                                                                 \n')
        f.write('model      : %s                                                                                               \n'%(model))
        f.write('                                                                                                              \n')
        f.write(';DataSet 1, 2, 3                                                                                              \n')
        f.write('data_set   : %d                                                                                               \n'%(data_set))
        f.write('                                                                                                              \n')
        f.write('#------TURN CUTS ON/OFF------                                                                                 \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Basic Kinematics Cuts                                                                                        \n')
        f.write('bool Em      = 1                                                                                              \n')
        f.write('bool W       = 0                                                                                              \n')
        f.write('bool h_delta = 1                                                                                              \n')
        f.write('bool e_delta = 1                                                                                              \n')
        f.write('bool ztar_diff = 1                                                                                            \n')
        f.write('bool Q2 = 1                                                                                                   \n')
        f.write('bool th_nq = 1                                                                                                \n')
        f.write('bool MM = 0                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';PID Cuts                                                                                                     \n')
        f.write('bool shmsCal_EtotTrackNorm  = 1                                                                               \n')
        f.write('bool coin_time              = %s                                                                              \n'%(cut_value))
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts                                                                                              \n')
        f.write('bool hmsCollCut   =  1                                                                                        \n')
        f.write('bool shmsCollCut  =  0                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts Scale                                                                                        \n')
        f.write('hms_scale         =  1                                                                                        \n')
        f.write('shms_scale        =  1                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------Set DATA/SIMC CUTS LIMITS ------                                                                       \n')
        f.write('Em_min : -0.02                                                                                                \n')  
        f.write('Em_max : 0.04                                                                                                 \n')  
        f.write('                                                                                                              \n')
        f.write('h_delta_min: -8.                                                                                              \n')
        f.write('h_delta_max:  8.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('e_delta_min: -10                                                                                              \n')
        f.write('e_delta_max: 22                                                                                               \n')
        f.write('                                                                                                              \n')
        f.write('W_min: 0.85                                                                                                   \n')
        f.write('W_max: 1.05                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write('ztarDiff_min: -2.                                                                                             \n')
        f.write('ztarDiff_max: 2.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('Q2_min: 4.                                                                                                    \n')
        f.write('Q2_max: 5.                                                                                                    \n')
        f.write('                                                                                                              \n')
        f.write('thnq_min: 35.                                                                                                 \n')
        f.write('thnq_max: 45.                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write('MM_min: 0.9                                                                                                   \n')
        f.write('MM_max: 0.985                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write(';SHMS Cal EtotTrackNorm Cut                                                                                   \n')
        f.write('shms_cal_min: 0.7                                                                                             \n')
        f.write('shms_cal_max: 5.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('coin_time_min: 10.5                                                                                           \n')
        f.write('coin_time_max: 14.5                                                                                           \n')
        f.write('                                                                                                              \n')
        f.close()

    if(study=="shmsCal"):

        #Generate the D(e,e'p)n Input File Based on User Input 
        f = open('set_deep_cuts.inp', 'w')                               
        f.write('#-------Single Run Analysis---------                                                                          \n')                                          
        f.write(';Use this option if you only want to look at a single file in data/simc                                       \n')
        f.write('single_run_flag: 0                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Specify filenames                                                                                            \n')
        f.write('data_fname: ROOTfiles/pm580_set1.root                                                                         \n')
        f.write('data_report_fname: REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_deep_check_3291_-1.report                        \n')
        f.write('simc_fname: worksim_voli/d2_pm580_lagetfsi_rad_set1.root                                                      \n')
        f.write('                                                                                                              \n')
        f.write('#--------Analyze DATA or SIMC-------                                                                          \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write('RUN_SIMC: 1                                                                                                   \n')
        f.write('RUN_DATA: 1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Analyze Radiative(1) or NonRadiative(0) SIMC?                                                                \n')
        f.write(';IMPORTANT: If doing radiative corrections, set to -1                                                         \n')
        f.write('radiate: -1                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';Do Radiative Corrections (1) (Will analyze both rad/no-rad simc. Also, assumes data file exists)             \n')
        f.write(';IMPORTANT: If doing radiative corrections, set radiate: -1 (see above)                                       \n')
        f.write('rad_corr_flag: 1                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------ D(e,e''p)n Missing Momentum Settings -------                                                          \n')
        f.write('#Units: Enegy/Momentum/W [GeV], spec_delta [%]                                                                \n')
        f.write('                                                                                                              \n')
        f.write(';80 MeV, 580 MeV, 750 MeV                                                                                     \n')
        f.write('pm_setting : %d                                                                                               \n'%(pm_set))
        f.write('                                                                                                              \n')
        f.write(';Theoretical Calculation: laget,  misak, . . .                                                                \n')
        f.write('theory     : laget                                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Theoretical Model: pwia, fsi                                                                                 \n')
        f.write('model      : %s                                                                                               \n'%(model))
        f.write('                                                                                                              \n')
        f.write(';DataSet 1, 2, 3                                                                                              \n')
        f.write('data_set   : %d                                                                                               \n'%(data_set))
        f.write('                                                                                                              \n')
        f.write('#------TURN CUTS ON/OFF------                                                                                 \n')
        f.write('# True (ON) =  1,  False (OFF) = 0                                                                            \n')
        f.write('                                                                                                              \n')
        f.write(';Basic Kinematics Cuts                                                                                        \n')
        f.write('bool Em      = 1                                                                                              \n')
        f.write('bool W       = 0                                                                                              \n')
        f.write('bool h_delta = 1                                                                                              \n')
        f.write('bool e_delta = 1                                                                                              \n')
        f.write('bool ztar_diff = 1                                                                                            \n')
        f.write('bool Q2 = 1                                                                                                   \n')
        f.write('bool th_nq = 1                                                                                                \n')
        f.write('bool MM = 0                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write(';PID Cuts                                                                                                     \n')
        f.write('bool shmsCal_EtotTrackNorm  = %s                                                                              \n'%(cut_value))
        f.write('bool coin_time              = 1                                                                               \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts                                                                                              \n')
        f.write('bool hmsCollCut   =  1                                                                                        \n')
        f.write('bool shmsCollCut  =  0                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write(';Collimator Cuts Scale                                                                                        \n')
        f.write('hms_scale         =  1                                                                                        \n')
        f.write('shms_scale        =  1                                                                                        \n')
        f.write('                                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('#------Set DATA/SIMC CUTS LIMITS ------                                                                       \n')
        f.write('Em_min : -0.02                                                                                                \n')  
        f.write('Em_max : 0.04                                                                                                 \n')  
        f.write('                                                                                                              \n')
        f.write('h_delta_min: -8.                                                                                              \n')
        f.write('h_delta_max:  8.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('e_delta_min: -10                                                                                              \n')
        f.write('e_delta_max: 22                                                                                               \n')
        f.write('                                                                                                              \n')
        f.write('W_min: 0.85                                                                                                   \n')
        f.write('W_max: 1.05                                                                                                   \n')
        f.write('                                                                                                              \n')
        f.write('ztarDiff_min: -2.                                                                                             \n')
        f.write('ztarDiff_max: 2.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('Q2_min: 4.                                                                                                    \n')
        f.write('Q2_max: 5.                                                                                                    \n')
        f.write('                                                                                                              \n')
        f.write('thnq_min: 35.                                                                                                 \n')
        f.write('thnq_max: 45.                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write('MM_min: 0.9                                                                                                   \n')
        f.write('MM_max: 0.985                                                                                                 \n')
        f.write('                                                                                                              \n')
        f.write(';SHMS Cal EtotTrackNorm Cut                                                                                   \n')
        f.write('shms_cal_min: 0.7                                                                                             \n')
        f.write('shms_cal_max: 5.                                                                                              \n')
        f.write('                                                                                                              \n')
        f.write('coin_time_min: 10.5                                                                                           \n')
        f.write('coin_time_max: 14.5                                                                                           \n')
        f.write('                                                                                                              \n')
        f.close()

if __name__=="__main__":
    main()

