#include <iostream>
#include <fstream>
#include <string>

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"


using namespace std;

// istart: buffering level, f(mu, k) = e^{-R*tau},  tau-->BUSY dead time in seconds
//mu = R* tau,  par[1]=tau, par[0] (istart)= Buffer Level R = input rate in Hz 
// par[0] = 2 for buffer level =2
Double_t dt_extended(Double_t *x, Double_t *par){
  Double_t dtts = 0;
  Float_t xx=x[0];
  Double_t muts;
  Int_t istart=int(par[0]);
  muts=par[1]*xx;
  for (Int_t i = istart; i < 40; i++) {
    Double_t temp = ( TMath::Power(muts,i) * TMath::Exp(-1.0*muts) )/ TMath::Factorial(i);
    dtts = dtts + temp;
    cout <<  xx << " " << i << " " << temp << endl;
  }
  dtts=100*dtts;
  return dtts;
}
Double_t dt_nonextended(Double_t *y, Double_t *par2){
  Float_t xx=y[0]*1000.;
  Double_t dt; 
  Double_t lt;
  dt=100.*(xx*par2[0]/(1+xx*par2[0]));
  lt = (100. - dt);
  return lt;
}
							    
void deadtime_poiss() {
  TLegend* leg1 = new TLegend(0.11,0.7,0.25,0.89);
  TCanvas* T1 = new TCanvas ("T1","T1", 1000, 700);
  T1->Divide(1,1);
  
  TMultiGraph *mg1 = new TMultiGraph();

  //edtm = 100 Hz, rate shows only poisson rate in kHz, took 2 min. runs (no scaler reads)
  //Double_t rate[9]={1.1, 5.2, 10.1, 20.5, 30.7, 51.7, 101.0};
  //Double_t CLT[9]={80.18, 47.76, 32.28, 18.83, 13.16, 8.10, 4.26};  //computer live time
  //Double_t TLT[9]={82.05, 48.45, 32.70, 18.93, 12.67, 7.91, 3.63};

  //Prescale  HMS data December 2017
  //Double_t rate[6]={1.95, 3.8, 4.5, 5.5, 5.85, 6.5};// 1.0, 5.3, 10.9, 20.0, 30.6, 53.0, 101.0};
  //Double_t CLT[6]={99.13, 94.69, 92.29, 87.78, 87.64, 98.4};//, 81.07, 47.28, 30.73, 18.1, 13.2, 7.91, 4.25};  /

  //NOT Prescale HMS data December 2017
  //Double_t rate[8]={0.150, 0.160, 0.420, 0.900, 3.0, 128.5, 156.0, 167.0};// 1.0, 5.3, 10.9, 20.0, 30.6, 53.0, 101.0};
  //Double_t CLT[8]={96.73, 96.82, 90.7, 83.11, 60.26, 2.89, 2.36, 2.31};//, 81.07, 47.28, 30.73, 18.1, 13.2, 7.91, 4.25};  /

  //NOT Prescale SHMS data December 2017
  //Double_t rate[6]={2.1, 3.1, 4.0, 9.1, 12.3, 15.9};
  //Double_t CLT[6]={66.47, 57.22, 58.33, 30.72, 25.03, 19.48};

  //---------------Jan 19, 2018, log entry edtm with beama data---------------------
  //EDTM = 100 Hz: NOT PreScaled HMS data January 2018
  //Double_t rate[9]={0.215, 0.671, 1.143, 1.473, 2.786, 3.491, 4.042, 4.462, 5.585};
  //Double_t CLT[9]={96.4, 87.25, 78.86, 67.22, 57.05, 51.134, 50.0787, 45.33, 41.02};
  //Double_t TLT[9]={97.52, 88.66, 81.195, 79.49, 64.85, 60.75, 55.015, 55.104, 49.108};
  
  //EDTM = 100 Hz: NOT PreScaled SHMS data January 2018
  //Double_t rate[8]={0.128, 0.234, 0.351, 0.439, 0.799, 1.025, 1.346, 1.739};
  //Double_t CLT[8]={98.715, 95.42, 92.39, 87.81, 81.75, 76.93, 71.74, 67.13};
  //Double_t TLT[8]{99.30, 96.81, 94.409, 92.785, 86.186, 82.808, 78.149, 72.957};



  
  //---------------Jan 19, 2018, log entry  ADDED A SCALE FACTOR ON DENOMINATOR, (scale LT = total LT * 0.83534759)---------------------
  //EDTM = 100 Hz: NOT PreScaled HMS data January 2018
  //Double_t rate[9]={0.215, 0.671, 1.143, 1.473, 2.786, 3.491, 4.042, 4.462, 5.585};
  //Double_t CLT[9]={96.4, 87.25, 78.86, 67.22, 57.05, 51.134, 50.0787, 45.33, 41.02};
  //Double_t TLT[9]={81.467, 74.06, 67.82, 66.40, 54.17, 50.74, 45.95, 46.03, 41.022};
  
  //EDTM = 100 Hz: NOT PreScaled SHMS data January 2018 ADDED A SCALE FACTOR ON DENOMINATOR, (scale LT = total LT * 0.92019600)---------------------
  // Double_t rate[8]={0.128, 0.234, 0.351, 0.439, 0.799, 1.025, 1.346, 1.739};
  // Double_t CLT[8]={98.7115, 95.427, 92.393, 87.813, 81.756, 76.937, 71.747, 67.135};
  // Double_t TLT[8]{91.380, 89.084, 86.875, 85.381, 79.308, 76.199, 71.913, 67.135};

  //January 26, 2018 Runs, edtm = 3 Hz
  Double_t rate[8]={0.128, 0.234, 0.351, 0.439, 0.799, 1.025, 1.346, 1.739};
  Double_t CLT[8]={98.7115, 95.427, 92.393, 87.813, 81.756, 76.937, 71.747, 67.135};
  Double_t TLT[8]{91.380, 89.084, 86.875, 85.381, 79.308, 76.199, 71.913, 67.135};



  
  /*
  //EDTM + Poisson studies, January 23, 2018
  Double_t rate[5]={0.174, 0.298, 1.5, 2.4, 4.1};
  Double_t CLT[5]={97.6079, 94.9164, 75.5929, 66.5208, 54.3514};
  Double_t err_CLT[5]={0.553, 0.426, 0.220, 0.125, 0.0862};
  Double_t TLT[5] = {98.6676, 96.3091, 77.2091, 67.4792, 54.9466};
  Double_t err_TLT[5]={0.724, 0.589, 0.867, 0.618, 0.549};
  Double_t err_x[5]={0,0,0,0,0};
    
  
  TGraphErrors *gr1 = new TGraphErrors(5, rate, CLT, err_x, err_CLT);
  TGraphErrors *gr2 = new TGraphErrors(5, rate, TLT, err_x, err_TLT);
  */
  TGraph *gr1 = new TGraph(8, rate, CLT);
  TGraph *gr2 = new TGraph(8, rate, TLT);
  
  mg1->Add(gr1);
  mg1->Add(gr2);
  mg1->Draw("AP");
  
  gr1->SetMarkerColor(1);
  gr1->SetMarkerStyle(21);
  //gr1->SetMarkerSize(1.5);

  gr2->SetMarkerColor(2);
  gr2->SetMarkerStyle(22);
  //gr2->SetMarkerSize(1.5);

  
  mg1->GetXaxis()->SetLimits(0,100.);
  mg1->GetYaxis()->SetLimits(0, 100.);
  //mg1->SetMinimum(0);
  //mg1->SetMaximum(7.0);

  mg1->SetTitle("");
  mg1->GetXaxis()->SetTitle("Rate (kHz)");
  mg1->GetYaxis()->SetTitle("Live Time (%)");
  leg1->AddEntry(gr1,"SHMS Computer Live Time (NOT Pre-Scaled)","p");
  leg1->AddEntry(gr2,"SHMS Total Live Time (NOT Pre-Scaled)","p");

  
  
 //leg1->AddEntry(gr2,"SHMS EDTM","p");
  /*  
  TF1 *deadt1= new TF1("deadt1",dt_nonextended,0.,55000.,2);
  deadt1->SetParameters(.0001,1);
  deadt1->Draw("same");
  deadt1->SetLineColor(2);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->AddEntry(deadt1,"deadtime = 100 usec","l");
  TF1 *deadt2 = new TF1("deadt2",dt_nonextended,0,55000.,2);
  deadt2->SetParameters(220.e-6,1);
  deadt2->Draw("same");
  deadt2->SetLineColor(3);
  leg1->AddEntry(deadt2,"deadtime = 220 usec","l");
  */

  //==========================
  
  TF1 *deadt3 = new TF1("deadt3",dt_nonextended,0,200.,2);
  deadt3->SetParameters(220.e-6,1);
  deadt3->Draw("same");
  deadt3->SetLineColor(4);
  leg1->AddEntry(deadt3,"BUSY MIN = 220 #mus","l");
  
  TF1 *deadt4 = new TF1("EDTM + Poisson Live Time Measurements",dt_nonextended,0,200.,2);
  deadt4->SetParameters(316.e-6,1);
  deadt4->Draw("same");
  deadt4->SetLineColor(1);
  leg1->AddEntry(deadt4,"BUSY MAX = 316 #mus","l");
  leg1->Draw();
  
  //===========================

  
  TF1 *deadt5 = new TF1("deadt5",dt_extended,0.,5000.,2);
  deadt5->SetParameters(0,280.e-6);
  deadt5->Draw("same");
  deadt5->SetLineColor(1);
  leg1->AddEntry(deadt5,"deadtime = 280 usec buf=2","l");
  leg1->Draw();
  
}
