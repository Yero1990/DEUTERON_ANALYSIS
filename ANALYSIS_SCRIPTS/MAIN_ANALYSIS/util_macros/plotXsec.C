/*Macro to plot DATA, SIMC Cross sections for the D(e,e'p)
The Cross sections are in Pmiss/PhaseSpace vs. theta_nq bins, so
one would need to get the projectionsY from the 2D Histos, to get
the cross section in theta_nw bins. 

TH1 *hbins[100] ;//or whatever you need, ie nbins for (int i=0;i<nbins;i++) { hbins[i] = h2->ProjectionY(Form("bin%d",i+1),i+1,i+2); } 

 */


//Read ROOTfiles
pm80_pwia_fname = "Xsec_pm80_lagetpwia_dataset1.root";
TFile *file_pm80_pwia = new TFile(pm80_pwia_fname, "READ");


//Get 2D Histogram Objects
TH2F *data_Pm_vs_thnq = 0;
TH2F *simc_Pm_vs_thnq = 0;

file_pm80_pwia->cd();
file_pm80_pwia->GetObject("", data_Pm_vs_thnq;);
file_pm80_pwia->GetObject("", simc_Pm_vs_thnq;); 

//Create 1D Histograms to store projections (in thnq bins)


//Loop over th_nq bins and get projections



//plot DATA/SIMC superimposed






