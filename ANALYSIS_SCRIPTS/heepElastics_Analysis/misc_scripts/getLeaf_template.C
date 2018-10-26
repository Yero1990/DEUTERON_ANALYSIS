//Generic code to read and loop through N leafs from a given TTree
//The leafs names are read from a leaf_list.txt file.  For now, they can only be a Double_t (not int or array are yet done)

void getLeaf_template()
{


  //-------Count the NUmber of Leafs in the list-------  
  ifstream myfile;
  myfile.open("leaf_list.txt");
  string line;

  Int_t cnts = -1;  //leaf counter
  //Get Number of leafs
  if(myfile.is_open()){
    while(!myfile.eof()){
      getline(myfile, line);
      if(line[0]=='#') continue;
	cnts++;
    } 
  }
  myfile.close();
  //--------------------------------------------------


  //---------------READ THE LEAFS into a string array----------------------------
  myfile.open("leaf_list.txt");
  //Create arrays
  TString leaf_name[cnts];
  //Make generic leaf variables (assuming it is a Double_t -- later, I should generalize)
  Double_t leaf_var[cnts];

  int index = 0;  //index array 
  //Read leaf list txt file
  while (getline(myfile, line))
    {
      if(line[0]=='#') continue;
      leaf_name[index] = line;
      index++;
    }
  //----------------------------------------------------------------------------


  //-------------CREATE EMPTY HISTOGRAMS---------------------------------------------
  
  //Create empty histogram arrays with the appropiate names based on the leaf you want to Fill
  TH1F *hist[cnts];
 
  hist[0] = new TH1F("h_Xfp", "HMS X_fp", 100, -60, 60);
  hist[1] = new TH1F("h_Yfp", "HMS Y_fp", 100, -60, 60);
  hist[2] = new TH1F("h_beta", "HMS Hodo Beta", 100, 0.6, 1.3);

  //--------------------------------------------------------


  
  //--------------OPEN ROOTfile and Get Tree------------------------
  //Open TFile
  TString filename = "coin_replay_production_1929_10000.root";
  TFile *f1 = new TFile(filename);

  //Get TTree
  TTree *T = (TTree*)f1->Get("T");

  //-----------------------------------------------------------------


  //---------------Set Branch Address ------------------------------
  for (int i=0; i<cnts; i++)
    {
      cout << leaf_name[i] << endl;
      T->SetBranchAddress(leaf_name[i], &leaf_var[i]);
    }

  //---------------------------------------------------------------


  //-----------LOOP OVER ALL ENTRIES IN TREE-----------------------
  //Loop over all entries
  for(int i=0; i<T->GetEntries(); i++){

    T->GetEntry(i);

    //cout << "leaf_var1: " << leaf_var[0] << endl;
    
    //Fill Histograms
    hist[0]->Fill(leaf_var[0]);
    hist[1]->Fill(leaf_var[1]);
    hist[2]->Fill(leaf_var[2]);

  }

  //---------END ENTRY LOOP ---------------------------------------

  //DRaw HIstograms
  hist[2]->Draw();

  
} //end function


