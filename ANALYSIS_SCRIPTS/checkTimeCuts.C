void checkTimeCuts()
{

  gROOT->SetBatch(kTRUE);
  Int_t runNUM = 1267;
  
  TString filename = "../../ROOTfiles/hms_replay_matrixopt_1267_100000.root";
  //hms_replay_matrixopt_1267_100000.root";
  
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");
  
  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("hCal_histos_tCUT%d.root", runNUM), "recreate");

  //--------------------------------------------
  //Define Hodo TIme Window Canvases
  TCanvas *hod1xp = new TCanvas("hod1xp", "hod1xPos");
  TCanvas *hod1xn = new TCanvas("hod1xn", "hod1xNeg");
  TCanvas *hod2xp = new TCanvas("hod2xp", "hod2xPos");
  TCanvas *hod2xn = new TCanvas("hod2xn", "hod2xNeg");
  hod1xp->Divide(4,4);
  hod1xn->Divide(4,4);
  hod2xp->Divide(4,4);
  hod2xn->Divide(4,4);

  TCanvas *hod1yp = new TCanvas("hod1yp", "hod1yPos");
  TCanvas *hod1yn = new TCanvas("hod1yn", "hod1yNeg");
  TCanvas *hod2yp = new TCanvas("hod2yp", "hod2yPos");
  TCanvas *hod2yn = new TCanvas("hod2yn", "hod2yNeg");
  hod1yp->Divide(5,2);
  hod1yn->Divide(5,2);
  hod2yp->Divide(5,2);
  hod2yn->Divide(5,2);

  //Define Calorimeter Time Window Canvases
  TCanvas *hCal1p = new TCanvas("hCal1p", "hCal1Pos", 1000, 500);
  TCanvas *hCal1n = new TCanvas("hCal1n", "hCal1Neg", 1000, 500);
 
  TCanvas *hCal2p = new TCanvas("hCal2p", "hCal2Pos", 1000, 500);
  TCanvas *hCal2n = new TCanvas("hCal2n", "hCal2Neg", 1000, 500);

  TCanvas *hCal3p = new TCanvas("hCal3p", "hCal3Pos", 1000, 500);
  TCanvas *hCal4p = new TCanvas("hCal4p", "hCal4Pos", 1000, 500);

  hCal1p->Divide(5,3);
  hCal1n->Divide(5,3);
  
  hCal2p->Divide(5,3);
  hCal2n->Divide(5,3);
  
  hCal3p->Divide(5,3);
  hCal4p->Divide(5,3);

  //--------------------------------------------

  static const Int_t PLANES = 4;
  static const Int_t SIDES = 2;
  string pl_names[4] = {"1x", "1y", "2x", "2y"};
  Int_t maxPMT[4] = {16, 10, 16, 10};

  //Define Histograms for REF Time
  TH1F *hodo_Tref = new TH1F("hodoTref", "Hodoscope hT1 TDC Raw Time", 300, 1200, 1800);
  TH1F *DC_Tref1 = new TH1F("DCTref1", "DC REF TDC Raw Times", 300, 14600, 15200);
  TH1F *DC_Tref2 = new TH1F("DCTref2", "DC REF TDC Raw Times", 300, 14600, 15200);
  TH1F *DC_Tref3 = new TH1F("DCTref3", "DC REF TDC Raw Times", 300, 14600, 15200);
  TH1F *DC_Tref4 = new TH1F("DCTref4", "DC REF TDC Raw Times", 300, 14600, 15200);
  TH1F *hFADC_Tref = new TH1F("hFADC_Tref", "FADC REF adcPulseTimeRaw", 70, 2600, 2740);

  //Define Histograms for Setting Time Window Cuts

  //HODO:
  TH1F *h1x_pos[16];
  TH1F *h1x_neg[16];
  
  TH1F *h1y_pos[10];
  TH1F *h1y_neg[10];
  
  TH1F *h2x_pos[16];
  TH1F *h2x_neg[16];
  
  TH1F *h2y_pos[10];
  TH1F *h2y_neg[10];

  //CALORIMETER
  TH1F *hCal_L1pos[13];    //layer 1 +
  TH1F *hCal_L1neg[13];    //layer 1 -
 
  TH1F *hCal_L2pos[13];    //layer 2 +
  TH1F *hCal_L2neg[13];    //layer 2 -
  
  TH1F *hCal_L3pos[13];    //layer 3 +  
  TH1F *hCal_L4pos[13];    //layer 4 +

  //Define Mean/StdDev
  Double_t h1xpos_Mean, h1xpos_Sig;
  Double_t h1xneg_Mean, h1xneg_Sig;
  Double_t h1ypos_Mean, h1ypos_Sig;
  Double_t h1yneg_Mean, h1yneg_Sig;
  Double_t h2xpos_Mean, h2xpos_Sig;
  Double_t h2xneg_Mean, h2xneg_Sig;
  Double_t h2ypos_Mean, h2ypos_Sig;
  Double_t h2yneg_Mean, h2yneg_Sig;

  Double_t hCal_L1p_Mean, hCal_L1p_Sig;
  Double_t hCal_L1n_Mean, hCal_L1n_Sig;
  
  Double_t hCal_L2p_Mean, hCal_L2p_Sig;
  Double_t hCal_L2n_Mean, hCal_L2n_Sig;

  Double_t hCal_L3p_Mean, hCal_L3p_Sig;
  Double_t hCal_L4p_Mean, hCal_L4p_Sig;

  //Define Arrays to store Min/Max Time Window Cuts
  Double_t tWinMin[4][2][16];
  Double_t tWinMax[4][2][16];

  Double_t hCal_tWinMin[4][2][13] = {0.};
  Double_t hCal_tWinMax[4][2][13] = {0.};

  /*

  //Draw REF Time Histograms
  T->Draw("T.hms.hT1_tdcTimeRaw>>hodoTref");
  T->Draw("T.hms.hDCREF1_tdcTimeRaw>>DCTref1");
  T->Draw("T.hms.hDCREF2_tdcTimeRaw>>DCTref2");
  T->Draw("T.hms.hDCREF3_tdcTimeRaw>>DCTref3");
  T->Draw("T.hms.hDCREF4_tdcTimeRaw>>DCTref4");
  T->Draw("T.hms.hFADC_TREF_ROC1_adcPulseTimeRaw>>hFADC_Tref");
   

  //Loop over HODOSCOPES PMT
  for (int ipmt=0; ipmt<16; ipmt++)
    {

      h1x_pos[ipmt] = new TH1F(Form("h1x_%d+", ipmt+1 ), "", 60, -80, -30);
      h1x_neg[ipmt] = new TH1F(Form("h1x_%d-", ipmt+1 ), "", 60, -80, -30);

      h2x_pos[ipmt] = new TH1F(Form("h2x_%d+", ipmt+1 ), "", 60, -80, -30);
      h2x_neg[ipmt] = new TH1F(Form("h2x_%d-", ipmt+1 ), "", 60, -80, -30);

      hod1xp->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.hod.1x.GoodPosAdcTdcDiffTime[%d]>>h1x_%d+", ipmt, ipmt+1), Form("H.hod.1x.GoodPosAdcMult[%d]>=1", ipmt));
      hod1xp->Modified();
      h1xpos_Mean = h1x_pos[ipmt]->GetMean(),  h1xpos_Sig = h1x_pos[ipmt]->GetStdDev();
      tWinMin[0][0][ipmt] = h1xpos_Mean - 6.*h1xpos_Sig, tWinMax[0][0][ipmt] = h1xpos_Mean + 6.*h1xpos_Sig;
      TLine *l1xp_min = new TLine( tWinMin[0][0][ipmt], 0,  tWinMin[0][0][ipmt], h1x_pos[ipmt]->GetMaximum());
      l1xp_min->SetLineColor(kRed);
      l1xp_min->Draw();
      TLine *l1xp_max = new TLine( tWinMax[0][0][ipmt], 0,  tWinMax[0][0][ipmt], h1x_pos[ipmt]->GetMaximum());
      l1xp_max->SetLineColor(kRed);
      l1xp_max->Draw();
      
      hod1xn->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.hod.1x.GoodNegAdcTdcDiffTime[%d]>>h1x_%d-", ipmt, ipmt+1), Form("H.hod.1x.GoodNegAdcMult[%d]>=1", ipmt));
      hod1xn->Modified();
      h1xneg_Mean = h1x_neg[ipmt]->GetMean(),  h1xneg_Sig = h1x_neg[ipmt]->GetStdDev();
      tWinMin[0][1][ipmt] = h1xneg_Mean - 6.*h1xneg_Sig, tWinMax[0][1][ipmt] = h1xneg_Mean + 6.*h1xneg_Sig;
      TLine *l1xn_min = new TLine( tWinMin[0][1][ipmt], 0,  tWinMin[0][1][ipmt], h1x_neg[ipmt]->GetMaximum());
      l1xn_min->SetLineColor(kRed);
      l1xn_min->Draw();
      TLine *l1xn_max = new TLine( tWinMax[0][1][ipmt], 0,  tWinMax[0][1][ipmt], h1x_neg[ipmt]->GetMaximum());
      l1xn_max->SetLineColor(kRed);
      l1xn_max->Draw();

      hod2xp->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.hod.2x.GoodPosAdcTdcDiffTime[%d]>>h2x_%d+", ipmt, ipmt+1), Form("H.hod.2x.GoodPosAdcMult[%d]>=1", ipmt));
      hod2xp->Modified();
      h2xpos_Mean = h2x_pos[ipmt]->GetMean(),  h2xpos_Sig = h2x_pos[ipmt]->GetStdDev();
      tWinMin[2][0][ipmt] = h2xpos_Mean - 6.*h2xpos_Sig, tWinMax[2][0][ipmt] = h2xpos_Mean + 6.*h2xpos_Sig;
      TLine *l2xp_min = new TLine( tWinMin[2][0][ipmt], 0,  tWinMin[2][0][ipmt], h2x_pos[ipmt]->GetMaximum());
      l2xp_min->SetLineColor(kRed);
      l2xp_min->Draw();
      TLine *l2xp_max = new TLine( tWinMax[2][0][ipmt], 0,  tWinMax[2][0][ipmt], h2x_pos[ipmt]->GetMaximum());
      l2xp_max->SetLineColor(kRed);
      l2xp_max->Draw();

      hod2xn->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.hod.2x.GoodNegAdcTdcDiffTime[%d]>>h2x_%d-", ipmt, ipmt+1), Form("H.hod.2x.GoodNegAdcMult[%d]>=1", ipmt));
      hod2xn->Modified();
      h2xneg_Mean = h2x_neg[ipmt]->GetMean(),  h2xneg_Sig = h2x_neg[ipmt]->GetStdDev();
      tWinMin[2][1][ipmt] = h2xneg_Mean - 6.*h2xneg_Sig, tWinMax[2][1][ipmt] = h2xneg_Mean + 6.*h2xneg_Sig;
      TLine *l2xn_min = new TLine( tWinMin[2][1][ipmt], 0,  tWinMin[2][1][ipmt], h2x_neg[ipmt]->GetMaximum());
      l2xn_min->SetLineColor(kRed);
      l2xn_min->Draw();
      TLine *l2xn_max = new TLine( tWinMax[2][1][ipmt], 0,  tWinMax[2][1][ipmt], h2x_neg[ipmt]->GetMaximum());
      l2xn_max->SetLineColor(kRed);
      l2xn_max->Draw();
      
    
    } // end pmt loop

  //LOOP over Y Planes
    for (int ipmt=0; ipmt<10; ipmt++)
      {
	h1y_pos[ipmt] = new TH1F(Form("h1y_%d+", ipmt+1 ), "", 60, -80, -30);
	h1y_neg[ipmt] = new TH1F(Form("h1y_%d-", ipmt+1 ), "", 60, -80, -30);
      
     	h2y_pos[ipmt] = new TH1F(Form("h2y_%d+", ipmt+1 ), "", 60, -80, -30);
	h2y_neg[ipmt] = new TH1F(Form("h2y_%d-", ipmt+1 ), "", 60, -80, -30);

	hod1yp->cd(ipmt+1);
	gPad->SetLogy();
	T->Draw(Form("H.hod.1y.GoodPosAdcTdcDiffTime[%d]>>h1y_%d+", ipmt, ipmt+1), Form("H.hod.1y.GoodPosAdcMult[%d]>=1", ipmt));
	hod1yp->Modified();
	h1ypos_Mean = h1y_pos[ipmt]->GetMean(),  h1ypos_Sig = h1y_pos[ipmt]->GetStdDev();
	tWinMin[1][0][ipmt] = h1ypos_Mean - 6.*h1ypos_Sig, tWinMax[1][0][ipmt] = h1ypos_Mean + 6.*h1ypos_Sig;
	TLine *l1yp_min = new TLine( tWinMin[1][0][ipmt], 0,  tWinMin[1][0][ipmt], h1y_pos[ipmt]->GetMaximum());
	l1yp_min->SetLineColor(kRed);
	l1yp_min->Draw();
	TLine *l1yp_max = new TLine( tWinMax[1][0][ipmt], 0,  tWinMax[1][0][ipmt], h1y_pos[ipmt]->GetMaximum());
	l1yp_max->SetLineColor(kRed);
	l1yp_max->Draw();
		
	hod1yn->cd(ipmt+1);
	gPad->SetLogy();
	T->Draw(Form("H.hod.1y.GoodNegAdcTdcDiffTime[%d]>>h1y_%d-", ipmt, ipmt+1), Form("H.hod.1y.GoodNegAdcMult[%d]>=1", ipmt));
	hod1yn->Modified();
	h1yneg_Mean = h1y_neg[ipmt]->GetMean(),  h1yneg_Sig = h1y_neg[ipmt]->GetStdDev();
	tWinMin[1][1][ipmt] = h1yneg_Mean - 6.*h1yneg_Sig, tWinMax[1][1][ipmt] = h1yneg_Mean + 6.*h1yneg_Sig;
	TLine *l1yn_min = new TLine( tWinMin[1][1][ipmt], 0,  tWinMin[1][1][ipmt], h1y_neg[ipmt]->GetMaximum());
	l1yn_min->SetLineColor(kRed);
	l1yn_min->Draw();
	TLine *l1yn_max = new TLine( tWinMax[1][1][ipmt], 0,  tWinMax[1][1][ipmt], h1y_neg[ipmt]->GetMaximum());
	l1yn_max->SetLineColor(kRed);
	l1yn_max->Draw();

	hod2yp->cd(ipmt+1);
	gPad->SetLogy();
	T->Draw(Form("H.hod.2y.GoodPosAdcTdcDiffTime[%d]>>h2y_%d+", ipmt, ipmt+1), Form("H.hod.2y.GoodPosAdcMult[%d]>=1", ipmt));
	hod2yp->Modified();
	h2ypos_Mean = h2y_pos[ipmt]->GetMean(),  h2ypos_Sig = h2y_pos[ipmt]->GetStdDev();
	tWinMin[3][0][ipmt] = h2ypos_Mean - 6.*h2ypos_Sig, tWinMax[3][0][ipmt] = h2ypos_Mean + 6.*h2ypos_Sig;
	TLine *l2yp_min = new TLine( tWinMin[3][0][ipmt], 0,  tWinMin[3][0][ipmt], h2y_pos[ipmt]->GetMaximum());
	l2yp_min->SetLineColor(kRed);
	l2yp_min->Draw();
	TLine *l2yp_max = new TLine( tWinMax[3][0][ipmt], 0,  tWinMax[3][0][ipmt], h2y_pos[ipmt]->GetMaximum());
	l2yp_max->SetLineColor(kRed);
	l2yp_max->Draw();
	
	hod2yn->cd(ipmt+1);
	gPad->SetLogy();
	T->Draw(Form("H.hod.2y.GoodNegAdcTdcDiffTime[%d]>>h2y_%d-", ipmt, ipmt+1), Form("H.hod.2y.GoodNegAdcMult[%d]>=1", ipmt));
	hod2yn->Modified();
	h2yneg_Mean = h2y_neg[ipmt]->GetMean(),  h2yneg_Sig = h2y_neg[ipmt]->GetStdDev();
	tWinMin[3][1][ipmt] = h2yneg_Mean - 6.*h2yneg_Sig, tWinMax[3][1][ipmt] = h2yneg_Mean + 6.*h2yneg_Sig;
	TLine *l2yn_min = new TLine( tWinMin[3][1][ipmt], 0,  tWinMin[3][1][ipmt], h2y_neg[ipmt]->GetMaximum());
	l2yn_min->SetLineColor(kRed);
	l2yn_min->Draw();
	TLine *l2yn_max = new TLine( tWinMax[3][1][ipmt], 0,  tWinMax[3][1][ipmt], h2y_neg[ipmt]->GetMaximum());
	l2yn_max->SetLineColor(kRed);
	l2yn_max->Draw();
	
      }


  hod1xp->SaveAs("hod1xPos.pdf");
  hod1xn->SaveAs("hod1xNeg.pdf");

  hod1yp->SaveAs("hod1yPos.pdf");
  hod1yn->SaveAs("hod1yNeg.pdf");
  
  hod2xp->SaveAs("hod2xPos.pdf");
  hod2xn->SaveAs("hod2xNeg.pdf");
  
  hod2yp->SaveAs("hod2yPos.pdf");
  hod2yn->SaveAs("hod2yNeg.pdf");

  */

  //Loop over CALORIMETER PMT
  for (int ipmt=0; ipmt<13; ipmt++)
    {
      hCal_L1pos[ipmt] = new TH1F(Form("hCal_L1_%d+", ipmt+1 ), "", 200, -150, -50);
      hCal_L1neg[ipmt] = new TH1F(Form("hCal_L1_%d-", ipmt+1 ), "", 200, -150, -50);
      
      hCal_L2pos[ipmt] = new TH1F(Form("hCal_L2_%d+", ipmt+1 ), "", 200, -150, -50);
      hCal_L2neg[ipmt] = new TH1F(Form("hCal_L2_%d-", ipmt+1 ), "", 200, -150, -50);
      
      hCal_L3pos[ipmt] = new TH1F(Form("hCal_L3_%d+", ipmt+1 ), "", 200, -150, -50);
      hCal_L4pos[ipmt] = new TH1F(Form("hCal_L4_%d+", ipmt+1 ), "", 200, -150, -50);

      hCal1p->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.1pr.goodPosAdcTdcDiffTime[%d]>>hCal_L1_%d+", ipmt, ipmt+1), Form("H.cal.1pr.goodPosAdcMult[%d]>=1", ipmt));
      hCal1p->Modified();
      hCal_L1p_Mean = hCal_L1pos[ipmt]->GetMean(), hCal_L1p_Sig = hCal_L1pos[ipmt]->GetStdDev();
      hCal_tWinMin[0][0][ipmt] = hCal_L1p_Mean - 4.*hCal_L1p_Sig, hCal_tWinMax[0][0][ipmt] = hCal_L1p_Mean + 4.*hCal_L1p_Sig;    
      TLine *l1p_min = new TLine( hCal_tWinMin[0][0][ipmt], 0,  hCal_tWinMin[0][0][ipmt], hCal_L1pos[ipmt]->GetMaximum());
      l1p_min->SetLineColor(kRed);
      l1p_min->Draw();
      TLine *l1p_max = new TLine( hCal_tWinMax[0][0][ipmt], 0,  hCal_tWinMax[0][0][ipmt], hCal_L1pos[ipmt]->GetMaximum());
      l1p_max->SetLineColor(kRed);
      l1p_max->Draw();
      
      hCal1n->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.1pr.goodNegAdcTdcDiffTime[%d]>>hCal_L1_%d-", ipmt, ipmt+1), Form("H.cal.1pr.goodNegAdcMult[%d]>=1", ipmt));
      hCal1n->Modified();
      hCal_L1n_Mean = hCal_L1neg[ipmt]->GetMean(), hCal_L1n_Sig = hCal_L1neg[ipmt]->GetStdDev();
      hCal_tWinMin[0][1][ipmt] = hCal_L1n_Mean - 4.*hCal_L1n_Sig, hCal_tWinMax[0][1][ipmt] = hCal_L1n_Mean + 4.*hCal_L1n_Sig;    
      TLine *l1n_min = new TLine( hCal_tWinMin[0][1][ipmt], 0,  hCal_tWinMin[0][1][ipmt], hCal_L1neg[ipmt]->GetMaximum());
      l1n_min->SetLineColor(kRed);
      l1n_min->Draw();
      TLine *l1n_max = new TLine( hCal_tWinMax[0][1][ipmt], 0,  hCal_tWinMax[0][1][ipmt], hCal_L1neg[ipmt]->GetMaximum());
      l1n_max->SetLineColor(kRed);
      l1n_max->Draw();
       
      hCal2p->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.2ta.goodPosAdcTdcDiffTime[%d]>>hCal_L2_%d+", ipmt, ipmt+1), Form("H.cal.2ta.goodPosAdcMult[%d]>=1", ipmt));
      hCal2p->Modified();
      hCal_L2p_Mean = hCal_L2pos[ipmt]->GetMean(), hCal_L2p_Sig = hCal_L2pos[ipmt]->GetStdDev();
      hCal_tWinMin[1][0][ipmt] = hCal_L2p_Mean - 4.*hCal_L2p_Sig, hCal_tWinMax[1][0][ipmt] = hCal_L2p_Mean + 4.*hCal_L2p_Sig;    
      TLine *l2p_min = new TLine( hCal_tWinMin[1][0][ipmt], 0,  hCal_tWinMin[1][0][ipmt], hCal_L2pos[ipmt]->GetMaximum());
      l2p_min->SetLineColor(kRed);
      l2p_min->Draw();
      TLine *l2p_max = new TLine( hCal_tWinMax[1][0][ipmt], 0,  hCal_tWinMax[1][0][ipmt], hCal_L2pos[ipmt]->GetMaximum());
      l2p_max->SetLineColor(kRed);
      l2p_max->Draw();
 
      hCal2n->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.2ta.goodNegAdcTdcDiffTime[%d]>>hCal_L2_%d-", ipmt, ipmt+1), Form("H.cal.2ta.goodNegAdcMult[%d]>=1", ipmt));
      hCal2n->Modified();
      hCal_L2n_Mean = hCal_L2neg[ipmt]->GetMean(), hCal_L2n_Sig = hCal_L2neg[ipmt]->GetStdDev();
      hCal_tWinMin[1][1][ipmt] = hCal_L2n_Mean - 4.*hCal_L2n_Sig, hCal_tWinMax[1][1][ipmt] = hCal_L2n_Mean + 4.*hCal_L2n_Sig;    
      TLine *l2n_min = new TLine( hCal_tWinMin[1][1][ipmt], 0,  hCal_tWinMin[1][1][ipmt], hCal_L2neg[ipmt]->GetMaximum());
      l2n_min->SetLineColor(kRed);
      l2n_min->Draw();
      TLine *l2n_max = new TLine( hCal_tWinMax[1][1][ipmt], 0,  hCal_tWinMax[1][1][ipmt], hCal_L2neg[ipmt]->GetMaximum());
      l2n_max->SetLineColor(kRed);
      l2n_max->Draw();
      
      hCal3p->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.3ta.goodPosAdcTdcDiffTime[%d]>>hCal_L3_%d+", ipmt, ipmt+1), Form("H.cal.3ta.goodPosAdcMult[%d]>=1", ipmt));
      hCal3p->Modified();
      hCal_L3p_Mean = hCal_L3pos[ipmt]->GetMean(), hCal_L3p_Sig = hCal_L3pos[ipmt]->GetStdDev();
      hCal_tWinMin[2][0][ipmt] = hCal_L3p_Mean - 4.*hCal_L3p_Sig, hCal_tWinMax[2][0][ipmt] = hCal_L3p_Mean + 4.*hCal_L3p_Sig;    
      TLine *l3p_min = new TLine( hCal_tWinMin[2][0][ipmt], 0,  hCal_tWinMin[2][0][ipmt], hCal_L3pos[ipmt]->GetMaximum());
      l3p_min->SetLineColor(kRed);
      l3p_min->Draw();
      TLine *l3p_max = new TLine( hCal_tWinMax[2][0][ipmt], 0,  hCal_tWinMax[2][0][ipmt], hCal_L3pos[ipmt]->GetMaximum());
      l3p_max->SetLineColor(kRed);
      l3p_max->Draw();

      hCal4p->cd(ipmt+1);
      gPad->SetLogy();
      T->Draw(Form("H.cal.4ta.goodPosAdcTdcDiffTime[%d]>>hCal_L4_%d+", ipmt, ipmt+1), Form("H.cal.4ta.goodPosAdcMult[%d]>=1", ipmt));
      hCal4p->Modified();
      hCal_L4p_Mean = hCal_L4pos[ipmt]->GetMean(), hCal_L4p_Sig = hCal_L4pos[ipmt]->GetStdDev();
      hCal_tWinMin[3][0][ipmt] = hCal_L4p_Mean - 4.*hCal_L4p_Sig, hCal_tWinMax[3][0][ipmt] = hCal_L4p_Mean + 4.*hCal_L4p_Sig;    
      TLine *l4p_min = new TLine( hCal_tWinMin[3][0][ipmt], 0,  hCal_tWinMin[3][0][ipmt], hCal_L4pos[ipmt]->GetMaximum());
      l4p_min->SetLineColor(kRed);
      l4p_min->Draw();
      TLine *l4p_max = new TLine( hCal_tWinMax[3][0][ipmt], 0,  hCal_tWinMax[3][0][ipmt], hCal_L4pos[ipmt]->GetMaximum());
      l4p_max->SetLineColor(kRed);
      l4p_max->Draw();

      

    } //end loop over cal. pmts
  
  hCal1p->SaveAs("hCal_L1p.pdf");
  hCal1n->SaveAs("hCal_L1n.pdf");
  hCal2p->SaveAs("hCal_L2p.pdf");
  hCal2n->SaveAs("hCal_L2n.pdf");
  hCal3p->SaveAs("hCal_L3p.pdf");
  hCal4p->SaveAs("hCal_L4p.pdf");

  /************WRITE FIT RESULTS TO PARAMETER FILE***************/
  
  ofstream outPARAM;
  outPARAM.open(Form("../PARAM/HMS/HODO/hhodo_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
  outPARAM << "hhodo_PosAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << tWinMin[0][0][ipmt] << ", " << setw(15) << tWinMin[1][0][ipmt] << ", " << setw(15) << tWinMin[2][0][ipmt] << ", " << setw(15) << tWinMin[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  tWinMin[0][0][ipmt] << ", " << setw(15) << tWinMin[1][0][ipmt] << ", " << setw(15) << tWinMin[2][0][ipmt] << ", " << setw(15) << tWinMin[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_PosAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << tWinMax[0][0][ipmt] << ", " << setw(15) << tWinMax[1][0][ipmt] << ", " << setw(15) << tWinMax[2][0][ipmt] << ", " << setw(15) << tWinMax[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  tWinMax[0][0][ipmt] << ", " << setw(15) << tWinMax[1][0][ipmt] << ", " << setw(15) << tWinMax[2][0][ipmt] << ", " << setw(15) << tWinMax[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << tWinMin[0][1][ipmt] << ", " << setw(15) << tWinMin[1][1][ipmt] << ", " << setw(15) << tWinMin[2][1][ipmt] << ", " << setw(15) << tWinMin[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  tWinMin[0][1][ipmt] << ", " << setw(15) << tWinMin[1][1][ipmt] << ", " << setw(15) << tWinMin[2][1][ipmt] << ", " << setw(15) << tWinMin[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
     outPARAM << tWinMax[0][1][ipmt] << ", " << setw(15) << tWinMax[1][1][ipmt] << ", " << setw(15) << tWinMax[2][1][ipmt] << ", " << setw(15) << tWinMax[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  tWinMax[0][1][ipmt] << ", " << setw(15) << tWinMax[1][1][ipmt] << ", " << setw(15) << tWinMax[2][1][ipmt] << ", " << setw(15) << tWinMax[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM.close();
  

  //WRITE CALORIMETER TIME Window Cuts to param file
  
  outPARAM.open(Form("../PARAM/HMS/CAL/hCal_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hcal_pos_AdcTimeWindowMin = ";
  
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << hCal_tWinMin[layer][0][0]<<","
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
      outPARAM << setw(38)<< hCal_tWinMin[layer][0][0]<<","
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
	outPARAM << hCal_tWinMax[layer][0][0]<<","
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
      outPARAM << setw(38)<< hCal_tWinMax[layer][0][0]<<","
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
	outPARAM << hCal_tWinMin[layer][1][0]<<","
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
      outPARAM << setw(38)<< hCal_tWinMin[layer][1][0]<<","
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
	outPARAM << hCal_tWinMax[layer][1][0]<<","
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
      outPARAM << setw(38)<< hCal_tWinMax[layer][1][0]<<","
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

  /*
 //--------Write Parameters to Param File-----
 for (Int_t ipmt = 0; ipmt < 13; ipmt++){
   if (ipmt==0){
     outPARAM << hCal_tWinMin[0][0][ipmt] << ", " << setw(15) << hCal_tWinMin[1][0][ipmt] << ", " << setw(15) << hCal_tWinMin[2][0][ipmt] << ", " << setw(15) << hCal_tWinMin[3][0][ipmt] << fixed << endl; 
   }
   else{
     outPARAM << setw(36) <<  hCal_tWinMin[0][0][ipmt] << ", " << setw(15) << hCal_tWinMin[1][0][ipmt] << ", " << setw(15) << hCal_tWinMin[2][0][ipmt] << ", " << setw(15) << hCal_tWinMin[3][0][ipmt] << fixed << endl; 
   }
 } //end pmt loop
  
 outPARAM << " " << endl;
 outPARAM << " " << endl;

 outPARAM << "hcal_pos_AdcTimeWindowMax = ";
   
 //--------Write Parameters to Param File-----
 for (Int_t ipmt = 0; ipmt < 13; ipmt++){
   if (ipmt==0){
     outPARAM << hCal_tWinMax[0][0][ipmt] << ", " << setw(15) << hCal_tWinMax[1][0][ipmt] << ", " << setw(15) << hCal_tWinMax[2][0][ipmt] << ", " << setw(15) << hCal_tWinMax[3][0][ipmt] << fixed << endl; 
   }
   else{
     outPARAM << setw(36) <<  hCal_tWinMax[0][0][ipmt] << ", " << setw(15) << hCal_tWinMax[1][0][ipmt] << ", " << setw(15) << hCal_tWinMax[2][0][ipmt] << ", " << setw(15) << hCal_tWinMax[3][0][ipmt] << fixed << endl; 
   }
 } //end pmt loop
 
 outPARAM << " " << endl;
 outPARAM << " " << endl;

 outPARAM << "hcal_neg_AdcTimeWindowMin = ";
   
 //--------Write Parameters to Param File-----
 for (Int_t ipmt = 0; ipmt < 13; ipmt++){
   if (ipmt==0){
     outPARAM << hCal_tWinMin[0][1][ipmt] << ", " << setw(15) << hCal_tWinMin[1][1][ipmt] << ", " << setw(15) << hCal_tWinMin[2][1][ipmt] << ", " << setw(15) << hCal_tWinMin[3][1][ipmt] << fixed << endl; 
   }
   else{
     outPARAM << setw(36) <<  hCal_tWinMin[0][1][ipmt] << ", " << setw(15) << hCal_tWinMin[1][1][ipmt] << ", " << setw(15) << hCal_tWinMin[2][1][ipmt] << ", " << setw(15) << hCal_tWinMin[3][1][ipmt] << fixed << endl; 
   }
 } //end pmt loop
  
 outPARAM << " " << endl;
 outPARAM << " " << endl;

 outPARAM << "hcal_neg_AdcTimeWindowMax = ";
   
 //--------Write Parameters to Param File-----
 for (Int_t ipmt = 0; ipmt < 13; ipmt++){
   if (ipmt==0){
     outPARAM << hCal_tWinMax[0][1][ipmt] << ", " << setw(15) << hCal_tWinMax[1][1][ipmt] << ", " << setw(15) << hCal_tWinMax[2][1][ipmt] << ", " << setw(15) << hCal_tWinMax[3][1][ipmt] << fixed << endl; 
   }
   else{
     outPARAM << setw(36) <<  hCal_tWinMax[0][1][ipmt] << ", " << setw(15) << hCal_tWinMax[1][1][ipmt] << ", " << setw(15) << hCal_tWinMax[2][1][ipmt] << ", " << setw(15) << hCal_tWinMax[3][1][ipmt] << fixed << endl; 
   }
 } //end pmt loop

  */
 outPARAM.close();

  //Write Histograms to ROOT file
  outROOT->Write();
  outROOT->Close();
  
}
