//This code served to look at all possibloe tracks, P.tr.*, H.tr.*
//And to look at pruning variables to select appropiate pruning parameters
//in pracking.param and htracking.param

void PruneTracking()
{

  gStyle->SetOptStat(1111111);

  //Define some constants
  Double_t Mp = 0.938272;
  Double_t me = 0.00051099;

  Double_t fStartTimeCenter_e = 32.;  //defined in phodo_cuts.param / hhodo_cuts.param to be the same
  Double_t fStartTimeCenter_h = 32.;  //defined in phodo_cuts.param / hhodo_cuts.param to be the same

  //Define some Pruning Variables that involve differences
  Double_t fPruneBeta_e;    // beta - p/E (electrons)
  Double_t fPruneBeta_h;    // beta - p/E (hadrons)       
  
  Double_t fPruneFpTime_e;   //P.hod.fpHitsTime - fStartTimeCenter
  Double_t fPruneFpTime_h;   //H.hod.fpHitsTime - fStartTimeCenter

  TString nametrk = ""; //string to name number of tracks in TLegend

  //Define Minimum Chi2 (TO be used to choose smalles chi2 in track loop)
  Double_t fMinChi2_e = 0.0;
  Int_t good_echi2trk = 0;    //track corresponding to the minimum chi2 value

  TString eArm = "SHMS";
  TString hArm = "HMS";

  int run, evt;
  run = 3377;
  evt = -1;
 
  
  TString filename = Form("../../../../ROOTfiles/coin_replay_trkStudy_%d_%d.root", run, evt); 
  
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  //Histograms (The capital "H" stands for histogram)
  TH1F *H_trk_exptar = new TH1F("H_trk_exptar", eArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_eyptar = new TH1F("H_trk_eyptar", eArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_eytar = new TH1F("trk_eytar", eArm + " Ytar", 100, -4, 4); 
  TH1F *H_trk_edelta = new TH1F("trk_edelta", eArm + " Delta", 100, -10, 22); 
  TH1F *H_trk_entrks = new TH1F("H_trk_entrks", eArm + " Total Tracks", 100, -1, 11); 
  TH1F *H_trk_ebeta = new TH1F("trk_ebeta", eArm + " Track Beta", 100, 0.6, 1.2); 
  TH1F *H_trk_ep = new TH1F("trk_ep", eArm + " Track Momentum", 100, 6, 10); 
  TH1F *H_trk_echi2 = new TH1F("trk_echi2", eArm + " Track Chi2", 100, 0, 100); 
  TH1F *H_trk_ebetachi2 = new TH1F("trk_ebetachi2", eArm + " Track Beta Chi2", 100, -5, 80); 
  TH1F *H_trk_eNDoF = new TH1F("trk_eNDoF", eArm + " # Deg. of Freedom", 100, 0, 15); 

  TH1F *H_trk_hxptar = new TH1F("trk_hxptar", hArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_hyptar = new TH1F("trk_hyptar", hArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_hytar = new TH1F("trk_hytar", hArm + " Ytar", 100, -7, 7); 
  TH1F *H_trk_hdelta = new TH1F("trk_hdelta", hArm + " Delta", 100, -15, 15);   
  TH1F *H_trk_hntrks = new TH1F("H_trk_hntrks", hArm + " Total Tracks", 100, -1, 11); 
  TH1F *H_trk_hbeta = new TH1F("trk_hbeta", hArm + " Track Beta", 100, 0.6, 1.2); 
  TH1F *H_trk_hp = new TH1F("trk_hp", hArm + " Track Momentum", 100, 1.5, 2.3); 
  TH1F *H_trk_hchi2 = new TH1F("trk_hchi2", hArm + " Track Chi2", 100, 0, 100); 
  TH1F *H_trk_hbetachi2 = new TH1F("trk_hbetachi2", hArm + " Track Beta Chi2", 100, -5, 80); 
  TH1F *H_trk_hNDoF = new TH1F("trk_hNDoF", hArm + " # Deg. of Freedom", 100, 0, 15); 

  //Special Pruning Histograms (Differences of variables)
  TH1F *H_trk_pruneBeta_e = new TH1F("trk_pruneBeta_e", "BetaTrack - BetaP", 100, -0.5, 0.5);
  TH1F *H_trk_pruneFPTime_e = new TH1F("trk_pruneFPTime_e", "FPTime - StartTimeCenter", 100, -50, 50);

  //Golden Track Histos (As Determine By Pruning Tracking Procedure)
  TH1F *H_gtrkprune_exptar = new TH1F("H_gtrkprune_exptar", eArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_gtrkprune_eyptar = new TH1F("H_gtrkprune_eyptar", eArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_gtrkprune_eytar = new TH1F("gtrkprune_eytar", eArm + " Ytar", 100, -4, 4); 
  TH1F *H_gtrkprune_edelta = new TH1F("gtrkprune_edelta", eArm + " Delta", 100, -10, 22); 
  


  //Golden Track Histos (As Determine By Lowest Chi2 Tracking Procedure)
  TH1F *H_gtrkchi2_exptar = new TH1F("H_gtrkchi2_exptar", eArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_gtrkchi2_eyptar = new TH1F("H_gtrkchi2_eyptar", eArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_gtrkchi2_eytar = new TH1F("gtrkchi2_eytar", eArm + " Ytar", 100, -4, 4); 
  TH1F *H_gtrkchi2_edelta = new TH1F("gtrkchi2_edelta", eArm + " Delta", 100, -10, 22); 


  //Track Variables
  Int_t etrk_nhits;   //track variables have multiple hits, as the golden hit has not been chosen yet. (All track ndata are the same) 
  Double_t entrk;  //total nummber of tracks 
  Double_t exptar[100];    
  Double_t eyptar[100];
  Double_t eytar[100];
  Double_t edelta[100];
  Double_t trk_ebeta[100];
  Double_t trk_ep[100];          //track electron momentum
  Double_t trk_echi2[100];   
  Double_t trk_ebetachi2[100];
  Double_t trk_eDoF[100];         //degrees of freedom
  Double_t fpHitsTime_e;
  //Golden Track Variables
  Double_t gtrk_edelta;
  Double_t gtrk_exptar;
  Double_t gtrk_eyptar;
  Double_t gtrk_eytar;
  Double_t gtrk_beta;



  Int_t htrk_nhits;  
  Double_t hntrk;   //total nummber of tracks 
  Double_t hxptar[100];
  Double_t hyptar[100];
  Double_t hytar[100];
  Double_t hdelta[100];
  Double_t trk_hbeta[100];
  Double_t trk_hp[100];
  Double_t trk_hchi2[100];
  Double_t trk_hbetachi2[100];
  Double_t trk_hDoF[100];
  Double_t fpHitsTime_h;

  //Define Additional Variables to be calculated inside Loop
  Double_t fBetaP_e;  //Electron arm beta calculated from track momentum
  Double_t fBetaP_h;  //Hadron arm beta calculated from track momentum


  //Set Branch Address
  T->SetBranchAddress("Ndata.P.tr.tg_th", &etrk_nhits);
  T->SetBranchAddress("P.tr.n", &entrk);
  T->SetBranchAddress("P.tr.tg_dp", edelta);
  T->SetBranchAddress("P.tr.tg_th", exptar);
  T->SetBranchAddress("P.tr.tg_ph", eyptar);
  T->SetBranchAddress("P.tr.tg_y", eytar);
  T->SetBranchAddress("P.tr.beta", trk_ebeta);
  T->SetBranchAddress("P.tr.p", trk_ep);
  T->SetBranchAddress("P.tr.chi2", trk_echi2);
  T->SetBranchAddress("P.tr.betachisq", trk_ebetachi2);
  T->SetBranchAddress("P.tr.ndof",  trk_eDoF);
  T->SetBranchAddress("P.hod.fpHitsTime", &fpHitsTime_e);

  T->SetBranchAddress("P.gtr.dp", &gtrk_edelta);
  T->SetBranchAddress("P.gtr.th", &gtrk_exptar);
  T->SetBranchAddress("P.gtr.ph", &gtrk_eyptar);
  T->SetBranchAddress("P.gtr.y", &gtrk_eytar);


  T->SetBranchAddress("Ndata.H.tr.tg_th", &htrk_nhits);
  T->SetBranchAddress("H.tr.n", &hntrk);
  T->SetBranchAddress("H.tr.tg_th", hxptar);
  T->SetBranchAddress("H.tr.tg_ph", hyptar);
  T->SetBranchAddress("H.tr.tg_y", hytar);
  T->SetBranchAddress("H.tr.tg_dp", hdelta);
  T->SetBranchAddress("H.tr.beta", trk_hbeta);
  T->SetBranchAddress("H.tr.p", trk_hp);
  T->SetBranchAddress("H.tr.chi2", trk_hchi2);
  T->SetBranchAddress("H.tr.betachisq", trk_hbetachi2);
  T->SetBranchAddress("H.tr.ndof",  trk_hDoF);
  T->SetBranchAddress("H.hod.fpHitsTime", &fpHitsTime_h);


  Bool_t entrk_cut;
  Bool_t hntrk_cut;

  //Loop over number of events
  for (Long64_t i=0; i<T->GetEntries(); i++) {
    
    T->GetEntry(i);


    //Set Cut on number of tracks
    entrk_cut = entrk > 1;
      
      H_trk_entrks->Fill(entrk);
      //cout << " ** total # tracks = " << entrk << endl;
      //cout << " ** total # hits = " << etrk_nhits << endl;

      if(entrk_cut){
	
	nametrk = Form("All %d-Track Events", int(entrk));
	  
	  //cout << "-----EVENT " << i << "-----" << endl;

      //Loop over all SHMS tracks per event
      for (int e_ihit = 0; e_ihit<etrk_nhits; e_ihit++)
	{
	  //Assume 1st track Minimum Chi2 
	  fMinChi2_e = trk_echi2[0];
	  good_echi2trk = 0;
	  
	  //Check if subsequent tracks have a smaller chi2
	  if( trk_echi2[e_ihit] <  fMinChi2_e ){
	    fMinChi2_e = trk_echi2[e_ihit];
	    good_echi2trk = e_ihit;
	  }

	  //Calculate additional Pruning variables
	  fBetaP_e = trk_ep[e_ihit] / sqrt(trk_ep[e_ihit]*trk_ep[e_ihit] + me*me);   //beta from track momentum
	  fPruneBeta_e = trk_ebeta[e_ihit] - fBetaP_e;
	  fPruneFpTime_e = fpHitsTime_e - fStartTimeCenter_e;

	  H_trk_pruneBeta_e->Fill(fPruneBeta_e);
	  H_trk_pruneFPTime_e->Fill(fPruneFpTime_e);

	  /*
	  cout << " ** itrack = " << e_ihit << endl; 
	  cout << " ** itrack exptar << " << exptar[e_ihit] << endl;
	  cout << " ** itrack eyptar << " << eyptar[e_ihit] << endl;
	  cout << " ** itrack eytar << " << eytar[e_ihit] << endl;
	  cout << " ** itrack edelta = " << edelta[e_ihit] << endl; 
	  cout << " ** itrack ebeta_diff = " << fPruneBeta_e << endl;
	  cout << " ** itrack dof = " << trk_eDoF[e_ihit] << endl;
	  cout << " ** itrack chi2beta = " <<  trk_ebetachi2[e_ihit] << endl;
	  cout << " ** itrack fptime_diff = " <<  fPruneFpTime_e << endl;
	  cout << " ** itrack echi2 = " << trk_echi2[e_ihit] << endl; 
	  */

	  //Fill Electron Arm Histograms (Fill Using ALL Possible Tracks)
	  H_trk_exptar->Fill(exptar[e_ihit]);
	  H_trk_eyptar->Fill(eyptar[e_ihit]);
	  H_trk_eytar->Fill(eytar[e_ihit]);
	  H_trk_edelta->Fill(edelta[e_ihit]);
	  H_trk_ebeta->Fill(trk_ebeta[e_ihit]);
	  H_trk_ep->Fill(trk_ep[e_ihit]);
	  H_trk_echi2->Fill(trk_echi2[e_ihit]);
	  H_trk_ebetachi2->Fill(trk_ebetachi2[e_ihit]);
	  H_trk_eNDoF->Fill(trk_eDoF[e_ihit]);

	} //end loop over etracks

      
      //cout << "**MinChi2 = " << fMinChi2_e << endl;
      //cout << "**MinChi2 Track = " << good_echi2trk << endl;
	 
      //Fill Electron Arm Histograms (Using Lowest Chi2 Method)
      H_gtrkchi2_exptar->Fill(exptar[good_echi2trk]);
      H_gtrkchi2_eyptar->Fill(eyptar[good_echi2trk]);
      H_gtrkchi2_eytar->Fill(eytar[good_echi2trk]);
      H_gtrkchi2_edelta->Fill(edelta[good_echi2trk]);
      
      //Fill Golden Track (Using the Prune Method)
      H_gtrkprune_exptar->Fill(gtrk_exptar);
      H_gtrkprune_eyptar->Fill(gtrk_eyptar);
      H_gtrkprune_eytar->Fill(gtrk_eytar);
      H_gtrkprune_edelta->Fill(gtrk_edelta);

      //cout << " ** golden track edelta = " <<  gtrk_edelta << endl;
      


      } //end num. etracks cut

    hntrk_cut = hntrk >= 2;
    H_trk_hntrks->Fill(hntrk);
    //Loop over all HMS tracks per event
    for (int h_ihit = 0; h_ihit<htrk_nhits; h_ihit++)
      {
	
	//Fill Hadron Arm Histograms
	H_trk_hxptar->Fill(hxptar[h_ihit]);
	H_trk_hyptar->Fill(hyptar[h_ihit]);
	H_trk_hytar->Fill(hytar[h_ihit]);
	H_trk_hdelta->Fill(hdelta[h_ihit]);
	H_trk_hbeta->Fill(trk_hbeta[h_ihit]);
	H_trk_hp->Fill(trk_hp[h_ihit]);
	H_trk_hchi2->Fill(trk_hchi2[h_ihit]);
       
      

      } //end loop over all hits
    

  } //end entry loop
 
  
  //Draw Histograms to Canvas
  TCanvas *etg_Canv = new TCanvas("e0", "SHMS Track Quantities", 1500, 1500);
  etg_Canv->Divide(2,2);
  //TCanvas *emisc_Canv = new TCanvas("e1", "SHMS Miscellaneous Quantities", 1500, 1500);
  //emisc_Canv->Divide(2,2);
  TCanvas *ePrune_Canv = new TCanvas("e2", "SHMS Pruning Quantities", 1500, 1200);
  ePrune_Canv->Divide(3,2);

  /*
  TCanvas *htg_Canv = new TCanvas("h0", "HMS Track Quantities", 1500, 1500);
  htg_Canv->Divide(2,2);
  TCanvas *hkin_Canv = new TCanvas("h1", "HMS Kin Quantities", 1500, 1500);
  hkin_Canv->Divide(2,2);
  */

  //SHMS Track @ Target Quantities
  auto leg1 = new TLegend(0.1,0.8,0.28,0.9);
  auto leg2 = new TLegend(0.1,0.8,0.28,0.9);
  auto leg3 = new TLegend(0.1,0.8,0.28,0.9);
  auto leg4 = new TLegend(0.1,0.8,0.28,0.9);
    
  etg_Canv->cd(1);
  H_trk_exptar->Draw();
  H_gtrkprune_exptar->Draw("sames");
  H_gtrkchi2_exptar->Draw("sames");
  H_trk_exptar->SetLineColor(kBlack);
  H_gtrkprune_exptar->SetLineColor(kRed);
  H_gtrkchi2_exptar->SetLineColor(kBlue);
  leg1->AddEntry(H_trk_exptar, nametrk, "f");
  leg1->AddEntry(H_gtrkprune_exptar, "Prune", "f");
  leg1->AddEntry(H_gtrkchi2_exptar, "Best Chi2", "f");
  leg1->Draw();

  etg_Canv->cd(2);
  H_trk_eyptar->Draw();
  H_gtrkprune_eyptar->Draw("sames");
  H_gtrkchi2_eyptar->Draw("sames");
  H_trk_eyptar->SetLineColor(kBlack);
  H_gtrkprune_eyptar->SetLineColor(kRed);
  H_gtrkchi2_eyptar->SetLineColor(kBlue);
  leg2->AddEntry(H_trk_eyptar, nametrk, "f");
  leg2->AddEntry(H_gtrkprune_eyptar, "Prune", "f");
  leg2->AddEntry(H_gtrkchi2_eyptar, "Best Chi2", "f");
  leg2->Draw();

  etg_Canv->cd(3);
  H_trk_eytar->Draw();
  H_gtrkprune_eytar->Draw("sames");
  H_gtrkchi2_eytar->Draw("sames");
  H_trk_eytar->SetLineColor(kBlack);
  H_gtrkprune_eytar->SetLineColor(kRed);
  H_gtrkchi2_eytar->SetLineColor(kBlue);
  leg3->AddEntry(H_trk_eytar, nametrk, "f");
  leg3->AddEntry(H_gtrkprune_eytar, "Prune", "f");
  leg3->AddEntry(H_gtrkchi2_eytar, "Best Chi2", "f");
  leg3->Draw();


  etg_Canv->cd(4);
  H_trk_edelta->Draw();
  H_gtrkprune_edelta->Draw("sames");
  H_gtrkchi2_edelta->Draw("sames");
  H_trk_edelta->SetLineColor(kBlack);
  H_gtrkprune_edelta->SetLineColor(kRed);
  H_gtrkchi2_edelta->SetLineColor(kBlue);
  leg4->AddEntry(H_trk_edelta, nametrk, "f");
  leg4->AddEntry(H_gtrkprune_edelta, "Prune", "f");
  leg4->AddEntry(H_gtrkchi2_edelta, "Best Chi2", "f");
  leg4->Draw();


  ePrune_Canv->cd(1);
  H_trk_pruneBeta_e->SetFillStyle(3);
  H_trk_pruneBeta_e->SetLineWidth(2);
  H_trk_pruneBeta_e->Draw();


  ePrune_Canv->cd(2);
  H_trk_pruneFPTime_e->SetFillStyle(3);
  H_trk_pruneFPTime_e->SetLineWidth(2);
  H_trk_pruneFPTime_e->Draw();

  ePrune_Canv->cd(3);


  /*
  //SHMS Misc.
  emisc_Canv->cd(1);
  H_trk_entrks->Draw();
  emisc_Canv->cd(2);
  H_trk_echi2->Draw();
  emisc_Canv->cd(3);
  H_trk_ep->Draw();
  emisc_Canv->cd(4);
  H_trk_ebeta->Draw();


  //HMS Track @ Target Quantities
  htg_Canv->cd(1);
  H_trk_hxptar->Draw();
  htg_Canv->cd(2);
  H_trk_hyptar->Draw();
  htg_Canv->cd(3);
  H_trk_hytar->Draw();
  htg_Canv->cd(4);
  H_trk_hdelta->Draw();

  //HMS Misc.
  hkin_Canv->cd(1);
  H_trk_hntrks->Draw();
  hkin_Canv->cd(2);
  H_trk_hchi2->Draw();
  hkin_Canv->cd(3);
  H_trk_hp->Draw();
  hkin_Canv->cd(4);
  H_trk_hbeta->Draw();
  */
}
