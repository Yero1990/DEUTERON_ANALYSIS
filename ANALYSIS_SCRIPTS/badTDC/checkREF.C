void checkREF()
{

  gROOT->SetBatch(kTRUE); 
 

  //run list
  static const int run[6] = {1135, 1311, 1763, 1880, 2097, 4321};

  TCanvas *c1 = new TCanvas("Plane 1V2, UnCorr REF Time ", "Plane 1V2, Wire Group 33-48, UnCorr. REF. Time",  1500, 500);
  TCanvas *c2 = new TCanvas("Plane 1V2, Corr REF Time ", "Plane 1V2, Wire Group 33-48, Corr. REF. Time",  1500, 500);

  c1->Divide(3,2);
  c2->Divide(3,2);
  
  TH2F *goodgroup_noref[6];
  TH2F *goodgroup_ref[6];

  TH2F *test[6];

  //Loop over runs
  
  for (int i=0; i<6; i++)
    {

      TString filename = Form("../../ROOTfiles/hms_replay_dc_calib_%d_50000.root", run[i]);                              
      
      //read the file and get the tree                     
      TFile *data_file = new TFile(filename, "READ");                                                     
      TTree *T = (TTree*)data_file->Get("T");
      
      
      //Good Group (Plane 2U1: Wires 49-64)
      
      if (i<5)
	{
	  goodgroup_noref[i] = new TH2F(Form("run_%d_goodgroup_UnCorr", run[i]), Form("Run %d: hDCRef vs. 2u1 Uncorrected Ref. Time: Wire group: 49-64", run[i]), 200, 1000, 6000, 200, 1600, 1800);
	  goodgroup_ref[i] = new TH2F(Form("run_%d_goodgroup_Corr", run[i]), Form("Run %d: hDCRef vs. 2u1 Corrected Ref. Time: Wire group: 49-64", run[i]), 200, -16000, -10000, 200, 1660, 1800);
	  
	  //Draw REF. Uncorrected tdc Time
	  c1->cd(i+1);
	  T->Draw(Form("T.hms.hDCREF1_tdcTime:H.dc.2u1.rawnorefcorrtdc>>run_%d_goodgroup_UnCorr", run[i]), "H.dc.2u1.wirenum>=49&&H.dc.2u1.wirenum<=64", "colz");
	  c2->cd(i+1);
       	  T->Draw(Form("T.hms.hDCREF1_tdcTime:H.dc.2u1.rawtdc>>run_%d_goodgroup_Corr", run[i]), "H.dc.2u1.wirenum>=49&&H.dc.2u1.wirenum<=64", "colz");

	}
      else if (i==5)
	{
	  goodgroup_noref[i] = new TH2F(Form("run_%d_goodgroup_UnCorr", run[i]), Form("Run %d: hDCRef vs. 2u1 Uncorrected Ref. Time: Wire group: 49-64", run[i]), 200, 1000, 6000, 200, 1600, 1800);
	  goodgroup_ref[i] = new TH2F(Form("run_%d_goodgroup_Corr", run[i]), Form("Run %d: hDCRef vs. 2u1 Corrected Ref. Time: Wire group: 49-64", run[i]), 200, -16000, -10000, 200, 1660, 1800);

	  c1->cd(i+1);
	  T->Draw(Form("T.coin.hDCREF1_tdcTime:H.dc.2u1.rawnorefcorrtdc>>run_%d_goodgroup_UnCorr", run[i]), "H.dc.2u1.wirenum>=49&&H.dc.2u1.wirenum<=64", "colz");
	  c2->cd(i+1);
	  T->Draw(Form("T.coin.hDCREF1_tdcTime:H.dc.2u1.rawtdc>>run_%d_goodgroup_Corr", run[i]), "H.dc.2u1.wirenum>=49&&H.dc.2u1.wirenum<=64", "colz");

	}

      

      //Draw Corr. Ref Time 
      //T->Draw("T.hms.hDCREF1_tdcTime:H.dc.1v2.rawtdc>>(200, -14000, -11000, 200, 1740, 1800)", "H.dc.1v2.wirenum>=33&&H.dc.1v2.wirenum<=48", "colz");
      
      //COin. Corr.
      // T->Draw("T.coin.hDCREF1_tdcTime:H.dc.1v2.rawtdc>>(200, -14000, -11000, 200, 1710, 1770)", "H.dc.1v2.wirenum>=33&&H.dc.1v2.wirenum<=48", "colz");
      
      //Coin. UnCorr.
      //T->Draw("T.coin.hDCREF1_tdcTime:H.dc.1v2.rawnorefcorrtdc>>(200, 2000, 5000, 200, 1710, 1770)", "H.dc.1v2.wirenum>=33&&H.dc.1v2.wirenum<=48", "colz");
        
      
    } //END run loop
  
  
  c1->SaveAs("./badgroup2u1_UnCorrREF.pdf");
  c2->SaveAs("./badgroup2u1_CorrREF.pdf");

}

