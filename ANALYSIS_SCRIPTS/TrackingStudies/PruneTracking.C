//This code served to look at all possibloe tracks, P.tr.*, H.tr.*
//And to look at pruning variables to select appropiate pruning parameters
//in pracking.param and htracking.param

void PruneTracking()
{

  TString eArm = "SHMS";
  TString hArm = "HMS";

  int run, evt;
  run = 3377;
  evt = 50000;
 
  
  TString filename = Form("../../../ROOTfiles/coin_replay_trkStudy_%d_%d.root", run, evt); 
  
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  //Histograms (The capital "H" stands for histogram)
  TH1F *H_trk_exptar = new TH1F("H_trk_exptar", eArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_eyptar = new TH1F("H_trk_eyptar", eArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_eytar = new TH1F("trk_eytar", eArm + " Ytar", 100, -4, 4); 
  TH1F *H_trk_edelta = new TH1F("trk_edelta", eArm + " Delta", 100, -10, 22); 
    
  TH1F *H_trk_hxptar = new TH1F("trk_hxptar", hArm + " X'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_hyptar = new TH1F("trk_hyptar", hArm + " Y'tar", 100, -0.1, 0.1); 
  TH1F *H_trk_hytar = new TH1F("trk_hytar", hArm + " Ytar", 100, -7, 7); 
  TH1F *H_trk_hdelta = new TH1F("trk_hdelta", hArm + " Delta", 100, -15, 15); 
    
  TH1F *H_trk_entrks = new TH1F("H_trk_entrks", eArm + " Total Tracks", 100, -1, 11); 
  TH1F *H_trk_ebeta = new TH1F("trk_ebeta", eArm + " Track Beta", 100, 0.6, 1.2); 
  TH1F *H_trk_ep = new TH1F("trk_ep", eArm + " Track Momentum", 100, 6, 10); 
  TH1F *H_trk_echi2 = new TH1F("trk_echi2", eArm + " Track Chi2", 100, 0, 100); 

  TH1F *H_trk_hntrks = new TH1F("H_trk_hntrks", hArm + " Total Tracks", 100, -1, 11); 
  TH1F *H_trk_hbeta = new TH1F("trk_hbeta", hArm + " Track Beta", 100, 0.6, 1.2); 
  TH1F *H_trk_hp = new TH1F("trk_hp", hArm + " Track Momentum", 100, 1.5, 2.3); 
  TH1F *H_trk_hchi2 = new TH1F("trk_hchi2", hArm + " Track Chi2", 100, 0, 100); 
  
  //Golden Track Histos
  TH1F *H_gtrk_edelta = new TH1F("gtrk_edelta", eArm + " Delta", 100, -10, 22); 



  //Variables
  Int_t etrk_nhits;   //track variables have multiple hits, as the golden hit has not been chosen yet. (All track ndata are the same) 
  Double_t entrk;  //total nummber of tracks 
  Double_t exptar[100];
  Double_t eyptar[100];
  Double_t eytar[100];
  Double_t edelta[100];
  Double_t trk_ebeta[100];
  Double_t trk_ep[100];
  Double_t trk_echi2[100];
  Double_t gtrk_edelta;

  Int_t htrk_nhits;  
  Double_t hntrk;   //total nummber of tracks 
  Double_t hxptar[100];
  Double_t hyptar[100];
  Double_t hytar[100];
  Double_t hdelta[100];
  Double_t trk_hbeta[100];
  Double_t trk_hp[100];
  Double_t trk_hchi2[100];
 


  //Set Branch Address

  T->SetBranchAddress("Ndata.P.tr.tg_th", &etrk_nhits);
  T->SetBranchAddress("P.tr.n", &entrk);
  T->SetBranchAddress("P.tr.tg_th", exptar);
  T->SetBranchAddress("P.tr.tg_ph", eyptar);
  T->SetBranchAddress("P.tr.tg_y", eytar);
  T->SetBranchAddress("P.tr.tg_dp", edelta);
  T->SetBranchAddress("P.tr.beta", trk_ebeta);
  T->SetBranchAddress("P.tr.p", trk_ep);
  T->SetBranchAddress("P.tr.chi2", trk_echi2);
  T->SetBranchAddress("P.gtr.dp", &gtrk_edelta);


  T->SetBranchAddress("Ndata.H.tr.tg_th", &htrk_nhits);
  T->SetBranchAddress("H.tr.n", &hntrk);
  T->SetBranchAddress("H.tr.tg_th", hxptar);
  T->SetBranchAddress("H.tr.tg_ph", hyptar);
  T->SetBranchAddress("H.tr.tg_y", hytar);
  T->SetBranchAddress("H.tr.tg_dp", hdelta);
  T->SetBranchAddress("H.tr.beta", trk_hbeta);
  T->SetBranchAddress("H.tr.p", trk_hp);
  T->SetBranchAddress("H.tr.chi2", trk_hchi2);

  
  //Long64_t nentries = T->GetEntries();
  
  //cout << "nentries = " << nentries << endl;
 
  for (Long64_t i=0; i<T->GetEntries(); i++) {
    
    T->GetEntry(i);

    H_trk_entrks->Fill(entrk);
    //Loop over all SHMS hits per track event
    for (int e_ihit = 0; e_ihit<etrk_nhits; e_ihit++)
      {
	
	//Fill Electron Arm Histograms
	H_trk_exptar->Fill(exptar[e_ihit]);
	H_trk_eyptar->Fill(eyptar[e_ihit]);
	H_trk_eytar->Fill(eytar[e_ihit]);
	H_trk_edelta->Fill(edelta[e_ihit]);
	H_trk_ebeta->Fill(trk_ebeta[e_ihit]);
	H_trk_ep->Fill(trk_ep[e_ihit]);
	H_trk_echi2->Fill(trk_echi2[e_ihit]);
      }
    //Fill Golden Track
    H_gtrk_edelta->Fill(gtrk_edelta);


    H_trk_hntrks->Fill(hntrk);
    //Loop over all HMS hits per track event
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
      }
    

  } //end entry loop
 

  //Draw Histograms to Canvas
  TCanvas *etg_Canv = new TCanvas("e0", "SHMS Track Quantities", 1500, 1500);
  etg_Canv->Divide(2,2);
  TCanvas *ekin_Canv = new TCanvas("e1", "SHMS Kin Quantities", 1500, 1500);
  ekin_Canv->Divide(2,2);
   
  TCanvas *htg_Canv = new TCanvas("h0", "HMS Track Quantities", 1500, 1500);
  htg_Canv->Divide(2,2);
  TCanvas *hkin_Canv = new TCanvas("h1", "HMS Kin Quantities", 1500, 1500);
  hkin_Canv->Divide(2,2);
  

  //SHMS Track @ Target Quantities
  etg_Canv->cd(1);
  H_trk_exptar->Draw();
  etg_Canv->cd(2);
  H_trk_eyptar->Draw();
  etg_Canv->cd(3);
  H_trk_eytar->Draw();
  etg_Canv->cd(4);
  H_trk_edelta->Draw();
  H_gtrk_edelta->SetLineColor(kRed);
  H_gtrk_edelta->Draw("sames");

  //SHMS Misc.
  ekin_Canv->cd(1);
  H_trk_entrks->Draw();
  ekin_Canv->cd(2);
  H_trk_echi2->Draw();
  ekin_Canv->cd(3);
  H_trk_ep->Draw();
  ekin_Canv->cd(4);
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

}
