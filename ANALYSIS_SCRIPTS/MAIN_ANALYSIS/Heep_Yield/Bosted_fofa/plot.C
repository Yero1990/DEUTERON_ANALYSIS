void plot()
{

  //TString fname_simc = "heep_simc_histos_3288_rad_Q2_4.0_4.1_zdiff3cm.root";
  //TString fname = "heep_data_histos_3288_combined_Q2_4.0_4.1_zdiff3cm.root";

  ofstream fout;
  
  int run[4] = {3288, 3371, 3374, 3377};
 

  TCanvas *c;
  //Create canvas to store Q2 ratio
  c = new TCanvas("canv", "", 1000, 1000);
  c->Divide(2,2);
      

      
  //Create Output file to write Yield and ration
  TString fout_name = "heep_yield_study.dat";
  cout << "FILENAME: " << fout_name << endl;
  fout.open(fout_name, std::ofstream::out | std::ofstream::app);
  fout << "#! Run[i,0]/   Ydata[f,0]/  Ydata_err[f,1]/   Ysimc[f,2]/   Ysimc_err[f,3]/   R[f,4]/   R_err[f,5]/\n";

  for(int irun = 0; irun<4; irun++)
    {
      TString fname_simc = Form("heep_simc_histos_%d_rad.root", run[irun]);
      TString fname = Form("heep_data_histos_%d_combined.root", run[irun]);
      
      TFile *f = new TFile(fname);
      TFile *fsimc = new TFile(fname_simc);
      
      
      f->cd();
      TH1F * hW = 0;
      TH1F * hQ2 = 0;
      TH1F * h_hyptar = 0;
      TH1F * h_hdelta = 0;
      
      hW = (TH1F*)f->Get("H_W");
      hQ2 = (TH1F*)f->Get("H_Q2");
      h_hyptar = (TH1F*)f->Get("H_hyptar");
      h_hdelta = (TH1F*)f->Get("H_hdelta");
      
      
      double err_data;
      double Idata = hW->IntegralAndError(hW->FindBin(0.85), hW->FindBin(1.05), err_data);
      
      cout << "Wdata = " << Idata << " +/- " << err_data << endl;
      //-----------
      
      fsimc->cd();
      TH1F * hsimcW = 0;
      TH1F * hsimcQ2 = 0;
      TH1F * hsimc_hyptar = 0;
      TH1F * hsimc_hdelta = 0;
      
      hsimcW = (TH1F*)fsimc->Get("H_W");
      hsimcQ2 = (TH1F*)fsimc->Get("H_Q2");
      hsimc_hyptar = (TH1F*)fsimc->Get("H_hyptar");
      hsimc_hdelta = (TH1F*)fsimc->Get("H_hdelta");
      
      
      double err_simc;
      double Isimc = hsimcW->IntegralAndError(hsimcW->FindBin(0.85), hsimcW->FindBin(1.05), err_simc);
      
      cout << "Wsimc = " << Isimc << " +/- " << err_simc << endl;
      
      double R = Idata / Isimc;
      double R_err = R * sqrt(pow((err_data/Idata),2) + pow(err_simc/Isimc,2));
      
      cout << "R = " << R << " +/- " << R_err << endl;
      
      fout << run[irun] << "   " << Idata << "   " << err_data << "    " << Isimc << "   " << err_simc << "    " << R << "    " << R_err << endl;  
      /* 
	 c[0]->cd(irun+1);
	 
	 hQ2->Divide(hsimcQ2);
	 hQ2->SetTitle(Form("Run %i", run[irun]));
	 hQ2->SetLineColor(hscale_color[iscale]);
	 hQ2->SetLineWidth(2);
	 hQ2->SetMarkerStyle(22);
	 hQ2->SetMarkerColor(hscale_color[iscale]);
	 hQ2->SetMarkerSize(0.5);
	 hQ2->Draw("sames");
	 
	 h_hyptar->Divide(hsimc_hyptar);
	 h_hyptar->SetTitle(Form("Run %i", run[irun]));
	 h_hyptar->SetLineColor(hscale_color[iscale]);
	 h_hyptar->SetLineWidth(2);
	 h_hyptar->SetMarkerStyle(22);
	 h_hyptar->SetMarkerColor(hscale_color[iscale]);
	 h_hyptar->SetMarkerSize(0.5);
	 h_hyptar->Draw("sames");
	 
	 h_hdelta->Divide(hsimc_hdelta);
	 h_hdelta->SetTitle(Form("Run %i", run[irun]));
	 h_hdelta->SetLineColor(hscale_color[iscale]);
	 h_hdelta->SetLineWidth(2);
	 h_hdelta->SetMarkerStyle(22);
	 h_hdelta->SetMarkerColor(hscale_color[iscale]);
	 h_hdelta->SetMarkerSize(0.5);
	 h_hdelta->Draw("sames");
      */
    } //end run
  
  fout.close();
  
}
