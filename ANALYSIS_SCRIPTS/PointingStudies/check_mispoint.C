#include "set_heep_histos.h"

void check_mispoint()
{
  
  //gROOT->SetBatch(1);
  TString hadron_arm;
  TString electron_arm;
  
  hadron_arm = "SHMS";
  electron_arm = "HMS";
  
  TString file_path ="../../../../ROOTfiles/";
  
  TString file1 = file_path+"hms_replay_delta_scan_1161_noOffset.root";
  TString file2 = file_path+"hms_replay_delta_scan_1161_gBeamOffset.root";
  
  
  TFile *f1 = new TFile(file1, "READ");
  TFile *f2 = new TFile(file2, "READ");
  
  f1->cd();
  TTree *T1 = (TTree*)f1->Get("T");

  f2->cd();
  TTree *T2 = (TTree*)f2->Get("T");

  TH1F *data_eytar = new TH1F("data_eytar", "", 100, -0.1, 0.1);
  
  TCanvas *c1 = new TCanvas("c1", "", 2000, 1000);
  c1->Divide(4,2);
  
  f1->cd();

  //Target Recon. Variable (in Hall Coord. System)
  c1->cd(1);
  T1->Draw("H.gtr.y>>data_eytar_NO_Offset(100,-5,5)");

  c1->cd(2);
  T1->Draw("H.gtr.th>>data_exptar_NO_Offset(100,-0.1,0.1)");

  c1->cd(3);
  T1->Draw("H.gtr.ph>>data_eyptar_NO_Offset(100,-0.1,0.1)");

  c1->cd(4);
  T1->Draw("H.gtr.dp>>data_edelta_NO_Offset(100, -10, 10)");
 
  c1->cd(5);
  T1->Draw("H.react.x>>data_xtar_NO_Offset(100, -.5, .5)");
  
  c1->cd(6);
  T1->Draw("H.react.y>>data_ytar_NO_Offset(100, -.5, .5)");
  
  c1->cd(7);
  T1->Draw("H.react.z>>data_ztar_NO_Offset(100, -10, 10)");
  
  f2->cd();

  //Target Recon. Variable (in Hall Coord. System)
  c1->cd(1);
  T2->Draw("H.gtr.y>>data_eytar(100,-5,5)", "", "sames");

  c1->cd(2);
  T2->Draw("H.gtr.th>>data_exptar(100,-0.1,0.1)", "", "sames");

  c1->cd(3);
  T2->Draw("H.gtr.ph>>data_eyptar(100,-0.1,0.1)", "", "sames");

  c1->cd(4);
  T2->Draw("H.gtr.dp>>data_edelta(100, -10, 10)", "", "sames");
 
  c1->cd(5);
  T2->Draw("H.react.x>>data_xtar(100, -.5, .5)", "", "sames");
 
  c1->cd(6);
  T2->Draw("H.react.y>>data_ytar(100, -.5, .5)", "", "sames");
  
  c1->cd(7);
  T2->Draw("H.react.z>>data_ztar(100, -10, 10)", "", "sames");
  
}
