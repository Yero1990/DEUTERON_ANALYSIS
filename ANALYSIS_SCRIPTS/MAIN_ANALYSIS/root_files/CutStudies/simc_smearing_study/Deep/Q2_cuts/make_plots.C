void make_plots()
{

  //Open ROOT files;
  TFile *data1_file = new TFile("deep_data_histos_3289_original.root");  //no Q2 cut
  TFile *data2_file = new TFile("deep_data_histos_3289.root");  //Q2 cut

  TFile *simc1_file = new TFile("deep_simc_histos_3289_0.04deltasmear.root");  // no Q2 cut
  TFile *simc2_file = new TFile("deep_simc_histos_3289.root"); //Q2 cut


 //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm1 =  0;
  TH1F *simc_pm1 =  0;
  TH1F *ratio_pm1 = 0;
  
  TH1F *data_pm2 =  0;
  TH1F *simc_pm2 =  0;
  TH1F *ratio_pm2 = 0;

 


  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1);
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2);

  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1);
  
  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2);
  
  
  
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


  /*
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
  data_pm3->SetLineColor(kMagenta);
  data_pm3->SetLineWidth(2);
  //yptar 1mr smear
  //data_pm4->Divide(simc_pm4);
  //data_pm4->SetLineColor(kRed);
  //data_pm4->SetLineWidth(2);
  //yptar 2mr smear
  //data_pm5->Divide(simc_pm5);
  //data_pm5->SetLineColor(kGreen);
  //data_pm5->SetLineWidth(2);
  //xptar 5mr smear
  data_pm6->Divide(simc_pm6);
  data_pm6->SetLineColor(kRed);
  data_pm6->SetLineWidth(2);

  

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");
  data_pm3->Draw("SAMES");
  data_pm6->Draw("SAMES");

  */

}
