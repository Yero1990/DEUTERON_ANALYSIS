//Simple code used to check location of the W-peak over all the H(e,e'p) runs taken on Dec-2017/Spring-2018

//---Possible ROOTfile patterns
//coin_replay_heep_check_1719_-1.root 
//hms_coin_replay_heep_check_2058_-1.root
//hms_replay_heep_check_1150_-1.root 
//shms_coin_replay_heep_check_3375_-1.root 
//shms_replay_heep_check_1689_-1.root      


//daq_mode:  coin, singles
//spec_mode: coin, singles
//e-Arm:  hms, shms


void check_elastics(TString daq_mode="", TString spec_mode="", TString eArm="")
{
 

   TObjArray HList(0);

  //ROOTfile name pattern
  TString ROOTFileNamePattern;
  TString filename;

  TFile *data_file;
  TTree *T;


  //Create output root file where histograms will be stored                                                                                                       
  TFile *outROOT = new TFile("./coin_hmsElec_histos.root", "recreate");



  //----------Define Leafs Names/Variables-----------

  //Leaf pre-fixes    
  TString kin_pfx;
  
  //Leaf Names
  TString nW;

  //Leaf Variables
  Double_t W;



  
  //----------Open Run List---------------

  TString lpath;
  ifstream ifs;
  
  if(daq_mode=="coin" && spec_mode=="coin") 
    {
      if(eArm=="shms"){ lpath = "runlists/good_coin_pElec_list.dat", ifs.open(lpath), kin_pfx = "P.kin.primary";}
      else if(eArm=="hms"){ lpath = "runlists/good_coin_hElec_list.dat", ifs.open(lpath), kin_pfx = "H.kin.primary";}
            
      ROOTFileNamePattern = "../../../ROOTfiles/coin_replay_heep_check_%d_-1.root";
    }


  if(daq_mode=="coin" && spec_mode=="singles")
    {

      if(eArm=="shms"){ lpath = "runlists/good_coin_shms_singles_list.dat", ifs.open(lpath), kin_pfx = "P.kin";}
      else if(eArm=="hms"){ lpath = "runlists/good_coin_hms_singles_list.dat", ifs.open(lpath), kin_pfx = "H.kin";}

      ROOTFileNamePattern = "../../../ROOTfiles/"+eArm+"_coin_replay_heep_check_%d_-1.root";       

    }


  if(daq_mode=="singles" && spec_mode=="singles")
    {
     
      if(eArm=="shms"){ lpath = "runlists/good_shms_singles_list.dat", ifs.open(lpath), kin_pfx = "P.kin"; }
      else{ lpath = "runlists/good_hms_singles_list.dat", ifs.open(lpath), kin_pfx = "H.kin"; }
   
      ROOTFileNamePattern = "../../../ROOTfiles/"+eArm+"_replay_heep_check_%d_-1.root";

    }


  //-----------------------------------------


  
  //Define Kinematics Leaf Names
  nW = kin_pfx + ".W";



  
  //-------Read Run List--------
  string line;
  Int_t irun;

 
  Int_t index = 0;
  cout << "DAQ Mode: " << daq_mode << endl;
  cout << "Spec Mode: " << spec_mode << endl;
  cout << "e- Arm: " << eArm << endl;


  //Count total number of runs for Histogram book-keeping
  Int_t RUNS = 0;
  
  while(getline(ifs, line))         
    {               
      RUNS++;
    }

  ifs.close();
  
  // static const Int_t tot_runs = RUNS;
  cout << "total runs = " << RUNS << endl;

  //Create Histograms
  TH1F* hist_W[RUNS];
  
  ifs.open(lpath);
  
  while(getline(ifs, line))
    {
     
      
      irun = stoi(line.c_str());
      cout << "Analyzing Run: " << irun << endl;
      
      
     
      //Create Histograms
      hist_W[index] = new TH1F(Form("histW_Run%d", irun), Form("Run %d: W", irun), 100, 0.7, 1.2);
      HList.Add(hist_W[index]);
      
      //Read ROOTfile
      filename = Form(ROOTFileNamePattern, irun);

      cout << "filename = " << filename << endl;
  
      data_file = new TFile(filename, "READ");
      T = (TTree*)data_file->Get("T");

      
      //Set Branch Address
      T->SetBranchAddress(nW, &W); 

 
      
      //----LOOP OVER ALL EVENTS----
      Long64_t nentries = T->GetEntries();

      for(Long64_t i=0; i< nentries; i++)
	{
	  
	  T->GetEntry(i);
	  
	  if(W>0 && W < 100.){
	    hist_W[index]->Fill(W);
	  }
	  
	}
      //hist_W[index]->Draw();
      //Write Histo to ROOTfile
      //outROOT->cd();
      //hist_W[index]->Write();
      
     
      index ++; //index histogram counter
      
    } //END LOOP OVER RUN LIST


  //Write Histograms to ROOT file                                                                       
                                                                                                                                             
  outROOT->cd();
  HList.Write();    
      
}
