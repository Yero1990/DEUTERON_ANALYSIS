void checkRatio()
{

  //User input Buffer Level Run Number
  Int_t runBL1, runBL5, runBL10;
  
  //At poisson rate ~ 5kHz
  runBL1 = 2180;    
  runBL5 = 2208;
  runBL10 = 2258;
    
  //ROOTFile Names
  TString fBL1 = Form("../../../ROOTfiles/hms_replay_scalers_%d_-1.root", runBL1);
  TString fBL5 = Form("../../../ROOTfiles/hms_replay_scalers_%d_-1.root", runBL5);
  TString fBL10 = Form("../../../ROOTfiles/hms_replay_scalers_%d_-1.root", runBL10);

  //read the file and get the tree
  TFile *fBL1_data = new TFile(fBL1, "READ");
  TFile *fBL5_data = new TFile(fBL5, "READ");
  TFile *fBL10_data = new TFile(fBL10, "READ");

  //Declare Leaf Variable Names/Values
  TString nhT1_rawtdc = "T.hms.hT1_tdcTimeRaw";
  TString nhT1_tdc = "T.hms.hT1_tdcTime";

  Double_t hT1_rawtdc;
  Double_t hT1_tdc;

  //Declare Histograms
  TH1F *H_BL1 = new TH1F("BL1_hT1", "", 100, 1900, 2400);
  TH1F *H_BL5 = new TH1F("BL5_hT1", "", 100, 1900, 2400);
  TH1F *H_BL10 = new TH1F("BL10_hT1", "", 100, 1900, 2400);

  TH1F *H_BL1_corr = new TH1F("BL1_hT1_refcorr", "", 100, 100, 400);
  TH1F *H_BL5_corr = new TH1F("BL5_hT1_refcorr", "", 100, 100, 400);
  TH1F *H_BL10_corr = new TH1F("BL10_hT1_refcorr", "", 100, 100, 400);

  
  
  fBL1_data->cd();
  TTree *TL1 = (TTree*)fBL1_data->Get("T");
  TL1->SetBranchAddress(nhT1_rawtdc, &hT1_rawtdc);     
  TL1->SetBranchAddress(nhT1_tdc, &hT1_tdc);     
  for(Long64_t i=0; i<6000; i++)
    {
      TL1->GetEntry(i);  
      H_BL1->Fill(hT1_rawtdc);
      H_BL1_corr->Fill(hT1_tdc);			
    }
  
  //---------------------------------------------------

  fBL5_data->cd();
  TTree *TL5 = (TTree*)fBL5_data->Get("T");
  TL5->SetBranchAddress(nhT1_rawtdc, &hT1_rawtdc); 
  TL5->SetBranchAddress(nhT1_tdc, &hT1_tdc); 
  for(Long64_t i=0; i<6000; i++)
    {
      TL5->GetEntry(i);  
      H_BL5->Fill(hT1_rawtdc);
      H_BL5_corr->Fill(hT1_tdc);
    }

  //--------------------------------------------------
  fBL10_data->cd();
  TTree *TL10 = (TTree*)fBL10_data->Get("T");
  TL10->SetBranchAddress(nhT1_rawtdc, &hT1_rawtdc); 
  TL10->SetBranchAddress(nhT1_tdc, &hT1_tdc); 
  for(Long64_t i=0; i<6000; i++)
    {
      TL10->GetEntry(i);  
      H_BL10->Fill(hT1_rawtdc);
      H_BL10_corr->Fill(hT1_tdc);

    }

  //-------------------------------------------------

  TH1F *L1L5_ratio = new TH1F("h1", "L1:L5 Ratio", 100, 1900, 2400);
  TH1F *L1L10_ratio = new TH1F("h2", "L1:L10 Ratio", 100, 1900, 2400);
  TH1F *L5L10_ratio = new TH1F("h3", "L5:L10 Ratio", 100, 1900, 2400);

  TH1F *L1L5_ratio_ref = new TH1F("h1_refcorr", "L1:L5 Ratio", 100, 100, 400);
  TH1F *L1L10_ratio_ref = new TH1F("h2_refcorr", "L1:L10 Ratio", 100, 100, 400);
  TH1F *L5L10_ratio_ref = new TH1F("h3_refcorr", "L5:L10 Ratio", 100, 100, 400);


  L1L5_ratio->Divide(H_BL1,H_BL5);
  L1L10_ratio->Divide(H_BL1,H_BL10);
  L5L10_ratio->Divide(H_BL5,H_BL10);


  TCanvas *c1 = new TCanvas("c1", "", 1000, 1000);
  c1->Divide(3,1);
  
  c1->cd(1);
  L1L5_ratio->Draw();
  c1->cd(2);
  L1L10_ratio->Draw();
  c1->cd(3);
  L5L10_ratio->Draw();

}
