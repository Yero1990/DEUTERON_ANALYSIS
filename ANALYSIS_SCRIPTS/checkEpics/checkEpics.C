void checkEpics()
{
  
  gROOT->SetBatch(kTRUE);

  //Mean Variables to determine Avg. Magnet Current
  Double_t hQ1set_sum = 0;
  Double_t hQ2set_sum = 0;
  Double_t hQ3set_sum = 0;
  Double_t hDset_sum = 0;
  Double_t hNMRset_sum = 0;
  
  Double_t hQ1true_sum = 0;
  Double_t hQ2true_sum = 0;
  Double_t hQ3true_sum = 0;
  Double_t hDtrue_sum = 0;
  Double_t hNMRtrue_sum = 0;

  Double_t sQ1set_sum = 0;
  Double_t sQ2set_sum = 0;
  Double_t sQ3set_sum = 0;
  Double_t sDset_sum = 0;
  Double_t sHBset_sum = 0;
  
  Double_t sQ1true_sum = 0;
  Double_t sQ2true_sum = 0;
  Double_t sQ3true_sum = 0;
  Double_t sDtrue_sum = 0;
  Double_t sHBtrue_sum = 0;


  
  
  //Define Magnet Current Leafs to be read from TTree
  
  //HMS
  TString nhQ1_set, nhQ2_set, nhQ3_set, nhD_set, nNMR_set;
  TString nhQ1_true, nhQ2_true, nhQ3_true, nhD_true, nNMR_true;
  //SHMS
  TString nsHB_set, nsQ1_set, nsQ2_set, nsQ3_set, nsD_set;
  TString nsHB_true, nsQ1_true, nsQ2_true, nsQ3_true, nsD_true;

  //HMS
  Double_t hQ1_set, hQ2_set, hQ3_set, hD_set, NMR_set;
  Double_t hQ1_true, hQ2_true, hQ3_true, hD_true, NMR_true;
  //SHMS
  Double_t sHB_set, sQ1_set, sQ2_set, sQ3_set, sD_set;
  Double_t sHB_true, sQ1_true, sQ2_true, sQ3_true, sD_true;

  nhQ1_set = "ecQ1_Set_Current";
  nhQ2_set = "ecQ2_Set_Current";
  nhQ3_set = "ecQ3_Set_Current";
  nhD_set = "ecDI_Set_Current";
  nNMR_set = "ecDI_B_Set_NMR";
  
  nhQ1_true = "ecQ1_I_True";
  nhQ2_true = "ecQ2_I_True";
  nhQ3_true = "ecQ3_I_True";
  nhD_true = "ecDI_I_True";
  nNMR_true = "ecDI_B_True_NMR";
  
  nsHB_set = "ecSHB_Set_Current";
  nsQ1_set = "ecSQ1_Set_Current";
  nsQ2_set = "ecSQ2_Set_Current";
  nsQ3_set = "ecSQ3_Set_Current";
  nsD_set = "ecSDI_Set_Current";

  nsHB_true = "ecSHB_I_True";
  nsQ1_true = "ecSQ1_I_True";
  nsQ2_true = "ecSQ2_I_True";
  nsQ3_true = "ecSQ3_I_True";
  nsD_true = "ecSDI_I_True";

  //Create File STreams to store CSV data
  //HMS
  ofstream mycsv_hset;
  ofstream mycsv_htrue;
  //SHMS
  //ofstream mycsv_sset;
  //ofstream mycsv_strue;

  //Open HMS file
  mycsv_hset.open("HMS_MagnI_set.csv", std::ios_base::app);
  mycsv_htrue.open("HMS_MagnI_true.csv", std::ios_base::app);
  
  //Open SHMS file
  //mycsv_sset.open("SHMS_MagnI_set.csv", std::ios_base::app);
  //mycsv_strue.open("SHMS_MagnI_true.csv", std::ios_base::app);
  
  //Write Header to HMS File
  mycsv_hset << "Run, Q1, Q2, Q3, D, NMR" << endl;
  mycsv_htrue << "Run, Q1, Q2, Q3, D, NMR" << endl;
 
  //Write Header to SHMS File
  //mycsv_sset << "Run, HB, Q1, Q2, Q3, D" << endl;
  //mycsv_strue << "Run, HB, Q1, Q2, Q3, D" << endl;


  //Loop over run Numbers
  for(Int_t irun=1161; irun<=1161; irun++ )
    {

      

      TString filename = Form("../../../ROOTfiles/hms_replay_epics_%d_-1.root", irun);
      TFile *data_file = new TFile(filename, "READ"); 
      TTree *T = (TTree*)data_file->Get("T");
      
      //Set Branch Address for reference times
      //HMS SET
      T->SetBranchAddress(nhQ1_set, &hQ1_set);
      T->SetBranchAddress(nhQ2_set, &hQ2_set);
      T->SetBranchAddress(nhQ3_set, &hQ3_set);
      T->SetBranchAddress(nhD_set, &hD_set);
      T->SetBranchAddress(nNMR_set, &NMR_set);
      
      //HMS TRUE
      T->SetBranchAddress(nhQ1_true, &hQ1_true);
      T->SetBranchAddress(nhQ2_true, &hQ2_true);
      T->SetBranchAddress(nhQ3_true, &hQ3_true);
      T->SetBranchAddress(nhD_true, &hD_true);
      T->SetBranchAddress(nNMR_true, &NMR_true);
      
      //SHMS SET
      T->SetBranchAddress(nsQ1_set, &sQ1_set);
      T->SetBranchAddress(nsQ2_set, &sQ2_set);
      T->SetBranchAddress(nsQ3_set, &sQ3_set);
      T->SetBranchAddress(nsD_set, &sD_set);
      T->SetBranchAddress(nsHB_set, &sHB_set);
      
      //SHMS TRUE
      T->SetBranchAddress(nsQ1_true, &sQ1_true);
      T->SetBranchAddress(nsQ2_true, &sQ2_true);
      T->SetBranchAddress(nsQ3_true, &sQ3_true);
      T->SetBranchAddress(nsD_true, &sD_true);
      T->SetBranchAddress(nsHB_true, &sHB_true);
      
      
      Long64_t nentries = T->GetEntries();
      
      //Loop over all entries
      for(Long64_t i=0; i<nentries; i++)
	{
	  
	  T->GetEntry(i);  
	  
	  //Sum over all epics reads for each magent current settings/readback values
	  hQ1set_sum = hQ1set_sum + hQ1_set;
	  hQ2set_sum = hQ2set_sum + hQ2_set;
	  hQ3set_sum = hQ3set_sum + hQ3_set;
	  hDset_sum =  hDset_sum + hD_set;
	  hNMRset_sum = hNMRset_sum + NMR_set;
	  
	  hQ1true_sum = hQ1true_sum + hQ1_true;
	  hQ2true_sum = hQ2true_sum + hQ2_true;
	  hQ3true_sum = hQ3true_sum + hQ3_true;
	  hDtrue_sum = hDtrue_sum + hD_true;
	  hNMRtrue_sum = hNMRtrue_sum + NMR_true;
	  
	  sQ1set_sum =  sQ1set_sum + sQ1_set;
	  sQ2set_sum = sQ2set_sum + sQ2_set;
	  sQ3set_sum = sQ3set_sum + sQ3_set;
	  sDset_sum = sDset_sum + sD_set;
	  sHBset_sum = sHBset_sum +  sHB_set;
	  
	  sQ1true_sum = sQ1true_sum + sQ1_true;
	  sQ2true_sum = sQ2true_sum + sQ2_true;
	  sQ3true_sum = sQ3true_sum + sQ3_true;
	  sDtrue_sum = sDtrue_sum + sD_true;
	  sHBtrue_sum = sHBtrue_sum +  sHB_true;
	  
	  
	} //end entry loop
      
      mycsv_hset << irun <<", " << float(hQ1set_sum/nentries) << ", " << float(hQ2set_sum/nentries) << ", " << float(hQ3set_sum/nentries) << ", " << float(hDset_sum/nentries) << ", " << float(hNMRset_sum/nentries) << endl;
      mycsv_htrue << irun <<", " << float(hQ1true_sum/nentries) << ", " << float(hQ2true_sum/nentries) << ", " << float(hQ3true_sum/nentries) << ", " << float(hDtrue_sum/nentries) << ", " << float(hNMRtrue_sum/nentries) << endl;
      
      //Write SHMS .csv
      // mycsv_sset << irun <<", " << float(sHBset_sum) << ", " << float(sQ1set_sum/nentries) << ", " << float(sQ2set_sum/nentries) << ", " << float(sQ3set_sum/nentries) << ", " << float(sDset_sum/nentries) << endl;
      //mycsv_strue << irun <<", " << float(sHBtrue_sum) << ", " << float(sQ1true_sum/nentries) << ", " << float(sQ2true_sum/nentries) << ", " << float(sQ3true_sum/nentries) << ", " << float(sDtrue_sum/nentries) << endl;

    } //end run loop
      
      
    }
 
