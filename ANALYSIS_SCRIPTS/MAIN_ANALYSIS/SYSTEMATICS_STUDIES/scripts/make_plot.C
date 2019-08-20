//This code reads in the combined ROOTfiles for each of the D(e,e'p)n
//Kinematic Settings and plots them to determine where to place the cuts
//fot systematic studies

void make_plot(int pm_set, string model, int data_set, string sys_ext)
{

  //NOMINAL CUTS (Used in drawing a line)
  Double_t Emin=-0.02;
  Double_t Emax=0.04;
    
  Double_t hdel_min=-8.;
  Double_t hdel_max=8.;

  Double_t edel_min=-10.;
  Double_t edel_max=22.;

  Double_t ztd_min=-2.;
  Double_t ztd_max=2.;

  Double_t Q2_min=4.;
  Double_t Q2_max=5.;

  Double_t thnq_min=35.;
  Double_t thnq_max=45.;

  Double_t pcal_min=0.7;
  Double_t pcal_max=5.;
  
  Double_t ctime_min=10.5;
  Double_t ctime_max=14.5;
  

  //SYSTEMATICS CUTS (Used in drawing a line)
  Double_t sysEmin=-0.02;
  Double_t sysEmax=0.04;

  Double_t sys_ztd_min=-2.;
  Double_t sys_ztd_max=2.;

  Double_t sys_pcal_min=0.7;
  Double_t sys_pcal_max=5.;
  
  Double_t sys_ctime_min=10.5;
  Double_t sys_ctime_max=14.5;


  // int pm_set = 580;
  // int data_set = 1;
  // string model="fsi";

  //ROOTfile names
  TString simc_filename = Form("../../root_files/pm%i_%sXsec_set%i_%s/deep_simc_histos_pm%i_laget%s_rad_set%i.root", pm_set, model.c_str(), data_set, sys_ext.c_str(), pm_set, model.c_str(), data_set);
  TString data_filename = Form( "../../root_files/pm%i_%sXsec_set%i_%s/deep_data_histos_pm%i_set%i_combined.root", pm_set, model.c_str(), data_set, sys_ext.c_str(), pm_set, data_set);
  
  //Open ROOTfile
  TFile *simc_file = new TFile(simc_filename);
  TFile *data_file = new TFile(data_filename);
 
  //----Histograms----
  //DATA
  TH1F *data_Em = 0;
  TH1F *data_hdelta = 0;
  TH1F *data_edelta = 0;
  TH1F *data_ztarDiff = 0;
  TH1F *data_Q2 = 0;
  TH1F *data_thnq = 0;
  TH2F *data_hColl = 0;
  //Specific to data
  TH1F *data_pcalEtotTrkNorm = 0;
  TH1F *data_CoinTime = 0;
  //SIMC 
  TH1F *simc_Em = 0;
  TH1F *simc_hdelta = 0;
  TH1F *simc_edelta = 0;
  TH1F *simc_ztarDiff = 0;
  TH1F *simc_Q2 = 0;
  TH1F *simc_thnq = 0;
  TH2F *simc_hColl = 0;

  //Get DATA Histograms
  //DATA
  data_file->cd();
  data_file->GetObject("H_Em_nuc_sys", data_Em);
  data_file->GetObject("H_hdelta_sys", data_hdelta);
  data_file->GetObject("H_edelta_sys", data_edelta);
  data_file->GetObject("H_ztar_diff_sys", data_ztarDiff);
  data_file->GetObject("H_Q2_sys", data_Q2);
  data_file->GetObject("H_theta_nq_sys", data_thnq);
  data_file->GetObject("H_hXColl_vs_hYColl_sys", data_hColl);
  
  data_file->GetObject("H_pcal_etotTrkNorm_sys", data_pcalEtotTrkNorm);
  data_file->GetObject("H_ctime_sys", data_CoinTime);
  //SIMC
  simc_file->cd();
  simc_file->GetObject("H_Em_nuc_sys", simc_Em);
  simc_file->GetObject("H_hdelta_sys", simc_hdelta);
  simc_file->GetObject("H_edelta_sys", simc_edelta);
  simc_file->GetObject("H_ztar_diff_sys", simc_ztarDiff);
  simc_file->GetObject("H_Q2_sys", simc_Q2);
  simc_file->GetObject("H_theta_nq_sys", simc_thnq);
  simc_file->GetObject("H_hXColl_vs_hYColl_sys", simc_hColl);

  //Set Vertical Cut Lines
  TLine *l_Emin = new TLine(Emin,0, Emin, simc_Em->GetMaximum());
  TLine *l_Emax = new TLine(Emax,0, Emax, simc_Em->GetMaximum());
  l_Emin->SetLineColor(kBlack);
  l_Emin->SetLineStyle(2);
  l_Emin->SetLineWidth(3);
  l_Emax->SetLineColor(kBlack);
  l_Emax->SetLineStyle(2);
  l_Emax->SetLineWidth(3);

  TLine *l_hdelmin = new TLine(hdel_min,0, hdel_min, simc_hdelta->GetMaximum());
  TLine *l_hdelmax = new TLine(hdel_max,0, hdel_max, simc_hdelta->GetMaximum());
  l_hdelmin->SetLineColor(kBlack);
  l_hdelmin->SetLineStyle(2);
  l_hdelmin->SetLineWidth(3);
  l_hdelmax->SetLineColor(kBlack);
  l_hdelmax->SetLineStyle(2);
  l_hdelmax->SetLineWidth(3);

  TLine *l_edelmin = new TLine(edel_min,0, edel_min, simc_edelta->GetMaximum());
  TLine *l_edelmax = new TLine(edel_max,0, edel_max, simc_edelta->GetMaximum());
  l_edelmin->SetLineColor(kBlack);
  l_edelmin->SetLineStyle(2);
  l_edelmin->SetLineWidth(3);
  l_edelmax->SetLineColor(kBlack);
  l_edelmax->SetLineStyle(2);
  l_edelmax->SetLineWidth(3);
  
  TLine *l_ztd_min = new TLine(ztd_min,0, ztd_min, simc_ztarDiff->GetMaximum());
  TLine *l_ztd_max = new TLine(ztd_max,0, ztd_max, simc_ztarDiff->GetMaximum());
  l_ztd_min->SetLineColor(kBlack);
  l_ztd_min->SetLineStyle(2);
  l_ztd_min->SetLineWidth(3);
  l_ztd_max->SetLineColor(kBlack);
  l_ztd_max->SetLineStyle(2);
  l_ztd_max->SetLineWidth(3);

  TLine *l_Q2_min = new TLine(Q2_min,0, Q2_min, simc_Q2->GetMaximum());
  TLine *l_Q2_max = new TLine(Q2_max,0, Q2_max, simc_Q2->GetMaximum());
  l_Q2_min->SetLineColor(kBlack);
  l_Q2_min->SetLineStyle(2);
  l_Q2_min->SetLineWidth(3);
  l_Q2_max->SetLineColor(kBlack);
  l_Q2_max->SetLineStyle(2);
  l_Q2_max->SetLineWidth(3);

  TLine *l_thnq_min = new TLine(thnq_min,0, thnq_min, simc_thnq->GetMaximum());
  TLine *l_thnq_max = new TLine(thnq_max,0, thnq_max, simc_thnq->GetMaximum());
  l_thnq_min->SetLineColor(kBlack);
  l_thnq_min->SetLineStyle(2);
  l_thnq_min->SetLineWidth(3);
  l_thnq_max->SetLineColor(kBlack);
  l_thnq_max->SetLineStyle(2);
  l_thnq_max->SetLineWidth(3);

  TLine *l_pcal_min = new TLine(pcal_min,0, pcal_min, data_pcalEtotTrkNorm->GetMaximum());
  TLine *l_pcal_max = new TLine(pcal_max,0, pcal_max, data_pcalEtotTrkNorm->GetMaximum());
  l_pcal_min->SetLineColor(kBlack);
  l_pcal_min->SetLineStyle(2);
  l_pcal_min->SetLineWidth(3);
  l_pcal_max->SetLineColor(kBlack);
  l_pcal_max->SetLineStyle(2);
  l_pcal_max->SetLineWidth(3);

  TLine *l_ctime_min = new TLine(ctime_min,0, ctime_min, data_CoinTime->GetMaximum());
  TLine *l_ctime_max = new TLine(ctime_max,0, ctime_max, data_CoinTime->GetMaximum());
  l_ctime_min->SetLineColor(kBlack);
  l_ctime_min->SetLineStyle(2);
  l_ctime_min->SetLineWidth(3);
  l_ctime_max->SetLineColor(kBlack);
  l_ctime_max->SetLineStyle(2);
  l_ctime_max->SetLineWidth(3);

  //Set Histograms Aesthetics
  data_Em->SetLineColor(kBlue);
  data_Em->SetLineWidth(2);

  data_hdelta->SetLineColor(kBlue);
  data_hdelta->SetLineWidth(2);
  
  data_edelta->SetLineColor(kBlue);
  data_edelta->SetLineWidth(2);
  
  data_ztarDiff->SetLineColor(kBlue);
  data_ztarDiff->SetLineWidth(2);
  
  data_Q2->SetLineColor(kBlue);
  data_Q2->SetLineWidth(2);

  data_thnq->SetLineColor(kBlue);
  data_thnq->SetLineWidth(2);

  data_pcalEtotTrkNorm->SetLineColor(kBlue);
  data_pcalEtotTrkNorm->SetLineWidth(2);

  data_CoinTime->SetLineColor(kBlue);
  data_CoinTime->SetLineWidth(2);

  //----------------------------------
  simc_Em->SetLineColor(kRed);
  simc_Em->SetLineWidth(2);
 
  simc_hdelta->SetLineColor(kRed);
  simc_hdelta->SetLineWidth(2);
  
  simc_edelta->SetLineColor(kRed);
  simc_edelta->SetLineWidth(2);
  
  simc_ztarDiff->SetLineColor(kRed);
  simc_ztarDiff->SetLineWidth(2);
  
  simc_Q2->SetLineColor(kRed);
  simc_Q2->SetLineWidth(2);

  simc_thnq->SetLineColor(kRed);
  simc_thnq->SetLineWidth(2);

  TCanvas *c1 = new TCanvas("c1", "", 1500, 1500);
  c1->Divide(3,3);
  
  c1->cd(1);
  simc_Em->Draw();
  data_Em->Draw("same");
  l_Emin->Draw("same");
  l_Emax->Draw("same");

  c1->cd(2);
  simc_hdelta->Draw();
  data_hdelta->Draw("same"); 
  l_hdelmin->Draw("same");
  l_hdelmax->Draw("same");

  c1->cd(3);
  simc_edelta->Draw();
  data_edelta->Draw("same");
  l_edelmin->Draw("same");
  l_edelmax->Draw("same");

  c1->cd(4);
  simc_ztarDiff->Draw();
  data_ztarDiff->Draw("same");
  l_ztd_min->Draw("same");
  l_ztd_max->Draw("same");

  c1->cd(5);
  simc_Q2->Draw();
  data_Q2->Draw("same");
  l_Q2_min->Draw("same");
  l_Q2_max->Draw("same");

  c1->cd(6);
  simc_thnq->Draw();
  data_thnq->Draw("same");
  l_thnq_min->Draw("same");
  l_thnq_max->Draw("same");

  c1->cd(7);
  simc_hColl->Draw("colz");
  //data_hColl->Draw("colz");
  
  c1->cd(8);
  data_pcalEtotTrkNorm->Draw();
  l_pcal_min->Draw("same");
  l_pcal_max->Draw("same");

  c1->cd(9);
  data_CoinTime->Draw();
  l_ctime_min->Draw("same");
  l_ctime_max->Draw("same");

  c1->SaveAs(Form("../systematic_plots_%s/pm%i_%s_set%i_cuts.pdf", sys_ext.c_str(), pm_set, model.c_str(), data_set));

}
