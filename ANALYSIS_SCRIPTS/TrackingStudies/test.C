void test()
{
  
  TString filename = "../../../ROOTfiles/coin_replay_trkStudy_3377_50000.root"; 
    
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  Double_t a[100];
  Double_t b[100];
  Double_t c[100];
  Double_t d[100];
 
  Int_t na;
  Int_t nb;
  Int_t nc;
  Int_t nd;


  T->SetBranchAddress("P.tr.tg_ph", a);
  T->SetBranchAddress("Ndata.P.tr.tg_ph", &na);


  T->SetBranchAddress("P.tr.tg_th", &b);
  T->SetBranchAddress("P.tr.tg_y", &c);
  T->SetBranchAddress("P.tr.tg_dp", &d);

  for (Long64_t i=0; i<T->GetEntries()-1; i++) {
    
    T->GetEntry(i);
    
    //cout << "i = " << endl;
    //cout << "Ndata = " << na << endl;

    for (int ihit=0; ihit<na; ihit++)
      {
	cout << "ihit = " << ihit << endl;
	cout << a[ihit] << endl;
	
      }


  }
    
  }
