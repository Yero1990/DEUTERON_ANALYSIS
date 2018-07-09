void setTimeWindows()
{

  gROOT->SetBatch(kTRUE);
  Int_t runNUM = 1267;
  
  TString filename = "../../ROOTfiles/hms_replay_dc_calib_1267_2000000_DCUnCalib.root";
  
  TFile *data_file = new TFile(filename, "READ"); 
  TTree *T = (TTree*)data_file->Get("T");
  
  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("hms_histos%d.root", runNUM), "recreate");


  /**************IMPORTANT ! ! ! ****************/

  //Define and set ref. time cuts 
  //(See /PARAM/HMS/GEN/h_reftime_cut.param)
  Double_t hod_trefcut = 1250.;
  Double_t dc_trefcut = 14800.;
  Double_t adc_trefcut = 2640.;  

  /********************************************/

  //Set ADC:TDC Time Diff. Histogram Bins
  Double_t hod_nbins, hod_xmin, hod_xmax;
  Double_t dc_nbins, dc_xmin, dc_xmax;
  Double_t cer_nbins, cer_xmin, cer_xmax;                                                                                              
  Double_t cal_nbins, cal_xmin, cal_xmax;                                                                                                                    

  /**************************************IMPORTANT ! ! ! *************************************************/

  //---------- Define and set Multiple of Sigma to place cuts (Mean +/- nSig*sig) around ADC:TDC Time Diff HERE ! ! !------
  Double_t hod_nSig = 6.0;
  Double_t dc_nSig = 5.5;
  Double_t cer_nSig = 3.5;
  Double_t cal_nSig = 4.0;

  //---------MODIFY HISTOGRAM BINNING HERE!!!-----------------
  hod_nbins = 50;
  hod_xmin = -70;
  hod_xmax = -40;

  dc_nbins = 500;                                                                                                                                         
  dc_xmin = -20000;                                                                                                                                      
  dc_xmax = -5000;   

  cer_nbins = 200;                                                                                                                                     
  cer_xmin = 50;                                                                                                                                       
  cer_xmax = 150;                                                                                                                     

  cal_nbins = 200;                                                                                                                                            
  cal_xmin = -140;                                                                                                                          
  cal_xmax = -60;                                                                                                                                    
 

  /******************************************************************************************************/


  /******Define Fixed Quantities********/
  static const Int_t PLANES = 4;
  static const Int_t SIDES = 2;
  TString spec = "H";
  string hod_pl_names[4] = {"1x", "1y", "2x", "2y"};
  string cal_pl_names[4] = {"1pr", "2ta", "3ta", "4ta"};
  string dc_pl_names[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  
  string side_names[2] = {"GoodPos", "GoodNeg"};
  string cal_side_names[2] = {"goodPos", "goodNeg"};
  
  string nsign[2] = {"+", "-"};
  Int_t maxPMT[4] = {16, 10, 16, 10};
  
  //Define Canvas
  TCanvas *hodoCanv[PLANES][SIDES];
  TCanvas *caloCanv[PLANES][SIDES];
  TCanvas *dcCanv;
  TCanvas *hCer_Canv;

  TCanvas *hms_REF_Canv;     //canvas to save reference time histograms

  //Define Histograms
  TH1F *H_hod_TdcAdcTimeDiff[PLANES][SIDES][16];
  TH1F *H_cal_TdcAdcTimeDiff[PLANES][SIDES][13];
  TH1F *H_dc_rawTDC[12];
  TH1F *H_cer_TdcAdcTimeDiff[2];

  //Reference time histograms
  TH1F *H_hodo_Tref = new TH1F("hodoTref", "Hodoscope hT1 TDC Raw Time", 300, 1200, 1800);                                                                            
  TH1F *H_DC_Tref1 = new TH1F("DCTref1", "DC REF TDC Raw Times", 300, 14600, 15200);                                                                                      
  TH1F *H_DC_Tref2 = new TH1F("DCTref2", "DC REF TDC Raw Times", 300, 14600, 15200);                                                                                       
  TH1F *H_DC_Tref3 = new TH1F("DCTref3", "DC REF TDC Raw Times", 300, 14600, 15200);                                                                                       
  TH1F *H_DC_Tref4 = new TH1F("DCTref4", "DC REF TDC Raw Times", 300, 14600, 15200);                                                                                      
  TH1F *H_hFADC_Tref = new TH1F("hFADC_Tref", "FADC REF adcPulseTimeRaw", 70, 2600, 2740); 

  //Define Arrays to store Min/Max Time Window Cuts
  Double_t hodo_tWinMin[4][2][16] = {0.};
  Double_t hodo_tWinMax[4][2][16] = {0.};

  Double_t hCal_tWinMin[4][2][13] = {0.};
  Double_t hCal_tWinMax[4][2][13] = {0.};

  Double_t hCer_tWinMin[2] = {0.};
  Double_t hCer_tWinMax[2] = {0.};

  Double_t hDC_tWinMin[12] = {0.};
  Double_t hDC_tWinMax[12] = {0.};

  //Mean and Sigma. Variables to determine TimeWindow Cut Region
  Double_t mean; 
  Double_t sig;
  

  //Define TLines to draw aroud Cut Region
  TLine *hod_LineMin[PLANES][SIDES][16];
  TLine *hod_LineMax[PLANES][SIDES][16];

  TLine *cal_LineMin[PLANES][SIDES][13];
  TLine *cal_LineMax[PLANES][SIDES][13];
  
  TLine *dc_LineMin[12];
  TLine *dc_LineMax[12];

  TLine *hCER_LineMin[2];
  TLine *hCER_LineMax[2];

  //Reference Time TLines
  TLine *hT1_Line;      //hms trigger ref. time
  TLine *hDCREF1_Line;  //hms DC ref. time
  TLine *hFADC_Line;    //flash ADC ref. time


  //Define Hodo Leafs to be read from TTree
  //---Names---
  TString base;
  TString nhod_TdcAdcTimeDiff;
  TString nhod_AdcMult;

  TString ncal_TdcAdcTimeDiff;
  TString ncal_AdcMult;

  TString ncer_TdcAdcTimeDiff;
  TString ncer_AdcMult;

  TString nndata_rawTDC;
  TString ndc_rawTDC;

  //Ref. Time Names
  TString n_hT1_ref = "T.hms.hT1_tdcTimeRaw";
  TString n_hDC_ref1 = "T.hms.hDCREF1_tdcTimeRaw";
  TString n_hDC_ref2 = "T.hms.hDCREF2_tdcTimeRaw";                                                                                                                           
  TString n_hDC_ref3 = "T.hms.hDCREF3_tdcTimeRaw";                                                                                                                   
  TString n_hDC_ref4 = "T.hms.hDCREF4_tdcTimeRaw";                                                                                                          
  TString n_hFADC_ref = "T.hms.hFADC_TREF_ROC1_adcPulseTimeRaw";
    

  //---Variables---
  Double_t hod_TdcAdcTimeDiff[PLANES][SIDES][16];
  Double_t hod_AdcMult[PLANES][SIDES][16];

  Double_t cal_TdcAdcTimeDiff[PLANES][SIDES][13];
  Double_t cal_AdcMult[PLANES][SIDES][13];

  Double_t cer_TdcAdcTimeDiff[2];
  Double_t cer_AdcMult[2];

  Double_t dc_rawTDC[12][1000];
  Int_t ndata_rawTDC[12];

  //Ref. Time Varables                                                                                                                                           
  Double_t hT1_ref;                                                                                                    
  Double_t hDC_ref1;
  Double_t hDC_ref2;                                                                                                                                                        
  Double_t hDC_ref3;
  Double_t hDC_ref4;                                                                                      
  Double_t hFADC_ref;

  //Set Branch Address for reference times
  T->SetBranchAddress(n_hT1_ref, &hT1_ref);
  T->SetBranchAddress(n_hDC_ref1, &hDC_ref1);                                                                                                                   
  T->SetBranchAddress(n_hDC_ref2, &hDC_ref2);
  T->SetBranchAddress(n_hDC_ref3, &hDC_ref3);
  T->SetBranchAddress(n_hDC_ref4, &hDC_ref4);
  T->SetBranchAddress(n_hFADC_ref, &hFADC_ref);

  //Loop over Cherenkov PMTs
  for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
    {
      //Initialize Histograms
      H_cer_TdcAdcTimeDiff[ipmt] = new TH1F(Form("hCer TDC:ADC Time Diff, PMT_%d", ipmt), Form("hCer TDC:ADC Time Diff, PMT_%d", ipmt ), cer_nbins, cer_xmin, cer_xmax);
      H_cer_TdcAdcTimeDiff[ipmt]->GetXaxis()->SetTitle("(TDC-ADC) Time Difference (ns) ");
      H_cer_TdcAdcTimeDiff[ipmt]->GetXaxis()->CenterTitle();
      H_cer_TdcAdcTimeDiff[ipmt]->GetYaxis()->SetTitle("Counts");
      H_cer_TdcAdcTimeDiff[ipmt]->GetYaxis()->CenterTitle();

      //----Define TTree Leaf Names-----
      base = spec + ".cer.";
      ncer_TdcAdcTimeDiff = base  + "goodAdcTdcDiffTime";
      ncer_AdcMult = base + "goodAdcMult";
      
      //------Set Branch Address-------
      T->SetBranchAddress(ncer_TdcAdcTimeDiff,  &cer_TdcAdcTimeDiff);
      T->SetBranchAddress(ncer_AdcMult,  &cer_AdcMult);

    }


  //Loop over drift chamber planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
      //Initialize Histograms
      H_dc_rawTDC[npl] = new TH1F(Form("DC Raw TDC Time, %s", dc_pl_names[npl].c_str()), Form("DC Raw TDC Time, %s", dc_pl_names[npl].c_str()), dc_nbins, dc_xmin, dc_xmax);
      H_dc_rawTDC[npl]->GetXaxis()->SetTitle("Raw TDC Time (Channels) ");
      H_dc_rawTDC[npl]->GetXaxis()->CenterTitle();
      H_dc_rawTDC[npl]->GetYaxis()->SetTitle("Counts");
      H_dc_rawTDC[npl]->GetYaxis()->CenterTitle();
      
      //----Define TTree Leaf Names-----
      base = spec + ".dc." + dc_pl_names[npl];
      ndc_rawTDC = base + "." + "rawtdc";
      nndata_rawTDC = "Ndata." + ndc_rawTDC;

      //------Set Branch Address-------
      T->SetBranchAddress(ndc_rawTDC,  dc_rawTDC[npl]);
      T->SetBranchAddress(nndata_rawTDC, &ndata_rawTDC[npl]);
    }
  
  //Loop over hodo/calorimeter planes
  for (Int_t npl = 0; npl < PLANES; npl++ )
    {
      
      //Loop over hodo/calorimeter sides
      for (Int_t iside = 0; iside < SIDES; iside++)
	{
	    
	  //Loop over hodo PMTs
	  for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
	    {

	      //Initialize Histograms
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("Good TDC:ADC Time Diff, %s%d%s", hod_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), Form("Good ADC:TDC Time Difference, %s%d%s", hod_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), hod_nbins, hod_xmin, hod_xmax);
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good (TDC-ADC) Time Difference (ns) ");
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitle("Counts");
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->CenterTitle();
	            

	      //----Define TTree Leaf Names-----
	      base = spec + ".hod." + hod_pl_names[npl];
	             
	      nhod_TdcAdcTimeDiff = base + "." + side_names[iside] + "AdcTdcDiffTime";
	      nhod_AdcMult = base + "." + side_names[iside] + "AdcMult";

	             
	      //------Set Branch Address-------
	      T->SetBranchAddress(nhod_TdcAdcTimeDiff,  &hod_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(nhod_AdcMult,  &hod_AdcMult[npl][iside]);
	        
	             
	    }

	  //Loop over calorimeter PMTs
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {
	            
	      //Initialize Histograms
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt] = new TH1F(Form("Good TDC:ADC Time Diff, %s%d%s", cal_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), Form("Good ADC:TDC Time Difference, %s%d%s", cal_pl_names[npl].c_str(), ipmt+1, side_names[iside].c_str()), cal_nbins, cal_xmin, cal_xmax);
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->SetTitle("Good (TDC-ADC) Time Difference (ns) ");
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetXaxis()->CenterTitle();
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->SetTitle("Counts");
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetYaxis()->CenterTitle();

	      //----Define TTree Leaf Names-----
	      base = spec + ".cal." + cal_pl_names[npl];
	             
	      ncal_TdcAdcTimeDiff = base + "." + cal_side_names[iside] + "AdcTdcDiffTime";
	      ncal_AdcMult = base + "." + cal_side_names[iside] + "AdcMult";

	             
	      //------Set Branch Address-------
	      T->SetBranchAddress(ncal_TdcAdcTimeDiff,  &cal_TdcAdcTimeDiff[npl][iside]);
	      T->SetBranchAddress(ncal_AdcMult,  &cal_AdcMult[npl][iside]);
	       
	    }
	    
	} //End side loop

    } //End plane loop

  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {

      T->GetEntry(i);  
      
      //Fill Reference Time Histograms
      H_hodo_Tref->Fill(hT1_ref);
      H_DC_Tref1->Fill(hDC_ref1);
      H_DC_Tref2->Fill(hDC_ref2);
      H_DC_Tref3->Fill(hDC_ref3);
      H_DC_Tref4->Fill(hDC_ref4);
      H_hFADC_Tref->Fill(hFADC_ref);
                                        
      //Loop over hCer pmts
      for (Int_t ipmt = 0; ipmt < 2; ipmt++)
	{                                                                                                                                             

	  //Require ADC Multiplicity == 1
	  if (cer_AdcMult[ipmt]>=1&&abs(cer_TdcAdcTimeDiff[ipmt])<1000)
	    {
	     
	      H_cer_TdcAdcTimeDiff[ipmt]->Fill(cer_TdcAdcTimeDiff[ipmt]);
	      
	    }
	}
      
      //Loop over dc  planes

      for (Int_t npl = 0; npl < 12; npl++ )
	{
	  for(Int_t j = 0; j < ndata_rawTDC[npl]; j++)
	    {
	      
	    H_dc_rawTDC[npl]->Fill(dc_rawTDC[npl][j]);
	    
	    }
	}
      
      
      //Loop over hodo/calorimeter planes
      for (Int_t npl = 0; npl < PLANES; npl++ )
	{
	    
	  //Loop over hodo/calorimeter side
	  for (Int_t iside = 0; iside < SIDES; iside++)
	    {

	      //Loop over Calorimeter PMTs
	      for (Int_t ipmt = 0; ipmt < 13; ipmt++)
		{
		    
		  if(cal_AdcMult[npl][iside][ipmt]>=1)
		  {
		    H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Fill(cal_TdcAdcTimeDiff[npl][iside][ipmt]);
		  }
		    
		} //end calo PMT loop
	            
	      //Loop over hodo PMTs
	      for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
		{
		  //Require ADC Multiplicity == 1
		  if(hod_AdcMult[npl][iside][ipmt]>=1)
		    {
		      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Fill(hod_TdcAdcTimeDiff[npl][iside][ipmt]);
		    }
		        
		} //end hodo PMT loop
	            
	    } // end side loop

	} //end plane loop
      
    } //end entry loop

                                                                                                                      
                                                                
  /***********DRAW HISTOGRAMS TO CANVAS***************/
  
  //Reference Time Histograms
  hms_REF_Canv = new TCanvas("REF Times", "HMS REF TIMES",  1000, 500);
  hms_REF_Canv->Divide(3,1);
  
  hT1_Line = new TLine(hod_trefcut, 0,  hod_trefcut, H_hodo_Tref->GetMaximum());
  hDCREF1_Line = new TLine(dc_trefcut, 0,  dc_trefcut, H_DC_Tref1->GetMaximum());
  hFADC_Line = new TLine(adc_trefcut, 0,  adc_trefcut, H_hFADC_Tref->GetMaximum());
  
  hms_REF_Canv->cd(1);
  gPad->SetLogy();
  H_hodo_Tref->Draw();
  hT1_Line->SetLineColor(kRed);
  hT1_Line->SetLineWidth(3);
  hT1_Line->Draw();
 
  hms_REF_Canv->cd(2);
  gPad->SetLogy();
  H_DC_Tref1->SetLineColor(kBlack);
  H_DC_Tref1->Draw();
  hDCREF1_Line->SetLineColor(kRed);
  hDCREF1_Line->SetLineWidth(3);
  hDCREF1_Line->Draw();

  hms_REF_Canv->cd(3);
  gPad->SetLogy();
  H_hFADC_Tref->Draw();
  hFADC_Line->SetLineColor(kRed);
  hFADC_Line->SetLineWidth(3);
  hFADC_Line->Draw();
  hms_REF_Canv->SaveAs("hms_REFTime_cuts.pdf");
  //---------------------------------------------------

  dcCanv = new TCanvas("DC Raw Times", "DC Raw Time", 1500, 500);
  dcCanv->Divide(6,2);
  
  //Loop over DC planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
     
      //Get Mean ans Sigma
      mean =  H_dc_rawTDC[npl]->GetMean();
      sig  = H_dc_rawTDC[npl]->GetStdDev();
    
      //Set Time Window Cuts
      hDC_tWinMin[npl] = mean - dc_nSig*sig;
      hDC_tWinMax[npl] = mean + dc_nSig*sig;
      
      dc_LineMin[npl] = new TLine(hDC_tWinMin[npl], 0, hDC_tWinMin[npl], H_dc_rawTDC[npl]->GetMaximum());
      dc_LineMax[npl] = new TLine(hDC_tWinMax[npl], 0, hDC_tWinMax[npl], H_dc_rawTDC[npl]->GetMaximum());

      dc_LineMin[npl]->SetLineColor(kRed);
      dc_LineMax[npl]->SetLineColor(kRed);
      
      dcCanv->cd(npl+1);
      //gPad->SetLogy();
      H_dc_rawTDC[npl]->Draw();
      dc_LineMin[npl]->Draw();
      dc_LineMax[npl]->Draw();
      
    }
  

  hCer_Canv = new TCanvas("hCer_ADC:TDC Time Diff", "DC Raw Time", 1500, 500);
  hCer_Canv->Divide(2,1);

  //Loop over hCer PMTs
  for (Int_t ipmt = 0; ipmt < 2; ipmt++ )
    {
      //Get Mean and Sigma
      mean = H_cer_TdcAdcTimeDiff[ipmt]->GetMean();
      sig = H_cer_TdcAdcTimeDiff[ipmt]->GetStdDev();

    
      //Set Time Window Cuts
      hCer_tWinMin[ipmt] = mean - cer_nSig*sig;
      hCer_tWinMax[ipmt] = mean + cer_nSig*sig;
      
      //Set Min/Max Line Limits
      hCER_LineMin[ipmt] = new TLine(hCer_tWinMin[ipmt], 0, hCer_tWinMin[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
      hCER_LineMax[ipmt] = new TLine(hCer_tWinMax[ipmt], 0, hCer_tWinMax[ipmt], H_cer_TdcAdcTimeDiff[ipmt]->GetMaximum());
                                  
      hCER_LineMin[ipmt]->SetLineColor(kRed);
      hCER_LineMax[ipmt]->SetLineColor(kRed);
         
      hCer_Canv->cd(ipmt+1);
      gPad->SetLogy();
      H_cer_TdcAdcTimeDiff[ipmt]->Draw();
      hCER_LineMin[ipmt]->Draw();
      hCER_LineMax[ipmt]->Draw();
    
    }

  
   
  //Loop over hodo/calo planes
  for (Int_t npl = 0; npl < PLANES; npl++ )
    {      

      //Loop over plane side
      for (Int_t iside = 0; iside < SIDES; iside++)
	{  

	  hodoCanv[npl][iside] = new TCanvas(Form("hodo_TDC:ADC Time Diff. Hod Plane %s%s", hod_pl_names[npl].c_str(), side_names[iside].c_str()), Form("Hodo TDC:ADC Time Diff, Plane %s", hod_pl_names[npl].c_str()),  1500, 600);

	  if (!(npl==2&&iside==1) || !(npl==3&&iside==1)){
	    caloCanv[npl][iside] = new TCanvas(Form("calo_TDC:ADC Time Diff. Cal Plane %s%s", cal_pl_names[npl].c_str(), side_names[iside].c_str()), Form("Calo TDC:ADC Time Diff, Plane %s", cal_pl_names[npl].c_str()),  1500, 600);
	    caloCanv[npl][iside]->Divide(5,3);
	  }
	    
	  //Divide Hodo Canvas Accordingly
	  if(npl == 0 || npl == 2)
	    {
	      hodoCanv[npl][iside]->Divide(4,4);
	    }
	    
	  else if (npl==1 || npl==3)
	    {
	      hodoCanv[npl][iside]->Divide(5,2);
	    }
	    
	  //Loop over pmt
	  for (Int_t ipmt = 0; ipmt < maxPMT[npl]; ipmt++)
	    {

	      //Get Mean and Sigma
	      mean = H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hodo_tWinMin[npl][iside][ipmt] = mean - hod_nSig*sig;
	      hodo_tWinMax[npl][iside][ipmt] = mean + hod_nSig*sig;

	            
	      //Set Min/Max Line Limits
	      hod_LineMin[npl][iside][ipmt] = new TLine(hodo_tWinMin[npl][iside][ipmt], 0, hodo_tWinMin[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      hod_LineMax[npl][iside][ipmt] = new TLine(hodo_tWinMax[npl][iside][ipmt], 0, hodo_tWinMax[npl][iside][ipmt], H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      hod_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      hod_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      hodoCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_hod_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      hod_LineMin[npl][iside][ipmt]->Draw();
	      hod_LineMax[npl][iside][ipmt]->Draw();
	    } //end pmt loop

	  //Loop over Calorimeter pmts
	  for (Int_t ipmt = 0; ipmt < 13; ipmt++)
	    {

	      //Get Mean and Sigma
	      mean = H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMean();
	      sig =  H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetStdDev();

	      //Set Time Window Cuts
	      hCal_tWinMin[npl][iside][ipmt] = mean - cal_nSig*sig;
	      hCal_tWinMax[npl][iside][ipmt] = mean + cal_nSig*sig;                                                                                                          
	      
	      //Set Min/Max Line Limits
	      cal_LineMin[npl][iside][ipmt] = new TLine(hCal_tWinMin[npl][iside][ipmt], 0, hCal_tWinMin[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());
	      cal_LineMax[npl][iside][ipmt] = new TLine(hCal_tWinMax[npl][iside][ipmt], 0, hCal_tWinMax[npl][iside][ipmt], H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->GetMaximum());

	      cal_LineMin[npl][iside][ipmt]->SetLineColor(kRed);
	      cal_LineMax[npl][iside][ipmt]->SetLineColor(kRed);

	      caloCanv[npl][iside]->cd(ipmt+1);
	      gPad->SetLogy();
	      H_cal_TdcAdcTimeDiff[npl][iside][ipmt]->Draw();
	      cal_LineMin[npl][iside][ipmt]->Draw();
	      cal_LineMax[npl][iside][ipmt]->Draw();

	    } //end pmt loop
	    
	    
	  hodoCanv[npl][iside]->SaveAs(Form("Hodo_%s%s.pdf", hod_pl_names[npl].c_str(), side_names[iside].c_str()));
	  

	  if ((npl==2&&iside==1) || (npl==3&&iside==1)) continue;
	  caloCanv[npl][iside]->SaveAs(Form("Calo_%s%s.pdf", cal_pl_names[npl].c_str(), side_names[iside].c_str()));
	    

	} //end side loop
      
      
    } //end plane loop
  
  dcCanv->SaveAs("hDC_RawTime.pdf");
  hCer_Canv->SaveAs("hCer_TimeCuts.pdf");
 
  //Write Histograms to ROOT file
  outROOT->Write();
  outROOT->Close();

  
 
  //------------Write Time Window Min/Max Limits to Parameter File---------------
  ofstream outPARAM;
  outPARAM.open(Form("../PARAM/HMS/HODO/hhodo_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hhodo_tWin_%d.param", runNUM));
  outPARAM << "; HMS Hodoscope Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "; " << setw(32) << "1x " << setw(19) << "1y " << setw(16) << "2x " << setw(16) << "2y " << endl;
  outPARAM << "hhodo_PosAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMin[0][0][ipmt] << ", " << setw(15) << hodo_tWinMin[1][0][ipmt] << ", " << setw(15) << hodo_tWinMin[2][0][ipmt] << ", " << setw(15) << hodo_tWinMin[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMin[0][0][ipmt] << ", " << setw(15) << hodo_tWinMin[1][0][ipmt] << ", " << setw(15) << hodo_tWinMin[2][0][ipmt] << ", " << setw(15) << hodo_tWinMin[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_PosAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMax[0][0][ipmt] << ", " << setw(15) << hodo_tWinMax[1][0][ipmt] << ", " << setw(15) << hodo_tWinMax[2][0][ipmt] << ", " << setw(15) << hodo_tWinMax[3][0][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMax[0][0][ipmt] << ", " << setw(15) << hodo_tWinMax[1][0][ipmt] << ", " << setw(15) << hodo_tWinMax[2][0][ipmt] << ", " << setw(15) << hodo_tWinMax[3][0][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMin = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
      outPARAM << setprecision(2) << hodo_tWinMin[0][1][ipmt] << ", " << setw(15) << hodo_tWinMin[1][1][ipmt] << ", " << setw(15) << hodo_tWinMin[2][1][ipmt] << ", " << setw(15) << hodo_tWinMin[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMin[0][1][ipmt] << ", " << setw(15) << hodo_tWinMin[1][1][ipmt] << ", " << setw(15) << hodo_tWinMin[2][1][ipmt] << ", " << setw(15) << hodo_tWinMin[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hhodo_NegAdcTimeWindowMax = ";
  
  //--------Write Parameters to Param File-----
  for (Int_t ipmt = 0; ipmt < 16; ipmt++){
    if (ipmt==0){
     outPARAM << setprecision(2) << hodo_tWinMax[0][1][ipmt] << ", " << setw(15) << hodo_tWinMax[1][1][ipmt] << ", " << setw(15) << hodo_tWinMax[2][1][ipmt] << ", " << setw(15) << hodo_tWinMax[3][1][ipmt] << fixed << endl; 
    }
    else{
      outPARAM << setw(36) <<  setprecision(2) << hodo_tWinMax[0][1][ipmt] << ", " << setw(15) << hodo_tWinMax[1][1][ipmt] << ", " << setw(15) << hodo_tWinMax[2][1][ipmt] << ", " << setw(15) << hodo_tWinMax[3][1][ipmt] << fixed << endl; 
    }
  } //end pmt loop
  
  outPARAM.close();

  //---------------------WRITE CALORIMETER TIME WINDOW CUTS TO PARAM FILE--------------------
  outPARAM.open(Form("../PARAM/HMS/CAL/hCal_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hCal_tWin_%d.param", runNUM));

  outPARAM << "; HMS Calorimeter Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  
  outPARAM << "hcal_pos_AdcTimeWindowMin = ";
  
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
outPARAM << setprecision(2) << hCal_tWinMin[layer][0][0]<<","
	 << hCal_tWinMin[layer][0][1]<<","
	 << hCal_tWinMin[layer][0][2]<<","
	 << hCal_tWinMin[layer][0][3]<<","
	 << hCal_tWinMin[layer][0][4]<<","
	 << hCal_tWinMin[layer][0][5]<<","
	 << hCal_tWinMin[layer][0][6]<<","
	 << hCal_tWinMin[layer][0][7]<<","
	 << hCal_tWinMin[layer][0][8]<<","
	 << hCal_tWinMin[layer][0][9]<<","
	 << hCal_tWinMin[layer][0][10]<<","
	 << hCal_tWinMin[layer][0][11]<<","
	 << hCal_tWinMin[layer][0][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMin[layer][0][0]<<","
	       << hCal_tWinMin[layer][0][1]<<","
	       << hCal_tWinMin[layer][0][2]<<","
	       << hCal_tWinMin[layer][0][3]<<","
	       << hCal_tWinMin[layer][0][4]<<","
	       << hCal_tWinMin[layer][0][5]<<","
	       << hCal_tWinMin[layer][0][6]<<","
	       << hCal_tWinMin[layer][0][7]<<","
	       << hCal_tWinMin[layer][0][8]<<","
	       << hCal_tWinMin[layer][0][9]<<","
	       << hCal_tWinMin[layer][0][10]<<","
	       << hCal_tWinMin[layer][0][11]<<","
	       << hCal_tWinMin[layer][0][12]<< fixed << endl;
      
    }
    
  }

  outPARAM << "" << endl;
  outPARAM << "" << endl;

  outPARAM << "hcal_pos_AdcTimeWindowMax = ";

  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMax[layer][0][0]<<","
		 << hCal_tWinMax[layer][0][1]<<","
		 << hCal_tWinMax[layer][0][2]<<","
		 << hCal_tWinMax[layer][0][3]<<","
		 << hCal_tWinMax[layer][0][4]<<","
		 << hCal_tWinMax[layer][0][5]<<","
		 << hCal_tWinMax[layer][0][6]<<","
		 << hCal_tWinMax[layer][0][7]<<","
		 << hCal_tWinMax[layer][0][8]<<","
		 << hCal_tWinMax[layer][0][9]<<","
		 << hCal_tWinMax[layer][0][10]<<","
		 << hCal_tWinMax[layer][0][11]<<","
		 << hCal_tWinMax[layer][0][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMax[layer][0][0]<<","
	       << hCal_tWinMax[layer][0][1]<<","
	       << hCal_tWinMax[layer][0][2]<<","
	       << hCal_tWinMax[layer][0][3]<<","
	       << hCal_tWinMax[layer][0][4]<<","
	       << hCal_tWinMax[layer][0][5]<<","
	       << hCal_tWinMax[layer][0][6]<<","
	       << hCal_tWinMax[layer][0][7]<<","
	       << hCal_tWinMax[layer][0][8]<<","
	       << hCal_tWinMax[layer][0][9]<<","
	       << hCal_tWinMax[layer][0][10]<<","
	       << hCal_tWinMax[layer][0][11]<<","
	       << hCal_tWinMax[layer][0][12]<< fixed << endl;
      
    }
    
  }
   
  outPARAM << "hcal_neg_AdcTimeWindowMin = ";
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMin[layer][1][0]<<","
		 << hCal_tWinMin[layer][1][1]<<","
		 << hCal_tWinMin[layer][1][2]<<","
		 << hCal_tWinMin[layer][1][3]<<","
		 << hCal_tWinMin[layer][1][4]<<","
		 << hCal_tWinMin[layer][1][5]<<","
		 << hCal_tWinMin[layer][1][6]<<","
		 << hCal_tWinMin[layer][1][7]<<","
		 << hCal_tWinMin[layer][1][8]<<","
		 << hCal_tWinMin[layer][1][9]<<","
		 << hCal_tWinMin[layer][1][10]<<","
		 << hCal_tWinMin[layer][1][11]<<","
		 << hCal_tWinMin[layer][1][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMin[layer][1][0]<<","
	       << hCal_tWinMin[layer][1][1]<<","
	       << hCal_tWinMin[layer][1][2]<<","
	       << hCal_tWinMin[layer][1][3]<<","
	       << hCal_tWinMin[layer][1][4]<<","
	       << hCal_tWinMin[layer][1][5]<<","
	       << hCal_tWinMin[layer][1][6]<<","
	       << hCal_tWinMin[layer][1][7]<<","
	       << hCal_tWinMin[layer][1][8]<<","
	       << hCal_tWinMin[layer][1][9]<<","
	       << hCal_tWinMin[layer][1][10]<<","
	       << hCal_tWinMin[layer][1][11]<<","
	       << hCal_tWinMin[layer][1][12]<< fixed << endl;
      
    }
    
  }

  outPARAM << "" << endl;
  outPARAM << "" << endl;

  outPARAM << "hcal_neg_AdcTimeWindowMax = ";
  //Loop over layers
  for (Int_t layer = 0; layer < 4; layer++){
    
    if (layer == 0)
      {
	outPARAM << setprecision(2) << hCal_tWinMax[layer][1][0]<<","
		 << hCal_tWinMax[layer][1][1]<<","
		 << hCal_tWinMax[layer][1][2]<<","
		 << hCal_tWinMax[layer][1][3]<<","
		 << hCal_tWinMax[layer][1][4]<<","
		 << hCal_tWinMax[layer][1][5]<<","
		 << hCal_tWinMax[layer][1][6]<<","
		 << hCal_tWinMax[layer][1][7]<<","
		 << hCal_tWinMax[layer][1][8]<<","
		 << hCal_tWinMax[layer][1][9]<<","
		 << hCal_tWinMax[layer][1][10]<<","
		 << hCal_tWinMax[layer][1][11]<<","
		 << hCal_tWinMax[layer][1][12]<< fixed << endl;
      }
    else{
      outPARAM << setprecision(2) << setw(33)<< hCal_tWinMax[layer][1][0]<<","
	       << hCal_tWinMax[layer][1][1]<<","
	       << hCal_tWinMax[layer][1][2]<<","
	       << hCal_tWinMax[layer][1][3]<<","
	       << hCal_tWinMax[layer][1][4]<<","
	       << hCal_tWinMax[layer][1][5]<<","
	       << hCal_tWinMax[layer][1][6]<<","
	       << hCal_tWinMax[layer][1][7]<<","
	       << hCal_tWinMax[layer][1][8]<<","
	       << hCal_tWinMax[layer][1][9]<<","
	       << hCal_tWinMax[layer][1][10]<<","
	       << hCal_tWinMax[layer][1][11]<<","
	       << hCal_tWinMax[layer][1][12]<< fixed << endl;
      
    }
    
  }  

  outPARAM.close();

  //------------------Write CHerenkov Time Window Cuts to Param File------------------------
 
  outPARAM.open(Form("../PARAM/HMS/CER/hCer_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hCer_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS Cherenkov Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hcer_adcTimeWindowMin =" << hCer_tWinMin[0] << "," << hCer_tWinMin[1] << endl;
  outPARAM << "hcer_adcTimeWindowMax =" << hCer_tWinMax[0] << "," << hCer_tWinMax[1] << endl;
  outPARAM.close();


  //--------------Write DC Time Window Cuts to Parameter File--------------------------------
  
  outPARAM.open(Form("../PARAM/HMS/DC/hDC_tWin_%d.param", runNUM));
  //outPARAM.open(Form("./hDC_tWin_%d.param", runNUM));
  
  outPARAM << "; HMS DC Parameter File Containing TimeWindow Min/Max Cuts " << endl;
  outPARAM << " " << endl;
  outPARAM << " " << endl;
  outPARAM << "hdc_tdc_min_win = " << setprecision(2) << hDC_tWinMin[0] << ", " << hDC_tWinMin[1] << ", " << hDC_tWinMin[2] << ", " << hDC_tWinMin[3] << ", " << hDC_tWinMin[4] << ", " << hDC_tWinMin[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMin[6] << ", " << hDC_tWinMin[7] << ", " << hDC_tWinMin[8] << ", " << hDC_tWinMin[9] << ", " << hDC_tWinMin[10] << ", " << hDC_tWinMin[11] <<endl;

  outPARAM << "hdc_tdc_max_win = " << setprecision(2) << hDC_tWinMax[0] << ", " << hDC_tWinMax[1] << ", " << hDC_tWinMax[2] << ", " << hDC_tWinMax[3] << ", " << hDC_tWinMax[4] << ", " << hDC_tWinMax[5] <<endl;
  outPARAM << setw(27) << setprecision(2) << hDC_tWinMax[6] << ", " << hDC_tWinMax[7] << ", " << hDC_tWinMax[8] << ", " << hDC_tWinMax[9] << ", " << hDC_tWinMax[10] << ", " << hDC_tWinMax[11] <<endl;

  outPARAM.close();
  
} //end program
