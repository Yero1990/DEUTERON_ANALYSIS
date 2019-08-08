//Script to calculate the Missing Momentum Yield Ratio, Pm_data/Pm_simc for
//various cuts for systematics analysis of D(e,e'p)n experiment (E12-10-003)
#include "GetBinInfo.C"
void systematics()
{

  gStyle->SetOptStat(0);
 

  //---File Names---
  
  //HMS Coll. Nominal Scale 1
  TString simc_filename = "../root_files/deep_simc_histos_pm80_lagetpwia_rad_set1_1hscale.root";
  TString data_filename = "../root_files/deep_data_histos_pm80_set1_combined_1hscale.root";
    
  //HMS Coll. Scale to 0.7 (tight HMS Coll. Cut)
  TString simc_filename_hColltight = "../root_files/deep_simc_histos_pm80_lagetpwia_rad_set1_0.7hscale.root";
  TString data_filename_hColltight = "../root_files/deep_data_histos_pm80_set1_combined_0.7hscale.root";
    
  //HMS Coll. Scale to 1.3 (loose HMS Coll. Cut)
  TString simc_filename_hCollloose = "../root_files/deep_simc_histos_pm80_lagetpwia_rad_set1_1.3hscale.root";
  TString data_filename_hCollloose = "../root_files/deep_data_histos_pm80_set1_combined_1.3hscale.root";
   
  //---Data Files---
  
  //HMS Coll. Nominal Scale 1
  TFile *simc_file = new TFile(simc_filename);
  TFile *data_file = new TFile(data_filename);

  //HMS Coll. Scale to 0.7 (tight HMS Coll. Cut)
  TFile *simc_file_hColltight = new TFile(simc_filename_hColltight);
  TFile *data_file_hColltight = new TFile(data_filename_hColltight);

  //HMS Coll. Scale to 1.3 (loose HMS Coll. Cut)
  TFile *simc_file_hCollloose = new TFile(simc_filename_hCollloose);
  TFile *data_file_hCollloose = new TFile(data_filename_hCollloose);

  //----Histograms----

  //Systematics on Emiss
  TH1F *simcPm_sysEm_nominal = 0;
  TH1F *simcPm_sysEm_loose   = 0;
  TH1F *simcPm_sysEm_tight   = 0;

  TH1F *dataPm_sysEm_nominal = 0;
  TH1F *dataPm_sysEm_loose   = 0;
  TH1F *dataPm_sysEm_tight   = 0;

  //Systematics on HMS delta
  TH1F *simcPm_syshdelta_nominal = 0;
  TH1F *simcPm_syshdelta_loose   = 0;
  TH1F *simcPm_syshdelta_tight   = 0;

  TH1F *dataPm_syshdelta_nominal = 0;
  TH1F *dataPm_syshdelta_loose   = 0;
  TH1F *dataPm_syshdelta_tight   = 0;

  //Systematics on SHMS delta
  TH1F *simcPm_sysedelta_nominal = 0;
  TH1F *simcPm_sysedelta_loose   = 0;
  TH1F *simcPm_sysedelta_tight   = 0;

  TH1F *dataPm_sysedelta_nominal = 0;
  TH1F *dataPm_sysedelta_loose   = 0;
  TH1F *dataPm_sysedelta_tight   = 0;

  //Systematics on Ztar Difference
  TH1F *simcPm_sysZtarDiff_nominal = 0;
  TH1F *simcPm_sysZtarDiff_loose = 0;
  TH1F *simcPm_sysZtarDiff_tight = 0;

  TH1F *dataPm_sysZtarDiff_nominal = 0;
  TH1F *dataPm_sysZtarDiff_loose = 0;
  TH1F *dataPm_sysZtarDiff_tight = 0;

  //Systematics on HMS Collimator Cut
  TH1F *simcPm_syshColl_nominal = 0;
  TH1F *simcPm_syshColl_loose = 0;
  TH1F *simcPm_syshColl_tight = 0;

  TH1F *dataPm_syshColl_nominal = 0;
  TH1F *dataPm_syshColl_loose = 0;
  TH1F *dataPm_syshColl_tight = 0;

  //Systematics on SHMS EtotTrackNorm
  TH1F *dataPm_sysEtotTrkNorm_nominal = 0;
  TH1F *dataPm_sysEtotTrkNorm_loose = 0;
  TH1F *dataPm_sysEtotTrkNorm_tight = 0;

  //Systematics on Coin. Time
  TH1F *dataPm_sysCtime_nominal = 0;
  TH1F *dataPm_sysCtime_loose = 0;
  TH1F *dataPm_sysCtime_tight = 0;

  TH1F *simcPm_nominal = 0;     //This should be the nominal Pmiss with all nominal cuts
                                //There is no SHMS Cal./COin time CUt on SIMC, so we divide by this quantity.


  //Get Tight/Loose Collimator Histograms (They are called 'nominal' in the root file, but are really NOT)
  simc_file_hColltight->cd();
  simc_file_hColltight->GetObject("H_Pm_syshColl_nominal", simcPm_syshColl_tight);
  
  simc_file_hCollloose->cd();
  simc_file_hCollloose->GetObject("H_Pm_syshColl_nominal", simcPm_syshColl_loose);

  data_file_hColltight->cd();
  data_file_hColltight->GetObject("H_Pm_syshColl_nominal", dataPm_syshColl_tight);
  
  data_file_hCollloose->cd();
  data_file_hCollloose->GetObject("H_Pm_syshColl_nominal", dataPm_syshColl_loose);


  //Get Histograms
  simc_file->cd();

  simc_file->GetObject("H_Pm", simcPm_nominal);  //Used to divide Cal. and coin time cuts systematics


  simc_file->GetObject("H_Pm_sysEm_nominal", simcPm_sysEm_nominal);
  simc_file->GetObject("H_Pm_sysEm_loose",   simcPm_sysEm_loose);
  simc_file->GetObject("H_Pm_sysEm_tight",   simcPm_sysEm_tight);

  simc_file->GetObject("H_Pm_syshdelta_nominal", simcPm_syshdelta_nominal);
  simc_file->GetObject("H_Pm_syshdelta_loose",   simcPm_syshdelta_loose);
  simc_file->GetObject("H_Pm_syshdelta_tight",   simcPm_syshdelta_tight);

  simc_file->GetObject("H_Pm_sysedelta_nominal", simcPm_sysedelta_nominal);
  simc_file->GetObject("H_Pm_sysedelta_loose",   simcPm_sysedelta_loose);
  simc_file->GetObject("H_Pm_sysedelta_tight",   simcPm_sysedelta_tight);

  simc_file->GetObject("H_Pm_sysZtarDiff_nominal", simcPm_sysZtarDiff_nominal);
  simc_file->GetObject("H_Pm_sysZtarDiff_loose",   simcPm_sysZtarDiff_loose);
  simc_file->GetObject("H_Pm_sysZtarDiff_tight",   simcPm_sysZtarDiff_tight);
  
  simc_file->GetObject("H_Pm_syshColl_nominal", simcPm_syshColl_nominal);


  data_file->cd();
  data_file->GetObject("H_Pm_sysEm_nominal", dataPm_sysEm_nominal);
  data_file->GetObject("H_Pm_sysEm_loose",   dataPm_sysEm_loose);
  data_file->GetObject("H_Pm_sysEm_tight",   dataPm_sysEm_tight);
  
  data_file->GetObject("H_Pm_syshdelta_nominal", dataPm_syshdelta_nominal);
  data_file->GetObject("H_Pm_syshdelta_loose",   dataPm_syshdelta_loose);
  data_file->GetObject("H_Pm_syshdelta_tight",   dataPm_syshdelta_tight);

  data_file->GetObject("H_Pm_sysedelta_nominal", dataPm_sysedelta_nominal);
  data_file->GetObject("H_Pm_sysedelta_loose",   dataPm_sysedelta_loose);
  data_file->GetObject("H_Pm_sysedelta_tight",   dataPm_sysedelta_tight);

  data_file->GetObject("H_Pm_sysZtarDiff_nominal", dataPm_sysZtarDiff_nominal);
  data_file->GetObject("H_Pm_sysZtarDiff_loose",   dataPm_sysZtarDiff_loose);
  data_file->GetObject("H_Pm_sysZtarDiff_tight",   dataPm_sysZtarDiff_tight);

  data_file->GetObject("H_Pm_sysEtotTrkNorm_nominal", dataPm_sysEtotTrkNorm_nominal);
  data_file->GetObject("H_Pm_sysEtotTrkNorm_loose",   dataPm_sysEtotTrkNorm_loose);
  data_file->GetObject("H_Pm_sysEtotTrkNorm_tight",   dataPm_sysEtotTrkNorm_tight);

  data_file->GetObject("H_Pm_sysCtime_nominal", dataPm_sysCtime_nominal);
  data_file->GetObject("H_Pm_sysCtime_loose",   dataPm_sysCtime_loose);
  data_file->GetObject("H_Pm_sysCtime_tight",   dataPm_sysCtime_tight);

  data_file->GetObject("H_Pm_syshColl_nominal", dataPm_syshColl_nominal);

  //Take the Ratio of DATA/SIMC Missing Momentum Yield
  dataPm_sysEm_nominal->Divide(simcPm_sysEm_nominal);
  dataPm_sysEm_loose->Divide(simcPm_sysEm_loose);
  dataPm_sysEm_tight->Divide(simcPm_sysEm_tight);
  
  dataPm_syshdelta_nominal->Divide(simcPm_syshdelta_nominal);
  dataPm_syshdelta_loose->Divide(simcPm_syshdelta_loose);
  dataPm_syshdelta_tight->Divide(simcPm_syshdelta_tight);

  dataPm_sysedelta_nominal->Divide(simcPm_sysedelta_nominal);
  dataPm_sysedelta_loose->Divide(simcPm_sysedelta_loose);
  dataPm_sysedelta_tight->Divide(simcPm_sysedelta_tight);
  
  dataPm_sysZtarDiff_nominal->Divide(simcPm_sysZtarDiff_nominal);
  dataPm_sysZtarDiff_loose->Divide(simcPm_sysZtarDiff_loose);
  dataPm_sysZtarDiff_tight->Divide(simcPm_sysZtarDiff_tight);

  dataPm_syshColl_nominal->Divide(simcPm_syshColl_nominal);
  dataPm_syshColl_loose->Divide(simcPm_syshColl_loose);
  dataPm_syshColl_tight->Divide(simcPm_syshColl_tight);
  
  dataPm_sysEtotTrkNorm_nominal->Divide(simcPm_nominal);
  dataPm_sysEtotTrkNorm_loose->Divide(simcPm_nominal);
  dataPm_sysEtotTrkNorm_tight->Divide(simcPm_nominal);

  dataPm_sysCtime_nominal->Divide(simcPm_nominal);
  dataPm_sysCtime_loose->Divide(simcPm_nominal);
  dataPm_sysCtime_tight->Divide(simcPm_nominal);



  //----Plot Pm_data / Pm_simc Ratio---- 
  //NOTE:The data histos are now actually the ratio, as they get updated when h1->Divide(h2) ==> h1=h1/h2 which is the ratio
  TCanvas *c1 = new TCanvas("c1", "", 1500, 900);
  c1->Divide(4,2);
  
  //Em Systematics
  c1->cd(1);
  //nominal
  dataPm_sysEm_nominal->Draw();
  dataPm_sysEm_nominal->SetMarkerColor(kBlack);
  dataPm_sysEm_nominal->SetLineColor(kBlack);
  dataPm_sysEm_nominal->SetMarkerStyle(20);
  dataPm_sysEm_nominal->SetMarkerSize(1.5);
  dataPm_sysEm_nominal->SetLineWidth(2);
  //loose
  dataPm_sysEm_loose->Draw("sames");
  dataPm_sysEm_loose->SetMarkerColor(kBlue);
  dataPm_sysEm_loose->SetLineColor(kBlue);
  dataPm_sysEm_loose->SetMarkerStyle(21);
  dataPm_sysEm_loose->SetMarkerSize(1.5);
  dataPm_sysEm_loose->SetLineWidth(2);
  //tight
  dataPm_sysEm_tight->Draw("sames");
  dataPm_sysEm_tight->SetMarkerColor(kRed);
  dataPm_sysEm_tight->SetLineColor(kRed);
  dataPm_sysEm_tight->SetMarkerStyle(22);
  dataPm_sysEm_tight->SetMarkerSize(1.5);
  dataPm_sysEm_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_sysEm_nominal->SetTitle("P_{m} Yield Ratio: E_{miss} Systematics");
  dataPm_sysEm_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_sysEm_nominal->GetXaxis()->CenterTitle();
  dataPm_sysEm_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_sysEm_nominal->GetYaxis()->CenterTitle();
  dataPm_sysEm_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_sysEm_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_sysEm_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_sysEm_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_sysEm_nominal->GetXaxis()->SetRangeUser(0, 0.35);

  //HMS Delta Systematics
  c1->cd(2);
  //nominal
  dataPm_syshdelta_nominal->Draw();
  dataPm_syshdelta_nominal->SetMarkerColor(kBlack);
  dataPm_syshdelta_nominal->SetLineColor(kBlack);
  dataPm_syshdelta_nominal->SetMarkerStyle(20);
  dataPm_syshdelta_nominal->SetMarkerSize(1.5);
  dataPm_syshdelta_nominal->SetLineWidth(2);
  //loose
  dataPm_syshdelta_loose->Draw("sames");
  dataPm_syshdelta_loose->SetMarkerColor(kBlue);
  dataPm_syshdelta_loose->SetLineColor(kBlue);
  dataPm_syshdelta_loose->SetMarkerStyle(21);
  dataPm_syshdelta_loose->SetMarkerSize(1.5);
  dataPm_syshdelta_loose->SetLineWidth(2);
  //tight
  dataPm_syshdelta_tight->Draw("sames");
  dataPm_syshdelta_tight->SetMarkerColor(kRed);
  dataPm_syshdelta_tight->SetLineColor(kRed);
  dataPm_syshdelta_tight->SetMarkerStyle(22);
  dataPm_syshdelta_tight->SetMarkerSize(1.5);
  dataPm_syshdelta_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_syshdelta_nominal->SetTitle("P_{m} Yield Ratio: HMS #delta Systematics");
  dataPm_syshdelta_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_syshdelta_nominal->GetXaxis()->CenterTitle();
  dataPm_syshdelta_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_syshdelta_nominal->GetYaxis()->CenterTitle();
  dataPm_syshdelta_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_syshdelta_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_syshdelta_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_syshdelta_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_syshdelta_nominal->GetXaxis()->SetRangeUser(0, 0.35);
  
  //SHMS Delta Systematics
  c1->cd(3);
  //nominal
  dataPm_sysedelta_nominal->Draw();
  dataPm_sysedelta_nominal->SetMarkerColor(kBlack);
  dataPm_sysedelta_nominal->SetLineColor(kBlack);
  dataPm_sysedelta_nominal->SetMarkerStyle(20);
  dataPm_sysedelta_nominal->SetMarkerSize(1.5);
  dataPm_sysedelta_nominal->SetLineWidth(2);
  //loose
  dataPm_sysedelta_loose->Draw("sames");
  dataPm_sysedelta_loose->SetMarkerColor(kBlue);
  dataPm_sysedelta_loose->SetLineColor(kBlue);
  dataPm_sysedelta_loose->SetMarkerStyle(21);
  dataPm_sysedelta_loose->SetMarkerSize(1.5);
  dataPm_sysedelta_loose->SetLineWidth(2);
  //tight
  dataPm_sysedelta_tight->Draw("sames");
  dataPm_sysedelta_tight->SetMarkerColor(kRed);
  dataPm_sysedelta_tight->SetLineColor(kRed);
  dataPm_sysedelta_tight->SetMarkerStyle(22);
  dataPm_sysedelta_tight->SetMarkerSize(1.5);
  dataPm_sysedelta_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_sysedelta_nominal->SetTitle("P_{m} Yield Ratio: SHMS #delta Systematics");
  dataPm_sysedelta_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_sysedelta_nominal->GetXaxis()->CenterTitle();
  dataPm_sysedelta_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_sysedelta_nominal->GetYaxis()->CenterTitle();
  dataPm_sysedelta_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_sysedelta_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_sysedelta_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_sysedelta_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_sysedelta_nominal->GetXaxis()->SetRangeUser(0, 0.35);

  //ZtarDiff Systematics
  c1->cd(4);
  //nominal
  dataPm_sysZtarDiff_nominal->Draw();
  dataPm_sysZtarDiff_nominal->SetMarkerColor(kBlack);
  dataPm_sysZtarDiff_nominal->SetLineColor(kBlack);
  dataPm_sysZtarDiff_nominal->SetMarkerStyle(20);
  dataPm_sysZtarDiff_nominal->SetMarkerSize(1.5);
  dataPm_sysZtarDiff_nominal->SetLineWidth(2);
  //loose
  dataPm_sysZtarDiff_loose->Draw("sames");
  dataPm_sysZtarDiff_loose->SetMarkerColor(kBlue);
  dataPm_sysZtarDiff_loose->SetLineColor(kBlue);
  dataPm_sysZtarDiff_loose->SetMarkerStyle(21);
  dataPm_sysZtarDiff_loose->SetMarkerSize(1.5);
  dataPm_sysZtarDiff_loose->SetLineWidth(2);
  //tight
  dataPm_sysZtarDiff_tight->Draw("sames");
  dataPm_sysZtarDiff_tight->SetMarkerColor(kRed);
  dataPm_sysZtarDiff_tight->SetLineColor(kRed);
  dataPm_sysZtarDiff_tight->SetMarkerStyle(22);
  dataPm_sysZtarDiff_tight->SetMarkerSize(1.5);
  dataPm_sysZtarDiff_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_sysZtarDiff_nominal->SetTitle("P_{m} Yield Ratio: Z_{tar} Diff Systematics");
  dataPm_sysZtarDiff_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_sysZtarDiff_nominal->GetXaxis()->CenterTitle();
  dataPm_sysZtarDiff_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_sysZtarDiff_nominal->GetYaxis()->CenterTitle();
  dataPm_sysZtarDiff_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_sysZtarDiff_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_sysZtarDiff_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_sysZtarDiff_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_sysZtarDiff_nominal->GetXaxis()->SetRangeUser(0, 0.35);

  //HMS Collimator Systematics
  c1->cd(5);
  //nominal
  dataPm_syshColl_nominal->Draw();
  dataPm_syshColl_nominal->SetMarkerColor(kBlack);
  dataPm_syshColl_nominal->SetLineColor(kBlack);
  dataPm_syshColl_nominal->SetMarkerStyle(20);
  dataPm_syshColl_nominal->SetMarkerSize(1.5);
  dataPm_syshColl_nominal->SetLineWidth(2);
  //loose
  dataPm_syshColl_loose->Draw("sames");
  dataPm_syshColl_loose->SetMarkerColor(kBlue);
  dataPm_syshColl_loose->SetLineColor(kBlue);
  dataPm_syshColl_loose->SetMarkerStyle(21);
  dataPm_syshColl_loose->SetMarkerSize(1.5);
  dataPm_syshColl_loose->SetLineWidth(2);
  //tight
  dataPm_syshColl_tight->Draw("sames");
  dataPm_syshColl_tight->SetMarkerColor(kRed);
  dataPm_syshColl_tight->SetLineColor(kRed);
  dataPm_syshColl_tight->SetMarkerStyle(22);
  dataPm_syshColl_tight->SetMarkerSize(1.5);
  dataPm_syshColl_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_syshColl_nominal->SetTitle("P_{m} Yield Ratio: HMS Collimator Systematics");
  dataPm_syshColl_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_syshColl_nominal->GetXaxis()->CenterTitle();
  dataPm_syshColl_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_syshColl_nominal->GetYaxis()->CenterTitle();
  dataPm_syshColl_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_syshColl_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_syshColl_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_syshColl_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_syshColl_nominal->GetXaxis()->SetRangeUser(0, 0.35);

  //SHMS EtotTrackNorm Systematics
  c1->cd(6);
  //nominal
  dataPm_sysEtotTrkNorm_nominal->Draw();
  dataPm_sysEtotTrkNorm_nominal->SetMarkerColor(kBlack);
  dataPm_sysEtotTrkNorm_nominal->SetLineColor(kBlack);
  dataPm_sysEtotTrkNorm_nominal->SetMarkerStyle(20);
  dataPm_sysEtotTrkNorm_nominal->SetMarkerSize(1.5);
  dataPm_sysEtotTrkNorm_nominal->SetLineWidth(2);
  //loose
  dataPm_sysEtotTrkNorm_loose->Draw("sames");
  dataPm_sysEtotTrkNorm_loose->SetMarkerColor(kBlue);
  dataPm_sysEtotTrkNorm_loose->SetLineColor(kBlue);
  dataPm_sysEtotTrkNorm_loose->SetMarkerStyle(21);
  dataPm_sysEtotTrkNorm_loose->SetMarkerSize(1.5);
  dataPm_sysEtotTrkNorm_loose->SetLineWidth(2);
  //tight
  dataPm_sysEtotTrkNorm_tight->Draw("sames");
  dataPm_sysEtotTrkNorm_tight->SetMarkerColor(kRed);
  dataPm_sysEtotTrkNorm_tight->SetLineColor(kRed);
  dataPm_sysEtotTrkNorm_tight->SetMarkerStyle(22);
  dataPm_sysEtotTrkNorm_tight->SetMarkerSize(1.5);
  dataPm_sysEtotTrkNorm_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_sysEtotTrkNorm_nominal->SetTitle("P_{m} Yield Ratio: E_{tot}TrkNorm Systematics");
  dataPm_sysEtotTrkNorm_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_sysEtotTrkNorm_nominal->GetXaxis()->CenterTitle();
  dataPm_sysEtotTrkNorm_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_sysEtotTrkNorm_nominal->GetYaxis()->CenterTitle();
  dataPm_sysEtotTrkNorm_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_sysEtotTrkNorm_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_sysEtotTrkNorm_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_sysEtotTrkNorm_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_sysEtotTrkNorm_nominal->GetXaxis()->SetRangeUser(0, 0.35);

  //Coin Time Systematics
  c1->cd(7);
  //nominal
  dataPm_sysCtime_nominal->Draw();
  dataPm_sysCtime_nominal->SetMarkerColor(kBlack);
  dataPm_sysCtime_nominal->SetLineColor(kBlack);
  dataPm_sysCtime_nominal->SetMarkerStyle(20);
  dataPm_sysCtime_nominal->SetMarkerSize(1.5);
  dataPm_sysCtime_nominal->SetLineWidth(2);
  //loose
  dataPm_sysCtime_loose->Draw("sames");
  dataPm_sysCtime_loose->SetMarkerColor(kBlue);
  dataPm_sysCtime_loose->SetLineColor(kBlue);
  dataPm_sysCtime_loose->SetMarkerStyle(21);
  dataPm_sysCtime_loose->SetMarkerSize(1.5);
  dataPm_sysCtime_loose->SetLineWidth(2);
  //tight
  dataPm_sysCtime_tight->Draw("sames");
  dataPm_sysCtime_tight->SetMarkerColor(kRed);
  dataPm_sysCtime_tight->SetLineColor(kRed);
  dataPm_sysCtime_tight->SetMarkerStyle(22);
  dataPm_sysCtime_tight->SetMarkerSize(1.5);
  dataPm_sysCtime_tight->SetLineWidth(2);
  //Set Title/Label 
  dataPm_sysCtime_nominal->SetTitle("P_{m} Yield Ratio: Coin. Time Systematics");
  dataPm_sysCtime_nominal->GetXaxis()->SetTitle("Missing Momentum, P_{m} [GeV]");
  dataPm_sysCtime_nominal->GetXaxis()->CenterTitle();
  dataPm_sysCtime_nominal->GetYaxis()->SetTitle("P_{m}^{data} / P_{m}^{simc}");
  dataPm_sysCtime_nominal->GetYaxis()->CenterTitle();
  dataPm_sysCtime_nominal->GetXaxis()->SetLabelFont(22);
  dataPm_sysCtime_nominal->GetYaxis()->SetLabelFont(22);
  dataPm_sysCtime_nominal->GetXaxis()->SetTitleFont(22);
  dataPm_sysCtime_nominal->GetYaxis()->SetTitleFont(22);
  //Set Axis Limits
  dataPm_sysCtime_nominal->GetXaxis()->SetRangeUser(0, 0.35);


  /*
    Are the Systematic Effects Significant?   Use Roger Barlow approach in: Systematics: Facts and Fictions
    
    (Consider a measurement done two different ways (e.g. apply different cuts). Let the measurements and its uncertainty be:
    (a1, sig_1) and (a2, sig_2) where 'sig' is the error bar or standard deviation of the measurement 'a'.
    The difference, delta = a1 - a2 then has an associated uncertainty, (sig_delta)**2 = sig_1**2 - sig_2**2  (this is the difference of their variances)
    Then, if delta / sig_delta > 2 (or the measurement difference is greater than two standard deviations) then it is considere a significant difference.
  */

  
  //Call GetBinInfo(TH1F* h1, ofname="", comments="")  to get bin information of relevant histos to work with later on.
  //The output is a txt file with the bin information

  GetBinInfo(dataPm_sysEm_nominal, "binInfo_sysEm_nominal.txt", "Bin Information for Systematics Studies using nominal Emiss cuts Yield Ratio for Deuteron 80 MeV.");
  GetBinInfo(dataPm_sysEm_loose, "binInfo_sysEm_loose.txt", "Bin Information for Systematics Studies using loose Emiss cuts on  Yield Ratio for Deuteron 80 MeV.");
  GetBinInfo(dataPm_sysEm_tight, "binInfo_sysEm_tight.txt", "Bin Information for Systematics Studies using tight Emiss cuts on  Yield Ratio for Deuteron 80 MeV.");


  

}
