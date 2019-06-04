void make_plots()
{

  TH1F::SetDefaultSumw2();

  //Open ROOT files;
  TFile *data0_file = new TFile("../deep_data_histos_3289_chi2.root");
  TFile *data1_file = new TFile("../deep_data_histos_3289_prune.root");
  TFile *data2_file = new TFile("../deep_data_histos_3289_prune_AND_DCAlign.root");

  TFile *simc0_file = new TFile("../deep_simc_histos_3289.root");


  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm0 =  0;
  TH1F *data_pm1 =  0;
  TH1F *data_pm2 =  0;
  TH1F *simc_pm0 =  0;

  data0_file->cd();
  data0_file->GetObject("H_Pm", data_pm0);
  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1); 
   
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2);
  
  simc0_file->cd();
  simc0_file->GetObject("H_Pm", simc_pm0); 
  
  
  //Calculate Ratios
  data_pm0->Divide(simc_pm0);
  data_pm0->SetLineColor(kBlack);
  data_pm0->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kBlack); 
  data_pm0->SetLineWidth(2);

  data_pm1->Divide(simc_pm0);
  data_pm1->SetLineColor(kBlue);
  data_pm1->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kBlue); 
  data_pm1->SetLineWidth(2);

  data_pm2->Divide(simc_pm0);
  data_pm2->SetLineColor(kRed);
  data_pm2->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kRed); 
  data_pm2->SetLineWidth(2);



  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm0->Draw();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");

  

}
