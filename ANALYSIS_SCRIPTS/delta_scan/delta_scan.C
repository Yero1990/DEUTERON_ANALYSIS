//Script to plot the one pass delta scan results (HMS run 1149-1171)
//for hydrogen elastics

void delta_scan()

{
  
  gROOT->SetBatch(kTRUE);


  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile("./hms_DeltaScan_histos.root", "RECREATE");


  //Set Histogram Binning
  //---Focal Plane/Delta---
  Double_t xfp_nbins, xfp_min, xfp_max;
  Double_t yfp_nbins, yfp_min, yfp_max;
  Double_t xp_fp_nbins, xp_fp_min, xp_fp_max;
  Double_t yp_fp_nbins, yp_fp_min, yp_fp_max;
  Double_t delta_nbins, delta_min, delta_max;
  //--Detector Calib Check---
  Double_t hodBeta_nbins, hodBeta_min, hodBeta_max;
  Double_t calEtrkNorm_nbins, calEtrkNorm_min, calEtrkNorm_max;
  Double_t dcDist_nbins, dcDist_min, dcDist_max;
  Double_t dcRes_nbins, dcRes_min, dcRes_max;
  //--Kinematics---
  Double_t Q2_nbins, Q2_min, Q2_max;
  Double_t W_nbins, W_min, W_max;
  Double_t xBj_nbins, xBj_min, xBj_max;
  
  xfp_nbins   = 100, xfp_min  =  -50,  xfp_max   =  50; 
  yfp_nbins   = 100, yfp_min  =  -40,  yfp_max   =  40;
  xp_fp_nbins = 100, xp_fp_min = -0.1, xp_fp_max =  0.1;
  yp_fp_nbins = 100, yp_fp_min = -0.1, yp_fp_max =  0.1;
  delta_nbins = 100, delta_min = -15,  delta_max =  15;
  
  hodBeta_nbins     = 100, hodBeta_min     = 0.3,    hodBeta_max     = 1.6;
  calEtrkNorm_nbins = 100, calEtrkNorm_min = 0.001,  calEtrkNorm_max = 2.0;
  dcDist_nbins      = 50,  dcDist_min      = -0.1,   dcDist_max      = 0.6;
  dcRes_nbins       = 100, dcRes_min       = -0.1,   dcRes_max       = 0.1;
  
  Q2_nbins  = 100, Q2_min  = 0,   Q2_max  = 0.4;
  W_nbins   = 100, W_min   = 0.9, W_max   = 1.0;
  xBj_nbins = 100, xBj_min = 0.5, xBj_max = 1.5;
  
  //Define Fixed Quantities
  static const Int_t dcPLANES = 12;
  string dc_pl_names[dcPLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  Int_t cnt=-1;  //run counter

  //----DEFINE CANVAS----
  
  //===Focal Plane/Delta
  TCanvas *xfp_v_yfp_Canv;
  TCanvas *W_v_xfp_Canv;
  TCanvas *W_v_xpfp_Canv;
  TCanvas *W_v_yfp_Canv;
  TCanvas *W_v_ypfp_Canv;


  //===Calibration Check!
  TCanvas *hod_Canv;
  TCanvas *cal_Canv;
  TCanvas *dcDist_Canv;
  TCanvas *dcResSigma_Canv;
  TCanvas *dcResMean_Canv;

  //===Kinematics 
  TCanvas *Q2_Canv;
  TCanvas *W_Canv;
  TCanvas *xBj_Canv;

  
  //===Fit Projections===
  TCanvas *fitProj_Xfp_Canv[21]; 

  //===Fit Graphs===
  TCanvas *fitGrph_XfpMean_Canv = new TCanvas("fitGrph_Xfp_Canv", "W Projections on X_{fp}", 3000, 2000);
  fitGrph_XfpMean_Canv->Divide(7,3, 0.01, 0.01);
  
  //Histograms Aesthetics
  TLine *line;  //line to draw at Mp, 0.938 GeV
  

  //Define TGraphs for plotting  
  TGraph *gr_mean[21];
  TGraph *gr_sigma[21];
  

  //Create/Divide Canvases
  xfp_v_yfp_Canv = new TCanvas("xfp_v_yfp_Canv", "X_{fp} vs. Y_{fp}", 2500, 1500);
  xfp_v_yfp_Canv->Divide(7,3);
  
  W_v_xfp_Canv = new TCanvas("W_v_xfp_Canv", "W vs. X_{fp}", 2500, 1500);
  W_v_xfp_Canv->Divide(7,3);
  
  W_v_xpfp_Canv = new TCanvas("W_v_xpfp_Canv", "W vs. X'_{fp}", 2500, 1500);
  W_v_xpfp_Canv->Divide(7,3);
  
  W_v_yfp_Canv = new TCanvas("W_v_yfp_Canv", "W vs. Y_{fp}", 2500, 1500);
  W_v_yfp_Canv->Divide(7,3);
  
  W_v_ypfp_Canv = new TCanvas("W_v_ypfp_Canv", "W vs. Y'_{fp}", 2500, 1500);
  W_v_ypfp_Canv->Divide(7,3);

  hod_Canv = new TCanvas("Hodo_Canv", "Hodoscope Beta", 2500, 1500);
  hod_Canv->Divide(7,3);

  cal_Canv = new TCanvas("Calo_Canv", "Calorimeter Norm. Track Energy", 2500, 1500);                              
  cal_Canv->Divide(7,3);   

  dcDist_Canv = new TCanvas("Drift Distance Canv.", "Superimposed Drift Distance", 2500, 1500);
  dcDist_Canv->Divide(7,3);
  
  Q2_Canv = new TCanvas("Q2_Canv", "Q2", 2500, 1500);
  Q2_Canv->Divide(7,3);

  W_Canv = new TCanvas("W_Canv", "W", 2500, 1500);
  W_Canv->Divide(7,3);

  xBj_Canv = new TCanvas("xBj_Canv", "xBj", 2500, 1500);
  xBj_Canv->Divide(7,3);

  dcResSigma_Canv = new TCanvas("Residual_Sig_Canv", "Residual Sigma", 2500, 1500);
  dcResSigma_Canv->Divide(7,3);

  dcResMean_Canv = new TCanvas("Residual_Mean_Canv", "Residual Mean", 2500, 1500);
  dcResMean_Canv->Divide(7,3);
  

  //----Define Histograms----

  //===Focal Plane/Delta
  TH2F *H_xfp_v_yfp[21];
  TH2F *H_W_v_xfp[21];
  TH2F *H_W_v_xpfp[21];
  TH2F *H_W_v_yfp[21];
  TH2F *H_W_v_ypfp[21];

  //===Calibration Check!
  TH1F *H_hod[21];
  TH1F *H_cal[21];
  TH1F *H_dcDist[21][dcPLANES];   //SUPERIMPOSSE 12 planes drift distance, per run
  TH1F *H_dcRes[21][dcPLANES];   //SUPERIMPOSSE 12 planes drift distance, per run

  //===Kinematics 
  TH1F *H_Q2[21];
  TH1F *H_W[21];
  TH1F *H_xBj[21];

  //==ProjectionY Hist
  TH1D *H_W_Xfp_projY[21];
  
  //Set the Leaf/Variable Names
   //---Names---(Calibration Check!)
  TString base;
  TString ndc_ndata;
  TString ndc_dist;
  TString ndc_nhit;
  TString ndc_res = "H.dc.residualExclPlane";
  TString nhod_beta = "H.hod.beta";
  TString ncal_etrknorm = "H.cal.etracknorm";
  //---Names---(Focal Plane)
  TString nxfp = "H.dc.x_fp";
  TString nyfp = "H.dc.y_fp";
  TString nxpfp = "H.dc.xp_fp";
  TString nypfp = "H.dc.yp_fp";
  //---Names---(Kinematics)
  TString nW = "H.kin.W";
  TString nQ2 = "H.kin.Q2";
  TString nxBj = "H.kin.x_bj";

  //--Variables (Calibration Check!)
  Int_t dc_ndata[dcPLANES];
  Double_t dc_dist[dcPLANES][1000];
  Double_t dc_res[dcPLANES]; 
  Double_t dc_nhit[dcPLANES];
  Double_t hod_beta;
  Double_t cal_etrknorm;
  //--Variables (Focal Plane)
  Double_t xfp;
  Double_t yfp;
  Double_t xpfp;
  Double_t ypfp;
  //--Variables (Kinematics)
  Double_t Q2;
  Double_t W;
  Double_t xBj;

  //Define Mean/Sigma to be used for residuals
  Double_t dc_mean[dcPLANES];
  Double_t dc_sigma[dcPLANES];
  Double_t x[dcPLANES];

  //Define W-Projection Relevant Variables
  TF1 *fit;
  Double_t bin_max = 0;
  Int_t max_Content = 0;
  Double_t x_max = 0;
  Double_t mean_fit = 0;
  Double_t std = 0;  
  Double_t sigma_fit = 0;
  Double_t chi2;
  Int_t kentries;

  //Create Arrays to store Fit Values
  Double_t mean_arr[21][25] = {0.};
  Double_t sigma_arr[21][25] = {0.};

  //Create TGraphs to plot arrays
  TGraph *gr_meanWxfp[21];
  TGraph *gr_sigmaWxfp[21];


  Int_t good_bin = -1;  //good bin counter
  //Set Array for plotting W mean values obtaiend from correlation 
  Double_t x_arr[21][25];
  for (int j = 0; j<21; j++)
    {
      for (int i=0; i<25; i++)
	{
	  x_arr[j][i] = (i+1)*1.0; 
	}
    }
  
  //Loop over Run Number
  for (int run=1149; run<=1171; run++)
    {
  
      //ignore bad runs
      if (run==1155 || run==1156) continue;
       
      //run counter
      cnt++;
      cout << "Analyzing Run " << run << " . . . " <<  endl;
      //Initialize Histograms
      
      //===Focal Plane/Delta
      H_xfp_v_yfp[cnt] = new TH2F(Form("H_Xfp_v_Yfp: Run%d",run), Form("Run %d: X_{fp} vs. Y_{fp}", run), yfp_nbins, yfp_min, yfp_max, xfp_nbins, xfp_min, xfp_max);
      H_W_v_xfp[cnt] = new TH2F(Form("W_v_Xfp: Run%d",run), Form("Run %d: W vs. X_{fp}", run), xfp_nbins, xfp_min, xfp_max, W_nbins, W_min, W_max);
      H_W_v_xpfp[cnt] = new TH2F(Form("W_v_Xpfp: Run%d",run), Form("Run %d: W vs. Xp_{fp}", run), xp_fp_nbins, xp_fp_min, xp_fp_max, W_nbins, W_min, W_max);
      H_W_v_yfp[cnt] = new TH2F(Form("W_v_Yfp: Run%d",run), Form("Run %d: W vs. Y_{fp}", run), yfp_nbins, yfp_min, yfp_max, W_nbins, W_min, W_max);
      H_W_v_ypfp[cnt] =  new TH2F(Form("W_v_Ypfp: Run%d",run), Form("Run %d: W vs. Yp_{fp}", run), yp_fp_nbins, yp_fp_min, yp_fp_max, W_nbins, W_min, W_max);

      //===Calibration Check!
      H_hod[cnt] = new TH1F(Form("H_hodBeta: Run%d",run), Form("Run %d: Hodoscope Beta", run), hodBeta_nbins, hodBeta_min, hodBeta_max);
      H_cal[cnt] = new TH1F(Form("H_calEtrkNorm: Run%d",run), Form("Run %d: Calorimeter E_{track} Norm.", run), calEtrkNorm_nbins, calEtrkNorm_min, calEtrkNorm_max);
      
      //Loop over 12 Planes
      for (int npl=0; npl<dcPLANES; npl++)
	{
	  H_dcDist[cnt][npl] = new TH1F(Form("Run %d: DC_%s_DriftDist", run,  dc_pl_names[npl].c_str()), Form("Run %d: DC Drift Distance, Plane %s", run,  dc_pl_names[npl].c_str()), dcDist_nbins, dcDist_min, dcDist_max);
	  H_dcRes[cnt][npl] = new TH1F(Form("Run %d: DC_%s_DriftResiduals",run, dc_pl_names[npl].c_str()), Form("Run %d: DC Residuals, Plane %s", run, dc_pl_names[npl].c_str()), dcRes_nbins, dcRes_min, dcRes_max);

	}

      //===Kinematics
      H_Q2[cnt] = new TH1F(Form("Run %d: H_Q2", run), Form("Run %d: Q^{2}", run), Q2_nbins, Q2_min, Q2_max);
      H_W[cnt] = new TH1F(Form("Run %d: H_W", run), Form("Run %d: Invariant Mass, W", run), W_nbins, W_min, W_max);
      H_xBj[cnt] = new TH1F(Form("Run %d: H_xBj", run), Form("Run %d: x-Bjorken, x_{Bj}", run), xBj_nbins, xBj_min, xBj_max);


      TString filename = Form("../../../ROOTfiles/hms_replay_delta_scan_%d_-1.root", run);

      //read the file and get the tree
      TFile *data_file = new TFile(filename, "READ");

      TTree *T = (TTree*)data_file->Get("T");
      
      //Set the Branch Address for Hod/Calo/FocalPlane/Kinematics
      T->SetBranchAddress(nhod_beta, &hod_beta);
      T->SetBranchAddress(ncal_etrknorm, &cal_etrknorm);
      T->SetBranchAddress(nxfp, &xfp);
      T->SetBranchAddress(nyfp, &yfp);
      T->SetBranchAddress(nxpfp, &xpfp);
      T->SetBranchAddress(nypfp, &ypfp);
      T->SetBranchAddress(nW, &W);
      T->SetBranchAddress(nQ2, &Q2);
      T->SetBranchAddress(nxBj, &xBj);

       //Loop over DC Planes to SetBranchAddress
      for (Int_t npl = 0; npl < dcPLANES; npl++ )
	{
	  x[npl] = npl+1;  //set x-axis for use with TGraph

	  //----Define TTree Leaf Names-----
	  base = "H.dc." + dc_pl_names[npl];
	  ndc_dist = base + "." + "dist";
	  ndc_nhit = base + "." + "nhit";
	  ndc_ndata = "Ndata." + base + "." + "time";
	  
	  //------Set Branch Address-------
	  T->SetBranchAddress(ndc_ndata, &dc_ndata[npl]);
	  T->SetBranchAddress(ndc_dist, dc_dist[npl]);
	  T->SetBranchAddress(ndc_nhit, &dc_nhit[npl]);
	  T->SetBranchAddress("H.dc.residualExclPlane", &dc_res[0]);
	
	} //end dc plane loop

    
      //Loop over Entries
      Long64_t nentries = T->GetEntries();
  
      //Loop over all entries
      for(Long64_t i=0; i<nentries; i++)
	{
	  
	  T->GetEntry(i);  
	
	  
	  //Loop over all DC planes
	  for (Int_t npl = 0; npl < dcPLANES; npl++ )
	    {
	      //Loop over hits
	      for (Int_t j=0; j < dc_ndata[npl]; j++)
		{
		  //Fill Histograms
		  if(dc_nhit[npl]==1)
		    {
		      H_dcDist[cnt][npl]->Fill(dc_dist[npl][j]);		      
		    } //end single hit requirement
		
		} //end loop over hits
	      
	      if(dc_nhit[npl]==1)
		{
		  H_dcRes[cnt][npl]->Fill(dc_res[npl]);
		}
	      
	    } //end dc plane loop
	  
	  //Fill Calorimeter/Hodoscope Histos
	  H_cal[cnt]->Fill(cal_etrknorm);
	  
	  if(cal_etrknorm>0.7){
	    H_hod[cnt]->Fill(hod_beta);
	  }
	  
	  //Fill Focal Plane 2D Correlations
	  H_xfp_v_yfp[cnt]->Fill(yfp, xfp);
	  H_W_v_xfp[cnt]->Fill(xfp, W);
	  H_W_v_xpfp[cnt]->Fill(xpfp, W);
	  H_W_v_yfp[cnt]->Fill(yfp, W);
	  H_W_v_ypfp[cnt]->Fill(ypfp, W);

	  //Fill Kinematics Quantities
	  H_Q2[cnt]->Fill(Q2);
	  H_W[cnt]->Fill(W);
	  H_xBj[cnt]->Fill(xBj);

	} //end entry loop
    
      //-------FIT PROJECTIONS of W vs. Focal Plane (xfp, xpfp, yfp, ypfp) projections
      fitProj_Xfp_Canv[cnt] = new TCanvas(Form("fitProj_Xfp_Canv_Run%d", run), "W Projections", 2500, 1500);
      fitProj_Xfp_Canv[cnt]->Divide(5,5);
    

      H_W_Xfp_projY[cnt] = new TH1D(Form("W_v_Xfp_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
      
      //reset good_bin counter
      good_bin = -1;
      Double_t integral_ratio;
	//Loop over all xfp bins and fit
      for (int ibin=0; ibin<xfp_nbins; ibin++)
	{
	  
	  // fitProj_Xfp_Canv[cnt]->cd(ibin+1);  //change order
	  H_W_Xfp_projY[cnt] =  H_W_v_xfp[cnt]->ProjectionY(Form("W_Xfp_run%d_bin%d", run, ibin), ibin, ibin+1);
	
	  //Get the Mean/Sigma to use as Fit Parameters (in hist range 0.93, 0.96)
	  H_W_Xfp_projY[cnt]->GetXaxis()->SetRange(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(0.93), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(0.96));

	  if (run==1157)
	    {
	      H_W_Xfp_projY[cnt]->GetXaxis()->SetRange(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(0.9), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(0.96));
	    }

	  bin_max = H_W_Xfp_projY[cnt]->GetMaximumBin();
	  max_Content =  H_W_Xfp_projY[cnt]->GetBinContent(bin_max);
	  x_max = H_W_Xfp_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
	  std =  H_W_Xfp_projY[cnt]->GetStdDev();
	  kentries =  H_W_Xfp_projY[cnt]->GetEntries();
	  
	  H_W_Xfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
	  if (kentries<1000 || max_Content < 20) continue;
	  //H_W_Xfp_projY[cnt]->GetXaxis()->SetRange(W_min, W_max);
	  good_bin++;
	  
	  //Convert the good bins to actual Xfp values
	  x_arr[cnt][good_bin] =  H_W_v_xfp[cnt]->GetXaxis()->GetBinCenter(ibin);
	  /*
	  cout << Form("x_arr[%d][%d] = ",cnt,good_bin) << x_arr[cnt][good_bin] << endl;
	  cout << "true bin = " << ibin << endl;
	  cout << "good_bin = " << good_bin << endl;
	  cout << "bin_max = " << bin_max << endl;
	  cout << "x_max = " << x_max << endl;
	  cout << "kentries = " << kentries << endl;
	  cout << "max COntent = " << max_Content << endl;
	  */
	  integral_ratio = H_W_Xfp_projY[cnt]->Integral(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(0.96), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(1.0)) / kentries;
	  //cout << "Integral / Entries = " << integral_ratio << endl;
	  
	  fitProj_Xfp_Canv[cnt]->cd(good_bin+1);
	  fitProj_Xfp_Canv[cnt]->Update();
	  H_W_Xfp_projY[cnt]->Draw(); 

	  if (integral_ratio >= 0.1)
	    {
	      //cout << "int ration >>> " << integral_ratio << endl;
	      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+0.5*std);
	      H_W_Xfp_projY[cnt]->Fit("fit", "QR");
	    }
	  else if (integral_ratio < 0.1)
	    {
	      //cout << "int ration >>> " << integral_ratio << endl;
	      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
	      H_W_Xfp_projY[cnt]->Fit("fit", "QR");
	    }
	  


	  //fitProj_Xfp_Canv[cnt]->Modified();
	  // fitProj_Xfp_Canv[cnt]->Update();
	  mean_fit =  fit->GetParameter(1);
	  sigma_fit = fit->GetParameter(2);
	  chi2 = fit->GetChisquare();

	  //Store Fit Values in Array
	  mean_arr[cnt][good_bin] = mean_fit;
	  sigma_arr[cnt][good_bin] = sigma_fit;

       	}
    
      //Create horizontal line at Mp = 0.938 to be used as reference
      line = new TLine(x_arr[cnt][0], 0.938, x_arr[cnt][good_bin], 0.938);
      line->SetLineColor(kRed);

      fitGrph_XfpMean_Canv->cd(cnt+1);
      gr_meanWxfp[cnt] = new TGraph(25, x_arr[cnt], mean_arr[cnt]);
      gr_meanWxfp[cnt]->SetMarkerStyle(22);
      gr_meanWxfp[cnt]->SetMarkerColor(kBlue);
      gr_meanWxfp[cnt]->SetMarkerSize(2);
      gr_meanWxfp[cnt]->SetTitle(Form("W Projections on X_{fp}, Run %d", run));
      gr_meanWxfp[cnt]->GetXaxis()->SetTitle("X-Focal Plane (cm)");
      gr_meanWxfp[cnt]->GetXaxis()->CenterTitle();
      gr_meanWxfp[cnt]->GetXaxis()->SetRangeUser(x_arr[cnt][0], x_arr[cnt][good_bin]);
      gr_meanWxfp[cnt]->GetYaxis()->SetRangeUser(0.9,1.0);
      gr_meanWxfp[cnt]->Draw("AP");
      line->Draw("same");
      fitGrph_XfpMean_Canv->Update();
      fitProj_Xfp_Canv[cnt]->SaveAs(Form("fitProj_Xfp_Run%d.pdf", run));

  
      dcDist_Canv->cd(cnt+1);
      //---- Plots Residuals Mean/Sigma per plane-------
      for (int npl=0; npl<dcPLANES; npl++)
	{

	  //Draw Drift Distance
	  //H_dcDist[cnt][npl]->Draw("sames");


	  //Get Mean/Sigma for residuals and convert to microns
	  // dc_mean[npl] =  H_dcRes[cnt][npl]->GetMean()*1e4; 
	  //dc_sigma[npl] =  H_dcRes[cnt][npl]->GetStdDev()*1e4;

	  

	}
      /*
      dcResMean_Canv->cd(cnt+1);
      gr_mean[cnt] = new TGraph(12, x, dc_mean);
      gr_mean[cnt]->SetMarkerStyle(22);
      gr_mean[cnt]->SetMarkerColor(kBlue);
      gr_mean[cnt]->SetMarkerSize(2);
      gr_mean[cnt]->GetYaxis()->SetRangeUser(-250, 250);
      
      //Set Axis Titles
      gr_mean[cnt]->GetXaxis()->SetTitle("HMS DC Planes Residuals");
      gr_mean[cnt]->GetXaxis()->CenterTitle();
      gr_mean[cnt]->GetYaxis()->SetTitle("HMS DC Residual Mean (#mum)");
      gr_mean[cnt]->GetYaxis()->CenterTitle();
      gr_mean[cnt]->SetTitle("HMS DC Plane Residuals Mean");
      gr_mean[cnt]->Draw("AP");

      dcResSigma_Canv->cd(cnt+1);
      gr_sigma[cnt] = new TGraph(12, x, dc_sigma);
      gr_sigma[cnt]->SetMarkerStyle(22);
      gr_sigma[cnt]->SetMarkerColor(kRed);
      gr_sigma[cnt]->SetMarkerSize(2);
      gr_sigma[cnt]->GetYaxis()->SetRangeUser(0, 1000.);
      
      //Set Axis Titles
      gr_sigma[cnt]->GetXaxis()->SetTitle("HMS DC Planes Residuals");
      gr_sigma[cnt]->GetXaxis()->CenterTitle();
      gr_sigma[cnt]->GetYaxis()->SetTitle("HMS DC Residual #sigma (#mum)");
      gr_sigma[cnt]->GetYaxis()->CenterTitle();
      gr_sigma[cnt]->SetTitle("HMS DC Plane Residuals Sigma");
      gr_sigma[cnt]->Draw("AP");
      */
      //Plot Hodo Beta/Calo Etrack Norm (Calibration Check!)
      hod_Canv->cd(cnt+1);
      H_hod[cnt]->Draw();
      cal_Canv->cd(cnt+1);
      H_cal[cnt]->Draw();


      //-----Draw Histograms on Canvas----
      //==Focal Plane Correlations===
      xfp_v_yfp_Canv->cd(cnt+1);
      H_xfp_v_yfp[cnt]->Draw("COLZ");
      
      W_v_xfp_Canv->cd(cnt+1);
      H_W_v_xfp[cnt]->Draw("COLZ");
       
      W_v_xpfp_Canv->cd(cnt+1);
      H_W_v_xpfp[cnt]->Draw("COLZ");
      
      W_v_yfp_Canv->cd(cnt+1);
      H_W_v_yfp[cnt]->Draw("COLZ");

      W_v_ypfp_Canv->cd(cnt+1);
      H_W_v_ypfp[cnt]->Draw("COLZ");

      //==Kinematics==
      W_Canv->cd(cnt+1);
      H_W[cnt]->Draw();
      Q2_Canv->cd(cnt+1);
      H_Q2[cnt]->Draw();
      xBj_Canv->cd(cnt+1);
      H_xBj[cnt]->Draw();

      outROOT->cd();
      outROOT->Write();

    } //end run number loop

  //cout << "Ended Final Run Loop .. . ." << endl;

  //Save Canvas
  
  //===Calibration Checks
  hod_Canv->SaveAs("./hodoBeta.pdf");
  cal_Canv->SaveAs("./caloEtrkNorm.pdf"); 
  dcDist_Canv->SaveAs("./dcDist.pdf");

  dcResMean_Canv->SaveAs("dcResidual_Mean.pdf");                                                                       
  dcResSigma_Canv->SaveAs("dcResidual_Sigma.pdf"); 

  //====Focal Plane=====
  xfp_v_yfp_Canv->SaveAs("xfp_v_yfp_plots.pdf");  
  W_v_xfp_Canv->SaveAs("W_v_xfp_plots.pdf");
  W_v_xpfp_Canv->SaveAs("W_v_xpfp_plots.pdf");
  W_v_yfp_Canv->SaveAs("W_v_yfp_plots.pdf");
  W_v_ypfp_Canv->SaveAs("W_v_ypfp_plots.pdf");

  //===Kinematics====
  W_Canv->SaveAs("InvariantMass.pdf");
  Q2_Canv->SaveAs("Q2.pdf");
  xBj_Canv->SaveAs("xBj.pdf");

  
  //===Fit W projection Graphs===
  fitGrph_XfpMean_Canv->SaveAs("fit_W_ProjGraph.pdf");
 

  outROOT->Close();
  
}
