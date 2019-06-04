void make_profile()
{

  TString simc_fname = "deep_simc_histos_3289.root";
  TString data_fname = "deep_data_histos_3289.root";                   

  TFile *simc_file = new TFile(simc_fname, "READ"); 
  TFile *data_file = new TFile(data_fname, "READ"); 

  TProfile *simcEm_profile = new TProfile();
  TProfile *dataEm_profile = new TProfile(); 
                                                                 
  TH2F *simc_Em_vs_Pm = 0;  
  TH2F *data_Em_vs_Pm = 0; 

  simc_file->cd();
  simc_file->GetObject("H_Em_vs_Pm", simc_Em_vs_Pm);       

  data_file->cd();
  data_file->GetObject("H_Em_nuc_vs_Pm", data_Em_vs_Pm);

  simcEm_profile = simc_Em_vs_Pm->ProfileX("simcEmProfileX",1, 100);
  //simcEm_profile->Draw();

  dataEm_profile = data_Em_vs_Pm->ProfileX("dataEmProfileX",1, 100);                                             
  //dataEm_profile->Draw();

  TCanvas *c1 = new TCanvas("c1", "", 1800,1500);
  c1->Divide(2,2);

  c1->cd(1);
  simc_Em_vs_Pm->Draw("colz");
  c1->cd(2);
  simcEm_profile->Draw(); 
  c1->cd(3);                                                                                                                              
  data_Em_vs_Pm->Draw("colz");                                                                                             
  c1->cd(4);                                                                                                                        
  dataEm_profile->Draw();                                             
      

}
