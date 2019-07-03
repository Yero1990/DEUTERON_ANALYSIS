/*Macro to plot DATA, SIMC Cross sections for the D(e,e'p)
The Cross sections are in Pmiss/PhaseSpace vs. theta_nq bins, so
one would need to get the projectionsY from the 2D Histos, to get
the cross section in theta_nw bins. 

TH1 *hbins[100] ;//or whatever you need, ie nbins for (int i=0;i<nbins;i++) { hbins[i] = h2->ProjectionY(Form("bin%d",i+1),i+1,i+2); } 

 */

void plotXsec(int pm, int set)
{

  TH1F::SetDefaultSumw2();
  
//Read ROOTfiles
  TString pwia_fname = Form("pm580/Xsec_pm%d_lagetpwia_dataset%d.root", pm, set);
  TString fsi_fname = Form("pm580/Xsec_pm%d_lagetfsi_dataset%d.root", pm, set);
  
  TFile *file_pwia = new TFile(pwia_fname, "READ");
  TFile *file_fsi = new TFile(fsi_fname, "READ");


  //Get 2D Histogram Objects
  TH2F *data_Pm_vs_thnq = 0;
  TH2F *simc_Pm_vs_thnq_pwia = 0;
  TH2F *simc_Pm_vs_thnq_fsi = 0;

  
  file_pwia->cd();
  file_pwia->GetObject("H_simc2DXsec", simc_Pm_vs_thnq_pwia); 

  file_fsi->cd();
  file_fsi->GetObject("H_simc2DXsec", simc_Pm_vs_thnq_fsi);
  file_fsi->GetObject("H_data2DXsec", data_Pm_vs_thnq);

  //the data histo is the same for both files
  
  //Get the total number of bins
  static const int thnq_bins = data_Pm_vs_thnq->GetNbinsX();
  static const int pm_bins = data_Pm_vs_thnq->GetNbinsY();

  TCanvas *c1 = new TCanvas("c1", "Cross Sections", 3000, 2800);
  c1->Divide(3, 3);
  
  //Create 1D Histograms to store projections (in thnq bins)
  TH1D *data_thnq_bins[thnq_bins];
  TH1D *simc_pwia_thnq_bins[thnq_bins];
  TH1D *simc_fsi_thnq_bins[thnq_bins];
  
  //Bin Information
  Double_t xbin_center = 0.;
  Double_t xbin_width = 0.;
  Double_t xbin_low = 0.;
  Double_t xbin_up = 0.;

  
  TFile *outROOT = new TFile(Form("Xsec_pm%d_set%d_slices.root", pm, set), "RECREATE");
  outROOT->cd();

  
 //Loop over th_nq bins and get projections
for(int ix_bin=1; ix_bin<=thnq_bins; ix_bin++)
  {

    xbin_low = data_Pm_vs_thnq->GetXaxis()->GetBinLowEdge(ix_bin);
    xbin_up = data_Pm_vs_thnq->GetXaxis()->GetBinUpEdge(ix_bin);
    xbin_center = data_Pm_vs_thnq->GetXaxis()->GetBinCenter(ix_bin);

    cout << "ix_bin = " << ix_bin << "xbin_center = " << xbin_center << endl;
    //Get Y Projection
    data_thnq_bins[ix_bin-1] = data_Pm_vs_thnq->ProjectionY(Form("H_dataXsec_thnq_bin%d",ix_bin), ix_bin, ix_bin);
    data_thnq_bins[ix_bin-1]->SetTitle(Form("D(e,e'p), Pm = %d MeV, #theta_{nq}:(%d,%d) deg", pm, int(xbin_low), int(xbin_up)));

    simc_pwia_thnq_bins[ix_bin-1] = simc_Pm_vs_thnq_pwia->ProjectionY(Form("H_pwiaXsec_thnq_bin%d",ix_bin), ix_bin, ix_bin);
    simc_pwia_thnq_bins[ix_bin-1]->SetTitle(Form("D(e,e'p), Pm = %d MeV, #theta_{nq}:(%d,%d) deg", pm, int(xbin_low), int(xbin_up)));

    simc_fsi_thnq_bins[ix_bin-1] = simc_Pm_vs_thnq_fsi->ProjectionY(Form("H_fsiXsec_thnq_bin%d",ix_bin), ix_bin, ix_bin);
    simc_fsi_thnq_bins[ix_bin-1]->SetTitle(Form("D(e,e'p), Pm = %d MeV, #theta_{nq}:(%d,%d) deg", pm, int(xbin_low), int(xbin_up)));

    //Set Histograms Aesthetics
    simc_pwia_thnq_bins[ix_bin-1]->SetLineColor(kBlue);
    simc_pwia_thnq_bins[ix_bin-1]->SetLineWidth(2);
    simc_pwia_thnq_bins[ix_bin-1]->SetMarkerStyle(21);
    simc_pwia_thnq_bins[ix_bin-1]->SetMarkerColor(kBlue);

    simc_fsi_thnq_bins[ix_bin-1]->SetLineColor(kRed);
    simc_fsi_thnq_bins[ix_bin-1]->SetLineWidth(2);
    simc_fsi_thnq_bins[ix_bin-1]->SetMarkerStyle(21);
    simc_fsi_thnq_bins[ix_bin-1]->SetMarkerColor(kRed);

    data_thnq_bins[ix_bin-1]->SetLineColor(kBlack);
    data_thnq_bins[ix_bin-1]->SetLineWidth(2);
    data_thnq_bins[ix_bin-1]->SetMarkerStyle(21);
    data_thnq_bins[ix_bin-1]->SetMarkerColor(kBlack);
    
    //Draw to Canvas
    c1->cd(ix_bin);
    simc_pwia_thnq_bins[ix_bin-1]->Draw("E");
    simc_fsi_thnq_bins[ix_bin-1]->Draw("Esame");
    data_thnq_bins[ix_bin-1]->Draw("Esame");
    gPad->SetLogy();

    
    //data_thnq_bins[ix_bin-1]->Write();
    //simc_pwia_thnq_bins[ix_bin-1]->Write();
    //simc_fsi_thnq_bins[ix_bin-1]->Write();
    
  
    
    
  }

//c1->Draw();
 
//outROOT->Close();




}


