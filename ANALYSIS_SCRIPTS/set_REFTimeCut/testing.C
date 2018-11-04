void testing()
{
  
  Double_t var;
  Double_t cert1[2];
  Double_t mult[2];
  TString name1 = "H.cer.goodAdcTdcDiffTime";
  TString name2 = "H.cer.goodAdcMult";
  
  
  TString filename = "../../../ROOTfiles/coin_replay_timeWin_check_3288_1000.root";
  
  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  T->SetBranchAddress("H.cer.goodAdcTdcDiffTime", &var);  
  //T->SetBranchAddress("H.cer.goodAdcTdcDiffTime", &cert1[1]);
 

  //T->SetBranchAddress("H.cer.goodAdcMult", &mult);

  TH1F* hcer1 = new TH1F("CER1", "", 200, 0, 200);
  //TH1F* hcer2 = new TH1F("CER2", "", 200, 0, 200);
  
  //TH1F* hcer1m = new TH1F("CER1m", "", 10, 0.1, 10);
  //TH1F* hcer2m = new TH1F("CER2m", "", 10, 0.1, 10);
  
  Long64_t nentries = T->GetEntries();
  
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i); 

      //cout << Form("------Event %lld", i+1) << endl;
 
      // cout << "var = " << var << endl;
      //cout << "cer_time_pmt1 =" << cert1[0] << endl; 
      //cout << "cer_time_pmt2 =" << cert1[1] << endl; 

      //hcer1->Fill(var);
      //hcer2->Fill(cert1[1]);
      
      //hcer1m->Fill(mult[0]);
      //hcer2m->Fill(mult[1]);



    }
  
  
  //TCanvas *c1 = new TCanvas("c1", "" ,1000, 1000);
  //c1->Divide(2,2);
  //c1->cd(1);
  //hcer1->Draw();
  //c1->cd(2);
  //hcer2->Draw();
  
  //c1->cd(3);
  //hcer1m->Draw();
  //c1->cd(4);
  //hcer1m->Draw();
  
}
