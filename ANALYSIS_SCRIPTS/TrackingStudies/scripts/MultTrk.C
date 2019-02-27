void MultTrk()
{

  int run, evt;
  run = 3377;
  evt = 10000;
 
  
  TString filename = Form("../../../../ROOTfiles/coin_replay_trkStudy_%d_%d.root", run, evt); 
  
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  //Define Variables
  Double_t pdc_ntrk;
  Double_t goodscinhit;
  Double_t etotnorm;
  Double_t betanotrk;
  Double_t ngc_npeSum;

  T->SetBranchAddress("P.dc.ntrack", &pdc_ntrk);
  T->SetBranchAddress("P.hod.goodscinhit", &goodscinhit);
  T->SetBranchAddress("P.cal.etotnorm", &etotnorm);
  T->SetBranchAddress("P.hod.betanotrack", &betanotrk);
  T->SetBranchAddress("P.ngcer.npeSum", &ngc_npeSum);

 //Loop over number of events
  for (Long64_t i=0; i<T->GetEntries(); i++) {
    
    T->GetEntry(i);
  
    if(goodscinhit==1&&pdc_ntrk==1&&etotnorm>1.7){
    cout << "---Event: " << i << "----" << endl;
    cout << "pdc_ntrack = " << pdc_ntrk << endl;
    cout << "phod_goodscinhit = " << goodscinhit << endl;
    cout << "etot_norm = " << etotnorm << endl;
    cout << "beta_notrk = " << betanotrk << endl;
    cout << "ngc_npeSum = " << ngc_npeSum << endl;
    }


  }

}
