#include<iostream>
#include "analyze.h"

using namespace std;

//_______________________________________________________________________
analyze::analyze(int run=-1, string e_arm="SHMS", string type="data") 
  : runNUM(run),       
    e_arm_name(e_arm),    //electron arm: "HMS" or "SHMS" 
    analysis(type)       //analysis type: "data" or "simc"
    
{
  
  cout << "Calling Constructor . . . " << endl;
  
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

  //Initialize DATA/SIMC Histograms
  H_Emiss = NULL;

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
  delete H_Emiss; H_Emiss = NULL;

  //Delete Scaler Histograms
  delete H_bcmCurrent; H_bcmCurrent = NULL;

}


//___________________________________________________________________________
void analyze::SetFileNames()
{
  
  //Set FileName Pattern
  data_InputFileName = Form("ROOTfiles/coin_replay_scaler_test_%d_-1.root", runNUM);
  simc_InputFileName = Form("worksim_voli/D2_heep_%d.root", runNUM);
  
  data_OutputFileName = Form("heep_data_histos_%d.root",runNUM);;
  simc_OutputFileName = Form("heep_simc_histos_%d.root",runNUM);;
  
  report_OutputFileName = "report_test.dat";

}

//___________________________________________________________________________
void analyze::SetDefinitions()
{
  /*Brief: Set particle masses, useful mathematical constants, and cut limits
    Units: Mass [GeV]
   */
  
  
  pi = TMath::Pi();
  dtr = pi / 180.;    //degree-to-radians conversion factor
  
  //Particle Masses
  MP = 0.938272;     //proton mass
  MN = 0.939566;     //neutron mass
  MD = 1.87561;      //deuteron mass
  me = 0.00051099;   //electron mass

  //Target Mass (FIXME!)
  tgt_mass = MP;   //For now is the proton mass. Later on, add a flag to switch between "heep" and "deep"

  //FIXME (Need to learn how to read/parse REPORT-FILES in C++ to get angles easily. These are needed for auxiliary functions.)
  if(runNUM==3288){e_th = 12.194, e_ph = 0., h_th = -37.338, h_ph=0.;}
  if(runNUM==3371){e_th = 13.93,  e_ph = 0., h_th = -33.545, h_ph=0.;}
  if(runNUM==3374){e_th = 9.928,  e_ph = 0., h_th = -42.9,   h_ph=0.;}
  if(runNUM==3377){e_th = 8.495,  e_ph = 0., h_th = -47.605, h_ph=0.;}



}


//___________________________________________________________________________
void analyze::SetHistBins()
{
  cout << "Calling SetHistBins . . . " << endl;

  //Set Histogram Limits for a specified run / kinematic setting
  
  //-----H(e,e'p) Elastic Runs----
  if(runNUM==3288)
    {
      //Emiss
      Em_nbins = 100;
      Em_xmin = -0.05;
      Em_xmax = 0.1;
    }

} //End SetHistBins()

//_______________________________________________________________________________
void analyze::CreateHist()
{
  
  //Function to Create Histograms
  H_Emiss = new TH1F("H_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax); 
  H_Emiss->SetDefaultSumw2();
  
  H_bcmCurrent = new TH1F("H_bcmCurrent", "BCM Current", 100, 0, 100);
  

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
      scaler_tree->SetBranchAddress("P.pTRIG6.scaler",&pTRIG6_scaler);
      scaler_tree->SetBranchAddress("P.EDTM.scaler",&pEDTM_scaler);
}

//____________________________________________________________________________
void analyze::ScalerEventLoop(Double_t current_thrs_bcm=5.)
{
  
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
      prev_ptrig6_scaler = pTRIG6_scaler;
      prev_pedtm_scaler = pEDTM_scaler;
            
      cout << "ScalerEventLoop(PASS2): " << std::setprecision(2) << double(i) / scal_entries * 100. << "  % " << std::flush << "\r";

    } //End Scaler Read Loop
   
  //Calculate Rates if Current Cut Passed (units of Hz)
  pS1XscalerRate_bcm_cut = total_ps1x_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG1scalerRate_bcm_cut = total_ptrig1_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG2scalerRate_bcm_cut = total_ptrig2_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG3scalerRate_bcm_cut = total_ptrig3_scaler_bcm_cut / total_time_bcm_cut;
  pTRIG6scalerRate_bcm_cut = total_ptrig6_scaler_bcm_cut / total_time_bcm_cut;
  pEDTMscalerRate_bcm_cut =  total_pedtm_scaler_bcm_cut / total_time_bcm_cut;
  

}

//____________________________________________________________________________
void analyze::ReadTree()
{
  cout << "Calling Read Tree . . . " << endl;

  
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
      tree->SetBranchAddress("T.coin.pTRIG6_ROC2_tdcTimeRaw",&pTRIG6_tdcTimeRaw);
      tree->SetBranchAddress("T.coin.pEDTM_tdcTimeRaw",&pEDTM_tdcTimeRaw);

      //SHMS Detectors
      tree->SetBranchAddress("P.hgcer.npeSum",&pHGCER_npeSum);
      tree->SetBranchAddress("P.ngcer.npeSum",&pNGCER_npeSum);
      tree->SetBranchAddress("P.cal.etotnorm",&pCAL_etotnorm);    
      tree->SetBranchAddress("P.cal.etottracknorm",&pCAL_etottracknorm);    
      tree->SetBranchAddress("P.hod.betanotrack",&pBetanotrk);    
      tree->SetBranchAddress("P.hod.goodscinhit",&pGoodScinHit);    
      tree->SetBranchAddress("P.dc.ntrack",&pdc_ntrack);    


      //HMS Detectors
      tree->SetBranchAddress("H.cer.npeSum",&hCER_npeSum);
      tree->SetBranchAddress("H.cal.etotnorm",&hCAL_etotnorm);      
      tree->SetBranchAddress("H.cal.etottracknorm",&hCAL_etottracknorm);      
      tree->SetBranchAddress("H.hod.betanotrack",&hBetanotrk);    
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
      inROOT = new TFile(simc_InputFileName, "READ");
      
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
      tree->SetBranchAddress("tar_x", &htar_x);
      tree->SetBranchAddress("h_yv",  &htar_y);
      tree->SetBranchAddress("h_zv",  &htar_z);

      tree->SetBranchAddress("tar_x", &etar_x);
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
      //are calculated externally (using auxiliary methods from hcana)
      //Kp, Kn are calculated in the event loop
      //M_recoil, E_recoil (missing neutron mass and neutron recoil energy) are calculated in the event loop
      tree->SetBranchAddress("theta_pq", &th_pq);
      tree->SetBranchAddress("phi_pq", &ph_pq);
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
      

    }
  


}

//________________________________________________________________________________
void analyze::EventLoop()
{

  /*Loop over Events*/
  
  if(analysis=="data")
    {
      for(int ientry=0; ientry<nentries; ientry++)
	{
	  
	  tree->GetEntry(ientry);
	  
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
      
	   //Define DATA/SIMC CUTS (BETTER BE THE SAME CUTS!)
	   c_edelta = e_delta>-10.&&e_delta<22.;
	   c_hdelta = abs(h_delta)<8.;
	   

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
		   
		   //Fill Histograms
		   H_Emiss->Fill(Em);
		   
		   
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
	      
	      //***NOTE*** The following needs to be calculated by hand:
	      //Xbj, th_q, Pmx_lab,Pmy_lab,Pmz_lab, Pmx_q, Pmy_q, Pmz_q, Kp, Kn, 
	      //M_recoil, E_recoil, th_nq (thbq), ph_nq (phbq)
	     
	      //--------Calculated Kinematic Varibales----------------
	      
	      //Convert MeV to GeV
	      Ein = Ein / 1000.;     //incident beam energy
	      kf = kf / 1000.;       //final electron momentum
	      Pf = Pf / 1000.;       //final proton momentum
	      
	      ki = sqrt(Ein*Ein - me*me);        //initial electron momentum
	      E_recoil = sqrt(MN*MN + Pm*Pm);    //recoil energy (neutron energy)
	      M_recoil = sqrt( pow(nu+MD-sqrt(MP*MP+Pf*Pf),2) - Pm*Pm );  //recoil mass (neutron missing mass)
	      
	      X = Q2 / (2.*MP*nu);                           
	      th_q = acos( (ki - kf*cos(theta_e))/q );       
	      th_pq =  th_q - theta_p;
	      th_nq = acos((q - Pf*cos(th_pq))/Pm);
	      	      
	      Kp = Ep - MP;
	      Kn = E_recoil - MN;
	     
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
	      fX.SetVectM(Pf_vec, MP);    //SET FOUR VECTOR OF detected particle
	      fB = fA1 - fX;   //4-MOMENTUM OF UNDETECTED PARTICLE 
	      
	      Pmx_lab = fB.X();
	      Pmy_lab = fB.Y(); 
	      Pmz_lab = fB.Z(); 
	      
	      //Pm_v2 = sqrt(Pmx_v2*Pmx_v2 + Pmy_v2*Pmy_v2 + Pmz_v2*Pmz_v2);
	      
	      //--------Rotate the recoil system from +z to +q-------
	      qvec = fQ.Vect();
	      kfvec = fP1.Vect();
	      
	      rot_to_q.SetZAxis( qvec, kfvec).Invert();
	      
	      bq = fB.Vect();
	      
	      bq *= rot_to_q;
	      p_miss_q = -bq;
	      
	      //Missing Momentum Components in the q-frame
	      Pmz_q = p_miss_q.Z();   //parallel component to +z
	      Pmx_q = p_miss_q.X();   //in-plane perpendicular component to +z
	      Pmy_q = p_miss_q.Y();   //out-of-plane component (Oop)
	      
	      
	      //--------------------------------------------------------------------------------




	      //Fill Histograms
	      H_Emiss->Fill(Em);
	      
	      
	      cout << "EventLoop: " << std::setprecision(2) << double(ientry) / nentries * 100. << "  % " << std::flush << "\r";
	    }
	  
	}
}
  
//____________________________________________________________________________
void analyze::CalcEff()
{
  /*Method to calculate tracking efficiencies, live time, and total charge*/


  //Calculate Average BCM Current                                                                                                       
  avg_current_bcm_cut = total_charge_bcm_cut / total_time_bcm_cut; //uA                                                                 
                                                                                                                                   
  //Convert charge from uC to mC                                                                                                 
  total_charge_bcm_cut = total_charge_bcm_cut / 1000.; 

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

}


//____________________________________________________________________________
void analyze::WriteHist()
{

  /* Write Histograms to a ROOTfile */

  if(analysis=="data")
    {
      //Create output ROOTfile
      outROOT = new TFile(data_OutputFileName, "RECREATE");
      
      H_Emiss->Write();
    }
  else if(analysis=="simc")
    {
      //Create output ROOTfile
      outROOT = new TFile(simc_OutputFileName, "RECREATE");
      
      H_Emiss->Write();
    }
  

}

//____________________________________________________________
void analyze::WriteReport()
{

  if(analysis=="data"){
    /*Method to write charge, efficiencies, live time and other relevant quantities to a data file*/
    
    //Check if file already exists
    in_file.open(report_OutputFileName);
    
    if(in_file.fail()){
      
      cout << "Report File does NOT exist, will create one . . . " << endl;
      
      out_file.open(report_OutputFileName);
      //out_file << std::left << std::setw(25) << "Column 1" << std::setw(25) << "Column 2" << endl;
      out_file << "#Run[i,0]/" << std::setw(25) << "charge[f,1]/" << std::setw(25) << "cpuLT[f,2]/"  << std::setw(25) <<  "tLT[f,3]/"  << std::setw(25) <<  "hTrkEff[f,4]/" << std::setw(25) <<  "eTrkEff[f,5]/" << std::setw(25) <<   "avg_current[f,6]/" << endl;
      out_file.close();
      
    }
    
    //Open Report FIle in append mode
    out_file.open(report_OutputFileName, ios::out | ios::app);
    out_file << runNUM << std::setw(25) << total_charge_bcm_cut << std::setw(25) << cpuLT << std::setw(25) << tLT << std::setw(25) << hTrkEff  << std::setw(25) << eTrkEff  << std::setw(25) << avg_current_bcm_cut << endl;
    out_file.close();
  }  
  
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
