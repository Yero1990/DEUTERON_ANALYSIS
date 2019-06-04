void make_plots()
{

  //Open ROOT files;
  TFile *data1_file = new TFile("deep_data_histos_3289_Em15MeV.root");
  TFile *simc1_file = new TFile("deep_simc_histos_3289_Em15MeV.root");
 
  TFile *data2_file = new TFile("deep_data_histos_3289_Em10MeV.root");
  TFile *simc2_file = new TFile("deep_simc_histos_3289_Em10MeV.root");

  TFile *data3_file = new TFile("deep_data_histos_3289_Em5MeV.root");
  TFile *simc3_file = new TFile("deep_simc_histos_3289_Em5MeV.root");

  TFile *data4_file = new TFile("deep_data_histos_3289_Em5to30MeV.root");
  TFile *simc4_file = new TFile("deep_simc_histos_3289_Em5to30MeV.root");

 //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm1 =  0;
  TH1F *simc_pm1 =  0;
  TH1F *ratio_pm1 = 0;
  
  TH1F *data_pm2 =  0;
  TH1F *simc_pm2 =  0;
  TH1F *ratio_pm2 = 0;

  TH1F *data_pm3 =  0;
  TH1F *simc_pm3 =  0;
  TH1F *ratio_pm3 = 0;
  
  TH1F *data_pm4 =  0;
  TH1F *simc_pm4 =  0;
  TH1F *ratio_pm4 = 0;

  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1);
 
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2);

  data3_file->cd();
  data3_file->GetObject("H_Pm", data_pm3);
 
  data4_file->cd();
  data4_file->GetObject("H_Pm", data_pm4);


  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1);
  
  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2);
    
  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3);
  
  simc4_file->cd();
  simc4_file->GetObject("H_Pm", simc_pm4);


  /*
  TCanvas *c0 = new TCanvas("c0", "", 1800,1500);
  c0->Divide(1,2);
  c0->cd(1);
  data_pm1->SetLineColor(kBlue);
  simc_pm1->SetLineColor(kRed);
  data_pm1->Draw("E0");
  simc_pm1->Draw("histsames");
  c0->cd(2);
  data_pm2->SetLineColor(kBlue);
  simc_pm2->SetLineColor(kRed);
  data_pm2->Draw("E0");
  simc_pm2->Draw("histsames");
  */

  
  //Calculate Ratios
  //Em: 15 MeV
  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetLineWidth(2);
  //Em: 10 MeV
  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetLineWidth(2);
  //Em: 5 MeV
  data_pm3->Divide(simc_pm3);
  data_pm3->SetLineColor(kMagenta);
  data_pm3->SetLineWidth(2);
  //Em: 5 MeV to 30 MeV
  data_pm4->Divide(simc_pm4);
  data_pm4->SetLineColor(kRed);
  data_pm4->SetLineWidth(2);

  
  
  

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");
  data_pm3->Draw("SAMES");
  data_pm4->Draw("SAMES");

  

}
