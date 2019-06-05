#include<iostream>
#include "analyze.h"

using namespace std;

//_______________________________________________________________________
analyze::analyze(int run=-1, string e_arm="SHMS", string type="data", string react="heep") 
  : runNUM(run),       
    e_arm_name(e_arm),    //electron arm: "HMS" or "SHMS" 
    analysis(type),       //analysis type: "data" or "simc"
    reaction(react)       //reaction type: "heep" or "deep"
{
  
  cout << "Calling Constructor . . . " << endl;
  cout << "  " << endl;

  //Set Spectrometer Prefix later use
  if(e_arm=="SHMS"){
    h_arm_name = "HMS";
    eArm = "P";
    hArm = "H";
  }
  else if(e_arm=="HMS"){
    h_arm_name = "SHMS";
    eArm = "H";
    hArm = "P";
  }
  
  //Initialize TFile Pointers
  inROOT = NULL;
  outROOT = NULL;
  
  //Initialize TTree Pointers
  tree = NULL;
  scaler_tree = NULL;

  //Initialize Scaler Pointer
  evt_flag_bcm = NULL;   //scaler read array of 0 or 1 (determine if scaler read passed bcm cut)
  scal_evt_num = NULL;

  //Initialize Graphical Cuts (Collimator Study)
  hms_Coll_gCut = NULL;
  shms_Coll_gCut = NULL;

  //Initialize DATA (ONLY) Histograms

  //Trigger Detector
  H_ctime = NULL;

  //HMS Detectors
  H_hbeta = NULL;
  H_hcer = NULL;
  H_hcal = NULL;

  //SHMS Detectors
  H_pbeta = NULL;
  H_pngcer = NULL;
  H_pcal_etotnorm = NULL;
  H_pcal_etotTrkNorm = NULL;

  //Initialize DATA/SIMC Histograms
  
  //Primary (electron) Kinematics
  H_Q2 = NULL;
  H_omega = NULL;
  H_W = NULL;
  H_W2 = NULL;
  H_xbj = NULL;
  H_kf = NULL;
  H_theta_q = NULL;
  H_q = NULL;
  H_theta_elec = NULL;

  //Secondary (Hadron) Kinematics
  H_Em = NULL;
  H_Em_nuc = NULL;
  H_Pm = NULL;
  H_Pmx_lab = NULL;
  H_Pmy_lab = NULL;
  H_Pmz_lab = NULL;
  H_Pmx_q = NULL;
  H_Pmy_q = NULL;
  H_Pmz_q = NULL;
  H_MM = NULL;
  H_MM2 = NULL;
  H_Pf = NULL;
  H_Ep = NULL;
  H_En = NULL;
  H_Kp = NULL;
  H_Kn = NULL;
  H_theta_prot = NULL;
  H_theta_pq = NULL;
  H_theta_nq = NULL;

  //Target Reconstruction Histos
  H_hx_tar = NULL;
  H_hy_tar = NULL;
  H_hz_tar = NULL;

  H_ex_tar = NULL;
  H_ey_tar = NULL;
  H_ez_tar = NULL;

  H_ztar_diff = NULL;

  //Hadron Arm Recon. / Focal Plane Histos
  H_hytar = NULL;
  H_hxptar = NULL;
  H_hyptar = NULL;
  H_hdelta = NULL;

  H_hxfp = NULL;
  H_hyfp = NULL;
  H_hxpfp = NULL;
  H_hypfp = NULL;
  
  //Electron Arm Recon. / Focal Plane Histos
  H_eytar = NULL;
  H_exptar = NULL;
  H_eyptar = NULL;
  H_edelta = NULL;

  H_exfp = NULL;
  H_eyfp = NULL;
  H_expfp = NULL;
  H_eypfp = NULL;

  //HMS/SHMS Collimator
  H_hXColl = NULL;
  H_hYColl = NULL;
  H_eXColl = NULL;
  H_eYColl = NULL;

  //2D Collimator Histos
  H_hXColl_vs_hYColl = NULL;
  H_eXColl_vs_eYColl = NULL;

  H_Em_vs_Pm = NULL;
  H_Em_nuc_vs_Pm = NULL;

  //Initialize Scaler Histograms
  H_bcmCurrent = NULL;
  
}

//____________________________________________
analyze::~analyze()
{
  //Destructor
  
  cout << "Calling Destructor  . . . " << endl;
  
  
  //Delete FileName Pointers
  delete inROOT; inROOT = NULL;
  delete outROOT; outROOT = NULL;
  
  //Delete Scaler related event flag
  delete [] evt_flag_bcm; evt_flag_bcm = NULL;
  delete [] scal_evt_num; scal_evt_num = NULL;
  
  //Delete DATA/SIMC Histograms

  //Trigger Detector
  delete H_ctime; H_ctime= NULL;

  //HMS Detectors
  delete H_hbeta; H_hbeta = NULL;
  delete H_hcer;  H_hcer  = NULL;
  delete H_hcal;  H_hcal  = NULL;

  //SHMS Detectors
  delete H_pbeta;  H_pbeta  = NULL;
  delete H_pngcer; H_pngcer = NULL;
  delete H_pcal_etotnorm;   H_pcal_etotnorm   = NULL;
  delete H_pcal_etotTrkNorm;   H_pcal_etotTrkNorm   = NULL;

  //Initialize DATA/SIMC Histograms
  
  //Primary (electron) Kinematics
  delete H_Q2;         H_Q2         = NULL;
  delete H_omega;      H_omega      = NULL;
  delete H_W;          H_W          = NULL;
  delete H_W2;         H_W2         = NULL;
  delete H_xbj;        H_xbj        = NULL;
  delete H_kf;         H_kf         = NULL;
  delete H_theta_q;    H_theta_q    = NULL;
  delete H_q;          H_q          = NULL;
  delete H_theta_elec; H_theta_elec = NULL;

  //Secondary (Hadron) Kinematics
  delete H_Em;         H_Em         = NULL;
  delete H_Em_nuc;     H_Em_nuc     = NULL;
  delete H_Pm;         H_Pm         = NULL;
  delete H_Pmx_lab;    H_Pmx_lab    = NULL;
  delete H_Pmy_lab;    H_Pmy_lab    = NULL;
  delete H_Pmz_lab;    H_Pmz_lab    = NULL;
  delete H_Pmx_q;      H_Pmx_q      = NULL;
  delete H_Pmy_q;      H_Pmy_q      = NULL;
  delete H_Pmz_q;      H_Pmz_q      = NULL;
  delete H_MM;         H_MM         = NULL;
  delete H_MM2;        H_MM2        = NULL;
  delete H_Pf;         H_Pf         = NULL;
  delete H_Ep;         H_Ep         = NULL;
  delete H_En;         H_En         = NULL;
  delete H_Kp;         H_Kp         = NULL;                                                                                          
  delete H_Kn;         H_Kn         = NULL;  
  delete H_theta_prot; H_theta_prot = NULL;
  delete H_theta_pq;   H_theta_pq   = NULL;
  delete H_theta_nq;   H_theta_nq   = NULL;

  //Target Reconstruction Histos
  delete H_hx_tar;  H_hx_tar = NULL;
  delete H_hy_tar;  H_hy_tar = NULL;
  delete H_hz_tar;  H_hz_tar = NULL;

  delete H_ex_tar;  H_ex_tar = NULL;
  delete H_ey_tar;  H_ey_tar = NULL;
  delete H_ez_tar;  H_ez_tar = NULL;

  delete H_ztar_diff; H_ztar_diff= NULL;

  //Hadron Arm Recon. / Focal Plane Histos
  delete H_hytar;   H_hytar  = NULL;
  delete H_hxptar;  H_hxptar = NULL;
  delete H_hyptar;  H_hyptar = NULL;
  delete H_hdelta;  H_hdelta = NULL;

  delete H_hxfp;    H_hxfp   = NULL;
  delete H_hyfp;    H_hyfp   = NULL;
  delete H_hxpfp;   H_hxpfp  = NULL;
  delete H_hypfp;   H_hypfp  = NULL;
  
  //Electron Arm Recon. / Focal Plane Histos
  delete H_eytar;   H_eytar  = NULL;
  delete H_exptar;  H_exptar = NULL;
  delete H_eyptar;  H_eyptar = NULL;
  delete H_edelta;  H_edelta = NULL;

  delete H_exfp;    H_exfp  = NULL;
  delete H_eyfp;    H_eyfp  = NULL;
  delete H_expfp;   H_expfp = NULL;
  delete H_eypfp;   H_eypfp = NULL;

  //HMS/SHMS Collimator
  delete H_hXColl;  H_hXColl = NULL;
  delete H_hYColl;  H_hYColl = NULL;
  delete H_eXColl;  H_eXColl = NULL;
  delete H_eYColl;  H_eYColl = NULL;

  //2D Collimator Histos
  delete H_hXColl_vs_hYColl; H_hXColl_vs_hYColl = NULL;
  delete H_eXColl_vs_eYColl; H_eXColl_vs_eYColl = NULL;
  delete H_Em_vs_Pm;         H_Em_vs_Pm         = NULL;
  delete H_Em_nuc_vs_Pm;     H_Em_nuc_vs_Pm         = NULL;

  //Delete Scaler Histograms
  delete H_bcmCurrent; H_bcmCurrent = NULL;

  cout << "End CallingDestructor() . . " << endl;
}


//___________________________________________________________________________
void analyze::SetFileNames()
{
  
  cout << "Calling SetFileNames() . . . " << endl;
   
  //Set Input CutFile Name (to read cuts and other parameters)
  input_CutFileName = Form("set_%s_cuts.inp", reaction.c_str());

  //If reaction is D(e,e'p)n
  if(reaction=="deep"){

    //Read Parameters from D(e,e'p) input file
    pm_setting = stoi(split(FindString("pm_setting", input_CutFileName)[0], ':')[1]);
    theory = trim(split(FindString("theory", input_CutFileName)[0], ':')[1]);
    model = trim(split(FindString("model", input_CutFileName)[0], ':')[1]);
    data_set = stoi(split(FindString("data_set", input_CutFileName)[0], ':')[1]);
  
    //Set Input Names
    data_InputFileName = Form("ROOTfiles/coin_replay_%s_check_%d_-1.root", reaction.c_str(), runNUM);
    data_InputReport = Form("REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_%s_check_%d_-1.report", reaction.c_str(), runNUM); 

    simc_InputFileName_rad = Form("worksim_voli/d2_pm%d_%s%s_rad_set%d.root", pm_setting, theory.c_str(), model.c_str(), data_set );
    simc_InputFileName_norad = Form("worksim_voli/d2_pm%d_%s%s_norad_set%d.root", pm_setting, theory.c_str(), model.c_str(), data_set );
    
    //Set Output Names
    data_OutputFileName = Form("%s_data_histos_pm%d_set%d_%d.root",reaction.c_str(), pm_setting, data_set, runNUM);
    data_OutputFileName_radCorr = Form("%s_data_histos_pm%d_set%d_%d_radcorr.root",reaction.c_str(), pm_setting, data_set, runNUM);
    report_OutputFileName = Form("report_%s_pm%d_set%d.dat", reaction.c_str(), pm_setting, data_set);

    simc_OutputFileName_rad = Form("%s_simc_histos_pm%d_%s%s_rad_set%d.root",reaction.c_str(), pm_setting, theory.c_str(), model.c_str(), data_set);
    simc_OutputFileName_norad = Form("%s_simc_histos_pm%d_%s%s_norad_set%d.root",reaction.c_str(), pm_setting, theory.c_str(), model.c_str(), data_set);
    simc_OutputFileName_radCorr = Form("%s_simc_histos_pm%d_%s%s_RadCorrRatio_set%d.root",reaction.c_str(), pm_setting, theory.c_str(), model.c_str(), data_set);
   

  }
  

  //If reaction is H(e,e'p)
  if(reaction=="heep"){

    
    //Set Input Names
    data_InputFileName = Form("ROOTfiles/coin_replay_%s_check_%d_-1.root", reaction.c_str(), runNUM);
    data_InputReport = Form("REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_%s_check_%d_-1.report", reaction.c_str(), runNUM); 

    simc_InputFileName_rad = Form("worksim_voli/D2_heep_%d_rad.root", runNUM);
    simc_InputFileName_norad = Form("worksim_voli/D2_heep_%d_norad.root", runNUM);
    

    //Set Output Names
    data_OutputFileName = Form("%s_data_histos_%d.root",reaction.c_str(), runNUM);
    data_OutputFileName_radCorr = Form("%s_data_histos_%d_radcorr.root",reaction.c_str(), runNUM); 
    report_OutputFileName = Form("report_%s.dat", reaction.c_str());

    simc_OutputFileName_rad = Form("%s_simc_histos_%d_rad.root",reaction.c_str(), runNUM);
    simc_OutputFileName_norad = Form("%s_simc_histos_%d_norad.root",reaction.c_str(), runNUM);
    simc_OutputFileName_radCorr = Form("%s_simc_histos_%d_RadCorrRatio.root",reaction.c_str(), runNUM);


  }



  cout << "Ending SetFileNames() . . . " << endl;
}

//_____________________________________________________________________________
void analyze::SetCuts()
{

  cout << "Calling SetCuts() . . ." << endl;
  
  //Read Cut Flags from set_heep(deep)_cuts.input file 
  
  //==BASIC==
  Em_cut_flag = stoi(split(FindString("bool Em", input_CutFileName)[0], '=')[1]);
  W_cut_flag = stoi(split(FindString("bool W", input_CutFileName)[0], '=')[1]);
  hdelta_cut_flag = stoi(split(FindString("bool h_delta", input_CutFileName)[0], '=')[1]);
  edelta_cut_flag = stoi(split(FindString("bool e_delta", input_CutFileName)[0], '=')[1]);
  ztar_diff_cut_flag = stoi(split(FindString("bool ztar_diff", input_CutFileName)[0], '=')[1]);
  Q2_cut_flag = stoi(split(FindString("bool Q2", input_CutFileName)[0], '=')[1]);
  thnq_cut_flag = stoi(split(FindString("bool th_nq", input_CutFileName)[0], '=')[1]);
  MM_cut_flag = stoi(split(FindString("bool MM", input_CutFileName)[0], '=')[1]);

  //==PID==
  shmsCal_cut_flag = stoi(split(FindString("bool shmsCal_EtotTrackNorm", input_CutFileName)[0], '=')[1]);
  coin_cut_flag = stoi(split(FindString("bool coin_time", input_CutFileName)[0], '=')[1]);
  
  //==Collimator==
  hmsCollCut_flag = stoi(split(FindString("bool hmsCollCut", input_CutFileName)[0], '=')[1]);
  shmsCollCut_flag = stoi(split(FindString("bool shmsCollCut", input_CutFileName)[0], '=')[1]);
  
  //==Read Collimator Cut Scale Factor==
  hms_scale =  stod(split(FindString("hms_scale", input_CutFileName)[0], '=')[1]);
  shms_scale =  stod(split(FindString("shms_scale", input_CutFileName)[0], '=')[1]);



  //Read Cut Limits from set_heep(deep)_cuts.input file 
  Em_min = stod(split(FindString("Em_min", input_CutFileName)[0], ':')[1]);
  Em_max = stod(split(FindString("Em_max", input_CutFileName)[0], ':')[1]);
  
  hdel_min = stod(split(FindString("h_delta_min", input_CutFileName)[0], ':')[1]);
  hdel_max = stod(split(FindString("h_delta_max", input_CutFileName)[0], ':')[1]);
 
  edel_min = stod(split(FindString("e_delta_min", input_CutFileName)[0], ':')[1]);
  edel_max = stod(split(FindString("e_delta_max", input_CutFileName)[0], ':')[1]);
  
  W_min = stod(split(FindString("W_min", input_CutFileName)[0], ':')[1]);
  W_max = stod(split(FindString("W_max", input_CutFileName)[0], ':')[1]);

  ztarDiff_min = stod(split(FindString("ztarDiff_min", input_CutFileName)[0], ':')[1]); 
  ztarDiff_max = stod(split(FindString("ztarDiff_max", input_CutFileName)[0], ':')[1]);
 
  Q2_min = stod(split(FindString("Q2_min", input_CutFileName)[0], ':')[1]); 
  Q2_max = stod(split(FindString("Q2_max", input_CutFileName)[0], ':')[1]);
  
  thnq_min = stod(split(FindString("thnq_min", input_CutFileName)[0], ':')[1]); 
  thnq_max = stod(split(FindString("thnq_max", input_CutFileName)[0], ':')[1]);

  MM_min = stod(split(FindString("MM_min", input_CutFileName)[0], ':')[1]); 
  MM_max = stod(split(FindString("MM_max", input_CutFileName)[0], ':')[1]);

  shms_cal_min = stod(split(FindString("shms_cal_min", input_CutFileName)[0], ':')[1]);
  shms_cal_max = stod(split(FindString("shms_cal_max", input_CutFileName)[0], ':')[1]);
  
  ctime_min = stod(split(FindString("coin_time_min", input_CutFileName)[0], ':')[1]);
  ctime_max = stod(split(FindString("coin_time_max", input_CutFileName)[0], ':')[1]);



  cout << "Ending SetCuts() . . ." << endl;

}

//___________________________________________________________________________
void analyze::SetDefinitions()
{
  /*Brief: Set particle masses, useful mathematical constants, and cut limits
    Units: Mass [GeV]
   */
  
  cout << "Calling SetDefinitions() . . . " << endl;
  
  pi = TMath::Pi();
  dtr = pi / 180.;    //degree-to-radians conversion factor


  //Particle Masses
  MP = 0.938272;     //proton mass
  MN = 0.939566;     //neutron mass
  MD = 1.87561;      //deuteron mass
  me = 0.00051099;   //electron mass

  //Target Mass 
  if(reaction=="heep"){tgt_mass = MP;} 
  else if(reaction=="deep"){tgt_mass = MD;} 
   
  //Read Spectrometer Kinematics from REPORT_FILE
  string temp;
  
  //Read Angles (in deg)
  temp = FindString("hHMS Angle", data_InputReport)[0];    //Find line containing string
  h_th = stod(split(temp, ':')[1]);                              //split string, take the number part, and conver to double


  temp = FindString("pSHMS Angle", data_InputReport)[0];
  e_th = stod(split(temp, ':')[1]);
  
  //Read Central Momenta (in GeV)
  temp = FindString("hHMS P Central", data_InputReport)[0]; 
  h_Pcen = stod(split(temp, ':')[1]);
  
  temp = FindString("pSHMS P Central", data_InputReport)[0]; 
  e_Pcen = stod(split(temp, ':')[1]);
  
  //Read Beam Positions (in cm, Hall Coord. System)
  temp = FindString("pSHMS X BPM", data_InputReport)[0];
  xBPM = stod(split(split(temp, ':')[1], 'c')[0]);
  
  temp = FindString("pSHMS Y BPM", data_InputReport)[0];
  yBPM = stod(split(split(temp, ':')[1], 'c')[0]);
  
  
  //Read MisPointings (in cm)
  temp = FindString("hHMS X Mispointing", data_InputReport)[0];
  h_xMisPoint = stod(split(split(temp, ':')[1], 'c')[0]);
  
  temp = FindString("hHMS Y Mispointing", data_InputReport)[0];
  h_yMisPoint = stod(split(split(temp, ':')[1], 'c')[0]);
  
  temp = FindString("pSHMS X Mispointing", data_InputReport)[0];
  e_xMisPoint = stod(split(split(temp, ':')[1], 'c')[0]);
  
  temp = FindString("pSHMS Y Mispointing", data_InputReport)[0];
  e_yMisPoint = stod(split(split(temp, ':')[1], 'c')[0]);
  
  
  cout << "Ending SetDefinitions() . . . " << endl;
  
}


//___________________________________________________________________________
void analyze::SetHistBins()
{
  cout << "Calling SetHistBins() . . . " << endl;
      
  //HMS DETECTORS               //SHMS Detectors         //Trigger Detector
  hbeta_nbins = 100;	        pbeta_nbins = 100;       coin_nbins = 100;    
  hbeta_xmin = 0.5;		pbeta_xmin = 0.5;        coin_xmin = 0.;
  hbeta_xmax = 1.5;		pbeta_xmax = 1.5;        coin_xmax = 30.;
  
  hcer_nbins = 100;		pngcer_nbins = 100;  
  hcer_xmin = 0.001;	        pngcer_xmin = 0.001; 
  hcer_xmax = 20.;		pngcer_xmax = 50.;   
  
  hcal_nbins = 100;		pcal_nbins = 100;    
  hcal_xmin = 0.001;	        pcal_xmin = 0.001;   
  hcal_xmax = 1.5;		pcal_xmax = 1.5;   

  //Set Histogram Limits for a specified run / kinematic setting
  
  //-----H(e,e'p) Elastic Runs----
  if(runNUM==3288)
    {
      
      //-----------------------KINEMATICS---------------------
      
      //Missing Energy                    //Q2			          //Final Proton Momentum			     
      Em_nbins = 100;			  Q2_nbins = nbins;	   	   Pf_nbins = nbins;				    
      Em_xmin = -0.05;			  Q2_xmin = 2.5;	   	   Pf_xmin = 2.5;				    
      Em_xmax = 0.1;			  Q2_xmax = 5;		   	   Pf_xmax = 3.5;				    
      					 			   	 						    
      //Missing Momentum 		  //omega (E-E')	   	   //Final Proton Energy              
      Pm_nbins = nbins;			  om_nbins = nbins;	   	   Ep_nbins = nbins;	            			    
      Pm_xmin = -0.02;			  om_xmin = 1.8;	   	   Ep_xmin = 2.5;	            			     
      Pm_xmax = 0.08;			  om_xmax = 2.6;	   	   Ep_xmax = 3.5;	           			     
      								   	 						    
      Pmx_nbins = nbins;		  //W_inv		   	   //Final Electron Momentum			    
      Pmx_xmin = -0.05;			  W_nbins = nbins;	   	   kf_nbins = nbins;				    
      Pmx_xmax = 0.05;			  W_xmin = 0.85;	   	   kf_xmin = 8;					    
      					  W_xmax = 1.05;;	   	   kf_xmax = 9;					    
      Pmy_nbins = nbins;					   	 						    
      Pmy_xmin = -0.05;			  //W2			   	   //th_q (Angle between +Z(hall) and q-vector)	    
      Pmy_xmax = 0.05;			  W2_nbins = nbins;	   	   thq_nbins = nbins;				    
      					  W2_xmin = 0.0005;           	   thq_xmin = 32.;				    
      Pmz_nbins = nbins;		  W2_xmax = 0.0005;; 	   	   thq_xmax = 42.;				    
      Pmz_xmin = -0.02;						   	   						    
      Pmz_xmax = 0.08;			  //theta_elec		   	   //Magnitude of q-ector			    
      					  the_nbins = nbins;	   	   q_nbins = nbins;				    
      /*Missing Mass*/ 			  the_xmin = 10.;	   	   q_xmin = 2.6;					    
      MM_nbins = nbins;			  the_xmax = 15.;	   	   q_xmax = 4.;					    
      MM_xmin = -0.1;						   	 						    
      MM_xmax = 0.1;			  //theta_prot		   	   //th_pq (Angle between proton and q-vector)	    
      					  thp_nbins = nbins;	   	   thpq_nbins = nbins;				    
      /*Missing Mass Squared*/		  thp_xmin = 34.;	   	   thpq_xmin = -0.05;				    
      MM2_nbins = nbins;		  thp_xmax = 42.;	   	   thpq_xmax = 1.2;                                  
      MM2_xmin = -0.01;			  			   
      MM2_xmax = 0.01;			  
			   
      // X-bJORKEN                         		   
      xbj_nbins = nbins;		  	   
      xbj_xmin = 0.8;			  	   
      xbj_xmax = 1.1;			        


      //-----------------------------------Focal Plane /  Target Reconstruction------------------------------------
      
      //Target Recon. Var.(Lab)        //Hadron arm Recon. Quantities (ytar, xptar, yptar, delta)	      //Hadron arm Focal Plane Quantities    		           
      xtar_nbins = nbins;	       hytar_nbins = nbins;						      hxfp_nbins = nbins;			       		  
      xtar_xmin = -0.5;		       hytar_xmin = -5.;						      hxfp_xmin = -50.;				       			  
      xtar_xmax = 0.5;		       hytar_xmax = 5.;							      hxfp_xmax = 40.;				       		  
      				       									      						       		  
      ytar_nbins = nbins;	       hxptar_nbins = 70;						      hyfp_nbins = nbins;  			       		  
      ytar_xmin = -0.5;		       hxptar_xmin = -0.1;						      hyfp_xmin = -10.;				       		  
      ytar_xmax = 0.5;		       hxptar_xmax = 0.1;						      hyfp_xmax = 25.;				       		  
      				       									      						       		  
      ztar_nbins = nbins;	       hyptar_nbins = 70;						      hxpfp_nbins = nbins;			       		  
      ztar_xmin = -10.0;	       hyptar_xmin = -0.05;						      hxpfp_xmin = -0.06;			       		  
      ztar_xmax = 10.0;		       hyptar_xmax = 0.05;						      hxpfp_xmax = 0.06;			       		  
      				       									      						       		  
				       hdelta_nbins = 70;						      hypfp_nbins = nbins;			       		  
				       hdelta_xmin = -9.;						      hypfp_xmin = -0.015;			       		  
				       hdelta_xmax = 9.;                                                      hypfp_xmax = 0.03;                                                  


  //Collimator                         //Electron Arm Recon Quantities ( ytar, xptar, yptar, delta)	      //Electron Arm Focal Plane Quantities	 
  hXColl_nbins = 100;		       eytar_nbins = nbins;						      exfp_nbins = nbins;			 	   
  hXColl_xmin = -15.;  		       eytar_xmin = -4.;						      exfp_xmin = -15.;			 	   
  hXColl_xmax = 15.;   		       eytar_xmax = 4.;							      exfp_xmax = 10.;			 
  				         								      					 	   
  hYColl_nbins = 100;                  exptar_nbins = nbins;						      eyfp_nbins = nbins;			 	                            
  hYColl_xmin = -15.;                  exptar_xmin = -0.06;						      eyfp_xmin = -10.;			 	                                                                                   
  hYColl_xmax = 15.;		       exptar_xmax = 0.06;						      eyfp_xmax = 10.;			 	   
  				         								     					 	   
  eXColl_nbins = 100;		       eyptar_nbins = nbins;						      expfp_nbins = nbins;			 	   
  eXColl_xmin = -15.;		       eyptar_xmin = -0.03;						      expfp_xmin = -0.04;			 	   
  eXColl_xmax = 15.;		       eyptar_xmax = 0.02;						      expfp_xmax = 0.04;			 	   
  				         								     					 	   
  eYColl_nbins = 100;      	       edelta_nbins = nbins;						      eypfp_nbins = nbins;			 	   
  eYColl_xmin = -15.;                  edelta_xmin = -5.;  						      eypfp_xmin = -0.03;			 	                                                       
  eYColl_xmax = 15.;		       edelta_xmax = 5.;                                                      eypfp_xmax = 0.03;                        

  
    } //End 3288
  
  if(runNUM==3371)
    {
      
      //-----------------------KINEMATICS---------------------
      
      //Missing Energy                    //Q2			          //Final Proton Momentum			     
      Em_nbins = 100;			  Q2_nbins = nbins;	   	   Pf_nbins = nbins;				    
      Em_xmin = -0.05;			  Q2_xmin = 4.; 	   	   Pf_xmin = 3.;				    
      Em_xmax = 0.1;			  Q2_xmax = 5.8;       	   	   Pf_xmax = 4.;				    
      					 			   	 						    
      //Missing Momentum 		  //omega (E-E')	   	   //Final Proton Energy				    
      Pm_nbins = nbins;			  om_nbins = nbins;	   	   Ep_nbins = nbins;				    
      Pm_xmin = -0.02;			  om_xmin = 1.8;	   	   Ep_xmin = 2.5;				    
      Pm_xmax = 0.08;			  om_xmax = 3.4;	   	   Ep_xmax = 3.5;				    
      								   	 						    
      Pmx_nbins = nbins;		  //W_inv		   	   //Final Electron Momentum			    
      Pmx_xmin = -0.15;			  W_nbins = nbins;	   	   kf_nbins = nbins;				    
      Pmx_xmax = 0.15;			  W_xmin = 0.85;	   	   kf_xmin = 7;					    
      					  W_xmax = 1.05;;	   	   kf_xmax = 8.5;					    
      Pmy_nbins = nbins;					   	 						    
      Pmy_xmin = -0.15;			  //W2			   	   //th_q (Angle between +Z(hall) and q-vector)	    
      Pmy_xmax = 0.15;			  W2_nbins = nbins;	   	   thq_nbins = nbins;				    
      					  W2_xmin = 0.5;           	   thq_xmin = 27.;				    
      Pmz_nbins = nbins;		  W2_xmax = 0.9;; 	   	   thq_xmax = 37.;				    
      Pmz_xmin = -0.15;						   	   						    
      Pmz_xmax = 0.15;			  //theta_elec		   	   //Magnitude of q-ector			    
                                          the_nbins = nbins;	   	   q_nbins = nbins;				    
      /*Missing Mass*/ 			  the_xmin = 10.;	   	   q_xmin = 3.1;					    
      MM_nbins = nbins;			  the_xmax = 16.;	   	   q_xmax = 4.2;					    
      MM_xmin = -0.1;						   	 						    
      MM_xmax = 0.1;			  //theta_prot		   	   //th_pq (Angle between proton and q-vector)	    
                                          thp_nbins = nbins;	   	   thpq_nbins = nbins;				    
      /*Missing Mass Squared*/		  thp_xmin = 30.;	   	   thpq_xmin = -0.05;				    
      MM2_nbins = nbins;		  thp_xmax = 37.;	   	   thpq_xmax = 1.2;                                  
      MM2_xmin = -0.01;			  			   
      MM2_xmax = 0.01;			  
      
      // X-bJORKEN                        			   
      xbj_nbins = nbins;		  	   
      xbj_xmin = 0.8;			  	   
      xbj_xmax = 1.1;			            


      //-----------------------------------Focal Plane /  Target Reconstruction------------------------------------
      
      //Target Recon. Var.(Lab)        //Hadron arm Recon. Quantities (ytar, xptar, yptar, delta)	      //Hadron arm Focal Plane Quantities    		           
      xtar_nbins = nbins;	       hytar_nbins = nbins;						      hxfp_nbins = nbins;			       		  
      xtar_xmin = -0.5;		       hytar_xmin = -5.;						      hxfp_xmin = -50.;				       			  
      xtar_xmax = 0.5;		       hytar_xmax = 5.;							      hxfp_xmax = 40.;				       		  
      				       									      						       		  
      ytar_nbins = nbins;	       hxptar_nbins = 70;						      hyfp_nbins = nbins;  			       		  
      ytar_xmin = -0.5;		       hxptar_xmin = -0.1;						      hyfp_xmin = -10.;				       		  
      ytar_xmax = 0.5;		       hxptar_xmax = 0.1;						      hyfp_xmax = 25.;				       		  
      				       									      						       		  
      ztar_nbins = nbins;	       hyptar_nbins = 70;						      hxpfp_nbins = nbins;			       		  
      ztar_xmin = -10.0;	       hyptar_xmin = -0.05;						      hxpfp_xmin = -0.06;			       		  
      ztar_xmax = 10.0;		       hyptar_xmax = 0.05;						      hxpfp_xmax = 0.06;			       		  
      				       									      						       		  
				       hdelta_nbins = 70;						      hypfp_nbins = nbins;			       		  
				       hdelta_xmin = -9.;						      hypfp_xmin = -0.015;			       		  
				       hdelta_xmax = 9.;                                                      hypfp_xmax = 0.03;                                                  


  //Collimator                         //Electron Arm Recon Quantities ( ytar, xptar, yptar, delta)	      //Electron Arm Focal Plane Quantities	 
  hXColl_nbins = 100;		       eytar_nbins = nbins;						      exfp_nbins = nbins;			 	   
  hXColl_xmin = -15.;  		       eytar_xmin = -4.;						      exfp_xmin = -25.;			 	   
  hXColl_xmax = 15.;   		       eytar_xmax = 4.;							      exfp_xmax = 0.;			 
  				         								      					 	   
  hYColl_nbins = 100;                  exptar_nbins = nbins;						      eyfp_nbins = nbins;			 	                            
  hYColl_xmin = -15.;                  exptar_xmin = -0.06;						      eyfp_xmin = -20.;			 	                                                                                   
  hYColl_xmax = 15.;		       exptar_xmax = 0.06;						      eyfp_xmax = 15.;			 	   
  				         								     					 	   
  eXColl_nbins = 100;		       eyptar_nbins = nbins;						      expfp_nbins = nbins;			 	   
  eXColl_xmin = -15.;		       eyptar_xmin = -0.03;						      expfp_xmin = -0.06;			 	   
  eXColl_xmax = 15.;		       eyptar_xmax = 0.02;						      expfp_xmax = 0.02;			 	   
  				         								     					 	   
  eYColl_nbins = 100;      	       edelta_nbins = nbins;						      eypfp_nbins = nbins;			 	   
  eYColl_xmin = -15.;                  edelta_xmin = -12.;  						      eypfp_xmin = -0.04;			 	                                                       
  eYColl_xmax = 15.;		       edelta_xmax = -3.;                                                     eypfp_xmax = 0.03;                        
  
  
    } //End 3371

  if(runNUM==3374)
    {
      
      //-----------------------KINEMATICS---------------------
      
      //Missing Energy                    //Q2			          //Final Proton Momentum			     
      Em_nbins = 100;			  Q2_nbins = nbins;	   	   Pf_nbins = nbins;				    
      Em_xmin = -0.05;			  Q2_xmin = 2.; 	   	   Pf_xmin = 2.;				    
      Em_xmax = 0.1;			  Q2_xmax = 3.4;       	   	   Pf_xmax = 3.;				    
      					 			   	 						    
      //Missing Momentum 		  //omega (E-E')	   	   //Final Proton Energy				    
      Pm_nbins = nbins;			  om_nbins = nbins;	   	   Ep_nbins = nbins;				    
      Pm_xmin = -0.02;			  om_xmin = 1.3;	   	   Ep_xmin = 2.5;				    
      Pm_xmax = 0.08;			  om_xmax = 2.0;	   	   Ep_xmax = 3.5;				    
      								   	 						    
      Pmx_nbins = nbins;		  //W_inv		   	   //Final Electron Momentum			    
      Pmx_xmin = -0.15;			  W_nbins = nbins;	   	   kf_nbins = nbins;				    
      Pmx_xmax = 0.15;			  W_xmin = 0.85;	   	   kf_xmin = 8;					    
      					  W_xmax = 1.05;;	   	   kf_xmax = 9.5;					    
      Pmy_nbins = nbins;					   	 						    
      Pmy_xmin = -0.15;			  //W2			   	   //th_q (Angle between +Z(hall) and q-vector)	    
      Pmy_xmax = 0.15;			  W2_nbins = nbins;	   	   thq_nbins = nbins;				    
      					  W2_xmin = 0.5;           	   thq_xmin = 38.;				    
      Pmz_nbins = nbins;		  W2_xmax = 0.9;; 	   	   thq_xmax = 45.5;				    
      Pmz_xmin = -0.15;						   	   						    
      Pmz_xmax = 0.15;			  //theta_elec		   	   //Magnitude of q-ector			    
                                          the_nbins = nbins;	   	   q_nbins = nbins;				    
      /*Missing Mass*/ 			  the_xmin = 9.;	   	   q_xmin = 2.;					    
      MM_nbins = nbins;			  the_xmax = 12.;	   	   q_xmax = 3.;					    
      MM_xmin = -0.1;						   	 						    
      MM_xmax = 0.1;			  //theta_prot		   	   //th_pq (Angle between proton and q-vector)	    
                                          thp_nbins = nbins;	   	   thpq_nbins = nbins;				    
      /*Missing Mass Squared*/		  thp_xmin = 40.;	   	   thpq_xmin = -0.05;				    
      MM2_nbins = nbins;		  thp_xmax = 47.;	   	   thpq_xmax = 1.2;                                  
      MM2_xmin = -0.01;			  			   
      MM2_xmax = 0.01;			  
      
      // X-bJORKEN                         		   
      xbj_nbins = nbins;		  	   
      xbj_xmin = 0.8;			  	   
      xbj_xmax = 1.1;			   


      //-----------------------------------Focal Plane /  Target Reconstruction------------------------------------
      
      //Target Recon. Var.(Lab)        //Hadron arm Recon. Quantities (ytar, xptar, yptar, delta)	      //Hadron arm Focal Plane Quantities    		           
      xtar_nbins = nbins;	       hytar_nbins = nbins;						      hxfp_nbins = nbins;			       		  
      xtar_xmin = -0.5;		       hytar_xmin = -5.;						      hxfp_xmin = -50.;				       			  
      xtar_xmax = 0.5;		       hytar_xmax = 5.;							      hxfp_xmax = 40.;				       		  
      				       									      						       		  
      ytar_nbins = nbins;	       hxptar_nbins = 70;						      hyfp_nbins = nbins;  			       		  
      ytar_xmin = -0.5;		       hxptar_xmin = -0.1;						      hyfp_xmin = -10.;				       		  
      ytar_xmax = 0.5;		       hxptar_xmax = 0.1;						      hyfp_xmax = 25.;				       		  
      				       									      						       		  
      ztar_nbins = nbins;	       hyptar_nbins = 70;						      hxpfp_nbins = nbins;			       		  
      ztar_xmin = -10.0;	       hyptar_xmin = -0.05;						      hxpfp_xmin = -0.06;			       		  
      ztar_xmax = 10.0;		       hyptar_xmax = 0.05;						      hxpfp_xmax = 0.06;			       		  
      				       									      						       		  
				       hdelta_nbins = 70;						      hypfp_nbins = nbins;			       		  
				       hdelta_xmin = -9.;						      hypfp_xmin = -0.015;			       		  
				       hdelta_xmax = 9.;                                                      hypfp_xmax = 0.03;                                                  


  //Collimator                         //Electron Arm Recon Quantities ( ytar, xptar, yptar, delta)	      //Electron Arm Focal Plane Quantities	 
  hXColl_nbins = 100;		       eytar_nbins = nbins;						      exfp_nbins = nbins;			 	   
  hXColl_xmin = -15.;  		       eytar_xmin = -4.;						      exfp_xmin = 0.;			 	   
  hXColl_xmax = 15.;   		       eytar_xmax = 4.;							      exfp_xmax = 15.;			 
  				         								      					 	   
  hYColl_nbins = 100;                  exptar_nbins = nbins;						      eyfp_nbins = nbins;			 	                            
  hYColl_xmin = -15.;                  exptar_xmin = -0.06;						      eyfp_xmin = -7.;			 	                                                                                   
  hYColl_xmax = 15.;		       exptar_xmax = 0.06;						      eyfp_xmax = 3.;			 	   
  				         								     					 	   
  eXColl_nbins = 100;		       eyptar_nbins = nbins;						      expfp_nbins = nbins;			 	   
  eXColl_xmin = -15.;		       eyptar_xmin = -0.03;						      expfp_xmin = -0.01;			 	   
  eXColl_xmax = 15.;		       eyptar_xmax = 0.02;						      expfp_xmax = 0.04;			 	   
  				         								     					 	   
  eYColl_nbins = 100;      	       edelta_nbins = nbins;						      eypfp_nbins = nbins;			 	   
  eYColl_xmin = -15.;                  edelta_xmin = 3.;  						      eypfp_xmin = -0.02;			 	                                                       
  eYColl_xmax = 15.;		       edelta_xmax = 10.;                                                     eypfp_xmax = 0.02;                        
  
  
    } //End 3374

  if(runNUM==3377)
    {
      
      //-----------------------KINEMATICS---------------------
      
      //Missing Energy                    //Q2			          //Final Proton Momentum			     
      Em_nbins = 100;			  Q2_nbins = nbins;	   	   Pf_nbins = nbins;				    
      Em_xmin = -0.05;			  Q2_xmin = 1.4; 	   	   Pf_xmin = 1.5;				    
      Em_xmax = 0.1;			  Q2_xmax = 2.6;       	   	   Pf_xmax = 2.5;				    
      					 			   	 						    
      //Missing Momentum 		  //omega (E-E')	   	   //Final Proton Energy				    
      Pm_nbins = nbins;			  om_nbins = nbins;	   	   Ep_nbins = nbins;				    
      Pm_xmin = -0.02;			  om_xmin = 0.9;	   	   Ep_xmin = 2.5;				    
      Pm_xmax = 0.08;			  om_xmax = 1.7;	   	   Ep_xmax = 3.5;				    
      								   	 						    
      Pmx_nbins = nbins;		  //W_inv		   	   //Final Electron Momentum			    
      Pmx_xmin = -0.15;			  W_nbins = nbins;	   	   kf_nbins = nbins;				    
      Pmx_xmax = 0.15;			  W_xmin = 0.85;	   	   kf_xmin = 9.;					    
      					  W_xmax = 1.05;;	   	   kf_xmax = 9.7;					    
      Pmy_nbins = nbins;					   	 						    
      Pmy_xmin = -0.15;			  //W2			   	   //th_q (Angle between +Z(hall) and q-vector)	    
      Pmy_xmax = 0.15;			  W2_nbins = nbins;	   	   thq_nbins = nbins;				    
      					  W2_xmin = 0.5;           	   thq_xmin = 44.;				    
      Pmz_nbins = nbins;		  W2_xmax = 0.9;; 	   	   thq_xmax = 52.;				    
      Pmz_xmin = -0.15;						   	   						    
      Pmz_xmax = 0.15;			  //theta_elec		   	   //Magnitude of q-ector			    
                                          the_nbins = nbins;	   	   q_nbins = nbins;				    
      /*Missing Mass*/ 			  the_xmin = 7.5;	   	   q_xmin = 1.6;					    
      MM_nbins = nbins;			  the_xmax = 10.;	   	   q_xmax = 2.4;					    
      MM_xmin = -0.1;						   	 						    
      MM_xmax = 0.1;			  //theta_prot		   	   //th_pq (Angle between proton and q-vector)	    
                                          thp_nbins = nbins;	   	   thpq_nbins = nbins;				    
      /*Missing Mass Squared*/		  thp_xmin = 44.;	   	   thpq_xmin = -0.05;				    
      MM2_nbins = nbins;		  thp_xmax = 52.;	   	   thpq_xmax = 1.2;                                  
      MM2_xmin = -0.01;			  			   
      MM2_xmax = 0.01;			  
      
      // X-bJORKEN                        		   
      xbj_nbins = nbins;		 	   
      xbj_xmin = 0.8;			  	   
      xbj_xmax = 1.1;			    


      //-----------------------------------Focal Plane /  Target Reconstruction------------------------------------
      
      //Target Recon. Var.(Lab)        //Hadron arm Recon. Quantities (ytar, xptar, yptar, delta)	      //Hadron arm Focal Plane Quantities    		           
      xtar_nbins = nbins;	       hytar_nbins = nbins;						      hxfp_nbins = nbins;			       		  
      xtar_xmin = -0.5;		       hytar_xmin = -5.;						      hxfp_xmin = -50.;				       			  
      xtar_xmax = 0.5;		       hytar_xmax = 5.;							      hxfp_xmax = 40.;				       		  
      				       									      						       		  
      ytar_nbins = nbins;	       hxptar_nbins = 70;						      hyfp_nbins = nbins;  			       		  
      ytar_xmin = -0.5;		       hxptar_xmin = -0.1;						      hyfp_xmin = -10.;				       		  
      ytar_xmax = 0.5;		       hxptar_xmax = 0.1;						      hyfp_xmax = 25.;				       		  
      				       									      						       		  
      ztar_nbins = nbins;	       hyptar_nbins = 70;						      hxpfp_nbins = nbins;			       		  
      ztar_xmin = -10.0;	       hyptar_xmin = -0.05;						      hxpfp_xmin = -0.06;			       		  
      ztar_xmax = 10.0;		       hyptar_xmax = 0.05;						      hxpfp_xmax = 0.06;			       		  
      				       									      						       		  
				       hdelta_nbins = 70;						      hypfp_nbins = nbins;			       		  
				       hdelta_xmin = -9.;						      hypfp_xmin = -0.015;			       		  
				       hdelta_xmax = 9.;                                                      hypfp_xmax = 0.03;                                                  


  //Collimator                         //Electron Arm Recon Quantities ( ytar, xptar, yptar, delta)	      //Electron Arm Focal Plane Quantities	 
  hXColl_nbins = 100;		       eytar_nbins = nbins;						      exfp_nbins = nbins;			 	   
  hXColl_xmin = -15.;  		       eytar_xmin = -4.;						      exfp_xmin = 10.;			 	   
  hXColl_xmax = 15.;   		       eytar_xmax = 4.;							      exfp_xmax = 25.;			 
  				         								      					 	   
  hYColl_nbins = 100;                  exptar_nbins = nbins;						      eyfp_nbins = nbins;			 	                            
  hYColl_xmin = -15.;                  exptar_xmin = -0.06;						      eyfp_xmin = -10.;			 	                                                                                   
  hYColl_xmax = 15.;		       exptar_xmax = 0.06;						      eyfp_xmax = 5.;			 	   
  				         								     					 	   
  eXColl_nbins = 100;		       eyptar_nbins = nbins;						      expfp_nbins = nbins;			 	   
  eXColl_xmin = -15.;		       eyptar_xmin = -0.03;						      expfp_xmin = 0.01;			 	   
  eXColl_xmax = 15.;		       eyptar_xmax = 0.02;						      expfp_xmax = 0.05;			 	   
  				         								     					 	   
  eYColl_nbins = 100;      	       edelta_nbins = nbins;						      eypfp_nbins = nbins;			 	   
  eYColl_xmin = -15.;                  edelta_xmin = 8.;  						      eypfp_xmin = -0.01;			 	                                                       
  eYColl_xmax = 15.;		       edelta_xmax = 13.;                                                     eypfp_xmax = 0.01;                        
  
  
    } //End 3377
  
  if(runNUM==3289)
    {

      nbins = 100;
 
      //-----------------------KINEMATICS---------------------
      
      //Missing Energy                    //Q2			          //Final Proton Momentum			     
      Em_nbins = nbins;			  Q2_nbins = nbins;	   	   Pf_nbins = nbins;				    
      Em_xmin = -0.05;			  Q2_xmin = 2.5; 	   	   Pf_xmin = 2.5;				    
      Em_xmax = 0.1;			  Q2_xmax = 5.;       	   	   Pf_xmax = 3.2;				    
      					 			   	 						    
      //Missing Momentum 		  //omega (E-E')	   	   //Final Proton Energy				    
      Pm_nbins = nbins;			  om_nbins = nbins;	   	   Ep_nbins = nbins;				    
      Pm_xmin = -0.1;			  om_xmin = 1.5;	   	   Ep_xmin = 2.7;				    
      Pm_xmax = 0.5;			  om_xmax = 2.7;	   	   Ep_xmax = 3.3;				    
      								   	 						    
      Pmx_nbins = nbins;		          //W_inv		   	   //Final Electron Momentum			    
      Pmx_xmin = -0.3;			  W_nbins = nbins;	   	   kf_nbins = nbins;				    
      Pmx_xmax = 0.3;			  W_xmin = 0.85;	   	   kf_xmin = 8.2;					    
      					  W_xmax = 1.05;	   	   kf_xmax = 8.8;					    
      Pmy_nbins = nbins;					   	 						    
      Pmy_xmin = -0.3;			  //W2			   	   //th_q (Angle between +Z(hall) and q-vector)	    
      Pmy_xmax = 0.3;			  W2_nbins = nbins;	   	   thq_nbins = nbins;				    
      					  W2_xmin = -2;           	   thq_xmin = 32.;				    
      Pmz_nbins = nbins;		          W2_xmax = 2.; 	   	   thq_xmax = 42.;				    
      Pmz_xmin = -0.2;						   	   						    
      Pmz_xmax = 0.2;			  //theta_elec		   	   //Magnitude of q-ector			    
                                          the_nbins = nbins;	   	   q_nbins = nbins;				    
      /*Missing Mass*/ 			  the_xmin = 10;	   	   q_xmin = 2.4;					    
      MM_nbins = nbins;			  the_xmax = 14;	   	   q_xmax = 3.4;					    
      MM_xmin = 0.9;						   	 						    
      MM_xmax = 1.;			  //theta_prot		   	   //th_pq (Angle between proton and q-vector)	    
                                          thp_nbins = nbins;	   	   thpq_nbins = nbins;				    
      /*Missing Mass Squared*/		  thp_xmin = 34.;	   	   thpq_xmin = -0.001;				    
      MM2_nbins = nbins;		  thp_xmax = 42.;	   	   thpq_xmax = 5.;                                  
      MM2_xmin = -0.01;			  			   
      MM2_xmax = 0.01;			  
      
      // X-bJORKEN                         //th_nq                         //Proton Kin. Energy 
      xbj_nbins = nbins;		   thnq_nbins = nbins;              Kp_nbins = nbins; 
      xbj_xmin = 0.8;			   thnq_xmin = 0;                   Kp_xmin = 1.6;   
      xbj_xmax = 1.2;			   thnq_xmax = 180;                 Kp_xmax = 2.6;  
     
      //Neutron Kin. Energy                 //Neutron Final Energy, En
      Kn_nbins = nbins;                      En_nbins = nbins;
      Kn_xmin = -0.001;                      En_xmin = 0.938;                                                              
      Kn_xmax = 0.015;                        En_xmax = 0.96;


      //-----------------------------------Focal Plane /  Target Reconstruction------------------------------------
      
      //Target Recon. Var.(Lab)        //Hadron arm Recon. Quantities (ytar, xptar, yptar, delta)	      //Hadron arm Focal Plane Quantities    		           
      xtar_nbins = nbins;	       hytar_nbins = nbins;						      hxfp_nbins = nbins;			       		  
      xtar_xmin = -0.5;		       hytar_xmin = -7.;						      hxfp_xmin = -50.;				       			  
      xtar_xmax = 0.5;		       hytar_xmax = 7.;							      hxfp_xmax = 40.;				       		  
      				       									      						       		  
      ytar_nbins = nbins;	       hxptar_nbins = nbins;						      hyfp_nbins = nbins;  			       		 
      ytar_xmin = -0.5;		       hxptar_xmin = -0.1;						      hyfp_xmin = -15.;				       		  
      ytar_xmax = 0.5;		       hxptar_xmax = 0.1;						      hyfp_xmax = 25.;				       		  
      				       									      						       		  
      ztar_nbins = nbins;	       hyptar_nbins = nbins;						      hxpfp_nbins = nbins;			       		  
      ztar_xmin = -10.0;	       hyptar_xmin = -0.1;						      hxpfp_xmin = -0.08;			       		  
      ztar_xmax = 10.0;		       hyptar_xmax = 0.1;						      hxpfp_xmax = 0.06;			       		  
      				       									      						       		  
				       hdelta_nbins = nbins;						      hypfp_nbins = nbins;			       		  
				       hdelta_xmin = -15.;						      hypfp_xmin = -0.025;			       		  
				       hdelta_xmax = 15.;                                                     hypfp_xmax = 0.03;                                                  


  //Collimator                         //Electron Arm Recon Quantities ( ytar, xptar, yptar, delta)	      //Electron Arm Focal Plane Quantities	 
  hXColl_nbins = 100;		       eytar_nbins = nbins;						      exfp_nbins = nbins;			 	   
  hXColl_xmin = -15.;  		       eytar_xmin = -2.;						      exfp_xmin = -15.;			 	   
  hXColl_xmax = 15.;   		       eytar_xmax = 2.;							      exfp_xmax = 10.;			 
  				         								      					 	   
  hYColl_nbins = 100;                  exptar_nbins = nbins;						      eyfp_nbins = nbins;			 	                            
  hYColl_xmin = -15.;                  exptar_xmin = -0.06;						      eyfp_xmin = -10.;
  hYColl_xmax = 15.;		       exptar_xmax = 0.06;						      eyfp_xmax = 10.;			 	   
  				         								     					 	   
  eXColl_nbins = 100;		       eyptar_nbins = nbins;						      expfp_nbins = nbins;			 	   
  eXColl_xmin = -15.;		       eyptar_xmin = -0.03;						      expfp_xmin = -0.04;			 	   
  eXColl_xmax = 15.;		       eyptar_xmax = 0.03;						      expfp_xmax = 0.04;			 	   
  				         								     					 	   
  eYColl_nbins = 100;      	       edelta_nbins = nbins;						      eypfp_nbins = nbins;			 	   
  eYColl_xmin = -15.;                  edelta_xmin = -3.;  						      eypfp_xmin = -0.03; 
  eYColl_xmax = 15.;		       edelta_xmax = 3.;                                                     eypfp_xmax = 0.03;                        
  
  
    } //End 3289

  cout << "Ending SetHistBins() . . . " << endl;
  
} //End SetHistBins()

//_______________________________________________________________________________
void analyze::CreateHist()
{
  //Method to Create Histograms
  
  cout << "Calling CreateHist() . . . " << endl;
  
  //Trigger Detector
  H_ctime = new TH1F("H_ctime", "ep Coincidence Time", coin_nbins, coin_xmin, coin_xmax);
  H_ctime->Sumw2(); //Apply sum of weight squared to this histogram ABOVE.
  H_ctime->SetDefaultSumw2();  //Generalize sum weights squared to all histograms  (ROOT 6 has this by default. ROOT 5 does NOT)

  //HMS Detectors
  H_hbeta = new TH1F("H_hbeta", "HMS Beta", hbeta_nbins, hbeta_xmin, hbeta_xmax);
  H_hcer = new TH1F("H_hcer", "HMS Cherenkov Npe Sum", hcer_nbins, hcer_xmin, hcer_xmax);
  H_hcal = new TH1F("H_hcal", "HMS Cal. EtotNorm", hcal_nbins, hcal_xmin, hcal_xmax);
    
  //SHMS Detectors
  H_pbeta = new TH1F("H_pbeta", "SHMS Beta", pbeta_nbins, pbeta_xmin, pbeta_xmax);
  H_pngcer = new TH1F("H_pngcer", "SHMS Noble Cherenkov Npe Sum", pngcer_nbins, pngcer_xmin, pngcer_xmax);
  H_pcal_etotnorm = new TH1F("H_pcal_etotnorm", "SHMS Cal. EtotNorm", pcal_nbins, pcal_xmin, pcal_xmax);
  H_pcal_etotTrkNorm = new TH1F("H_pcal_etotTrkNorm", "SHMS Cal. EtotTrackNorm", pcal_nbins, pcal_xmin, pcal_xmax);



  //Primary (electron) Kinematics
  H_Q2 = new TH1F("H_Q2","Q2", Q2_nbins, Q2_xmin, Q2_xmax); 
  H_omega = new TH1F("H_omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax); 
  H_W = new TH1F("H_W", "Invariant Mass, W", W_nbins, W_xmin, W_xmax); 
  H_W2 = new TH1F("H_W2", "Invariant Mass, W2", W2_nbins, W2_xmin, W2_xmax); 
  H_xbj = new TH1F("H_xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);  
  H_kf = new TH1F("H_kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);
  H_theta_q = new TH1F("H_theta_q", "q-vector Angle, #theta_{q}", thq_nbins, thq_xmin, thq_xmax); 
  H_q = new TH1F("H_q", "q-vector, |q|", q_nbins, q_xmin, q_xmax);
  H_theta_elec = new TH1F("H_theta_elec", "Electron Scattering Angle", the_nbins, the_xmin, the_xmax); 

  //Secondary (Hadron) Kinematics
  H_Em = new TH1F("H_Emiss","Missing Energy", Em_nbins, Em_xmin, Em_xmax); 
  //H_Em->SetDefaultSumw2();  //FIXME:  Need to check if this actually works
  
  H_Em_nuc = new TH1F("H_Em_nuc","Nuclear Missing Energy", Em_nbins, Em_xmin, Em_xmax); 
  H_Pm = new TH1F("H_Pm","Missing Momentum", Pm_nbins, Pm_xmin, Pm_xmax); 
  H_Pmx_lab = new TH1F("H_Pmx_Lab","Pmiss X (Lab) ", Pmx_nbins, Pmx_xmin, Pmx_xmax);         
  H_Pmy_lab = new TH1F("H_Pmy_Lab","Pmiss Y (Lab) ", Pmy_nbins, Pmy_xmin, Pmy_xmax);    
  H_Pmz_lab = new TH1F("H_Pmz_Lab","Pmiss Z (Lab) ", Pmz_nbins, Pmz_xmin, Pmz_xmax);    
  H_Pmx_q = new TH1F("H_Pmx_q","Pmiss X (w.r.t q-vec) ", Pmx_nbins, Pmx_xmin, Pmx_xmax);   
  H_Pmy_q = new TH1F("H_Pmy_q","Pmiss Y (w.r.t q-vec) ", Pmy_nbins, Pmy_xmin, Pmy_xmax); 
  H_Pmz_q = new TH1F("H_Pmz_q","Pmiss Z (w.r.t. q-vec) ", Pmz_nbins, Pmz_xmin, Pmz_xmax); 
  H_MM = new TH1F("H_MM","Missing Mass", MM_nbins, MM_xmin, MM_xmax);        
  H_MM2 = new TH1F("H_MM2","Missing Mass Squared", MM2_nbins, MM2_xmin, MM2_xmax); 
  H_Pf = new TH1F("H_Pf", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
  H_Ep = new TH1F("H_Ep", "Final Proton Energy", Ep_nbins, Ep_xmin, Ep_xmax);
  H_En = new TH1F("H_En", "Neutron Final Energy", En_nbins, En_xmin, En_xmax);
  H_Kp = new TH1F("H_Kp", "Final Proton Kin. Energy", Kp_nbins, Kp_xmin, Kp_xmax);     
  H_Kn = new TH1F("H_Kn", "Neutron Final Kin. Energy", Kn_nbins, Kn_xmin, Kn_xmax);  
  H_theta_prot = new TH1F("H_theta_prot", "Proton Scattering Angle", thp_nbins, thp_xmin, thp_xmax);
  H_theta_pq = new TH1F("H_theta_pq", "(Proton, q-vector) Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
  H_theta_nq = new TH1F("H_theta_nq", "(q-vector,Neutron) Angle, #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax);

  //Target Reconstruction (Hall Coord. System) 
  H_hx_tar = new TH1F("H_hx_tar", Form("%s x-Target (Lab)", h_arm_name.c_str()), xtar_nbins, xtar_xmin, xtar_xmax);
  H_hy_tar = new TH1F("H_hy_tar", Form("%s y_Target (Lab)", h_arm_name.c_str()), ytar_nbins, ytar_xmin, ytar_xmax);
  H_hz_tar = new TH1F("H_hz_tar", Form("%s z_Target (Lab)", h_arm_name.c_str()), ztar_nbins, ztar_xmin, ztar_xmax);
  
  H_ex_tar = new TH1F("H_ex_tar", Form("%s x-Target (Lab)", e_arm_name.c_str()), xtar_nbins, xtar_xmin, xtar_xmax);
  H_ey_tar = new TH1F("H_ey_tar", Form("%s y-Target (Lab)", e_arm_name.c_str()), ytar_nbins, ytar_xmin, ytar_xmax);
  H_ez_tar = new TH1F("H_ez_tar", Form("%s z-Target (Lab)", e_arm_name.c_str()), ztar_nbins, ztar_xmin, ztar_xmax);

  H_ztar_diff = new TH1F("H_ztar_diff", "Ztar Difference", ztar_nbins, ztar_xmin, ztar_xmax);

  //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  H_hytar = new TH1F("H_hytar", Form("%s  Y_{tar}", h_arm_name.c_str()), hytar_nbins, hytar_xmin, hytar_xmax);
  H_hxptar = new TH1F("H_hxptar", Form("%s  X'_{tar}", h_arm_name.c_str()), hxptar_nbins, hxptar_xmin, hxptar_xmax);
  H_hyptar = new TH1F("H_hyptar", Form("%s  Y'_{tar}", h_arm_name.c_str()), hyptar_nbins, hyptar_xmin, hyptar_xmax );
  H_hdelta = new TH1F("H_hdelta", Form("%s  Momentum Acceptance, #delta", h_arm_name.c_str()), hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
  //Hadron arm Focal Plane Quantities
  H_hxfp = new TH1F("H_hxfp", Form("%s  X_{fp}", h_arm_name.c_str()), hxfp_nbins, hxfp_xmin, hxfp_xmax);
  H_hyfp = new TH1F("H_hyfp", Form("%s  Y_{fp}", h_arm_name.c_str()), hyfp_nbins, hyfp_xmin, hyfp_xmax);
  H_hxpfp = new TH1F("H_hxpfp", Form("%s  X'_{fp}", h_arm_name.c_str()), hxpfp_nbins, hxpfp_xmin, hxpfp_xmax );
  H_hypfp = new TH1F("H_hypfp", Form("%s  Y'_{fp}", h_arm_name.c_str()), hypfp_nbins, hypfp_xmin, hypfp_xmax);

  
  //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  H_eytar = new TH1F("H_eytar", Form("%s Y_{tar}", e_arm_name.c_str()), eytar_nbins, eytar_xmin, eytar_xmax);
  H_exptar = new TH1F("H_exptar", Form("%s X'_{tar}", e_arm_name.c_str()), exptar_nbins, exptar_xmin, exptar_xmax);
  H_eyptar = new TH1F("H_eyptar", Form("%s Y'_{tar}", e_arm_name.c_str()), eyptar_nbins, eyptar_xmin, eyptar_xmax);
  H_edelta = new TH1F("H_edelta", Form("%s Momentum Acceptance, #delta", e_arm_name.c_str()), edelta_nbins, edelta_xmin, edelta_xmax);
  
  //Electron Arm Focal Plane Quantities
  H_exfp = new TH1F("H_exfp", Form("%s X_{fp}", e_arm_name.c_str()), exfp_nbins, exfp_xmin, exfp_xmax);
  H_eyfp = new TH1F("H_eyfp", Form("%s Y_{fp}", e_arm_name.c_str()), eyfp_nbins, eyfp_xmin, eyfp_xmax);
  H_expfp = new TH1F("H_expfp", Form("%s X'_{fp}", e_arm_name.c_str()), expfp_nbins, expfp_xmin, expfp_xmax);
  H_eypfp = new TH1F("H_eypfp", Form("%s Y'_{fp}", e_arm_name.c_str()), eypfp_nbins, eypfp_xmin, eypfp_xmax);
  
   //HMS / SHMS Collimator
  H_hXColl = new TH1F("H_hXColl", Form("%s  X Collimator", h_arm_name.c_str()), hXColl_nbins, hXColl_xmin, hXColl_xmax);
  H_hYColl = new TH1F("H_hYColl", Form("%s  Y Collimator", h_arm_name.c_str()), hYColl_nbins, hYColl_xmin, hYColl_xmax); 
  H_eXColl = new TH1F("H_eXColl", Form("%s X Collimator", e_arm_name.c_str()), eXColl_nbins, eXColl_xmin, eXColl_xmax);                                                                             
  H_eYColl = new TH1F("H_eYColl", Form("%s Y Collimator", e_arm_name.c_str()), eYColl_nbins, eYColl_xmin, eYColl_xmax);        

  //2D Collimator Histos
  H_hXColl_vs_hYColl = new TH2F("H_hXColl_vs_hYColl", Form("%s  Collimator", h_arm_name.c_str()), hYColl_nbins, hYColl_xmin, hYColl_xmax,  hXColl_nbins, hXColl_xmin, hXColl_xmax);
  H_eXColl_vs_eYColl = new TH2F("H_eXColl_vs_eYColl", Form("%s Collimator", e_arm_name.c_str()), eYColl_nbins, eYColl_xmin, eYColl_xmax, eXColl_nbins, eXColl_xmin, eXColl_xmax); 

  H_Em_vs_Pm = new TH2F("H_Em_vs_Pm", "E_{miss} vs. P_{miss}", Pm_nbins, -0.01, 0.2, Em_nbins, Em_xmin, Em_xmax);
  H_Em_nuc_vs_Pm = new TH2F("H_Em_nuc_vs_Pm", "E_{miss.nuc} vs. P_{miss}", Pm_nbins, -0.01, 0.2, Em_nbins, Em_xmin, Em_xmax);


  //Scaler Histograms
  H_bcmCurrent = new TH1F("H_bcmCurrent", "BCM Current", 100, 0, 100);
    

  cout << "Ending CreateHist() . . . " << endl;


}

	       	
//____________________________________________________________________________
void analyze::ReadScalerTree(string bcm_type="BCM4A")
{
  cout << "Calling ReadScalerTree() . . . " << endl;
  cout << Form("Using %s ", bcm_type.c_str()) << endl;

      //Read ROOTfile
      inROOT = new TFile(data_InputFileName, "READ");
      
      //Get the SHMS scaler tree (HMS Scaler tree should be identical. It is just used for cross check)
      scaler_tree = (TTree*)inROOT->Get("TSP");
      scal_entries = scaler_tree->GetEntries();
      evt_flag_bcm = new Int_t[scal_entries]; //store 0 or 1, to determine which scaler read passed cut
      scal_evt_num = new Int_t[scal_entries]; //store event associated with scaler read

      //SetBranchAddress
      scaler_tree->SetBranchAddress("evNumber", &Scal_evNum);
      scaler_tree->SetBranchAddress(Form("P.%s.scalerCharge", bcm_type.c_str()), &Scal_BCM_charge); 
      scaler_tree->SetBranchAddress(Form("P.%s.scalerCurrent", bcm_type.c_str()), &Scal_BCM_current); 
      scaler_tree->SetBranchAddress("P.1MHz.scalerTime",&Scal_time);
      scaler_tree->SetBranchAddress("P.S1X.scaler",&pS1X_scaler);  
      scaler_tree->SetBranchAddress("P.pTRIG1.scaler",&pTRIG1_scaler);
      scaler_tree->SetBranchAddress("P.pTRIG2.scaler",&pTRIG2_scaler);
      scaler_tree->SetBranchAddress("P.pTRIG3.scaler",&pTRIG3_scaler);
      scaler_tree->SetBranchAddress("P.pTRIG4.scaler",&pTRIG4_scaler);
      scaler_tree->SetBranchAddress("P.pTRIG6.scaler",&pTRIG6_scaler);
      scaler_tree->SetBranchAddress("P.EDTM.scaler",&pEDTM_scaler);

      cout << "Ending ReadScalerTree() . . . " << endl;

}

//____________________________________________________________________________
void analyze::ScalerEventLoop(Double_t current_thrs_bcm=5.)
{

  cout << "Calling ScalerEventLoop() . . . " << endl;

  //1ST PASS Scaler reads loop. to get maximum current
  for (int i = 0; i < scal_entries; i++) 
    {
      scaler_tree->GetEntry(i);
      H_bcmCurrent->Fill(Scal_BCM_current);

      cout << "ScalerEventLoop(PASS1): " << std::setprecision(2) << double(i) / scal_entries * 100. << "  % " << std::flush << "\r";


    }
  
  set_current =  H_bcmCurrent->GetXaxis()->GetBinCenter( H_bcmCurrent->GetMaximumBin() );  //set current corresponds to maximum bin content of bcm current hist
  
  //Scaler reads loop. ith scaler read
  for (int i = 0; i < scal_entries; i++) 
    {
      /*(NOTE: Each scaler read is associated with as specific event number
	as (scaler read 1-> event 1000,  scaler read 2 -> event 2300, ...)
	This means events up to 1000 correspond to scaler read 1, ...*/
      
      scaler_tree->GetEntry(i);
      
      //Set Event Flag to FALSE
      evt_flag_bcm[i] = 0;
      
      //Store event associated with scaler read
      scal_evt_num[i] = Scal_evNum;
      
      //Store Cumulative Quantities
      total_charge_bcm = Scal_BCM_charge;
      total_time = Scal_time;
      total_ps1x_scaler = pS1X_scaler;
      total_ptrig1_scaler = pTRIG1_scaler;
      total_ptrig2_scaler = pTRIG2_scaler;
      total_ptrig3_scaler = pTRIG3_scaler;
      total_ptrig4_scaler = pTRIG4_scaler;
      total_ptrig6_scaler = pTRIG6_scaler;
      total_pedtm_scaler = pEDTM_scaler;

    

      //Check If BCM Beam Current in Between Reads is Over Threshold
      if(abs(Scal_BCM_current-set_current)<current_thrs_bcm)
	{
	  
	  //Turn Event Flag ON, if beam current is within threshold
	  evt_flag_bcm[i] = 1;
	  
	  //Store Quantities that Passed the Current Threshold
	  total_time_bcm_cut = total_time_bcm_cut + (Scal_time - prev_time);
	  total_charge_bcm_cut = total_charge_bcm_cut + (Scal_BCM_charge - prev_charge_bcm);  
	  total_ps1x_scaler_bcm_cut = total_ps1x_scaler_bcm_cut + (pS1X_scaler-prev_ps1x_scaler);
	  total_ptrig1_scaler_bcm_cut = total_ptrig1_scaler_bcm_cut + (pTRIG1_scaler-prev_ptrig1_scaler);
	  total_ptrig2_scaler_bcm_cut = total_ptrig2_scaler_bcm_cut + (pTRIG2_scaler-prev_ptrig2_scaler);
	  total_ptrig3_scaler_bcm_cut = total_ptrig3_scaler_bcm_cut + (pTRIG3_scaler-prev_ptrig3_scaler);
	  total_ptrig4_scaler_bcm_cut = total_ptrig4_scaler_bcm_cut + (pTRIG4_scaler-prev_ptrig4_scaler);
	  total_ptrig6_scaler_bcm_cut = total_ptrig6_scaler_bcm_cut + (pTRIG6_scaler-prev_ptrig6_scaler);
	  total_pedtm_scaler_bcm_cut = total_pedtm_scaler_bcm_cut + (pEDTM_scaler - prev_pedtm_scaler);
	
	} //End BCM Current Cut
      
          //Previous Scaler Reads (Necessary to Take Average between S-1 and S scaler reads, to get values in between)
      prev_time = Scal_time;
      prev_charge_bcm = Scal_BCM_charge;
      prev_ps1x_scaler = pS1X_scaler;
      prev_ptrig1_scaler = pTRIG1_scaler;
      prev_ptrig2_scaler = pTRIG2_scaler;
      prev_ptrig3_scaler = pTRIG3_scaler;
      prev_ptrig4_scaler = pTRIG4_scaler;
      prev_ptrig6_scaler = pTRIG6_scaler;
      prev_pedtm_scaler = pEDTM_scaler;
            
      cout << "ScalerEventLoop(PASS2): " << std::setprecision(2) << double(i) / scal_entries * 100. << "  % " << std::flush << "\r";

    } //End Scaler Read Loop
   
  //Calculate Rates if Current Cut Passed (units of Hz)
  pS1XscalerRate_bcm_cut = total_ps1x_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG1scalerRate_bcm_cut = total_ptrig1_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG2scalerRate_bcm_cut = total_ptrig2_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG3scalerRate_bcm_cut = total_ptrig3_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG4scalerRate_bcm_cut = total_ptrig4_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG6scalerRate_bcm_cut = total_ptrig6_scaler_bcm_cut / total_time_bcm_cut;
  pEDTMscalerRate_bcm_cut =  total_pedtm_scaler_bcm_cut / total_time_bcm_cut;
  
  cout << "Ending ScalerEventLoop() . . . " << endl;


}

//____________________________________________________________________________
void analyze::ReadTree(string rad_flag="")
{
  cout << "Calling ReadTree() . . . " << endl;

  
  if(analysis=="data")
    {
      
      cout << "Analyzing DATA . . . " << endl;

      //Read ROOTfile
      inROOT = new TFile(data_InputFileName, "READ");
      
      //Get the data tree
      tree = (TTree*)inROOT->Get("T");
      nentries = tree->GetEntries();
      
      
      //---------------SetBranchAddress-----------------
      //Coincidence Time
      tree->SetBranchAddress("CTime.epCoinTime_ROC2", &epCoinTime);

      //Trigger Detector / Global Variables
      tree->SetBranchAddress("g.evtyp",&gevtyp);
      tree->SetBranchAddress("g.evnum",&gevnum);
      tree->SetBranchAddress("T.coin.pTRIG1_ROC2_tdcTimeRaw",&pTRIG1_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pTRIG2_ROC2_tdcTimeRaw",&pTRIG2_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pTRIG3_ROC2_tdcTimeRaw",&pTRIG3_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pTRIG4_ROC2_tdcTimeRaw",&pTRIG4_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pTRIG6_ROC2_tdcTimeRaw",&pTRIG6_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&pEDTM_tdcTimeRaw);

      //SHMS Detectors
      tree->SetBranchAddress("P.hgcer.npeSum",&pHGCER_npeSum);
      tree->SetBranchAddress("P.ngcer.npeSum",&pNGCER_npeSum);
      tree->SetBranchAddress("P.cal.etotnorm",&pCAL_etotnorm);    
      tree->SetBranchAddress("P.cal.etottracknorm",&pCAL_etottracknorm);    
      tree->SetBranchAddress("P.hod.betanotrack",&pBetanotrk);    
      tree->SetBranchAddress("P.hod.beta",&pBeta);    
      tree->SetBranchAddress("P.hod.goodscinhit",&pGoodScinHit);    
      tree->SetBranchAddress("P.dc.ntrack",&pdc_ntrack);    


      //HMS Detectors
      tree->SetBranchAddress("H.cer.npeSum",&hCER_npeSum);
      tree->SetBranchAddress("H.cal.etotnorm",&hCAL_etotnorm);      
      tree->SetBranchAddress("H.cal.etottracknorm",&hCAL_etottracknorm);      
      tree->SetBranchAddress("H.hod.betanotrack",&hBetanotrk);    
      tree->SetBranchAddress("H.hod.beta",&hBeta);    
      tree->SetBranchAddress("H.hod.goodscinhit",&hGoodScinHit);    
      tree->SetBranchAddress("H.dc.ntrack",&hdc_ntrack);


      //Electron Arm Focal Plane / Reconstructed Quantities 
      tree->SetBranchAddress(Form("%s.dc.x_fp",  eArm.c_str()), &e_xfp);
      tree->SetBranchAddress(Form("%s.dc.xp_fp", eArm.c_str()), &e_xpfp);
      tree->SetBranchAddress(Form("%s.dc.y_fp",  eArm.c_str()), &e_yfp);
      tree->SetBranchAddress(Form("%s.dc.yp_fp", eArm.c_str()), &e_ypfp);
      
      tree->SetBranchAddress(Form("%s.gtr.y",  eArm.c_str()), &e_ytar);
      tree->SetBranchAddress(Form("%s.gtr.ph", eArm.c_str()), &e_yptar);
      tree->SetBranchAddress(Form("%s.gtr.th", eArm.c_str()), &e_xptar);
      tree->SetBranchAddress(Form("%s.gtr.dp", eArm.c_str()), &e_delta);    
      tree->SetBranchAddress(Form("%s.gtr.p",  eArm.c_str()), &kf);

      //Hadron Arm Focal Plane / Reconstructed Quantities
      tree->SetBranchAddress(Form("%s.dc.x_fp",  hArm.c_str()), &h_xfp);
      tree->SetBranchAddress(Form("%s.dc.xp_fp", hArm.c_str()), &h_xpfp);
      tree->SetBranchAddress(Form("%s.dc.y_fp",  hArm.c_str()), &h_yfp);
      tree->SetBranchAddress(Form("%s.dc.yp_fp", hArm.c_str()), &h_ypfp);
      
      tree->SetBranchAddress(Form("%s.gtr.y",  hArm.c_str()), &h_ytar);
      tree->SetBranchAddress(Form("%s.gtr.ph", hArm.c_str()), &h_yptar);
      tree->SetBranchAddress(Form("%s.gtr.th", hArm.c_str()), &h_xptar);
      tree->SetBranchAddress(Form("%s.gtr.dp", hArm.c_str()), &h_delta);    
      tree->SetBranchAddress(Form("%s.gtr.p",  hArm.c_str()), &Pf);
      
      //Target Quantities (tarx, tary, tarz) in Hall Coord. System
      tree->SetBranchAddress(Form("%s.react.x", hArm.c_str()), &htar_x);
      tree->SetBranchAddress(Form("%s.react.y", hArm.c_str()), &htar_y);
      tree->SetBranchAddress(Form("%s.react.z", hArm.c_str()), &htar_z);
      
      tree->SetBranchAddress(Form("%s.react.x", eArm.c_str()), &etar_x);
      tree->SetBranchAddress(Form("%s.react.y", eArm.c_str()), &etar_y);
      tree->SetBranchAddress(Form("%s.react.z", eArm.c_str()), &etar_z);
      
      //Collimator
      tree->SetBranchAddress(Form("%s.extcor.xsieve", hArm.c_str()),&hXColl);
      tree->SetBranchAddress(Form("%s.extcor.ysieve", hArm.c_str()),&hYColl);
      tree->SetBranchAddress(Form("%s.extcor.xsieve", eArm.c_str()),&eXColl);
      tree->SetBranchAddress(Form("%s.extcor.ysieve", eArm.c_str()),&eYColl);


      //Primary Kinematics (electron kinematics)
      tree->SetBranchAddress(Form("%s.kin.primary.scat_ang_rad", eArm.c_str()),&theta_e);
      tree->SetBranchAddress(Form("%s.kin.primary.W", eArm.c_str()),&W);
      tree->SetBranchAddress(Form("%s.kin.primary.Q2", eArm.c_str()),&Q2);
      tree->SetBranchAddress(Form("%s.kin.primary.x_bj", eArm.c_str()),&X);
      tree->SetBranchAddress(Form("%s.kin.primary.nu", eArm.c_str()),&nu);
      tree->SetBranchAddress(Form("%s.kin.primary.q3m", eArm.c_str()),&q);
      tree->SetBranchAddress(Form("%s.kin.primary.th_q", eArm.c_str()),&th_q);
      
      //Secondary Kinematics (hadron kinematics)
      tree->SetBranchAddress(Form("%s.kin.secondary.emiss", hArm.c_str()),&Em);
      tree->SetBranchAddress(Form("%s.kin.secondary.emiss_nuc", hArm.c_str()),&Em_nuc);     
      tree->SetBranchAddress(Form("%s.kin.secondary.pmiss", hArm.c_str()),&Pm);
      tree->SetBranchAddress(Form("%s.kin.secondary.Prec_x", hArm.c_str()),&Pmx_lab);       
      tree->SetBranchAddress(Form("%s.kin.secondary.Prec_y", hArm.c_str()),&Pmy_lab);   
      tree->SetBranchAddress(Form("%s.kin.secondary.Prec_z", hArm.c_str()),&Pmz_lab);   
      tree->SetBranchAddress(Form("%s.kin.secondary.pmiss_x", hArm.c_str()),&Pmx_q);        
      tree->SetBranchAddress(Form("%s.kin.secondary.pmiss_y", hArm.c_str()),&Pmy_q);   
      tree->SetBranchAddress(Form("%s.kin.secondary.pmiss_z", hArm.c_str()),&Pmz_q);   
      tree->SetBranchAddress(Form("%s.kin.secondary.tx", hArm.c_str()),&Kp);                 
      tree->SetBranchAddress(Form("%s.kin.secondary.tb", hArm.c_str()),&Kn);                 
      tree->SetBranchAddress(Form("%s.kin.secondary.Mrecoil", hArm.c_str()),&M_recoil);      
      tree->SetBranchAddress(Form("%s.kin.secondary.Erecoil", hArm.c_str()),&E_recoil);      
      tree->SetBranchAddress(Form("%s.kin.secondary.th_xq", hArm.c_str()),&th_pq);            
      tree->SetBranchAddress(Form("%s.kin.secondary.th_bq", hArm.c_str()),&th_nq);            
      tree->SetBranchAddress(Form("%s.kin.secondary.ph_xq", hArm.c_str()),&ph_pq);                           
      tree->SetBranchAddress(Form("%s.kin.secondary.ph_bq", hArm.c_str()),&ph_nq);                            
      tree->SetBranchAddress(Form("%s.kin.secondary.xangle", hArm.c_str()),&xangle);         

    }

  //-----------------------------------------------------------------

  else if(analysis=="simc")
    {
      cout << "Analyzing SIMC . . . " << endl;

      //Read ROOTfile
  
      //If Doing Radiative Corrections, Read NON-RAD ROOTfile
      if(rad_flag=="do_rad_corr")
	{
	  cout << "Doing Radiative Corrections . . . " << endl;
	  
	  inROOT = new TFile(simc_InputFileName_norad, "READ");
	}
      //Read Radiative ROOTfile by default
      else{
	inROOT = new TFile(simc_InputFileName_rad, "READ");
      }
      
      //Get the tree
      tree = (TTree*)inROOT->Get("SNT");
      nentries = tree->GetEntries();

      
      //Electron Arm Focal Plane / Reconstructed Quantities 
      tree->SetBranchAddress("e_xfp",  &e_xfp);
      tree->SetBranchAddress("e_xpfp", &e_xpfp);
      tree->SetBranchAddress("e_yfp",  &e_yfp);
      tree->SetBranchAddress("e_ypfp", &e_ypfp);

      tree->SetBranchAddress("e_ytar",  &e_ytar);
      tree->SetBranchAddress("e_yptar", &e_yptar);
      tree->SetBranchAddress("e_xptar", &e_xptar);
      tree->SetBranchAddress("e_delta", &e_delta);
      tree->SetBranchAddress("e_pf",    &kf);

      //Hadron Arm Focal Plane / Reconstructed Quantities 
      tree->SetBranchAddress("h_xfp",  &h_xfp);
      tree->SetBranchAddress("h_xpfp", &h_xpfp);
      tree->SetBranchAddress("h_yfp",  &h_yfp);
      tree->SetBranchAddress("h_ypfp", &h_ypfp);
        
      tree->SetBranchAddress("h_ytar",  &h_ytar);
      tree->SetBranchAddress("h_yptar", &h_yptar);
      tree->SetBranchAddress("h_xptar", &h_xptar);
      tree->SetBranchAddress("h_delta", &h_delta);
      tree->SetBranchAddress("h_pf",    &Pf);


      //Target Quantities (tarx, tary, tarz) in Hall Coord. System
      tree->SetBranchAddress("tar_x", &tar_x);
      tree->SetBranchAddress("h_yv",  &htar_y);
      tree->SetBranchAddress("h_zv",  &htar_z);
      tree->SetBranchAddress("e_yv",  &etar_y);
      tree->SetBranchAddress("e_zv",  &etar_z);
 

      //Primary Kinematics (electron kinematics)
      tree->SetBranchAddress("theta_e", &theta_e);
      tree->SetBranchAddress("W", &W);
      tree->SetBranchAddress("Q2", &Q2);
      //Xbj needs to be calculated in the event loop
      tree->SetBranchAddress("nu", &nu);
      tree->SetBranchAddress("q", &q);
      //th_q needs to be calculated in the event loop
            

      //Secondary Kinematics (hadron kinematics)
      tree->SetBranchAddress("Em", &Em);
      tree->SetBranchAddress("Pm", &Pm);
      //Pmx_lab,Pmy_lab,Pmz_lab, Pmx_q, Pmy_q, Pmz_q 
      //are calculated externally in the EventLoop (using auxiliary methods from hcana)
      //Kp, Kn are calculated in the event loop
      //M_recoil, E_recoil (missing neutron mass and neutron recoil energy) are calculated in the event loop
      // tree->SetBranchAddress("theta_pq", &th_pq); th_nq is calculated in the event loop (externally using hcana methods)
      // tree->SetBranchAddress("phi_pq", &ph_pq);   ph_nq is calculated in the event loop (externally using hcana methods)
      // th_nq is calculated in the event loop
      // ph_nq is calculated in the event loop
      tree->SetBranchAddress("theta_p", &theta_p);

      //SIMC-SPECIFIC LEAF VARIABLES (Not all may be used here)
      tree->SetBranchAddress("Normfac",  &Normfac);
      tree->SetBranchAddress("h_deltai", &h_deltai);
      tree->SetBranchAddress("h_yptari", &h_yptari);
      tree->SetBranchAddress("h_xptari", &h_xptari);
      tree->SetBranchAddress("h_ytari",  &h_ytari);

      tree->SetBranchAddress("e_deltai", &e_deltai);
      tree->SetBranchAddress("e_yptari", &e_yptari);
      tree->SetBranchAddress("e_xptari", &e_xptari);
      tree->SetBranchAddress("e_ytari",  &e_ytari);
      
      tree->SetBranchAddress("epsilon",  &epsilon);
      tree->SetBranchAddress("corrsing", &corrsing);
      tree->SetBranchAddress("fry",      &fry);
      tree->SetBranchAddress("radphot",  &radphot);
      tree->SetBranchAddress("sigcc",    &sigcc);
      tree->SetBranchAddress("Weight",   &Weight);
      tree->SetBranchAddress("Jacobian", &Jacobian);
      tree->SetBranchAddress("Genweight",&Genweight);
      tree->SetBranchAddress("SF_weight", &SF_weight);
      tree->SetBranchAddress("Jacobian_corr", &Jacobian_corr);
      tree->SetBranchAddress("sig", &sig);
      tree->SetBranchAddress("sig_recon", &sig_recon);
      tree->SetBranchAddress("sigcc_recon", &sigcc_recon);
      tree->SetBranchAddress("coul_corr", &coul_corr);
      tree->SetBranchAddress("Ein", &Ein);
      tree->SetBranchAddress("theta_rq", &theta_rq);
      tree->SetBranchAddress("SF_weight_recon", &SF_weight_recon);
      tree->SetBranchAddress("h_Thf", &h_Thf);
      tree->SetBranchAddress("Ein_v", &Ein_v);
      tree->SetBranchAddress("Q2_v", &Q2_v);
      tree->SetBranchAddress("nu_v", &nu_v);
      tree->SetBranchAddress("q_lab_v", &q_lab_v);
      tree->SetBranchAddress("pm_v", &pm_v);
      tree->SetBranchAddress("pm_par_v", &pm_par_v);
      tree->SetBranchAddress("pf_v", &pf_v);
      tree->SetBranchAddress("Ep_v", &Ep_v);
      tree->SetBranchAddress("Ef_v", &Ef_v);
      tree->SetBranchAddress("probabs", &prob_abs);


    }
  
  cout << "Ending ReadTree() . . . " << endl;


} //End ReadTree()

//________________________________________________________________________________
void analyze::EventLoop()
{

  cout << "Calling EventLoop() . . . " << endl;

  //Call Methods to Set Collimator Graphical Cuts (In case it is used)
  CollimatorStudy();
  
    /*Loop over Events*/
  
  if(analysis=="data")
    {
      for(int ientry=0; ientry<nentries; ientry++)
	{
	  
	  tree->GetEntry(ientry);
	  
	  //--------Calculated Kinematic Varibales----------------
	  theta_p = xangle - theta_e;

	  En = Kn + MN;
	  Ep = Kp + MP;

	  M_recoil = sqrt(pow((nu + MD - Ep), 2) - Pm*Pm);
	  MM2 = M_recoil * M_recoil;

	  //-----If H(e,e'p)
	  if(reaction=="heep"){
	    M_recoil = sqrt(Em*Em - Pm*Pm);
	    MM2 = Em*Em - Pm*Pm;
	  }
	  
	  W2 = W*W;
	 
	  ztar_diff = htar_z - etar_z;

	  //---------------------Define Cuts---------------------------
	  
	  c_noedtm = pEDTM_tdcTimeRaw==0;
	  c_edtm = pEDTM_tdcTimeRaw>1500&&pEDTM_tdcTimeRaw<2000.;
	  c_ptrig6 = pTRIG6_tdcTimeRaw>0;
	  c_hgcerNpesum =  pHGCER_npeSum>0.7;
	  c_ngcerNpesum =  pNGCER_npeSum>0.5;
	  c_etotnorm = pCAL_etotnorm>0.6;
	  c_etottrknorm = pCAL_etottracknorm>0.6;
	   
	  //CUTS: e- tracking efficiency 
	  good_elec_should = pGoodScinHit==1.&&pBetanotrk>0.5&&pBetanotrk<1.5&&pCAL_etotnorm>0.6&&pNGCER_npeSum>0.5;
	  good_elec_did = good_elec_should&&pdc_ntrack>0.;
	  
	  //CUTS: h tracking efficiency
	  good_hadron_should = hGoodScinHit==1.&&hBetanotrk>0.5&&hBetanotrk<1.5&&hCAL_etotnorm<0.6&&hCAL_etotnorm>0.&&hCER_npeSum<0.5;
	  good_hadron_did = good_hadron_should&&hdc_ntrack>0.;
	  
	  

	  //Define DATA/SIMC CUTS (BETTER BE THE SAME CUTS as in SIMC!)
	  if(edelta_cut_flag){c_edelta = e_delta>edel_min&&e_delta<edel_max;} 
	  else{c_edelta=1;} //OFF means NO LIMITS on CUT (ALWAYS TRUE)
	  
	  if(hdelta_cut_flag){c_hdelta = h_delta>hdel_min&&h_delta<hdel_max;} 
	  else{c_hdelta=1;}
	  
	  if(W_cut_flag)     {c_W = W>=W_min&&W<=W_max;}                      
	  else{c_W=1;}
	  
	  if(Em_cut_flag) {
	   
	    if(reaction=="heep") { c_Em = Em>Em_min&&Em<Em_max; }
	    if(reaction=="deep") { c_Em = Em_nuc>Em_min&&Em_nuc<Em_max; }
	  }                   
	  else{c_Em=1;}
	  
	  if(ztar_diff_cut_flag){ c_ztarDiff = ztar_diff>ztarDiff_min&&ztar_diff<ztarDiff_max;}
	  else{c_ztarDiff=1;}

	  if(Q2_cut_flag) {c_Q2 = Q2>Q2_min&&Q2<Q2_max;}
	  else{c_Q2 = 1;}

	  if(MM_cut_flag) {c_MM = M_recoil>MM_min&&M_recoil<MM_max;}
	  else{c_MM = 1;}

	  if(thnq_cut_flag) {c_th_nq = th_nq>(thnq_min*dtr)&&th_nq<(thnq_max*dtr);}
	  else{c_th_nq = 1;}
	  
	  
	  //PID CUTS (SPECIFIC TO DATA)
	  if(shmsCal_cut_flag)    {c_shms_cal = pCAL_etottracknorm>shms_cal_min&&pCAL_etottracknorm<shms_cal_max;}                   
	  else{c_shms_cal=1;}
	  
	  if(coin_cut_flag)    {c_ctime = epCoinTime>ctime_min&&epCoinTime<ctime_max;}                   
	  else{c_ctime=1;}
	  
	  //Collimator CUTS
	  if(hmsCollCut_flag)  { hmsColl_Cut =  hms_Coll_gCut->IsInside(hYColl, hXColl);}
	  else{hmsColl_Cut=1;}
	  
	  if(shmsCollCut_flag) { shmsColl_Cut =  shms_Coll_gCut->IsInside(eYColl, eXColl);}
	  else{shmsColl_Cut=1;}
	  
	  
	  base_cuts = c_edelta&&c_hdelta&&c_W&&c_Em&&c_ztarDiff&&c_Q2&&c_MM&&c_th_nq;
	  pid_cuts = c_shms_cal&&c_ctime;
	  
	  //----------------------------END DEFINE CUTS-------------------------------------
	  
	  //Count Accepted EDTM events (no current cut)
	  if(c_edtm){ total_pedtm_accp++;}
	  //Count Accepted pTRIG6 events (no current cut)
	  if(c_ptrig6){total_ptrig6_accp++;}
	  
	  //----------------------Check If BCM Current is within limits------------------------
	  if(evt_flag_bcm[scal_read]==1)
	    {
	      
	      //Count Accepted EDTM events
	      if(c_edtm){ total_pedtm_accp_bcm_cut++;}
	      
	      //Count Accepted pTRIG6 events (without EDTM)
	      if(c_ptrig6&&c_noedtm){ total_ptrig6_accp_bcm_cut++;}
	      
	      
	      //REQUIRE "NO EDTM" CUT TO FILL DATA HISTOGRAMS
	      if(c_noedtm) 
		{
		  
		  //Calculate Electron Tracking Efficiency
		  if(good_elec_did){ e_did++;}
		  if(good_elec_should){ e_should++; }
		  
		  //Calculate Hadron Tracking Efficiency
		  if(good_hadron_did){ h_did++;}
		  if(good_hadron_should){ h_should++; }
		  
		  //----------------------Fill DATA Histograms-----------------------
		  
		  if(base_cuts&&pid_cuts&&hmsColl_Cut&&shmsColl_Cut)
		    {
		      //Trigger Detector
		      H_ctime->Fill(epCoinTime);
		      
		      //HMS Detectors
		      H_hbeta->Fill(hBeta);
		      H_hcer->Fill(hCER_npeSum);
		      H_hcal->Fill(hCAL_etotnorm);
		      
		      
		      //SHMS Detectors
		      H_pbeta->Fill(pBeta);
		      H_pngcer->Fill(pNGCER_npeSum);
		      H_pcal_etotnorm->Fill(pCAL_etotnorm);
		      H_pcal_etotTrkNorm->Fill(pCAL_etottracknorm);
		      
		      
		      //Primary (electron) Kinematics
		      H_Q2->Fill(Q2);
		      H_omega->Fill(nu);
		      H_W->Fill(W);
		      H_W2->Fill(W2);
		      H_xbj->Fill(X);
		      H_kf->Fill(kf);
		      H_theta_q->Fill(th_q/dtr);
		      H_q->Fill(q);
		      H_theta_elec->Fill(theta_e/dtr);
		      
		      //Secondary (Hadron) Kinematics
		      H_Em->Fill(Em);
		      H_Em_nuc->Fill(Em_nuc);
		      H_Pm->Fill(Pm);
		      H_Pmx_lab->Fill(Pmx_lab);
		      H_Pmy_lab->Fill(Pmy_lab);
		      H_Pmz_lab->Fill(Pmz_lab);
		      H_Pmx_q->Fill(Pmx_q);
		      H_Pmy_q->Fill(Pmy_q);
		      H_Pmz_q->Fill(Pmz_q);
		      H_MM->Fill(M_recoil);
		      H_MM2->Fill(MM2); 
		      H_Pf->Fill(Pf);
		      H_Ep->Fill(Ep);
		      H_En->Fill(En);
		      H_Kp->Fill(Kp); 
                      H_Kn->Fill(Kn);  
		      H_theta_prot->Fill(theta_p/dtr);
		      H_theta_pq->Fill(th_pq/dtr);
		      H_theta_nq->Fill(th_nq/dtr);
		      
		      //Target Reconstruction (Hall Coord. System)
		      H_hx_tar->Fill(htar_x);
		      H_hy_tar->Fill(htar_y);
		      H_hz_tar->Fill(htar_z);
		      H_ex_tar->Fill(etar_x);
		      H_ey_tar->Fill(etar_y);
		      H_ez_tar->Fill(etar_z);
		      H_ztar_diff->Fill(ztar_diff);
		      
		      //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta) 
		      H_hytar->Fill(h_ytar);
		      H_hxptar->Fill(h_xptar);
		      H_hyptar->Fill(h_yptar);
		      H_hdelta->Fill(h_delta);
		      
		      //Hadron arm Focal Plane Quantities
		      H_hxfp->Fill(h_xfp);
		      H_hyfp->Fill(h_yfp);
		      H_hxpfp->Fill(h_xpfp);
		      H_hypfp->Fill(h_ypfp);
		      
		      //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
		      H_eytar->Fill(e_ytar);
		      H_exptar->Fill(e_xptar);
		      H_eyptar->Fill(e_yptar);
		      H_edelta->Fill(e_delta);
		      
		      //Electron Arm Focal Plane Quantities
		      H_exfp->Fill(e_xfp);
		      H_eyfp->Fill(e_yfp);
		      H_expfp->Fill(e_xpfp);
		      H_eypfp->Fill(e_ypfp);
		      
		      //HMS / SHMS Collimator
		      H_hXColl->Fill(hXColl);
		      H_hYColl->Fill(hYColl);
		      H_eXColl->Fill(eXColl);
		      H_eYColl->Fill(eYColl);
		      
		      //2D Collimator Histos
		      H_hXColl_vs_hYColl->Fill(hYColl, hXColl);
		      H_eXColl_vs_eYColl->Fill(eYColl, eXColl);

		      H_Em_vs_Pm->Fill(Pm, Em);
		      H_Em_nuc_vs_Pm->Fill(Pm, Em_nuc);


		    } //END CUTS
		  
		  //-------------------End Fill DATA Histograms----------------------
		  
		  
		  
		} //END "NO EDTM" CUT	      
	    }
	  //----------------------------END BCM CURRENT CUT------------------------------------
	  
	  
	  //Increment Scaler Read if event == scaler_evt_perlimit for that scaler read
	  if(gevnum==scal_evt_num[scal_read]){ scal_read++;}
	  
	  
	  cout << "EventLoop: " << std::setprecision(2) << double(ientry) / nentries * 100. << "  % " << std::flush << "\r";
	  
	} // END EVENT LOOP
      
    }
  
  else if(analysis=="simc")
    {

      for(int ientry=0; ientry<nentries; ientry++)
	{
	  
	  tree->GetEntry(ientry);
	  
	  //SIMC FullWeight
	  FullWeight = Normfac * Weight * prob_abs / nentries;
	  
	  //--------Calculated Kinematic Varibales----------------
	  
	  //Convert MeV to GeV
	  Ein = Ein / 1000.;     //incident beam energy
	  kf = kf / 1000.;       //final electron momentum
	  Pf = Pf / 1000.;       //final proton momentum
	  
	  ki = sqrt(Ein*Ein - me*me);        //initial electron momentum
	  
	  //redefine
	  Ep = sqrt(MP*MP + Pf*Pf);
	  En = sqrt(MN*MN + Pm*Pm);

	  Kp = Ep - MP;                                                                    
          Kn = En - MN;

	  //Em = nu - Kp - Kn;

	  M_recoil = sqrt( pow(nu+MD-Ep,2) - Pm*Pm );  //recoil mass (neutron missing mass)
	  MM2 = M_recoil * M_recoil;
	  
	  //-----If H(e,e'p)
	  if(reaction=="heep"){
	    M_recoil = sqrt(Em*Em - Pm*Pm);
	    MM2 = Em*Em - Pm*Pm;
	  }
	  //----------
	  
	  W2 = W*W;

	  //Use hcana formula to re-define HMS/SHMS Ztarget
	  htar_z = ((h_ytar + h_yMisPoint)-xBPM*(cos(h_th*dtr)-h_yptar*sin(h_th*dtr)))/(-sin(h_th*dtr)-h_yptar*cos(h_th*dtr));
	  etar_z = ((e_ytar - e_yMisPoint)-xBPM*(cos(e_th*dtr)-e_yptar*sin(e_th*dtr)))/(-sin(e_th*dtr)-e_yptar*cos(e_th*dtr));

	  ztar_diff = htar_z - etar_z;

	  

	  X = Q2 / (2.*MP*nu);                           
	  th_q = acos( (ki - kf*cos(theta_e))/q );       

      	  
	  //---------------------------------------------------
	  
	  //---------Calculate Pmx, Pmy, Pmz in the Lab, and in the q-system----------------
	  
	  //Calculate electron final momentum 3-vector
	  SetCentralAngles(e_th, e_ph);
	  TransportToLab(kf, e_xptar, e_yptar, kf_vec);
 
	  //Calculate 4-Vectors
	  fP0.SetXYZM(0.0, 0.0, ki, me);  //set initial e- 4-momentum
	  fP1.SetXYZM(kf_vec.X(), kf_vec.Y(), kf_vec.Z(), me);  //set final e- 4-momentum
	  fA.SetXYZM(0.0, 0.0, 0.0, tgt_mass );  //Set initial target at rest
	  fQ = fP0 - fP1;
	  fA1 = fA + fQ;   //final target (sum of final hadron four momenta)

	  //Get Detected Particle 4-momentum
	  SetCentralAngles(h_th, h_ph);
	  TransportToLab(Pf, h_xptar, h_yptar, Pf_vec);
	  fX.SetVectM(Pf_vec, MP);       //SET FOUR VECTOR OF detected particle
	  fB = fA1 - fX;                 //4-MOMENTUM OF UNDETECTED PARTICLE 

	  Pmx_lab = fB.X();
	  Pmy_lab = fB.Y(); 
	  Pmz_lab = fB.Z(); 
	  
	  //Pm = sqrt(Pmx_lab*Pmx_lab + Pmy_lab*Pmy_lab + Pmz_lab*Pmz_lab);
	  
	  //--------Rotate the recoil system from +z to +q-------
	  qvec = fQ.Vect();
	  kfvec = fP1.Vect();
	  
	  rot_to_q.SetZAxis( qvec, kfvec).Invert();
	  
	  xq = fX.Vect();
	  bq = fB.Vect();
	  
	  xq *= rot_to_q;
	  bq *= rot_to_q;

	  //Calculate Angles of q relative to x(detected proton) and b(recoil neutron)
	  th_pq = xq.Theta();   //"theta_pq"                                       
	  ph_pq   = xq.Phi();     //"out-of-plane angle", "phi_pq"                                                                    
	  th_nq = bq.Theta();   // theta_nq                                                                                                     
	  ph_nq   = bq.Phi();     //phi_nq

	  

	  p_miss_q = -bq;
	  
	  //Missing Momentum Components in the q-frame
	  Pmz_q = p_miss_q.Z();   //parallel component to +z
	  Pmx_q = p_miss_q.X();   //in-plane perpendicular component to +z
	  Pmy_q = p_miss_q.Y();   //out-of-plane component (Oop)
	  
	  
	  //--------------------------------------------------------------------------------
	  
	  //----------------------SIMC Collimator-------------------------
	  
	  htarx_corr = tar_x - h_xptar*htar_z*cos(h_th*dtr);
	  etarx_corr = tar_x - e_xptar*etar_z*cos(e_th*dtr);  
	  
	  
	  //Define Collimator (same as in HCANA)
	  hXColl = htarx_corr + h_xptar*168.;   //in cm
	  hYColl = h_ytar + h_yptar*168.;
	  eXColl = etarx_corr + e_xptar*253.;
	  eYColl = e_ytar + e_yptar*253.-(0.019+40.*.01*0.052)*e_delta+(0.00019+40*.01*.00052)*e_delta*e_delta; //correct for HB horizontal bend
	  
	  
	  //--------------------------------------------------------------
	  
	  //Define DATA/SIMC CUTS (BETTER BE THE SAME CUTS!)
	  if(edelta_cut_flag){c_edelta = e_delta>edel_min&&e_delta<edel_max;} 
	  else{c_edelta=1;} //OFF means NO LIMITS on CUT (ALWAYS TRUE)
	      
	  if(hdelta_cut_flag){c_hdelta = h_delta>hdel_min&&h_delta<hdel_max;} 
	  else{c_hdelta=1;}
	  
	  if(W_cut_flag)     {c_W = W>=W_min&&W<=W_max;}                      
	  else{c_W=1;}
	  
	  if(Em_cut_flag)    {c_Em = Em>Em_min&&Em<Em_max;}                   
	  else{c_Em=1;}

	  if(ztar_diff_cut_flag){ c_ztarDiff = ztar_diff>ztarDiff_min&&ztar_diff<ztarDiff_max;}
	  else{c_ztarDiff=1;}

	  if(Q2_cut_flag) {c_Q2 = Q2>Q2_min&&Q2<Q2_max;}
	  else{c_Q2 = 1;}
	  
	  if(MM_cut_flag) {c_MM = M_recoil>MM_min&&M_recoil<MM_max;}
	  else{c_MM = 1;}
	
	  if(thnq_cut_flag) { c_th_nq = th_nq>(thnq_min*dtr)&&th_nq<(thnq_max*dtr);}
	  else{c_th_nq = 1;}
	  
	
	  //Collimator CUTS
	  if(hmsCollCut_flag)  { hmsColl_Cut =  hms_Coll_gCut->IsInside(hYColl, hXColl);}
	  else{hmsColl_Cut=1;}
	  
	  if(shmsCollCut_flag) { shmsColl_Cut =  shms_Coll_gCut->IsInside(eYColl, eXColl);}
	  else{shmsColl_Cut=1;}
	  
	  
	  base_cuts = c_edelta&&c_hdelta&&c_W&&c_Em&&c_ztarDiff&&c_Q2&&c_MM&&c_th_nq;
	  
	  
	  //----------------------------END DEFINE CUTS-------------------------------------
	  
	  
	  
	  //-------------------------------Fill SIMC Histograms--------------------------
	  
	  if(base_cuts&&hmsColl_Cut&&shmsColl_Cut){

	    //Primary (electron) Kinematics
	    H_Q2->Fill(Q2, FullWeight);
	    H_omega->Fill(nu, FullWeight);
	    H_W->Fill(W, FullWeight);
	    H_W2->Fill(W2, FullWeight);
	    H_xbj->Fill(X, FullWeight);
	    H_kf->Fill(kf, FullWeight);
	    H_theta_q->Fill(th_q/dtr, FullWeight);
	    H_q->Fill(q, FullWeight);
	    H_theta_elec->Fill(theta_e/dtr, FullWeight);
	    
	    //Secondary (Hadron) Kinematics
	    H_Em->Fill(Em, FullWeight);
	    H_Pm->Fill(Pm, FullWeight);
	    H_Pmx_lab->Fill(Pmx_lab, FullWeight);
	    H_Pmy_lab->Fill(Pmy_lab, FullWeight);
	    H_Pmz_lab->Fill(Pmz_lab, FullWeight);
	    H_Pmx_q->Fill(Pmx_q, FullWeight);
	    H_Pmy_q->Fill(Pmy_q, FullWeight);
	    H_Pmz_q->Fill(Pmz_q, FullWeight);
	    H_MM->Fill(M_recoil, FullWeight);
	    H_MM2->Fill(MM2, FullWeight); 
	    H_Pf->Fill(Pf, FullWeight);
	    H_Ep->Fill(Ep, FullWeight);
	    H_En->Fill(En, FullWeight);
	    H_Kp->Fill(Kp, FullWeight); 
	    H_Kn->Fill(Kn, FullWeight);  
	    H_theta_prot->Fill(theta_p/dtr, FullWeight);
	    H_theta_pq->Fill(th_pq/dtr, FullWeight);
	    H_theta_nq->Fill(th_nq/dtr, FullWeight);
	    
	    //Target Reconstruction (Hall Coord. System)
	    H_hx_tar->Fill(tar_x, FullWeight);
	    H_hy_tar->Fill(htar_y, FullWeight);
	    H_hz_tar->Fill(htar_z, FullWeight);
	    H_ex_tar->Fill(tar_x, FullWeight);
	    H_ey_tar->Fill(etar_y, FullWeight);
	    H_ez_tar->Fill(etar_z, FullWeight);
	    H_ztar_diff->Fill(ztar_diff, FullWeight);
	    
	    //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta) 
	    H_hytar->Fill(h_ytar, FullWeight);
	    H_hxptar->Fill(h_xptar, FullWeight);
	    H_hyptar->Fill(h_yptar, FullWeight);
	    H_hdelta->Fill(h_delta, FullWeight);
		
	    //Hadron arm Focal Plane Quantities
	    H_hxfp->Fill(h_xfp, FullWeight);
	    H_hyfp->Fill(h_yfp, FullWeight);
	    H_hxpfp->Fill(h_xpfp, FullWeight);
	    H_hypfp->Fill(h_ypfp, FullWeight);
	    
	    //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
	    H_eytar->Fill(e_ytar, FullWeight);
	    H_exptar->Fill(e_xptar, FullWeight);
	    H_eyptar->Fill(e_yptar, FullWeight);
	    H_edelta->Fill(e_delta, FullWeight);
	    
	    //Electron Arm Focal Plane Quantities
	    H_exfp->Fill(e_xfp, FullWeight);
	    H_eyfp->Fill(e_yfp, FullWeight);
	    H_expfp->Fill(e_xpfp, FullWeight);
	    H_eypfp->Fill(e_ypfp, FullWeight);
	    
	    //HMS / SHMS Collimator
	    H_hXColl->Fill(hXColl, FullWeight);
	    H_hYColl->Fill(hYColl, FullWeight);
	    H_eXColl->Fill(eXColl, FullWeight);
	    H_eYColl->Fill(eYColl, FullWeight);
	    
	    //2D Collimator Histos
	    H_hXColl_vs_hYColl->Fill(hYColl, hXColl, FullWeight);
	    H_eXColl_vs_eYColl->Fill(eYColl, eXColl, FullWeight);
	    
	    H_Em_vs_Pm->Fill(Pm, Em, FullWeight);

	    
	    
	    cout << "EventLoop: " << std::setprecision(2) << double(ientry) / nentries * 100. << "  % " << std::flush << "\r";
	    
	  } //END CUTS
	  
	  //-----------------------------END Fill SIMC Histograms------------------------
	  
	} //End Event Loop
      
    } //End "SIMC"

    cout << "Ending EventLoop() . . . " << endl;

} //Ending EventLoop()

//____________________________________________________________________________
void analyze::CalcEff()
{

  cout << "Calling CalcEff() . . . " << endl;
  
  /*Method to calculate tracking efficiencies, live time, and total charge*/

  //Calculate Average BCM Current                                                                                                       
  avg_current_bcm_cut = total_charge_bcm_cut / total_time_bcm_cut; //uA                                                                 
                                                                                                                                   
  //Convert charge from uC to mC                                                                                                 
  total_charge_bcm_cut = total_charge_bcm_cut / 1000.; 

  //COnvert SHMS Rates from Hz to kHz  (Keep EDTM, HMS and coin. rates in units of Hz)
  pS1XscalerRate_bcm_cut = pS1XscalerRate_bcm_cut / 1000.;
  pTRIG1scalerRate_bcm_cut = pTRIG1scalerRate_bcm_cut / 1000.;
  pTRIG2scalerRate_bcm_cut = pTRIG2scalerRate_bcm_cut / 1000.;
  pTRIG3scalerRate_bcm_cut = pTRIG3scalerRate_bcm_cut / 1000.;


  //Calculate  Live Time                                                                                                                        
  cpuLT =  total_ptrig6_accp_bcm_cut / (total_ptrig6_scaler_bcm_cut-total_pedtm_scaler_bcm_cut);                                      
  cpuLT_err = sqrt(total_ptrig6_accp_bcm_cut) / (total_ptrig6_scaler_bcm_cut-total_pedtm_scaler_bcm_cut);                                 
  tLT =  total_pedtm_accp_bcm_cut / total_pedtm_scaler_bcm_cut;  

  //Calculate Tracking Efficiency                                                                                                
  eTrkEff = e_did / e_should; 
  eTrkEff_err = sqrt(e_should-e_did) / e_should;                                                            
                                                                                    
  //Hadron TRacking Efficiency                                                                                                                 
  hTrkEff = h_did / h_should;                                                                                                                  
  hTrkEff_err = sqrt(h_should-h_did) / h_should;      

  cout << "Ending CalcEff() . . . " << endl;


} //End CalcEff();

//____________________________________________________________________________
void analyze::ApplyWeight()
{
  //Method to apply correction to the data Yield by scaling the Filled Histograms
  //Corrections applied: total_charge, total live time, tracking efficiencies, proton absorption, target boiling corrections 
    
  cout << "Calling ApplyWeight() . . . " << endl; 
  
  if(analysis=="data"){

    //Target Boiling Slopes
    LH2_slope = 0.0006;
    LD2_slope = 0.0008;
    
    if(reaction=="heep"){
      tgtBoil_corr = (1.-LH2_slope * avg_current_bcm_cut);
    }
    
    if(reaction=="deep"){
      tgtBoil_corr = (1.-LD2_slope * avg_current_bcm_cut);
    }
    
    //Proton Absorption
    pAbs_corr = 0.9534;
    
    FullWeight = 1. / (total_charge_bcm_cut * eTrkEff * hTrkEff * tLT * pAbs_corr * tgtBoil_corr );
    
    cout << "total charge = " << setprecision(5) << total_charge_bcm_cut << " mC " << endl;
    cout << "e- trk eff = "   << setprecision(5) << eTrkEff << endl;
    cout << "h trk eff = "    << setprecision(5) << hTrkEff << endl;
    cout << "tLT  = "         << setprecision(5) << tLT << endl;
    cout << "pAbs  = "        << setprecision(5) << pAbs_corr << endl;
    cout << "tgtBoil = "      << setprecision(5) << tgtBoil_corr << endl;
    
    //Scale The DATA Histograms by Full Weight
    
    //Trigger Detector
    H_ctime->Scale(FullWeight);
    
    //HMS Detectors
    H_hbeta->Scale(FullWeight);
    H_hcer->Scale(FullWeight);
    H_hcal->Scale(FullWeight);
    
    //SHMS Detectors
    H_pbeta->Scale(FullWeight);
    H_pngcer->Scale(FullWeight);
    H_pcal_etotnorm->Scale(FullWeight);
    H_pcal_etotTrkNorm->Scale(FullWeight);

    //Initialize DATA/SIMC Histograms
    
    //Primary (electron) Kinematics
    H_Q2->Scale(FullWeight);
    H_omega->Scale(FullWeight);
    H_W->Scale(FullWeight);
    H_W2->Scale(FullWeight);
    H_xbj->Scale(FullWeight);
    H_kf->Scale(FullWeight);
    H_theta_q->Scale(FullWeight);
    H_q->Scale(FullWeight);
    H_theta_elec->Scale(FullWeight);
    
    //Secondary (Hadron) Kinematics
    H_Em->Scale(FullWeight);
    H_Em_nuc->Scale(FullWeight);
    H_Pm->Scale(FullWeight);
    H_Pmx_lab->Scale(FullWeight);
    H_Pmy_lab->Scale(FullWeight);
    H_Pmz_lab->Scale(FullWeight);
    H_Pmx_q->Scale(FullWeight);
    H_Pmy_q->Scale(FullWeight);
    H_Pmz_q->Scale(FullWeight);
    H_MM->Scale(FullWeight);
    H_MM2->Scale(FullWeight);
    H_Pf->Scale(FullWeight);
    H_Ep->Scale(FullWeight);
    H_En->Scale(FullWeight);
    H_Kp->Scale(FullWeight);                                                                                                          
    H_Kn->Scale(FullWeight); 
    H_theta_prot->Scale(FullWeight);
    H_theta_pq->Scale(FullWeight);
    H_theta_nq->Scale(FullWeight);
    
    //Target Reconstruction Histos
    H_hx_tar->Scale(FullWeight);
    H_hy_tar->Scale(FullWeight);
    H_hz_tar->Scale(FullWeight);
    
    H_ex_tar->Scale(FullWeight);
    H_ey_tar->Scale(FullWeight);
    H_ez_tar->Scale(FullWeight);
    
    H_ztar_diff->Scale(FullWeight);
    
    //Hadron Arm Recon. / Focal Plane Histos
    H_hytar->Scale(FullWeight);
    H_hxptar->Scale(FullWeight);
    H_hyptar->Scale(FullWeight);
    H_hdelta->Scale(FullWeight);
    
    H_hxfp->Scale(FullWeight);
    H_hyfp->Scale(FullWeight);
    H_hxpfp->Scale(FullWeight);
    H_hypfp->Scale(FullWeight);
    
    //Electron Arm Recon. / Focal Plane Histos
    H_eytar->Scale(FullWeight);
    H_exptar->Scale(FullWeight);
    H_eyptar->Scale(FullWeight);
    H_edelta->Scale(FullWeight);
    
    H_exfp->Scale(FullWeight);
    H_eyfp->Scale(FullWeight);
    H_expfp->Scale(FullWeight);
    H_eypfp->Scale(FullWeight);
    
    //HMS/SHMS Collimator
    H_hXColl->Scale(FullWeight);
    H_hYColl->Scale(FullWeight);
    H_eXColl->Scale(FullWeight);
    H_eYColl->Scale(FullWeight);
    
    //2D Collimator Histos
    H_hXColl_vs_hYColl->Scale(FullWeight);
    H_eXColl_vs_eYColl->Scale(FullWeight);
    
    H_Em_vs_Pm->Scale(FullWeight);

    //Initialize Scaler Histograms
    H_bcmCurrent->Scale(FullWeight);
    
  } //end DATA

  cout << "Ending ApplyWeight() . . . " << endl; 


}//End Apply Weight

//____________________________________________________________________________
void analyze::WriteHist(string rad_flag="")
{

  /* Write Histograms to a ROOTfile */

  cout << "Calling WriteHist() . . . " << endl;

  if(analysis=="data")
    {
      //Create output ROOTfile
      outROOT = new TFile(data_OutputFileName, "RECREATE");
      
      //Trigger Detector
      H_ctime->Write();
      
      //HMS Detectors
      H_hbeta->Write();
      H_hcer->Write();
      H_hcal->Write();
      
      //SHMS Detectors
      H_pbeta->Write();
      H_pngcer->Write();
      H_pcal_etotnorm->Write();
      H_pcal_etotTrkNorm->Write();

      //Primary (electron) Kinematics
      H_Q2->Write();
      H_omega->Write();
      H_W->Write();
      H_W2->Write();
      H_xbj->Write();
      H_kf->Write();
      H_theta_q->Write();
      H_q->Write();
      H_theta_elec->Write();
      
      //Secondary (Hadron) Kinematics
      H_Em->Write();
      H_Em_nuc->Write();
      H_Pm->Write();
      H_Pmx_lab->Write();
      H_Pmy_lab->Write();
      H_Pmz_lab->Write();
      H_Pmx_q->Write();
      H_Pmy_q->Write();
      H_Pmz_q->Write();
      H_MM->Write();
      H_MM2->Write();
      H_Pf->Write();
      H_Ep->Write();
      H_En->Write();
      H_Kp->Write(); 
      H_Kn->Write(); 
      H_theta_prot->Write();
      H_theta_pq->Write();
      H_theta_nq->Write();
      
      //Target Reconstruction Histos
      H_hx_tar->Write();
      H_hy_tar->Write();
      H_hz_tar->Write();
      
      H_ex_tar->Write();
      H_ey_tar->Write();
      H_ez_tar->Write();
      
      H_ztar_diff->Write();
      
      //Hadron Arm Recon. / Focal Plane Histos
      H_hytar->Write();
      H_hxptar->Write();
      H_hyptar->Write();
      H_hdelta->Write();
      
      H_hxfp->Write();
      H_hyfp->Write();
      H_hxpfp->Write();
      H_hypfp->Write();
      
      //Electron Arm Recon. / Focal Plane Histos
      H_eytar->Write();
      H_exptar->Write();
      H_eyptar->Write();
      H_edelta->Write();
      
      H_exfp->Write();
      H_eyfp->Write();
      H_expfp->Write();
      H_eypfp->Write();
      
      //HMS/SHMS Collimator
      H_hXColl->Write();
      H_hYColl->Write();
      H_eXColl->Write();
      H_eYColl->Write();
      
      //2D Collimator Histos
      H_hXColl_vs_hYColl->Write();
      H_eXColl_vs_eYColl->Write();
      
      H_Em_vs_Pm->Write();
      H_Em_nuc_vs_Pm->Write();


      H_bcmCurrent->Write();
    
    }
  
  else if(analysis=="simc")
    {
      //Create output ROOTfile
     
      //If Doing Radiative Corrections, Write NON-RAD SIMC ROOTfile Histograms
      if(rad_flag=="do_rad_corr"){
	outROOT = new TFile(simc_OutputFileName_norad, "RECREATE");
      }
      //By Default, Write Radiated SIMC ROOTfile Histograms
      else{
	outROOT = new TFile(simc_OutputFileName_rad, "RECREATE");
      }
      
      //Primary (electron) Kinematics
      H_Q2->Write();
      H_omega->Write();
      H_W->Write();
      H_W2->Write();
      H_xbj->Write();
      H_kf->Write();
      H_theta_q->Write();
      H_q->Write();
      H_theta_elec->Write();
      
      //Secondary (Hadron) Kinematics
      H_Em->Write();
      H_Pm->Write();
      H_Pmx_lab->Write();
      H_Pmy_lab->Write();
      H_Pmz_lab->Write();
      H_Pmx_q->Write();
      H_Pmy_q->Write();
      H_Pmz_q->Write();
      H_MM->Write();
      H_MM2->Write();
      H_Pf->Write();
      H_Ep->Write();
      H_En->Write();
      H_Kp->Write();          
      H_Kn->Write();  
      H_theta_prot->Write();
      H_theta_pq->Write();
      H_theta_nq->Write();
      
      //Target Reconstruction Histos
      H_hx_tar->Write();
      H_hy_tar->Write();
      H_hz_tar->Write();
      
      H_ex_tar->Write();
      H_ey_tar->Write();
      H_ez_tar->Write();
      
      H_ztar_diff->Write();
      
      //Hadron Arm Recon. / Focal Plane Histos
      H_hytar->Write();
      H_hxptar->Write();
      H_hyptar->Write();
      H_hdelta->Write();
      
      H_hxfp->Write();
      H_hyfp->Write();
      H_hxpfp->Write();
      H_hypfp->Write();
      
      //Electron Arm Recon. / Focal Plane Histos
      H_eytar->Write();
      H_exptar->Write();
      H_eyptar->Write();
      H_edelta->Write();
      
      H_exfp->Write();
      H_eyfp->Write();
      H_expfp->Write();
      H_eypfp->Write();
      
      //HMS/SHMS Collimator
      H_hXColl->Write();
      H_hYColl->Write();
      H_eXColl->Write();
      H_eYColl->Write();
      
      //2D Collimator Histos
      H_hXColl_vs_hYColl->Write();
      H_eXColl_vs_eYColl->Write();
         
      H_Em_vs_Pm->Write();

    }
  
  outROOT->Close();
  cout << "Ending WriteHist() . . . " << endl;

} //End WriteHist()

//____________________________________________________________
void analyze::WriteReport()
{
  
  /*Method to write charge, efficiencies, live time and other relevant quantities to a data file*/
  
  cout << "Calling WriteReport() . . ." << endl;

  if(analysis=="data"){
    
    //Check if file already exists
    in_file.open(report_OutputFileName);
    
    if(in_file.fail()){
      
      cout << "Report File does NOT exist, will create one . . . " << endl;
      
      out_file.open(report_OutputFileName);
      out_file << "#!Run[i,0]/" << std::setw(25) << "charge[f,1]/" << std::setw(25) << "cpuLT[f,2]/"  << std::setw(25) <<  "tLT[f,3]/"  << std::setw(25) <<  "hTrkEff[f,4]/" << std::setw(25) <<  "eTrkEff[f,5]/" << std::setw(25) <<   "avg_current[f,6]/"  << std::setw(25) << "pS1X_rate[f,7]/"  << std::setw(25) << "ptrig1_rate[f,8]/" << std::setw(25) << "ptrig2_rate[f,9]/" << std::setw(25) << "ptrig3_rate[f,10]/" << std::setw(25) << "ptrig4_rate[f,11]/" << std::setw(25) << "ptrig6_rate[f,12]/" << std::setw(25) << "HMS_Angle[f,13]/"  << std::setw(25) << "HMS_Pcen[f,14]/"  << std::setw(25) << "SHMS_Angle[f,15]/"   << std::setw(25) << "SHMS_Pcen[f,16]/"  << std::setw(25) << "HMS_Xmp[f,17]/" << std::setw(25) << "HMS_Ymp[f,18]/" << std::setw(25) << "SHMS_Xmp[f,19]/" << std::setw(25) << "SHMS_Ymp[f,20]/" << std::setw(25) << "xBPM[f,21]/" << std::setw(25) << "yBPM[f,22]/" << endl;
      out_file.close();
      
    }
    
    //Open Report FIle in append mode
    out_file.open(report_OutputFileName, ios::out | ios::app);
    out_file << runNUM << std::setw(25) << total_charge_bcm_cut << std::setw(25) << cpuLT << std::setw(25) << tLT << std::setw(25) << hTrkEff  << std::setw(25) << eTrkEff  << std::setw(25) << avg_current_bcm_cut << std::setw(25) << pS1XscalerRate_bcm_cut << std::setw(25) << pTRIG1scalerRate_bcm_cut << std::setw(25) << pTRIG2scalerRate_bcm_cut << std::setw(25) << pTRIG3scalerRate_bcm_cut << std::setw(25) << pTRIG4scalerRate_bcm_cut << std::setw(25) << pTRIG6scalerRate_bcm_cut << std::setw(25) << h_th  << std::setw(25) << h_Pcen << std::setw(25) << e_th << std::setw(25) << e_Pcen << std::setw(25) <<  h_xMisPoint << std::setw(25) <<  h_yMisPoint << std::setw(25) << e_xMisPoint << std::setw(25) << e_yMisPoint << std::setw(25) << xBPM << std::setw(25) << yBPM << endl;
    out_file.close();
  }  
  
  cout << "Ending WriteReport() . . ." << endl;

} //End WriteReport()

//_________________________________________________________
void analyze::CollimatorStudy()
{

  //Method to study various collimator cuts on the H(e,e'p) and D(e,e'p)n  Yield across Ytar, Y'tar, X'tar and delta

  cout << "Calling CollimatorStudy() . . . " << endl;
  
  //Scaling the HMS/SHMS Collimator Cuts
  hms_hsize = hms_scale*hms_hsize;  //The scale factor is read from set_heep_cuts.inp
  hms_vsize = hms_scale*hms_vsize;
  
  shms_hsize = shms_scale*shms_hsize;
  shms_vsize = shms_scale*shms_vsize;  

  //Define HMS Collimator Shape
  hms_Coll_gCut = new TCutG("hmsCollCut", 8 );
  hms_Coll_gCut->SetVarX("X");
  hms_Coll_gCut->SetVarY("Y");
 
  hms_Coll_gCut->SetPoint(0,  hms_hsize,     hms_vsize/2.);
  hms_Coll_gCut->SetPoint(1,  hms_hsize/2.,  hms_vsize   );
  hms_Coll_gCut->SetPoint(2, -hms_hsize/2.,  hms_vsize   );
  hms_Coll_gCut->SetPoint(3, -hms_hsize,     hms_vsize/2.);
  hms_Coll_gCut->SetPoint(4, -hms_hsize,    -hms_vsize/2.);
  hms_Coll_gCut->SetPoint(5, -hms_hsize/2., -hms_vsize   );
  hms_Coll_gCut->SetPoint(6,  hms_hsize/2., -hms_vsize   );
  hms_Coll_gCut->SetPoint(7,  hms_hsize,    -hms_vsize/2.);
  hms_Coll_gCut->SetPoint(8,  hms_hsize,     hms_vsize/2.);

  //Define SHMS Collimator Shape
  shms_Coll_gCut = new TCutG("shmsCollCut", 8 );
  shms_Coll_gCut->SetVarX("X");
  shms_Coll_gCut->SetVarY("Y");
 
  shms_Coll_gCut->SetPoint(0,  shms_hsize,     shms_vsize/2.);
  shms_Coll_gCut->SetPoint(1,  shms_hsize/2.,  shms_vsize   );
  shms_Coll_gCut->SetPoint(2, -shms_hsize/2.,  shms_vsize   );
  shms_Coll_gCut->SetPoint(3, -shms_hsize,     shms_vsize/2.);
  shms_Coll_gCut->SetPoint(4, -shms_hsize,    -shms_vsize/2.);
  shms_Coll_gCut->SetPoint(5, -shms_hsize/2., -shms_vsize   );
  shms_Coll_gCut->SetPoint(6,  shms_hsize/2., -shms_vsize   );
  shms_Coll_gCut->SetPoint(7,  shms_hsize,    -shms_vsize/2.);
  shms_Coll_gCut->SetPoint(8,  shms_hsize,     shms_vsize/2.);

  cout << "Ending CollimatorStudy() . . . " << endl;


}

//_______________________________________________________________________________
void analyze::CalcRadCorr()
{
  /*Brief: Method to calculate Radiative Correction Factor on a bin-by-bin basis
    By taking the ratio of Y_norad / Y_rad in SIMC. This assumes that rad_flag has been
    turnen ON in the set_deep_cuts.inp (or set_heep_cuts.inp), and that the ROOTfiles containing 
    the histogram objects for rad and no-rad SIMC exists.
  */
  cout << "Calling CalcRadCorr() . . . " << endl;

  //Read SIMC Radiative and Non-Radiative ROOTfiles
  TFile *rad_file = new TFile(simc_OutputFileName_rad, "READ");
  TFile *norad_file = new TFile(simc_OutputFileName_norad, "READ");

  //Get Necessary Histograms
  rad_file->cd();	
  rad_file->GetObject("H_Q2", simc_Q2_rad);
  rad_file->GetObject("H_Pm", simc_Pm_rad);
  rad_file->GetObject("H_theta_nq", simc_th_nq_rad);

  norad_file->cd();	
  norad_file->GetObject("H_Q2", simc_Q2_norad);
  norad_file->GetObject("H_Pm", simc_Pm_norad);
  norad_file->GetObject("H_theta_nq", simc_th_nq_norad);
  
  //Calculate Non-Radiative to Radiative SIMC Ratio 
  simc_Q2_norad->Divide(simc_Q2_rad);
  simc_Pm_norad->Divide(simc_Pm_rad);
  simc_th_nq_norad->Divide(simc_th_nq_rad);

  //Rename Histograms  / Set Title
  simc_Q2_norad->SetNameTitle("H_Q2_ratio", "SIMC Q2_{norad} / Q2_{rad} Ratio");
  simc_Pm_norad->SetNameTitle("H_Pm_ratio", "SIMC Pm_{norad} / Pm_{rad} Ratio");
  simc_th_nq_norad->SetNameTitle("H_th_nq_ratio", "SIMC th_nq_{norad} / th_nq_{rad} Ratio");


  //Write Radiative Correction Ratios to ROOTfile
  TFile *rad_ratio_file = new TFile(simc_OutputFileName_radCorr, "RECREATE");
  rad_ratio_file->cd();

  //Write To File
  simc_Q2_norad->Write();
  simc_Pm_norad->Write();
  simc_th_nq_norad->Write();

  rad_ratio_file->Close();

}

//_______________________________________________________________________________
void analyze::ApplyRadCorr()
{
  /* Brief: Method to Apply radiative corrections to data. Assumes the Ynorad / Yrad SIMC ratios
     have been saved to a ROOTfile. Read in this ROOTfile histograms (which are really the ratios or rad. correction)
     and Read in the data ROOTfile histograms. Both histograms are multiplied bin-by-bin to correct for radiative effect
     for each bin.

   */
  cout << "Calling ApplyRadCorr() . . . " << endl;
  
  //Read Data Un-RadCorr and SIMC RadCorr ROOTfiles
  TFile *data_file = new TFile(data_OutputFileName, "READ");
  TFile *radCorr_file = new TFile(simc_OutputFileName_radCorr, "READ");


  data_file->cd();	
  data_file->GetObject("H_Q2", data_Q2);
  data_file->GetObject("H_Pm", data_Pm);
  data_file->GetObject("H_th_nq", data_th_nq);

  radCorr_file->cd();	
  radCorr_file->GetObject("H_Q2_ratio", ratio_Q2);
  radCorr_file->GetObject("H_Pm_ratio", ratio_Pm);
  radCorr_file->GetObject("H_th_nq_ratio", ratio_th_nq);

  //Apply Radiative Corrections to Data
  data_Q2->Multiply(ratio_Q2);
  data_Pm->Multiply(ratio_Pm);
  data_th_nq->Multiply(ratio_th_nq);

  //Write Radiative Corrected Data to ROOTfile
  TFile *data_radcorr = new TFile(data_OutputFileName_radCorr, "RECREATE");

  data_radcorr->cd();

  data_Q2->Write();
  data_Pm->Write();
  data_th_nq->Write();

  data_radcorr->Close();

}


//---------------AUXILIARY FUNCTIONS TO CALCULATE Pmx, Pmy, Pmz in SIMC (same as HCANA) -------------------

//_____________________________________________________
void analyze::GeoToSph( Double_t  th_geo, Double_t  ph_geo, Double_t& th_sph, Double_t& ph_sph)
{
  
  // Convert geographical to spherical angles. Units are rad.
  
  static const Double_t twopi = 2.0*TMath::Pi();
  Double_t ct = cos(th_geo), cp = cos(ph_geo);
  Double_t tmp = ct*cp;
  th_sph = acos( tmp );
  tmp = sqrt(1.0 - tmp*tmp);
  ph_sph = (fabs(tmp) < 1e-6 ) ? 0.0 : acos( sqrt(1.0-ct*ct)*cp/tmp );
  if( th_geo/twopi-floor(th_geo/twopi) > 0.5 ) ph_sph = TMath::Pi() - ph_sph;
  if( ph_geo/twopi-floor(ph_geo/twopi) > 0.5 ) ph_sph = -ph_sph;
}

//_______________________________________________________________
void analyze::SetCentralAngles(Double_t th_cent=0, Double_t ph_cent=0)
{
  
  fThetaGeo = TMath::DegToRad()*th_cent; fPhiGeo = TMath::DegToRad()*ph_cent;
  GeoToSph( fThetaGeo, fPhiGeo, fThetaSph, fPhiSph );
  fSinThGeo = TMath::Sin( fThetaGeo ); fCosThGeo = TMath::Cos( fThetaGeo );
  fSinPhGeo = TMath::Sin( fPhiGeo );   fCosPhGeo = TMath::Cos( fPhiGeo );
  Double_t st, ct, sp, cp;
  st = fSinThSph = TMath::Sin( fThetaSph ); ct = fCosThSph = TMath::Cos( fThetaSph );
  sp = fSinPhSph = TMath::Sin( fPhiSph );   cp = fCosPhSph = TMath::Cos( fPhiSph );
  
  Double_t norm = TMath::Sqrt(ct*ct + st*st*cp*cp);
  TVector3 nx( st*st*sp*cp/norm, -norm, st*ct*sp/norm );
  TVector3 ny( ct/norm,          0.0,   -st*cp/norm   );
  TVector3 nz( st*cp,            st*sp, ct            );
  
  fToLabRot.SetToIdentity().RotateAxes( nx, ny, nz );
}

//____________________________________________________________________________________
void analyze::TransportToLab( Double_t p, Double_t xptar, Double_t yptar, TVector3& pvect) 
{
  TVector3 v( xptar, yptar, 1.0 );
  v *= p/TMath::Sqrt( 1.0+xptar*xptar+yptar*yptar );
  pvect = fToLabRot * v;
}

//------------------------------------------------------------------------------------------


//----------------------------------UTILITIES FUNCTIONS--------------------------------------

//_____________________________________________________________________________
string analyze::getString(char x)
{
  //method to convert a character to a string
  string s(1,x);
  return s;
}

//__________________________________________________________________
vector <string> analyze::split(string str, char del=':')
{

  //method to split a string into a vetor of strings separated by a delimiter del
  //Returns a vector of strings, whose elements are separated by the delimiter del.

  string temp1, temp2;

  vector <string> parse_word;
  int del_pos;  //delimiter position
    
    for (int i=0; i < str.size(); i++){

      //Get position of delimiter
      if(str[i]==del){
	del_pos = i;
      }

    }

    for (int i=0; i < str.size(); i++){

      //append char to a string for char left of the delimiter
      if(i<del_pos){
	temp1.append(getString(str[i]));
      }      

      //append char to a string for char right of the delimiter
      else if(i>del_pos){
	temp2.append(getString(str[i]));
      }

    }
    parse_word.push_back(temp1);
    parse_word.push_back(temp2);
    
    return parse_word;
}

//_______________________________________________________________________________________
vector <string> analyze::FindString(string keyword, string fname)
{

  //Method: Finds string keyword in a given txt file. 
  //Returns the lines (stored in a vector) in which the keyword was found. Lines are counted from 0. 
  
  ifstream ifile(fname);

  vector <string> line_found; //vector to store in which lines was the keyword found
  
  int line_cnt = 0;
  string line;                  //line string to read
  
  int found = -1; //position of found keyword

  while(getline(ifile, line))
    {
        
      found = line.find(keyword);
      
      if(found<0||found>1000){found=-1;} //not found

      if(found!=-1){
	
	line_found.push_back(line);
	

      } //end if statement
    
      line_cnt++;
    } //end readlines

  return line_found;

}
string& analyze::ltrim(std::string& s)
{
  auto it = std::find_if(s.begin(), s.end(),
			 [](char c) {
			   return !std::isspace<char>(c, std::locale::classic());
			 });
  s.erase(s.begin(), it);
  return s;
}

string& analyze::rtrim(std::string& s)
{
  auto it = std::find_if(s.rbegin(), s.rend(),
						[](char c) {
			   return !std::isspace<char>(c, std::locale::classic());
			 });
  s.erase(it.base(), s.end());
  return s;
}

string& analyze::trim(std::string& s)
{
  return ltrim(rtrim(s));
}

//-----------RUN ANALYSIS METHODS------------

//________________________________________________________
void analyze::run_simc_analysis(Bool_t rad_corr_flag=0)
{

  //Run SIMC analysis. By default, it reads the radiative ROOTfile
  SetFileNames();
  SetCuts();
  SetDefinitions();
  SetHistBins();
  CreateHist();
  ReadTree();
  EventLoop();
  WriteHist();
  
  //Calculate and Apply Radiative Corrections
  if(rad_corr_flag)
    {
      cout << "_____________________________" << endl;
      cout << "_____________________________" << endl;
      cout << "                             " << endl;
      cout << " Doing Radiative Corrections " << endl;
      cout << "_____________________________" << endl;
      cout << "_____________________________" << endl;

      ReadTree("do_rad_corr");
      EventLoop();
      WriteHist("do_rad_corr");
      CalcRadCorr();
      ApplyRadCorr();
    }
  

}

//________________________________________
void analyze::run_data_analysis()
{


  SetFileNames();
  SetCuts();
  SetDefinitions();
  SetHistBins();
  CreateHist();
  ReadScalerTree("BCM4A");   //argument: "BCM1", "BCM2", "BCM4A", "BCM4B", "BCM4C"
  ScalerEventLoop(5);       //argument represents current threshold(uA): usage in code-> Abs(bcm_current - set_current) < threshold
  ReadTree();
  EventLoop();
  CalcEff();
  ApplyWeight();
  WriteHist();
  WriteReport();

}
