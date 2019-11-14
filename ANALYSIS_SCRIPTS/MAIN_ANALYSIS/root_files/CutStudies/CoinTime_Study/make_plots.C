void make_plots()
{

  //Open ROOT files;
  TFile *data1_file = new TFile("no_coinCut/deep_data_histos_3289.root");
  TFile *simc1_file = new TFile("no_coinCut/deep_simc_histos_3289.root");
  
  TFile *data2_file = new TFile("coinCut/deep_data_histos_3289.root");
  TFile *simc2_file = new TFile("coinCut/deep_simc_histos_3289.root");

 //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm1 =  0;
  TH1F *simc_pm1 =  0;
  TH1F *ratio_pm1 = 0;
  
  TH1F *data_pm2 =  0;
  TH1F *simc_pm2 =  0;
  TH1F *ratio_pm2 = 0;

  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1); //no coin cut

  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1); //no coin cut
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2); //coin cut

  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2); //coin cut


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
  //No Coin
  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetLineWidth(2);
  //Coin cut
  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetLineWidth(2);

  
  

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");



  

}
