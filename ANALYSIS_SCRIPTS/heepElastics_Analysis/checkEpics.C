#include <stdlib.h>
#include "TMath.h"
void checkEpics(string exp)
{

  /*Brief
    Script to read out EPICS variables event-by-event and take their average. 
    These values are then writte to a csv FILE, so it can be easily plotted by
    a python script.
   */


  gROOT->SetBatch(kTRUE);

  //Mean Variables to determine Avg. Magnet Current
  Double_t hQ1set_sum;
  Double_t hQ2set_sum;
  Double_t hQ3set_sum;
  Double_t hDset_sum;
  Double_t hNMRset_sum;
      
  Double_t hQ1true_sum;
  Double_t hQ2true_sum;
  Double_t hQ3true_sum;
  Double_t hDtrue_sum;
  Double_t hNMRtrue_sum;
  
  Double_t sQ1set_sum;
  Double_t sQ2set_sum;
  Double_t sQ3set_sum;
  Double_t sDset_sum;
  Double_t sHBset_sum;
  
  Double_t sQ1true_sum;
  Double_t sQ2true_sum;
  Double_t sQ3true_sum;
  Double_t sDtrue_sum;
  Double_t sHBtrue_sum;

  

  Int_t hentries, sentries;  //count number of good entries
  
  //Define Magnet Current Leafs to be read from TTree
  
  //HMS Leaf Names
  TString nhQ1_set, nhQ2_set, nhQ3_set, nhD_set, nNMR_set;
  TString nhQ1_true, nhQ2_true, nhQ3_true, nhD_true, nNMR_true;
  
  //SHMS Leaf Names
  TString nsHB_set, nsQ1_set, nsQ2_set, nsQ3_set, nsD_set;
  TString nsHB_true, nsQ1_true, nsQ2_true, nsQ3_true, nsD_true;

  //HMS Leaf Variables
  Double_t hQ1_set, hQ2_set, hQ3_set, hD_set, NMR_set;
  Double_t hQ1_true, hQ2_true, hQ3_true, hD_true, NMR_true;
  
  //SHMS Leaf Variables
  Double_t sHB_set, sQ1_set, sQ2_set, sQ3_set, sD_set;
  Double_t sHB_true, sQ1_true, sQ2_true, sQ3_true, sD_true;

  //Additional EPICS LEAF names and variables;
  Double_t TFE;   //Hall C Tiefenback Energy

  Double_t FRX;    //Fast Raster X (mm)
  Double_t FRY;    //Fast Raster Y (mm)

  Double_t hColl;   //HMS Collimator  (-497...=all_out, -317...=Sieve, -143...=Pion, 0=Home, 488...=Large)  1e7 -->should divide by 1e5 to get 3 digits for easy comparison
  Double_t sColl;   //SHMS Collimator (-315...=Shift_sieve, -114...=Cent_Sieve, 0=Home, 860...=Coll.)      1e7 -->should divide by 1e5 to get 3 digits for easy comparison
  
  Double_t targ;    //Target Encoder Position

  Double_t bpmX;    //Beam Position at Target X
  Double_t bpmY;    //Beam Position at Target Y
 
  /* 
     Target encoder values taken snapshot
Index----Encoder--------Name--------------Divide Encoder by 1e4
     
0       33360185     Loop 1 4  cm          3336
1       29577088     Loop 1 10 cm          2957

2       23827667     Loop 2 10 cm          2382
3       16205625     Loop 3 10 cm          1620

4       11424989     10 cm Dummy + C       1142
5       10807261     10 cm Dummy           1080

6       10059485     4 cm Dummy            1005
7       8498909      Optics 1              849

8       7783645      Optics 2              778
9       6508765      Carbon Hole           650

10      5793501      Carbon 6%             579
11      5078237      Carbon 1.5%           507

12      4362973      Carbon 0.5%           436
13      3647709      10B4C                 364

14      2932445      11B4C                 293
15      2217181      Beryllium             221

16      1501405      Raster/HALO           150
  */


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
  ofstream mycsv;

 
  //Open CSV file
  mycsv.open(Form("%s_EPICS.csv", exp.c_str()), std::ios_base::app);

  if(strcmp(exp.c_str(),"hms")==0)
    {
      //Write Header to CSV File
      mycsv << "Run,Q1_set,Q2_set,Q3_set,D_set,NMR_set" << endl;
    }
    
  if(strcmp(exp.c_str(),"shms")==0)
    {
      //Write Header to CSV File
      mycsv << "Run,HB_set,Q1_set,Q2_set,Q3_set,D_set" << endl;
    }

  if(strcmp(exp.c_str(),"coin")==0)
    {
      //Write Header to CSV File
      mycsv << "Run,hQ1_set,hQ2_set,hQ3_set,hD_set,NMR_set,sHB_set,sQ1_set,sQ2_set,sQ3_set,sD_set" << endl;
    }

  //Read Run List
  ifstream ifs;
  ifs.open(Form("%s_test_list.dat", exp.c_str()));
  string line;
  Int_t irun;
  while(getline(ifs, line))
    {

      irun = stoi(line.c_str());
     
      cout << Form("Analyzing %s Run: ", exp.c_str()) << irun << endl;

      //Reset Sum Counter 
      hQ1set_sum = 0;
      hQ2set_sum = 0;
      hQ3set_sum = 0;
      hDset_sum = 0;
      hNMRset_sum = 0;
      
      hQ1true_sum = 0;
      hQ2true_sum = 0;
      hQ3true_sum = 0;
      hDtrue_sum = 0;
      hNMRtrue_sum = 0;
      
      sQ1set_sum = 0.;
      sQ2set_sum = 0.;
      sQ3set_sum = 0.;
      sDset_sum = 0.;
      sHBset_sum = 0.;
      
      sQ1true_sum = 0.;
      sQ2true_sum = 0.;
      sQ3true_sum = 0.;
      sDtrue_sum = 0.;
      sHBtrue_sum = 0.;

      hentries = 0;
      sentries = 0;

      TString filename = Form("../../../ROOTfiles/%s_replay_scaler_%d_-1.root", exp.c_str(), irun);
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
      	 
      Bool_t hgoodEPICS;
      Bool_t sgoodEPICS;

      //Loop over all entries
      for(Long64_t i=0; i<nentries; i++)
	{

	  T->GetEntry(i);  
	  
	  hgoodEPICS = kFALSE;
	  hgoodEPICS = abs(hQ1_set)<10000&&abs(hQ2_set)<10000&&abs(hQ3_set)<10000&&abs(hD_set)<10000&&abs(NMR_set)<10000;
	  if( hgoodEPICS )
	{
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
	  
	  hentries++;
	  
	    }

	  sgoodEPICS = kFALSE;
	  sgoodEPICS = abs(sQ1_set)<10000&&abs(sQ2_set)<10000&&abs(sQ3_set)<10000&&abs(sHB_set)<10000&&abs(sD_set)<10000;
	  if(sgoodEPICS )
	    {
        
	      sQ1set_sum =  sQ1set_sum + sQ1_set;
	      sQ2set_sum = sQ2set_sum + sQ2_set;
	      sQ3set_sum = sQ3set_sum + sQ3_set;
	      sDset_sum = sDset_sum + sD_set;
	      sHBset_sum = sHBset_sum + sHB_set;
	      
	      sQ1true_sum = sQ1true_sum + sQ1_true;
	      sQ2true_sum = sQ2true_sum + sQ2_true;
	      sQ3true_sum = sQ3true_sum + sQ3_true;
	      sDtrue_sum = sDtrue_sum + sD_true;
	      sHBtrue_sum = sHBtrue_sum +  sHB_true;
	    
	      sentries++;
	     

	    }
	  
	} //end entry loop

 
      if(strcmp(exp.c_str(),"hms")==0)
	{
	  //Write HMS .csv
	  mycsv << irun <<"," << float(hQ1set_sum/hentries) << "," << 
	    float(hQ2set_sum/hentries) << "," << float(hQ3set_sum/hentries) << "," << 
	    float(hDset_sum/hentries) << "," << float(hNMRset_sum/hentries) << endl;
	}

      
      if(strcmp(exp.c_str(),"shms")==0)
	{
	  //Write SHMS .csv
	  mycsv << irun <<"," << float(sHBset_sum/sentries) << "," << 
	    float(sQ1set_sum/sentries) << "," << float(sQ2set_sum/sentries) << "," << 
	    float(sQ3set_sum/sentries) << "," << float(sDset_sum/sentries) << endl;
	}

      if (strcmp(exp.c_str(),"coin")==0)
	{
	  mycsv << irun <<"," << float(hQ1set_sum/hentries) << "," << 
	    float(hQ2set_sum/hentries) << "," << float(hQ3set_sum/hentries) << "," << 
	    float(hDset_sum/hentries) << "," << float(hNMRset_sum/hentries) << "," <<
	    float(sHBset_sum/sentries) << "," << float(sQ1set_sum/sentries) << "," << 
	    float(sQ2set_sum/sentries) << "," << float(sQ3set_sum/sentries) << "," << 
	    float(sDset_sum/sentries) << endl;
	}
      
      
    } //end run WHILE loop
      
       

}
 
