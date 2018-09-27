void debug()
{

  TString filename = "../../../../ROOTfiles/coin_replay_scaler_4661_-1.root";
  
  //read the file and get the tree
  TFile *data_file = new TFile(filename, "READ");
  TTree *T = (TTree*)data_file->Get("T");
   

  //Create Histograms
  TH1F *phod1xpos_tdcCounter = new TH1F("phod1xpos_tdcCounter", "SHMS Hodo 1X+ TDC Counter", 140, 0.5, 14.5);
  TH1F *phod1xneg_tdcCounter = new TH1F("phod1xneg_tdcCounter", "SHMS Hodo 1X- TDC Counter", 140, 0.5, 14.5);
  
  TH1F *phod1ypos_tdcCounter = new TH1F("phod1ypos_tdcCounter", "SHMS Hodo 1Y+ TDC Counter", 140, 0.5, 14.5);
  TH1F *phod1yneg_tdcCounter = new TH1F("phod1yneg_tdcCounter", "SHMS Hodo 1Y- TDC Counter", 140, 0.5, 14.5);

  TH1F *phod2xpos_tdcCounter = new TH1F("phod2xpos_tdcCounter", "SHMS Hodo 2X+ TDC Counter", 140, 0.5, 14.5);
  TH1F *phod2xneg_tdcCounter = new TH1F("phod2xneg_tdcCounter", "SHMS Hodo 2X- TDC Counter", 140, 0.5, 14.5);
  
  TH1F *phod2ypos_tdcCounter = new TH1F("phod2ypos_tdcCounter", "SHMS Hodo 2Y+ TDC Counter", 200, 0.5, 21.5);
  TH1F *phod2yneg_tdcCounter = new TH1F("phod2yneg_tdcCounter", "SHMS Hodo 2Y- TDC Counter", 200, 0.5, 21.5);


  TH1F *ptrig1_tdcCounter = new TH1F("ptrig1_tdcCounter", "SHMS pTRIG1 TDC Counter", 500, 0, 5000);


  //Create Histograms to fill with max number of hits per event
  TH1F *phod1xpos_totHits = new TH1F("phod1xpos_totHits", "SHMS Hodo 1X+ Ndata", 40, 0.5, 40.5);
  TH1F *phod1xneg_totHits = new TH1F("phod1xneg_totHits", "SHMS Hodo 1X- Ndata", 40, 0.5, 40.5);
  
  TH1F *phod1ypos_totHits = new TH1F("phod1ypos_totHits", "SHMS Hodo 1Y+ Ndata", 40, 0.5, 40.5);
  TH1F *phod1yneg_totHits = new TH1F("phod1yneg_totHits", "SHMS Hodo 1Y- Ndata", 40, 0.5, 40.5);

  TH1F *phod2xpos_totHits = new TH1F("phod2xpos_totHits", "SHMS Hodo 2X+ Ndata", 40, 0.5, 40.5);
  TH1F *phod2xneg_totHits = new TH1F("phod2xneg_totHits", "SHMS Hodo 2X- Ndata", 40, 0.5, 40.5);
  
  TH1F *phod2ypos_totHits = new TH1F("phod2ypos_totHits", "SHMS Hodo 2Y+ Ndata", 40, 0.5, 40.5);
  TH1F *phod2yneg_totHits = new TH1F("phod2yneg_totHits", "SHMS Hodo 2Y- Ndata", 40, 0.5, 40.5);

  //2D Histos
  TH2F *phod1xpos_adcCorr = new TH2F("phod1xpos_adcCorr", "SHMS Hodo 1X+ ADC Correlation", 140, 0.5, 14.5, 40, 0.5, 40.5);



  //Create Variable Names
  TString N_phod_1xpos_counter="P.hod.1x.posTdcCounter";
  TString N_phod_1xpos_ndata="Ndata.P.hod.1x.posTdcCounter";
  TString N_phod_1xneg_counter="P.hod.1x.negTdcCounter";
  TString N_phod_1xneg_ndata="Ndata.P.hod.1x.negTdcCounter";
     
  TString N_phod_1ypos_counter="P.hod.1y.posTdcCounter";
  TString N_phod_1ypos_ndata="Ndata.P.hod.1y.posTdcCounter";
  TString N_phod_1yneg_counter="P.hod.1y.negTdcCounter";
  TString N_phod_1yneg_ndata="Ndata.P.hod.1y.negTdcCounter";
   
  TString N_phod_2xpos_counter="P.hod.2x.posTdcCounter";
  TString N_phod_2xpos_ndata="Ndata.P.hod.2x.posTdcCounter";
  TString N_phod_2xneg_counter="P.hod.2x.negTdcCounter";
  TString N_phod_2xneg_ndata="Ndata.P.hod.2x.negTdcCounter";
     
  TString N_phod_2ypos_counter="P.hod.2y.posTdcCounter";
  TString N_phod_2ypos_ndata="Ndata.P.hod.2y.posTdcCounter";
  TString N_phod_2yneg_counter="P.hod.2y.negTdcCounter";
  TString N_phod_2yneg_ndata="Ndata.P.hod.2y.negTdcCounter";
   


  TString N_phod_1xpos_Amp="P.hod.1x.posAdcPulseAmp";
  TString N_phod_1xpos_adccounter="P.hod.1x.posAdcCounter";
  TString N_phod_1xpos_pulsetime="P.hod.1x.posAdcPulseTime";
  TString N_phod_1xpos_adcndata="Ndata.P.hod.1x.posAdcCounter";
  TString N_phod_1xpos_Tdctime="P.hod.1x.posTdcTime";


  TString N_ptrig1_tdctime="D.ptrig1_ROC2";
  TString N_ptrig1_ndata="Ndata.D.ptrig1_ROC2";
  
  TString N_ptrig4_tdctime="D.ptrig4_ROC2";
  TString N_ptrig4_ndata="Ndata.D.ptrig4_ROC2";
  

  Double_t phod_1xpos_counter[1000];
  Int_t phod_1xpos_ndata;
 
  Double_t phod_1xneg_counter[1000];
  Int_t phod_1xneg_ndata;

  Double_t phod_1ypos_counter[1000];
  Int_t phod_1ypos_ndata;
 
  Double_t phod_1yneg_counter[1000];
  Int_t phod_1yneg_ndata;

  Double_t phod_2xpos_counter[1000];
  Int_t phod_2xpos_ndata;
 
  Double_t phod_2xneg_counter[1000];
  Int_t phod_2xneg_ndata;

  Double_t phod_2ypos_counter[1000];
  Int_t phod_2ypos_ndata;
 
  Double_t phod_2yneg_counter[1000];
  Int_t phod_2yneg_ndata;


  Double_t ptrig1_tdctime[1000];
  Int_t ptrig1_ndata;

  Double_t ptrig4_tdctime[1000];
  Int_t ptrig4_ndata;	 

  Double_t phod_1xpos_Amp[1000];
  Double_t phod_1xpos_adccounter[1000];
  Double_t phod_1xpos_pulsetime[1000];
  Double_t phod_1xpos_Tdctime[1000];
  Int_t phod_1xpos_adcndata;

  T->SetBranchAddress(N_phod_1xpos_adccounter, &phod_1xpos_adccounter);
  T->SetBranchAddress(N_phod_1xpos_adcndata, &phod_1xpos_adcndata);
  T->SetBranchAddress(N_phod_1xpos_Amp, &phod_1xpos_Amp);
  T->SetBranchAddress(N_phod_1xpos_pulsetime, &phod_1xpos_pulsetime);
  T->SetBranchAddress(N_phod_1xpos_Tdctime, &phod_1xpos_Tdctime);


  T->SetBranchAddress(N_phod_1xpos_counter, &phod_1xpos_counter);
  T->SetBranchAddress(N_phod_1xpos_ndata, &phod_1xpos_ndata);
 
  T->SetBranchAddress(N_phod_1xneg_counter, &phod_1xneg_counter);
  T->SetBranchAddress(N_phod_1xneg_ndata, &phod_1xneg_ndata);

  T->SetBranchAddress(N_phod_1ypos_counter, &phod_1ypos_counter);
  T->SetBranchAddress(N_phod_1ypos_ndata, &phod_1ypos_ndata);

  T->SetBranchAddress(N_phod_1yneg_counter, &phod_1yneg_counter);
  T->SetBranchAddress(N_phod_1yneg_ndata, &phod_1yneg_ndata);

  T->SetBranchAddress(N_phod_2xpos_counter, &phod_2xpos_counter);
  T->SetBranchAddress(N_phod_2xpos_ndata, &phod_2xpos_ndata); 

  T->SetBranchAddress(N_phod_2xneg_counter, &phod_2xneg_counter);
  T->SetBranchAddress(N_phod_2xneg_ndata, &phod_2xneg_ndata);

  T->SetBranchAddress(N_phod_2ypos_counter, &phod_2ypos_counter);
  T->SetBranchAddress(N_phod_2ypos_ndata, &phod_2ypos_ndata);
 
  T->SetBranchAddress(N_phod_2yneg_counter, &phod_2yneg_counter);
  T->SetBranchAddress(N_phod_2yneg_ndata, &phod_2yneg_ndata);



  T->SetBranchAddress(N_ptrig1_tdctime, &ptrig1_tdctime);
  T->SetBranchAddress(N_ptrig1_ndata,  &ptrig1_ndata);

  T->SetBranchAddress(N_ptrig4_tdctime, &ptrig4_tdctime);
  T->SetBranchAddress(N_ptrig4_ndata,  &ptrig4_ndata);

  Int_t hit_counter = 0;

  //-----LOOP OVER ALL EVENTS
  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
     
    
      T->GetEntry(i);  

      if(ptrig1_ndata==2)
	{
	  
	  hit_counter = hit_counter + 1;
	  /*
	  cout << "Event: " << i << endl;
	  cout << "mult 2 hits: " << hit_counter << " ptrig1_tdctime[0] = " <<  ptrig1_tdctime[0] <<" ptrig1_tdctime[1] = " <<  ptrig1_tdctime[1] << endl;

	  cout << "p1x+: " << phod_1xpos_ndata << endl;  //Fill Histograms with these values.
	  cout << "p1x-: " << phod_1xneg_ndata << endl;
	  cout << "p1y+: " << phod_1ypos_ndata << endl;
	  cout << "p1y-: " << phod_1yneg_ndata << endl;
 
	  cout << "p2x+: " << phod_2xpos_ndata << endl;
	  cout << "p2x-: " << phod_2xneg_ndata << endl;
	  cout << "p2y+: " << phod_2ypos_ndata << endl;
	  cout << "p2y-: " << phod_2yneg_ndata << endl;
	  */
	  phod1xpos_totHits->Fill( phod_1xpos_ndata);
	  phod1xneg_totHits->Fill( phod_1xneg_ndata);
	  phod1ypos_totHits->Fill( phod_1ypos_ndata);
	  phod1yneg_totHits->Fill( phod_1yneg_ndata);
	 
	  phod2xpos_totHits->Fill( phod_2xpos_ndata);
	  phod2xneg_totHits->Fill( phod_2xneg_ndata);
	  phod2ypos_totHits->Fill( phod_2ypos_ndata);
	  phod2yneg_totHits->Fill( phod_2yneg_ndata);

	  for (int n=0; n<phod_1xpos_adcndata; n++)
	    {	
	      phod1xpos_adcCorr->Fill(phod_1xpos_adccounter[n], phod_1xpos_ndata);
	      
	    }
	  /*
	  for (int n=0; n<phod_1xpos_adcndata; n++)
	    {	      
	      cout << "Adc Counter = " <<  phod_1xpos_adccounter[n] << "  Adc Amp = " <<  phod_1xpos_Amp[n] << " Adc Pulse Time = " << phod_1xpos_pulsetime[n] << endl;
	    }

	  for (int n=0; n<phod_1xpos_ndata; n++)
	    {

	      cout << "Tdc Counter = " << phod_1xpos_counter[n] << " Tdc Time = " << phod_1xpos_Tdctime[n] << endl; 

	    }
	  */
	}

      /*
      //Loop over all possible pTRIG1 hits per event
      for (int k=0; k<ptrig1_ndata; k++)
	{
	    
	  ptrig1_tdcCounter->Fill(ptrig1_tdctime[k]);
	  
	  

	  //require multiplicity of 2
	  if (ptrig1_tdctime[k]>4000 && k==1)
	    {
	      
	      //cout << "k = " << k << endl;
	      //Loop over all possible hodo hits per event
	      for (int j=0; j<phod_1xpos_ndata; j++) {phod1xpos_tdcCounter->Fill(phod_1xpos_counter[j]); } //end phodo ndata loop
	      for (int j=0; j<phod_1xneg_ndata; j++) {phod1xneg_tdcCounter->Fill(phod_1xneg_counter[j]); } 
	      	     
	      for (int j=0; j<phod_1ypos_ndata; j++) {phod1ypos_tdcCounter->Fill(phod_1ypos_counter[j]); } 
	      for (int j=0; j<phod_1yneg_ndata; j++) {phod1yneg_tdcCounter->Fill(phod_1yneg_counter[j]); } 

	      for (int j=0; j<phod_2xpos_ndata; j++) {phod2xpos_tdcCounter->Fill(phod_2xpos_counter[j]);}
	      for (int j=0; j<phod_2xneg_ndata; j++) {phod2xneg_tdcCounter->Fill(phod_2xneg_counter[j]);}
  
	      for (int j=0; j<phod_2ypos_ndata; j++) {phod2ypos_tdcCounter->Fill(phod_2ypos_counter[j]); } 
	      for (int j=0; j<phod_2yneg_ndata; j++) {phod2yneg_tdcCounter->Fill(phod_2yneg_counter[j]); } 
	      
	    } // end tdctime > 4000 cut

	} //end ptrig ndata loop
      */


      
 

	} //End Entry Loop
  /*
  //Draw Histogram
  TCanvas *c1 = new TCanvas("c1", "", 1000, 500);

  c1->Divide(2,2);

  c1->cd(1);
  phod1xpos_tdcCounter->Draw();
  phod1xneg_tdcCounter->SetLineColor(kRed);
  phod1xneg_tdcCounter->Draw("sames");
  c1->cd(2);
  phod1ypos_tdcCounter->Draw();
  phod1yneg_tdcCounter->SetLineColor(kRed);
  phod1yneg_tdcCounter->Draw("sames");

  c1->cd(3);
  phod2xpos_tdcCounter->Draw();
  phod2xneg_tdcCounter->SetLineColor(kRed);
  phod2xneg_tdcCounter->Draw("sames");
  c1->cd(4);
  phod2ypos_tdcCounter->Draw();
  phod2yneg_tdcCounter->SetLineColor(kRed);
  phod2yneg_tdcCounter->Draw("sames");

  

  //ptrig1_tdcCounter->Draw();

  //Draw Histogram
  TCanvas *c2 = new TCanvas("c2", "", 1000, 500);

  c2->Divide(4,2);
  
  c2->cd(1);
  phod1xpos_totHits->Draw();
  c2->cd(2);
  phod1xneg_totHits->Draw();
  c2->cd(3);
  phod1ypos_totHits->Draw();
  c2->cd(4);
  phod1yneg_totHits->Draw();

  c2->cd(5);
  phod2xpos_totHits->Draw();
  c2->cd(6);
  phod2xneg_totHits->Draw();
  c2->cd(7);
  phod2ypos_totHits->Draw();
  c2->cd(8);
  phod2yneg_totHits->Draw();
  */
  
  phod1xpos_adcCorr->Draw("colz");


}
