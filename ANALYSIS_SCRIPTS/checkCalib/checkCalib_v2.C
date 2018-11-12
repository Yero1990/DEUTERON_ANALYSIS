//Script to check if the detectors are calibrated properly
#include <sys/stat.h>
#include "checkCalib.h"

void checkCalib_v2(string detector, int run)
{

  //the user may input the following for detector: "dc", "cal", "hod", "cer"
  
  //Prevent plot display
  gROOT->SetBatch(kTRUE);
  

  //Create a directory where to store the plots and output root file
  mkdir(Form("./%s_Calib_%d", detector.c_str(), run), S_IRWXU);

  
  //=============================
  //INITIALIZE HISTOGRAM BINNING
  //=============================

  //HMS			                     //SHMS			     
  hcalEtrkNorm_nbins = 100,         	     pcalEtrkNorm_nbins = 100  ;
  hcalEtrkNorm_xmin = 0.001, 		     pcalEtrkNorm_xmin = 0.001 ;
  hcalEtrkNorm_xmax = 2.0,   		     pcalEtrkNorm_xmax = 2.0;   
			     		   			     
  hcalEtot_nbins = 100,      		     pcalEtot_nbins = 100;      
  hcalEtot_xmin = 0.001,     		     pcalEtot_xmin = 0.001;     
  hcalEtot_xmax = 3.0,	     		     pcalEtot_xmax = 3.0;	     
			     		   			     
  hcalXtrk_nbins = 100,      		     pcalXtrk_nbins = 100;      
  hcalXtrk_xmin = -50, 	     		     pcalXtrk_xmin = -50; 	     
  hcalXtrk_xmax = 50,  	     		     pcalXtrk_xmax = 50;  	     
  			     		     			     
  hcalYtrk_nbins = 100,      		     pcalYtrk_nbins = 100;      
  hcalYtrk_xmin = -50, 	     		     pcalYtrk_xmin = -50; 	     
  hcalYtrk_xmax = 50, 	     		     pcalYtrk_xmax = 50; 	     
  			     		     			     
  hdcTime_nbins = 300,	     		     pdcTime_nbins = 300;	     
  hdcTime_xmin = -50.,	     		     pdcTime_xmin = -50.;	     
  hdcTime_xmax = 250.,	     		     pdcTime_xmax = 250.;	     
  			     		     			     
  hdcRes_nbins = 100.,	     		     pdcRes_nbins = 100.;	     
  hdcRes_xmin = -0.1,	     		     pdcRes_xmin = -0.1;	     
  hdcRes_xmax = 0.1,	     		     pdcRes_xmax = 0.1;	     
  			     		     			     
  hdcDist_nbins = 70.,	     		     pdcDist_nbins = 70.;	     
  hdcDist_xmin = -0.1,	     		     pdcDist_xmin = -0.1;	     
  hdcDist_xmax = 0.6,	     		     pdcDist_xmax = 0.6;	     
			     		   			     
  hhodBeta_nbins = 100,	     		     phodBeta_nbins = 100;	     
  hhodBeta_xmin = 0.3,	     		     phodBeta_xmin = 0.3;	     
  hhodBeta_xmax = 1.6,	     		     phodBeta_xmax = 1.6;	     
  			     		     			     
  hhodXtrk_nbins = 80,	     		     phodXtrk_nbins = 80;	     
  hhodXtrk_xmin = -60,	     		     phodXtrk_xmin = -60;	     
  hhodXtrk_xmax = 60,	     		     phodXtrk_xmax = 60;	     
			     		   			     
  hhodYtrk_nbins = 80,	     		     phodYtrk_nbins = 80;	     
  hhodYtrk_xmin = -60,	     		     phodYtrk_xmin = -60;	     
  hhodYtrk_xmax = 60,	     		     phodYtrk_xmax = 60;	     
  			     		     			     
  hcer_nbins = 100,	     		     phgcer_nbins = 100,  pngcer_nbins = 100;	     
  hcer_xmin = 0,	     		     phgcer_xmin = 0, 	 pngcer_xmin = 0;     
  hcer_xmax = 20,           		     phgcer_xmax = 20,   pngcer_xmax = 20;        


  //=========================
  //====OPEN ROOT FILE=======
  //=========================
  TString filename = "../../../ROOTfiles/coin_replay_coin_all_3288_20000.root";


  TFile *data_file = new TFile(filename, "READ");
  TTree *T = (TTree*)data_file->Get("T");
  

  //Create output root file where histograms will be stored
  TFile *outROOT = new TFile(Form("./%s_Calib_%d/hms_%sCalib_histos%d.root", detector.c_str(), run, detector.c_str(), run), "recreate");


  //===========================
  //===Set Branch Address======
  //===========================

  nhdc_res = "H.dc.residualExclPlane";	       npdc_res = "P.dc.residualExclPlane";	     
  nhhod_beta = "H.hod.beta";		       nphod_beta = "P.hod.beta";		     
  nhhod_beta_notrk = "H.hod.betanotrack";      nphod_beta_notrk = "P.hod.betanotrack";    
  					       					     
  nhcer_npesum = "H.cer.npeSum";	       nphgcer_npesum = "P.hgcer.npeSum";    npngcer_npesum = "P.ngcer.npeSum";	     
  nhcer_npe = "H.cer.npe";		       nphgcer_npe = "P.hgcer.npe";	     npngcer_npe = "P.ngcer.npe";	     
					     					     
  nhcal_etot = "H.cal.etot";	     	       npcal_etot = "P.cal.etot";	     	     
  nhcal_etrknorm = "H.cal.etracknorm"; 	       npcal_etrknorm = "P.cal.etracknorm"; 	     
  nhcal_xtrack = "H.cal.xtrack";	       npcal_xtrack = "P.cal.xtrack";	     
  nhcal_ytrack = "H.cal.ytrack";               npcal_ytrack = "P.cal.ytrack";             
    



  //Initialize Some Histograms
  //===HMS====
  H_hhodBeta = new TH1F("hHod_Beta", "HMS Hodoscope Beta w/ Tracking", hhodBeta_nbins, hhodBeta_xmin, hhodBeta_xmax);
  H_hhodBetaNoTrk = new TH1F("hHod_Beta_noTracks", "HMS Hodoscope Beta w/out Tracking", hhodBeta_nbins, hhodBeta_xmin, hhodBeta_xmax);
  H_hcalEtrkNorm = new TH1F("hCal_eTrkNorm", "HMS Calorimeter Normalized Track Energy", hcalEtrkNorm_nbins, hcalEtrkNorm_xmin, hcalEtrkNorm_xmax);
  H_hcalEtot = new TH1F("hCal_eTot", "HMS Calorimeter Total Energy", hcalEtot_nbins, hcalEtot_xmin, hcalEtot_xmax);
  H_hcalEtrkNorm_vs_xtrk = new TH2F("hCal_eTrkNorm_v_xtrack", "HMS Norm. Trk E v. xTrack", hcalXtrk_nbins, hcalXtrk_xmin, hcalXtrk_xmax, hcalEtrkNorm_nbins, hcalEtrkNorm_xmin, hcalEtrkNorm_xmax);
  H_hcalEtrkNorm_vs_ytrk = new TH2F("hCal_eTrkNorm_v_ytrack", "HMS Norm. Trk E v. yTrack", hcalYtrk_nbins, hcalYtrk_xmin, hcalYtrk_xmax, hcalEtrkNorm_nbins, hcalEtrkNorm_xmin, hcalEtrkNorm_xmax);
  H_hcerNpeSum = new TH1F("hCer_npeSum", "HMS Cherenkov Total P.E. Sum", hcer_nbins, hcer_xmin, hcer_xmax);
  //===SHMS===
  H_phodBeta = new TH1F("pHod_Beta", "SHMS Hodoscope Beta w/ Tracking", phodBeta_nbins, phodBeta_xmin, phodBeta_xmax);
  H_phodBetaNoTrk = new TH1F("pHod_Beta_noTracks", "SHMS Hodoscope Beta w/out Tracking", phodBeta_nbins, phodBeta_xmin, phodBeta_xmax);
  H_pcalEtrkNorm = new TH1F("pCal_eTrkNorm", "SHMS Calorimeter Normalized Track Energy", pcalEtrkNorm_nbins, pcalEtrkNorm_xmin, pcalEtrkNorm_xmax);
  H_pcalEtot = new TH1F("pCal_eTot", "SHMS Calorimeter Total Energy", pcalEtot_nbins, pcalEtot_xmin, pcalEtot_xmax);
  H_pcalEtrkNorm_vs_xtrk = new TH2F("pCal_eTrkNorm_v_xtrack", "SHMS Norm. Trk E v. xTrack", pcalXtrk_nbins, pcalXtrk_xmin, pcalXtrk_xmax, pcalEtrkNorm_nbins, pcalEtrkNorm_xmin, pcalEtrkNorm_xmax);
  H_pcalEtrkNorm_vs_ytrk = new TH2F("pCal_eTrkNorm_v_ytrack", "SHMS Norm. Trk E v. yTrack", pcalYtrk_nbins, pcalYtrk_xmin, pcalYtrk_xmax, pcalEtrkNorm_nbins, pcalEtrkNorm_xmin, pcalEtrkNorm_xmax);  
  H_phgcerNpeSum = new TH1F("phgCer_npeSum", "SHMS HGCER Total P.E. Sum", phgcer_nbins, phgcer_xmin, phgcer_xmax);
  H_pngcerNpeSum = new TH1F("pngCer_npeSum", "SHMS NGCER Total P.E. Sum", pngcer_nbins, pngcer_xmin, pngcer_xmax);


  //Set Branch Address for Hodo, Calo, and Cherenkov
  //HMS
  T->SetBranchAddress(nhhod_beta, &hhod_beta);
  T->SetBranchAddress(nhhod_beta_notrk, &hhod_beta_notrk);
  T->SetBranchAddress(nhcer_npesum, &hcer_npesum);
  T->SetBranchAddress(nhcal_etot, &hcal_etot);
  T->SetBranchAddress(nhcal_etrknorm, &hcal_etrknorm);
  T->SetBranchAddress(nhcal_xtrack, &hcal_xtrack);
  T->SetBranchAddress(nhcal_ytrack, &hcal_ytrack);
  //SHMS
  T->SetBranchAddress(nphod_beta, &phod_beta);
  T->SetBranchAddress(nphod_beta_notrk, &phod_beta_notrk);
  T->SetBranchAddress(nphgcer_npesum, &phgcer_npesum);
  T->SetBranchAddress(npngcer_npesum, &pngcer_npesum);
  T->SetBranchAddress(npcal_etot, &pcal_etot);
  T->SetBranchAddress(npcal_etrknorm, &pcal_etrknorm);
  T->SetBranchAddress(npcal_xtrack, &pcal_xtrack);
  T->SetBranchAddress(npcal_ytrack, &pcal_ytrack);



  //Loop over DC Planes
  for (Int_t npl = 0; npl < dc_PLANES; npl++ )
    {
      x[npl] = npl+1;  //set x-axis for use with TGraph
      
      //Initialize DC Histograms
      
      //HMS DC
      H_hdcDist[npl] = new TH1F(Form("hDC_%s_DriftDist", hdc_pl_names[npl].c_str()), Form("HMS DC Drift Distance, Plane %s", hdc_pl_names[npl].c_str()), hdcDist_nbins, hdcDist_xmin, hdcDist_xmax);
      H_hdcDist[npl]->GetXaxis()->SetTitle("Drift Distance (cm) ");
      H_hdcDist[npl]->GetXaxis()->CenterTitle();
      H_hdcDist[npl]->GetYaxis()->SetTitle("Counts");
      H_hdcDist[npl]->GetYaxis()->CenterTitle();
      
      H_hdcTime[npl] = new TH1F(Form("hDC_%s_DriftTime", hdc_pl_names[npl].c_str()), Form("HMS DC Drift Time, Plane %s", hdc_pl_names[npl].c_str()), hdcTime_nbins, hdcTime_xmin, hdcTime_xmax);
      H_hdcTime[npl]->GetXaxis()->SetTitle("Drift Time (ns) ");
      H_hdcTime[npl]->GetXaxis()->CenterTitle();
      H_hdcTime[npl]->GetYaxis()->SetTitle("Counts");
      H_hdcTime[npl]->GetYaxis()->CenterTitle();
      
      H_hdcRes[npl] = new TH1F(Form("hDC_%s_DriftResiduals", hdc_pl_names[npl].c_str()), Form("HMS DC Residuals, Plane %s", hdc_pl_names[npl].c_str()), hdcRes_nbins, hdcRes_xmin, hdcRes_xmax);
      H_hdcRes[npl]->GetXaxis()->SetTitle("Drift Residuals (cm) ");
      H_hdcRes[npl]->GetXaxis()->CenterTitle();
      H_hdcRes[npl]->GetYaxis()->SetTitle("Counts");
      H_hdcRes[npl]->GetYaxis()->CenterTitle();
      
      //SHMS DC
      H_pdcDist[npl] = new TH1F(Form("pDC_%s_DriftDist", pdc_pl_names[npl].c_str()), Form("SHMS DC Drift Distance, Plane %s", pdc_pl_names[npl].c_str()), pdcDist_nbins, pdcDist_xmin, pdcDist_xmax);
      H_pdcDist[npl]->GetXaxis()->SetTitle("Drift Distance (cm) ");
      H_pdcDist[npl]->GetXaxis()->CenterTitle();
      H_pdcDist[npl]->GetYaxis()->SetTitle("Counts");
      H_pdcDist[npl]->GetYaxis()->CenterTitle();
      
      H_pdcTime[npl] = new TH1F(Form("pDC_%s_DriftTime", pdc_pl_names[npl].c_str()), Form("SHMS DC Drift Time, Plane %s", pdc_pl_names[npl].c_str()), pdcTime_nbins, pdcTime_xmin, pdcTime_xmax);
      H_pdcTime[npl]->GetXaxis()->SetTitle("Drift Time (ns) ");
      H_pdcTime[npl]->GetXaxis()->CenterTitle();
      H_pdcTime[npl]->GetYaxis()->SetTitle("Counts");
      H_pdcTime[npl]->GetYaxis()->CenterTitle();
      
      H_pdcRes[npl] = new TH1F(Form("pDC_%s_DriftResiduals", pdc_pl_names[npl].c_str()), Form("SHMS DC Residuals, Plane %s", pdc_pl_names[npl].c_str()), pdcRes_nbins, pdcRes_xmin, pdcRes_xmax);
      H_pdcRes[npl]->GetXaxis()->SetTitle("Drift Residuals (cm) ");
      H_pdcRes[npl]->GetXaxis()->CenterTitle();
      H_pdcRes[npl]->GetYaxis()->SetTitle("Counts");
      H_pdcRes[npl]->GetYaxis()->CenterTitle();


      //2D Histos
      //HMS
      H_hres_vs_wire[npl] = new TH2F(Form("hRes_vs_Wire, %s", hdc_pl_names[npl].c_str()), Form("HMS DC Residuals vs. Wire, Plane %s", hdc_pl_names[npl].c_str()), hnwires[npl], 0., hnwires[npl], hdcRes_nbins, hdcRes_xmin, hdcRes_xmax);
      H_hres_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_hres_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_hres_vs_wire[npl]->GetYaxis()->SetTitle("Drift Residuals (cm)");
      H_hres_vs_wire[npl]->GetYaxis()->CenterTitle();
      
      H_htime_vs_wire[npl] = new TH2F(Form("hTime_vs_Wire, %s", hdc_pl_names[npl].c_str()), Form("HMS DC Time vs. Wire, Plane %s", hdc_pl_names[npl].c_str()), hnwires[npl], 0., hnwires[npl], hdcTime_nbins, hdcTime_xmin, hdcTime_xmax);
      H_htime_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_htime_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_htime_vs_wire[npl]->GetYaxis()->SetTitle("Drift Time (ns)");
      H_htime_vs_wire[npl]->GetYaxis()->CenterTitle();
      
      H_hdist_vs_wire[npl] = new TH2F(Form("hDist_vs_Wire, %s", hdc_pl_names[npl].c_str()), Form("HMS DC Distance vs. Wire, Plane %s", hdc_pl_names[npl].c_str()), hnwires[npl], 0., hnwires[npl], hdcDist_nbins, hdcDist_xmin, hdcDist_xmax);
      H_hdist_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_hdist_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_hdist_vs_wire[npl]->GetYaxis()->SetTitle("Drift Distance (cm)");
      H_hdist_vs_wire[npl]->GetYaxis()->CenterTitle();
    
      //SHMS
      H_pres_vs_wire[npl] = new TH2F(Form("pRes_vs_Wire, %s", pdc_pl_names[npl].c_str()), Form("SHMS DC Residuals vs. Wire, Plane %s", pdc_pl_names[npl].c_str()), pnwires[npl], 0., pnwires[npl], pdcRes_nbins, pdcRes_xmin, pdcRes_xmax);
      H_pres_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_pres_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_pres_vs_wire[npl]->GetYaxis()->SetTitle("Drift Residuals (cm)");
      H_pres_vs_wire[npl]->GetYaxis()->CenterTitle();
      
      H_ptime_vs_wire[npl] = new TH2F(Form("pTime_vs_Wire, %s", pdc_pl_names[npl].c_str()), Form("SHMS DC Time vs. Wire, Plane %s", pdc_pl_names[npl].c_str()), pnwires[npl], 0., pnwires[npl], pdcTime_nbins, pdcTime_xmin, pdcTime_xmax);
      H_ptime_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_ptime_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_ptime_vs_wire[npl]->GetYaxis()->SetTitle("Drift Time (ns)");
      H_ptime_vs_wire[npl]->GetYaxis()->CenterTitle();
      
      H_pdist_vs_wire[npl] = new TH2F(Form("pDist_vs_Wire, %s", pdc_pl_names[npl].c_str()), Form("SHMS DC Distance vs. Wire, Plane %s", pdc_pl_names[npl].c_str()), pnwires[npl], 0., pnwires[npl], pdcDist_nbins, pdcDist_xmin, pdcDist_xmax);
      H_pdist_vs_wire[npl]->GetXaxis()->SetTitle("Wire Number ");
      H_pdist_vs_wire[npl]->GetXaxis()->CenterTitle();
      H_pdist_vs_wire[npl]->GetYaxis()->SetTitle("Drift Distance (cm)");
      H_pdist_vs_wire[npl]->GetYaxis()->CenterTitle();

      //===HMS===
      //----Define TTree Leaf Names-----
      base = "H.dc." + hdc_pl_names[npl];
      nhdc_time = base + "." + "time";
      nhdc_wire = base + "." + "wirenum";
      nhdc_dist = base + "." + "dist";
      nhdc_nhit = base + "." + "nhit";
      nhdc_ndata = "Ndata." + base + "." + "time";
      
      //------Set Branch Address-------
      T->SetBranchAddress(nhdc_ndata, &hdc_ndata[npl]);
      T->SetBranchAddress(nhdc_time, hdc_time[npl]);
      T->SetBranchAddress(nhdc_wire, hdc_wire[npl]);
      T->SetBranchAddress(nhdc_dist, hdc_dist[npl]);
      T->SetBranchAddress(nhdc_nhit, &hdc_nhit[npl]);
      T->SetBranchAddress("H.dc.residualExclPlane", &hdc_res[0]);
         
      //===SHMS===
      //----Define TTree Leaf Names-----
      base = "P.dc." + pdc_pl_names[npl];
      npdc_time = base + "." + "time";
      npdc_wire = base + "." + "wirenum";
      npdc_dist = base + "." + "dist";
      npdc_nhit = base + "." + "nhit";
      npdc_ndata = "Ndata." + base + "." + "time";
      
      //------Set Branch Address-------
      T->SetBranchAddress(npdc_ndata, &pdc_ndata[npl]);
      T->SetBranchAddress(npdc_time, pdc_time[npl]);
      T->SetBranchAddress(npdc_wire, pdc_wire[npl]);
      T->SetBranchAddress(npdc_dist, pdc_dist[npl]);
      T->SetBranchAddress(npdc_nhit, &pdc_nhit[npl]);
      T->SetBranchAddress("P.dc.residualExclPlane", &pdc_res[0]);

      

    } //end dc plane loop
  
  //Loop over HODO Planes
  for (Int_t npl = 0; npl < hod_PLANES; npl++ )
    {
      
      //Initialize HMS HODO Histograms
      H_hhodBeta_v_Xtrk[npl] = new TH2F(Form("hHod_%s_Beta_v_Xtrk", hod_pl_names[npl].c_str()), Form("HMS Hodo Beta vs. X-track, Plane %s", hod_pl_names[npl].c_str()), hhodXtrk_nbins, hhodXtrk_xmin, hhodXtrk_xmax,  hhodBeta_nbins, hhodBeta_xmin, hhodBeta_xmax);
      H_hhodBeta_v_Xtrk[npl]->GetXaxis()->SetTitle("Hodoscope X-Track (cm)");
      H_hhodBeta_v_Xtrk[npl]->GetXaxis()->CenterTitle();
      H_hhodBeta_v_Xtrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
      H_hhodBeta_v_Xtrk[npl]->GetYaxis()->CenterTitle();
      
      H_hhodBeta_v_Ytrk[npl] = new TH2F(Form("hHod_%s_Beta_v_Ytrk", hod_pl_names[npl].c_str()), Form("HMS Hodo Beta vs. Y-track, Plane %s", hod_pl_names[npl].c_str()), hhodYtrk_nbins, hhodYtrk_xmin, hhodYtrk_xmax,  hhodBeta_nbins, hhodBeta_xmin, hhodBeta_xmax);
      H_hhodBeta_v_Ytrk[npl]->GetXaxis()->SetTitle("Hodoscope Y-Track (cm)");
      H_hhodBeta_v_Ytrk[npl]->GetXaxis()->CenterTitle();
      H_hhodBeta_v_Ytrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
      H_hhodBeta_v_Ytrk[npl]->GetYaxis()->CenterTitle();
      
      //Initialize SHMS HODO Histograms
      H_phodBeta_v_Xtrk[npl] = new TH2F(Form("pHod_%s_Beta_v_Xtrk", hod_pl_names[npl].c_str()), Form("SHMS Hodo Beta vs. X-track, Plane %s", hod_pl_names[npl].c_str()), phodXtrk_nbins, phodXtrk_xmin, phodXtrk_xmax,  phodBeta_nbins, phodBeta_xmin, phodBeta_xmax);
      H_phodBeta_v_Xtrk[npl]->GetXaxis()->SetTitle("Hodoscope X-Track (cm)");
      H_phodBeta_v_Xtrk[npl]->GetXaxis()->CenterTitle();
      H_phodBeta_v_Xtrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
      H_phodBeta_v_Xtrk[npl]->GetYaxis()->CenterTitle();
      
      H_phodBeta_v_Ytrk[npl] = new TH2F(Form("pHod_%s_Beta_v_Ytrk", hod_pl_names[npl].c_str()), Form("SHMS Hodo Beta vs. Y-track, Plane %s", hod_pl_names[npl].c_str()), phodYtrk_nbins, phodYtrk_xmin, phodYtrk_xmax,  phodBeta_nbins, phodBeta_xmin, phodBeta_xmax);
      H_phodBeta_v_Ytrk[npl]->GetXaxis()->SetTitle("Hodoscope Y-Track (cm)");
      H_phodBeta_v_Ytrk[npl]->GetXaxis()->CenterTitle();
      H_phodBeta_v_Ytrk[npl]->GetYaxis()->SetTitle("Hodoscope Beta");
      H_phodBeta_v_Ytrk[npl]->GetYaxis()->CenterTitle();

      //----Define HMS TTree Leaf Names-----
      base = "H.hod." + hod_pl_names[npl];
      nhhod_xtrack = "H.hod." + hod_pl_names[npl] + ".TrackXPos";
      nhhod_ytrack = "H.hod." + hod_pl_names[npl] + ".TrackYPos";
      
      //------Set HMS Branch Address-------
      T->SetBranchAddress(nhhod_xtrack, &hhod_xtrack[npl]);
      T->SetBranchAddress(nhhod_ytrack, &hhod_ytrack[npl]);
      
      
      //----Define SHMS TTree Leaf Names-----
      base = "P.hod." + hod_pl_names[npl];
      nphod_xtrack = "P.hod." + hod_pl_names[npl] + ".TrackXPos";
      nphod_ytrack = "P.hod." + hod_pl_names[npl] + ".TrackYPos";
      
      //------Set SHMS Branch Address-------
      T->SetBranchAddress(nphod_xtrack, &phod_xtrack[npl]);
      T->SetBranchAddress(nphod_ytrack, &phod_ytrack[npl]);
    

      if(npl==0)
	{
	  //Loop over Cherenkov PMTs
	  for (int ipmt = 0; ipmt < 4; ipmt++)
	    {
	      //Initialize HGC/NGC Histos
	      H_phgcerNpe[ipmt] = new TH1F(Form("pHGCER_pmt%d", ipmt+1), Form("SHMS HGC PMT %d", ipmt+1), phgcer_nbins, phgcer_xmin, phgcer_xmax);
	      H_pngcerNpe[ipmt] = new TH1F(Form("pNGCER_pmt%d", ipmt+1), Form("SHMS NGC PMT %d", ipmt+1), pngcer_nbins, pngcer_xmin, pngcer_xmax);
     

	      //------Set Branch Address-------
	      T->SetBranchAddress(nphgcer_npe, &phgcer_npe[ipmt]);
	      T->SetBranchAddress(npngcer_npe, &pngcer_npe[ipmt]);

	      //HMS Gas Cherenkov
	      if(ipmt<2)
		{
		  H_hcerNpe[ipmt] = new TH1F(Form("hCER_pmt%d", ipmt+1), Form("HMS Cherenkov PMT %d", ipmt+1), hcer_nbins, hcer_xmin, hcer_xmax);

		  //------Set Branch Address-------
		  T->SetBranchAddress(nhcer_npe, &hcer_npe[ipmt]);

		} //end HMS Cer PMT Loop

	      
	    } //end SHMS Cer PMT Loop
	  
	

	} //end Plane==0 requirement, for cer pmt loop

    } //end hodo plane loop
  
  

  //==============================
  //=====LOOP OVER ALL EVENTS=====
  //==============================
  
  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<nentries; i++)
    {
      
      T->GetEntry(i);  

    }



  /*

 

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

      dcTimeCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Times.pdf", detector.c_str(), run));
      dcDistCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Dist.pdf", detector.c_str(), run));
      dcResCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_Res.pdf", detector.c_str(), run));
      
      dcResCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Res2D.pdf", detector.c_str(), run));
      dcTimeCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Time2D.pdf", detector.c_str(), run));
      dcDistCanv2D->SaveAs(Form("./%s_Calib_%d/HMS_DC_Dist2D.pdf", detector.c_str(), run));
      
      
      dcResCanvProf->SaveAs(Form("./%s_Calib_%d/HMS_DC_ResProfile.pdf", detector.c_str(), run));
      dcResGraphCanv->SaveAs(Form("./%s_Calib_%d/HMS_DC_ResPlot.pdf", detector.c_str(), run));
      
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

      calEtrkNormCanv->SaveAs(Form("./%s_Calib_%d/Calorimeter_CalibPlots.pdf", detector.c_str(), run));
      
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

      hodCanv->SaveAs(Form("./%s_Calib_%d/HodBetaPlots.pdf", detector.c_str(), run));
      hodCanv2D->SaveAs(Form("./%s_Calib_%d/HodBeta2DPlots.pdf", detector.c_str(), run));
      hodProfCanv->SaveAs(Form("./%s_Calib_%d/HodBetaProfilePlots.pdf", detector.c_str(), run));
    }
  
 //Write Histograms to ROOT file
  outROOT->Write();
  outROOT->Close();
*/
  
}


