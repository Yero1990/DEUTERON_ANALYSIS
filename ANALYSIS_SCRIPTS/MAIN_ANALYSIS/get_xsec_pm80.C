//Code to get preliminary cross setions from data / simc

//#include "../../simc_analysis/set_deep_histos.h"
void get_xsec_pm80()
{


  gStyle->SetOptStat(kFALSE);

  TString simc_fsi80 = "deep_simc_histos_3289.root";       
  //TString simc_pwia80 = "../../simc_analysis/D2simc_pm80_lagetpwia_rad_set1.root"; 
  
  TString data_pm80 = "deep_data_histos_3289.root";
  

  TFile *simc_fsi80_file = new TFile(simc_fsi80); 
  //TFile *simc_pwia80_file = new TFile(simc_pwia80); 

  TFile *data_pm80_file = new TFile(data_pm80);              



  
  //Create Histograms to store objects 
  TH1F *simcfsi80_cut_pm = 0;                                                              
  TH1F *simcpwia80_cut_pm = 0; 
  TH1F *simcpwia80_cut_pm_ps = 0;
  TH1F *simcfsi80_cut_pm_ps = 0; 
  TH1F *data80_cut_pm = 0;   
  TH1F *data80_cut_pm_LH2scaled = 0;   
  
  //DATA/SIMC Ratio for 80 MeV
  //  TH1F *ratio_pwia = new TH1F("ratio_pwia", "", Pm_nbins, Pm_xmin, Pm_xmax);
  TH1F *ratio_fsi = new TH1F("ratio_fsi", "", 100, -0.1, 0.5); 
    
  //TH1F *ratio_pwia_LH2scaled = new TH1F("ratio_pwia_LH2scaled", "", Pm_nbins, Pm_xmin, Pm_xmax);
  //TH1F *ratio_fsi_LH2scale = new TH1F("ratio_fsi_LH2scaled", "", Pm_nbins, Pm_xmin, Pm_xmax); 

  
  //  simcfsi80_cut_pm->Sumw2();
  
  //  simcpwia80_cut_pm->Sumw2();
  //simcpwia80_cut_pm_ps->Sumw2();
  //simcfsi80_cut_pm_ps->Sumw2();
  //data80_cut_pm->Sumw2();
  //data80_cut_pm_LH2scaled->Sumw2();
  
  ratio_fsi->Sumw2();
  //ratio_fsi_LH2scaled->Sumw2();
  
  
  //-----------------


  // ratio_pwia->GetXaxis()->SetTitle("Missing Momentum, Pm [GeV/c]");
  //ratio_pwia->GetXaxis()->CenterTitle();

  //ratio_pwia->GetYaxis()->SetTitle("Data / SIMC Yield Ratio Pm^{data} / Pm^{simc} "); 
  //ratio_pwia->GetYaxis()->CenterTitle();  
  
  //ratio_pwia->SetTitle("DATA / SIMC Yield Ratio");



  //------Get Histograms---------
  
    
  simc_fsi80_file->cd();
  simc_fsi80_file->GetObject("H_Pm", simcfsi80_cut_pm);
  //simc_fsi80_file->GetObject("cut_pm_ps",simcfsi80_cut_pm_ps); 

  //  simc_pwia80_file->cd();                                                 
  //simc_pwia80_file->GetObject("cut_pm", simcpwia80_cut_pm);                                                
  //simc_pwia80_file->GetObject("cut_pm_ps",simcpwia80_cut_pm_ps);       

  data_pm80_file->cd();
  data_pm80_file->GetObject("H_Pm", data80_cut_pm); 
  //  data_pm80_file->GetObject("cut_pm_LH2scale", data80_cut_pm_LH2scaled); 

  // ratio_pwia->Divide(data80_cut_pm, simcpwia80_cut_pm);
  ratio_fsi->Divide(data80_cut_pm, simcfsi80_cut_pm); 
  
  //ratio_pwia_LH2scaled->Divide(data80_cut_pm_LH2scaled, simcpwia80_cut_pm);
  //ratio_fsi_LH2scaled->Divide(data80_cut_pm_LH2scaled, simcfsi80_cut_pm);


  //ratio_pwia->SetMarkerStyle(20);
  //ratio_pwia->SetMarkerColor(kBlue); 
  ratio_fsi->SetMarkerStyle(20);
  ratio_fsi->SetMarkerColor(kRed); 


  //ratio_pwia_LH2scaled->SetMarkerStyle(20);
  //ratio_pwia_LH2scaled->SetMarkerColor(kRed); 
  //ratio_fsi_LH2scaled->SetMarkerStyle(20);
  //ratio_fsi_LH2scaled->SetMarkerColor(kRed);

  


  /*
  // Pm = 750 MeV

  simc_fsi750_file->cd();
  simc_fsi750_file->GetObject("cut_pm", simcfsi750_cut_pm);
  simc_fsi750_file->GetObject("cut_pm_ps",simcfsi750_cut_pm_ps); 
  
  data_750_file->cd();
  data_750_file->GetObject("cut_pm", data750_cut_pm); 

  ratio_data750->Divide(data750_cut_pm, simcfsi750_cut_pm_ps);
  ratio_data750->SetMarkerStyle(20);
  ratio_data750->SetMarkerColor(kBlue); 
  */

  //simc_cut_pm->Draw();
  //data_cut_pm->Draw("sames");

  /*
  TCanvas *c1 = new TCanvas("c1", "", 2000,2000);
  
  ratio_pwia->Draw("E1");
  ratio_pwia_LH2scaled->Draw("E1sames");

  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->SetHeader("D2, Pm = 80 MeV/c","C"); // option "C" allows to center the header
  legend->AddEntry(ratio_pwia,"PWIA","lep");
  legend->AddEntry(ratio_pwia_LH2scaled,"PWIA Scaled","lep"); 
  legend->Draw();
  */
  



  
  TCanvas *c2 = new TCanvas("c2", "", 2000,2000); 
  //ratio_pwia->GetXaxis()->SetRangeUser(0, 0.2);
  //ratio_fsi->GetXaxis()->SetRangeUser(0, 0.2); 
  ratio_fsi->Draw("E1");                                                                                                
  //  ratio_fsi_LH2scaled->Draw("E1sames");

  auto legend2 = new TLegend(0.1,0.7,0.48,0.9);                                                                                             
  legend2->SetHeader("D2, Pm = 80 MeV/c","C"); // option "C" allows to center the header                                           
  legend2->AddEntry(ratio_fsi,"FSI","lep");                                                                                       
  //legend2->AddEntry(ratio_pwia,"PWIA","lep");                                                                        
  legend2->Draw();    
  
}
