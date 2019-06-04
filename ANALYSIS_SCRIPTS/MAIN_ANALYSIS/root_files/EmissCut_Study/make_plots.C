void make_plots()
{

  TH1F::SetDefaultSumw2();

  //Open ROOT files;
  TFile *data1_file = new TFile("Em_set1/deep_data_histos_3289.root");
  TFile *simc1_file = new TFile("Em_set1/deep_simc_histos_3289.root");
  
  TFile *data2_file = new TFile("Em_set2/deep_data_histos_3289.root");
  TFile *simc2_file = new TFile("Em_set2/deep_simc_histos_3289.root");
  
  TFile *data3_file = new TFile("Em_set3/deep_data_histos_3289.root");
  TFile *simc3_file = new TFile("Em_set3/deep_simc_histos_3289.root");



  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm1 =  0;
  TH1F *simc_pm1 =  0;
 
  TH1F *data_pm2 =  0;
  TH1F *simc_pm2 =  0;
   
  TH1F *data_pm3 =  0;
  TH1F *simc_pm3 =  0;
  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1);
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2); 
   
  data3_file->cd();
  data3_file->GetObject("H_Pm", data_pm3);
  
  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1); 
   
  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2); 
  
  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3); 
  
  
  //Calculate Ratios


  data_pm1->Divide(simc_pm1);    //Em: -40, 0
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetMarkerStyle(21);
  data_pm1->SetMarkerColor(kBlack); 
  data_pm1->SetLineWidth(2);

  data_pm2->Divide(simc_pm2);    //Em: 0, 20
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kBlue); 
  data_pm2->SetLineWidth(2);

  data_pm3->Divide(simc_pm3);     //Em: 20, 40.
  data_pm3->SetLineColor(kRed);
  data_pm3->SetMarkerStyle(21);
  data_pm3->SetMarkerColor(kRed); 
  data_pm3->SetLineWidth(2);


  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");
  data_pm3->Draw("SAMES");

  

}
