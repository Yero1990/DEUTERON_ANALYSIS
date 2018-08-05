//Script to check if the detectors are calibrated properly


void checkCalib(string detector, int runNUM)
{

  //the user may input the following for detector: "dc", "cal"

  gROOT->SetBatch(kTRUE);
  // TString filename = "../../ROOTfiles/hms_replay_cal_calib_1263_100000.root";
  TString filename = "../../ROOTfiles/hms_replay_dc_calib_1161_-1.root";


  //read the file and get the tree
  TFile *data_file = new TFile(filename, "READ");
  TTree *T = (TTree*)data_file->Get("T");
  
  

  //Create a directory where to store the plots and output root file
  const char* dir_log = Form("mkdir -p ./%s_Calib_%d/", detector.c_str(), runNUM);
  
  //Check if directory exists
  if (system(dir_log) != 0) 
    {
      cout << "Creating Directory to store HMS Calibration Results . . ." << endl; 
      system(dir_log);  //create directory to log calibration results
    }


  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("./%s_Calib_%d/hms_%sCalib_histos%d.root", detector.c_str(), runNUM, detector.c_str(), runNUM), "recreate");

  //Set Histogram Binning
  Double_t dcTime_nbins, dcTime_xmin, dcTime_xmax;
  Double_t dcDist_nbins, dcDist_xmin, dcDist_xmax;
  Double_t dcRes_nbins, dcRes_xmin, dcRes_xmax;

  Double_t hodBeta_nbins, hodBeta_xmin, hodBeta_xmax;
  Double_t hodXtrk_nbins, hodXtrk_xmin, hodXtrk_xmax;  
  Double_t hodYtrk_nbins, hodYtrk_xmin, hodYtrk_xmax;  
  
  Double_t calEtrkNorm_nbins, calEtrkNorm_xmin, calEtrkNorm_xmax;
  Double_t calEtot_nbins, calEtot_xmin, calEtot_xmax;
  Double_t calXtrk_nbins, calXtrk_xmin, calXtrk_xmax;  
  Double_t calYtrk_nbins, calYtrk_xmin, calYtrk_xmax; 

  calEtrkNorm_nbins = 100  ;
  calEtrkNorm_xmin = 0.001 ; 
  calEtrkNorm_xmax = 2.0;

  calEtot_nbins = 100; 
  calEtot_xmin = 0.001; 
  calEtot_xmax = 3.0;

  calXtrk_nbins = 100; 
  calXtrk_xmin = -50; 
  calXtrk_xmax = 50;  
  
  calYtrk_nbins = 100; 
  calYtrk_xmin = -50; 
  calYtrk_xmax = 50; 
  
  dcTime_nbins = 300;
  dcTime_xmin = -50.;
  dcTime_xmax = 250.;
  
  dcRes_nbins = 100.;
  dcRes_xmin = -0.1;
  dcRes_xmax = 0.1;
  
  dcDist_nbins = 70.;
  dcDist_xmin = -0.1;
  dcDist_xmax = 0.6;

  hodBeta_nbins = 100;
  hodBeta_xmin = 0.3;
  hodBeta_xmax = 1.6;
  
  hodXtrk_nbins = 80;
  hodXtrk_xmin = -60;
  hodXtrk_xmax = 60;

  hodYtrk_nbins = 80;
  hodYtrk_xmin = -60;
  hodYtrk_xmax = 60;
  
  //Define Fixed Quantities
  static const Int_t dcPLANES = 12;
  static const Int_t hodPLANES = 4;
  string dc_pl_names[dcPLANES] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  string hod_pl_names[hodPLANES] = {"1x", "1y", "2x", "2y"};
  Int_t nwires[dcPLANES] = {96, 96, 102, 102, 96, 96, 96, 96, 102, 102, 96, 96};
  Int_t maxBar[hodPLANES] = {16, 10, 16, 10};
 
  //Define Canvas

  //==HODOSCOPES===
  TCanvas *hodCanv;
  TCanvas *hodCanv2D;
  TCanvas *hodProfCanv;

  //==DRIFT CHAMBERS===
  TCanvas *dcTimeCanv;
  TCanvas *dcDistCanv;
  TCanvas *dcResCanv;
  TCanvas *dcResGraphCanv;
  
  //Canvas to Draw 2D variales vs. wire num and Profile Histos
  TCanvas *dcResCanv2D;
  TCanvas *dcTimeCanv2D;
  TCanvas *dcDistCanv2D;
  TCanvas *dcResCanvProf;

  //==CALORIMETER===
  TCanvas *calEtrkNormCanv;

  //Define Histograms

  //===DRIFT CHAMBERS====
  TH1F *H_dcDist[dcPLANES];
  TH1F *H_dcTime[dcPLANES];
  TH1F *H_dcRes[dcPLANES];
  
  TH2F *H_res_vs_wire[dcPLANES];
  TH2F *H_time_vs_wire[dcPLANES];
  TH2F *H_dist_vs_wire[dcPLANES];
  
  TProfile *dcResProf[dcPLANES];

  //==CALORIMETER HISTOGRAMS===
  TH1F *H_calEtrkNorm;
  TH1F *H_calEtot;
  TH2F *H_calEtrkNorm_vs_xtrk;
  TH2F *H_calEtrkNorm_vs_ytrk;

  //===HODOSCOPES===
  TH1F *H_hodBeta;
  TH1F *H_hodBetaNoTrk;
  TH2F *H_hodBeta_v_Xtrk[hodPLANES];
  TH2F *H_hodBeta_v_Ytrk[hodPLANES];

  //Profile Histos of beta vs. xtrk (or ytrk)
  TProfile *hod_xProfX[hodPLANES];
  TProfile *hod_yProfX[hodPLANES];

  if (detector=="hod")
    {
      H_hodBeta = new TH1F("Hodoscope Beta", "Hodoscope Beta w/ Tracking", hodBeta_nbins, hodBeta_xmin, hodBeta_xmax);
      H_hodBetaNoTrk = new TH1F("Hodoscope Beta noTracks", "Hodoscope Beta w/out Tracking", hodBeta_nbins, hodBeta_xmin, hodBeta_xmax);
  
    }

  if (detector=="cal")
    {
      H_calEtrkNorm = new TH1F("Calorimeter eTrkNorm", "Calorimeter Normalized Track Energy", calEtrkNorm_nbins, calEtrkNorm_xmin, calEtrkNorm_xmax);
      H_calEtot = new TH1F("Calorimeter eTot", "Calorimeter Total Energy", calEtot_nbins, calEtot_xmin, calEtot_xmax);
      H_calEtrkNorm_vs_xtrk = new TH2F("eTrkNorm_v_xtrack", "Norm. Trk E v. xTrack", calXtrk_nbins, calXtrk_xmin, calXtrk_xmax, calEtrkNorm_nbins, calEtrkNorm_xmin, calEtrkNorm_xmax);
      H_calEtrkNorm_vs_ytrk = new TH2F("eTrkNorm_v_ytrack", "Norm. Trk E v. yTrack", calYtrk_nbins, calYtrk_xmin, calYtrk_xmax, calEtrkNorm_nbins, calEtrkNorm_xmin, calEtrkNorm_xmax);
    }


  //Define DC/Hod/Cer/Cal Leafs to be read from TTree
  //---Names---
  TString base;
  TString ndc_wire;
  TString ndc_time;
  TString ndc_ndata;
  TString ndc_dist;
  TString ndc_nhit;
  TString ndc_res = "H.dc.residualExclPlane";
  
  TString nhod_beta = "H.hod.beta";
  TString nhod_beta_notrk = "H.hod.betanotrack";
  TString nhod_xtrack;
  TString nhod_ytrack;

  TString ncer_npe = "H.cer.npeSum";
  TString ncal_etot = "H.cal.etot";
  TString ncal_etrknorm = "H.cal.etracknorm";
  TString ncal_xtrack = "H.cal.xtrack";
  TString ncal_ytrack = "H.cal.ytrack";


  //--Variables
  Double_t dc_wire[dcPLANES][1000];
  Double_t dc_time[dcPLANES][1000];
  Int_t dc_ndata[dcPLANES];
  Double_t dc_dist[dcPLANES][1000];
  Double_t dc_res[dcPLANES]; 
  Double_t dc_nhit[dcPLANES];
  
  Double_t hod_beta;
  Double_t hod_beta_notrk;
  Double_t hod_xtrack[hodPLANES];
  Double_t hod_ytrack[hodPLANES];
  
  
  Double_t cer_npe;
  Double_t cal_etot;
  Double_t cal_etrknorm;
  Double_t cal_xtrack;
  Double_t cal_ytrack;

  //Set Branch Address for Hodo, Calo, and Cherenkov
  T->SetBranchAddress(nhod_beta, &hod_beta);
  T->SetBranchAddress(nhod_beta_notrk, &hod_beta_notrk);
  T->SetBranchAddress(ncer_npe, &cer_npe);
  T->SetBranchAddress(ncal_etot, &cal_etot);
  T->SetBranchAddress(ncal_etrknorm, &cal_etrknorm);
  T->SetBranchAddress(ncal_xtrack, &cal_xtrack);
  T->SetBranchAddress(ncal_ytrack, &cal_ytrack);


  //Define Mean/Sigma to be used for residuals
  Double_t mean[dcPLANES];
  Double_t sigma[dcPLANES];
  Double_t x[dcPLANES];
      


      //Loop over DC Planes
      for (Int_t npl = 0; npl < dcPLANES; npl++ )
	{
	  x[npl] = npl+1;  //set x-axis for use with TGraph
	  
	  if (detector=="dc")
	    {
	      //Initialize DC Histograms
	      H_dcDist[npl] = new TH1F(Form("DC_%s_DriftDist", dc_pl_names[npl].c_str()), Form("DC Drift Distance, Plane %s", dc_pl_names[npl].c_str()), dcDist_nbins, dcDist_xmin, dcDist_xmax);
	      H_dcDist[npl]->GetXaxis()->SetTitle("Drift Distance (cm) ");
	      H_dcDist[npl]->GetXaxis()->CenterTitle();
	      H_dcDist[npl]->GetYaxis()->SetTitle("Counts");
	      H_dcDist[npl]->GetYaxis()->CenterTitle();
	      
	      H_dcTime[npl] = new TH1F(Form("DC_%s_DriftTime", dc_pl_names[npl].c_str()), Form("DC Drift Time, Plane %s", dc_pl_names[npl].c_str()), dcTime_nbins, dcTime_xmin, dcTime_xmax);
	      H_dcTime[npl]->GetXaxis()->SetTitle("Drift Time (ns) ");
	      H_dcTime[npl]->GetXaxis()->CenterTitle();
	      H_dcTime[npl]->GetYaxis()->SetTitle("Counts");
	      H_dcTime[npl]->GetYaxis()->CenterTitle();
	      
	      H_dcRes[npl] = new TH1F(Form("DC_%s_DriftResiduals", dc_pl_names[npl].c_str()), Form("DC Residuals, Plane %s", dc_pl_names[npl].c_str()), dcRes_nbins, dcRes_xmin, dcRes_xmax);
	      H_dcRes[npl]->GetXaxis()->SetTitle("Drift Residuals (cm) ");
	      H_dcRes[npl]->GetXaxis()->CenterTitle();
	      H_dcRes[npl]->GetYaxis()->SetTitle("Counts");
	      H_dcRes[npl]->GetYaxis()->CenterTitle();
	      
	      //2D Histos
	      H_res_vs_wire[npl] = new TH2F(Form("2D: Residuals_vs_Wire, %s", dc_pl_names[npl].c_str()), Form("DC Residuals vs. Wire, Plane %s", dc_pl_names[npl].c_str()), nwires[npl], 0., nwires[npl], dcRes_nbins, dcRes_xmin, dcRes_xmax);
	      H_res_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
	      H_res_vs_wire[npl]->GetXaxis()->CenterTitle();
	      H_res_vs_wire[npl]->GetYaxis()->SetTitle("Drift Residuals (cm)");
	      H_res_vs_wire[npl]->GetYaxis()->CenterTitle();
	      
	      H_time_vs_wire[npl] = new TH2F(Form("2D: Time_vs_Wire, %s", dc_pl_names[npl].c_str()), Form("DC Time vs. Wire, Plane %s", dc_pl_names[npl].c_str()), nwires[npl], 0., nwires[npl], dcTime_nbins, dcTime_xmin, dcTime_xmax);
	      H_time_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
	      H_time_vs_wire[npl]->GetXaxis()->CenterTitle();
	      H_time_vs_wire[npl]->GetYaxis()->SetTitle("Drift Time (ns)");
	      H_time_vs_wire[npl]->GetYaxis()->CenterTitle();
	      
	      H_dist_vs_wire[npl] = new TH2F(Form("2D: Distance_vs_Wire, %s", dc_pl_names[npl].c_str()), Form("DC Distance vs. Wire, Plane %s", dc_pl_names[npl].c_str()), nwires[npl], 0., nwires[npl], dcDist_nbins, dcDist_xmin, dcDist_xmax);
	      H_dist_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
	      H_dist_vs_wire[npl]->GetXaxis()->CenterTitle();
	      H_dist_vs_wire[npl]->GetYaxis()->SetTitle("Drift Distance (cm)");
	      H_dist_vs_wire[npl]->GetYaxis()->CenterTitle();
	      
	    } //end DC requirement
	  
	  //----Define TTree Leaf Names-----
	  base = "H.dc." + dc_pl_names[npl];
	  ndc_time = base + "." + "time";
	  ndc_wire = base + "." + "wirenum";
	  ndc_dist = base + "." + "dist";
	  ndc_nhit = base + "." + "nhit";
	  ndc_ndata = "Ndata." + base + "." + "time";
	  
	  //------Set Branch Address-------
	  T->SetBranchAddress(ndc_ndata, &dc_ndata[npl]);
	  T->SetBranchAddress(ndc_time, dc_time[npl]);
	  T->SetBranchAddress(ndc_wire, dc_wire[npl]);
	  T->SetBranchAddress(ndc_dist, dc_dist[npl]);
	  T->SetBranchAddress(ndc_nhit, &dc_nhit[npl]);
	  T->SetBranchAddress("H.dc.residualExclPlane", &dc_res[0]);
	  
	} //end dc plane loop
      
      //Loop over HODO Planes
      for (Int_t npl = 0; npl < hodPLANES; npl++ )
	{
	  	  
	  if (detector=="hod")
	    {
	      //Initialize HODO Histograms
	      H_hodBeta_v_Xtrk[npl] = new TH2F(Form("HOD_%s_Beta_v_Xtrk", hod_pl_names[npl].c_str()), Form("Hodo Beta vs. X-track, Plane %s", hod_pl_names[npl].c_str()), hodXtrk_nbins, hodXtrk_xmin, hodXtrk_xmax,  hodBeta_nbins, hodBeta_xmin, hodBeta_xmax);
	      H_hodBeta_v_Xtrk[npl]->GetXaxis()->SetTitle("Hodoscope X-Track (cm)");
	      H_hodBeta_v_Xtrk[npl]->GetXaxis()->CenterTitle();
	      H_hodBeta_v_Xtrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
	      H_hodBeta_v_Xtrk[npl]->GetYaxis()->CenterTitle();
   
	      H_hodBeta_v_Ytrk[npl] = new TH2F(Form("HOD_%s_Beta_v_Ytrk", hod_pl_names[npl].c_str()), Form("Hodo Beta vs. Y-track, Plane %s", hod_pl_names[npl].c_str()), hodYtrk_nbins, hodYtrk_xmin, hodYtrk_xmax,  hodBeta_nbins, hodBeta_xmin, hodBeta_xmax);
	      H_hodBeta_v_Ytrk[npl]->GetXaxis()->SetTitle("Hodoscope Y-Track (cm)");
	      H_hodBeta_v_Ytrk[npl]->GetXaxis()->CenterTitle();
	      H_hodBeta_v_Ytrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
	      H_hodBeta_v_Ytrk[npl]->GetYaxis()->CenterTitle();
	    } //end hodo detec. requirement

	  	  //----Define TTree Leaf Names-----
	  base = "H.hod." + hod_pl_names[npl];
	  nhod_xtrack = "H.hod." + hod_pl_names[npl] + ".TrackXPos";
	  nhod_ytrack = "H.hod." + hod_pl_names[npl] + ".TrackYPos";
	  
	  //------Set Branch Address-------
	  T->SetBranchAddress(nhod_xtrack, &hod_xtrack[npl]);
	  T->SetBranchAddress(nhod_ytrack, &hod_ytrack[npl]);


	} //end hodo plane loop

  //-----LOOP OVER ALL EVENTS
  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<100000; i++)
    {
      
      T->GetEntry(i);  


      if(detector=="dc")
	{
	  
	  //Loop over all DC planes
	  for (Int_t npl = 0; npl < dcPLANES; npl++ )
	    {
	      
	      //Loop over hits
	      for (Int_t j=0; j < dc_ndata[npl]; j++)
		{
		  //Fill Histograms
		  
		  if(dc_nhit[npl]==1)
		    {
		      H_dcTime[npl]->Fill(dc_time[npl][j]);
		      H_dcDist[npl]->Fill(dc_dist[npl][j]);
		      
		      //Fill 2D Histos
		      H_res_vs_wire[npl]->Fill(dc_wire[npl][j], dc_res[npl]);
		      H_time_vs_wire[npl]->Fill(dc_wire[npl][j], dc_time[npl][j]);
		      H_dist_vs_wire[npl]->Fill(dc_wire[npl][j], dc_dist[npl][j]);
		      
		    } //end single hit requirement
		} //end loop over hits
	      
	      if(dc_nhit[npl]==1)
		{
		  H_dcRes[npl]->Fill(dc_res[npl]);
		}
	      
	    }
	  
	} //end entry loop for "dc" detector
      
      if (detector=="cal")
	{
	  H_calEtrkNorm->Fill(cal_etrknorm);
	  H_calEtot->Fill(cal_etot); 
	  H_calEtrkNorm_vs_xtrk->Fill(cal_xtrack, cal_etrknorm);
	  H_calEtrkNorm_vs_ytrk->Fill(cal_ytrack, cal_etrknorm);
	}

      
      if(detector=="hod")
	{
	  if(cal_etrknorm>0.7)
	    {
	      H_hodBeta->Fill(hod_beta);
	      H_hodBetaNoTrk->Fill(hod_beta_notrk);
	      
	      //Loop over all HODO planes
	      for (Int_t npl = 0; npl < hodPLANES; npl++ )
		{
		  
		  H_hodBeta_v_Xtrk[npl]->Fill(hod_xtrack[npl], hod_beta);
		  H_hodBeta_v_Ytrk[npl]->Fill(hod_ytrack[npl], hod_beta);
		  
		} //end hodo plane loop
	    } //end cut
	} //end hodo requirement

    } //end entry loop
  

  
  /***********DRAW HISTOGRAMS TO CANVAS***************/

  if (detector=="dc")
    {
      
      dcTimeCanv = new TCanvas("DC Times", "HMS DC TIMES",  1500, 500);
      dcTimeCanv->Divide(6,2);
      
      dcDistCanv = new TCanvas("DC Dist", "HMS DC Distance",  1500, 500);
      dcDistCanv->Divide(6,2);
      
      dcResCanv = new TCanvas("DC Residuals", "HMS DC Residuals",  1500, 500);
      dcResCanv->Divide(6,2);
      
      dcResGraphCanv = new TCanvas("DC Residuals Graph", "HMS DC Residuals Graph",  1500, 500);
      dcResGraphCanv->Divide(2,1);
      
      //2d histos 
      dcResCanv2D = new TCanvas("DC Residuals vs. Wire", "HMS DC Residuals vs. Wire",  1500, 500);
      dcResCanv2D->Divide(6,2);
      
      dcTimeCanv2D = new TCanvas("DC Time vs. Wire", "HMS DC Time vs. Wire",  1500, 500);
      dcTimeCanv2D->Divide(6,2);
      
      dcDistCanv2D = new TCanvas("DC Dist vs. Wire", "HMS DC Dist vs. Wire",  1500, 500);
      dcDistCanv2D->Divide(6,2);
      
      //Profile Histograms
      dcResCanvProf = new TCanvas("DC Residuals vs. Wire: Profile", "HMS DC Residuals vs. Wire, Profile",  1500, 500);
      dcResCanvProf->Divide(6,2);
      
      //Loop over DC planes
      for (Int_t npl = 0; npl < dcPLANES; npl++ )
	{
	  
	  dcTimeCanv->cd(npl+1);
	  gPad->SetLogy();
	  H_dcTime[npl]->Draw();
	  
	  dcDistCanv->cd(npl+1);
	  H_dcDist[npl]->Draw();
	  
	  //Get Mean/Sigma for residuals and conver to microns
	  mean[npl] =  H_dcRes[npl]->GetMean()*1e4; 
	  sigma[npl] =  H_dcRes[npl]->GetStdDev()*1e4;
	  
	  dcResCanv->cd(npl+1);
	  H_dcRes[npl]->Draw();
	  
	  //2D and Profile Histograms
	  dcResCanv2D->cd(npl+1);
	  H_res_vs_wire[npl]->Draw("COLZ");
	  
	  dcTimeCanv2D->cd(npl+1);
	  H_time_vs_wire[npl]->Draw("COLZ");
	  
	  dcDistCanv2D->cd(npl+1);
	  H_dist_vs_wire[npl]->Draw("COLZ");
	  
	  
	  dcResCanvProf->cd(npl+1);
	  dcResProf[npl] = H_res_vs_wire[npl]->ProfileX(Form("Profile of Residuals, Plane %s", dc_pl_names[npl].c_str()), 0., nwires[npl]);
	  dcResProf[npl]->Draw();
	}
      
      TGraph *gr_mean = new TGraph(12, x, mean);
      
      //Change to SupPad 2 to plot mean
      dcResGraphCanv->cd(1);
      //dcResGraphCanv->SetGrid();
      gr_mean->SetMarkerStyle(22);
      gr_mean->SetMarkerColor(kBlue);
      gr_mean->SetMarkerSize(2);
      gr_mean->GetYaxis()->SetRangeUser(-250, 250);
      
      //Set Axis Titles
      gr_mean->GetXaxis()->SetTitle("HMS DC Planes Residuals");
      gr_mean->GetXaxis()->CenterTitle();
      gr_mean->GetYaxis()->SetTitle("HMS DC Residual Mean (#mum)");
      gr_mean->GetYaxis()->CenterTitle();
      gr_mean->SetTitle("HMS DC Plane Residuals Mean");

      gr_mean->Draw("AP");

      
      //Change to SubPad 1 to plot sigma
      dcResGraphCanv->cd(2);
      TGraph *gr_residual = new TGraph(12, x, sigma);
      //dcResGraphCanv->SetGrid();
      gr_residual->SetMarkerStyle(22);
      gr_residual->SetMarkerColor(kRed);
      gr_residual->SetMarkerSize(2);
      gr_residual->GetYaxis()->SetRangeUser(0, 1000.);
      
      //Set Axis Titles
      gr_residual->GetXaxis()->SetTitle("HMS DC Planes Residuals");
      gr_residual->GetXaxis()->CenterTitle();
      gr_residual->GetYaxis()->SetTitle("HMS DC Residual #sigma (#mum)");
      gr_residual->GetYaxis()->CenterTitle();
      gr_residual->SetTitle("HMS DC Plane Residuals Sigma");
      cout << "sigma = " << sigma[0] << endl;
      gr_residual->Draw("AP");
      dcResGraphCanv->Update();

      dcTimeCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Times.pdf", detector.c_str(), runNUM));
      dcDistCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Dist.pdf", detector.c_str(), runNUM));
      dcResCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Res.pdf", detector.c_str(), runNUM));
      
      dcResCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Res2D.pdf", detector.c_str(), runNUM));
      dcTimeCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Time2D.pdf", detector.c_str(), runNUM));
      dcDistCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Dist2D.pdf", detector.c_str(), runNUM));
      
      
      dcResCanvProf->SaveAs(Form("./%s_Calib_%d/HMS_DC_ResProfile.pdf", detector.c_str(), runNUM));
      dcResGraphCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_ResPlot.pdf", detector.c_str(), runNUM));
      
    }

  if (detector=="cal")
    {

      calEtrkNormCanv = new TCanvas("Calorimeter Canv" , "Calorimeter Plots", 1500, 500);
      calEtrkNormCanv->Divide(3,2);
      
      calEtrkNormCanv->cd(1);
      H_calEtrkNorm->Draw();
      
      calEtrkNormCanv->cd(2);
      H_calEtot->Draw();
      
      calEtrkNormCanv->cd(3);
      H_calEtrkNorm_vs_xtrk->Draw("COLZ");

      calEtrkNormCanv->cd(4);
      H_calEtrkNorm_vs_ytrk->Draw("COLZ");

      calEtrkNormCanv->SaveAs(Form("./%s_Calib_%d/Calorimeter_CalibPlots.pdf", detector.c_str(), runNUM));
      
    }
  
  if (detector=="hod")
    {
      
      hodCanv = new TCanvas("Hodoscope Beta Canv" , "Hodoscope Beta Plots", 1500, 500);
      hodCanv->Divide(2,1);
      hodCanv->cd(1);
      H_hodBetaNoTrk->Draw();
      hodCanv->cd(2);
      H_hodBeta->Draw();    

      hodCanv2D = new TCanvas("Hodoscope 2D Beta Canvas" , "Hodoscope Beta Plots", 1500, 500);
      hodCanv2D->Divide(4,2);
      
      hodProfCanv = new TCanvas("Hodoscope Beta Profile Canvas", "Hodoscope Beta ProfileX", 1500, 500);
      hodProfCanv->Divide(4,2);
      
  
      //Loop over Hodo planes
      for (Int_t npl = 0; npl < hodPLANES; npl++ )
	{
	 
	  hodCanv2D->cd(npl + 1);
	  H_hodBeta_v_Xtrk[npl]->Draw("COLZ");
	  
	  hodCanv2D->cd(npl + 5);
	  H_hodBeta_v_Ytrk[npl]->Draw("COLZ");

	  //X-Profile of 2D Histos beta vs xtrk (or ytrk)
	  hod_xProfX[npl] = new TProfile();
	  hod_yProfX[npl] = new TProfile();

	  hodProfCanv->cd(npl + 1);
	  hod_xProfX[npl] = H_hodBeta_v_Xtrk[npl]->ProfileX(Form("h%s_betaXtrk_ProfileX", hod_pl_names[npl].c_str()), 0, 200);
	  hod_xProfX[npl]->Draw();
	  hodProfCanv->cd(npl + 5);
	  hod_yProfX[npl] = H_hodBeta_v_Ytrk[npl]->ProfileX(Form("h%s_betaYtrk_ProfileX", hod_pl_names[npl].c_str()), 0, 200);
	  hod_yProfX[npl]->Draw();

	}

      hodCanv->SaveAs(Form("./%s_Calib_%d/HodBetaPlots.pdf", detector.c_str(), runNUM));
      hodCanv2D->SaveAs(Form("./%s_Calib_%d/HodBeta2DPlots.pdf", detector.c_str(), runNUM));
      hodProfCanv->SaveAs(Form("./%s_Calib_%d/HodBetaProfilePlots.pdf", detector.c_str(), runNUM));
    }
  
 //Write Histograms to ROOT file
  outROOT->Write();
  outROOT->Close();

  
}


