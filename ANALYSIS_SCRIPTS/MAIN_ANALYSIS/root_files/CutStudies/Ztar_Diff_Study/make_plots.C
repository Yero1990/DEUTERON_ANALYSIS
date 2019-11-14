void make_plots()
{

  TH1F::SetDefaultSumw2();

  //Open ROOT files;
  TFile *data0_file = new TFile("no_ztar_cuts/deep_data_histos_3289_pmXYZcuts_noZtar.root");
  TFile *simc0_file = new TFile("no_ztar_cuts/deep_simc_histos_3289_pmXYZcuts_noZtar.root");

  TFile *data1_file = new TFile("no_ztar_cuts/deep_data_histos_3289_noZtarCut.root");
  TFile *simc1_file = new TFile("no_ztar_cuts/deep_simc_histos_3289_noZtarCut.root");
  
  TFile *data2_file = new TFile("ztar_1cm/deep_data_histos_3289_zTarCut_1cm.root");
  TFile *simc2_file = new TFile("ztar_1cm/deep_simc_histos_3289_zTarCut_1cm.root");
  
  TFile *data3_file = new TFile("ztar_2cm/deep_data_histos_3289_zTarCut_2cm.root");
  TFile *simc3_file = new TFile("ztar_2cm/deep_simc_histos_3289_zTarCut_2cm.root");

  TFile *data4_file = new TFile("ztar_3cm/deep_data_histos_3289_zTarCut_3cm.root");
  TFile *simc4_file = new TFile("ztar_3cm/deep_simc_histos_3289_zTarCut_3cm.root");
  
  TFile *data5_file = new TFile("ztar_4cm/deep_data_histos_3289_zTarCut_4cm.root");
  TFile *simc5_file = new TFile("ztar_4cm/deep_simc_histos_3289_zTarCut_4cm.root");

  TFile *data6_file = new TFile("ztar_5cm/deep_data_histos_3289_zTarCut_5cm.root");
  TFile *simc6_file = new TFile("ztar_5cm/deep_simc_histos_3289_zTarCut_5cm.root");
  
  TFile *data7_file = new TFile("ztar_6cm/deep_data_histos_3289_zTarCut_6cm.root");
  TFile *simc7_file = new TFile("ztar_6cm/deep_simc_histos_3289_zTarCut_6cm.root");

  TFile *data8_file = new TFile("ztar_2cm_and_Pmcuts/deep_data_histos_3289_pmX0.1.root ");
  TFile *simc8_file = new TFile("ztar_2cm_and_Pmcuts/deep_simc_histos_3289_pmX0.1.root ");

  TFile *data9_file = new TFile("ztar_2cm_and_Pmcuts/deep_data_histos_3289_pmXandpmY0.1.root ");
  TFile *simc9_file = new TFile("ztar_2cm_and_Pmcuts/deep_simc_histos_3289_pmXandpmY0.1.root ");
 
  TFile *data10_file = new TFile("ztar_2cm_and_Pmcuts/deep_data_histos_3289_pmXYZ.root ");
  TFile *simc10_file = new TFile("ztar_2cm_and_Pmcuts/deep_simc_histos_3289_pmXYZ.root ");

  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm0 =  0;
  TH1F *simc_pm0 =  0;
  TH1F *ratio_pm0 = 0;

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
  
  TH1F *data_pm6 =  0;
  TH1F *simc_pm6 =  0;
  TH1F *ratio_pm6 = 0;
    
  TH1F *data_pm7 =  0;
  TH1F *simc_pm7 =  0;
  TH1F *ratio_pm7 = 0;

  TH1F *data_pm8 =  0;
  TH1F *simc_pm8 =  0;
  TH1F *ratio_pm8 = 0;
  
  TH1F *data_pm9 =  0;
  TH1F *simc_pm9 =  0;
  TH1F *ratio_pm9 = 0;
    
  TH1F *data_pm10 =  0;
  TH1F *simc_pm10 =  0;
  TH1F *ratio_pm10 = 0;

  data0_file->cd();
  data0_file->GetObject("H_Pm", data_pm0); //noZtar cut. With pmXYZ Cuts
  
  simc0_file->cd();
  simc0_file->GetObject("H_Pm", simc_pm0); 
  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1); //noZtar cut

  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1); 
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2); //Ztar 1cm cut

  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2); 
   
  data3_file->cd();
  data3_file->GetObject("H_Pm", data_pm3); //Ztar 2cm cut

  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3); 
    
  data4_file->cd();
  data4_file->GetObject("H_Pm", data_pm4); //Ztar 3 cm cut

  simc4_file->cd();
  simc4_file->GetObject("H_Pm", simc_pm4); 
  
  data5_file->cd();
  data5_file->GetObject("H_Pm", data_pm5); //Ztar 4 cm cut

  simc5_file->cd();
  simc5_file->GetObject("H_Pm", simc_pm5); 
  
  data6_file->cd();
  data6_file->GetObject("H_Pm", data_pm6); //Ztar 5 cm cut

  simc6_file->cd();
  simc6_file->GetObject("H_Pm", simc_pm6); 
  
  data7_file->cd();
  data7_file->GetObject("H_Pm", data_pm7); //Ztar 6 cm cut

  simc7_file->cd();
  simc7_file->GetObject("H_Pm", simc_pm7);
 
  data8_file->cd();
  data8_file->GetObject("H_Pm", data_pm8); //Ztar 2 cm and |pmX|<0.1 cut

  simc8_file->cd();
  simc8_file->GetObject("H_Pm", simc_pm8);
  
  data9_file->cd();
  data9_file->GetObject("H_Pm", data_pm9); //Ztar 2 cm and |pmX|<0.1&& |pmY|<0.1 cut

  simc9_file->cd();
  simc9_file->GetObject("H_Pm", simc_pm9);
   
  data10_file->cd();
  data10_file->GetObject("H_Pm", data_pm10); //Ztar 2 cm and |pmX|<0.1&& |pmY|<0.1 && pmZ>-0.05&&pmZ<0.1 cut

  simc10_file->cd();
  simc10_file->GetObject("H_Pm", simc_pm10);
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
  data_pm0->Divide(simc_pm0);
  data_pm0->SetLineColor(kBlack);
  data_pm0->SetMarkerStyle(21);
  data_pm0->SetLineWidth(2);

  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kBlack);
  data_pm1->SetMarkerStyle(21);
  data_pm1->SetLineWidth(2);

  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kCyan);
  data_pm2->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kCyan); 
  data_pm2->SetLineWidth(2);


  data_pm3->Divide(simc_pm3);
  data_pm3->SetLineColor(kRed);
  data_pm3->SetMarkerStyle(21);
  data_pm3->SetMarkerColor(kRed);
  data_pm3->SetLineWidth(2);

  data_pm4->Divide(simc_pm4);
  data_pm4->SetLineColor(kGreen);
  data_pm4->SetMarkerStyle(21);
  data_pm4->SetMarkerColor(kGreen);
  data_pm4->SetLineWidth(2);

  data_pm5->Divide(simc_pm5);
  data_pm5->SetLineColor(kBlue);
  data_pm5->SetMarkerStyle(21);
  data_pm5->SetMarkerColor(kBlue); 
  data_pm5->SetLineWidth(2);

  data_pm6->Divide(simc_pm6);
  data_pm6->SetLineColor(9);
  data_pm6->SetMarkerStyle(21);
  data_pm6->SetMarkerColor(9);
  data_pm6->SetLineWidth(2);

  data_pm7->Divide(simc_pm7);
  data_pm7->SetLineColor(kMagenta);
  data_pm7->SetMarkerStyle(21);
  data_pm7->SetMarkerColor(kMagenta);
  data_pm7->SetLineWidth(2);
  
  data_pm8->Divide(simc_pm8);
  data_pm8->SetLineColor(kBlue);
  data_pm8->SetMarkerStyle(21);
  data_pm8->SetMarkerColor(kBlue);
  data_pm8->SetLineWidth(2);
  
  data_pm9->Divide(simc_pm9);
  data_pm9->SetLineColor(kGreen);
  data_pm9->SetMarkerStyle(21);
  data_pm9->SetMarkerColor(kGreen);
  data_pm9->SetLineWidth(2);

  data_pm10->Divide(simc_pm10);
  data_pm10->SetLineColor(kRed);
  data_pm10->SetMarkerStyle(21);
  data_pm10->SetMarkerColor(kRed);
  data_pm10->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  //data_pm0->Draw();
  data_pm1->Draw();
  data_pm2->Draw("SAMES");
  data_pm3->Draw("SAMES");
  data_pm4->Draw("SAMES");
  data_pm5->Draw("SAMES");
  data_pm6->Draw("SAMES");
  data_pm7->Draw("SAMES");
  //data_pm8->Draw("SAMES");
  //data_pm9->Draw("SAMES");
  //data_pm10->Draw("SAMES");

  

}
