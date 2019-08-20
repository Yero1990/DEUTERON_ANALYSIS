void make_plots()
{

  TH1F::SetDefaultSumw2();

  //Open ROOT files;

  //------------STUDY 1: 2 % bins in delta from -3 to 3
  TFile *data0_file = new TFile("shms_delta_full/deep_data_histos_3289_full.root");
  TFile *simc0_file = new TFile("shms_delta_full/deep_simc_histos_3289_full.root ");

  TFile *data1_file = new TFile("shms_delta_-3to-1/deep_data_histos_3289_edelta_-3to-1.root");
  TFile *simc1_file = new TFile("shms_delta_-3to-1/deep_simc_histos_3289_edelta_-3to-1.root");
  
  TFile *data2_file = new TFile("shms_delta_-1to1/deep_data_histos_3289_edelta_-1to1.root");
  TFile *simc2_file = new TFile("shms_delta_-1to1/deep_simc_histos_3289_edelta_-1to1.root");
  
  TFile *data3_file = new TFile("shms_delta_1to3/deep_data_histos_3289_edelta_1to3.root");
  TFile *simc3_file = new TFile("shms_delta_1to3/deep_simc_histos_3289_edelta_1to3.root");

  //----------------STUDY 2: equal delta cuts-----------------
  TFile *data4_file = new TFile("shms_delta_3/deep_data_histos_3289_edelta3.root");
  TFile *simc4_file = new TFile("shms_delta_3/deep_simc_histos_3289_edelta3.root");
 
  TFile *data5_file = new TFile("shms_delta_2.5/deep_data_histos_3289_edelta2.5.root");
  TFile *simc5_file = new TFile("shms_delta_2.5/deep_simc_histos_3289_edelta2.5.root");
  
  TFile *data6_file = new TFile("shms_delta_2/deep_data_histos_3289_edelta2.root");
  TFile *simc6_file = new TFile("shms_delta_2/deep_simc_histos_3289_edelta2.root");
  
  TFile *data7_file = new TFile("shms_delta_1.5/deep_data_histos_3289_edelta1.5.root");
  TFile *simc7_file = new TFile("shms_delta_1.5/deep_simc_histos_3289_edelta1.5.root");
  
  TFile *data8_file = new TFile("shms_delta_1/deep_data_histos_3289_edelta1.root");
  TFile *simc8_file = new TFile("shms_delta_1/deep_simc_histos_3289_edelta1.root");

  TFile *data9_file = new TFile("shms_delta_0.5/deep_data_histos_3289_edelta0.5.root");
  TFile *simc9_file = new TFile("shms_delta_0.5/deep_simc_histos_3289_edelta0.5.root");

  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *data_pm0 =  0;
  TH1F *simc_pm0 =  0;

  TH1F *data_pm1 =  0;
  TH1F *simc_pm1 =  0;
  
  TH1F *data_pm2 =  0;
  TH1F *simc_pm2 =  0;
 
  TH1F *data_pm3 =  0;
  TH1F *simc_pm3 =  0;
 
  TH1F *data_pm4 =  0;
  TH1F *simc_pm4 =  0;
  
  TH1F *data_pm5 =  0;
  TH1F *simc_pm5 =  0;
 
  TH1F *data_pm6 =  0;
  TH1F *simc_pm6 =  0;

  TH1F *data_pm7 =  0;
  TH1F *simc_pm7 =  0;
  
  TH1F *data_pm8 =  0;
  TH1F *simc_pm8 =  0;
 
  TH1F *data_pm9 =  0;
  TH1F *simc_pm9 =  0;


  data0_file->cd();
  data0_file->GetObject("H_Pm", data_pm0); //Ztar cut, shms_delta: (-10,22)
  
  simc0_file->cd();
  simc0_file->GetObject("H_Pm", simc_pm0); 
  
  data1_file->cd();
  data1_file->GetObject("H_Pm", data_pm1); //Ztar cut, shms_delta: (-3,-1)

  simc1_file->cd();
  simc1_file->GetObject("H_Pm", simc_pm1); 
  
  data2_file->cd();
  data2_file->GetObject("H_Pm", data_pm2); //Ztar cut, shms_delta: (-1,1)

  simc2_file->cd();
  simc2_file->GetObject("H_Pm", simc_pm2); 
   
  data3_file->cd();
  data3_file->GetObject("H_Pm", data_pm3); //Ztar cut, shms_delta: (1,3)

  simc3_file->cd();
  simc3_file->GetObject("H_Pm", simc_pm3); 
    
  //---------------------------------------------------------------------------

  data4_file->cd();
  data4_file->GetObject("H_Pm", data_pm4); //Ztar cut, shms_delta: (-3,3)

  simc4_file->cd();
  simc4_file->GetObject("H_Pm", simc_pm4); 
     
  data5_file->cd();
  data5_file->GetObject("H_Pm", data_pm5); //Ztar cut, shms_delta: (-2.5,2.5)

  simc5_file->cd();
  simc5_file->GetObject("H_Pm", simc_pm5); 
    
  data6_file->cd();
  data6_file->GetObject("H_Pm", data_pm6); //Ztar cut, shms_delta: (-2,2)

  simc6_file->cd();
  simc6_file->GetObject("H_Pm", simc_pm6); 
  
  data7_file->cd();
  data7_file->GetObject("H_Pm", data_pm7); //Ztar cut, shms_delta: (-1.5,1.5)

  simc7_file->cd();
  simc7_file->GetObject("H_Pm", simc_pm7); 

  data8_file->cd();
  data8_file->GetObject("H_Pm", data_pm8); //Ztar cut, shms_delta: (-1,1)

  simc8_file->cd();
  simc8_file->GetObject("H_Pm", simc_pm8); 

  data9_file->cd();
  data9_file->GetObject("H_Pm", data_pm9); //Ztar cut, shms_delta: (-0.5,0.5)

  simc9_file->cd();
  simc9_file->GetObject("H_Pm", simc_pm9); 
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
  data_pm0->SetMarkerColor(kBlack); 
  data_pm0->SetLineWidth(2);

  data_pm1->Divide(simc_pm1);
  data_pm1->SetLineColor(kGreen);
  data_pm1->SetMarkerStyle(21);
  data_pm1->SetMarkerColor(kGreen); 
  data_pm1->SetLineWidth(2);

  data_pm2->Divide(simc_pm2);
  data_pm2->SetLineColor(kBlue);
  data_pm2->SetMarkerStyle(21);
  data_pm2->SetMarkerColor(kBlue); 
  data_pm2->SetLineWidth(2);

  data_pm3->Divide(simc_pm3);
  data_pm3->SetLineColor(kRed);
  data_pm3->SetMarkerStyle(21);
  data_pm3->SetMarkerColor(kRed);
  data_pm3->SetLineWidth(2);

  //------------STUDY 2----------

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
  data_pm6->SetLineColor(kRed);
  data_pm6->SetMarkerStyle(21);
  data_pm6->SetMarkerColor(kRed);
  data_pm6->SetLineWidth(2);

  data_pm7->Divide(simc_pm7);
  data_pm7->SetLineColor(kCyan);
  data_pm7->SetMarkerStyle(21);
  data_pm7->SetMarkerColor(kCyan); 
  data_pm7->SetLineWidth(2);

  data_pm8->Divide(simc_pm8);
  data_pm8->SetLineColor(kMagenta);
  data_pm8->SetMarkerStyle(21);
  data_pm8->SetMarkerColor(kMagenta);
  data_pm8->SetLineWidth(2);
 
  data_pm9->Divide(simc_pm9);
  data_pm9->SetLineColor(9);
  data_pm9->SetMarkerStyle(21);
  data_pm9->SetMarkerColor(9);
  data_pm9->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1", "Deep Pm Ratio", 1500,1000);
  c1->cd();
  data_pm0->Draw();
  //  data_pm1->Draw("SAMES");
  // data_pm2->Draw("SAMES");
  // data_pm3->Draw("SAMES");

  data_pm4->Draw("SAMES");  
  data_pm5->Draw("SAMES"); 
  data_pm6->Draw("SAMES");
  data_pm7->Draw("SAMES");
  data_pm8->Draw("SAMES");
  data_pm9->Draw("SAMES");

}
