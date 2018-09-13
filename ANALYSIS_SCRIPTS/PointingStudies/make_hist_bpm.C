#include <TSystem.h>
#include <TString.h>
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include <TNtuple.h>
#include "TCanvas.h"
#include <iostream>
#include <fstream>
#include "TMath.h"
#include "TH1F.h"
#include <TH2.h>
#include <TStyle.h>
#include <TGraph.h>
#include <TROOT.h>
#include <TMath.h>
#include <TLegend.h>
#include <TPaveLabel.h>
#include <TProfile.h>
#include <TObjArray.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include<math.h>
using namespace std;

void make_hist_bpm(){
  
  TString basename = "hms_replay_hscaler_1272_-1";
  Int_t nrun = 1272;
  if (basename=="") {
    cout << " Input the basename of the root file (assumed to be in worksim)" << endl;
    cin >> basename;
  }
  gStyle->SetPalette(1,0);
  gStyle->SetOptStat(11111);
  gStyle->SetOptFit(11);
  gStyle->SetTitleOffset(1.,"Y");
  gStyle->SetTitleOffset(.7,"X");
  gStyle->SetLabelSize(0.04,"XY");
  gStyle->SetTitleSize(0.06,"XY");
  gStyle->SetPadLeftMargin(0.12);
  TString inputroot;
  inputroot="../../../../ROOTfiles/"+basename+".root";
  TString outputhist;
  outputhist= basename+"_BPMhist.root";
 TObjArray HList(0);
 TString outputpdf;
 outputpdf=basename+".pdf";
 TString htitle=basename;
 TPaveLabel *title = new TPaveLabel(.15,.90,0.95,.99,htitle,"ndc");
 //
 TFile *fsimc = new TFile(inputroot); 
 TTree *tsimc = (TTree*) fsimc->Get("E");

 //Create OUTPUT ROOT file
 TFile *outROOT = new TFile(outputhist, "RECREATE");

 // Define branches
 Double_t  ibcm1;
 tsimc->SetBranchAddress("ibcm1",&ibcm1);
 Double_t  SAXpos;
 tsimc->SetBranchAddress("IPM3H07A.XPOS",&SAXpos);
 Double_t  SAXraw;
 tsimc->SetBranchAddress("IPM3H07A.XRAW",&SAXraw);
 Double_t  SAYpos;
 tsimc->SetBranchAddress("IPM3H07A.YPOS",&SAYpos);
 Double_t  SAYraw;
 tsimc->SetBranchAddress("IPM3H07A.YRAW",&SAYraw);
 Double_t  SBXpos;
 tsimc->SetBranchAddress("IPM3H07B.XPOS",&SBXpos);
 Double_t  SBXraw;
 tsimc->SetBranchAddress("IPM3H07B.XRAW",&SBXraw);
 Double_t  SBYpos;
 tsimc->SetBranchAddress("IPM3H07B.YPOS",&SBYpos);
 Double_t  SBYraw;
 tsimc->SetBranchAddress("IPM3H07B.YRAW",&SBYraw);
 Double_t  SCXpos;
 tsimc->SetBranchAddress("IPM3H07C.XPOS",&SCXpos);
 Double_t  SCXraw;
 tsimc->SetBranchAddress("IPM3H07C.XRAW",&SCXraw);
 Double_t  SCYpos;
 tsimc->SetBranchAddress("IPM3H07C.YPOS",&SCYpos);
 Double_t  SCYraw;
 tsimc->SetBranchAddress("IPM3H07C.YRAW",&SCYraw);
 Double_t Xtar_AB;
 Double_t Ytar_AB;
 Double_t Xtar_AC;
 Double_t Ytar_AC;
 Double_t Xtar_BC;
 Double_t Ytar_BC;
 // Define histograms
 TH1F *hSAXraw = new TH1F("hSAXraw",Form("Run %d ; SAX Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSAYraw = new TH1F("hSAYraw",Form("Run %d ; SAY Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSBXraw = new TH1F("hSBXraw",Form("Run %d ; SBX Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSBYraw = new TH1F("hSBYraw",Form("Run %d ; SBY Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSCXraw = new TH1F("hSCXraw",Form("Run %d ; SCX Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSCYraw = new TH1F("hSCYraw",Form("Run %d ; SCY Raw (mm); Counts",nrun),100,-5,5);
 TH1F *hSAXpos = new TH1F("hSAXpos",Form("Run %d ; SAX Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hSAYpos = new TH1F("hSAYpos",Form("Run %d ; SAY Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hSBXpos = new TH1F("hSBXpos",Form("Run %d ; SBX Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hSBYpos = new TH1F("hSBYpos",Form("Run %d ; SBY Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hSCXpos = new TH1F("hSCXpos",Form("Run %d ; SCX Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hSCYpos = new TH1F("hSCYpos",Form("Run %d ; SCY Pos (mm); Counts",nrun),100,-5,5);
 TH1F *hXtar = new TH1F("hXtar",Form("Run %d ; X target  (mm); Counts",nrun),100,-2,2);
 TH1F *hYtar = new TH1F("hYtar",Form("Run %d ; Y target  (mm); Counts",nrun),100,-2,2);
 TH1F *hXtar_AB = new TH1F("hXtar_AB",Form("Run %d ; X target (use AB) (mm); Counts",nrun),100,-2,2);
 TH1F *hYtar_AB = new TH1F("hYtar_AB",Form("Run %d ; Y target (use AB) (mm); Counts",nrun),100,-2,2);
 TH1F *hXtar_AC = new TH1F("hXtar_AC",Form("Run %d ; X target (use AC) (mm); Counts",nrun),100,-2,2);
 TH1F *hYtar_AC = new TH1F("hYtar_AC",Form("Run %d ; Y target (use AC) (mm); Counts",nrun),100,-2,2);
 TH1F *hXtar_BC = new TH1F("hXtar_BC",Form("Run %d ; X target (use BC) (mm); Counts",nrun),100,-2,2);
 TH1F *hYtar_BC = new TH1F("hYtar_BC",Form("Run %d ; Y target (use BC) (mm); Counts",nrun),100,-2,2);
 //
 // loop through data
 Double_t SA_zpos=370.82*10.; //mm
 Double_t SB_zpos=224.96*10.; //mm
 Double_t SC_zpos=129.3*10.; //mm
 Double_t zpos[3]={SA_zpos,SB_zpos,SC_zpos};
 Double_t xpos[3],ypos[3];
 Double_t SAX_off =  -0.12;
 Double_t SBX_off =  -0.06;
 Double_t SCX_off =  -1.01;
 Double_t SAY_off =  -0.44;
 Double_t SBY_off = +0.19;
 Double_t SCY_off = +0.55;
 Double_t SAX_scale = 1.00;
 Double_t SAY_scale = 0.96;
 Double_t SBX_scale = 1.24;
 Double_t SBY_scale = 1.19;
 Double_t SCX_scale = 0.94;
 Double_t SCY_scale = 0.84;
 TGraph* gr_xbeam;
 TGraph* gr_ybeam;
 Long64_t nentries = tsimc->GetEntries();
 for (int i = 0; i < nentries; i++) {
   tsimc->GetEntry(i);
   if (ibcm1>0.1) {
     hSAXraw->Fill(SAXraw);
     hSAYraw->Fill(SAYraw);
     hSBXraw->Fill(SBXraw);
     hSBYraw->Fill(SBYraw);
     hSCXraw->Fill(SCXraw);
     hSCYraw->Fill(SCYraw);
     SAXpos=SAX_off-SAX_scale*SAXraw;
     SAYpos=SAY_off+SAY_scale*SAYraw;
     SBXpos=SBX_off-SBX_scale*SBXraw;
     SBYpos=SBY_off+SBY_scale*SBYraw;
     SCXpos=SCX_off-SCX_scale*SCXraw;
     SCYpos=SCY_off+SCY_scale*SCYraw;
     xpos[0]=SAXpos;
     xpos[1]=SBXpos;
     xpos[2]=SCXpos;
     ypos[0]=SAYpos;
     ypos[1]=SBYpos;
     ypos[2]=SCYpos;
     gr_xbeam = new TGraph(3,zpos,xpos);
     gr_xbeam->SetMarkerSize(2.0);
     gr_xbeam->SetMarkerStyle(21);
     gr_ybeam = new TGraph(3,zpos,ypos);
     TF1 *xf1 = new TF1("xf1","[0]+[1]*x");
     gr_xbeam->Fit("xf1","Q");
     TF1 *yf1 = new TF1("yf1","[0]+[1]*x");
     gr_ybeam->Fit("yf1","Q");
     hSAXpos->Fill(SAXpos);
     hSAYpos->Fill(SAYpos);
     hSBXpos->Fill(SBXpos);
     hSBYpos->Fill(SBYpos);
     hSCXpos->Fill(SCXpos);
     hSCYpos->Fill(SCYpos);
     Xtar_AB = SAXpos - (SAXpos-SBXpos)/(SA_zpos-SB_zpos)*SA_zpos;
     Ytar_AB = SAYpos - (SAYpos-SBYpos)/(SA_zpos-SB_zpos)*SA_zpos;
     Xtar_AC = SAXpos - (SAXpos-SCXpos)/(SA_zpos-SC_zpos)*SA_zpos;
     Ytar_AC = SAYpos - (SAYpos-SCYpos)/(SA_zpos-SC_zpos)*SA_zpos;
     Xtar_BC = SBXpos - (SBXpos-SCXpos)/(SB_zpos-SC_zpos)*SB_zpos;
     Ytar_BC = SBYpos - (SBYpos-SCYpos)/(SB_zpos-SC_zpos)*SB_zpos;
     hXtar->Fill(xf1->GetParameter(0));
     hYtar->Fill(yf1->GetParameter(0));
     hXtar_AB->Fill(Xtar_AB);
     hYtar_AB->Fill(Ytar_AB);
     hXtar_AC->Fill(Xtar_AC);
     hYtar_AC->Fill(Ytar_AC);
     hXtar_BC->Fill(Xtar_BC);
     hYtar_BC->Fill(Ytar_BC);
   }
 }

 //TCanvas *c1 = new TCanvas("c1", "", 1000, 1000);
 //c1->cd();

 //gr_xbeam->Draw("ap");
 
 
 // plot
 outputpdf="plots/"+basename+"_beam.pdf";
 // plot
 outROOT->cd();
 outROOT->Write();

 //
}
