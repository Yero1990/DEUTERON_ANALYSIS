void make_plots()
{

  //Open ROOT files;
  TFile *data_file = new TFile("deep_data_histos_3289.root");
  TFile *simc1_file = new TFile("deep_simc_histos_3289_0.04deltasmear.root");
  TFile *simc2_file = new TFile("deep_simc_histos_3289_xptar1mr.root");
  TFile *simc3_file = new TFile("deep_simc_histos_3289_xptar2mr.root");
  TFile *simc4_file = new TFile("deep_simc_histos_3289_xptar3mr.root");
  TFile *simc5_file = new TFile("deep_simc_histos_3289_xptar5mr.root");


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
  
  TH1F *data_pm5 =  0;
  TH1F *simc_pm5 =  0;
  TH1F *ratio_pm5 = 0;



  data_file->cd();
  data_file->GetObject("H_Pm", data_pm1);
  data_pm2 = (TH1F*)data_pm1->Clone("dataPm");
  data_pm3 = (TH1F*)data_pm1->Clone("dataPm");
  data_pm4 = (TH1F*)data_pm1->Clone("dataPm");
  data_pm5 = (TH1F*)data_pm1->Clone("dataPm");



  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1);
  
  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2);
  
  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3);
  
  simc4_file->cd();
  simc4_file->GetObject("H_Pm", simc_pm4);
  
  simc5_file->cd();
  simc5_file->GetObject("H_Pm", simc_pm5);

  /*
  TCanvas *c0 = new TCanvas("c0", "", 1800,1500);
  c0->Divide(3,2);
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
  c0->cd(3);
  data_pm3->SetLineColor(kBlue);
  simc_pm3->SetLineColor(kRed);
  data_pm3->Draw("E0");
  simc_pm3->Draw("histsames");
  
  c0->cd(4);
  data_pm4->SetLineColor(kBlue);
  simc_pm4->SetLineColor(kRed);
  data_pm4->Draw("E0");
  simc_pm4->Draw("histsames");
  c0->cd(5);
  data_pm5->SetLineColor(kBlue);
  simc_pm5->SetLineColor(kRed);
  data_pm5->Draw("E0");
  simc_pm5->Draw("histsames");
  
  data_pm6->SetLineColor(kBlue);
  simc_pm6->SetLineColor(kRed);
  data_pm6->Draw("E0");
  simc_pm6->Draw("histsames");
*/  

  
  //Calculate Ratios
  //0.04 delta smear
  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetLineWidth(2);
  //xptar 1mr smear
  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetLineWidth(2);
  //xptar 2mr smear
  data_pm3->Divide(simc_pm3);
  data_pm3->SetLineColor(kGreen);
  data_pm3->SetLineWidth(2);
  //xptar 3mr smear
  data_pm4->Divide(simc_pm4);
  data_pm4->SetLineColor(kMagenta);
  data_pm4->SetLineWidth(2);
  //xptar 5mr smear
  data_pm5->Divide(simc_pm5);
  data_pm5->SetLineColor(kRed);
  data_pm5->SetLineWidth(2);

  
  

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");
  data_pm3->Draw("SAMES");
  data_pm4->Draw("SAMES");
  data_pm5->Draw("SAMES");

  

}
