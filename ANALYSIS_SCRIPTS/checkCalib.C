//Script to check if the detectors are calibrated properly


void checkDC_Calib(TString ROOTfile, Int_t run_num)
{
  
  //Create output root file where histograms will be stored
  //TFile *outROOT = new TFile(Form("hms_DCCalib_histos%d.root", run_num), "recreate");
  
  //read the file and get the tree
  TFile *data_file = new TFile(ROOTfile, "READ");
  TTree *T = (TTree*)data_file->Get("T");
  
  //Set Histogram Binning
  Double_t dcTime_nbins, dcTime_xmin, dcTime_xmax;
  Double_t dcDist_nbins, dcDist_xmin, dcDist_xmax;
  Double_t dcRes_nbins, dcRes_xmin, dcRes_xmax;
  
  dcTime_nbins = 300;
  dcTime_xmin = -50.;
  dcTime_xmax = 250.;
  
  dcRes_nbins = 100.;
  dcRes_xmin = -0.1;
  dcRes_xmax = 0.1;
  
  dcDist_nbins = 70.;
  dcDist_xmin = -0.1;
  dcDist_xmax = 0.6;
  
  //Define Fixed Quantities
  static const Int_t PLANES = 12;
  string dc_pl_names[12] = {"1u1", "1u2", "1x1", "1x2", "1v2", "1v1", "2v1", "2v2", "2x2", "2x1", "2u2", "2u1"};
  
  //Define Canvas
  TCanvas *dcTimeCanv;
  TCanvas *dcDistCanv;
  TCanvas *dcResCanv;
  TCanvas *dcResSigCanv;
  //Define Histograms
  TH1F *H_dcDist[PLANES];
  TH1F *H_dcTime[PLANES];
  TH1F *H_dcRes[PLANES];
  
  //Define DC Leafs to be read from TTree
  //---Names---
  TString base;
  TString ndc_time;
  TString ndc_ndata;
  TString ndc_dist;
  TString ndc_nhit;
  TString ndc_res = "H.dc.residualExclPlane";
  
  //--Variables
  Double_t dc_time[PLANES][1000];
  Int_t dc_ndata[PLANES];
  Double_t dc_dist[PLANES][1000];
  Double_t dc_res[PLANES];
  Double_t dc_nhit[PLANES];

  //Define Mean/Sigma to be used for residuals
  Double_t mean[PLANES];
  Double_t sigma[PLANES];
  Double_t x[PLANES];

  //Loop over DC Planes
  for (Int_t npl = 0; npl < 12; npl++ )
    {
      x[npl] = npl+1;  //set x-axis for use with TGraph

      //Initialize Histograms
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
          
      H_dcRes[npl] = new TH1F(Form("DC_%s_DriftResiduls", dc_pl_names[npl].c_str()), Form("DC Drift Residuals, Plane %s", dc_pl_names[npl].c_str()), dcRes_nbins, dcRes_xmin, dcRes_xmax);
      H_dcRes[npl]->GetXaxis()->SetTitle("Drift Residuals (cm) ");
      H_dcRes[npl]->GetXaxis()->CenterTitle();
      H_dcRes[npl]->GetYaxis()->SetTitle("Counts");
      H_dcRes[npl]->GetYaxis()->CenterTitle();

      //----Define TTree Leaf Names-----
      base = "H.dc." + dc_pl_names[npl];
      ndc_time = base + "." + "time";
      ndc_dist = base + "." + "dist";
      ndc_nhit = base + "." + "nhit";
      ndc_ndata = "Ndata." + base + "." + "time";
      
      //------Set Branch Address-------
      T->SetBranchAddress(ndc_ndata, &dc_ndata[npl]);
      T->SetBranchAddress(ndc_time, dc_time[npl]);
      T->SetBranchAddress(ndc_dist, dc_dist[npl]);
      T->SetBranchAddress(ndc_nhit, &dc_nhit[npl]);
      T->SetBranchAddress("H.dc.residual", &dc_res[0]);
     


    }
    
      
  //-----LOOP OVER ALL EVENTS
  Long64_t nentries = T->GetEntries();
  
  //Loop over all entries
  for(Long64_t i=0; i<100000; i++)
    {
      
      T->GetEntry(i);  

      
      //Loop over all DC planes
      for (Int_t npl = 0; npl < 12; npl++ )
	{
      
	  //Loop over hits
	  for (Int_t j=0; j < dc_ndata[npl]; j++)
	    {
	      //Fill Histograms
	    
	      if(dc_nhit[npl]==1)
		{
		  H_dcTime[npl]->Fill(dc_time[npl][j]);
		  H_dcDist[npl]->Fill(dc_dist[npl][j]);
		}
	    }
	    
	  if(dc_nhit[npl]==1)
	    {
	      H_dcRes[npl]->Fill(dc_res[npl]);
	    }
	  
	}
      
      
 
    }
  
  /***********DRAW HISTOGRAMS TO CANVAS***************/
  dcTimeCanv = new TCanvas("DC Times", "HMS DC TIMES",  1500, 500);
  dcTimeCanv->Divide(6,2);
    
  dcDistCanv = new TCanvas("DC Dist", "HMS DC Distance",  1500, 500);
  dcDistCanv->Divide(6,2);
    
  dcResCanv = new TCanvas("DC Residuals", "HMS DC Residuals",  1500, 500);
  dcResCanv->Divide(6,2);
    
  dcResSigCanv = new TCanvas("DC Residuals Graph", "HMS DC Residuals Graph",  1500, 500);

  //Loop over DC planes
  for (Int_t npl = 0; npl < 12; npl++ )
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

    }
  
  TGraph *gr_residual = new TGraph(12, x, sigma);
  dcResSigCanv->cd();
  dcResSigCanv->SetGrid();
  gr_residual->SetMarkerStyle(22);
  gr_residual->SetMarkerColor(kRed);
  gr_residual->SetMarkerSize(2);
  gr_residual->GetYaxis()->SetRangeUser(0., 500.);

  //Set Axis Titles
  gr_residual->GetXaxis()->SetTitle("HMS DC Planes");
  gr_residual->GetXaxis()->CenterTitle();
  gr_residual->GetYaxis()->SetTitle("HMS DC Residual (#mum)");
  gr_residual->GetYaxis()->CenterTitle();
  gr_residual->SetTitle("HMS DC Residuals");


  gr_residual->Draw("AP");

  dcTimeCanv->SaveAs("HMS_DC_Times.pdf");
  dcDistCanv->SaveAs("HMS_DC_Dist.pdf");
  dcResCanv->SaveAs("HMS_DC_Res.pdf");
  dcResSigCanv->SaveAs("HMS_DC_ResPlot.pdf");

  //Write Histograms to ROOT file
  //outROOT->Write();
  //outROOT->Close();
  
} 

void checkCalib()
{
  gROOT->SetBatch(kTRUE);
  
  checkDC_Calib("../../ROOTfiles/hms_replay_dc_calib_1267_1000000.root", 1267);
  
}
