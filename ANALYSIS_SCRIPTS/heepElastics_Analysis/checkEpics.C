#include <stdlib.h>
#include "TMath.h"
void checkEpics(string exp)
{

  /*Brief
    Script to read out EPICS variables event-by-event and take their average. 
    These values are then writte to a csv FILE, so it can be easily plotted by
    a python script.
   */

  //Choose Format to output the data file
  Bool_t csv = kFALSE;
  Bool_t ssv = kTRUE;   //space-separated values (used to put in W.B.'s LT.box format)

  gROOT->SetBatch(kTRUE);

  //Mean Variables to determine Avg. Magnet Current
  Double_t hQ1set_sum, hQ1set_avg;
  Double_t hQ2set_sum, hQ2set_avg;
  Double_t hQ3set_sum, hQ3set_avg;
  Double_t hDset_sum,  hDset_avg;
  Double_t hNMRset_sum, hNMRset_avg;
      
  Double_t hQ1true_sum,  hQ1true_avg;
  Double_t hQ2true_sum,  hQ2true_avg;
  Double_t hQ3true_sum,  hQ3true_avg;
  Double_t hDtrue_sum,   hDtrue_avg;
  Double_t hNMRtrue_sum, hNMRtrue_avg;
  
  Double_t sQ1set_sum, sQ1set_avg;
  Double_t sQ2set_sum, sQ2set_avg;
  Double_t sQ3set_sum, sQ3set_avg;
  Double_t sDset_sum,  sDset_avg;
  Double_t sHBset_sum, sHBset_avg;
  
  Double_t sQ1true_sum, sQ1true_avg;
  Double_t sQ2true_sum, sQ2true_avg;
  Double_t sQ3true_sum, sQ3true_avg;
  Double_t sDtrue_sum,  sDtrue_avg;
  Double_t sHBtrue_sum, sHBtrue_avg;

   
  //Variables to determine Avg. EPICS variables
  Double_t hColl_sum, hColl_avg;
  Double_t sColl_sum, sColl_avg;

  TString hColl_name;
  TString sColl_name;

  Double_t TFE_sum, TFE_avg;
  Double_t FRX_sum, FRX_avg;
  Double_t FRY_sum, FRY_avg;

  Double_t targ_sum, targ_avg;
  TString targ_name;

  Int_t hentries, sentries, good_raster_evt, good_TFE_evt, good_targ_evt, good_hColl_evt, good_sColl_evt;  //count number of good entries
  
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
  TString nTFE;  

  TString nFRX;  
  TString nFRY;   

  TString nhColl; 
  TString nsColl;   
  
  TString ntarg;    


  Double_t TFE;   //Hall C Tiefenback Energy

  Double_t FRX;    //Fast Raster X (mm)
  Double_t FRY;    //Fast Raster Y (mm)

  //all_out --> collimator ladder is completely out of the way, HOME--->Used to calibrate collimator positions (set to 0.0),  Shift_sieve--->shifted hole in sieve slit
  Double_t hColl;   //HMS Collimator  (-497...=all_out, -317...=Sieve, -143...=Pion, 0=Home, 488...=Large)  1e7 -->should divide by 1e5 to get 3 digits for easy comparison
  Double_t sColl;   //SHMS Collimator (-315...=Shift_sieve, -114...=Cent_Sieve, 0=Home, 860...=Coll.)      1e7 -->should divide by 1e5 to get 3 digits for easy comparison
  
  Double_t targ;    //Target Encoder Position

  Double_t targ_mass;   //Target Mass

 
  /* 
     Target encoder values taken snapshot
                                                              Last Dec. 2017 Run
//NOTE: December 2017, (Loop 1--->10 cm H2,  Loop 2---> He4)        HMS: 1277, SHMS: 1705,  COIN: 1722
//      Spring 2018, (Loop 1--->10 cm He4,   Loop 2--->H2)


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


  //LEAF NAMES: Magnet Currents

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


  //Other Important Leafs
  nTFE = "HALLC_p";       //Tiefenback Beam Energy

  nFRX = "EHCFR_LIXWidth";     //Fast Raster - X (mm)
  nFRY = "EHCFR_LIYWidth";     //Fast Raster- Y (mm)

  nhColl = "HCCO_HMS_POSRB";       //HMS collimator
  nsColl = "HCCO_SHMS_POSRB";      //SHMS collimator
  
  ntarg = "hcBDSPOS.VAL";        //Target Encoder

  

  //Create File STreams to store CSV data
  ofstream mycsv;
  ofstream myssv;
  
  //Open CSV file
  if(csv) 
    { 
      mycsv.open(Form("TEST_%s_EPICS.csv", exp.c_str()), std::ios_base::app); 
    }
  

  if(ssv) 
    {  
      myssv.open(Form("TEST_%s_EPICS.data", exp.c_str()), std::ios_base::app); 
    }


  if(strcmp(exp.c_str(),"hms")==0)
    {
      //Write Header to CSV or SSV File
      
      if(csv) {mycsv << "Run,Q1_set,Q2_set,Q3_set,D_set,NMR_set,Collimator,Target,Target_Mass,Raster,TFE,Angle" << endl;}
      if(ssv) {myssv << "#! Run[f,0]/   Q1_set[f,1]/   Q2_set[f,2]/   Q3_set[f,3]/    D_set[f,4]/    NMR_set[f,5]/    Collimator[f,6]/    Target[f,7]/     Target_Mass[f,8]/    Raster[f,9]/   TFE[f,10]/    Angle[f,11]/" << endl;}
    }
    
  if(strcmp(exp.c_str(),"shms")==0)
    {
      //Write Header to CSV File
      if(csv) {mycsv << "Run,HB_set,Q1_set,Q2_set,Q3_set,D_set,Collimator,Target,Target_Mass,Raster,TFE,Angle" << endl;}
      if(ssv) {myssv << "#! Run[f,0]/   Q1_set[f,1]/   Q2_set[f,2]/   Q3_set[f,3]/    D_set[f,4]/    Collimator[f,6]/    Target[f,7]/     Target_Mass[f,8]/    Raster[f,9]/   TFE[f,10]/     Angle[f,11]/" << endl;}

    }

  if(strcmp(exp.c_str(),"coin")==0)
    {
      //Write Header to CSV File
      if(csv) {mycsv << "Run,hQ1_set,hQ2_set,hQ3_set,hD_set,NMR_set,sHB_set,sQ1_set,sQ2_set,sQ3_set,sD_set,hms_Collimator,shms_Collimator,Target,Target_Mass,Raster,TFE,hms_Angle,shms_Angle" << endl;}
      if(ssv) {myssv << "#! Run[f,0]/   hQ1_set[f,1]/   hQ2_set[f,2]/   hQ3_set[f,3]/    hD_set[f,4]/    NMR_set[f,5]/  sHB_set[f,6]/    sQ1_set[f,7]/   sQ2_set[f,8]/   sQ3_set[f,9]/    sD_set[f,10]/   hms_Collimator[f,11]/  shms_Collimator[f,12]/  Target[f,13]/    Target_Mass[f,14]/    Raster[f,15]/   TFE[f,16]/    hms_Angle[f,17]/    shms_Angle[f,18]/" << endl;}

    }

  //Read Run List
  ifstream ifs;
  ifs.open(Form("heep_%s_runlist.dat", exp.c_str()));
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


      hColl_sum = 0;
      sColl_sum = 0;
      
      hColl_avg = 0;
      sColl_avg = 0;
	      

      TFE_sum = 0;
      FRX_sum = 0;
      FRY_sum = 0;
      
      targ_sum = 0;
      
      
      hentries = 0;
      sentries = 0;

      good_raster_evt = 0;
      good_TFE_evt = 0;
      good_targ_evt = 0;
      good_hColl_evt = 0;
      good_sColl_evt = 0;

      TString filename = Form("../../../ROOTfiles/%s_replay_scaler_%d_-1.root", exp.c_str(), irun);
      TFile *data_file = new TFile(filename, "READ"); 
      TTree *T = (TTree*)data_file->Get("T");
      
      //Set Branch Address for Magnet Configuration
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
        
      //Set Branch Address for Other Leafs
      T->SetBranchAddress(nTFE, &TFE);
      T->SetBranchAddress(nFRX, &FRX);
      T->SetBranchAddress(nFRY, &FRY);
      T->SetBranchAddress(nhColl, &hColl);
      T->SetBranchAddress(nsColl, &sColl);
      T->SetBranchAddress(ntarg, &targ);


      
      Long64_t nentries = T->GetEntries();
      	 
      Bool_t hgoodEPICS;
      Bool_t sgoodEPICS;

      //Loop over all entries
      for(Long64_t i=0; i<nentries; i++)
	{

	  T->GetEntry(i);  
	  
	  hgoodEPICS = kFALSE;
	  hgoodEPICS = abs(hQ1_set)<10000&&abs(hQ2_set)<10000&&abs(hQ3_set)<10000&&abs(NMR_set)<10000&&hQ1_set!=0&&hQ2_set!=0&&hQ3_set!=0;
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
	  sgoodEPICS = abs(sQ1_set)<10000&&abs(sQ2_set)<10000&&abs(sQ3_set)<10000&&abs(sHB_set)<10000&&abs(sD_set)<10000&&sQ1_set!=0&&sQ2_set!=0&&sQ3_set!=0&&sD_set>0;
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


	  if(FRX>0 && FRY>0) 
	    {
	      FRX_sum = FRX_sum + FRX;
	      FRY_sum = FRY_sum + FRY;
	      good_raster_evt++;
	    } 

	  if(TFE>0) 
	    {
	      TFE_sum = TFE_sum + TFE;
	      good_TFE_evt++;
	    }
	  
	  if(targ>0) 
	    {
	      targ_sum = targ_sum + targ;
	      good_targ_evt++;
	    }  
	    
	  if(1==1)
	    {
	      //HMS Collimator Setting
	      hColl_sum = hColl_sum + hColl;
	      good_hColl_evt++;
	    }

	  if(1==1)
	    {
	      //SHMS Collimator Setting
	      sColl_sum = sColl_sum + sColl;
	      good_sColl_evt++;
	    }
	    
             


	    
	  
	} //end entry loop
      
      //Determine the averages
      hQ1set_avg = float(hQ1set_sum/hentries);
      hQ2set_avg = float(hQ2set_sum/hentries);
      hQ3set_avg = float(hQ3set_sum/hentries);
      hDset_avg = float(hDset_sum/hentries);
      hNMRset_avg = float(hNMRset_sum/hentries);

      sHBset_avg = float(sHBset_sum/sentries);
      sQ1set_avg = float(sQ1set_sum/sentries);
      sQ2set_avg = float(sQ2set_sum/sentries);
      sQ3set_avg = float(sQ3set_sum/sentries);
      sDset_avg = float(sDset_sum/sentries);
      
      hColl_avg = float(hColl_sum/good_hColl_evt)/1.e5;    
      sColl_avg = float(sColl_sum/good_sColl_evt)/1.e5;

      targ_avg = float(targ_sum/good_targ_evt)/1.e4;

      TFE_avg = float(TFE_sum/good_TFE_evt)/1000.;
      FRX_avg = int(FRX_sum/good_raster_evt);
      FRY_avg = int(FRY_sum/good_raster_evt);
      
      

      //Define Collimator Naming Based on Encoder Position
      if(hColl_avg>300.&&hColl_avg<700) {hColl_name = "Large_Coll";}
      else if (hColl_avg>-700.&&hColl_avg<100.) {hColl_name = "Home";}
      else if (hColl_avg>-1800.&&hColl_avg<-1000.) {hColl_name = "Pion";}
      else if (hColl_avg>-3800.&&hColl_avg<-2700) {hColl_name = "Sieve";}
      else if (hColl_avg>-5300.&&hColl_avg<-4300) {hColl_name = "ALL_OUT";}


      
      if(sColl_avg>300.&&sColl_avg<1200.) {sColl_name = "Coll";}
      else if (sColl_avg>-700.&&sColl_avg<100.) {sColl_name = "Home";}
      else if (sColl_avg>-1500.&&sColl_avg<-900.) {sColl_name = "Centered_Sieve";}
      else if (sColl_avg>-3800.&&sColl_avg<-2700) {sColl_name = "Shifted_Sieve";}

      //Define Target Type Based on Encoder Position
      
      //Only Dec. 2017 Runs
      if((exp=="hms"&&irun<=1277) || (exp=="shms"&&irun<=1705) || (exp=="coin"&&irun<=1722))
	{
	  if (targ_avg>2600.&&targ_avg<3100.){targ_name = "LH2", targ_mass = 1.00794;}
	  else if (targ_avg>2000.&&targ_avg<2500.){targ_name = "LHe4", targ_mass = 4.002602;}
	  
	}                         
      //Post Dec. 2017 Runs, Loop 1: 10 cm LHe4,  Loop 2: 10 cm LH2
      else
	{
	  if (targ_avg>2600.&&targ_avg<3100.){targ_name = "LHe4", targ_mass = 4.002602;}
	  else  if (targ_avg>2000.&&targ_avg<2500.){targ_name = "LH2", targ_mass = 1.00794;}
	}

      
      if(targ_avg>1300&&targ_avg<1900) {targ_name = "LD2", targ_mass = 2.014101;}
      
      if(targ_avg>1105&&targ_avg<1240) {targ_name = "C+Al_Dummy_10cm";}
      
      if(targ_avg>1040&&targ_avg<1100) {targ_name = "Al_Dummy_10cm", targ_mass = 26.98;}  //Al-27

      if(targ_avg>980&&targ_avg<1020) {targ_name = "Al_Dummy_4cm", targ_mass = 26.98;}

      if(targ_avg>800&&targ_avg<920) {targ_name = "Optics-1", targ_mass = 12.0107;}

      if(targ_avg>710&&targ_avg<795) {targ_name = "Optics-2", targ_mass = 12.0107;}

      if(targ_avg>600&&targ_avg<700) {targ_name = "C-Hole", targ_mass = 12.0107;}

      if(targ_avg>550&&targ_avg<595) {targ_name = "Carbon-6%", targ_mass = 12.0107;}

      if(targ_avg>470&&targ_avg<540) {targ_name = "Carbon-1.5%", targ_mass = 12.0107;}

      if(targ_avg>400&&targ_avg<465) {targ_name = "Carbon-0.5%", targ_mass = 12.0107;}

      if(targ_avg>320&&targ_avg<395) {targ_name = "10B4C", targ_mass = 10.0102;}     //^10B_{4}C  , Boron-10 Carbide

      if(targ_avg>260&&targ_avg<315) {targ_name = "11B4C", targ_mass = 11.01;}

      if(targ_avg>190&&targ_avg<250) {targ_name = "Beryllium", targ_mass = 9.012;}

      if(targ_avg>50&&targ_avg<185) {targ_name = "Raster-HALO";}  //?? What is the mass of this? 


      if(strcmp(exp.c_str(),"hms")==0)
	{
	  //Write HMS .csv (or ssv)
	  if(csv){
	  mycsv << irun <<"," << hQ1set_avg << "," << 
	    hQ2set_avg  << "," << hQ3set_avg << "," << 
	    hDset_avg << "," <<  hNMRset_avg << "," << hColl_name << "," << targ_name << "," << targ_mass << "," << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "," << TFE_avg << endl;
	  }
	
	  if(ssv){
	    myssv << irun <<"    " << hQ1set_avg << "    " << 
	      hQ2set_avg  << "    " << hQ3set_avg << "    " << 
	      hDset_avg << "    " <<  hNMRset_avg << "    " << hColl_name << "    " << targ_name << "    " << targ_mass << "    " << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "    " << TFE_avg << endl;
	  }
	  
	}

      
      if(strcmp(exp.c_str(),"shms")==0)
	{
	  //Write SHMS .csv
	  if(csv){
	  mycsv << irun <<"," << sHBset_avg << "," << 
	    sQ1set_avg << "," << sQ2set_avg << "," << 
	    sQ3set_avg << "," << sDset_avg << "," << sColl_name << "," << targ_name << "," << targ_mass << "," << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "," << TFE_avg <<  endl;
	  }
	
	  if(ssv){
	  myssv << irun <<"    " << sHBset_avg << "    " << 
	    sQ1set_avg << "    " << sQ2set_avg << "    " << 
	    sQ3set_avg << "    " << sDset_avg << "    " << sColl_name << "    " << targ_name << "    " << targ_mass << "    " << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "    " << TFE_avg <<  endl;
	  }

	}

      if (strcmp(exp.c_str(),"coin")==0)
	{
	
	  if(csv){
	  mycsv << irun <<"," << hQ1set_avg << "," << 
	    hQ2set_avg << "," << hQ3set_avg << "," <<
	    hDset_avg << "," << hNMRset_avg << "," << 
	    sHBset_avg << "," << sQ1set_avg << "," << 
	    sQ2set_avg << "," << sQ3set_avg << "," << 
	    sDset_avg << "," << hColl_name << "," << 
	    sColl_name << "," << targ_name << "," << targ_mass << "," << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "," << TFE_avg << endl;
	  }
	
	  if(ssv){
	    myssv << irun <<"    " << hQ1set_avg << "    " << 
	      hQ2set_avg << "    " << hQ3set_avg << "    " <<
	      hDset_avg << "    " << hNMRset_avg << "    " << 
	      sHBset_avg << "    " << sQ1set_avg << "    " << 
	      sQ2set_avg << "    " << sQ3set_avg << "    " << 
	      sDset_avg << "    " << hColl_name << "    " << 
	      sColl_name << "    " << targ_name << "    " << targ_mass << "    " << Form("%dx%d",(int)FRX_avg,(int)FRY_avg) << "    " << TFE_avg << endl;
	  }
	  

	}
      
      
    } //end run WHILE loop
      
       

}
 
