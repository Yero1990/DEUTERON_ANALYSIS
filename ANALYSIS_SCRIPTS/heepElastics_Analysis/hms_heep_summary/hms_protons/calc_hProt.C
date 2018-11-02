//Generic code to read and loop through N leafs from a given TTree
//The leafs names are read from a leaf_list.txt file.  For now, they can only be a Double_t (not int or array are yet done)
#include "TMath.h"
void calc_hProt()
{

  gROOT->SetBatch(kTRUE);
  gStyle->SetOptFit();


  //Define some constants
  Double_t Mp = 0.938272;  //proton mass
  Double_t Eb;

  //Define some variables to be determined inside the entry loop
  Double_t theta_p;     //proton arm angle (event by event)
  Double_t hmsP_calc;   //calculated proton momentum

  //-------Count the NUmber of Leafs in the list-------  
  ifstream myfile;
  myfile.open("leaf_list.txt");
  string line;

  Int_t cnts = -1;  //leaf counter
  //Get Number of leafs
  if(myfile.is_open()){
    while(!myfile.eof()){
      getline(myfile, line);
      if(line[0]=='#') continue;
	cnts++;
    } 
  }
  myfile.close();
  //--------------------------------------------------


  //---------------READ THE LEAFS into a string array----------------------------
  myfile.open("leaf_list.txt");
  //Create arrays
  TString leaf_name[cnts];
  //Make generic leaf variables (assuming it is a Double_t -- later, I should generalize)
  Double_t leaf_var[cnts];

  int index = 0;  //index array 
  //Read leaf list txt file
  while (getline(myfile, line))
    {
      if(line[0]=='#') continue;
      leaf_name[index] = line;
      index++;
    }
  //----------------------------------------------------------------------------


  //-------------CREATE EMPTY HISTOGRAMS---------------------------------------------
  
  //Create empty histogram arrays with the appropiate names based on the leaf you want to Fill
  TH1F *hist[8][cnts];
 
  Double_t xRes_arr[8];
  Double_t yRes_arr[8];
  Double_t yRes_arr_err[8];
  
  //--------------------------------------------------------

  TCanvas *c0 = new TCanvas("c0", "Missing Energy", 1500, 1000);   
  c0->Divide(4,2);
  TCanvas *c1 = new TCanvas("c1", "Calculated/Measured HMS Momentum", 1500, 1000);   
  c1->Divide(4,2);
  TCanvas *c2 = new TCanvas("c2", "HMS Momentum Fract. Dev. From Measured", 1500,1000);
  c2->Divide(4,2);
  TCanvas *c3 = new TCanvas("c3","Frac. Deviation from P_{meas} vs. Kin Group",200,10,500,300);

  //--------------OPEN ROOTfile and Get Tree------------------------

  //Read Run List
  ifstream ifs;
  ifs.open("../../runlists/hmsProt_list.dat");
  string rline;
  Int_t irun;
  index = 0;
  while(getline(ifs, rline))                                                                                                                                         
    {                                                                                     
      // irun = stoi(rline.c_str());                                                                       
      

      if(index==0) {

	Eb = 2.221;
	hist[index][0] = new TH1F(Form("calc_P: g%d", index+1), Form("Run g%d",index+1), 100, 0.5, 1.5); 
	hist[index][1] = new TH1F(Form("meas_P: g%d", index+1), Form("Run g%d", index+1), 100, 0.5, 1.5);  
      }

      else if(index>=1 && index<=2) {

	Eb = 6.430;
	hist[index][0] = new TH1F(Form("calc_P: g%d", index+1), Form("Run g%d",index+1), 100, 2, 4); 
	hist[index][1] = new TH1F(Form("meas_P: g%d", index+1), Form("Run g%d", index+1), 100, 2, 4);  
      }


      else if(index>2) {

	Eb = 10.58794;
	hist[index][0] = new TH1F(Form("calc_P: g%d", index+1), Form("Run g%d",index+1), 100, 1.5, 4); 
	hist[index][1] = new TH1F(Form("meas_P: g%d", index+1), Form("Run g%d", index+1), 100, 1.5, 4);  
      }
    
 
      hist[index][2] = new TH1F(Form("pDiff: g%d",index+1), Form("Run g%d: HMS Fractional. Dev. P_{meas}", index+1), 100, -0.05, 0.05);
      
      hist[index][3] = new TH1F(Form("Emiss: g%d",index+1), Form("Run g%d: E_{miss}", index+1), 100, -0.2, 0.3);


      //Open TFile
      string filename = "../../../../../ROOTfiles/good_Heep_hmsProt/"+rline;
      TFile *f1 = new TFile(filename.c_str());
      
      //Get TTree
      TTree *T = (TTree*)f1->Get("T");
      
      //-----------------------------------------------------------------
      
      
      //---------------Set Branch Address ------------------------------
      for (int i=0; i<cnts; i++)
	{
	  //cout << leaf_name[i] << endl;
	  T->SetBranchAddress(leaf_name[i], &leaf_var[i]);
	}
      
      //---------------------------------------------------------------
      
      
      //Define new variables to be calculated in the loop
      
      
      //-----------LOOP OVER ALL ENTRIES IN TREE-----------------------
      //Loop over all entries
      for(int i=0; i<T->GetEntries(); i++){

	T->GetEntry(i);

	//HMS Particle angles relative to central angle
	theta_p = leaf_var[0]*180./TMath::Pi() - leaf_var[1];

	//HMS Particle calculated momentum (Using only the particle angle and beam energy)
	hmsP_calc = 2.*Mp*Eb*(Eb + Mp)*TMath::Cos(theta_p*TMath::Pi()/180.) / (Mp*Mp + 2.*Mp*Eb + Eb*Eb*TMath::Power(TMath::Sin(theta_p*TMath::Pi()/180.),2)) ;


	
	if(TMath::Abs(theta_p)<100 && TMath::Abs(hmsP_calc)<100 && leaf_var[2]>-100 && leaf_var[2]<100. && leaf_var[3] > -0.08 && leaf_var[3] < 0.15 && abs(leaf_var[4]) < 8. )
	  {

	    
	    //DEGUB
	    // cout << "KG: " << index + 1 << endl;
	    //cout << "hmsP_calc - hmsP_meas = " <<  hmsP_calc << " - " << leaf_var[2] << " = " <<  hmsP_calc - leaf_var[2] << endl;

	    //Fill Histograms
	    hist[index][0]->Fill(hmsP_calc);  //calculated momentum from formula (function of theta_p and Ebeam)
	    hist[index][1]->Fill(leaf_var[2]);  //measured momentum H.gtr.p
	    hist[index][2]->Fill((hmsP_calc - leaf_var[2]) / leaf_var[2]);  //HMS (Calculated - Measured)/Measured Momentum (fractonal deviation from measured)
	  }
	hist[index][3]->Fill(leaf_var[3]);   //FIlling Missing Energy Histogram

      }
      
      //---------END ENTRY LOOP ---------------------------------------
      
         
      //DRaw HIstograms
      c0->cd(index+1);
      hist[index][3]->Draw();
      

      c1->cd(index+1);
      hist[index][0]->Draw();
      hist[index][0]->SetLineColor(kRed);
      hist[index][1]->Draw("sames");

      //Get max bin value/sigma from momentum difference histo to use as fit parameters
      int bin_max = hist[index][2]->GetMaximumBin();
      Double_t xmax_val = hist[index][2]->GetXaxis()->GetBinCenter(bin_max); 
      Double_t sig_Res = hist[index][2]->GetStdDev();
       
      c2->cd(index+1);
      hist[index][2]->Draw();


      TF1 *fit = new TF1("fit", "gaus", xmax_val - 0.8*sig_Res, xmax_val + 0.7*sig_Res);
      hist[index][2]->Fit("fit", "R");
  
      
      Double_t mu_Res_fit = fit->GetParameter(1);
      Double_t sig_Res_fit = fit->GetParameter(2);
      Double_t mu_Res_err_fit =  fit->GetParError(1);

      xRes_arr[index] = index + 1;          //kin group
      yRes_arr[index] = mu_Res_fit;          //mean fit fractional deviation from meas. momentum
      yRes_arr_err[index] =  mu_Res_err_fit;    //error from mean fit

     
      index++;

    } //end loop over runs 
  
  Double_t ex[8] = {0.};
  
  TGraphErrors* gr = new TGraphErrors(8,xRes_arr,yRes_arr, ex, yRes_arr_err);
  
  
  c3->cd();

  gr->SetTitle(" (P_{calc} - P_{meas}) / P_{meas.} vs. Kin. Group");

  gr->GetYaxis()->SetTitle("(P_{calc} - P_{meas}) / P_{measured} [fractional deviation]");
  gr->GetYaxis()->CenterTitle();
  
  gr->GetXaxis()->SetTitle("Kinematic Group");
  gr->GetXaxis()->CenterTitle();

  gr->SetMarkerStyle(21);
  gr->SetMarkerColor(kBlack);
  gr->SetMarkerSize(0.5);
  gr->Draw("AP");
  
  c0->SaveAs("testingMissing_Energy.pdf");
  c1->SaveAs("testingHMS_Calc_MeasP.pdf");
  c2->SaveAs("testingMomentum_Diff.pdf");
  c3->SaveAs("testingResidual_GRaph.pdf");
  
  

} //end function


