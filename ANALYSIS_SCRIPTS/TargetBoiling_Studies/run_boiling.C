
void get_boiling(Int_t runNum, Double_t &set_current, Double_t &avg_current_bcm4a, Double_t &scl_Yield_bcm4a,Double_t &scl_err_bcm4a, 
		 Double_t &notrk_Yield_bcm4a, Double_t &notrk_err_bcm4a, Double_t &trk_Yield_bcm4a, Double_t &trk_err_bcm4a,  
		 Double_t &cpuLT_bcm4a, Double_t &tLT_bcm4a, Double_t &Qtot_bcm4a, Double_t &hS1XscalerRate_bcm4a, Double_t &hTRIG1scalerRate_bcm4a, 
		 Double_t &hTRIG2scalerRate_bcm4a, Double_t &hTRIG3scalerRate_bcm4a, Double_t &hEDTMscalerRate_bcm4a, Double_t &eTrkEff_bcm4a,
		 Double_t &avg_current_bcm4b, Double_t &scl_Yield_bcm4b,Double_t &scl_err_bcm4b, 
		 Double_t &notrk_Yield_bcm4b, Double_t &notrk_err_bcm4b, Double_t &trk_Yield_bcm4b, Double_t &trk_err_bcm4b,  
		 Double_t &cpuLT_bcm4b, Double_t &tLT_bcm4b, Double_t &Qtot_bcm4b, Double_t &hS1XscalerRate_bcm4b, Double_t &hTRIG1scalerRate_bcm4b, 
		 Double_t &hTRIG2scalerRate_bcm4b, Double_t &hTRIG3scalerRate_bcm4b, Double_t &hEDTMscalerRate_bcm4b, Double_t &eTrkEff_bcm4b
		 )
{

  TH1F::SetDefaultSumw2(kTRUE);

  gROOT->SetBatch(kTRUE);

  //Define Constants
  //Int_t runNum = 2093;
  Double_t current_thrs_bcm4a = 3.;
  Double_t current_thrs_bcm4b = 3.;

  Double_t pS;   //Pre-Scale FActor


  //HMS LD2 Boiling Study
  if(runNum==2073){
    set_current = 80.;
    pS = 1.;
    current_thrs_bcm4a = 5.; 
    current_thrs_bcm4b = 5.; 
    //eTrkEff = 0.9931;  
  }
  if(runNum==2074){
    set_current = 70.;
    pS = 1.;
    //eTrkEff = 0.9932;  
  }
  if(runNum==2087){
    set_current = 55.;
    pS = 1.;
    //eTrkEff = 0.9933;  
  }
  if(runNum==2088){
    set_current = 45.;
    pS = 1.;
    //eTrkEff = 0.9929;  
  }
  if(runNum==2089){
    set_current = 35.;
    pS = 1.;
    //eTrkEff = 0.9932;  
  }
  if(runNum==2090){
    set_current = 20.;
    pS = 1.;
    //eTrkEff = 0.9932;  
  }
  if(runNum==2091){
    set_current = 10.;
    pS = 1.;
    //eTrkEff = 0.9933;  
  }
  //HMS Carbon Boiling Study
  if(runNum==2093){
    set_current = 60.;
    pS = 1.;
    //eTrkEff = 0.9936;  
  }
  if(runNum==2094){
    set_current = 50.;
    pS = 1.;
    //eTrkEff = 0.9930;  
  }
  if(runNum==2095){
    set_current = 35;
    pS = 1.;
    //eTrkEff = 0.9936;  
  }
  //HMS Al. dummy
  if(runNum==2096){
    set_current = 40;
    pS = 1.;
    //eTrkEff = 0.9936;  
  }

  //HMS LH2 Boiling Study
  if(runNum==2075){
    set_current = 80.;
    pS = 1.;
    current_thrs_bcm4a = 5.; 
    current_thrs_bcm4b = 5.; 
    //eTrkEff = 0.9932;
  }
  if(runNum==2076){
    set_current = 70.;
    pS = 1.;
    //eTrkEff = 0.9932;
  }
  if(runNum==2078){
    set_current =  10.;
    pS = 1.;
    //eTrkEff = 0.9935;
  }
  if(runNum==2080){
    set_current = 10.;
    pS = 1.;
    //eTrkEff = 0.9930;
  }
  if(runNum==2081){
    set_current = 20.;
    pS = 1.;
    //eTrkEff = 0.9934;
  }
  if(runNum==2082){
    set_current = 35.;
    pS = 1.;
    //eTrkEff = 0.9952;
  }
  if(runNum==2083){
    set_current = 35.;
    pS = 1.;
    //eTrkEff = 0.9933;
  }
  if(runNum==2084){
    set_current = 45.;
    pS = 1.;
    //eTrkEff = 0.9924;
  }
  if(runNum==2085){
    set_current = 55.;
    pS = 1.;
    //eTrkEff = 0.9932;
  }


  //Created and Read Rootfile
  TString filename=Form("../../../ROOTfiles/hms_replay_tgt_boiling_%d_-1.root", runNum);
  
  TFile *file = new TFile(filename);
  
  TTree *tdata = (TTree*) file->Get("T");    //data TTree
  TTree *tscal = (TTree*) file->Get("TSH");  //Scaler TTree


  //Get Scaler Leafs
  Double_t Scal_evNum;    //event number associated with scaler reads
  tscal->SetBranchAddress("evNumber", &Scal_evNum);
  Double_t  Scal_BCM4A_charge;
  tscal->SetBranchAddress("H.BCM4A.scalerCharge",&Scal_BCM4A_charge);
  Double_t  Scal_BCM4A_current;
  tscal->SetBranchAddress("H.BCM4A.scalerCurrent",&Scal_BCM4A_current);  
  Double_t  Scal_BCM4B_charge;
  tscal->SetBranchAddress("H.BCM4B.scalerCharge",&Scal_BCM4B_charge);
  Double_t  Scal_BCM4B_current;
  tscal->SetBranchAddress("H.BCM4B.scalerCurrent",&Scal_BCM4B_current);  
  Double_t  Scal_time;
  tscal->SetBranchAddress("H.1MHz.scalerTime",&Scal_time);
  Double_t  hS1X_scaler;
  tscal->SetBranchAddress("H.S1X.scaler",&hS1X_scaler);         //HMS S1X 
  Double_t  hTRIG1_scaler;
  tscal->SetBranchAddress("H.hTRIG1.scaler",&hTRIG1_scaler);    //HMS 3/4
  Double_t  hTRIG2_scaler;  
  tscal->SetBranchAddress("H.hTRIG2.scaler",&hTRIG2_scaler);    //HMS EL-REAL
  Double_t  hTRIG3_scaler; 
  tscal->SetBranchAddress("H.hTRIG3.scaler",&hTRIG3_scaler);    //HMS EL-CLEAN
  Double_t  hEDTM_scaler; 
  tscal->SetBranchAddress("H.EDTM.scaler",&hEDTM_scaler);    //HMS EDTM 
  

  //Defive Quantities To Store Previous Reads and cumulative quantities
  Double_t prev_time = 0.;
  Double_t prev_charge_bcm4a = 0.;
  Double_t prev_charge_bcm4b = 0.;
  Double_t prev_hs1x_scaler = 0;
  Double_t prev_htrig1_scaler = 0;
  Double_t prev_htrig2_scaler = 0;
  Double_t prev_htrig3_scaler = 0;
  Double_t prev_hedtm_scaler = 0;

  Double_t total_time = 0.;
  Double_t total_charge_bcm4a = 0.;
  Double_t total_charge_bcm4b = 0.;
  Double_t total_hs1x_scaler = 0;
  Double_t total_htrig1_scaler = 0;
  Double_t total_htrig2_scaler = 0;
  Double_t total_htrig3_scaler = 0;
  Double_t total_hedtm_scaler = 0;

  //BCM4A Cut variables
  Double_t total_time_bcm4a_cut = 0.;
  Double_t total_charge_bcm4a_cut = 0.;
  Double_t total_hs1x_scaler_bcm4a_cut = 0;
  Double_t total_htrig1_scaler_bcm4a_cut = 0;
  Double_t total_htrig2_scaler_bcm4a_cut = 0;
  Double_t total_htrig3_scaler_bcm4a_cut = 0;
  Double_t total_hedtm_scaler_bcm4a_cut = 0;

  //BCM4B Cut variables
  Double_t total_time_bcm4b_cut = 0.;
  Double_t total_charge_bcm4b_cut = 0.;
  Double_t total_hs1x_scaler_bcm4b_cut = 0;
  Double_t total_htrig1_scaler_bcm4b_cut = 0;
  Double_t total_htrig2_scaler_bcm4b_cut = 0;
  Double_t total_htrig3_scaler_bcm4b_cut = 0;
  Double_t total_hedtm_scaler_bcm4b_cut = 0;

  //Loop Over Scaler Reads 
  Long64_t scal_entries = tscal->GetEntries();

  Int_t evt_flag_bcm4a[scal_entries];             //Store Flag [0 or 1], to know if scaler read passed current cut (1) or not (0)
  Int_t evt_flag_bcm4b[scal_entries];             //Store Flag [0 or 1], to know if scaler read passed current cut (1) or not (0)

  Int_t scal_evt_num[scal_entries];    //Store Event Associated with Scaler Read
 
  for (int i = 0; i < scal_entries; i++) {
    
    //**NOTE: Each scaler read is associated with as specific event number
    //        as (scaler read 1-> event 1000,  scaler read 2 -> event 2300, ...)
    //        This means events up to 1000 correspond to scaler read 1, ...
   
    tscal->GetEntry(i);
       
    
    evt_flag_bcm4a[i] = 0;
    evt_flag_bcm4b[i] = 0;
    
    scal_evt_num[i] = Scal_evNum; //store events associated with scaler reads (to be used in data tree)

    //Store Cumulative Quantities
    total_charge_bcm4a = Scal_BCM4A_charge;
    total_charge_bcm4b = Scal_BCM4B_charge;
    total_time = Scal_time;
    total_hs1x_scaler = hS1X_scaler;
    total_htrig1_scaler = hTRIG1_scaler;
    total_htrig2_scaler = hTRIG2_scaler;
    total_htrig3_scaler = hTRIG3_scaler;
    total_hedtm_scaler = hEDTM_scaler;

    //Check If BCM4A Beam Current in Between Reads is Over Threshold
    if(abs(Scal_BCM4A_current-set_current)<current_thrs_bcm4a)
      {

	//Turn Event Flag ON, if beam current is within threshold
	evt_flag_bcm4a[i] = 1;

	//Store Quantities that Passed the Current Threshold
	total_time_bcm4a_cut = total_time_bcm4a_cut + (Scal_time - prev_time);
	total_charge_bcm4a_cut = total_charge_bcm4a_cut + (Scal_BCM4A_charge - prev_charge_bcm4a);  
	total_hs1x_scaler_bcm4a_cut = total_hs1x_scaler_bcm4a_cut + (hS1X_scaler-prev_hs1x_scaler);
	total_htrig1_scaler_bcm4a_cut = total_htrig1_scaler_bcm4a_cut + (hTRIG1_scaler-prev_htrig1_scaler);
	total_htrig2_scaler_bcm4a_cut = total_htrig2_scaler_bcm4a_cut + (hTRIG2_scaler-prev_htrig2_scaler);
	total_htrig3_scaler_bcm4a_cut = total_htrig3_scaler_bcm4a_cut + (hTRIG3_scaler-prev_htrig3_scaler);
	total_hedtm_scaler_bcm4a_cut = total_hedtm_scaler_bcm4a_cut + (hEDTM_scaler - prev_hedtm_scaler);
      }
    
    //Check If BCM4B Beam Current in Between Reads is Over Threshold
    if(abs(Scal_BCM4B_current-set_current)<current_thrs_bcm4b)
      {
	
	//Turn Event Flag ON, if beam current is within threshold
	evt_flag_bcm4b[i] = 1;

	//Store Quantities that Passed the Current Threshold
	total_time_bcm4b_cut = total_time_bcm4b_cut + (Scal_time - prev_time);
	total_charge_bcm4b_cut = total_charge_bcm4b_cut + (Scal_BCM4B_charge - prev_charge_bcm4b);  
	total_hs1x_scaler_bcm4b_cut = total_hs1x_scaler_bcm4b_cut + (hS1X_scaler-prev_hs1x_scaler);
	total_htrig1_scaler_bcm4b_cut = total_htrig1_scaler_bcm4b_cut + (hTRIG1_scaler-prev_htrig1_scaler);
	total_htrig2_scaler_bcm4b_cut = total_htrig2_scaler_bcm4b_cut + (hTRIG2_scaler-prev_htrig2_scaler);
	total_htrig3_scaler_bcm4b_cut = total_htrig3_scaler_bcm4b_cut + (hTRIG3_scaler-prev_htrig3_scaler);
	total_hedtm_scaler_bcm4b_cut = total_hedtm_scaler_bcm4b_cut + (hEDTM_scaler - prev_hedtm_scaler);
      }

    //Previous Scaler Reads (Necessary to Take Average between S-1 and S scaler reads, to get values in between)
    prev_time = Scal_time;
    prev_charge_bcm4a = Scal_BCM4A_charge;
    prev_charge_bcm4b = Scal_BCM4B_charge;
    prev_hs1x_scaler = hS1X_scaler;
    prev_htrig1_scaler = hTRIG1_scaler;
    prev_htrig2_scaler = hTRIG2_scaler;
    prev_htrig3_scaler = hTRIG3_scaler;
    prev_hedtm_scaler = hEDTM_scaler;

  } //end scaler read loop

  //Calculate Rates if Current Cut Passed
  //BCM4A
  hS1XscalerRate_bcm4a = total_hs1x_scaler_bcm4a_cut / total_time_bcm4a_cut;
  hTRIG1scalerRate_bcm4a = total_htrig1_scaler_bcm4a_cut / total_time_bcm4a_cut;
  hTRIG2scalerRate_bcm4a = total_htrig2_scaler_bcm4a_cut / total_time_bcm4a_cut;
  hTRIG3scalerRate_bcm4a = total_htrig3_scaler_bcm4a_cut / total_time_bcm4a_cut;
  hEDTMscalerRate_bcm4a =  total_hedtm_scaler_bcm4a_cut / total_time_bcm4a_cut;
  //BCM4B
  hS1XscalerRate_bcm4b = total_hs1x_scaler_bcm4b_cut / total_time_bcm4b_cut;
  hTRIG1scalerRate_bcm4b = total_htrig1_scaler_bcm4b_cut / total_time_bcm4b_cut;
  hTRIG2scalerRate_bcm4b = total_htrig2_scaler_bcm4b_cut / total_time_bcm4b_cut;
  hTRIG3scalerRate_bcm4b = total_htrig3_scaler_bcm4b_cut / total_time_bcm4b_cut;
  hEDTMscalerRate_bcm4b =  total_hedtm_scaler_bcm4b_cut / total_time_bcm4b_cut;

  

  //*******************
  //      DATA
  //*******************

  //Get Data Leafs
  Double_t gevtyp;
  tdata->SetBranchAddress("g.evtyp",&gevtyp);
  Double_t gevnum;
  tdata->SetBranchAddress("g.evnum",&gevnum);
  Double_t hTRIG1_tdcTimeRaw;
  tdata->SetBranchAddress("T.hms.hTRIG1_tdcTimeRaw",&hTRIG1_tdcTimeRaw);
  Double_t hTRIG2_tdcTimeRaw;
  tdata->SetBranchAddress("T.hms.hTRIG2_tdcTimeRaw",&hTRIG2_tdcTimeRaw);
  Double_t hTRIG3_tdcTimeRaw;
  tdata->SetBranchAddress("T.hms.hTRIG3_tdcTimeRaw",&hTRIG3_tdcTimeRaw);
  Double_t hEDTM_tdcTimeRaw;
  tdata->SetBranchAddress("T.hms.hEDTM_tdcTimeRaw",&hEDTM_tdcTimeRaw);
  Double_t hCER_npeSum; 
  tdata->SetBranchAddress("H.cer.npeSum",&hCER_npeSum);    
  Double_t hCAL_etotnorm; 
  tdata->SetBranchAddress("H.cal.etotnorm",&hCAL_etotnorm);    
  Double_t hCAL_etottracknorm; 
  tdata->SetBranchAddress("H.cal.etottracknorm",&hCAL_etottracknorm);    
  Double_t hDelta;
  tdata->SetBranchAddress("H.gtr.dp",&hDelta);    
  Double_t hBetanotrk;
  tdata->SetBranchAddress("H.hod.betanotrack",&hBetanotrk);    
  Double_t hGoodScinHit;
  tdata->SetBranchAddress("H.hod.goodscinhit",&hGoodScinHit);    
  Double_t hdc_ntrack;
  tdata->SetBranchAddress("H.dc.ntrack",&hdc_ntrack);    

  //Create Histograms 
  TH1F *H_hCER_npeSum = new TH1F("H_hCER_npeSum", "HMS Cer NpeSum", 100,0.1,10);
  TH1F *H_hCAL_etotnorm = new TH1F("H_hCAL_etotnorm", "HMS Cal EtotNorm", 100,0.1,1.5);
  TH1F *H_hCAL_etottracknorm = new TH1F("H_hCAL_etottracknorm", "HMS Cal EtotTrackNorm", 100,0.1,1.5);
  TH1F *H_hDelta = new TH1F("H_hDelta", "HMS Delta", 100,-15,15);
  
  TH1F *H_hCER_npeSum_cut = new TH1F("H_hCER_npeSum_cut", "HMS Cer NpeSum", 100,0.1,10);
  TH1F *H_hCAL_etotnorm_cut = new TH1F("H_hCAL_etotnorm_cut", "HMS Cal EtotNorm", 100,0.1,1.5);
  TH1F *H_hCAL_etottracknorm_cut = new TH1F("H_hCAL_etottracknorm_cut", "HMS Cal EtotTrackNorm", 100,0.1,1.5);
  TH1F *H_hDelta_cut = new TH1F("H_hDelta_cut", "HMS Delta_cut", 100,-15,15);

  //BCM4A
  TH1F *H_hCAL_etotnorm_ntrkY_4a = new TH1F("H_hCAL_etotnorm_ntrkY_4a", "HMS Cal. E_{tot} Norm, Yield_{ntrk}", 100, 0.1, 2.0);
  TH1F *H_hDelta_trkY_4a = new TH1F("H_hDelta_trkY_4a", "HMS #delta, Yield_{trk}", 100, -15, 15);
  //BCM4B
  TH1F *H_hCAL_etotnorm_ntrkY_4b = new TH1F("H_hCAL_etotnorm_ntrkY_4b", "HMS Cal. E_{tot} Norm, Yield_{ntrk}", 100, 0.1, 2.0);
  TH1F *H_hDelta_trkY_4b = new TH1F("H_hDelta_trkY_4b", "HMS #delta, Yield_{trk}", 100, -15, 15);
  
  //Set-Up Tdc Counters
  Double_t total_htrig1_accp = 0;
  Double_t total_htrig2_accp = 0;
  Double_t total_htrig3_accp = 0;
  Double_t total_hedtm_accp = 0;
  //Count ONLY for BCM4A Cut
  Double_t total_htrig1_accp_cut_4a = 0;
  Double_t total_htrig2_accp_cut_4a = 0;
  Double_t total_htrig3_accp_cut_4a = 0;
  Double_t total_hedtm_accp_cut_4a = 0;
  //Count ONLY for BCM4B Cut
  Double_t total_htrig1_accp_cut_4b = 0;
  Double_t total_htrig2_accp_cut_4b = 0;
  Double_t total_htrig3_accp_cut_4b = 0;
  Double_t total_hedtm_accp_cut_4b = 0;

  //Set Up Yield Counter
  //BCM4A
  Double_t Y_ntrk_4a;
  Double_t Y_trk_4a;
  //BCM4B
  Double_t Y_ntrk_4b;
  Double_t Y_trk_4b;


  //Tracking Efficiency Counter
  //BCM4A
  Double_t e_did_4a=0.;
  Double_t e_should_4a=0.;
  Double_t eTrkEff_err_4a;
  //BCM4B
  Double_t e_did_4b=0.;
  Double_t e_should_4b=0.;
  Double_t eTrkEff_err_4b;
  
  //Loop Over Data Events 
  Int_t scal_read = 0; //scaler read counter

  Long64_t data_entries = tdata->GetEntries();
  //for (int i = 0; i < data_entries; i++) {
  for (int i = 0; i < 5; i++) {

      
      tdata->GetEntry(i);
      
      cout << "ientry = " << i << endl;
      cout << "evNum = " << gevnum << endl;
      cout << "scal_ev_num = " << scal_evt_num[scal_read] << endl;

      //Define Cuts
      Bool_t c_noedtm = hEDTM_tdcTimeRaw==0;
      Bool_t c_edtm = hEDTM_tdcTimeRaw>0;
      Bool_t c_htrig2 = hTRIG2_tdcTimeRaw>0;
      Bool_t c_cerNpesum =  hCER_npeSum>0.7;
      Bool_t c_hdelta = abs(hDelta)<=8.;
      Bool_t c_etotnorm = hCAL_etotnorm>0.6;
      Bool_t c_etottrknorm = hCAL_etottracknorm>0.6;
      //e- tracking efficiency 
      Bool_t good_elec_should = hGoodScinHit==1.&&hBetanotrk>0.85&&hBetanotrk<1.5&&hCAL_etotnorm>0.6&&hCER_npeSum>0.7;
      Bool_t good_elec_did = good_elec_should&&hdc_ntrack>0.;


      //Count Accepted EDTM events
      if(c_edtm){
	total_hedtm_accp++;
      }
      //Count Accepted hTRIG2 events
      if(c_htrig2){
	total_htrig2_accp++;
      }
      
      //--------Check If BCM4A Current is within limits---------
      if(evt_flag_bcm4a[scal_read]==1){
       

	//Count Accepted EDTM events
	if(c_edtm){
	  total_hedtm_accp_cut_4a++;
	}

	//Count Accepted hTRIG2 events (without EDTM)
	if(c_htrig2&&c_noedtm){
	  total_htrig2_accp_cut_4a++;
	}
      
	if(c_noedtm) {

	  /*
	  //Fill DATA Histograms
	  H_hCER_npeSum->Fill(hCER_npeSum);
	  H_hCAL_etotnorm->Fill(hCAL_etotnorm);
	  H_hCAL_etottracknorm->Fill(hCAL_etottracknorm);
	  H_hDelta->Fill(hDelta);
	  //Fill With Cuts 
	  if(c_cerNpesum){ H_hCER_npeSum_cut->Fill(hCER_npeSum);}
	  if(c_etotnorm){H_hCAL_etotnorm_cut->Fill(hCAL_etotnorm);}
	  if(c_etottrknorm){H_hCAL_etottracknorm_cut->Fill(hCAL_etottracknorm);}
	  if(c_hdelta){H_hDelta_cut->Fill(hDelta);}
	  */

	  //Make Cuts to Count Yield
	  //---Get NON-TRACKING Yield
	  if(c_cerNpesum&&c_etotnorm)
	    {
	      H_hCAL_etotnorm_ntrkY_4a->Fill(hCAL_etotnorm);
	      Y_ntrk_4a++;
	  
	    }
	  
	  if(c_etottrknorm&&c_hdelta)
	    {
	      H_hDelta_trkY_4a->Fill(hDelta);
	      Y_trk_4a++;
	    }

	  //Calculate Electron Tracking Efficiency
	  if(good_elec_did){
	    e_did_4a++;
	  }
	  if(good_elec_should){
	    e_should_4a++;
	  }

	} //end cut on NO EDTM


      } 
      //-------------End BCM4A Current Cut----------------
     

      //--------Check If BCM4B Current is within limits---------
      if(evt_flag_bcm4b[scal_read]==1){
       

	//Count Accepted EDTM events
	if(c_edtm){
	  total_hedtm_accp_cut_4b++;
	}

	//Count Accepted hTRIG2 events (without EDTM)
	if(c_htrig2&&c_noedtm){
	  total_htrig2_accp_cut_4b++;
	}
      
	if(c_noedtm) {

	  /*
	  //Fill DATA Histograms
	  H_hCER_npeSum->Fill(hCER_npeSum);
	  H_hCAL_etotnorm->Fill(hCAL_etotnorm);
	  H_hCAL_etottracknorm->Fill(hCAL_etottracknorm);
	  H_hDelta->Fill(hDelta);
	  //Fill With Cuts 
	  if(c_cerNpesum){ H_hCER_npeSum_cut->Fill(hCER_npeSum);}
	  if(c_etotnorm){H_hCAL_etotnorm_cut->Fill(hCAL_etotnorm);}
	  if(c_etottrknorm){H_hCAL_etottracknorm_cut->Fill(hCAL_etottracknorm);}
	  if(c_hdelta){H_hDelta_cut->Fill(hDelta);}
	  */

	  //Make Cuts to Count Yield
	  //---Get NON-TRACKING Yield
	  if(c_cerNpesum&&c_etotnorm)
	    {
	      H_hCAL_etotnorm_ntrkY_4b->Fill(hCAL_etotnorm);
	      Y_ntrk_4b++;
	  
	    }
	  
	  if(c_etottrknorm&&c_hdelta)
	    {
	      H_hDelta_trkY_4b->Fill(hDelta);
	      Y_trk_4b++;
	    }

	  //Calculate Electron Tracking Efficiency
	  if(good_elec_did){
	    e_did_4b++;
	  }
	  if(good_elec_should){
	    e_should_4b++;
	  }

	} //end cut on NO EDTM


      } 
      //-------------End BCM4B Current Cut----------------



      //Increment Scaler Read if event == scaler_evt_pperlimit for that scaler read
      if(gevnum==scal_evt_num[scal_read]){
	scal_read++;
      }
  
    } //end data loop
    
    /*
    cout << "Total Accepted EDTM (CUT)= " << total_hedtm_accp_cut_4a << endl;
    cout << "Total Accepted hTRIG2 (CUT) = " << total_htrig2_accp_cut_4a << endl;
    cout << "Total Accepted EDTM = " << total_hedtm_accp << endl;
    cout << "Total Accepted hTRIG2 = " << total_htrig2_accp << endl;
    */


    //Draw Histograms
    TCanvas *c1 = new TCanvas("c1", "", 1500,1500);
    c1->Divide(2,2);
    c1->cd(1);
    H_hCER_npeSum->Draw();
    H_hCER_npeSum_cut->SetLineColor(kRed);
    H_hCER_npeSum_cut->Draw("sames");
    c1->cd(2);
    H_hCAL_etotnorm->Draw();
    H_hCAL_etotnorm_cut->SetLineColor(kRed);
    H_hCAL_etotnorm_cut->Draw("sames");
    c1->cd(3);
    H_hCAL_etottracknorm->Draw();
    H_hCAL_etottracknorm_cut->SetLineColor(kRed);
    H_hCAL_etottracknorm_cut->Draw("sames");
    c1->cd(4);
    H_hDelta->Draw();
    H_hDelta_cut->SetLineColor(kRed);
    H_hDelta_cut->Draw("sames");



    
    //Calculate  Live Time
    //BCM4A
    cpuLT_bcm4a =  total_htrig2_accp_cut_4a / (total_htrig2_scaler_bcm4a_cut-total_hedtm_scaler_bcm4a_cut);
    tLT_bcm4a =  total_hedtm_accp_cut_4a / total_hedtm_scaler_bcm4a_cut;
    //BCM4B
    cpuLT_bcm4b =  total_htrig2_accp_cut_4b / (total_htrig2_scaler_bcm4b_cut-total_hedtm_scaler_bcm4b_cut);
    tLT_bcm4b =  total_hedtm_accp_cut_4b / total_hedtm_scaler_bcm4b_cut;
    
    //Calculate Tracking Efficiency
    //BCM4A
    eTrkEff_bcm4a = e_did_4a / e_should_4a;
    eTrkEff_err_4a = sqrt(e_should_4a-e_did_4a) / e_should_4a;
    //BCM4B
    eTrkEff_bcm4b = e_did_4b / e_should_4b;
    eTrkEff_err_4b = sqrt(e_should_4b-e_did_4b) / e_should_4b;
    
    //Avg Current
    avg_current_bcm4a = total_charge_bcm4a_cut / total_time_bcm4a_cut; //uA
    avg_current_bcm4b = total_charge_bcm4b_cut / total_time_bcm4b_cut; //uA

    total_charge_bcm4a_cut = total_charge_bcm4a_cut/1000.;  //COnvert from uC to mC
    Qtot_bcm4a = total_charge_bcm4a_cut;

    total_charge_bcm4b_cut = total_charge_bcm4b_cut/1000.;  //COnvert from uC to mC
    Qtot_bcm4b = total_charge_bcm4b_cut;
    
    //Calculate Normalized Yields
    //Yield involving ONLY scaler quantities  ---> Y / Q
    Double_t notrk_Yield;//, notrk_Yield_bcm4a, notrk_err_bcm4a;    //Yield counting data variables, NO TRACKING ----> Y / (Q*tLT_bcm4a)
    Double_t trk_Yield;//, trk_Yield_bcm4a, trk_err_bcm4a;      //Yield counting data variables,  TRACKING ------> Y / (Q*tLT_bcm4a*trkEff)
    
    //-----SCALER YIELD-----
    //BCM4A
    scl_Yield_bcm4a = (total_htrig2_scaler_bcm4a_cut-total_hedtm_scaler_bcm4a_cut) / (total_charge_bcm4a_cut);
    scl_err_bcm4a = sqrt(total_htrig2_scaler_bcm4a_cut) / total_charge_bcm4a_cut;
    //BCM4B
    scl_Yield_bcm4b = (total_htrig2_scaler_bcm4b_cut-total_hedtm_scaler_bcm4b_cut) / (total_charge_bcm4b_cut);
    scl_err_bcm4b = sqrt(total_htrig2_scaler_bcm4b_cut) / total_charge_bcm4b_cut;

    
    //-----NON-TRACKING Yield---
    notrk_Yield = Y_ntrk_4a / (total_charge_bcm4a_cut*cpuLT_bcm4a);

    //BCM4A
    H_hCAL_etotnorm_ntrkY_4a->Scale(1./(total_charge_bcm4a_cut*cpuLT_bcm4a));
    notrk_Yield_bcm4a = H_hCAL_etotnorm_ntrkY_4a->IntegralAndError(H_hCAL_etotnorm_ntrkY_4a->FindBin(0.6), H_hCAL_etotnorm_ntrkY_4a->FindBin(5.), notrk_err_bcm4a);
    //BCM4B
    H_hCAL_etotnorm_ntrkY_4b->Scale(1./(total_charge_bcm4b_cut*cpuLT_bcm4b));
    notrk_Yield_bcm4b = H_hCAL_etotnorm_ntrkY_4b->IntegralAndError(H_hCAL_etotnorm_ntrkY_4b->FindBin(0.6), H_hCAL_etotnorm_ntrkY_4b->FindBin(5.), notrk_err_bcm4b);


    
    //-----TRACKING Yield---
    trk_Yield = Y_trk_4a / (total_charge_bcm4a_cut*cpuLT_bcm4a*eTrkEff_bcm4a);
    //BCM4A
    H_hDelta_trkY_4a->Scale(1./(total_charge_bcm4a_cut*cpuLT_bcm4a*eTrkEff_bcm4a));
    trk_Yield_bcm4a = H_hDelta_trkY_4a->IntegralAndError(H_hDelta_trkY_4a->FindBin(-8.), H_hDelta_trkY_4a->FindBin(8.), trk_err_bcm4a);    
    //BCM4B
    H_hDelta_trkY_4b->Scale(1./(total_charge_bcm4b_cut*cpuLT_bcm4b*eTrkEff_bcm4a));
    trk_Yield_bcm4b = H_hDelta_trkY_4b->IntegralAndError(H_hDelta_trkY_4b->FindBin(-8.), H_hDelta_trkY_4b->FindBin(8.), trk_err_bcm4b);  
}


void run_boiling(string target)
{

  //User Input: target-> "Al", "C12", "LH2",  "LD2"

  Int_t runNUM;
  string line;

  //Read FileName
  //  TString filename = Form("hms_%s.dat", target.c_str());
  TString filename = "hms_test.dat";
  ifstream ifs;
  ifs.open(filename);

  //Create Output File to write results
  ofstream ofs;
  
  //ofs.open(Form("hms_%s_yield.data", target.c_str()));
  ofs.open("hms_test_yield.data");

  ofs << "#!Run[i,0]/    set_current[f,1]/   avg_current_bcm4a[f,2]/     sclY4a[f,3]/     sclY_err4a[f,4]/    ntrkY4a[f,5]/    ntrkY_err4a[f,6]/    trkY4a[f,7]/    trkY_err4a[f,8]/    cpuLT_bcm4a[f,9]/     tLT_bcm4a[f,10]/    Qtot_bcm4a[f,11]/    hs1x_rate_bcm4a[f,12]/    htrig1_rate_bcm4a[f,13]/     htrig2_rate_bcm4a[f,14]/     htrig3_rate_bcm4a[f,15]/    hedtm_rate_bcm4a[f,16]/   h_eTrkEff_bcm4a[f,17]/      avg_current_bcm4b[f,18]/     sclY4b[f,19]/     sclY_err4b[f,20]/    ntrkY4b[f,21]/    ntrkY_err4b[f,22]/    trkY4b[f,23]/    trkY_err4b[f,24]/    cpuLT_bcm4b[f,25]/     tLT_bcm4b[f,26]/    Qtot_bcm4b[f,27]/     hs1x_rate_bcm4b[f,28]/      htrig1_rate_bcm4b[f,29]/     htrig2_rate_bcm4b[f,30]/     htrig3_rate_bcm4b[f,31]/    hedtm_rate_bcm4b[f,32]/   h_eTrkEff_bcm4b[f,33]/" << endl;
    
  
  //Variables to be passed to function
  Double_t set_current;
  Double_t sclY4a, sclY4a_err;
  Double_t ntrkY4a, ntrkY4a_err;
  Double_t trkY4a, trkY4a_err;
  Double_t avg_current_bcm4a;
  Double_t cpuLT_bcm4a;
  Double_t tLT_bcm4a;
  Double_t Qtot_bcm4a;
  Double_t htrig1_rate_bcm4a;
  Double_t htrig2_rate_bcm4a;
  Double_t htrig3_rate_bcm4a;
  Double_t hedtm_rate_bcm4a;
  Double_t h_eTrkEff_bcm4a;
  Double_t hs1x_rate_bcm4a;

  //BCM4B
  Double_t sclY4b, sclY4b_err;
  Double_t ntrkY4b, ntrkY4b_err;
  Double_t trkY4b, trkY4b_err;
  Double_t avg_current_bcm4b;
  Double_t cpuLT_bcm4b;
  Double_t tLT_bcm4b;
  Double_t Qtot_bcm4b;
  Double_t htrig1_rate_bcm4b;
  Double_t htrig2_rate_bcm4b;
  Double_t htrig3_rate_bcm4b;
  Double_t hedtm_rate_bcm4b;
  Double_t h_eTrkEff_bcm4b;
  Double_t hs1x_rate_bcm4b;
  
  //Read run txt file
  while (getline(ifs, line)){
    
    //convert run from string to int
    runNUM = stoi(line);  
    
    get_boiling(runNUM, set_current,  avg_current_bcm4a, sclY4a, sclY4a_err, ntrkY4a, ntrkY4a_err, trkY4a, trkY4a_err,
		cpuLT_bcm4a, tLT_bcm4a, Qtot_bcm4a, hs1x_rate_bcm4a, htrig1_rate_bcm4a, htrig2_rate_bcm4a, htrig3_rate_bcm4a, hedtm_rate_bcm4a, h_eTrkEff_bcm4a,
		avg_current_bcm4b, sclY4b, sclY4b_err, ntrkY4b, ntrkY4b_err, trkY4b, trkY4b_err,
		cpuLT_bcm4b, tLT_bcm4b, Qtot_bcm4b, hs1x_rate_bcm4b, htrig1_rate_bcm4b, htrig2_rate_bcm4b, htrig3_rate_bcm4b, hedtm_rate_bcm4b, h_eTrkEff_bcm4b);
    
    //Write to file
    ofs << Form("%i     %f     %f      %f     %f     %f     %f     %f     %f     %f     %f     %f     %f    %f    %f     %f     %f    %f    %f    %f     %f     %f     %f     %f     %f     %f     %f     %f    %f    %f     %f     %f    %f    %f", runNUM, set_current, avg_current_bcm4a, sclY4a, sclY4a_err, ntrkY4a, ntrkY4a_err, trkY4a, trkY4a_err, cpuLT_bcm4a, tLT_bcm4a, Qtot_bcm4a, hs1x_rate_bcm4a, htrig1_rate_bcm4a, htrig2_rate_bcm4a, htrig3_rate_bcm4a, hedtm_rate_bcm4a, h_eTrkEff_bcm4a, avg_current_bcm4b, sclY4b, sclY4b_err, ntrkY4b, ntrkY4b_err, trkY4b, trkY4b_err, cpuLT_bcm4b, tLT_bcm4b, Qtot_bcm4b, hs1x_rate_bcm4b, htrig1_rate_bcm4b, htrig2_rate_bcm4b, htrig3_rate_bcm4b, hedtm_rate_bcm4b, h_eTrkEff_bcm4b) << endl;



  }
  
}
