//#include "example.h"
//Define and Set REF. TIME CUTS 
//0.0625 ns / Ch., in case it is used

void setTimeWindows_v2()
{

  //(See /PARAM/HMS/GEN/h_reftime_cut.param, units in Channel)
  static const Double_t hhod_trefcut = 2100.;      //hodo tdc ref cut
  static const Double_t hdc_trefcut = 15600.;      //dc tdc ref cut
  static const Double_t hadc_trefcut = 3150.;      //hodo/cer/cal adc ref cut
  
  //(See /PARAM/SHMS/GEN/p_reftime_cut.param, units in Channel)
  static const Double_t phod_trefcut = 3000.;
  static const Double_t pdc_trefcut = 13500.;
  static const Double_t padc_trefcut = 3000.;  
  
  //Define some detectors planes and sides
  static const Int_t hod_PLANES = 4;
  static const Int_t cal_PLANES = 4;
  static const Int_t dc_PLANES = 12;
  static const Int_t SIDES = 2;
  
  static const string hod_pl_names[hod_PLANES] = {"1x", "1y", "2x", "2y"};
  static const string cal_pl_names[cal_PLANES] = {"1pr", "2ta", "3ta", "4ta"};
  
  //For SHMS, P.cal.fly.goodAdcTdcDiffTime
  // P.cal.pr.good{Pos,Neg}AdcMult or AdcTdcDiffTime
  
  static const string hdc_pl_names[dc_PLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  static const string pdc_pl_names[dc_PLANES] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
  
  static const string side_names[SIDES] = {"GoodPos", "GoodNeg"};
  static const string cal_side_names[SIDES] = {"goodPos", "goodNeg"};
  
  static const string nsign[SIDES] = {"+", "-"};
  
  static const Int_t hmaxPMT[hod_PLANES] = {16, 10, 16, 10};
  static const Int_t pmaxPMT[hod_PLANES] = {13, 13, 14, 21};
  

  //Define REF Time Histogram Binning
  //HMS
  Double_t hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax;
  Double_t hdc_tref_nbins, hdc_tref_xmin, hdc_tref_xmax;
  Double_t hadc_tref_nbins, hadc_tref_xmin, hadc_tref_xmax;
  //SHMS
  Double_t phod_tref_nbins, phod_tref_xmin, phod_tref_xmax;
  Double_t pdc_tref_nbins, pdc_tref_xmin, pdc_tref_xmax;
  Double_t padc_tref_nbins, padc_tref_xmin, padc_tref_xmax;
  

  //Define ADC:TDC Time Diff. Histogram Bins
  //HMS
  Double_t hhod_nbins, hhod_xmin, hhod_xmax;
  Double_t hdc_nbins, hdc_xmin, hdc_xmax;
  Double_t hcer_nbins, hcer_xmin, hcer_xmax;                                                                                              
  Double_t hcal_nbins, hcal_xmin, hcal_xmax;                                                                                                                    
  //SHMS
  Double_t phod_nbins, phod_xmin, phod_xmax;
  Double_t pdc_nbins, pdc_xmin, pdc_xmax;
  Double_t phgcer_nbins, phgcer_xmin, phgcer_xmax;                                                                                              
  Double_t pngcer_nbins, pngcer_xmin, pngcer_xmax;
  Double_t pPrsh_nbins, pPrsh_xmin, pPrsh_xmax;                                                                                                                                                                                                   
  Double_t pcal_nbins, pcal_xmin, pcal_xmax;                                                                                                                    
  
  //Define Histograms for reference time Cuts
  //HMS
  TH1F *H_hodo_Tref;
  TH1F *H_DC_Tref[4];
  TH1F *H_FADC_Tref;
  //SHMS
  TH1F *P_hodo_Tref;
  TH1F *P_DC_Tref[10];
  TH1F *P_FADC_Tref;
  
  //Define Histograms for Time Window Cuts
  //HMS
  TH1F *H_hod_TdcAdcTimeDiff[hod_PLANES][SIDES][16];
  TH1F *H_cal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
  TH1F *H_dc_rawTDC[dc_PLANES];
  TH1F *H_cer_TdcAdcTimeDiff[2];
  
  //SHMS
  TH1F *P_hod_TdcAdcTimeDiff[hod_PLANES][SIDES][21];
  TH1F *P_cal_TdcAdcTimeDiff[224];  //fly's eye (224 pmt-channels)
  TH1F *P_prSh_TdcAdcTimeDiff[SIDES][14];
  TH1F *P_dc_rawTDC[dc_PLANES];
  TH1F *P_hgcer_TdcAdcTimeDiff[4];
  TH1F *P_ngcer_TdcAdcTimeDiff[4];


  //Define Arrays to store Min/Max Time Window Cuts
  //HMS
  Double_t hhodo_tWinMin[hod_PLANES][SIDES][16] = {0.};
  Double_t hhodo_tWinMax[hod_PLANES][SIDES][16] = {0.};
  
  Double_t hCal_tWinMin[cal_PLANES][SIDES][13] = {0.};
  Double_t hCal_tWinMax[cal_PLANES][SIDES][13] = {0.};
  
  Double_t hCer_tWinMin[2] = {0.};
  Double_t hCer_tWinMax[2] = {0.};
  
  Double_t hDC_tWinMin[dc_PLANES] = {0.};
  Double_t hDC_tWinMax[dc_PLANES] = {0.};

  //SHMS
  Double_t phodo_tWinMin[hod_PLANES][SIDES][21] = {0.};
  Double_t phodo_tWinMax[hod_PLANES][SIDES][21] = {0.};
  
  Double_t pCal_tWinMin[224] = {0.};
  Double_t pCal_tWinMax[224] = {0.};
  
  Double_t pPrsh_tWinMin[SIDES][14] = { 0.};
  Double_t pPrsh_tWinMax[SIDES][14] = { 0.};

  Double_t phgcer_tWinMin[2] = {0.};
  Double_t phgcer_tWinMax[2] = {0.};
  
  Double_t pngcer_tWinMin[4] = {0.};
  Double_t pngcer_tWinMax[4] = {0.};
  
  Double_t pDC_tWinMin[dc_PLANES] = {0.};
  Double_t pDC_tWinMax[dc_PLANES] = {0.};


  //Define Canvas
  //HMS
  TCanvas *hms_REF_Canv;                      //canvas to save reference time histograms
  TCanvas *hhodoCanv[hod_PLANES][SIDES];
  TCanvas *hcaloCanv[cal_PLANES][SIDES];
  TCanvas *hdcCanv;
  TCanvas *hCer_Canv;
  //SHMS
  TCanvas *shms_REF_Canv;                      //canvas to save reference time histograms
  TCanvas *phodoCanv[hod_PLANES][SIDES];
  TCanvas *pcalCanv;
  TCanvas *pPrshCanv[SIDES];
  TCanvas *pdcCanv;
  TCanvas *pngCer_Canv;
  TCanvas *phgCer_Canv;
  
  //Define and set Multiple of Sigma to place cuts (Mean +/- nSig*sig) around ADC:TDC Time Diff HERE ! ! !
  //HMS
  Double_t hhod_nSig;
  Double_t hdc_nSig; 
  Double_t hcer_nSig;
  Double_t hcal_nSig;
  //SHMS
  Double_t phod_nSig;
  Double_t pdc_nSig; 
  Double_t phgcer_nSig;
  Double_t pngcer_nSig;
  Double_t pcal_nSig;
  
  //Mean and Sigma. Variables to determine TimeWindow Cut Region
  Double_t mean; 
  Double_t sig;
  
  
  //Define TLines to draw around Cut Region
  
  //Reference Time TLines
  //HMS
  TLine *hT1_Line;      //hms trigger ref. time
  TLine *hDCREF_Line;  //hms DC ref. time
  TLine *hFADC_Line;    //flash ADC ref. time
  //SHMS
  TLine *pT2_Line;      //shms trigger ref. time
  TLine *pDCREF_Line;  //shms DC ref. time
  TLine *pFADC_Line;    //flash ADC ref. time
  
  
  //Detectors Time Window CUts Lines
  //HMS
  TLine *hhod_LineMin[hod_PLANES][SIDES][16];
  TLine *hhod_LineMax[hod_PLANES][SIDES][16];
  
  TLine *hcal_LineMin[cal_PLANES][SIDES][13];
  TLine *hcal_LineMax[cal_PLANES][SIDES][13];
  
  TLine *hdc_LineMin[dc_PLANES];
  TLine *hdc_LineMax[dc_PLANES];
  
  TLine *hCER_LineMin[2];
  TLine *hCER_LineMax[2];
  
  //SHMS
  TLine *phod_LineMin[hod_PLANES][SIDES][21];
  TLine *phod_LineMax[hod_PLANES][SIDES][21];
  
  TLine *pcal_LineMin[224];
  TLine *pcal_LineMax[224];
  
  TLine *pPrsh_LineMin[14];
  TLine *pPrsh_LineMax[14];
  
  TLine *pdc_LineMin[dc_PLANES];
  TLine *pdc_LineMax[dc_PLANES];
  
  TLine *phgcer_LineMin[2];
  TLine *phgcer_LineMax[2];
  
  TLine *pngcer_LineMin[2];
  TLine *pngcer_LineMax[2];
  
  
  TString base;
  
  //Define Hodo Leafs to be read from TTree                                                                                                                                             
  //HMS Leaf Names                                                                                                                                                                     
  TString n_hhod_TdcAdcTimeDiff;                                                                                                                                             
  TString n_hhod_AdcMult;                                                                                                                                                   
  TString n_hcal_TdcAdcTimeDiff;                                                                                                                                               
  TString n_hcal_AdcMult;                                                                                                                                                         
  TString n_hcer_TdcAdcTimeDiff;                                                                                                                      
  TString n_hcer_AdcMult;                                                                                                                                                                
  TString n_hndata_rawTDC;                                                                                                                          
  TString n_hdc_rawTDC; 
  
  //HMS Ref. Time Names
  TString n_hT1_ref;
  TString n_hDC_ref;
  TString n_hFADC_ref;
  TString n_hT1_tdcMult;
  TString n_hDC_tdcMult;
  TString n_hFADC_adcMult;
  
  //SHMS Leaf Names              
  TString n_phod_TdcAdcTimeDiff;                                                                                                                                                         
  TString n_phod_AdcMult;                                                                                                                                                              
  TString n_pcal_TdcAdcTimeDiff;                                                                                                                                                        
  TString n_pcal_AdcMult;                                                                                                                                                               
  TString n_pPrSh_TdcAdcTimeDiff;
  TString n_pPrSh_AdcMult;
  TString n_phgcer_TdcAdcTimeDiff;                                                                                                                                          
  TString n_phgcer_AdcMult;
  TString n_pngcer_TdcAdcTimeDiff;                                                                                                                                                      
  TString n_pngcer_AdcMult;
  TString n_pdc_rawTDC;                                                                                                                                                               
  TString n_pndata_rawTDC;                                                                                                                                                               
  
  //Ref. Time Names                                                                                                                                                                      
  TString n_pT2_ref;                                                                                                                                                
  TString n_pDC_ref;                                                                                                                                                    
  TString n_pFADC_ref;        
  TString n_pT2_tdcMult;                                                                                                                                                
  TString n_pDC_tdcMult;                                                                                                                                                    
  TString n_pFADC_adcMult;                                                                                                                                 
  
  
  //Define Variables Associated with Leafs
  //HMS Leaf Variables
  Double_t hhod_TdcAdcTimeDiff[hod_PLANES][SIDES][16];
  Double_t hhod_AdcMult[hod_PLANES][SIDES][16];
  Double_t hcal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
  Double_t hcal_AdcMult[cal_PLANES][SIDES][13];
  Double_t hcer_TdcAdcTimeDiff[2];
  Double_t hcer_AdcMult[2];

  //HMS Ref. Time Varables                                                                                                                                           
  Double_t hT1_ref;                                                                                                    
  Double_t hDC_ref[4];                                                                                      
  Double_t hFADC_ref;
  Double_t hT1_tdcMult;
  Double_t hDC_tdcMult[4];
  Double_t hFADC_adcMult;

  //SHMS Leaf Variables
  Double_t phod_TdcAdcTimeDiff[hod_PLANES][SIDES][21];
  Double_t phod_AdcMult[hod_PLANES][SIDES][21];
  Double_t pcal_TdcAdcTimeDiff[1][224];
  Double_t pcal_AdcMult[1][224];
  Double_t pPrSh_TdcAdcTimeDiff[1][SIDES][14]; 
  Double_t pPrSh_AdcMult[1][SIDES][14]; 
  Double_t phgcer_TdcAdcTimeDiff[2];
  Double_t phgcer_AdcMult[2];
  Double_t pngcer_TdcAdcTimeDiff[4];
  Double_t pngcer_AdcMult[4];

  //SHMS Ref. Time Varables                                                                                                                                           
  Double_t pT2_ref;                                                                                                    
  Double_t pDC_ref[10];                                                                                      
  Double_t pFADC_ref;
  Double_t pT2_tdcMult;
  Double_t pDC_tdcMult[10];
  Double_t pFADC_adcMult;
 
  //Drift Chamber rawTDC / Ndata
  Double_t hdc_rawTDC[dc_PLANES][1000];
  Double_t pdc_rawTDC[dc_PLANES][1000];

  Int_t hndata_rawTDC[dc_PLANES];
  Int_t pndata_rawTDC[dc_PLANES];
  

  //REF Time Histos (Bin Width was consistently set to 2)
  //HMS                           SHMS
  hhod_tref_nbins = 100,          phod_tref_nbins = 100;
  hhod_tref_xmin = 1700,          phod_tref_xmin = 1500;
  hhod_tref_xmax = 2500,          phod_tref_xmax = 4200;

  hdc_tref_nbins = 200,           pdc_tref_nbins = 100;
  hdc_tref_xmin = 14600,          pdc_tref_xmin = 13500;
  hdc_tref_xmax = 16000,          pdc_tref_xmax = 15000;
 
  hadc_tref_nbins = 150,          padc_tref_nbins = 100;
  hadc_tref_xmin = 3000,          padc_tref_xmin = 2000;
  hadc_tref_xmax = 3300,          padc_tref_xmax = 4500;


  
  //ADC:TDC Time Diff Histos
  //HMS               SHMS
  hhod_nbins = 50,    phod_nbins = 50;    
  hhod_xmin = -70,    phod_xmin = -70;    
  hhod_xmax = -40,    phod_xmax = -40;                                              
  hdc_nbins = 100,    pdc_nbins = 500;                                                      
  hdc_xmin = -16000,  pdc_xmin = -20000;                                                                
  hdc_xmax = -10000,   pdc_xmax = -5000;  

  hcer_nbins = 200,   phgcer_nbins = 200,    pngcer_nbins = 200;                                                                                                                                     
  hcer_xmin = 50,     phgcer_xmin = -100,      pngcer_xmin = 50;                                                                                                                                   
  hcer_xmax = 150,    phgcer_xmax = 100,     pngcer_xmax = 150;                                                                                                                 
                                          
  hcal_nbins = 200,   pPrsh_nbins = 200,      pcal_nbins = 200;                                                                                                                                            
  hcal_xmin = -140,   pPrsh_xmin = -140,      pcal_xmin = -140;                                                                                                                    
  hcal_xmax = -60,    pPrsh_xmax = -60,       pcal_xmax = -60; 


  //Set ADC:TDC Time Window Cut Range
  //Based on multiples of sigma from the histos
  hhod_nSig = 6.0;
  hdc_nSig = 5.5; 
  hcer_nSig = 3.5;  
  hcal_nSig = 4.0;
  
  phod_nSig = 6.0;
  pdc_nSig = 5.5; 
  phgcer_nSig = 3.5;
  pngcer_nSig = 3.5;
  pcal_nSig = 4.0;


  //gROOT->SetBatch(kTRUE);


  //=========================
  //====OPEN ROOT FILE=======
  //=========================

  Int_t runNUM = 3288;
  string daq = "coin";    //or hms, shms  (single arm mode)
  string rtype = "coin";  //or "hms", "shms"  (singles in coin mode)
  
  TString filename = "coin_replay_timeWin_check_3288_1000.root";

  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");
  
  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("%s_histos_run%d.root", rtype.c_str(), runNUM), "recreate");
         


  //===========================
  //===Reference Time Leafs====
  //===========================
  


  //HMS REF-TIME LEAFS
  for (int i=0; i<4; i++)
    {
      n_hDC_ref = Form("T.coin.hDCREF%d_tdcTimeRaw", i+1);
      n_hDC_tdcMult = Form("T.coin.hDCREF%d_tdcMultiplicity", i+1);
      
      T->SetBranchAddress(n_hDC_ref, &hDC_ref[i]);
      T->SetBranchAddress(n_hDC_tdcMult, &hDC_tdcMult[i]);
      
      H_DC_Tref[i] = new TH1F(Form("hDC%d_refTime", i+1), Form("HMS DC Ref %d", i+1), hdc_tref_nbins,  hdc_tref_xmin, hdc_tref_xmax);

    }

  H_hodo_Tref = new TH1F("hT1_ref", "HMS Hodo hT1 Ref. Time", hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);
  H_FADC_Tref = new TH1F("hFADC_ref", "HMS fADC Ref. Time", hadc_tref_nbins,  hadc_tref_xmin, hadc_tref_xmax);


  n_hT1_ref = "T.coin.hT1_tdcTimeRaw";
  n_hFADC_ref = "T.coin.hFADC_TREF_ROC1_adcPulseTimeRaw";
  n_hT1_tdcMult = "T.coin.hT1_tdcMultiplicity";
  n_hFADC_adcMult = "T.coin.hFADC_TREF_ROC1_adcMultiplicity";
  
  T->SetBranchAddress(n_hT1_ref, &hT1_ref);     
  T->SetBranchAddress(n_hFADC_ref, &hFADC_ref);
  T->SetBranchAddress(n_hT1_tdcMult, &hT1_tdcMult);
  T->SetBranchAddress(n_hFADC_adcMult, &hFADC_adcMult);
  
  
  //SHMS REF-TIME LEAFS 
  for (int i=0; i<10; i++)
    {
      n_pDC_ref = Form("T.coin.pDCREF%d_tdcTimeRaw", i+1);
      n_pDC_tdcMult = Form("T.coin.pDCREF%d_tdcMultiplicity", i+1);
      
      T->SetBranchAddress(n_pDC_ref, &pDC_ref[i]);
      T->SetBranchAddress(n_pDC_tdcMult, &pDC_tdcMult[i]);
           
      P_DC_Tref[i] = new TH1F(Form("pDC%d_refTime", i+1), Form("SHMS DC Ref %d", i+1), pdc_tref_nbins,  pdc_tref_xmin, pdc_tref_xmax);

    }
  
  n_pT2_ref = "T.coin.pT2_tdcTimeRaw";
  n_pT2_tdcMult = "T.coin.pT2_tdcMultiplicity";
  n_pFADC_ref = "T.coin.pFADC_TREF_ROC2_adcPulseTimeRaw";
  n_pFADC_adcMult = "T.coin.pFADC_TREF_ROC2_adcMultiplicity";

  P_hodo_Tref = new TH1F("pT2_ref", "SHMS Hodo pT2 Ref. Time", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);
  P_FADC_Tref = new TH1F("pFADC_ref", "SHMS fADC Ref. Time", padc_tref_nbins,  padc_tref_xmin, padc_tref_xmax);


  T->SetBranchAddress(n_pT2_ref, &pT2_ref);
  T->SetBranchAddress(n_pT2_tdcMult, &pT2_tdcMult);
  T->SetBranchAddress(n_pFADC_ref, &pFADC_ref);
  T->SetBranchAddress(n_pFADC_adcMult, &pFADC_adcMult);
  
  //======================================
  //=======Detector Time Window Leafs=====
  //======================================
  

 
  //Loop over Cherenkov PMTs
  for (Int_t ipmt = 0; ipmt < 4; ipmt++ )
    {  
      
      if (ipmt<2)
	{
	  //HMS  Cherenkov
	  n_hcer_TdcAdcTimeDiff =  "H.cer.goodAdcTdcDiffTime";
	  n_hcer_AdcMult = "H.cer.goodAdcMult";
	  
	  T->SetBranchAddress(n_hcer_AdcMult, &hcer_AdcMult);
	  T->SetBranchAddress(n_hcer_TdcAdcTimeDiff, &hcer_TdcAdcTimeDiff);
	  
	  H_cer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("hCER%d_timeDiff", ipmt+1), Form("HMS Cer %d AdcTdcTimeDiff", ipmt+1), hcer_nbins, hcer_xmin, hcer_xmax);
	  
	}
 
	  //SHMS Heavy Gas Cherenkov
	  n_phgcer_TdcAdcTimeDiff =  "P.hgcer.goodAdcTdcDiffTime";
	  n_phgcer_AdcMult = "P.hgcer.goodAdcMult";
	  
	  T->SetBranchAddress(n_phgcer_AdcMult, &phgcer_AdcMult);
	  T->SetBranchAddress(n_phgcer_TdcAdcTimeDiff, &phgcer_TdcAdcTimeDiff);
	  
	  P_hgcer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pHGCER%d_timeDiff", ipmt+1), Form("SHMS Heavy Gas Cer%d AdcTdcTimeDiff", ipmt+1), phgcer_nbins, phgcer_xmin, phgcer_xmax);
	  
	  //SHMS Noble Gas Cherenkov
	  n_pngcer_TdcAdcTimeDiff =  "P.ngcer.goodAdcTdcDiffTime";
	  n_pngcer_AdcMult = "P.ngcer.goodAdcMult";
	  
	  T->SetBranchAddress(n_pngcer_AdcMult, &pngcer_AdcMult);
	  T->SetBranchAddress(n_pngcer_TdcAdcTimeDiff, &pngcer_TdcAdcTimeDiff);
	  
	  P_ngcer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pNGCER%d_timeDiff", ipmt+1), Form("SHMS Noble Gas Cer%d AdcTdcTimeDiff", ipmt+1), pngcer_nbins, pngcer_xmin, pngcer_xmax);
	  
 
    }

      
 //Loop over drift chamber planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {

      //HMS
      base = "H.dc." + hdc_pl_names[npl];
      n_hdc_rawTDC = base + "." + "rawtdc";
      n_hndata_rawTDC = "Ndata." + n_hdc_rawTDC;
      
      T->SetBranchAddress(n_hdc_rawTDC, hdc_rawTDC[npl]);
      T->SetBranchAddress(n_hndata_rawTDC, &hndata_rawTDC[npl]);
      
      H_dc_rawTDC[npl] = new TH1F(Form("hDC%s_rawTDC", hdc_pl_names[npl].c_str()), Form("HMS DC Plane %s Raw TDC", hdc_pl_names[npl].c_str()), hdc_nbins, hdc_xmin, hdc_xmax);

      //SHMS
      base = "P.dc." + pdc_pl_names[npl];
      n_pdc_rawTDC = base + "." + "rawtdc";
      n_pndata_rawTDC = "Ndata." + n_pdc_rawTDC;

      T->SetBranchAddress(n_pdc_rawTDC, pdc_rawTDC[npl]);
      T->SetBranchAddress(n_pndata_rawTDC, &pndata_rawTDC[npl]);
      
      P_dc_rawTDC[npl] = new TH1F(Form("pDC%s_rawTDC", hdc_pl_names[npl].c_str()), Form("SHMS DC Plane %s Raw TDC", hdc_pl_names[npl].c_str()), pdc_nbins, pdc_xmin, pdc_xmax);

    }

 //Loop over hodo/calorimeter planes
  for (Int_t npl = 0; npl < hod_PLANES; npl++ )
    {
      
      //Loop over hodo/calorimeter sides
      for (Int_t iside = 0; iside < SIDES; iside++)
	{
	    
	  //Loop over HMS hodo PMTs
	  for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++)
	    {
	      base = "H.hod." + hod_pl_names[npl];
	      
	      n_hhod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      n_hhod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	      
	      T->SetBranchAddress(n_hhod_TdcAdcTimeDiff, &hhod_TdcAdcTimeDiff[npl][iside][ipmt]);
	      T->SetBranchAddress(n_hhod_AdcMult, &hhod_AdcMult[npl][iside][ipmt]);

	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hhod_nbins,hhod_xmin,hhod_xmax);

	    }

	  //Loop over HMS calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	      base =  "H.cal." + cal_pl_names[npl];
	      
	      n_hcal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      n_hcal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	      T->SetBranchAddress(n_hcal_TdcAdcTimeDiff, &hcal_TdcAdcTimeDiff[npl][iside][ipmt]);
	      T->SetBranchAddress(n_hcal_AdcMult, &hcal_AdcMult[npl][iside][ipmt]);
	  
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hcal_nbins,hcal_xmin,hcal_xmax) ;

	    }


	  //Loop over SHMS hodo PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {
	      base = "P.hod." + hod_pl_names[npl];
	      
	      n_phod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      n_phod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	  	
	      T->SetBranchAddress(n_phod_TdcAdcTimeDiff, &phod_TdcAdcTimeDiff[npl][iside][ipmt]);
	      T->SetBranchAddress(n_phod_AdcMult, &phod_AdcMult[npl][iside][ipmt]);
	    	     
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("pHod%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("SHMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),phod_nbins,phod_xmin,phod_xmax);

	    }
	  
	  if(npl==0)
	    {
	      //Loop over SHMS PreSH PMTs
	      for (Int_t ipmt = 0; ipmt < 14; ipmt++)
		{
		  base =  "P.cal.pr";
		  
		  n_pPrSh_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
		  n_pPrSh_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";
		  
		  T->SetBranchAddress(n_pPrSh_TdcAdcTimeDiff, &pPrSh_TdcAdcTimeDiff[npl][iside][ipmt]);
		  T->SetBranchAddress(n_pPrSh_AdcMult, &pPrSh_AdcMult[npl][iside][ipmt]);
	      
		  P_prSh_TdcAdcTimeDiff[iside][ipmt] = new TH1F(Form("pPrSh_pmt%d%s", ipmt+1, nsign[iside].c_str()), Form("SHMS Pre-Shower PMT_%d%s", ipmt+1, nsign[iside].c_str()), pPrsh_nbins, pPrsh_xmin, pPrsh_xmax);
		}
	      if(iside==0)
		{
		  //Loop over SHMS fly's eye Calorimeter
		  for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		    {
		      base =  "P.cal.fly";
		      n_pcal_TdcAdcTimeDiff = base + "." + "goodAdcTdcDiffTime";
		      n_pcal_AdcMult = "totNumGoodAdcHits";
		      //For multiplicity, see THcSHowerArray.cxx, for totNumGoodAdcHits, 
		      T->SetBranchAddress(n_pcal_TdcAdcTimeDiff, &pcal_TdcAdcTimeDiff[iside][ipmt]);
		      
		      P_cal_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pSh_pmt%d", ipmt+1), Form("SHMS Pre-Shower PMT_%d", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
		    }
		} //end side0 requirement for fly's eye

	    } //End plane 0 requirement for Pre-SHower


	} //End Loop over sides

    } //End Loop over planes
      

  //===================================
  //====== E V E N T    L O O P =======
  //===================================

  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i); 


      //--------------Loop over HMS/SHMS Ref. TImes-------------------

      //Define Multiplicity Cuts Here

      //SHMS DC Ref Times
      for (int iref=0; iref<10; iref++)
	{

	  P_DC_Tref[iref]->Fill(pDC_ref[iref]);
	  
	  //HMS DC Ref. Times
	  if(iref<4)
	    {
	      H_DC_Tref[iref]->Fill(hDC_ref[iref]);
	    }
	}

      //HMS Ref
      H_hodo_Tref->Fill(hT1_ref);
      H_FADC_Tref->Fill(hFADC_ref);

      //SHMS Ref
      P_hodo_Tref->Fill(pT2_ref);
      P_FADC_Tref->Fill(pFADC_ref);

      

      //------------------------------------------------------------------------------
 
      //Loop over Cherenkov PMTs
      for (Int_t ipmt = 0; ipmt < 4; ipmt++)
	{                                                                                                                                             
	  
	  if(ipmt < 2)
	    {
	      //----HMS Cherenkov----
	      
	      //Define Multiplicity Cuts
	      
	      //Require ADC Multiplicity == 1  NOT YET DONE . . .
	      if (1)
		{
		  cout << hcer_TdcAdcTimeDiff[ipmt] << endl;
		  H_cer_TdcAdcTimeDiff[ipmt]->Fill(hcer_TdcAdcTimeDiff[ipmt]);
		  
		}
	    }
	  
	  //----SHMS Heavy Gas Cherenkov-----
	  
	  //Define Multiplicity Cuts

	  //Require ADC Multiplicity == 1
	  if (1)
	    {
	      P_hgcer_TdcAdcTimeDiff[ipmt]->Fill(phgcer_TdcAdcTimeDiff[ipmt]);
	      
	    }
	
	  //----SHMS Noble Gas Cherenkov-----
	  
	  //Define Multiplicity Cuts

	  //Require ADC Multiplicity == 1
	  if (1)
	    {
	      P_ngcer_TdcAdcTimeDiff[ipmt]->Fill(pngcer_TdcAdcTimeDiff[ipmt]);
	      
	    }
	  

	} //End Cherenkov PMT loop




      //-----------------------------------------------------------------------------

      //Loop over Drift Chamber Planes
      for (Int_t npl = 0; npl<dc_PLANES; npl++)
	{


	  //-------HMS Drift Chambers----------
	  
	  //Define Cuts Here

	  //Loop over all hits per event
	      for(Int_t j = 0; j < hndata_rawTDC[npl]; j++)
		{
	        
		  H_dc_rawTDC[npl]->Fill(hdc_rawTDC[npl][j]);
		}
	    
	  

	  //--------SHMS Drift Chambers--------
	  
	  //Define Cuts Here

	  //Loop over all hits per event
	  for(Int_t j = 0; j < pndata_rawTDC[npl]; j++)
	    {
	      P_dc_rawTDC[npl]->Fill(pdc_rawTDC[npl][j]);
	    }

	
	}
      

      //-------------------------------------------------------------------------------


      //Loop over Hodoscopes/Calorimeter Planes
      for (Int_t ip =0; ip < hod_PLANES; ip++)
	{


	  //Loop over hodo/calorimeter side
	  for (Int_t iside = 0; iside < SIDES; iside++)
	    {

	      //Loop over Hodoscopes PMTs
	      for (Int_t ipmt = 0; ipmt < hmaxPMT[ip]; ipmt++)
		{

		  //DEfine Multiplicity CUts here

		  //-------------HMS Hodoscopoes--------------
		  H_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hhod_TdcAdcTimeDiff[ip][iside][ipmt]);
	  
		}

	      //Loop over Calorimeter PMTs
	      for (Int_t ipmt = 0; ipmt < 13; ipmt++)
		{

		  //------------HMS Calorimeter----------------

		  //DEfine Multiplicity CUts here
		   

		  H_cal_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);



		}
	      
	      
	      //Loop over SHMS Hodoscopes PMTs
	      for (Int_t ipmt = 0; ipmt < pmaxPMT[ip]; ipmt++)
		{
		  
		  //------------SHMS Hodoscopes----------------

		  P_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(phod_TdcAdcTimeDiff[ip][iside][ipmt]);

		}

	      
	      
	      //------------SHMS PreSHower-------------------
	      	  
	      //Loop over SHMS PrSh PMTs
	      for (Int_t ipmt=0; ipmt < 14; ipmt++)
		{
		   
		  if(ip==0){
		  P_prSh_TdcAdcTimeDiff[iside][ipmt]->Fill(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt]);
		  }
       

		} //End loop over SHMS PrSH PMTs

	      
	      //----------SHMS FLy's Eye Calorimeter-------------
	      for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		{
		  if(ip==0&&iside==0)
		    {
		      P_cal_TdcAdcTimeDiff[ipmt]->Fill(pcal_TdcAdcTimeDiff[iside][ipmt]);
		    }
		}
	      


	    } // END LOOP OVER SIDES

	} //END LOOP OVER PLANES


    } //END EVENT LOOP
  
  

  //DRAW HISTOGRAMS TO CANVAS
  
  //-------Reference Time Histograms----------

  //HMS
  hms_REF_Canv = new TCanvas("REF Times", "HMS REF TIMES",  1500, 500);
  hms_REF_Canv->Divide(3,1);
  
  hT1_Line = new TLine(hhod_trefcut, 0,  hhod_trefcut, H_hodo_Tref->GetMaximum());
  hDCREF_Line = new TLine(hdc_trefcut, 0,  hdc_trefcut, H_DC_Tref[0]->GetMaximum());
  hFADC_Line = new TLine(hadc_trefcut, 0,  hadc_trefcut, H_FADC_Tref->GetMaximum());
  
  hms_REF_Canv->cd(1);
  gPad->SetLogy();
  H_hodo_Tref->Draw();
  hT1_Line->SetLineColor(kRed);
  hT1_Line->SetLineWidth(3);
  hT1_Line->Draw();
  
  hms_REF_Canv->cd(2);
  gPad->SetLogy();
  H_DC_Tref[0]->SetLineColor(kBlack);
  H_DC_Tref[0]->Draw();
  hDCREF_Line->SetLineColor(kRed);
  hDCREF_Line->SetLineWidth(3);
  hDCREF_Line->Draw();

  hms_REF_Canv->cd(3);
  gPad->SetLogy();
  H_FADC_Tref->Draw();
  hFADC_Line->SetLineColor(kRed);
  hFADC_Line->SetLineWidth(3);
  hFADC_Line->Draw();
  hms_REF_Canv->SaveAs("hms_REFTime_cuts.pdf");
  
  //SHMS
  shms_REF_Canv = new TCanvas("REF Times", "SHMS REF TIMES",  1500, 500);
  shms_REF_Canv->Divide(3,1);
  
  pT2_Line = new TLine(phod_trefcut, 0,  phod_trefcut, P_hodo_Tref->GetMaximum());
  pDCREF_Line = new TLine(pdc_trefcut, 0,  pdc_trefcut, P_DC_Tref[0]->GetMaximum());
  pFADC_Line = new TLine(padc_trefcut, 0,  padc_trefcut, P_FADC_Tref->GetMaximum());
  
  shms_REF_Canv->cd(1);
  gPad->SetLogy();
  P_hodo_Tref->Draw();
  pT2_Line->SetLineColor(kRed);
  pT2_Line->SetLineWidth(3);
  pT2_Line->Draw();
  
  shms_REF_Canv->cd(2);
  gPad->SetLogy();
  P_DC_Tref[0]->SetLineColor(kBlack);
  for(Int_t iref=0; iref<10; iref++)
    {
      P_DC_Tref[iref]->Draw("sames");
    }
  pDCREF_Line->SetLineColor(kRed);
  pDCREF_Line->SetLineWidth(3);
  pDCREF_Line->Draw();

  shms_REF_Canv->cd(3);
  gPad->SetLogy();
  P_FADC_Tref->Draw();
  pFADC_Line->SetLineColor(kRed);
  pFADC_Line->SetLineWidth(3);
  pFADC_Line->Draw();
  shms_REF_Canv->SaveAs("shms_REFTime_cuts.pdf");



  //-----Setting up Detector Time WIndows----

  //Cherenkovs
  
  //HMS
  hCer_Canv = new TCanvas("hCer_ADC:TDC Time Diff", "HMS Cherenkov ADC:TDC Time Diff", 1500, 500);
  hCer_Canv->Divide(2,1);

  //SHMS Heavy Gas Cherenkov
  phgCer_Canv = new TCanvas("pHGCer_ADC:TDC Time Diff", "SHMS Heavy Gas Cherenkov ADC:TDC Time Diff", 1500, 1500);
  phgCer_Canv->Divide(2,2);
  
  //Loop over hCer PMTs
  for (Int_t ipmt = 0; ipmt < 4; ipmt++ )
    {

      //HMS Cherenkov
      if(ipmt < 2)
	{
	  //Get Mean and Sigma
	  mean = H_cer_TdcAdcTimeDiff[ipmt]->GetMean();
	  sig = H_cer_TdcAdcTimeDiff[ipmt]->GetStdDev();
    
	  //Set Time Window Cuts
	  hCer_tWinMin[ipmt] = mean - hcer_nSig*sig;
	  hCer_tWinMax[ipmt] = mean + hcer_nSig*sig;
	  
	  //Set Min/Max Line Limits
	  hCER_LineMin[ipmt] = new TLine(hCer_tWinMin[ipmt], 0, hCer_tWinMin[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
	  hCER_LineMax[ipmt] = new TLine(hCer_tWinMax[ipmt], 0, hCer_tWinMax[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
	  
	  hCER_LineMin[ipmt]->SetLineColor(kRed);
	  hCER_LineMax[ipmt]->SetLineColor(kRed);
	  
	  hCer_Canv->cd(ipmt+1);
	  gPad->SetLogy();
	  H_cer_TdcAdcTimeDiff[ipmt]->Draw();
	  hCER_LineMin[ipmt]->Draw();
	  hCER_LineMax[ipmt]->Draw();
	}
    


      //Get Mean and Sigma
      mean = P_hgcer_TdcAdcTimeDiff[ipmt]->GetMean();
      sig = P_hgcer_TdcAdcTimeDiff[ipmt]->GetStdDev();
      
      //Set Time Window Cuts
      phgcer_tWinMin[ipmt] = mean - phgcer_nSig*sig;
      phgcer_tWinMax[ipmt] = mean + phgcer_nSig*sig;
      
      //Set Min/Max Line Limits
      phgcer_LineMin[ipmt] = new TLine(phgcer_tWinMin[ipmt], 0, phgcer_tWinMin[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      phgcer_LineMax[ipmt] = new TLine(phgcer_tWinMax[ipmt], 0, phgcer_tWinMax[ipmt], P_hgcer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      
      phgcer_LineMin[ipmt]->SetLineColor(kRed);
      phgcer_LineMax[ipmt]->SetLineColor(kRed);
      
      phgCer_Canv->cd(ipmt+1);
      gPad->SetLogy();
      P_hgcer_TdcAdcTimeDiff[ipmt]->Draw();
      phgcer_LineMin[ipmt]->Draw();
      phgcer_LineMax[ipmt]->Draw();
      

    }

  
  hCer_Canv->SaveAs("hCER_timeWindow.pdf");
  phgCer_Canv->SaveAs("pHGCER_timeWindow.pdf");


  //Drift Chambers
  //HMS
  hdcCanv = new TCanvas("HMS DC Raw Times", "HMS DC Raw Times", 1500, 500);
  hdcCanv->Divide(6,2);
  //SHMS
  pdcCanv = new TCanvas("SHMS DC Raw Times", "SHMS DC Raw Times", 1500, 500);
  pdcCanv->Divide(6,2);
  
  //Loop over DC planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
     
      //HMS 

      //Get Mean ans Sigma
      mean =  H_dc_rawTDC[npl]->GetMean();
      sig  = H_dc_rawTDC[npl]->GetStdDev();
    
      //Set Time Window Cuts
      hDC_tWinMin[npl] = mean - hdc_nSig*sig;
      hDC_tWinMax[npl] = mean + hdc_nSig*sig;
      
      hdc_LineMin[npl] = new TLine(hDC_tWinMin[npl], 0, hDC_tWinMin[npl], H_dc_rawTDC[npl]->GetMaximum());
      hdc_LineMax[npl] = new TLine(hDC_tWinMax[npl], 0, hDC_tWinMax[npl], H_dc_rawTDC[npl]->GetMaximum());

      hdc_LineMin[npl]->SetLineColor(kRed);
      hdc_LineMax[npl]->SetLineColor(kRed);
      
      hdcCanv->cd(npl+1);
      gPad->SetLogy();
      H_dc_rawTDC[npl]->Draw();
      hdc_LineMin[npl]->Draw();
      hdc_LineMax[npl]->Draw();
      
      //SHMS
      //Get Mean ans Sigma
      mean =  P_dc_rawTDC[npl]->GetMean();
      sig  = P_dc_rawTDC[npl]->GetStdDev();
    
      //Set Time Window Cuts
      pDC_tWinMin[npl] = mean - pdc_nSig*sig;
      pDC_tWinMax[npl] = mean + pdc_nSig*sig;
      
      pdc_LineMin[npl] = new TLine(pDC_tWinMin[npl], 0, pDC_tWinMin[npl], P_dc_rawTDC[npl]->GetMaximum());
      pdc_LineMax[npl] = new TLine(pDC_tWinMax[npl], 0, pDC_tWinMax[npl], P_dc_rawTDC[npl]->GetMaximum());

      pdc_LineMin[npl]->SetLineColor(kRed);
      pdc_LineMax[npl]->SetLineColor(kRed);
      
      pdcCanv->cd(npl+1);
      gPad->SetLogy();
      P_dc_rawTDC[npl]->Draw();
      pdc_LineMin[npl]->Draw();
      pdc_LineMax[npl]->Draw();


    }

  hdcCanv->SaveAs("hDC_rawTDC_window.pdf");
  pdcCanv->SaveAs("pDC_rawTDC_window.pdf");



  //---------------------------------------------------

  //Define Histograms for Reference time
  //HMS
  //TH1F *H_hodo_Tref = new TH1F("hhodoTref", "HMS Hodoscope hT1 TDC Raw Time",  hhod_tref_nbins, hhod_tref_xmin, hhod_tref_xmax);                                                                            
  //TH1F *H_DC_Tref[4];                                                                                     
  //TH1F *H_FADC_Tref = new TH1F("hFADC_Tref", "HMS FADC REF adcPulseTimeRaw", hadc_tref_nbins, hadc_tref_xmin, hadc_tref_xmax); 
  //for(int i=0; i<4; i++)
  // {
  //   H_DC_Tref[i] = new TH1F(Form("hDCTref_%d",i), Form("HMS DC %d REF TDC Raw Times",i), hdc_tref_nbins, hdc_tref_xmin, hdc_tref_xmax);
  // }
  
  //SHMS
  // TH1F *P_hodo_Tref = new TH1F("phodoTref", "SHMS Hodoscope pT2 TDC Raw Time", phod_tref_nbins, phod_tref_xmin, phod_tref_xmax);                                                                            
  //TH1F *P_DC_Tref[10]; // = new TH1F("pDCTref1", "SHMS DC REF TDC Raw Times", pdc_tref_nbins, pdc_tref_xmin, pdc_tref_xmax);                                                                                           
  //TH1F *P_FADC_Tref = new TH1F("pFADC_Tref", "SHMS FADC REF adcPulseTimeRaw", padc_tref_nbins, padc_tref_xmin, padc_tref_xmax); 
  //for(int i=0; i<10; i++)
  //  {
  //    P_DC_Tref[i] = new TH1F(Form("pDCTref_%d",i), Form("SHMS DC %d REF TDC Raw Times",i), pdc_tref_nbins, pdc_tref_xmin, pdc_tref_xmax);
  //  }



  //Ref. Time Names
  //TString n_hT1_ref = "T.hms.hT1_tdcTimeRaw";
  //TString n_hDC_ref1 = "T.hms.hDCREF1_tdcTimeRaw";
  //TString n_hDC_ref2 = "T.hms.hDCREF2_tdcTimeRaw";                                                                                                                           
  //TString n_hDC_ref3 = "T.hms.hDCREF3_tdcTimeRaw";                                                                                                                   
  //TString n_hDC_ref4 = "T.hms.hDCREF4_tdcTimeRaw";                                                                                                          
  //TString n_hFADC_ref = "T.hms.hFADC_TREF_ROC1_adcPulseTimeRaw";
    
  
  /*
  //---Variables---
  Double_t hod_TdcAdcTimeDiff[PLANES][SIDES][16];
  Double_t hod_AdcMult[PLANES][SIDES][16];

  Double_t cal_TdcAdcTimeDiff[PLANES][SIDES][13];
  Double_t cal_AdcMult[PLANES][SIDES][13];

  Double_t cer_TdcAdcTimeDiff[2];
  Double_t cer_AdcMult[2];

  Double_t dc_rawTDC[12][1000];
  Int_t ndata_rawTDC[12];

  //Ref. Time Varables                                                                                                                                           
  Double_t hT1_ref;                                                                                                    
  Double_t hDC_ref1;
  Double_t hDC_ref2;                                                                                                                                                        
  Double_t hDC_ref3;
  Double_t hDC_ref4;                                                                                      
  Double_t hFADC_ref;

  //Set Branch Address for reference times
  T->SetBranchAddress(n_hT1_ref, &hT1_ref);
  T->SetBranchAddress(n_hDC_ref1, &hDC_ref1);                                                                                                                   
  T->SetBranchAddress(n_hDC_ref2, &hDC_ref2);
  T->SetBranchAddress(n_hDC_ref3, &hDC_ref3);
  T->SetBranchAddress(n_hDC_ref4, &hDC_ref4);
  T->SetBranchAddress(n_hFADC_ref, &hFADC_ref);

  //Loop over Cherenkov PMTs
  for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
    {
      //Initialize Histograms
      H_cer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("hCer TDC:ADC Time Diff, PMT_%d", ipmt), Form("hCer TDC:ADC Time Diff, PMT_%d", ipmt ), cer_nbins, cer_xmin, cer_xmax);
      H_cer_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetTitle("(TDC-ADC) Time Difference (ns) ");
      H_cer_TdcAdcTimeDiff[ipmt]->GetXaxis()->CenterTitle();
      H_cer_TdcAdcTimeDiff[ipmt]->GetYaxis()->SetTitle("Counts");
      H_cer_TdcAdcTimeDiff[ipmt]->GetYaxis()->CenterTitle();

      //----Define TTree Leaf Names-----
      base = spec + ".cer.";
      ncer_TdcAdcTimeDiff = base  + "goodAdcTdcDiffTime";
      ncer_AdcMult = base + "goodAdcMult";
      
      //------Set Branch Address-------
      T->SetBranchAddress(ncer_TdcAdcTimeDiff,  &cer_TdcAdcTimeDiff);
      T->SetBranchAddress(ncer_AdcMult,  &cer_AdcMult);

    }


  //Loop over drift chamber planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
      //Initialize Histograms
      H_dc_rawTDC[npl] = new TH1F(Form("DC Raw TDC Time, %s", dc_pl_names[npl].c_str()), Form("DC Raw TDC Time, %s", dc_pl_names[npl].c_str()), dc_nbins, dc_xmin, dc_xmax);
      H_dc_rawTDC[npl]->GetXaxis()->SetTitle("Raw TDC Time (Channels) ");
      H_dc_rawTDC[npl]->GetXaxis()->CenterTitle();
      H_dc_rawTDC[npl]->GetYaxis()->SetTitle("Counts");
      H_dc_rawTDC[npl]->GetYaxis()->CenterTitle();
      
      //----Define TTree Leaf Names-----
      base = spec + ".dc." + dc_pl_names[npl];
      ndc_rawTDC = base + "." + "rawtdc";
      nndata_rawTDC = "Ndata." + ndc_rawTDC;

      //------Set Branch Address-------
      T->SetBranchAddress(ndc_rawTDC,  dc_rawTDC[npl]);
      T->SetBranchAddress(nndata_rawTDC, &ndata_rawTDC[npl]);
    }
  
  //Loop over hodo/calorimeter planes
  for (Int_t npl = 0; npl < PLANES; npl++ )
    {
      
      //Loop over hodo/calorimeter sides
      for (Int_t iside = 0; iside < SIDES; iside++)
	{
	    
	  //Loop over hodo PMTs
	  for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
	    {

	      //Initialize Histograms
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("Good TDC:ADC Time Diff, %s%d%s", hod_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), Form("Good ADC:TDC Time Difference, %s%d%s", hod_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), hod_nbins, hod_xmin, hod_xmax);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good (TDC-ADC) Time Difference (ns) ");
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitle("Counts");
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->CenterTitle();
	            

	      //----Define TTree Leaf Names-----
	      base = spec + ".hod." + hod_pl_names[npl];
	             
	      nhod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      nhod_AdcMult = base + "." + side_names[iside] + "AdcMult";

	             
	      //------Set Branch Address-------
	      T->SetBranchAddress(nhod_TdcAdcTimeDiff,  &hod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(nhod_AdcMult,  &hod_AdcMult[npl][iside]);
	        
	             
	    }

	  //Loop over calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	            
	      //Initialize Histograms
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("Good TDC:ADC Time Diff, %s%d%s", cal_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), Form("Good ADC:TDC Time Difference, %s%d%s", cal_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), cal_nbins, cal_xmin, cal_xmax);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good (TDC-ADC) Time Difference (ns) ");
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitle("Counts");
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->CenterTitle();

	      //----Define TTree Leaf Names-----
	      base = spec + ".cal." + cal_pl_names[npl];
	             
	      ncal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      ncal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	             
	      //------Set Branch Address-------
	      T->SetBranchAddress(ncal_TdcAdcTimeDiff,  &cal_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(ncal_AdcMult,  &cal_AdcMult[npl][iside]);
	       
	    }
	    
	} //End side loop

    } //End plane loop

  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {

      T->GetEntry(i);  
      
      //Fill Reference Time Histograms
      H_hodo_Tref->Fill(hT1_ref);
      H_DC_Tref1->Fill(hDC_ref1);
      H_DC_Tref2->Fill(hDC_ref2);
      H_DC_Tref3->Fill(hDC_ref3);
      H_DC_Tref4->Fill(hDC_ref4);
      H_hFADC_Tref->Fill(hFADC_ref);
                                        
      //Loop over hCer pmts
      for (Int_t ipmt = 0; ipmt < 2; ipmt++)
	{                                                                                                                                             

	  //Require ADC Multiplicity == 1
	  if (cer_AdcMult[ipmt]>=1&&abs(cer_TdcAdcTimeDiff[ipmt])<1000)
	    {
	     
	      H_cer_TdcAdcTimeDiff[ipmt]->Fill(cer_TdcAdcTimeDiff[ipmt]);
	      
	    }
	}
      
      //Loop over dc  planes

      for (Int_t npl = 0; npl < 12; npl++ )
	{
	  for(Int_t j = 0; j < ndata_rawTDC[npl]; j++)
	    {
	      
	    H_dc_rawTDC[npl]->Fill(dc_rawTDC[npl][j]);
	    
	    }
	}
      
      
      //Loop over hodo/calorimeter planes
      for (Int_t npl = 0; npl < PLANES; npl++ )
	{
	    
	  //Loop over hodo/calorimeter side
	  for (Int_t iside = 0; iside < SIDES; iside++)
	    {

	      //Loop over Calorimeter PMTs
	      for (Int_t ipmt = 0; ipmt < 13; ipmt++)
		{
		    
		  if(cal_AdcMult[npl][iside][ipmt]>=1)
		  {
		    H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Fill(cal_TdcAdcTimeDiff[npl][iside][ipmt]);
		  }
		    
		} //end calo PMT loop
	            
	      //Loop over hodo PMTs
	      for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
		{
		  //Require ADC Multiplicity == 1
		  if(hod_AdcMult[npl][iside][ipmt]>=1)
		    {
		      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Fill(hod_TdcAdcTimeDiff[npl][iside][ipmt]);
		    }
		        
		} //end hodo PMT loop
	            
	    } // end side loop

	} //end plane loop
      
    } //end entry loop

  
                                                                                                                      
                                                                
  //DRAW HISTOGRAMS TO CANVAS
  
  
  //Reference Time Histograms
  hms_REF_Canv = new TCanvas("REF Times", "HMS REF TIMES",  1000, 500);
  hms_REF_Canv->Divide(3,1);
  
  hT1_Line = new TLine(hod_trefcut, 0,  hod_trefcut, H_hodo_Tref->GetMaximum());
  hDCREF1_Line = new TLine(dc_trefcut, 0,  dc_trefcut, H_DC_Tref1->GetMaximum());
  hFADC_Line = new TLine(adc_trefcut, 0,  adc_trefcut, H_hFADC_Tref->GetMaximum());
  
  hms_REF_Canv->cd(1);
  gPad->SetLogy();
  H_hodo_Tref->Draw();
  hT1_Line->SetLineColor(kRed);
  hT1_Line->SetLineWidth(3);
  hT1_Line->Draw();
 
  hms_REF_Canv->cd(2);
  gPad->SetLogy();
  H_DC_Tref1->SetLineColor(kBlack);
  H_DC_Tref1->Draw();
  hDCREF1_Line->SetLineColor(kRed);
  hDCREF1_Line->SetLineWidth(3);
  hDCREF1_Line->Draw();

  hms_REF_Canv->cd(3);
  gPad->SetLogy();
  H_hFADC_Tref->Draw();
  hFADC_Line->SetLineColor(kRed);
  hFADC_Line->SetLineWidth(3);
  hFADC_Line->Draw();
  hms_REF_Canv->SaveAs("hms_REFTime_cuts.pdf");
  //---------------------------------------------------

  dcCanv = new TCanvas("DC Raw Times", "DC Raw Time", 1500, 500);
  dcCanv->Divide(6,2);
  
  //Loop over DC planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
     
      //Get Mean ans Sigma
      mean =  H_dc_rawTDC[npl]->GetMean();
      sig  = H_dc_rawTDC[npl]->GetStdDev();
    
      //Set Time Window Cuts
      hDC_tWinMin[npl] = mean - dc_nSig*sig;
      hDC_tWinMax[npl] = mean + dc_nSig*sig;
      
      dc_LineMin[npl] = new TLine(hDC_tWinMin[npl], 0, hDC_tWinMin[npl], H_dc_rawTDC[npl]->GetMaximum());
      dc_LineMax[npl] = new TLine(hDC_tWinMax[npl], 0, hDC_tWinMax[npl], H_dc_rawTDC[npl]->GetMaximum());

      dc_LineMin[npl]->SetLineColor(kRed);
      dc_LineMax[npl]->SetLineColor(kRed);
      
      dcCanv->cd(npl+1);
      //gPad->SetLogy();
      H_dc_rawTDC[npl]->Draw();
      dc_LineMin[npl]->Draw();
      dc_LineMax[npl]->Draw();
      
    }
  

  hCer_Canv = new TCanvas("hCer_ADC:TDC Time Diff", "DC Raw Time", 1500, 500);
  hCer_Canv->Divide(2,1);

  //Loop over hCer PMTs
  for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
    {
      //Get Mean and Sigma
      mean = H_cer_TdcAdcTimeDiff[ipmt]->GetMean();
      sig = H_cer_TdcAdcTimeDiff[ipmt]->GetStdDev();

    
      //Set Time Window Cuts
      hCer_tWinMin[ipmt] = mean - cer_nSig*sig;
      hCer_tWinMax[ipmt] = mean + cer_nSig*sig;
      
      //Set Min/Max Line Limits
      hCER_LineMin[ipmt] = new TLine(hCer_tWinMin[ipmt], 0, hCer_tWinMin[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      hCER_LineMax[ipmt] = new TLine(hCer_tWinMax[ipmt], 0, hCer_tWinMax[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
                                  
      hCER_LineMin[ipmt]->SetLineColor(kRed);
      hCER_LineMax[ipmt]->SetLineColor(kRed);
         
      hCer_Canv->cd(ipmt+1);
      gPad->SetLogy();
      H_cer_TdcAdcTimeDiff[ipmt]->Draw();
      hCER_LineMin[ipmt]->Draw();
      hCER_LineMax[ipmt]->Draw();
    
    }

  
   
  //Loop over hodo/calo planes
  for (Int_t npl = 0; npl < PLANES; npl++ )
    {      

      //Loop over plane side
      for (Int_t iside = 0; iside < SIDES; iside++)
	{  

	  hodoCanv[npl][iside] = new TCanvas(Form("hodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("Hodo TDC:ADC Time Diff, Plane %s", hod_pl_names[npl].c_str()),  1500, 600);

	  if (!(npl==2&&iside==1) || !(npl==3&&iside==1)){
	    caloCanv[npl][iside] = new TCanvas(Form("calo_TDC:ADC Time Diff. Cal Plane %s%s", cal_pl_names[npl].c_str(), side_names[iside].c_str()), Form("Calo TDC:ADC Time Diff, Plane %s", cal_pl_names[npl].c_str()),  1500, 600);
	    caloCanv[npl][iside]->Divide(5,3);
	  }
	    
	  //Divide Hodo Canvas Accordingly
	  if(npl == 0 || npl == 2)
	    {
	      hodoCanv[npl][iside]->Divide(4,4);
	    }
	    
	  else if (npl==1 || npl==3)
	    {
	      hodoCanv[npl][iside]->Divide(5,2);
	    }
	    
	  //Loop over pmt
	  for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
	    {

	      //Get Mean and Sigma
	      mean = H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hodo_tWinMin[npl][iside][ipmt] = mean - hod_nSig*sig;
	      hodo_tWinMax[npl][iside][ipmt] = mean + hod_nSig*sig;

	            
	      //Set Min/Max Line Limits
	      hod_LineMin[npl][iside][ipmt] = new TLine(hodo_tWinMin[npl][iside][ipmt], 0, hodo_tWinMin[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hod_LineMax[npl][iside][ipmt] = new TLine(hodo_tWinMax[npl][iside][ipmt], 0, hodo_tWinMax[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hod_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      hod_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      hodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      hod_LineMin[npl][iside][ipmt]->Draw();
	      hod_LineMax[npl][iside][ipmt]->Draw();
	    } //end pmt loop

	  //Loop over Calorimeter pmts
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {

	      //Get Mean and Sigma
	      mean = H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hCal_tWinMin[npl][iside][ipmt] = mean - cal_nSig*sig;
	      hCal_tWinMax[npl][iside][ipmt] = mean + cal_nSig*sig;                                                                                                          
	      
	      //Set Min/Max Line Limits
	      cal_LineMin[npl][iside][ipmt] = new TLine(hCal_tWinMin[npl][iside][ipmt], 0, hCal_tWinMin[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      cal_LineMax[npl][iside][ipmt] = new TLine(hCal_tWinMax[npl][iside][ipmt], 0, hCal_tWinMax[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      cal_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      cal_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      caloCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      cal_LineMin[npl][iside][ipmt]->Draw();
	      cal_LineMax[npl][iside][ipmt]->Draw();

	    } //end pmt loop
	    
	    
	  hodoCanv[npl][iside]->SaveAs(Form("Hodo_%s%s.pdf", hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  

	  if ((npl==2&&iside==1) || (npl==3&&iside==1)) continue;
	  caloCanv[npl][iside]->SaveAs(Form("Calo_%s%s.pdf", cal_pl_names[npl].c_str(), side_names[iside].c_str()));
	    

	} //end side loop
      
      
    } //end plane loop
  
  dcCanv->SaveAs("hDC_RawTime.pdf");
  hCer_Canv->SaveAs("hCer_TimeCuts.pdf");
 
  //Write Histograms to ROOT file
  outROOT->Write();
  outROOT->Close();

  
 
  //------------Write Time Window Min/Max Limits to Parameter File---------------
  ofstream outPARAM;
  outPARAM.open(Form("../PARAM/HMS/HODO/hhodo_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hhodo_tWin_%d.param", runNUM));
  outPARAM << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
  outPARAM << "hhodo_PosAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMin[0][0][ipmt] << ", " << setw(15) << hodo_tWinMin[1][0][ipmt] << ", " << setw(15) << hodo_tWinMin[2][0][ipmt] << ", " << setw(15) << hodo_tWinMin[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMin[0][0][ipmt] << ", " << setw(15) << hodo_tWinMin[1][0][ipmt] << ", " << setw(15) << hodo_tWinMin[2][0][ipmt] << ", " << setw(15) << hodo_tWinMin[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_PosAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMax[0][0][ipmt] << ", " << setw(15) << hodo_tWinMax[1][0][ipmt] << ", " << setw(15) << hodo_tWinMax[2][0][ipmt] << ", " << setw(15) << hodo_tWinMax[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMax[0][0][ipmt] << ", " << setw(15) << hodo_tWinMax[1][0][ipmt] << ", " << setw(15) << hodo_tWinMax[2][0][ipmt] << ", " << setw(15) << hodo_tWinMax[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMin[0][1][ipmt] << ", " << setw(15) << hodo_tWinMin[1][1][ipmt] << ", " << setw(15) << hodo_tWinMin[2][1][ipmt] << ", " << setw(15) << hodo_tWinMin[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMin[0][1][ipmt] << ", " << setw(15) << hodo_tWinMin[1][1][ipmt] << ", " << setw(15) << hodo_tWinMin[2][1][ipmt] << ", " << setw(15) << hodo_tWinMin[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
     outPARAM << setprecision(2) << hodo_tWinMax[0][1][ipmt] << ", " << setw(15) << hodo_tWinMax[1][1][ipmt] << ", " << setw(15) << hodo_tWinMax[2][1][ipmt] << ", " << setw(15) << hodo_tWinMax[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMax[0][1][ipmt] << ", " << setw(15) << hodo_tWinMax[1][1][ipmt] << ", " << setw(15) << hodo_tWinMax[2][1][ipmt] << ", " << setw(15) << hodo_tWinMax[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM.close();

  //---------------------WRITE CALORIMETER TIME WINDOW CUTS TO PARAM FILE--------------------
  outPARAM.open(Form("../PARAM/HMS/CAL/hCal_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hCal_tWin_%d.param", runNUM));

  outPARAM << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hcal_pos_AdcTimeWindowMin = ";
  
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
outPARAM << setprecision(2) << hCal_tWinMin[layer][0][0]<<","
	 << hCal_tWinMin[layer][0][1]<<","
	 << hCal_tWinMin[layer][0][2]<<","
	 << hCal_tWinMin[layer][0][3]<<","
	 << hCal_tWinMin[layer][0][4]<<","
	 << hCal_tWinMin[layer][0][5]<<","
	 << hCal_tWinMin[layer][0][6]<<","
	 << hCal_tWinMin[layer][0][7]<<","
	 << hCal_tWinMin[layer][0][8]<<","
	 << hCal_tWinMin[layer][0][9]<<","
	 << hCal_tWinMin[layer][0][10]<<","
	 << hCal_tWinMin[layer][0][11]<<","
	 << hCal_tWinMin[layer][0][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMin[layer][0][0]<<","
	       << hCal_tWinMin[layer][0][1]<<","
	       << hCal_tWinMin[layer][0][2]<<","
	       << hCal_tWinMin[layer][0][3]<<","
	       << hCal_tWinMin[layer][0][4]<<","
	       << hCal_tWinMin[layer][0][5]<<","
	       << hCal_tWinMin[layer][0][6]<<","
	       << hCal_tWinMin[layer][0][7]<<","
	       << hCal_tWinMin[layer][0][8]<<","
	       << hCal_tWinMin[layer][0][9]<<","
	       << hCal_tWinMin[layer][0][10]<<","
	       << hCal_tWinMin[layer][0][11]<<","
	       << hCal_tWinMin[layer][0][12]<< fixed << endl;
      
    }
    
  }

  outPARAM << "" << endl;
  outPARAM << "" << endl;

  outPARAM << "hcal_pos_AdcTimeWindowMax = ";

  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMax[layer][0][0]<<","
		 << hCal_tWinMax[layer][0][1]<<","
		 << hCal_tWinMax[layer][0][2]<<","
		 << hCal_tWinMax[layer][0][3]<<","
		 << hCal_tWinMax[layer][0][4]<<","
		 << hCal_tWinMax[layer][0][5]<<","
		 << hCal_tWinMax[layer][0][6]<<","
		 << hCal_tWinMax[layer][0][7]<<","
		 << hCal_tWinMax[layer][0][8]<<","
		 << hCal_tWinMax[layer][0][9]<<","
		 << hCal_tWinMax[layer][0][10]<<","
		 << hCal_tWinMax[layer][0][11]<<","
		 << hCal_tWinMax[layer][0][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMax[layer][0][0]<<","
	       << hCal_tWinMax[layer][0][1]<<","
	       << hCal_tWinMax[layer][0][2]<<","
	       << hCal_tWinMax[layer][0][3]<<","
	       << hCal_tWinMax[layer][0][4]<<","
	       << hCal_tWinMax[layer][0][5]<<","
	       << hCal_tWinMax[layer][0][6]<<","
	       << hCal_tWinMax[layer][0][7]<<","
	       << hCal_tWinMax[layer][0][8]<<","
	       << hCal_tWinMax[layer][0][9]<<","
	       << hCal_tWinMax[layer][0][10]<<","
	       << hCal_tWinMax[layer][0][11]<<","
	       << hCal_tWinMax[layer][0][12]<< fixed << endl;
      
    }
    
  }
   
  outPARAM << "hcal_neg_AdcTimeWindowMin = ";
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMin[layer][1][0]<<","
		 << hCal_tWinMin[layer][1][1]<<","
		 << hCal_tWinMin[layer][1][2]<<","
		 << hCal_tWinMin[layer][1][3]<<","
		 << hCal_tWinMin[layer][1][4]<<","
		 << hCal_tWinMin[layer][1][5]<<","
		 << hCal_tWinMin[layer][1][6]<<","
		 << hCal_tWinMin[layer][1][7]<<","
		 << hCal_tWinMin[layer][1][8]<<","
		 << hCal_tWinMin[layer][1][9]<<","
		 << hCal_tWinMin[layer][1][10]<<","
		 << hCal_tWinMin[layer][1][11]<<","
		 << hCal_tWinMin[layer][1][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMin[layer][1][0]<<","
	       << hCal_tWinMin[layer][1][1]<<","
	       << hCal_tWinMin[layer][1][2]<<","
	       << hCal_tWinMin[layer][1][3]<<","
	       << hCal_tWinMin[layer][1][4]<<","
	       << hCal_tWinMin[layer][1][5]<<","
	       << hCal_tWinMin[layer][1][6]<<","
	       << hCal_tWinMin[layer][1][7]<<","
	       << hCal_tWinMin[layer][1][8]<<","
	       << hCal_tWinMin[layer][1][9]<<","
	       << hCal_tWinMin[layer][1][10]<<","
	       << hCal_tWinMin[layer][1][11]<<","
	       << hCal_tWinMin[layer][1][12]<< fixed << endl;
      
    }
    
  }

  outPARAM << "" << endl;
  outPARAM << "" << endl;

  outPARAM << "hcal_neg_AdcTimeWindowMax = ";
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMax[layer][1][0]<<","
		 << hCal_tWinMax[layer][1][1]<<","
		 << hCal_tWinMax[layer][1][2]<<","
		 << hCal_tWinMax[layer][1][3]<<","
		 << hCal_tWinMax[layer][1][4]<<","
		 << hCal_tWinMax[layer][1][5]<<","
		 << hCal_tWinMax[layer][1][6]<<","
		 << hCal_tWinMax[layer][1][7]<<","
		 << hCal_tWinMax[layer][1][8]<<","
		 << hCal_tWinMax[layer][1][9]<<","
		 << hCal_tWinMax[layer][1][10]<<","
		 << hCal_tWinMax[layer][1][11]<<","
		 << hCal_tWinMax[layer][1][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMax[layer][1][0]<<","
	       << hCal_tWinMax[layer][1][1]<<","
	       << hCal_tWinMax[layer][1][2]<<","
	       << hCal_tWinMax[layer][1][3]<<","
	       << hCal_tWinMax[layer][1][4]<<","
	       << hCal_tWinMax[layer][1][5]<<","
	       << hCal_tWinMax[layer][1][6]<<","
	       << hCal_tWinMax[layer][1][7]<<","
	       << hCal_tWinMax[layer][1][8]<<","
	       << hCal_tWinMax[layer][1][9]<<","
	       << hCal_tWinMax[layer][1][10]<<","
	       << hCal_tWinMax[layer][1][11]<<","
	       << hCal_tWinMax[layer][1][12]<< fixed << endl;
      
    }
    
  }  

  outPARAM.close();

  //------------------Write CHerenkov Time Window Cuts to Param File------------------------
 
  outPARAM.open(Form("../PARAM/HMS/CER/hCer_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hCer_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS Cherenkov Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hcer_adcTimeWindowMin =" << hCer_tWinMin[0] << "," << hCer_tWinMin[1] << endl;
  outPARAM << "hcer_adcTimeWindowMax =" << hCer_tWinMax[0] << "," << hCer_tWinMax[1] << endl;
  outPARAM.close();


  //--------------Write DC Time Window Cuts to Parameter File--------------------------------
  
  outPARAM.open(Form("../PARAM/HMS/DC/hDC_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hDC_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS DC Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hdc_tdc_min_win = " << setprecision(2) << hDC_tWinMin[0] << ", " << hDC_tWinMin[1] << ", " << hDC_tWinMin[2] << ", " << hDC_tWinMin[3] << ", " << hDC_tWinMin[4] << ", " << hDC_tWinMin[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMin[6] << ", " << hDC_tWinMin[7] << ", " << hDC_tWinMin[8] << ", " << hDC_tWinMin[9] << ", " << hDC_tWinMin[10] << ", " << hDC_tWinMin[11] <<endl;

  outPARAM << "hdc_tdc_max_win = " << setprecision(2) << hDC_tWinMax[0] << ", " << hDC_tWinMax[1] << ", " << hDC_tWinMax[2] << ", " << hDC_tWinMax[3] << ", " << hDC_tWinMax[4] << ", " << hDC_tWinMax[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMax[6] << ", " << hDC_tWinMax[7] << ", " << hDC_tWinMax[8] << ", " << hDC_tWinMax[9] << ", " << hDC_tWinMax[10] << ", " << hDC_tWinMax[11] <<endl;

  outPARAM.close();
  */
} //end program
