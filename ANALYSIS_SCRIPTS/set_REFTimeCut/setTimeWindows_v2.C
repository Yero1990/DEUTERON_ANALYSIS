//#include "example.h"
//Define and Set REF. TIME CUTS 
//0.0625 ns / Ch., in case it is used
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TLine.h"
#include "TCanvas.h"

//This code currrently works ony for ROOT 6.08
void setTimeWindows_v2()
{


    //=========================
  //====OPEN ROOT FILE=======
  //=========================

  Int_t runNUM = 3288;
  string daq = "coin";    //or hms, shms  (single arm mode)
  string rtype = "coin";  //or "hms", "shms"  (singles in coin mode)
  
  TString filename = "../../../ROOTfiles/coin_replay_timeWin_check_3288_50000.root";

  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");
  
  //Create output root file where histograms will be stored
  //TFile *outROOT = new TFile(Form("%s_histos_run%d.root", rtype.c_str(), runNUM), "recreate");
         


  //(See /PARAM/HMS/GEN/h_reftime_cut.param, units in Channel)
  static const Double_t hhod_trefcut = 2100.;      //hodo tdc ref cut
  static const Double_t hdc_trefcut = 15600.;      //dc tdc ref cut
  static const Double_t hadc_trefcut = 3150.;      //hodo/cer/cal adc ref cut
  
  //(See /PARAM/SHMS/GEN/p_reftime_cut.param, units in Channel)
  static const Double_t phod_trefcut = 2800.;
  static const Double_t pdc_trefcut = 13700.;
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
  Double_t pPrSh_nSig;

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
  
  TLine *pPrsh_LineMin[2][14];
  TLine *pPrsh_LineMax[2][14];
  
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
  Double_t phgcer_TdcAdcTimeDiff[4];
  Double_t phgcer_AdcMult[4];
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

  hdc_tref_nbins = 200,           pdc_tref_nbins = 200;
  hdc_tref_xmin = 14600,          pdc_tref_xmin = 13000;
  hdc_tref_xmax = 16000,          pdc_tref_xmax = 15500;
 
  hadc_tref_nbins = 150,          padc_tref_nbins = 100;
  hadc_tref_xmin = 3000,          padc_tref_xmin = 2000;
  hadc_tref_xmax = 3300,          padc_tref_xmax = 4500;


  
  //ADC:TDC Time Diff Histos
  //HMS               SHMS
  hhod_nbins = 50,    phod_nbins = 100;    
  hhod_xmin = -70,    phod_xmin = -70;    
  hhod_xmax = -40,    phod_xmax = 70;                                              
  
  hdc_nbins = 100,    pdc_nbins = 500;                                                      
  hdc_xmin = -16000,  pdc_xmin = -20000;                                                                
  hdc_xmax = -10000,  pdc_xmax = -5000;  

  hcer_nbins = 100,   phgcer_nbins = 200,    pngcer_nbins = 200;                                                                                                                                     
  hcer_xmin = 0,     phgcer_xmin = -100,    pngcer_xmin = 50;                                                                                                                                   
  hcer_xmax = 150,    phgcer_xmax = 100,     pngcer_xmax = 150;                                                                                                                 
                                          
  hcal_nbins = 200,   pPrsh_nbins = 200,      pcal_nbins = 200;                                                                                                                                            
  hcal_xmin = -140,   pPrsh_xmin = -200,      pcal_xmin = -200;                                                                                                                    
  hcal_xmax = -60,    pPrsh_xmax = 200,       pcal_xmax = 200; 


  //Set ADC:TDC Time Window Cut Range
  //Based on multiples of sigma from the histos
  hhod_nSig = 6.0;
  hdc_nSig = 4.5; 
  hcer_nSig = 3.5;  
  hcal_nSig = 4.0;
  
  phod_nSig = 3.0;
  pdc_nSig = 3.0; 
  phgcer_nSig = 3.5;
  pngcer_nSig = 3.5;
  pcal_nSig = 4.0;
  pPrSh_nSig = 3.0;

  //gROOT->SetBatch(kTRUE);




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

      //SHMS Heavy Gas Cherenkov
      n_phgcer_TdcAdcTimeDiff =  "P.hgcer.goodAdcTdcDiffTime";
      n_phgcer_AdcMult = "P.hgcer.goodAdcMult";
      
      T->SetBranchAddress(n_phgcer_AdcMult, &phgcer_AdcMult[ipmt]);
      T->SetBranchAddress(n_phgcer_TdcAdcTimeDiff, &phgcer_TdcAdcTimeDiff[ipmt]);
      
      P_hgcer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pHGCER%d_timeDiff", ipmt+1), Form("SHMS Heavy Gas Cer%d AdcTdcTimeDiff", ipmt+1), phgcer_nbins, phgcer_xmin, phgcer_xmax);
      
      //SHMS Noble Gas Cherenkov
      n_pngcer_TdcAdcTimeDiff =  "P.ngcer.goodAdcTdcDiffTime";
      n_pngcer_AdcMult = "P.ngcer.goodAdcMult";
      
      T->SetBranchAddress(n_pngcer_AdcMult, &pngcer_AdcMult[ipmt]);
      T->SetBranchAddress(n_pngcer_TdcAdcTimeDiff, &pngcer_TdcAdcTimeDiff[ipmt]);
      
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
      
      P_dc_rawTDC[npl] = new TH1F(Form("pDC%s_rawTDC", pdc_pl_names[npl].c_str()), Form("SHMS DC Plane %s Raw TDC", pdc_pl_names[npl].c_str()), pdc_nbins, pdc_xmin, pdc_xmax);
      
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
	      
	      T->SetBranchAddress(n_hhod_TdcAdcTimeDiff, hhod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_hhod_AdcMult, hhod_AdcMult[npl][iside]);

	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hHod%s%d%s_timeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Hodo %s%d%s AdcTdcTimeDiff", hod_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hhod_nbins,hhod_xmin,hhod_xmax);

	    }
	  



	  //Loop over SHMS hodo PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {
	      base = "P.hod." + hod_pl_names[npl];
	      
	      n_phod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      n_phod_AdcMult = base + "." + side_names[iside] + "AdcMult";
	  	
	      T->SetBranchAddress(n_phod_TdcAdcTimeDiff, phod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_phod_AdcMult, phod_AdcMult[npl][iside]);
	    	     
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
		  
		  T->SetBranchAddress(n_pPrSh_TdcAdcTimeDiff, pPrSh_TdcAdcTimeDiff[npl][iside]);
		  T->SetBranchAddress(n_pPrSh_AdcMult, pPrSh_AdcMult[npl][iside]);
	      
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
		      T->SetBranchAddress(n_pcal_TdcAdcTimeDiff, pcal_TdcAdcTimeDiff[iside]);
		      
		      P_cal_TdcAdcTimeDiff[ipmt] = new TH1F(Form("pSh_pmt%d", ipmt+1), Form("SHMS Pre-Shower PMT_%d", ipmt+1), pcal_nbins, pcal_xmin, pcal_xmax);
		    }
		} //end side0 requirement for fly's eye

	    } //End plane 0 requirement for Pre-SHower


	} //End Loop over sides

    } //End Loop over planes
 

  Double_t hcer_TdcAdcTimeDiff[2];
  Double_t hcer_AdcMult[2];
  
  for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
    {
      //HMS  Cherenkov
      n_hcer_TdcAdcTimeDiff =  "H.cer.goodAdcTdcDiffTime";
      n_hcer_AdcMult = "H.cer.goodAdcMult";
      
      T->SetBranchAddress(n_hcer_AdcMult, &hcer_AdcMult);
      T->SetBranchAddress(n_hcer_TdcAdcTimeDiff, &hcer_TdcAdcTimeDiff);
      
      H_cer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("hCER%d_timeDiff", ipmt+1), Form("HMS Cer %d AdcTdcTimeDiff", ipmt+1), hcer_nbins, hcer_xmin, hcer_xmax);
    }
  


  //HMS Calorimeter
  Double_t hcal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
  Double_t hcal_AdcMult[cal_PLANES][SIDES][13];
  
  for(int npl=0; npl<4; npl++ )
    {
      for(int iside=0; iside<2; iside++)
	{
	  	  //Loop over HMS calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	      base =  "H.cal." + cal_pl_names[npl];
	      
	      n_hcal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      n_hcal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	      T->SetBranchAddress(n_hcal_TdcAdcTimeDiff, hcal_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_hcal_AdcMult, hcal_AdcMult[npl][iside]);
	  
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hcal_nbins,hcal_xmin,hcal_xmax) ;

	    }
	}
    }
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
	}

      for(int iref=0; iref<4; iref++)
	{
	  //HMS DC Ref. Times
	  H_DC_Tref[iref]->Fill(hDC_ref[iref]);
	}

      //HMS Ref
      H_hodo_Tref->Fill(hT1_ref);
      H_FADC_Tref->Fill(hFADC_ref);

      //SHMS Ref
      P_hodo_Tref->Fill(pT2_ref);
      P_FADC_Tref->Fill(pFADC_ref);
      	    

      //------------------------------------------------------------------------------
 
      //Loop over Cherenkov PMTs
      
      for (Int_t ipmt = 0; ipmt < 2; ipmt++)
	{ 
	  //----HMS Cherenkov----
	      
	  //Define Multiplicity Cuts
	      
	  //Require ADC Multiplicity == 1  NOT YET DONE . . 
	  if(abs(hcer_TdcAdcTimeDiff[ipmt])<1000){

	    H_cer_TdcAdcTimeDiff[ipmt]->Fill(hcer_TdcAdcTimeDiff[ipmt]);
	  }	  
	}
      
      for (Int_t ipmt = 0; ipmt < 4; ipmt++)
	{                                                                                                                                             
	  
	  //----SHMS Heavy Gas Cherenkov-----
	  
	  //Define Multiplicity Cuts

	  //Require ADC Multiplicity == 1

	  //cout << phgcer_TdcAdcTimeDiff[ipmt] << endl;
	  P_hgcer_TdcAdcTimeDiff[ipmt]->Fill(phgcer_TdcAdcTimeDiff[ipmt]);
	    
	  
	  //----SHMS Noble Gas Cherenkov-----
	  
	  //Define Multiplicity Cuts

	  //Require ADC Multiplicity == 1

	  P_ngcer_TdcAdcTimeDiff[ipmt]->Fill(pngcer_TdcAdcTimeDiff[ipmt]);
	      
       
	} //End Cherenkov PMT loop
	  

      //-----------------------------------------------------------------------------
      
      //Loop over Drift Chamber Planes
      for (Int_t npl = 0; npl<dc_PLANES; npl++)
	{


	  //-------HMS Drift Chambers----------
	  
	  //Define Cuts Here
	  //cout << hndata_rawTDC[npl] << endl;
	  //cout << hdc_rawTDC[npl][1] << endl;

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

		  if(abs(hhod_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
		    {
		      H_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hhod_TdcAdcTimeDiff[ip][iside][ipmt]);

		    }

		}

	      //Loop over Calorimeter PMTs
	      for (Int_t ipmt = 0; ipmt < 13; ipmt++)
		{

		  //------------HMS Calorimeter----------------

		  //DEfine Multiplicity CUts here
		   
		  if(abs(hcal_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
		    {
	        
		      //cout << "TimeDiff: " << hcal_TdcAdcTimeDiff[ip][iside][ipmt] << endl;
		      H_cal_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(hcal_TdcAdcTimeDiff[ip][iside][ipmt]);
		      

		    }
		}
	      
	      
	      //Loop over SHMS Hodoscopes PMTs
	      for (Int_t ipmt = 0; ipmt < pmaxPMT[ip]; ipmt++)
		{
		  
		  //------------SHMS Hodoscopes----------------
		  if(abs(phod_TdcAdcTimeDiff[ip][iside][ipmt])<1000.)
		    {
        
		      P_hod_TdcAdcTimeDiff[ip][iside][ipmt]->Fill(phod_TdcAdcTimeDiff[ip][iside][ipmt]);
		    }
		}

	      
	      
	      //------------SHMS PreSHower-------------------
	      	  
	      //Loop over SHMS PrSh PMTs
	      for (Int_t ipmt=0; ipmt < 14; ipmt++)
		{
		   
		  if(ip==0&& abs(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt])<1000.){
		    P_prSh_TdcAdcTimeDiff[iside][ipmt]->Fill(pPrSh_TdcAdcTimeDiff[ip][iside][ipmt]);
		  }
       

		} //End loop over SHMS PrSH PMTs

	      
	      //----------SHMS FLy's Eye Calorimeter-------------
	      for (Int_t ipmt = 0; ipmt < 224; ipmt++)
		{
		  if(ip==0&&iside==0&&abs(pcal_TdcAdcTimeDiff[iside][ipmt])<1000.)
		    {
		      P_cal_TdcAdcTimeDiff[ipmt]->Fill(pcal_TdcAdcTimeDiff[iside][ipmt]);
		    }
		}
	      


	    } // END LOOP OVER SIDES

	} //END LOOP OVER PLANES
      

    } //END EVENT LOOP
  
  
  
  //DRAW HISTOGRAMS TO CANVAS

  /*

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
  */
   //HODOSCOPES / CALORIMETERS
  //Loop over planes
  for (Int_t npl = 0; npl < hod_PLANES; npl++ )
    {      

      //Loop over plane side
      for (Int_t iside = 0; iside < SIDES; iside++)
	{  
	  
	  //Define HMS Hodo Canv
	  //hhodoCanv[npl][iside] = new TCanvas(Form("hhodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("HMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);
	  //Define SHMS Hodo Canv
	  //phodoCanv[npl][iside] = new TCanvas(Form("phodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("SHMS Hodo TDC-ADC Time Diff, Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()),  1500, 600);

	  /*
	  //Define HMS Calorimeter Canvas for all planes
	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside] = new TCanvas(Form("hcalo_TDC:ADC Time Diff. Cal Plane %s%s", cal_pl_names[npl].c_str(), cal_side_names[iside].c_str()), Form("Calo TDC:ADC Time Diff, Plane %s %s", cal_pl_names[npl].c_str(), cal_side_names[iside].c_str()),  1500, 600);
	    hcaloCanv[npl][iside]->Divide(5,3);	   
	  }
	  */
	  
	  
	  //Define SHMS PreShower and Calorimeter Canvas
	  if(npl==0)
	    {
	      pPrshCanv[iside] =  new TCanvas(Form("pPrSh_TDC:ADC Time Diff %s", cal_side_names[iside].c_str()), Form("SHMS PreShower TDC:ADC Time Diff %s",  cal_side_names[iside].c_str()),  1500, 600);
	    
	      //Define Fly's Eye Calorimeter
	      if(iside==0)
		{
		  pcalCanv =  new TCanvas("pCal_TDC:ADC Time Diff", "SHMS Calo TDC:ADC Time Diff",  2500, 2500);
		}
	    }

	  /*
	  //Divide HMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 2)
	    {
	      hhodoCanv[npl][iside]->Divide(4,4);
	    }
	    
	  else if (npl==1 || npl==3)
	    {
	      hhodoCanv[npl][iside]->Divide(5,2);
	    }
	  
	  //Divide SHMS Hodo Canvas Accordingly
	  if(npl == 0 || npl == 1 || npl==2)
	    {
	      phodoCanv[npl][iside]->Divide(7,2);
	    }
	    
	  else if (npl==3)
	    {
	      phodoCanv[npl][iside]->Divide(7,3);
	    }
	  */
	  
	  //Divide SHMS PreSh / Calo Canvas Accordingly
	  if(npl==0)
	    {
	      pPrshCanv[iside]->Divide(7,2);

	      if(iside==0)
		{
		  pcalCanv->Divide(15,15);
		}
	    }
	  

	  /*
	  //Loop over HMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < hmaxPMT[npl]; ipmt++)
	    {

	      //Get Mean and Sigma
	      mean = H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hhodo_tWinMin[npl][iside][ipmt] = mean - hhod_nSig*sig;
	      hhodo_tWinMax[npl][iside][ipmt] = mean + hhod_nSig*sig;

	            
	      //Set Min/Max Line Limits
	      hhod_LineMin[npl][iside][ipmt] = new TLine(hhodo_tWinMin[npl][iside][ipmt], 0, hhodo_tWinMin[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hhod_LineMax[npl][iside][ipmt] = new TLine(hhodo_tWinMax[npl][iside][ipmt], 0, hhodo_tWinMax[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hhod_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      hhod_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      hhodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      hhod_LineMin[npl][iside][ipmt]->Draw();
	      hhod_LineMax[npl][iside][ipmt]->Draw();
	    } //end hms hodo pmt loop
	  
	   //Loop over SHMS HODO PMTs
	  for (Int_t ipmt = 0; ipmt < pmaxPMT[npl]; ipmt++)
	    {
	      //Get Mean and Sigma
	      mean = P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      phodo_tWinMin[npl][iside][ipmt] = mean - phod_nSig*sig;
	      phodo_tWinMax[npl][iside][ipmt] = mean + phod_nSig*sig;

	            
	      //Set Min/Max Line Limits
	      phod_LineMin[npl][iside][ipmt] = new TLine(phodo_tWinMin[npl][iside][ipmt], 0, phodo_tWinMin[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      phod_LineMax[npl][iside][ipmt] = new TLine(phodo_tWinMax[npl][iside][ipmt], 0, phodo_tWinMax[npl][iside][ipmt], P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      phod_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      phod_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      phodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      phod_LineMin[npl][iside][ipmt]->Draw();
	      phod_LineMax[npl][iside][ipmt]->Draw();
	    } //end shms hodo pmt loop

	  
	  //Loop over HMS Calorimeter pmts
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	     
	      //Get Mean and Sigma
	      mean = H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hCal_tWinMin[npl][iside][ipmt] = mean - hcal_nSig*sig;
	      hCal_tWinMax[npl][iside][ipmt] = mean + hcal_nSig*sig;                                                                                                          
	      
	      //Set Min/Max Line Limits
	      hcal_LineMin[npl][iside][ipmt] = new TLine(hCal_tWinMin[npl][iside][ipmt], 0, hCal_tWinMin[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hcal_LineMax[npl][iside][ipmt] = new TLine(hCal_tWinMax[npl][iside][ipmt], 0, hCal_tWinMax[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hcal_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      hcal_LineMax[npl][iside][ipmt]->SetLineColor(kRed);
	      
	      if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	      hcaloCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      hcal_LineMin[npl][iside][ipmt]->Draw();
	      hcal_LineMax[npl][iside][ipmt]->Draw();
	      }
	    } //end pmt loop
	  */
	    //Loop over SHMS PreSh PMTs
	  for(int ipmt=0; ipmt<14; ipmt++)
	    {
	      if (npl!=0) continue;
	      //Get Mean and Sigma
	      mean = P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMean();
	      sig =  P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetStdDev();
	      
	      //Set Time Window Cuts
	      pPrsh_tWinMin[iside][ipmt] = mean - pPrSh_nSig*sig;
	      pPrsh_tWinMax[iside][ipmt] = mean + pPrSh_nSig*sig;                                                                                                          
	      
	      //Set Min/Max Line Limits
	      pPrsh_LineMin[iside][ipmt] = new TLine(pPrsh_tWinMin[iside][ipmt], 0, pPrsh_tWinMin[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      pPrsh_LineMax[iside][ipmt] = new TLine(pPrsh_tWinMax[iside][ipmt], 0, pPrsh_tWinMax[iside][ipmt], P_prSh_TdcAdcTimeDiff[iside][ipmt]->GetMaximum());
	      
	      pPrsh_LineMin[iside][ipmt]->SetLineColor(kRed);
	      pPrsh_LineMax[iside][ipmt]->SetLineColor(kRed);
	      
	      pPrshCanv[iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      P_prSh_TdcAdcTimeDiff[iside][ipmt]->Draw();
	      pPrsh_LineMin[iside][ipmt]->Draw();
	      pPrsh_LineMax[iside][ipmt]->Draw();
	    
	    } //end pmt loop
	  	  
	  if(iside==0)
	    {
	      //Loop over SHMS FLy's Eye PMTs
	      for(int ipmt=0; ipmt<224; ipmt++)
		{
		  //Get Mean and Sigma
		  mean = P_cal_TdcAdcTimeDiff[ipmt]->GetMean();
		  sig =  P_cal_TdcAdcTimeDiff[ipmt]->GetStdDev();
		  
		  //Set Time Window Cuts
		  pCal_tWinMin[ipmt] = mean - pcal_nSig*sig;
		  pCal_tWinMax[ipmt] = mean + pcal_nSig*sig;                                                                                                          
		  
		  //Set Min/Max Line Limits
		  pcal_LineMin[ipmt] = new TLine(pCal_tWinMin[ipmt], 0, pCal_tWinMin[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  pcal_LineMax[ipmt] = new TLine(pCal_tWinMax[ipmt], 0, pCal_tWinMax[ipmt], P_cal_TdcAdcTimeDiff[ipmt]->GetMaximum());
		  
		  pcal_LineMin[ipmt]->SetLineColor(kRed);
		  pcal_LineMax[ipmt]->SetLineColor(kRed);
		  
		  pcalCanv->cd(ipmt+1);
		  gPad->SetLogy();
		  P_cal_TdcAdcTimeDiff[ipmt]->Draw();
		  pcal_LineMin[ipmt]->Draw();
		  pcal_LineMax[ipmt]->Draw();
		  
		} // End FLys Eye PMT loop
	    }


	  /*
	  //hhodoCanv[npl][iside]->SaveAs(Form("Hodo_%s%s.pdf", hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  
	  
	  if (!(npl==2&&iside==1) && !(npl==3&&iside==1)){
	    hcaloCanv[npl][iside]->SaveAs(Form("Calo_%s%s.pdf", cal_pl_names[npl].c_str(), side_names[iside].c_str()));
	  }
	  */
	 
    } //end side loop
      
      
    } //end plane loop
	  
	 

  /*

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

