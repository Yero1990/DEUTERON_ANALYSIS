//Script to plot the one pass delta scan results (HMS run 1149-1171)
//for hydrogen elastics

void coin_Wcheck()

{
  
  gROOT->SetBatch(kTRUE);
  //shoe fit results
  gStyle->SetOptFit(111111);

  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile("./coin_Wcheck_histos.root", "RECREATE");


  //Set Histogram Binning
  //---Focal Plane/Delta---
  Double_t xfp_nbins, xfp_min, xfp_max;
  Double_t yfp_nbins, yfp_min, yfp_max;
  Double_t xp_fp_nbins, xp_fp_min, xp_fp_max;
  Double_t yp_fp_nbins, yp_fp_min, yp_fp_max;
  Double_t delta_nbins, delta_min, delta_max;

  //---Target Reconstruction Variables
  Double_t ytar_nbins, ytar_min, ytar_max;
  Double_t yptar_nbins, yptar_min, yptar_max;

  //--Detector Calib Check---
  Double_t hodBeta_nbins, hodBeta_min, hodBeta_max;
  Double_t calEtrkNorm_nbins, calEtrkNorm_min, calEtrkNorm_max;
  Double_t dcDist_nbins, dcDist_min, dcDist_max;
  Double_t dcRes_nbins, dcRes_min, dcRes_max;

  //--Kinematics---
  Double_t Q2_nbins, Q2_min, Q2_max;
  Double_t W_nbins, W_min, W_max;
  Double_t xBj_nbins, xBj_min, xBj_max;
  Double_t emiss_nbins, emiss_min, emiss_max;

  xfp_nbins   = 100, xfp_min  =  -10,  xfp_max   =  10; 
  yfp_nbins   = 100, yfp_min  =  -10,  yfp_max   =  10;
  xp_fp_nbins = 100, xp_fp_min = -0.06, xp_fp_max =  0.04;
  yp_fp_nbins = 100, yp_fp_min = -0.03, yp_fp_max =  0.03;
  delta_nbins = 100, delta_min = -5,  delta_max =  3;

  ytar_nbins = 50, ytar_min = -2, ytar_max = 3;
  yptar_nbins = 100, yptar_min = -0.03, yptar_max = 0.03;

  
  hodBeta_nbins     = 100, hodBeta_min     = 0.3,    hodBeta_max     = 1.6;
  calEtrkNorm_nbins = 100, calEtrkNorm_min = 0.001,  calEtrkNorm_max = 2.0;
  dcDist_nbins      = 50,  dcDist_min      = -0.1,   dcDist_max      = 0.6;
  dcRes_nbins       = 100, dcRes_min       = -0.1,   dcRes_max       = 0.1;
  
  Q2_nbins  = 100, Q2_min  = 2,   Q2_max  = 5.;
  W_nbins   = 100, W_min   = 0.8, W_max   = 1.1;
  xBj_nbins = 100, xBj_min = 0.5, xBj_max = 1.5;
  emiss_nbins = 100, emiss_min = -0.2, emiss_max = 0.2;

  //Define Fixed Quantities SHMS DC
  static const Int_t dcPLANES = 12;
  string dc_pl_names[dcPLANES] = {"1u1", "1u2", "1x1", "1x2", "1v1", "1v2", "2v2", "2v1", "2x2", "2x1", "2u2", "2u1"};
  Int_t cnt=-1;  //run counter

  //----DEFINE CANVAS----
  
  //===Focal Plane/Delta
  TCanvas *xfp_v_yfp_Canv;
  TCanvas *W_v_xfp_Canv;
  TCanvas *W_v_xpfp_Canv;
  TCanvas *W_v_yfp_Canv;
  TCanvas *W_v_ypfp_Canv;
 
  TCanvas *Em_v_xfp_Canv;
  TCanvas *Em_v_xpfp_Canv;
  TCanvas *Em_v_yfp_Canv;
  TCanvas *EM_v_ypfp_Canv;


  //===Target Reconstruction
  TCanvas *W_v_ytar_Canv;
  TCanvas *W_v_yptar_Canv;
  TCanvas *W_v_delta_Canv;
  
  TCanvas *Em_v_ytar_Canv;
  TCanvas *Em_v_yptar_Canv;
  TCanvas *Em_v_delta_Canv;

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
  TCanvas *em_Canv;
  
  //===Fit Projections===
  //(FOCAL PLANE)
  TCanvas *fitProj_Xfp_Canv[21]; 
  TCanvas *fitProj_Xpfp_Canv[21]; 
  TCanvas *fitProj_Yfp_Canv[21]; 
  TCanvas *fitProj_Ypfp_Canv[21]; 

  TCanvas *EmfitProj_Xfp_Canv[21]; 
  TCanvas *EmfitProj_Xpfp_Canv[21]; 
  TCanvas *EmfitProj_Yfp_Canv[21]; 
  TCanvas *EmfitProj_Ypfp_Canv[21]; 

  //(TARGET)
  TCanvas *fitProj_Ytar_Canv[21];
  TCanvas *fitProj_Yptar_Canv[21];
  TCanvas *fitProj_Delta_Canv[21];

  TCanvas *EmfitProj_Ytar_Canv[21];
  TCanvas *EmfitProj_Yptar_Canv[21];
  TCanvas *EmfitProj_Delta_Canv[21];



  //===Fit Graphs Canvas====
  TCanvas *fitGrph_XfpMean_Canv = new TCanvas("fitGrph_Xfp_Canv", "W Projections on X_{fp}", 3000, 2000);
  fitGrph_XfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
   
  TCanvas *fitGrph_XpfpMean_Canv = new TCanvas("fitGrph_Xpfp_Canv", "W Projections on X'_{fp}", 3000, 2000);
  fitGrph_XpfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
  
  TCanvas *fitGrph_YfpMean_Canv = new TCanvas("fitGrph_Yfp_Canv", "W Projections on Y_{fp}", 3000, 2000);
  fitGrph_YfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
    
  TCanvas *fitGrph_YpfpMean_Canv = new TCanvas("fitGrph_Ypfp_Canv", "W Projections on Y'_{fp}", 3000, 2000);
  fitGrph_YpfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);

  TCanvas *fitGrph_YtarMean_Canv = new TCanvas("fitGrph_Ytar_Canv", "W Projections on Y_{tar}", 3000, 2000); 
  fitGrph_YtarMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01); 

  TCanvas *fitGrph_YptarMean_Canv = new TCanvas("fitGrph_Yptar_Canv", "W Projections on Y'_{tar}", 3000, 2000);     
  fitGrph_YptarMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);  

  TCanvas *fitGrph_DeltaMean_Canv = new TCanvas("fitGrph_Delta_Canv", "W Projections on #delta_{SHMS}", 3000, 2000); 
  fitGrph_DeltaMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01); 

  //---Emiss Graphs----
  TCanvas *EmfitGrph_XfpMean_Canv = new TCanvas("EmfitGrph_Xfp_Canv", "Em Projections on X_{fp}", 3000, 2000);
  EmfitGrph_XfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
   
  TCanvas *EmfitGrph_XpfpMean_Canv = new TCanvas("EmfitGrph_Xpfp_Canv", "Em Projections on X'_{fp}", 3000, 2000);
  EmfitGrph_XpfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
  
  TCanvas *EmfitGrph_YfpMean_Canv = new TCanvas("EmfitGrph_Yfp_Canv", "W Projections on Y_{fp}", 3000, 2000);
  EmfitGrph_YfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);
    
  TCanvas *EmfitGrph_YpfpMean_Canv = new TCanvas("EmfitGrph_Ypfp_Canv", "W Projections on Y'_{fp}", 3000, 2000);
  EmfitGrph_YpfpMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);

  TCanvas *EmfitGrph_YtarMean_Canv = new TCanvas("EmfitGrph_Ytar_Canv", "W Projections on Y_{tar}", 3000, 2000); 
  EmfitGrph_YtarMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01); 

  TCanvas *EmfitGrph_YptarMean_Canv = new TCanvas("EmfitGrph_Yptar_Canv", "W Projections on Y'_{tar}", 3000, 2000);     
  EmfitGrph_YptarMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01);  

  TCanvas *EmfitGrph_DeltaMean_Canv = new TCanvas("EmfitGrph_Delta_Canv", "W Projections on #delta_{SHMS}", 3000, 2000); 
  EmfitGrph_DeltaMean_Canv->Divide(1,1); //(7,3, 0.01, 0.01); 










  //Histograms Aesthetics
  TLine *line;  //line to draw at Mp, 0.938 GeV
  

  //Define TGraphs for plotting DC Residuals Mean/Sigma
  TGraph *gr_mean[21];
  TGraph *gr_sigma[21];
  

  //Create/Divide(1,1); // Canvases
  xfp_v_yfp_Canv = new TCanvas("xfp_v_yfp_Canv", "X_{fp} vs. Y_{fp}", 2500, 1500);
  xfp_v_yfp_Canv->Divide(1,1); //(7,3);
  
  W_v_xfp_Canv = new TCanvas("W_v_xfp_Canv", "W vs. X_{fp}", 2500, 1500);
  W_v_xfp_Canv->Divide(1,1); //(7,3);
  
  W_v_xpfp_Canv = new TCanvas("W_v_xpfp_Canv", "W vs. X'_{fp}", 2500, 1500);
  W_v_xpfp_Canv->Divide(1,1); //(7,3);
  
  W_v_yfp_Canv = new TCanvas("W_v_yfp_Canv", "W vs. Y_{fp}", 2500, 1500);
  W_v_yfp_Canv->Divide(1,1); //(7,3);
  
  W_v_ypfp_Canv = new TCanvas("W_v_ypfp_Canv", "W vs. Y'_{fp}", 2500, 1500);
  W_v_ypfp_Canv->Divide(1,1); //(7,3);

  W_v_ytar_Canv = new TCanvas("W_v_ytar_Canv", "W vs. Y_{tar}",  2500, 1500);
  W_v_ytar_Canv->Divide(1,1); //(7,3);

  W_v_yptar_Canv = new TCanvas("W_v_yptar_Canv", "W vs. Y'_{tar}",  2500, 1500);         
  W_v_yptar_Canv->Divide(1,1); //(7,3);

  W_v_delta_Canv = new TCanvas("W_v_delta_Canv", "W vs. #delta_{SHMS}",  2500, 1500);             
  W_v_delta_Canv->Divide(1,1); //(7,3);

  hod_Canv = new TCanvas("Hodo_Canv", "Hodoscope Beta", 2500, 1500);
  hod_Canv->Divide(1,1); //(7,3);

  cal_Canv = new TCanvas("Calo_Canv", "Calorimeter Norm. Track Energy", 2500, 1500);               
  cal_Canv->Divide(1,1); //(7,3);   

  dcDist_Canv = new TCanvas("Drift Distance Canv.", "Superimposed Drift Distance", 2500, 1500);
  dcDist_Canv->Divide(1,1); //(6,2);
  
  Q2_Canv = new TCanvas("Q2_Canv", "Q2", 2500, 1500);
  Q2_Canv->Divide(1,1); //(7,3);

  W_Canv = new TCanvas("W_Canv", "W", 2500, 1500);
  W_Canv->Divide(1,1); //(7,3);

  xBj_Canv = new TCanvas("xBj_Canv", "xBj", 2500, 1500);
  xBj_Canv->Divide(1,1); //(7,3);
  
  em_Canv = new TCanvas("Em", "Em", 2500,2500);
  em_Canv->Divide(1,1);
  
  dcResSigma_Canv = new TCanvas("Residual_Sig_Canv", "Residual Sigma", 2500, 1500);
  dcResSigma_Canv->Divide(1,1); //(7,3);

  dcResMean_Canv = new TCanvas("Residual_Mean_Canv", "Residual Mean", 2500, 1500);
  dcResMean_Canv->Divide(1,1); //(7,3);
  

  //----Define Histograms----

  //===Focal Plane
  TH2F *H_xfp_v_yfp[21];
  TH2F *H_W_v_xfp[21];
  TH2F *H_W_v_xpfp[21];
  TH2F *H_W_v_yfp[21];
  TH2F *H_W_v_ypfp[21];

  //===Target REconstruction
  TH2F *H_W_v_ytar[21];
  TH2F *H_W_v_yptar[21];
  TH2F *H_W_v_delta[21];

  //===Calibration Check!
  TH1F *H_hod[21];
  TH1F *H_cal[21];
  TH1F *H_dcDist[21][dcPLANES];   //SUPERIMPOSSE 12 planes drift distance, per run
  TH1F *H_dcRes[21][dcPLANES];   //SUPERIMPOSSE 12 planes drift distance, per run

  //===Kinematics 
  TH1F *H_Q2[21];
  TH1F *H_W[21];
  TH1F *H_xBj[21];
  TH1F *H_em[21];

  //==W Projection on Focal Plane Histos
  TH1D *H_W_Xfp_projY[21];
  TH1D *H_W_Xpfp_projY[21];
  TH1D *H_W_Yfp_projY[21];
  TH1D *H_W_Ypfp_projY[21];

  //==W Projection on Target Histos
  TH1D *H_W_Ytar_projY[21];
  TH1D *H_W_Yptar_projY[21];
  TH1D *H_W_Delta_projY[21];

  //Set the Leaf/Variable Names
   //---Names---(Calibration Check!)
  TString base;
  TString ndc_ndata;
  TString ndc_dist;
  TString ndc_nhit;
  TString ndc_res = "P.dc.residualExclPlane";
  TString nhod_beta = "P.hod.beta";
  TString ncal_etrknorm = "P.cal.etracknorm";
  //---Names---(Focal Plane)
  TString nxfp = "P.dc.x_fp";
  TString nyfp = "P.dc.y_fp";
  TString nxpfp = "P.dc.xp_fp";
  TString nypfp = "P.dc.yp_fp";
  //---Names---(Target Recon.)
  TString nytar = "P.gtr.y";
  TString nyptar = "P.gtr.ph";
  TString ndelta = "P.gtr.dp";
  //---Names---(Kinematics)
  TString nW = "P.kin.primary.W";
  TString nQ2 = "P.kin.primary.Q2";
  TString nxBj = "P.kin.primary.x_bj";
  TString nemiss = "H.kin.secondary.emiss";

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
  //--Variables (Target Recon.)
  Double_t ytar;
  Double_t yptar;
  Double_t delta;
  //--Variables (Kinematics)
  Double_t Q2;
  Double_t W;
  Double_t xBj;
  Double_t emiss;
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

  //Create Arrays to store W (inv. mass) Fit Values, when projected onto F. Plane
  Double_t meanXfp_arr[21][25] = {0.};   //for X focal plane
  Double_t meanXpfp_arr[21][25] = {0.};   //for X' focal plane
  
  Double_t sigmaXfp_arr[21][25] = {0.};  
  Double_t sigmaXpfp_arr[21][25] = {0.};

  Double_t meanYfp_arr[21][50] = {0.};  //for Y focal plane quantities
  Double_t meanYpfp_arr[21][50] = {0.}; //for Y' focal plane quantities
  
  Double_t sigmaYfp_arr[21][50] = {0.};
  Double_t sigmaYpfp_arr[21][50] = {0.};
 
  Double_t meanYtar_arr[21][30] = {0.};  
  Double_t meanYptar_arr[21][30] = {0.};
  Double_t meanDelta_arr[21][30] = {0.};
  
  Double_t sigmaYtar_arr[21][30] = {0.};
  Double_t sigmaYptar_arr[21][30] = {0.};
  Double_t sigmaDelta_arr[21][30] = {0.};


  //Create TGraphs to plot arrays
  TGraph *gr_meanWxfp[21];
  TGraph *gr_sigmaWxfp[21];
  
  TGraph *gr_meanWxpfp[21];
  TGraph *gr_sigmaWxpfp[21];
  
  TGraph *gr_meanWyfp[21];
  TGraph *gr_sigmaWyfp[21];
   
  TGraph *gr_meanWypfp[21];
  TGraph *gr_sigmaWypfp[21];

  TGraph *gr_meanWytar[21];
  TGraph *gr_meanWyptar[21];
  TGraph *gr_meanWdelta[21];

  Int_t good_bin = -1;  //good bin counter

  //Set Array for X-axis of TGraph when plotting W mean values obtaiend from correlation 
  Double_t xfp_arr[21][25];  
  Double_t xpfp_arr[21][25];  
  
  Double_t yfp_arr[21][50];   
  Double_t ypfp_arr[21][50]; 

  Double_t ytar_arr[21][30];   
  Double_t yptar_arr[21][30];
  Double_t delta_arr[21][30];

  for (int j = 0; j<21; j++)
    {
      for (int i=0; i<25; i++)
	{
	  xfp_arr[j][i] = (i+1)*1.0; 
	  xpfp_arr[j][i] = (i+1)*1.0;
	}
      
      for (int t=0; t<50; t++)
	{
	  yfp_arr[j][t] = (t+1)*1.0; 
	  ypfp_arr[j][t] = (t+1)*1.0; 
	}

      for (int n=0; n<30; n++)
	{
	  ytar_arr[j][n] = (n+1)*1.0;
	  yptar_arr[j][n] = (n+1)*1.0;
	  delta_arr[j][n] = (n+1)*1.0;
	}
    }
  
  //Loop over Run Number
  for (int run=3288; run<=3288; run++)
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

      //===Target Recon. Variables
      H_W_v_ytar[cnt] = new TH2F(Form("W_v_Ytar: Run%d",run), Form("Run %d: W vs. Y_{tar}", run), ytar_nbins, ytar_min, ytar_max, W_nbins, W_min, W_max);
      H_W_v_yptar[cnt] = new TH2F(Form("W_v_Yptar: Run%d",run), Form("Run %d: W vs. Y'_{tar}", run), yptar_nbins, yptar_min, yptar_max, W_nbins, W_min, W_max);
      H_W_v_delta[cnt] = new TH2F(Form("W_v_delta: Run%d",run), Form("Run %d: W vs. $delta_{SHMS}", run), delta_nbins, delta_min, delta_max, W_nbins, W_min, W_max);

      //===Calibration Check!
      H_hod[cnt] = new TH1F(Form("H_hodBeta: Run%d",run), Form("Run %d: Hodoscope Beta", run), hodBeta_nbins, hodBeta_min, hodBeta_max);
      H_cal[cnt] = new TH1F(Form("H_calEtrkNorm: Run%d",run), Form("Run %d: Calorimeter E_{track} Norm.", run), calEtrkNorm_nbins, calEtrkNorm_min, calEtrkNorm_max);
      
      //Loop over 12 Planes
      for (int npl=0; npl<dcPLANES; npl++)
	{
	  H_dcDist[cnt][npl] = new TH1F(Form("Run %d: DC_%s_DriftDist", run,  dc_pl_names[npl].c_str()), Form("DC Drift Distance, Plane %s", dc_pl_names[npl].c_str()), dcDist_nbins, dcDist_min, dcDist_max);
	  H_dcRes[cnt][npl] = new TH1F(Form("Run %d: DC_%s_DriftResiduals",run, dc_pl_names[npl].c_str()), Form("Run %d: DC Residuals, Plane %s", run, dc_pl_names[npl].c_str()), dcRes_nbins, dcRes_min, dcRes_max);

	}

      //===Kinematics
      H_Q2[cnt] = new TH1F(Form("Run %d: H_Q2", run), Form("Run %d: Q^{2}", run), Q2_nbins, Q2_min, Q2_max);
      H_W[cnt] = new TH1F(Form("Run %d: H_W", run), Form("Run %d: Invariant Mass, W", run), W_nbins, W_min, W_max);
      H_xBj[cnt] = new TH1F(Form("Run %d: H_xBj", run), Form("Run %d: x-Bjorken, x_{Bj}", run), xBj_nbins, xBj_min, xBj_max);
      H_em[cnt] = new TH1F(Form("Run %d: H_emiss", run), Form("Run %d: Missing Energy, E_{m}", run), emiss_nbins, emiss_min, emiss_max);

      TString filename = Form("../../../../ROOTfiles/coin_replay_heep_check_%d_-1.root", run);

      //read the file and get the tree
      TFile *data_file = new TFile(filename, "READ");

      TTree *T = (TTree*)data_file->Get("T");
      
      //Set the Branch Address for Hod/Calo/FocalPlane/Target/Kinematics
      T->SetBranchAddress(nhod_beta, &hod_beta);
      T->SetBranchAddress(ncal_etrknorm, &cal_etrknorm);
      T->SetBranchAddress(nxfp, &xfp);
      T->SetBranchAddress(nyfp, &yfp);
      T->SetBranchAddress(nxpfp, &xpfp);
      T->SetBranchAddress(nypfp, &ypfp);
      T->SetBranchAddress(nytar, &ytar);
      T->SetBranchAddress(nyptar, &yptar);
      T->SetBranchAddress(ndelta, &delta); 
      T->SetBranchAddress(nW, &W);
      T->SetBranchAddress(nQ2, &Q2);
      T->SetBranchAddress(nxBj, &xBj);
      T->SetBranchAddress(nemiss, &emiss);

       //Loop over DC Planes to SetBranchAddress
      for (Int_t npl = 0; npl < dcPLANES; npl++ )
	{
	  x[npl] = npl+1;  //set x-axis for use with TGraph

	  //----Define TTree Leaf Names-----
	  base = "P.dc." + dc_pl_names[npl];
	  ndc_dist = base + "." + "dist";
	  ndc_nhit = base + "." + "nhit";
	  ndc_ndata = "Ndata." + base + "." + "time";
	  
	  //------Set Branch Address-------
	  T->SetBranchAddress(ndc_ndata, &dc_ndata[npl]);
	  T->SetBranchAddress(ndc_dist, dc_dist[npl]);
	  T->SetBranchAddress(ndc_nhit, &dc_nhit[npl]);
	  T->SetBranchAddress("P.dc.residualExclPlane", &dc_res[0]);
	
	} //end dc plane loop

    
      //Loop over Entries
      Long64_t nentries = T->GetEntries();

      //Define Missing Energy CUT
      Bool_t em_cut;
  
      //Loop over all entries
      for(Long64_t i=0; i<nentries; i++)
	{
	  
	  T->GetEntry(i);  
	
	  em_cut = emiss < 0.04;
	  //cout << "em_cut = " << em_cut << endl;
	  if(!em_cut) {continue;}
	  //cout << "em_cut = " << em_cut << endl;
	  
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

	  //Fill Target Recon. Correlations
	  H_W_v_ytar[cnt]->Fill(ytar, W);
	  H_W_v_yptar[cnt]->Fill(yptar, W);
	  H_W_v_delta[cnt]->Fill(delta, W);

	  //Fill Kinematics Quantities
	  H_Q2[cnt]->Fill(Q2);
	  H_W[cnt]->Fill(W);
	  H_xBj[cnt]->Fill(xBj);
	  H_em[cnt]->Fill(emiss);
	} //end entry loop
    	  
      
      //**********************************
      //  X FOCAL PLANE PROJECTIONS/FITS *
      //**********************************
      
      //-------Create Fit PROJECTIONS Canvas-------
      fitProj_Xfp_Canv[cnt] = new TCanvas(Form("fitProj_Xfp_Canv_Run%d", run), "W Projections on X Focal Plane", 2500, 1500);
      fitProj_Xfp_Canv[cnt]->Divide(5,5);
      

      H_W_Xfp_projY[cnt] = new TH1D(Form("W_v_Xfp_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
      
      //reset good_bin counter
      good_bin = -1;
      Double_t integral_ratio;

      //Loop over all xfp bins and fit
      for (int ibin=0; ibin<xfp_nbins; ibin++)
	{
	  
	  //----GET 1D Projections of W vs. Focal Plane Quantities
	  H_W_Xfp_projY[cnt] =  H_W_v_xfp[cnt]->ProjectionY(Form("W_Xfp_run%d_bin%d", run, ibin), ibin, ibin+1);

	  //Set Range in W to get the Mean/Sigma to use as Fit Parameters 
	  H_W_Xfp_projY[cnt]->GetXaxis()->SetRange(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_max));


	  //---EXCEPTIONS------
	  if (run==1157)
	    {
	      H_W_Xfp_projY[cnt]->GetXaxis()->SetRange(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_max));
	    }
	  //-------------------
	  H_W_Xfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
	  bin_max = H_W_Xfp_projY[cnt]->GetMaximumBin();
	  max_Content =  H_W_Xfp_projY[cnt]->GetBinContent(bin_max);
	  x_max = H_W_Xfp_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
	  std =  H_W_Xfp_projY[cnt]->GetStdDev();
	  kentries =  H_W_Xfp_projY[cnt]->GetEntries();
	  
	  H_W_Xfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
	  if (kentries<1000 || max_Content < 20) continue;
	  good_bin++;
	  
	  //Convert the good bins to actual Xfp values
	  xfp_arr[cnt][good_bin] =  H_W_v_xfp[cnt]->GetXaxis()->GetBinCenter(ibin);
	  integral_ratio = H_W_Xfp_projY[cnt]->Integral(H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Xfp_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
	  
	  //Draw Projection on Canvas
	  fitProj_Xfp_Canv[cnt]->cd(good_bin+1);
	  fitProj_Xfp_Canv[cnt]->Update();
	  H_W_Xfp_projY[cnt]->Draw(); 

	  
	  //Perform the Fit
	  if (integral_ratio >= 0.1)
	    {
	      //cout << "int ration >>> " << integral_ratio << endl;
	      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
	      H_W_Xfp_projY[cnt]->Fit("fit", "QR");
	    }
	  else if (integral_ratio < 0.1)
	    {
	      //cout << "int ration >>> " << integral_ratio << endl;
	      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
	      H_W_Xfp_projY[cnt]->Fit("fit", "QR");
	    }
	  
	  //Get Fit Parameters
	  mean_fit =  fit->GetParameter(1);
	  sigma_fit = fit->GetParameter(2);
	  chi2 = fit->GetChisquare();

	  //Store Fit Values in Array
	  meanXfp_arr[cnt][good_bin] = mean_fit;
	  sigmaXfp_arr[cnt][good_bin] = sigma_fit;

       	} //end loop over bins
    
      //Create horizontal line at Mp = 0.938 to be used as reference
      line = new TLine(xfp_arr[cnt][0], 0.938, xfp_arr[cnt][good_bin], 0.938);
      line->SetLineColor(kRed);
      //Draw Graph of Mean W peaks vs. X_fp
      fitGrph_XfpMean_Canv->cd(cnt+1);
      gr_meanWxfp[cnt] = new TGraph(good_bin+1, xfp_arr[cnt], meanXfp_arr[cnt]);
      gr_meanWxfp[cnt]->SetMarkerStyle(22);
      gr_meanWxfp[cnt]->SetMarkerColor(kBlue);
      gr_meanWxfp[cnt]->SetMarkerSize(2);
      gr_meanWxfp[cnt]->SetTitle(Form("W Projections on X_{fp}, Run %d", run));
      gr_meanWxfp[cnt]->GetXaxis()->SetTitle("X-Focal Plane (cm)");
      gr_meanWxfp[cnt]->GetXaxis()->CenterTitle();
      gr_meanWxfp[cnt]->GetXaxis()->SetRangeUser(xfp_arr[cnt][0], xfp_arr[cnt][good_bin]);
      gr_meanWxfp[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
      gr_meanWxfp[cnt]->Draw("AP");
      line->Draw("same");
      fitGrph_XfpMean_Canv->Update();
      //Save Graph Canvas
      fitProj_Xfp_Canv[cnt]->SaveAs(Form("fitProj_Xfp_Run%d.pdf", run));



      //***********************************
      //  Xp FOCAL PLANE PROJECTIONS/FITS *
      //***********************************
      
      //-------Create FIT PROJECTIONS Canvas------
      fitProj_Xpfp_Canv[cnt] = new TCanvas(Form("fitProj_Xpfp_Canv_Run%d", run), "W Projections on X' Focal Plane", 2500, 1500);
      fitProj_Xpfp_Canv[cnt]->Divide(5,5);
      

      H_W_Xpfp_projY[cnt] = new TH1D(Form("W_v_Xpfp_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
      
      //reset good_bin counter
      good_bin = -1;
      
      //Loop over all xpfp bins and fit
      for (int ibin=0; ibin<xp_fp_nbins; ibin++)
	{

	  //----GET 1D Projections of W vs. Focal Plane Quantities
	  H_W_Xpfp_projY[cnt] =  H_W_v_xpfp[cnt]->ProjectionY(Form("W_Xpfp_run%d_bin%d", run, ibin), ibin, ibin+1);
	  H_W_Xpfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
	  bin_max = H_W_Xpfp_projY[cnt]->GetMaximumBin();
	  max_Content =  H_W_Xpfp_projY[cnt]->GetBinContent(bin_max);
	  x_max = H_W_Xpfp_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
	  std =  H_W_Xpfp_projY[cnt]->GetStdDev();
	  kentries =  H_W_Xpfp_projY[cnt]->GetEntries();

	  H_W_Xpfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
	  if (kentries<1000 || max_Content < 20) continue;
	  good_bin++;
	  
	  //Convert the good bins to actual Xpfp values
	  xpfp_arr[cnt][good_bin] =  H_W_v_xpfp[cnt]->GetXaxis()->GetBinCenter(ibin);
	  integral_ratio = H_W_Xpfp_projY[cnt]->Integral(H_W_Xpfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Xpfp_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  

	  //Draw Projection on Canvas
	  fitProj_Xpfp_Canv[cnt]->cd(good_bin+1);
	  fitProj_Xpfp_Canv[cnt]->Update();
	  H_W_Xpfp_projY[cnt]->Draw(); 

	  if(integral_ratio>=0.1){
	    fit = new TF1("fit", "gaus", x_max-1.2*std, x_max+1.4*std); 
	    H_W_Xpfp_projY[cnt]->Fit("fit", "QR");
	  }
	  
	  else if(integral_ratio<0.1){
	    fit = new TF1("fit", "gaus", x_max-1.2*std, x_max+1.4*std);
	    H_W_Xpfp_projY[cnt]->Fit("fit", "QR");
	  }
	  
	  //Get Fit Parameters
	  mean_fit =  fit->GetParameter(1);
	  sigma_fit = fit->GetParameter(2);
	  chi2 = fit->GetChisquare();
	  
	  //Store Fit Values in Array
	  meanXpfp_arr[cnt][good_bin] = mean_fit;
	  sigmaXpfp_arr[cnt][good_bin] = sigma_fit;
	  
	} //end loop over bins
    
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(xpfp_arr[cnt][0], 0.938, xpfp_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. X_fp
  fitGrph_XpfpMean_Canv->cd(cnt+1);
  gr_meanWxpfp[cnt] = new TGraph(good_bin+1, xpfp_arr[cnt], meanXpfp_arr[cnt]);
  gr_meanWxpfp[cnt]->SetMarkerStyle(22);
  gr_meanWxpfp[cnt]->SetMarkerColor(kBlue);
  gr_meanWxpfp[cnt]->SetMarkerSize(2);
  gr_meanWxpfp[cnt]->SetTitle(Form("W Projections on X'_{fp}: Run %d", run));
  gr_meanWxpfp[cnt]->GetXaxis()->SetTitle("X'-Focal Plane (cm)");
  gr_meanWxpfp[cnt]->GetXaxis()->CenterTitle();
  gr_meanWxpfp[cnt]->GetXaxis()->SetRangeUser(xpfp_arr[cnt][0], xpfp_arr[cnt][good_bin]);
  gr_meanWxpfp[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWxpfp[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_XpfpMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Xpfp_Canv[cnt]->SaveAs(Form("fitProj_Xpfp_Run%d.pdf", run));
  
    
  //***********************************
  //  Y FOCAL PLANE PROJECTIONS/FITS *
  //***********************************
  
  //-------Create FIT PROJECTIONS Canvas------
  fitProj_Yfp_Canv[cnt] = new TCanvas(Form("fitProj_Yfp_Canv_Run%d", run), "W Projections on Y Focal Plane", 2500, 1500);
  fitProj_Yfp_Canv[cnt]->Divide(5,10);
  

  H_W_Yfp_projY[cnt] = new TH1D(Form("W_v_Yfp_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
  
  //reset good_bin counter
  good_bin = -1;
  
  //Loop over all xpfp bins and fit
  for (int ibin=0; ibin<yfp_nbins; ibin++)
    {

      //----GET 1D Projections of W vs. Y Focal Plane Quantities
      H_W_Yfp_projY[cnt] =  H_W_v_yfp[cnt]->ProjectionY(Form("W_Yfp_run%d_bin%d", run, ibin), ibin, ibin+1);
      H_W_Yfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
      bin_max = H_W_Yfp_projY[cnt]->GetMaximumBin();
      max_Content =  H_W_Yfp_projY[cnt]->GetBinContent(bin_max);
      x_max = H_W_Yfp_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
      std =  H_W_Yfp_projY[cnt]->GetStdDev();
      kentries =  H_W_Yfp_projY[cnt]->GetEntries();
      
      H_W_Yfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
      if (kentries<300 || max_Content < 50) continue;
      good_bin++;
	  
      //Convert the good bins to actual Xpfp values
      yfp_arr[cnt][good_bin] =  H_W_v_yfp[cnt]->GetXaxis()->GetBinCenter(ibin);
      integral_ratio = H_W_Yfp_projY[cnt]->Integral(H_W_Yfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Yfp_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
      
      //Draw Projection on Canvas
      fitProj_Yfp_Canv[cnt]->cd(good_bin+1);
      fitProj_Yfp_Canv[cnt]->Update();
      H_W_Yfp_projY[cnt]->Draw(); 
	  
      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
      H_W_Yfp_projY[cnt]->Fit("fit", "QR");
      
      //Get Fit Parameters
      mean_fit =  fit->GetParameter(1);
      sigma_fit = fit->GetParameter(2);
      chi2 = fit->GetChisquare();
      
      //Store Fit Values in Array
      meanYfp_arr[cnt][good_bin] = mean_fit;
      sigmaYfp_arr[cnt][good_bin] = sigma_fit;
      
    } //end loop over bins
  
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(yfp_arr[cnt][0], 0.938, yfp_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. Y_fp
  fitGrph_YfpMean_Canv->cd(cnt+1);
  gr_meanWyfp[cnt] = new TGraph(good_bin+1, yfp_arr[cnt], meanYfp_arr[cnt]);
  gr_meanWyfp[cnt]->SetMarkerStyle(22);
  gr_meanWyfp[cnt]->SetMarkerColor(kBlue);
  gr_meanWyfp[cnt]->SetMarkerSize(2);
  gr_meanWyfp[cnt]->SetTitle(Form("W Projections on Y_{fp}: Run %d", run));
  gr_meanWyfp[cnt]->GetXaxis()->SetTitle("Y-Focal Plane (cm)");
  gr_meanWyfp[cnt]->GetXaxis()->CenterTitle();
  gr_meanWyfp[cnt]->GetXaxis()->SetRangeUser(yfp_arr[cnt][0], yfp_arr[cnt][good_bin]);
  gr_meanWyfp[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWyfp[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_YfpMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Yfp_Canv[cnt]->SaveAs(Form("fitProj_Yfp_Run%d.pdf", run));

  
  //***********************************
  //  Y' FOCAL PLANE PROJECTIONS/FITS *
  //***********************************
  
  //-------Create FIT PROJECTIONS Canvas------
  fitProj_Ypfp_Canv[cnt] = new TCanvas(Form("fitProj_Ypfp_Canv_Run%d", run), "W Projections on Y' Focal Plane", 2500, 1500);
  fitProj_Ypfp_Canv[cnt]->Divide(5,10);
  

  H_W_Ypfp_projY[cnt] = new TH1D(Form("W_v_Ypfp_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
  
  //reset good_bin counter
  good_bin = -1;
  
  //Loop over all xpfp bins and fit
  for (int ibin=0; ibin<yp_fp_nbins; ibin++)
    {

      //----GET 1D Projections of W vs. Y Focal Plane Quantities
      H_W_Ypfp_projY[cnt] =  H_W_v_ypfp[cnt]->ProjectionY(Form("W_Ypfp_run%d_bin%d", run, ibin), ibin, ibin+1);
      H_W_Ypfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
      bin_max = H_W_Ypfp_projY[cnt]->GetMaximumBin();
      max_Content =  H_W_Ypfp_projY[cnt]->GetBinContent(bin_max);
      x_max = H_W_Ypfp_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
      std =  H_W_Ypfp_projY[cnt]->GetStdDev();
      kentries =  H_W_Ypfp_projY[cnt]->GetEntries();
      
      H_W_Ypfp_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
      if (kentries<300 || max_Content < 50) continue;
      good_bin++;
	  
      //Convert the good bins to actual Xpfp values
      ypfp_arr[cnt][good_bin] =  H_W_v_ypfp[cnt]->GetXaxis()->GetBinCenter(ibin);
      integral_ratio = H_W_Ypfp_projY[cnt]->Integral(H_W_Ypfp_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Ypfp_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
      
      //Draw Projection on Canvas
      fitProj_Ypfp_Canv[cnt]->cd(good_bin+1);
      fitProj_Ypfp_Canv[cnt]->Update();
      H_W_Ypfp_projY[cnt]->Draw(); 
	  
      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
      H_W_Ypfp_projY[cnt]->Fit("fit", "QR");
      
      //Get Fit Parameters
      mean_fit =  fit->GetParameter(1);
      sigma_fit = fit->GetParameter(2);
      chi2 = fit->GetChisquare();
      
      //Store Fit Values in Array
      meanYpfp_arr[cnt][good_bin] = mean_fit;
      sigmaYpfp_arr[cnt][good_bin] = sigma_fit;
      
    } //end loop over bins
  
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(ypfp_arr[cnt][0], 0.938, ypfp_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. Y_fp
  fitGrph_YpfpMean_Canv->cd(cnt+1);
  gr_meanWypfp[cnt] = new TGraph(good_bin+1, ypfp_arr[cnt], meanYpfp_arr[cnt]);
  gr_meanWypfp[cnt]->SetMarkerStyle(22);
  gr_meanWypfp[cnt]->SetMarkerColor(kBlue);
  gr_meanWypfp[cnt]->SetMarkerSize(2);
  gr_meanWypfp[cnt]->SetTitle(Form("W Projections on Y'_{fp}: Run %d", run));
  gr_meanWypfp[cnt]->GetXaxis()->SetTitle("Y'-Focal Plane (cm)");
  gr_meanWypfp[cnt]->GetXaxis()->CenterTitle();
  gr_meanWypfp[cnt]->GetXaxis()->SetRangeUser(ypfp_arr[cnt][0], ypfp_arr[cnt][good_bin]);
  gr_meanWypfp[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWypfp[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_YpfpMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Ypfp_Canv[cnt]->SaveAs(Form("fitProj_Ypfp_Run%d.pdf", run));


    
  //*****************************
  //  Y-TARGET PROJECTIONS/FITS *
  //*****************************
  
  //-------Create FIT PROJECTIONS Canvas------
  fitProj_Ytar_Canv[cnt] = new TCanvas(Form("fitProj_Ytar_Canv_Run%d", run), "W Projections on Y-Target", 2500, 1500);
  fitProj_Ytar_Canv[cnt]->Divide(5,6);
  

  H_W_Ytar_projY[cnt] = new TH1D(Form("W_v_Ytar_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
  
  //reset good_bin counter
  good_bin = -1;
  
  //Loop over all xpfp bins and fit
  for (int ibin=0; ibin<ytar_nbins; ibin++)
    {

      //----GET 1D Projections of W vs. Y Target
      H_W_Ytar_projY[cnt] =  H_W_v_ytar[cnt]->ProjectionY(Form("W_Ytar_run%d_bin%d", run, ibin), ibin, ibin+1);
      H_W_Ytar_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
      bin_max = H_W_Ytar_projY[cnt]->GetMaximumBin();
      max_Content =  H_W_Ytar_projY[cnt]->GetBinContent(bin_max);
      x_max = H_W_Ytar_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
      std =  H_W_Ytar_projY[cnt]->GetStdDev();
      kentries =  H_W_Ytar_projY[cnt]->GetEntries();
      
      H_W_Ytar_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
      if (kentries<300 || max_Content < 50) continue;
      good_bin++;
	  
      //Convert the good bins to actual Ytar values
      ytar_arr[cnt][good_bin] =  H_W_v_ytar[cnt]->GetXaxis()->GetBinCenter(ibin);
      integral_ratio = H_W_Ytar_projY[cnt]->Integral(H_W_Ytar_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Ytar_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
      
      //Draw Projection on Canvas
      fitProj_Ytar_Canv[cnt]->cd(good_bin+1);
      fitProj_Ytar_Canv[cnt]->Update();
      H_W_Ytar_projY[cnt]->Draw(); 
	  
      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
      H_W_Ytar_projY[cnt]->Fit("fit", "QR");
      
      //Get Fit Parameters
      mean_fit =  fit->GetParameter(1);
      sigma_fit = fit->GetParameter(2);
      chi2 = fit->GetChisquare();
      
      //Store Fit Values in Array
      meanYtar_arr[cnt][good_bin] = mean_fit;
      sigmaYtar_arr[cnt][good_bin] = sigma_fit;

    } //end loop over bins
  
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(ytar_arr[cnt][0], 0.938, ytar_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. Y_fp
  fitGrph_YtarMean_Canv->cd(cnt+1);
  gr_meanWytar[cnt] = new TGraph(good_bin+1, ytar_arr[cnt], meanYtar_arr[cnt]);
  gr_meanWytar[cnt]->SetMarkerStyle(22);
  gr_meanWytar[cnt]->SetMarkerColor(kBlue);
  gr_meanWytar[cnt]->SetMarkerSize(2);
  gr_meanWytar[cnt]->SetTitle(Form("W Projections on Y_{tar}: Run %d", run));
  gr_meanWytar[cnt]->GetXaxis()->SetTitle("Y-Target (cm)");
  gr_meanWytar[cnt]->GetXaxis()->CenterTitle();
  gr_meanWytar[cnt]->GetXaxis()->SetRangeUser(ytar_arr[cnt][0], ytar_arr[cnt][good_bin]);
  gr_meanWytar[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWytar[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_YtarMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Ytar_Canv[cnt]->SaveAs(Form("fitProj_Ytar_Run%d.pdf", run));

  
  //******************************
  //  Y'-TARGET PROJECTIONS/FITS *
  //******************************
  
  //-------Create FIT PROJECTIONS Canvas------
  fitProj_Yptar_Canv[cnt] = new TCanvas(Form("fitProj_Yptar_Canv_Run%d", run), "W Projections on Y'-Target", 2500, 1500);
  fitProj_Yptar_Canv[cnt]->Divide(5,6);
  

  H_W_Yptar_projY[cnt] = new TH1D(Form("W_v_Yptar_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
  
  //reset good_bin counter
  good_bin = -1;
  
  //Loop over all xpfp bins and fit
  for (int ibin=0; ibin<yptar_nbins; ibin++)
    {

      //----GET 1D Projections of W vs. Y Target
      H_W_Yptar_projY[cnt] =  H_W_v_yptar[cnt]->ProjectionY(Form("W_Yptar_run%d_bin%d", run, ibin), ibin, ibin+1);
      H_W_Yptar_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
      bin_max = H_W_Yptar_projY[cnt]->GetMaximumBin();
      max_Content =  H_W_Yptar_projY[cnt]->GetBinContent(bin_max);
      x_max = H_W_Yptar_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
      std =  H_W_Yptar_projY[cnt]->GetStdDev();
      kentries =  H_W_Yptar_projY[cnt]->GetEntries();
      
      H_W_Yptar_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
      if (kentries<300 || max_Content < 50) continue;
      good_bin++;
	  
      //Convert the good bins to actual Yptar values
      yptar_arr[cnt][good_bin] =  H_W_v_yptar[cnt]->GetXaxis()->GetBinCenter(ibin);
      integral_ratio = H_W_Yptar_projY[cnt]->Integral(H_W_Yptar_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Yptar_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
      
      //Draw Projection on Canvas
      fitProj_Yptar_Canv[cnt]->cd(good_bin+1);
      fitProj_Yptar_Canv[cnt]->Update();
      H_W_Yptar_projY[cnt]->Draw(); 
	  
      fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
      H_W_Yptar_projY[cnt]->Fit("fit", "QR");
      
      //Get Fit Parameters
      mean_fit =  fit->GetParameter(1);
      sigma_fit = fit->GetParameter(2);
      chi2 = fit->GetChisquare();
      
      //Store Fit Values in Array
      meanYptar_arr[cnt][good_bin] = mean_fit;
      sigmaYptar_arr[cnt][good_bin] = sigma_fit;
      
    } //end loop over bins
  
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(yptar_arr[cnt][0], 0.938, yptar_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. Y_fp
  fitGrph_YptarMean_Canv->cd(cnt+1);
  gr_meanWyptar[cnt] = new TGraph(good_bin+1, yptar_arr[cnt], meanYptar_arr[cnt]);
  gr_meanWyptar[cnt]->SetMarkerStyle(22);
  gr_meanWyptar[cnt]->SetMarkerColor(kBlue);
  gr_meanWyptar[cnt]->SetMarkerSize(2);
  gr_meanWyptar[cnt]->SetTitle(Form("W Projections on Y'_{tar}: Run %d", run));
  gr_meanWyptar[cnt]->GetXaxis()->SetTitle("Y'-Target (cm)");
  gr_meanWyptar[cnt]->GetXaxis()->CenterTitle();
  gr_meanWyptar[cnt]->GetXaxis()->SetRangeUser(yptar_arr[cnt][0], yptar_arr[cnt][good_bin]);
  gr_meanWyptar[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWyptar[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_YptarMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Yptar_Canv[cnt]->SaveAs(Form("fitProj_Yptar_Run%d.pdf", run));

  //******************************
  //  Delta PROJECTIONS/FITS     *
  //******************************
  
  //-------Create FIT PROJECTIONS Canvas------
  fitProj_Delta_Canv[cnt] = new TCanvas(Form("fitProj_Delta_Canv_Run%d", run), "W Projections on Delta", 2500, 1500);
  fitProj_Delta_Canv[cnt]->Divide(5,6);
  

  H_W_Delta_projY[cnt] = new TH1D(Form("W_v_Delta_run%d",run), "", W_nbins, W_min, W_max); //proj. hist
  
  //reset good_bin counter
  good_bin = -1;
  
  //Loop over all xpfp bins and fit
  for (int ibin=0; ibin<delta_nbins; ibin++)
    {

      //----GET 1D Projections of W vs. Y Target
      H_W_Delta_projY[cnt] =  H_W_v_delta[cnt]->ProjectionY(Form("W_Delta_run%d_bin%d", run, ibin), ibin, ibin+1);
      H_W_Delta_projY[cnt]->GetXaxis()->SetRangeUser(W_min,W_max);
      bin_max = H_W_Delta_projY[cnt]->GetMaximumBin();
      max_Content =  H_W_Delta_projY[cnt]->GetBinContent(bin_max);
      x_max = H_W_Delta_projY[cnt]->GetXaxis()->GetBinCenter(bin_max);
      std =  H_W_Delta_projY[cnt]->GetStdDev();
      kentries =  H_W_Delta_projY[cnt]->GetEntries();
      
      H_W_Delta_projY[cnt]->GetXaxis()->SetRangeUser(W_min, W_max);
	  
      if (kentries<300 || max_Content < 50) continue;
      good_bin++;
	  
      //Convert the good bins to actual Yptar values
      delta_arr[cnt][good_bin] =  H_W_v_delta[cnt]->GetXaxis()->GetBinCenter(ibin);
      integral_ratio = H_W_Delta_projY[cnt]->Integral(H_W_Delta_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Delta_projY[cnt]->GetXaxis()->FindBin(W_max)) / kentries;	  
      
      int Wint, bkgint;
      Wint = H_W_Delta_projY[cnt]->Integral(H_W_Delta_projY[cnt]->GetXaxis()->FindBin(W_min), H_W_Delta_projY[cnt]->GetXaxis()->FindBin(W_max));
      bkgint = H_W_Delta_projY[cnt]->Integral(H_W_Delta_projY[cnt]->GetXaxis()->FindBin(0.91), H_W_Delta_projY[cnt]->GetXaxis()->FindBin(1.0));

      if(bkgint > Wint) continue;

      //Draw Projection on Canvas
      fitProj_Delta_Canv[cnt]->cd(good_bin+1);
      fitProj_Delta_Canv[cnt]->Update();
      H_W_Delta_projY[cnt]->Draw(); 
	 
      if(integral_ratio>=0.1)
	{
	  fit = new TF1("fit", "gaus", x_max-1.3*std, x_max+1.3*std);
	  H_W_Delta_projY[cnt]->Fit("fit", "QR");
	}

      else if(integral_ratio<0.1)
	{
	  fit = new TF1("fit", "gaus", x_max-1*std, x_max+1*std);
	  H_W_Delta_projY[cnt]->Fit("fit", "QR");
	}
 
      
      //Get Fit Parameters
      mean_fit =  fit->GetParameter(1);
      sigma_fit = fit->GetParameter(2);
      chi2 = fit->GetChisquare();
      
      //Store Fit Values in Array
      meanDelta_arr[cnt][good_bin] = mean_fit;
      sigmaDelta_arr[cnt][good_bin] = sigma_fit;
      
    } //end loop over bins
  
  
  //Create horizontal line at Mp = 0.938 to be used as reference
  line = new TLine(delta_arr[cnt][0], 0.938, delta_arr[cnt][good_bin], 0.938);
  line->SetLineColor(kRed);
  //Draw Graph of Mean W peaks vs. Y_fp
  fitGrph_DeltaMean_Canv->cd(cnt+1);
  gr_meanWdelta[cnt] = new TGraph(good_bin+1, delta_arr[cnt], meanDelta_arr[cnt]);
  gr_meanWdelta[cnt]->SetMarkerStyle(22);
  gr_meanWdelta[cnt]->SetMarkerColor(kBlue);
  gr_meanWdelta[cnt]->SetMarkerSize(2);
  gr_meanWdelta[cnt]->SetTitle(Form("W Projections on #delta_{SHMS}: Run %d", run));
  gr_meanWdelta[cnt]->GetXaxis()->SetTitle("#delta_{SHMS} (%)");
  gr_meanWdelta[cnt]->GetXaxis()->CenterTitle();
  gr_meanWdelta[cnt]->GetXaxis()->SetRangeUser(delta_arr[cnt][0], delta_arr[cnt][good_bin]);
  gr_meanWdelta[cnt]->GetYaxis()->SetRangeUser(W_min,W_max);
  gr_meanWdelta[cnt]->Draw("AP");
  line->Draw("same");
  fitGrph_DeltaMean_Canv->Update();
  //Save Graph Canvas
  fitProj_Delta_Canv[cnt]->SaveAs(Form("fitProj_Delta_Run%d.pdf", run));
  

  //----------PLOT DRIFT CHAMBER RELEVANT QUANTITIES---------------------
 
  //reset
  bin_max = 0;
  max_Content = 0;

      dcDist_Canv->cd(cnt+1);
      //---- Plots Residuals Mean/Sigma per plane-------
      for (int npl=0; npl<dcPLANES; npl++)
	{
	  bin_max = H_dcDist[cnt][npl]->GetMaximumBin();
	  max_Content = H_dcDist[cnt][npl]->GetBinContent(bin_max);
	  H_dcDist[cnt][npl]->SetMaximum(max_Content+500); 

	  dcDist_Canv->cd(npl+1);

	  //Draw Drift Distance
	  H_dcDist[cnt][npl]->DrawNormalized("same");


	  //Get Mean/Sigma for residuals and convert to microns
	  dc_mean[npl] =  H_dcRes[cnt][npl]->GetMean()*1e4; 
	  dc_sigma[npl] =  H_dcRes[cnt][npl]->GetStdDev()*1e4;

	  
	}
      
      dcResMean_Canv->cd(cnt+1);
      gr_mean[cnt] = new TGraph(12, x, dc_mean);
      gr_mean[cnt]->SetMarkerStyle(22);
      gr_mean[cnt]->SetMarkerColor(kBlue);
      gr_mean[cnt]->SetMarkerSize(2);
      gr_mean[cnt]->GetYaxis()->SetRangeUser(-250, 250);
      
      //Set Axis Titles
      gr_mean[cnt]->GetXaxis()->SetTitle("SHMS DC Planes Residuals");
      gr_mean[cnt]->GetXaxis()->CenterTitle();
      gr_mean[cnt]->GetYaxis()->SetTitle("SHMS DC Residual Mean (#mum)");
      gr_mean[cnt]->GetYaxis()->CenterTitle();
      gr_mean[cnt]->SetTitle("SHMS DC Plane Residuals Mean");
      gr_mean[cnt]->Draw("AP");

      dcResSigma_Canv->cd(cnt+1);
      gr_sigma[cnt] = new TGraph(12, x, dc_sigma);
      gr_sigma[cnt]->SetMarkerStyle(22);
      gr_sigma[cnt]->SetMarkerColor(kRed);
      gr_sigma[cnt]->SetMarkerSize(2);
      gr_sigma[cnt]->GetYaxis()->SetRangeUser(0, 1000.);
      
      //Set Axis Titles
      gr_sigma[cnt]->GetXaxis()->SetTitle("SHMS DC Planes Residuals");
      gr_sigma[cnt]->GetXaxis()->CenterTitle();
      gr_sigma[cnt]->GetYaxis()->SetTitle("SHMS DC Residual #sigma (#mum)");
      gr_sigma[cnt]->GetYaxis()->CenterTitle();
      gr_sigma[cnt]->SetTitle("SHMS DC Plane Residuals Sigma");
      gr_sigma[cnt]->Draw("AP");
      
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


      //==Target Recon. Correlations
      W_v_ytar_Canv->cd(cnt+1);
      H_W_v_ytar[cnt]->Draw("COLZ"); 

      W_v_yptar_Canv->cd(cnt+1);
      H_W_v_yptar[cnt]->Draw("COLZ"); 

      W_v_delta_Canv->cd(cnt+1); 
      H_W_v_delta[cnt]->Draw("COLZ"); 

      //==Kinematics==
      W_Canv->cd(cnt+1);
      H_W[cnt]->Draw();
      Q2_Canv->cd(cnt+1);
      H_Q2[cnt]->Draw();
      xBj_Canv->cd(cnt+1);
      H_xBj[cnt]->Draw();
      em_Canv->cd(cnt+1);
      H_em[cnt]->Draw();

      outROOT->cd();
      outROOT->Write();

    } //end run number loop

  cout << "Ended Final Run Loop .. . ." << endl;

  //Save Canvas
  
  //===Calibration Checks
  hod_Canv->SaveAs("hodoBeta.pdf");
  cal_Canv->SaveAs("caloEtrkNorm.pdf"); 
  dcDist_Canv->SaveAs("dcDist.pdf");

  dcResMean_Canv->SaveAs("dcResidual_Mean.pdf");                                                                       
  dcResSigma_Canv->SaveAs("dcResidual_Sigma.pdf"); 

  //====Focal Plane=====
  xfp_v_yfp_Canv->SaveAs("xfp_v_yfp_plots.pdf");  
  W_v_xfp_Canv->SaveAs("W_v_xfp_plots.pdf");
  W_v_xpfp_Canv->SaveAs("W_v_xpfp_plots.pdf");
  W_v_yfp_Canv->SaveAs("W_v_yfp_plots.pdf");
  W_v_ypfp_Canv->SaveAs("W_v_ypfp_plots.pdf");

  //=====Target=======
  W_v_ytar_Canv->SaveAs("W_v_ytar_plots.pdf");
  W_v_yptar_Canv->SaveAs("W_v_yptar_plots.pdf"); 
  W_v_delta_Canv->SaveAs("W_v_delta_plots.pdf"); 

  //===Kinematics====
  W_Canv->SaveAs("InvariantMass.pdf");
  Q2_Canv->SaveAs("Q2.pdf");
  xBj_Canv->SaveAs("xBj.pdf");
  em_Canv->SaveAs("Em.pdf");
  
  //===Fit W projection Graphs===
  fitGrph_XfpMean_Canv->SaveAs("fit_W_XfpProjGraph.pdf");
  fitGrph_XpfpMean_Canv->SaveAs("fit_W_XpfpProjGraph.pdf");
  fitGrph_YfpMean_Canv->SaveAs("fit_W_YfpProjGraph.pdf");
  fitGrph_YpfpMean_Canv->SaveAs("fit_W_YpfpProjGraph.pdf");

  fitGrph_YtarMean_Canv->SaveAs("fit_W_YtarProjGraph.pdf"); 
  fitGrph_YptarMean_Canv->SaveAs("fit_W_YptarProjGraph.pdf");
  fitGrph_DeltaMean_Canv->SaveAs("fit_W_DeltaProjGraph.pdf");

  outROOT->Close();
  
}
