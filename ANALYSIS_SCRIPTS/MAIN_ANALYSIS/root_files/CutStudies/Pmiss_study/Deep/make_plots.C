void make_plots()
{

  //Open ROOT files;
  TFile *data1_file = new TFile("no_pmiss_cuts/deep_data_histos_3289.root");
  TFile *simc1_file = new TFile("no_pmiss_cuts/deep_simc_histos_3289.root");
  
  TFile *data2_file = new TFile("pmiss_cuts/pmX_0.08/deep_data_histos_3289.root");
  TFile *simc2_file = new TFile("pmiss_cuts/pmX_0.08/deep_simc_histos_3289.root");
  
  TFile *data3_file = new TFile("pmiss_cuts/pmXY_0.1/deep_data_histos_3289.root");
  TFile *simc3_file = new TFile("pmiss_cuts/pmXY_0.1/deep_simc_histos_3289.root");
 
  TFile *data4_file = new TFile("pmiss_cuts/pmXY_0.1_pmZcut/deep_data_histos_3289.root");
  TFile *simc4_file = new TFile("pmiss_cuts/pmXY_0.1_pmZcut/deep_simc_histos_3289.root");
  
  TFile *data5_file = new TFile("pmiss_cuts/pm_and_ztar_diff_cuts/deep_data_histos_3289.root");
  TFile *simc5_file = new TFile("pmiss_cuts/pm_and_ztar_diff_cuts/deep_simc_histos_3289.root");

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
  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1); //noPm cut

  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1); //noPm cut
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2); //Pmx < 0.08 cut

  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2); //Pmx < 0.08 cut
   
  data3_file->cd();
  data3_file->GetObject("H_Pm", data_pm3); //|Pmx| < 0.1 &&|Pmy| < 0.1 cut

  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3); //|Pmx| < 0.1 &&|Pmy| < 0.1 cut
    
  data4_file->cd();
  data4_file->GetObject("H_Pm", data_pm4); //|Pmx| < 0.1 &&|Pmy| < 0.1 cut

  simc4_file->cd();
  simc4_file->GetObject("H_Pm", simc_pm4); //|Pmx| < 0.1 &&|Pmy| < 0.1 && (Pmz>-0.05&&Pmz<0.1) cut
  
  data5_file->cd();
  data5_file->GetObject("H_Pm", data_pm5); //|Pmx| < 0.1 &&|Pmy| < 0.1 cut

  simc5_file->cd();
  simc5_file->GetObject("H_Pm", simc_pm5); //|Pmx| < 0.1 &&|Pmy| < 0.1 && (Pmz>-0.05&&Pmz<0.1) cut && |ztar|<2
  

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
  //No Pm Cut
  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetLineWidth(2);
  //Pmx < 0.08 cut
  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetLineWidth(2);
  //|Pmx| < 0.1 &&|Pmy| < 0.1 cut
  data_pm3->Divide(simc_pm3);
  data_pm3->SetLineColor(kMagenta);
  data_pm3->SetLineWidth(2);
  //|Pmx| < 0.1 &&|Pmy| < 0.1 && pmZ cut
  data_pm4->Divide(simc_pm4);
  data_pm4->SetLineColor(kGreen);
  data_pm4->SetLineWidth(2);
  //|Pmx| < 0.1 &&|Pmy| < 0.1 && pmZ cut && |ztar_diff|<2
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
