#include <sys/stat.h>
void testing()
{
  
  Int_t run = 3288;

  mkdir(Form("refTime_cuts_%d", run), S_IRWXU);
  mkdir(Form("refTime_cuts_%d/HMS", run), S_IRWXU);
  mkdir(Form("refTime_cuts_%d/SHMS", run), S_IRWXU);


  /*
  TString base, n_hcal_TdcAdcTimeDiff, n_hcal_AdcMult;
  static const Int_t cal_PLANES = 4;
  static const Int_t dc_PLANES = 12;
  static const Int_t SIDES = 2;
  static const TString cal_side_names[2] = {"goodPos", "goodNeg"};
  static const string cal_pl_names[cal_PLANES] = {"1pr", "2ta", "3ta", "4ta"};
  

  TString filename = "../../../ROOTfiles/coin_replay_timeWin_check_3288_50000.root";
  
  //read ROOTfile and Get TTree
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");

  //HMS Calorimeter
  Double_t hcal_TdcAdcTimeDiff[cal_PLANES][SIDES][13];
  Double_t hcal_AdcMult[cal_PLANES][SIDES][13];
  

  for(int npl=0; npl<4; npl++ )
    {
      for(int iside=0; iside<2; iside++)
	{
	  	  //Loop over HMS calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	      base =  "H.cal." + cal_pl_names[npl];
	      
	      n_hcal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      n_hcal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	      T->SetBranchAddress(n_hcal_TdcAdcTimeDiff, hcal_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(n_hcal_AdcMult, &hcal_AdcMult);
	  
	      //H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("hCal%s%d%s_timeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str() ), Form("HMS Cal %s%d%s AdcTdcTimeDiff", cal_pl_names[npl].c_str(),ipmt+1,nsign[iside].c_str()),hcal_nbins,hcal_xmin,hcal_xmax) ;

	    }
	}
    }
  
  Long64_t nentries = T->GetEntries();
  
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i); 
      
      for(int ipmt=0; ipmt<13; ipmt++)
	{
	  if(hcal_TdcAdcTimeDiff[1][1][ipmt] < 1000)
	    cout <<"ipmt = " << ipmt << " " <<  hcal_TdcAdcTimeDiff[1][1][ipmt] << endl;
	}
      
    }
  
  
 
  */
}
