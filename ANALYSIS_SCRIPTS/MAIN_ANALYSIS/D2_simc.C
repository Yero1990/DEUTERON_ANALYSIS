//Code to check Deuteron Electro-Disintegration D(e,e'p)n Simulation, E12-10-003 

#include "set_deep_histos.h"

//Define Prototypes for Auxiliary Functions
void GeoToSph( Double_t  th_geo, Double_t  ph_geo,
	       Double_t& th_sph, Double_t& ph_sph);

void SetCentralAngles(Double_t th_cent, Double_t ph_cent);

void TransportToLab( Double_t p, Double_t xptar, Double_t yptar,
		     TVector3& pvect );  

void D2_simc(int set, int Pmiss, string model, string rad, bool Qnorm=false)
{

  /*Code Usage Example:
    >> root -l
    >> .L D2_simc.C
    >> D2_simc(1, 80, "pwia", "rad", false)     // set = 0, 1 ,2, 3, :: Missing Momentum Pmiss = 80, 580 or 750,  model = "pwia" or "fsi", rad = "rad" or "norad"
    where "rad" ---> simulate radiative tail and Eloss,   "norad"---> Does NOT simulate radiative tail or Eloss
    Qnorm ---> weight simc by charge/efficiencies/live time ?
  */
  
  //PREVENT DISPLAY 
  //gROOT->SetBatch(kTRUE);

  Double_t charge_factor = 1.;       //Units: mC   :: beam_current(uA) * time (hrs) * 3600. / 1000.  3600--> hrs to sec,  1000--> uC to mC
  Double_t e_trkEff = 1.;
  Double_t h_trkEff = 1.;           
  Double_t c_LT = 1.;
  Double_t t_LT = 1.;

  if (Qnorm){
  if(set==1&&Pmiss==80){
    
    charge_factor = 142.553;   //BCM4A
    
    c_LT = 0.97881;          //computer live time
    t_LT = 0.909529;          //total live time
    
    e_trkEff = 0.966524;       //shms e- trk eff
    h_trkEff = 0.989003;        //hms had trk eff

  }


    //Combined 580 data sets 
    if(set==-1&&Pmiss==580){                                                                                                                                                                                                                                       
      charge_factor = 3759.779;   //BCM4A (mC)                                                                                                   
      c_LT = 0.998465;          //computer live time                                                                  
      t_LT = 0.930204;          //total live time                                                                                 
      
      e_trkEff = 0.96600;       //shms e- trk eff                                                                       
      h_trkEff = 0.974655;        //hms had trk eff                                                         
      
    } 

 if(set==1&&Pmiss==580){
    
    charge_factor =1827.029;   //BCM4A (mC)
    
    c_LT = 0.998534;          //computer live time
    t_LT = 0.930728;          //total live time
    
    e_trkEff = 0.966850;       //shms e- trk eff
    h_trkEff = 0.962029;        //hms had trk eff

  }

 if(set==2&&Pmiss==580){
    
    charge_factor = 1932.75;   //BCM4A (mC)
    
    c_LT = 0.998398;          //computer live time
    t_LT = 0.929696;          //total live time
    
    e_trkEff = 0.965208;       //shms e- trk eff
    h_trkEff = 0.987885;        //hms had trk eff

  }

     //Combined 750 MeV sets
    if(set==-1&&Pmiss==750){                                                                                                          
                                                                                                                                    
      charge_factor = 8315.383;   //BCM4A (mC)                                                                               
                                                                                                                                        
      c_LT = 0.998544;          //computer live time                                                                              
      t_LT = 0.925702;          //total live time                                                                                    
                                                                                                                                          
      e_trkEff = 0.962190;       //shms e- trk eff                                                                                            
      h_trkEff = 0.989080;        //hms had trk eff                                                
                                                                                                       
    } 

 if(set==1&&Pmiss==750){
    
    charge_factor = 5335.617;   //BCM4A (mC)
    
    c_LT = 0.998538;          //computer live time
    t_LT = 0.926217;          //total live time
    
    e_trkEff = 0.962456;       //shms e- trk eff
    h_trkEff = 0.988749;        //hms had trk eff

  }
 if(set==2&&Pmiss==750){
    
    charge_factor = 1894.894;   //BCM4A (mC)
    
    c_LT = 0.998538;          //computer live time
    t_LT = 0.924257;          //total live time
    
    e_trkEff = 0.960770;       //shms e- trk eff
    h_trkEff = 0.989432;        //hms had trk eff

  }

 if(set==3&&Pmiss==750){
    
    charge_factor = 1084.872;   //BCM4A (mC)
    
    c_LT = 0.998583;          //computer live time
    t_LT = 0.925570;          //total live time
    
    e_trkEff = 0.963303;       //shms e- trk eff
    h_trkEff = 0.990051;        //hms had trk eff

  }
                                
  }

  TString filename; 

  filename = Form("../worksim_voli/d2_pm%d_laget%s_%s_set%d.root", Pmiss, model.c_str(), rad.c_str(), set);
  
  if(set==-1){ filename = Form("../worksim_voli/d2_pm%d_laget%s_%s_total.root", Pmiss, model.c_str(), rad.c_str());}

 
 TFile *data_file = new TFile(filename, "READ"); 
 TTree *SNT = (TTree*)data_file->Get("SNT");
 
 //Create output root file where histograms will be stored
 TFile *outROOT;
 if(set==-1){
   outROOT = new TFile(Form("D2simc_pm%d_laget%s_%s_total.root", Pmiss, model.c_str(), rad.c_str()), "recreate");
 }
 else{
   outROOT = new TFile(Form("D2simc_pm%d_laget%s_%s_set%d.root", Pmiss, model.c_str(), rad.c_str(), set), "recreate");
 }

  //*****************************************
  // Phase Spase Histograms: 
  // Only fill with variable (Un-weighted)
  //*****************************************
  TH1F *pm_ps = new TH1F("pm_ps","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);
  TH1F *cut_pm_ps = new TH1F("cut_pm_ps","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax); 
  TH1F *cut_pm_ps_red = new TH1F("cut_pm_ps_red","Phase Space (Used in red. Xsec)", Pm_nbins, Pm_xmin, Pm_xmax); 

  pm_ps->Sumw2();
  cut_pm_ps->Sumw2();
  cut_pm_ps_red->Sumw2();

  //********* Create 1D Histograms **************
  
  //Kinematics Quantities
  TH1F *MM2 = new TH1F("MM2", "Missing Mass Squared, MM2", MM2_nbins, MM2_xmin, MM2_xmax );
  TH1F *Emiss = new TH1F("Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);       //min width = 21.6 (0.0216)MeV,  COUNTS/25 MeV
  TH1F *pm = new TH1F("pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);  
  TH1F *Kred = new TH1F("Kred","K =[ E_{p}P_{p}/(2#pi)^{3}] #sigma_{cc}", Pm_nbins, Pm_xmin, Pm_xmax); 
     
  TH1F *pmX_lab = new TH1F("pmX_Lab","Pmiss X (Lab) ", Pmx_nbins, Pmx_xmin, Pmx_xmax); 
  TH1F *pmY_lab = new TH1F("pmY_Lab","Pmiss Y (Lab) ", Pmy_nbins, Pmy_xmin, Pmy_xmax);  
  TH1F *pmZ_lab = new TH1F("pmZ_Lab","Pmiss Z (Lab) ", Pmz_nbins, Pmz_xmin, Pmz_xmax);  
  TH1F *pmX_q = new TH1F("pmX_q","Pmiss X (w.r.t q-vec) ", Pmx_nbins, Pmx_xmin, Pmx_xmax); 
  TH1F *pmY_q = new TH1F("pmY_q","Pmiss Y (w.r.t q-vec) ", Pmy_nbins, Pmy_xmin, Pmy_xmax);  
  TH1F *pmZ_q = new TH1F("pmZ_q","Pmiss Z (w.r.t. q-vec) ", Pmz_nbins, Pmz_xmin, Pmz_xmax);  


  TH1F *Q_2 = new TH1F("Q_2","Q2", Q2_nbins, Q2_xmin, Q2_xmax);
  TH1F *omega = new TH1F("omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax);
  TH1F *W_inv = new TH1F("W_inv", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);     //min width = 19.9 MeV (0.0199) (bin width = 25 MeV)
  TH1F *theta_elec = new TH1F("theta_elec", "Electron Scatt. Angle", the_nbins, the_xmin, the_xmax);
  TH1F *theta_prot = new TH1F("theta_prot", "Proton Scatt. Angle", thp_nbins, thp_xmin, thp_xmax);
  
  //Additional Kinematics Variables
  TH1F *W_2 = new TH1F("W2", "Invariant Mass W2", W2_nbins, W2_xmin, W2_xmax);
  TH1F *xbj = new TH1F("xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);
  TH1F *P_f = new TH1F("P_f", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
  TH1F *k_f = new TH1F("kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);
  TH1F *theta_q = new TH1F("theta_q", "q-vector Angle, #theta_{q}", thq_nbins, thq_xmin, thq_xmax);
  TH1F *q_vec = new TH1F("q", "q-vector, |q|", q_nbins, q_xmin, q_xmax);
  TH1F *thet_pq = new TH1F("theta_pq", "(Proton, q-vector) Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
  TH1F *thet_pq_v2 = new TH1F("theta_pq_v2", "(Proton, q-vector) Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
  TH1F *E_n = new TH1F("En", "Neutron Final Energy", En_nbins, En_xmin, En_xmax);
  TH1F *theta_nq = new TH1F("theta_nq", "(q-vector,Neutron) Angle, #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax);
  TH1F *Mmiss = new TH1F("Mmiss","Missing Mass", Mm_nbins, Mm_xmin, Mm_xmax);                                                                           
  TH1F *pmx = new TH1F("pmx","Pmx missing momentum", Pmx_nbins, Pmx_xmin, Pmx_xmax);                                                                                                
  TH1F *pmy = new TH1F("pmy","Pmy missing momentum", Pmy_nbins, Pmy_xmin, Pmy_xmax);                                                                                                       
  TH1F *pmz = new TH1F("pmz","Pmz missing momentum", Pmz_nbins, Pmz_xmin, Pmz_xmax);                                                         
  TH1F *KinN = new TH1F("Kn","Neutron Kin. Energy", Kn_nbins, Kn_xmin, Kn_xmax);                                                                       
  TH1F *KinP = new TH1F("Kp","Proton Kin. Energy", Kp_nbins, Kp_xmin, Kp_xmax);  
  TH1F *E_p = new TH1F("Ep","Proton Final Energy", Ep_nbins, Ep_xmin, Ep_xmax);  

  
  //Target Reconstruction Variables
  TH1F *x_tar = new TH1F("x_tar", "x_Target (Lab)", xtar_nbins, xtar_xmin, xtar_xmax);
  TH1F *y_tarH = new TH1F("y_tarH", hadron_arm + " y_Target (Lab)", ytar_nbins, ytar_xmin, ytar_xmax);
  TH1F *z_tarH = new TH1F("z_tarH", hadron_arm + " z_Target (Lab)", ztar_nbins, ztar_xmin, ztar_xmax);
  
  TH1F *y_tarP = new TH1F("y_tarP", electron_arm + " y_Target (Lab)", ytar_nbins, ytar_xmin, ytar_xmax);                                     
  TH1F *z_tarP = new TH1F("z_tarP", electron_arm + " z_Target (Lab)", ztar_nbins, ztar_xmin, ztar_xmax);  

  //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  TH1F *hytar = new TH1F("hytar", hadron_arm + " Y_{tar}", hytar_nbins, hytar_xmin, hytar_xmax);
  TH1F *hxptar = new TH1F("hxptar", hadron_arm + " X'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH1F *hyptar = new TH1F("hyptar", hadron_arm + " Y'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax );
  TH1F *hdelta = new TH1F("hdelta", hadron_arm + " Momentum Acceptance, #delta", hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
  //Hadron arm Focal Plane Quantities
  TH1F *hxfp = new TH1F("hxfp", hadron_arm + " X_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax);
  TH1F *hyfp = new TH1F("hyfp", hadron_arm + " Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax);
  TH1F *hxpfp = new TH1F("hxpfp", hadron_arm + " X'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax );
  TH1F *hypfp = new TH1F("hypfp", hadron_arm + " Y'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax);
 
  
  //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  TH1F *eytar = new TH1F("eytar", electron_arm + " Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax);
  TH1F *exptar = new TH1F("exptar", electron_arm + " X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax);
  TH1F *eyptar = new TH1F("eyptar", electron_arm + " Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH1F *edelta = new TH1F("edelta", electron_arm + " Momentum Acceptance, #delta", edelta_nbins, edelta_xmin, edelta_xmax);
  
  //Electron Arm Focal Plane Quantities
  TH1F *exfp = new TH1F("exfp", electron_arm + " X_{fp}", exfp_nbins, exfp_xmin, exfp_xmax);
  TH1F *eyfp = new TH1F("eyfp", electron_arm + " Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax);
  TH1F *expfp = new TH1F("expfp", electron_arm + " X'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax);
  TH1F *eypfp = new TH1F("eypfp", electron_arm + " Y'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax);
  
  //Cross-Check correlations
  TH2F *emiss_vs_pmiss = new TH2F("emiss_vs_pmiss", " E_{miss} vs. P_{miss}", Pm_nbins, Pm_xmin, Pm_xmax, Em_nbins, Em_xmin, Em_xmax);
  TH2F *edelta_vs_eyptar = new TH2F("edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  
  
  //Create 2D Histograms at the Focal Plane Quantities
  TH2F *h_xfp_vs_yfp = new TH2F("h_xfp_vs_yfp", "X_{fp} vs Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxfp_nbins, hxfp_xmin, hxfp_xmax);
  TH2F *e_xfp_vs_yfp = new TH2F("e_xfp_vs_yfp", "X_{fp} vs Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exfp_nbins, exfp_xmin, exfp_xmax);
  
  //2D HMS v. SHMS Acceptance Correlations
  TH2F *hytar_vs_eytar = new TH2F("hytar_vs_eytar", "HMS vs. SHMS, Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *hxptar_vs_exptar = new TH2F("hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *hyptar_vs_eyptar = new TH2F("hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *hdelta_vs_edelta = new TH2F("hdelta_vs_edelta", "HMS vs. SHMS, #delta", edelta_nbins, edelta_xmin, edelta_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
  //OPTICS CHECK (W correlations with electron arm Focal Plane / Target Quantities)
  TH2F *W_vs_exfp = new TH2F("W_vs_exfp", "W vs eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_expfp = new TH2F("W_vs_expfp", "W vs eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_eyfp = new TH2F("W_vs_eyfp", "W vs eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_eypfp = new TH2F("W_vs_eypfp", "W vs eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, W_nbins, W_xmin, W_xmax);
  
  TH2F *W_vs_eytar = new TH2F("W_vs_eytar", "W vs eY_{tar}", eytar_nbins, eytar_xmin, eytar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_exptar = new TH2F("W_vs_exptar", "W vs eX'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_eyptar = new TH2F("W_vs_eyptar", "W vs eY'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_edelta = new TH2F("W_vs_edelta", "W vs edelta", edelta_nbins, edelta_xmin, edelta_xmax, W_nbins, W_xmin, W_xmax);
  
  //OPTICS CHECK (Emiss correlations with electron arm Focal Plane / Target Quantities)                                                                                                             
  TH2F *Em_vs_exfp = new TH2F("Em_vs_exfp", "Em vs eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                            
  TH2F *Em_vs_expfp = new TH2F("Em_vs_expfp", "Em vs eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  TH2F *Em_vs_eyfp = new TH2F("Em_vs_eyfp", "Em vs eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  TH2F *Em_vs_eypfp = new TH2F("Em_vs_eypfp", "Em vs eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  
  TH2F *Em_vs_eytar = new TH2F("Em_vs_eytar", "Em vs eY_{tar}", eytar_nbins, eytar_xmin, eytar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                            
  TH2F *Em_vs_exptar = new TH2F("Em_vs_exptar", "Em vs eX'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                            
  TH2F *Em_vs_eyptar = new TH2F("Em_vs_eyptar", "Em vs eY'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                  
  TH2F *Em_vs_edelta = new TH2F("Em_vs_edelta", "Em vs edelta", edelta_nbins, edelta_xmin, edelta_xmax, Em_nbins, Em_xmin, Em_xmax); 
  
  //OPTICS CHECK (W correlations with hadron arm Focal Plane / Target Quantities)
  TH2F *W_vs_hxfp = new TH2F("W_vs_hxfp", "W vs hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hxpfp = new TH2F("W_vs_hxpfp", "W vs hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hyfp = new TH2F("W_vs_hyfp", "W vs hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hypfp = new TH2F("W_vs_hypfp", "W vs hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, W_nbins, W_xmin, W_xmax);
  
  TH2F *W_vs_hytar = new TH2F("W_vs_hytar", "W vs hY_{tar}", hytar_nbins, hytar_xmin, hytar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hxptar = new TH2F("W_vs_hxptar", "W vs hX'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hyptar = new TH2F("W_vs_hyptar", "W vs hY'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *W_vs_hdelta = new TH2F("W_vs_hdelta", "W vs hdelta", hdelta_nbins, hdelta_xmin, hdelta_xmax, W_nbins, W_xmin, W_xmax);
  
  //OPTICS CHECK (Emiss correlations with hadron arm Focal Plane / Target Quantities)                                                                                                             
  TH2F *Em_vs_hxfp = new TH2F("Em_vs_hxfp", "Em vs hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                            
  TH2F *Em_vs_hxpfp = new TH2F("Em_vs_hxpfp", "Em vs hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  TH2F *Em_vs_hyfp = new TH2F("Em_vs_hyfp", "Em vs hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  TH2F *Em_vs_hypfp = new TH2F("Em_vs_hypfp", "Em vs hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                               
  
  TH2F *Em_vs_hytar = new TH2F("Em_vs_hytar", "Em vs hY_{tar}", hytar_nbins, hytar_xmin, hytar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                            
  TH2F *Em_vs_hxptar = new TH2F("Em_vs_hxptar", "Em vs hX'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                            
  TH2F *Em_vs_hyptar = new TH2F("Em_vs_hyptar", "Em vs hY'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax, Em_nbins, Em_xmin, Em_xmax);                                                                  
  TH2F *Em_vs_hdelta = new TH2F("Em_vs_hdelta", "Em vs hdelta", hdelta_nbins, hdelta_xmin, hdelta_xmax, Em_nbins, Em_xmin, Em_xmax); 
  
  //OPTICS CHECK (Electron Arm Reconstructed Quantities vs. Focal Plane Quantities) --Each of the reconstructed quantities is a polynomial expansion of focal plane quantities
  TH2F *eytar_vs_exfp = new TH2F("eytar_vs_exfp", "SHMS eY_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *eytar_vs_expfp = new TH2F("eytar_vs_expfp", "SHMS eY_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *eytar_vs_eyfp = new TH2F("eytar_vs_eyfp", "SHMS eY_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *eytar_vs_eypfp = new TH2F("eytar_vs_eypfp", "SHMS eY_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);

  TH2F *eyptar_vs_exfp = new TH2F("eyptar_vs_exfp", "SHMS eY'_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *eyptar_vs_expfp = new TH2F("eyptar_vs_expfp", "SHMS eY'_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *eyptar_vs_eyfp = new TH2F("eyptar_vs_eyfp", "SHMS eY'_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *eyptar_vs_eypfp = new TH2F("eyptar_vs_eypfp", "SHMS eY'_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);

  TH2F *exptar_vs_exfp = new TH2F("exptar_vs_exfp", "SHMS eX'_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *exptar_vs_expfp = new TH2F("exptar_vs_expfp", "SHMS eX'_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *exptar_vs_eyfp = new TH2F("exptar_vs_eyfp", "SHMS eX'_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *exptar_vs_eypfp = new TH2F("exptar_vs_eypfp", "SHMS eX'_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);

  TH2F *edelta_vs_exfp = new TH2F("edelta_vs_exfp", "SHMS Delta e#delta vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *edelta_vs_expfp = new TH2F("edelta_vs_expfp", "SHMS Delta e#delta vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *edelta_vs_eyfp = new TH2F("edelta_vs_eyfp", "SHMS Delta e#delta vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *edelta_vs_eypfp = new TH2F("edelta_vs_eypfp", "SHMS Delta e#delta vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);

  //OPTICS CHECK (Hadron  Arm Reconstructed Quantities vs. Focal Plane Quantities) --Each of the reconstructed quantities is a polynomial expansion of focal plane quantities
  TH2F *hytar_vs_hxfp = new TH2F("hytar_vs_hxfp", "HMS hY_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *hytar_vs_hxpfp = new TH2F("hytar_vs_hxpfp", "HMS hY_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *hytar_vs_hyfp = new TH2F("hytar_vs_hyfp", "HMS hY_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *hytar_vs_hypfp = new TH2F("hytar_vs_hypfp", "HMS hY_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);

  TH2F *hyptar_vs_hxfp = new TH2F("hyptar_vs_hxfp", "HMS hY'_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *hyptar_vs_hxpfp = new TH2F("hyptar_vs_hxpfp", "HMS hY'_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *hyptar_vs_hyfp = new TH2F("hyptar_vs_hyfp", "HMS hY'_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *hyptar_vs_hypfp = new TH2F("hyptar_vs_hypfp", "HMS hY'_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);

  TH2F *hxptar_vs_hxfp = new TH2F("hxptar_vs_hxfp", "HMS hX'_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *hxptar_vs_hxpfp = new TH2F("hxptar_vs_hxpfp", "HMS hX'_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *hxptar_vs_hyfp = new TH2F("hxptar_vs_hyfp", "HMS hX'_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *hxptar_vs_hypfp = new TH2F("hxptar_vs_hypfp", "HMS hX'_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);

  TH2F *hdelta_vs_hxfp = new TH2F("hdelta_vs_hxfp", "HMS Delta h#delta vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *hdelta_vs_hxpfp = new TH2F("hdelta_vs_hxpfp", "HMS Delta h#delta vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *hdelta_vs_hyfp = new TH2F("hdelta_vs_hyfp", "HMS Delta h#delta vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *hdelta_vs_hypfp = new TH2F("hdelta_vs_hypfp", "HMS Delta h#delta vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);

  TH2F *Q2_vs_thnq = new TH2F("Q2_vs_thnq", "Q2 vs. #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax, Q2_nbins, Q2_xmin, Q2_xmax);
  TH2F *Q2_vs_Pm = new TH2F("Q2_vs_Pm", "Q2 vs. Pm", Pm_nbins, Pm_xmin, Pm_xmax, Q2_nbins, Q2_xmin, Q2_xmax); 

  /************Define Histos to APPLY CUTS*********************************/
  
  //Kinematics Quantities
  TH1F *cut_MM2 = new TH1F("cut_MM2", "Missing Mass Squared, MM2", MM2_nbins, MM2_xmin, MM2_xmax );
  TH1F *cut_Emiss = new TH1F("cut_Emiss","missing energy", Em_nbins, Em_xmin, Em_xmax);       //min width = 21.6 (0.0216)MeV,  CUT_OUNTS/25 MeV
  TH1F *cut_pm = new TH1F("cut_pm","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);  //min width = 32 MeV (0.032)
  TH1F *cut_pm_v2 = new TH1F("cut_pm_v2","missing momentum", Pm_nbins, Pm_xmin, Pm_xmax);  //min width = 32 MeV (0.032)
  TH1F *cut_Kred = new TH1F("cut_Kred","Pmiss*K_{red} =[ E_{p}P_{p}/(2#pi)^{3}] #sigma_{cc}", Pm_nbins, Pm_xmin, Pm_xmax); 
  TH1F *cut_pm_red = new TH1F("cut_pm_red","Reduced Cross Section, #sigma_{cc}", Pm_nbins, Pm_xmin, Pm_xmax); 
  TH1F *cut_pm_red2 = new TH1F("cut_pm_red2","Reduced Cross Section, #sigma_{cc}", Pm_nbins, Pm_xmin, Pm_xmax); 


  cut_Emiss->Sumw2();
  cut_pm->Sumw2();
  cut_Kred->Sumw2();
  cut_pm_red->Sumw2();
  cut_pm_red2->Sumw2();
  cut_pm_v2->Sumw2();

  TH1F *cut_pmX_lab = new TH1F("cut_pmX_Lab","Pmiss X (Lab) ", Pmx_nbins, Pmx_xmin, Pmx_xmax); 
  TH1F *cut_pmY_lab = new TH1F("cut_pmY_Lab","Pmiss Y (Lab) ", Pmy_nbins, Pmy_xmin, Pmy_xmax);  
  TH1F *cut_pmZ_lab = new TH1F("cut_pmZ_Lab","Pmiss Z (Lab) ", Pmz_nbins, Pmz_xmin, Pmz_xmax);  
  TH1F *cut_pmX_q = new TH1F("cut_pmX_q","Pmiss X (w.r.t q-vec) ", Pmx_nbins, Pmx_xmin, Pmx_xmax); 
  TH1F *cut_pmY_q = new TH1F("cut_pmY_q","Pmiss Y (w.r.t q-vec) ", Pmy_nbins, Pmy_xmin, Pmy_xmax);  
  TH1F *cut_pmZ_q = new TH1F("cut_pmZ_q","Pmiss Z (w.r.t. q-vec) ", Pmz_nbins, Pmz_xmin, Pmz_xmax);  
  

  TH1F *cut_Q_2 = new TH1F("cut_Q_2","Q2", Q2_nbins, Q2_xmin, Q2_xmax);
  TH1F *cut_omega = new TH1F("cut_omega","Energy Transfer, #omega", om_nbins, om_xmin, om_xmax);
  TH1F *cut_W_inv = new TH1F("cut_W_inv", "Invariant Mass, W", W_nbins, W_xmin, W_xmax);     //min width = 19.9 MeV (0.0199) (bin width = 25 MeV)
  TH1F *cut_theta_elec = new TH1F("cut_theta_elec", "Electron Scatt. Angle", the_nbins, the_xmin, the_xmax);
  TH1F *cut_theta_prot = new TH1F("cut_theta_prot", "Proton Scatt. Angle", thp_nbins, thp_xmin, thp_xmax);

  cut_Q_2->Sumw2();
  cut_omega->Sumw2();
  
  
  //Additional Kinematics Variables
  TH1F *cut_W_2 = new TH1F("cut_W2", "Invariant Mass W2", W2_nbins, W2_xmin, W2_xmax);
  TH1F *cut_xbj = new TH1F("cut_xbj", "x-Bjorken", xbj_nbins, xbj_xmin, xbj_xmax);
  TH1F *cut_P_f = new TH1F("cut_P_f", "Final Proton Momentum", Pf_nbins, Pf_xmin, Pf_xmax);
  TH1F *cut_k_f = new TH1F("cut_kf", "Final e^{-} Momentum", kf_nbins, kf_xmin, kf_xmax);
  TH1F *cut_q_vec = new TH1F("cut_q", "q-vector, |q|", q_nbins, q_xmin, q_xmax);
  TH1F *cut_theta_q = new TH1F("cut_theta_q", "q-vector Angle, #theta_{q}", thq_nbins, thq_xmin, thq_xmax);
  TH1F *cut_thet_pq = new TH1F("cut_theta_pq", "(Proton, q-vector) Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
  TH1F *cut_thet_pq_v2 = new TH1F("cut_theta_pq_v2", "(Proton, q-vector) Angle, #theta_{pq}", thpq_nbins, thpq_xmin, thpq_xmax);
  TH1F *cut_E_n = new TH1F("cut_En", "Neutron Final Energy", En_nbins, En_xmin, En_xmax);
  TH1F *cut_theta_nq = new TH1F("cut_theta_nq", "(q-vector, Neutron) Angle, #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax);

  TH1F *cut_Mmiss = new TH1F("cut_Mmiss","Missing Mass", Mm_nbins, Mm_xmin, Mm_xmax);         
  TH1F *cut_Erecoil = new TH1F("cut_Erecoil","Recoil Neutron Energy", En_nbins, En_xmin, En_xmax);   
  
  TH1F *cut_pmxL_v2 = new TH1F("cut_pmxL_v2","Pmx missing momentum", Pmx_nbins, Pmx_xmin, Pmx_xmax);            
  TH1F *cut_pmyL_v2 = new TH1F("cut_pmyL_v2","Pmy missing momentum", Pmy_nbins, Pmy_xmin, Pmy_xmax);                                                                             
  TH1F *cut_pmzL_v2 = new TH1F("cut_pmzL_v2","Pmz missing momentum", Pmz_nbins, Pmz_xmin, Pmz_xmax);                    
   
  TH1F *cut_pmxq_v2 = new TH1F("cut_pmxq_v2","Pmx missing momentum", Pmx_nbins, Pmx_xmin, Pmx_xmax);            
  TH1F *cut_pmyq_v2 = new TH1F("cut_pmyq_v2","Pmy missing momentum", Pmy_nbins, Pmy_xmin, Pmy_xmax);                                                                             
  TH1F *cut_pmzq_v2 = new TH1F("cut_pmzq_v2","Pmz missing momentum", Pmz_nbins, Pmz_xmin, Pmz_xmax);                    
 
  TH1F *cut_KinN = new TH1F("cut_Kn","Neutron Kin. Energy", Kn_nbins, Kn_xmin, Kn_xmax);                        
  TH1F *cut_KinP = new TH1F("cut_Kp","Proton Kin. Energy", Kp_nbins, Kp_xmin, Kp_xmax);    
  TH1F *cut_E_p = new TH1F("cut_Ep","Proton Final Energy", Ep_nbins, Ep_xmin, Ep_xmax);  
  

  cut_theta_nq->Sumw2();
  cut_Mmiss->Sumw2();
  cut_xbj->Sumw2();
  cut_P_f->Sumw2();
  cut_k_f->Sumw2();
  cut_q_vec->Sumw2();
  cut_theta_q->Sumw2();
  cut_thet_pq->Sumw2();

  //Target Reconstruction Variables
  TH1F *cut_x_tar = new TH1F("cut_x_tar", "x_Target (Lab)", xtar_nbins, xtar_xmin, xtar_xmax);
  
  TH1F *cut_y_tarH = new TH1F("cut_y_tarH", hadron_arm + " y_Target (Lab)", ytar_nbins, ytar_xmin, ytar_xmax);    
  TH1F *cut_z_tarH = new TH1F("cut_z_tarH", hadron_arm + " z_Target (Lab)", ztar_nbins, ztar_xmin, ztar_xmax);                                
                                                                                                                                                                 
  TH1F *cut_y_tarP = new TH1F("cut_y_tarP", electron_arm + " y_Target (Lab)", ytar_nbins, ytar_xmin, ytar_xmax);                     
  TH1F *cut_z_tarP = new TH1F("cut_z_tarP", electron_arm + " z_Target (Lab)", ztar_nbins, ztar_xmin, ztar_xmax);  
  
  //Hadron arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  TH1F *cut_hytar = new TH1F("cut_hytar", hadron_arm + " Y_{tar}", hytar_nbins, hytar_xmin, hytar_xmax);
  TH1F *cut_hxptar = new TH1F("cut_hxptar", hadron_arm + " X'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH1F *cut_hyptar = new TH1F("cut_hyptar", hadron_arm + " Y'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax );
  TH1F *cut_hdelta = new TH1F("cut_hdelta", hadron_arm + " Momentum Acceptance, #delta", hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
  //Hadron arm Focal Plane Quantities
  TH1F *cut_hxfp = new TH1F("cut_hxfp", hadron_arm + " X_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax);
  TH1F *cut_hyfp = new TH1F("cut_hyfp", hadron_arm + " Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax);
  TH1F *cut_hxpfp = new TH1F("cut_hxpfp", hadron_arm + " X'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax );
  TH1F *cut_hypfp = new TH1F("cut_hypfp", hadron_arm + " Y'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax);
  
  
  //Electron Arm Reconstructed Quantities ( xtar, ytar, xptar, yptar, delta)
  TH1F *cut_eytar = new TH1F("cut_eytar", electron_arm + " Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax);
  TH1F *cut_exptar = new TH1F("cut_exptar", electron_arm + " X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax);
  TH1F *cut_eyptar = new TH1F("cut_eyptar", electron_arm + " Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH1F *cut_edelta = new TH1F("cut_edelta", electron_arm + " Momentum Acceptance, #delta", edelta_nbins, edelta_xmin, edelta_xmax);
  
  //Electron Arm Focal Plane Quantities
  TH1F *cut_exfp = new TH1F("cut_exfp", electron_arm + " X_{fp}", exfp_nbins, exfp_xmin, exfp_xmax);
  TH1F *cut_eyfp = new TH1F("cut_eyfp", electron_arm + " Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax);
  TH1F *cut_expfp = new TH1F("cut_expfp", electron_arm + " X'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax);
  TH1F *cut_eypfp = new TH1F("cut_eypfp", electron_arm + " Y'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax);
  
  //Cross-Check correlations
  TH2F *cut_emiss_vs_pmiss = new TH2F("cut_emiss_vs_pmiss", " E_{miss} vs. P_{miss}", Pm_nbins, Pm_xmin, Pm_xmax, Em_nbins, Em_xmin, Em_xmax);
  TH2F *cut_edelta_vs_eyptar = new TH2F("cut_edelta_vs_eyptar", electron_arm + " #delta vs. Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  
  
  //Create 2D Histograms at the Focal Plane Quantities
  TH2F *cut_h_xfp_vs_yfp = new TH2F("cut_h_xfp_vs_yfp", "X_{fp} vs Y_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxfp_nbins, hxfp_xmin, hxfp_xmax);
  TH2F *cut_e_xfp_vs_yfp = new TH2F("cut_e_xfp_vs_yfp", "X_{fp} vs Y_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exfp_nbins, exfp_xmin, exfp_xmax);
  
  //2D HMS v. SHMS Acceptance Correlations
  TH2F *cut_hytar_vs_eytar = new TH2F("cut_hytar_vs_eytar", "HMS vs. SHMS, Y_{tar}", eytar_nbins, eytar_xmin, eytar_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *cut_hxptar_vs_exptar = new TH2F("cut_hxptar_vs_exptar", "HMS vs. SHMS, X'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *cut_hyptar_vs_eyptar = new TH2F("cut_hyptar_vs_eyptar", "HMS vs. SHMS, Y'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *cut_hdelta_vs_edelta = new TH2F("cut_hdelta_vs_edelta", "HMS vs. SHMS, #delta", edelta_nbins, edelta_xmin, edelta_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  
  //OPTICS CHECK (W correlations with electron Focal Plane / Target Quantities)
  TH2F *cut_W_vs_exfp = new TH2F("cut_W_vs_exfp", "cut_W vs eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_expfp = new TH2F("cut_W_vs_expfp", "cut_W vs eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_eyfp = new TH2F("cut_W_vs_eyfp", "cut_W vs eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_eypfp = new TH2F("cut_W_vs_eypfp", "cut_W vs eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, W_nbins, W_xmin, W_xmax);
  
  TH2F *cut_W_vs_eytar = new TH2F("cut_W_vs_eytar", "cut_W vs eY_{tar}", eytar_nbins, eytar_xmin, eytar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_exptar = new TH2F("cut_W_vs_exptar", "cut_W vs eX'_{tar}", exptar_nbins, exptar_xmin, exptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_eyptar = new TH2F("cut_W_vs_eyptar", "cut_W vs eY'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_edelta = new TH2F("cut_W_vs_edelta", "cut_W vs edelta", edelta_nbins, edelta_xmin, edelta_xmax, W_nbins, W_xmin, W_xmax);
  
  //OPTICS CHECK (W correlations with hadron Focal Plane / Target Quantities)
  TH2F *cut_W_vs_hxfp = new TH2F("cut_W_vs_hxfp", "cut_W vs hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hxpfp = new TH2F("cut_W_vs_hxpfp", "cut_W vs hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hyfp = new TH2F("cut_W_vs_hyfp", "cut_W vs hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hypfp = new TH2F("cut_W_vs_hypfp", "cut_W vs hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, W_nbins, W_xmin, W_xmax);
  
  TH2F *cut_W_vs_hytar = new TH2F("cut_W_vs_hytar", "cut_W vs hY_{tar}", hytar_nbins, hytar_xmin, hytar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hxptar = new TH2F("cut_W_vs_hxptar", "cut_W vs hX'_{tar}", hxptar_nbins, hxptar_xmin, hxptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hyptar = new TH2F("cut_W_vs_hyptar", "cut_W vs hY'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax, W_nbins, W_xmin, W_xmax);
  TH2F *cut_W_vs_hdelta = new TH2F("cut_W_vs_hdelta", "cut_W vs hdelta", hdelta_nbins, hdelta_xmin, hdelta_xmax, W_nbins, W_xmin, W_xmax);
  
  //OPTICS CHECK (Electron Arm Reconstructed Quantities vs. Focal Plane Quantities) --Each of the reconstructed quantities is a polynomial expansion of focal plane quantities
  TH2F *cut_eytar_vs_exfp = new TH2F("cut_eytar_vs_exfp", "SHMS eY_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *cut_eytar_vs_expfp = new TH2F("cut_eytar_vs_expfp", "SHMS eY_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *cut_eytar_vs_eyfp = new TH2F("cut_eytar_vs_eyfp", "SHMS eY_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);
  TH2F *cut_eytar_vs_eypfp = new TH2F("cut_eytar_vs_eypfp", "SHMS eY_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, eytar_nbins, eytar_xmin, eytar_xmax);

  TH2F *cut_eyptar_vs_exfp = new TH2F("cut_eyptar_vs_exfp", "SHMS eY'_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *cut_eyptar_vs_expfp = new TH2F("cut_eyptar_vs_expfp", "SHMS eY'_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *cut_eyptar_vs_eyfp = new TH2F("cut_eyptar_vs_eyfp", "SHMS eY'_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);
  TH2F *cut_eyptar_vs_eypfp = new TH2F("cut_eyptar_vs_eypfp", "SHMS eY'_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, eyptar_nbins, eyptar_xmin, eyptar_xmax);

  TH2F *cut_exptar_vs_exfp = new TH2F("cut_exptar_vs_exfp", "SHMS eX'_{tar} vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *cut_exptar_vs_expfp = new TH2F("cut_exptar_vs_expfp", "SHMS eX'_{tar} vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *cut_exptar_vs_eyfp = new TH2F("cut_exptar_vs_eyfp", "SHMS eX'_{tar} vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);
  TH2F *cut_exptar_vs_eypfp = new TH2F("cut_exptar_vs_eypfp", "SHMS eX'_{tar} vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, exptar_nbins, exptar_xmin, exptar_xmax);

  TH2F *cut_edelta_vs_exfp = new TH2F("cut_edelta_vs_exfp", "SHMS Delta e#delta vs. eX_{fp}", exfp_nbins, exfp_xmin, exfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *cut_edelta_vs_expfp = new TH2F("cut_edelta_vs_expfp", "SHMS Delta e#delta vs. eX'_{fp}", expfp_nbins, expfp_xmin, expfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *cut_edelta_vs_eyfp = new TH2F("cut_edelta_vs_eyfp", "SHMS Delta e#delta vs. eY_{fp}", eyfp_nbins, eyfp_xmin, eyfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);
  TH2F *cut_edelta_vs_eypfp = new TH2F("cut_edelta_vs_eypfp", "SHMS Delta e#delta vs. eY'_{fp}", eypfp_nbins, eypfp_xmin, eypfp_xmax, edelta_nbins, edelta_xmin, edelta_xmax);

  //OPTICS CHECK (Hadron  Arm Reconstructed Quantities vs. Focal Plane Quantities) --Each of the reconstructed quantities is a polynomial expansion of focal plane quantities
  TH2F *cut_hytar_vs_hxfp = new TH2F("cut_hytar_vs_hxfp", "HMS hY_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *cut_hytar_vs_hxpfp = new TH2F("cut_hytar_vs_hxpfp", "HMS hY_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *cut_hytar_vs_hyfp = new TH2F("cut_hytar_vs_hyfp", "HMS hY_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);
  TH2F *cut_hytar_vs_hypfp = new TH2F("cut_hytar_vs_hypfp", "HMS hY_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hytar_nbins, hytar_xmin, hytar_xmax);

  TH2F *cut_hyptar_vs_hxfp = new TH2F("cut_hyptar_vs_hxfp", "HMS hY'_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *cut_hyptar_vs_hxpfp = new TH2F("cut_hyptar_vs_hxpfp", "HMS hY'_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *cut_hyptar_vs_hyfp = new TH2F("cut_hyptar_vs_hyfp", "HMS hY'_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);
  TH2F *cut_hyptar_vs_hypfp = new TH2F("cut_hyptar_vs_hypfp", "HMS hY'_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hyptar_nbins, hyptar_xmin, hyptar_xmax);

  TH2F *cut_hxptar_vs_hxfp = new TH2F("cut_hxptar_vs_hxfp", "HMS hX'_{tar} vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *cut_hxptar_vs_hxpfp = new TH2F("cut_hxptar_vs_hxpfp", "HMS hX'_{tar} vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *cut_hxptar_vs_hyfp = new TH2F("cut_hxptar_vs_hyfp", "HMS hX'_{tar} vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);
  TH2F *cut_hxptar_vs_hypfp = new TH2F("cut_hxptar_vs_hypfp", "HMS hX'_{tar} vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);

  TH2F *cut_hdelta_vs_hxfp = new TH2F("cut_hdelta_vs_hxfp", "HMS Delta h#delta vs. hX_{fp}", hxfp_nbins, hxfp_xmin, hxfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *cut_hdelta_vs_hxpfp = new TH2F("cut_hdelta_vs_hxpfp", "HMS Delta h#delta vs. hX'_{fp}", hxpfp_nbins, hxpfp_xmin, hxpfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *cut_hdelta_vs_hyfp = new TH2F("cut_hdelta_vs_hyfp", "HMS Delta h#delta vs. hY_{fp}", hyfp_nbins, hyfp_xmin, hyfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);
  TH2F *cut_hdelta_vs_hypfp = new TH2F("cut_hdelta_vs_hypfp", "HMS Delta h#delta vs. hY'_{fp}", hypfp_nbins, hypfp_xmin, hypfp_xmax, hdelta_nbins, hdelta_xmin, hdelta_xmax);

  TH2F *cut_Q2_vs_thnq = new TH2F("cut_Q2_vs_thnq", "Q2 vs. #theta_{nq}", thnq_nbins, thnq_xmin, thnq_xmax, Q2_nbins, Q2_xmin, Q2_xmax);         
  TH2F *cut_Q2_vs_Pm = new TH2F("cut_Q2_vs_Pm", "Q2 vs. Pm", Pm_nbins, Pm_xmin, Pm_xmax, Q2_nbins, Q2_xmin, Q2_xmax);  

  //Solid Angle Acceptance Plots                                                                                                                                           
  TH2F *cut_exptar_vs_eyptar = new TH2F("cut_exptar_vs_eyptar", "SHMS eX'_{tar} vs. eY'_{tar}", eyptar_nbins, eyptar_xmin, eyptar_xmax, exptar_nbins, exptar_xmin, exptar_xmax);             
  TH2F *cut_hxptar_vs_hyptar = new TH2F("cut_hxptar_vs_hyptar", "HMS hX'_{tar} vs. hY'_{tar}", hyptar_nbins, hyptar_xmin, hyptar_xmax, hxptar_nbins, hxptar_xmin, hxptar_xmax);              
  
  
  Float_t  Normfac;
  Float_t  h_delta;
  Float_t  h_yptar;
  Float_t  h_xptar;
  Float_t  h_ytar;
  Float_t  h_xfp;
  Float_t  h_xpfp;
  Float_t  h_yfp;
  Float_t  h_ypfp;
  Float_t  h_deltai;
  Float_t  h_yptari;
  Float_t  h_xptari;
  Float_t  h_ytari;
  Float_t  e_delta;
  Float_t  e_yptar;
  Float_t  e_xptar;
  Float_t  e_ytar;
  Float_t  e_xfp;
  Float_t  e_xpfp;
  Float_t  e_yfp;
  Float_t  e_ypfp;
  Float_t  e_deltai;
  Float_t  e_yptari;
  Float_t  e_xptari;
  Float_t  e_ytari;
  Float_t  q;
  Float_t  nu;
  Float_t  Q2;
  Float_t  W;
  Float_t  epsilon;
  Float_t  Em;
  Float_t  Pm;
  Float_t  theta_pq;
  Float_t  phi_pq;
  Float_t  corrsing;
  Float_t  Pmx;
  Float_t  Pmy;
  Float_t  Pmz;
  Float_t  PmPar;
  Float_t  PmPer;
  Float_t  PmOop;
  Float_t  fry;
  Float_t  radphot;
  Float_t  sigcc;
  Float_t  Weight;
  Float_t  Jacobian;
  Float_t  theta_e;
  Float_t  theta_p;
  Float_t  tar_x;
  Float_t  tar_y;
  Float_t  tar_z;
  Float_t  Genweight;
  Float_t  SF_weight;
  Float_t  Jacobian_corr;
  Float_t  sig;
  Float_t  sig_recon;
  Float_t  sigcc_recon;
  Float_t  coul_corr;
  Float_t  h_zv;
  Float_t  h_yv;
  Float_t  e_zv;
  Float_t  e_yv;
  Float_t  h_pf;
  Float_t  e_pf;
  Float_t  Ein;
  Float_t  theta_rq;
  Float_t  SF_weight_recon;
  Float_t  h_Thf;
  Float_t  Ein_v;
  

  //Define SIMC TTree Variables
  SNT->SetBranchAddress("Normfac", &Normfac);
  SNT->SetBranchAddress("h_delta", &h_delta);
  SNT->SetBranchAddress("h_yptar", &h_yptar);
  SNT->SetBranchAddress("h_xptar", &h_xptar);
  SNT->SetBranchAddress("h_ytar", &h_ytar);
  SNT->SetBranchAddress("h_xfp", &h_xfp);
  SNT->SetBranchAddress("h_xpfp", &h_xpfp);
  SNT->SetBranchAddress("h_yfp", &h_yfp);
  SNT->SetBranchAddress("h_ypfp", &h_ypfp);
  SNT->SetBranchAddress("h_deltai", &h_deltai);
  SNT->SetBranchAddress("h_yptari", &h_yptari);
  SNT->SetBranchAddress("h_xptari", &h_xptari);
  SNT->SetBranchAddress("h_ytari", &h_ytari);
  SNT->SetBranchAddress("e_delta", &e_delta);
  SNT->SetBranchAddress("e_yptar", &e_yptar);
  SNT->SetBranchAddress("e_xptar", &e_xptar);
  SNT->SetBranchAddress("e_ytar", &e_ytar);
  SNT->SetBranchAddress("e_xfp", &e_xfp);
  SNT->SetBranchAddress("e_xpfp", &e_xpfp);
  SNT->SetBranchAddress("e_yfp", &e_yfp);
  SNT->SetBranchAddress("e_ypfp", &e_ypfp);
  SNT->SetBranchAddress("e_deltai", &e_deltai);
  SNT->SetBranchAddress("e_yptari", &e_yptari);
  SNT->SetBranchAddress("e_xptari", &e_xptari);
  SNT->SetBranchAddress("e_ytari", &e_ytari);
  SNT->SetBranchAddress("q", &q);
  SNT->SetBranchAddress("nu", &nu);
  SNT->SetBranchAddress("Q2", &Q2);
  SNT->SetBranchAddress("W", &W);
  SNT->SetBranchAddress("epsilon", &epsilon);
  SNT->SetBranchAddress("Em", &Em);
  SNT->SetBranchAddress("Pm", &Pm);
  SNT->SetBranchAddress("theta_pq", &theta_pq);
  SNT->SetBranchAddress("phi_pq", &phi_pq);
  SNT->SetBranchAddress("corrsing", &corrsing);
  SNT->SetBranchAddress("Pmx", &Pmx);
  SNT->SetBranchAddress("Pmy", &Pmy);
  SNT->SetBranchAddress("Pmz", &Pmz);
  SNT->SetBranchAddress("PmPar", &PmPar);    //Missing Momentum Components in q-vector coordinates (parallel to q-vec)
  SNT->SetBranchAddress("PmPer", &PmPer);    //(Perpendicular to q-vec)
  SNT->SetBranchAddress("PmOop", &PmOop);    //(Out of plane to q-vec)
  SNT->SetBranchAddress("fry", &fry);
  SNT->SetBranchAddress("radphot", &radphot);
  SNT->SetBranchAddress("sigcc", &sigcc);
  SNT->SetBranchAddress("Weight", &Weight);
  SNT->SetBranchAddress("Jacobian", &Jacobian);
  SNT->SetBranchAddress("theta_e", &theta_e);
  SNT->SetBranchAddress("theta_p", &theta_p);
  SNT->SetBranchAddress("tar_x", &tar_x);
  SNT->SetBranchAddress("tar_y", &tar_y);
  SNT->SetBranchAddress("tar_z", &tar_z);
  SNT->SetBranchAddress("Genweight", &Genweight);
  SNT->SetBranchAddress("SF_weight", &SF_weight);
  SNT->SetBranchAddress("Jacobian_corr", &Jacobian_corr);
  SNT->SetBranchAddress("sig", &sig);
  SNT->SetBranchAddress("sig_recon", &sig_recon);
  SNT->SetBranchAddress("sigcc_recon", &sigcc_recon);
  SNT->SetBranchAddress("coul_corr", &coul_corr);
  SNT->SetBranchAddress("h_zv", &h_zv);
  SNT->SetBranchAddress("h_yv", &h_yv);
  SNT->SetBranchAddress("e_zv", &e_zv);
  SNT->SetBranchAddress("e_yv", &e_yv);
  SNT->SetBranchAddress("h_pf", &h_pf);
  SNT->SetBranchAddress("e_pf", &e_pf);
  SNT->SetBranchAddress("Ein", &Ein);
  SNT->SetBranchAddress("theta_rq", &theta_rq);
  SNT->SetBranchAddress("SF_weight_recon", &SF_weight_recon);
  SNT->SetBranchAddress("h_Thf", &h_Thf);
  SNT->SetBranchAddress("Ein_v", &Ein_v);

  //Declare Neccessary Variables to Determine the 4-Momentum of Recoil System
  TLorentzVector fP0;           // Beam 4-momentum
  TLorentzVector fP1;           // Scattered electron 4-momentum
  TLorentzVector fA;            // Target 4-momentum
  TLorentzVector fA1;           // Final system 4-momentum
  TLorentzVector fQ;            // Momentum transfer 4-vector
  TLorentzVector fX;            // Detected secondary particle 4-momentum (GeV)
  TLorentzVector fB;            // Recoil system 4-momentum (GeV)

  TVector3 Pf_vec;
  TVector3 kf_vec;

  
  //Central in-plane (th) and out-of-plane (ph) (should be zero for both spectrometers)
  Double_t h_th = -38.896;    //the neg. sign indicates which side of the beam pipe the spec. is on (- means beam right)
  Double_t h_ph = 0.;
  
  Double_t e_th = 12.194;
  Double_t e_ph = 0.;




  //Declare necessary variables for rotaion from +z to +q
  TVector3 qvec(0.,0.,0.);
  TVector3 kfvec(0.,0.,0.);
  TRotation rot_to_q;
  TVector3 bq(0.,0.,0.);   //recoil system in lab frame (Pmx, Pmy, Pmz)
  TVector3 p_miss_q(0.,0.,0.);   //recoil system in q-frame
  Double_t Pm_alt;




  //Define Additional Kinematic Variables
  Double_t Eb = 10.6005;  //GeV Beam Energy
  Double_t W2;             //Invarianrt Mass Squared
  Double_t X;              //B-jorken X
  Double_t Pf;             //Final Proton Momentum 
  Double_t Pfv2;           //Final Proton Momentum (NOT using delta)
  Double_t Kp;               //Proton Kinetic Energy
  Double_t Kn;               //Neutron Kinetic Energy
  Double_t MM;              //Missing Mass
  Double_t MM_2;
  Double_t ki;             //Incident e- momentum
  Double_t kf;             //Final electron momentum
  Double_t kfv2;
  Double_t En;             //Neutron Energy
  Double_t Ep;             //proton final energy
  Double_t Ee;             //electron final energy
  Double_t th_nq;       //Angle between q-vector and neutron
  Double_t th_q;         //Angle between q-vector and beamline (+z axis --lab)
  Double_t th_pq;          //version 2 of theta_pq
  Double_t qx, qy, qz;
  Double_t kfx, kfy, kfz;
  Double_t Pmx_v2, Pmy_v2, Pmz_v2, Pm_v2;
  Double_t PmPer_v2, PmOop_v2, PmPar_v2;



  //Define Histograms for Emiss cut study                                                                                                                                           
  TH1F *pm_noemcut = new TH1F("pm_noemcut", "Pmiss Study", Pm_nbins, Pm_xmin, Pm_xmax);                                                                                         
  TH1F *pm_em30cut = new TH1F("pm_em30cut", "Pmiss Study", Pm_nbins, Pm_xmin, Pm_xmax);                                                                                
  TH1F *pm_em60cut = new TH1F("pm_em60cut", "Pmiss Study", Pm_nbins, Pm_xmin, Pm_xmax);                                                                                        
  TH1F *pm_em90cut = new TH1F("pm_em90cut", "Pmiss Study", Pm_nbins, Pm_xmin, Pm_xmax); 

  //Determine Full Weight Quantities (Assume one for heep check)
  Double_t FullWeight;
  Double_t Fps; //Phase Space weight factor

  //  dSigma / dX  =  K * sig_cc,   factor --> K * sig_cc,  where K = Ep * Pp / (2*pi)^{3}
  Double_t red_xsec_factor;   

  //simc Pmiss is weighted by this factor to get the SIMC reduced cross section
  Double_t red_xsec_simc;
  Double_t red_xsec_simc2;

  //Define Boolean for Kin. Cuts
  Bool_t c_Em;
  Bool_t c_hdelta;
  Bool_t c_edelta;
  Bool_t c_Q2;
  Bool_t c_th_nq;
  Bool_t c_MM;

  //Acceptance Cuts                                                                                                                                
  Bool_t c_exptar;                                                                                                                                    
  Bool_t c_eyptar;                                                                                                                               
  Bool_t c_hxptar;                                                                                                            
  Bool_t c_hyptar;                                                                                                                    
  Bool_t c_eSolid;                                                                                                                          
  Bool_t c_hSolid; 

  //=======================
  // E N T R Y    L O O P
  //=======================

  Long64_t nentries = SNT->GetEntries();  

  for (Long64_t i=0; i<nentries;i++) {
    
    SNT->GetEntry(i);
   
    //If cross section sigma = 0, continue to next event
    //    if(sig==0) continue;




    //-----Define Additional Kinematic Variables--------
    Ein = Ein / 1000.;   //This beam energy has Eloss, therefore, it is slightly smaller than 10.6005 (10.5992)
    W2 = W*W;
    ki = sqrt(Ein*Ein - me*me);    //use beam energy without Eloss corrections, as they are NOT done in data as well                       
    kf = e_pf/1000.;               //final electron momentum magnitude
    Ee = sqrt(me*me + kf*kf);
    Pf = h_pf/1000.;
    En = sqrt(MN*MN + Pm*Pm);
    Pfv2 = sqrt(pow(nu + MD - En,2) - MP*MP);
    Ep = sqrt(MP*MP + Pfv2*Pfv2);
    X = Q2 / (2.*MP*nu);
    th_q = acos( (ki - kf*cos(theta_e))/q ); //th_q = theta_p + theta_pq;
    th_pq =  th_q - theta_p;
    th_nq = acos((q - Pf*cos(th_pq))/Pm);
    MM = TMath::Sqrt( TMath::Power(nu+MD-sqrt(MP*MP+Pf*Pf),2) - Pm*Pm );
    MM_2 = MM*MM;
    Kp = Ep - MP;
    Kn = En - MN;
        

    
    //Calculate electron final momentum 3-vector
    SetCentralAngles(e_th, e_ph);
    TransportToLab(kf, e_xptar, e_yptar, kf_vec);


    //Calculate 4-Vectors
    fP0.SetXYZM(0.0, 0.0, ki, me);  //set initial e- 4-momentum
    fP1.SetXYZM(kf_vec.X(), kf_vec.Y(), kf_vec.Z(), me);  //set final e- 4-momentum
    fA.SetXYZM(0.0, 0.0, 0.0, MD);  //Set initial target at rest
    fQ = fP0 - fP1;
    fA1 = fA + fQ;   //final target (sum of final hadron four momenta)

    //Get Detected Particle 4-momentum
    SetCentralAngles(h_th, h_ph);
    TransportToLab(Pf, h_xptar, h_yptar, Pf_vec);
    fX.SetVectM(Pf_vec, MP);    //SET FOUR VECTOR OF detected particle
    fB = fA1 - fX;   //4-MOMENTUM OF UNDETECTED PARTICLE 

    Pmx_v2 = fB.X();
    Pmy_v2 = fB.Y(); 
    Pmz_v2 = fB.Z(); 

    Pm_v2 = sqrt(Pmx_v2*Pmx_v2 + Pmy_v2*Pmy_v2 + Pmz_v2*Pmz_v2);

    //--------Rotate the recoil system from +z to +q-------
    qvec = fQ.Vect();
    kfvec = fP1.Vect();

    rot_to_q.SetZAxis( qvec, kfvec).Invert();

    bq = fB.Vect();
    
    bq *= rot_to_q;
    p_miss_q = -bq;

    PmPar_v2 = p_miss_q.Z();
    PmPer_v2 = p_miss_q.X();
    PmOop_v2 = p_miss_q.Y();

    //Define cuts
    c_Em = Em<0.04;
    c_exptar = abs(e_xptar)<0.025; 
    c_eyptar = e_yptar > -0.027 && e_yptar < 0.027;                  
    c_eSolid = c_exptar&&c_eyptar; 
    c_hdelta = h_delta > -8. && h_delta < 8.;
    c_edelta = e_delta > -2.7 && e_delta < 2.7;
    c_Q2 = Q2 >4.2;
    c_th_nq = (th_nq/dtr) >= 35. &&  (th_nq/dtr) <=45. ;
    c_th_nq = (th_nq/dtr) >= 55. &&  (th_nq/dtr) <=65. ;
    c_th_nq = (th_nq/dtr) >= 45. &&  (th_nq/dtr) <=55. ;
    c_MM = MM > 0.92 && MM < 0.96;

    //Full Weight
    FullWeight = (Normfac*Weight*charge_factor*e_trkEff*h_trkEff*t_LT)/nentries;

    //Phase Space Weight 
    Fps = FullWeight / sig ;  //Divide out the cross section

    
    //Reduced Cross Section (Momentum Distribution) Factor  (Pmiss is weighted by this and divided by Pmiss, to get average Ksigma_cc)
    red_xsec_factor = (sqrt(MP*MP + Pf*Pf) * Pf / pow(2.*TMath::Pi(),3)) * sigcc;      //factor = Ep * Pp / (2*pi)^{3}  * sigma_cc = K*sigma_cc
    

    //SIMC Reduced Cross Section (Model Dependent)
    red_xsec_simc = sig / (red_xsec_factor);
    red_xsec_simc2 = Weight / (red_xsec_factor);


    // cout << "Full Weight = " << FullWeight << endl;
    // cout << "Sig = " << sig << endl;
    //cout << "FPS = " << Fps << endl;


    //APPLY CUTS: BEGIN CUTS LOOP
      if (c_Em&&c_hdelta&&c_edelta)
	{

	  //Fill Phase Space
	  cut_pm_ps->Fill(Pm, Fps);   //This Phase Space is used to get experimental cross sections
	  cut_pm_ps_red->Fill(Pm);   //This Phase Space is used to get the average K*sigma_cc
	  cut_Kred->Fill(Pm, red_xsec_factor);  //Missing Momentum, Weighted by reduced cross_section factor
	  

	  cut_pm_red->Fill(Pm, red_xsec_simc);  //This histogram should be divided by the cut_pm_ps_red, to get the model red. cross section
	  cut_pm_red2->Fill(Pm, red_xsec_simc2);  //This histogram should be divided by the cut_pm_ps_red, to get the model red. cross section


	  //Divide to get simc  red. cross section
	  // Fill->(Pm,  sig / (red_xsec_factor))
	  // Fill->(Pm)

	  // K*sigma_cc_avg =  Pm[weighted by K*sigma_cc] / Pm =  cut_Kred / cut_pm_ps_red.  This is done by dividing these two histogram objects in another code.
	  //The experimental cross section is then divided by K*sigma_cc_avg to get the reduced cross section

	  //Exp. red. Xsec  = sigma_exp(data) / K*sigma_cc_avg, where sigma_exp(data) = dataYield / cut_pm_ps

	  //Kinematics
	  cut_Emiss->Fill(Em, FullWeight);
	  cut_pm->Fill(Pm, FullWeight);
	  cut_pm_v2->Fill(Pm_v2, FullWeight);

	  cut_pmX_lab->Fill(-Pmx, FullWeight);
	  cut_pmY_lab->Fill(Pmy, FullWeight);
	  cut_pmZ_lab->Fill(Pmz, FullWeight);

	  cut_pmxL_v2->Fill(Pmx_v2, FullWeight);
	  cut_pmyL_v2->Fill(Pmy_v2, FullWeight);
	  cut_pmzL_v2->Fill(Pmz_v2, FullWeight);

	  cut_pmX_q->Fill(PmPer, FullWeight);
	  cut_pmY_q->Fill(PmOop, FullWeight);
	  cut_pmZ_q->Fill(PmPar, FullWeight);

	  cut_pmxq_v2->Fill(PmPer_v2, FullWeight);
	  cut_pmyq_v2->Fill(PmOop_v2, FullWeight);
	  cut_pmzq_v2->Fill(PmPar_v2, FullWeight);

	  cut_Q_2->Fill(Q2, FullWeight);
	  cut_omega->Fill(nu, FullWeight);
	  cut_W_inv->Fill(W, FullWeight);
	  cut_theta_elec->Fill(theta_e/dtr, FullWeight);
	  cut_theta_prot->Fill(theta_p/dtr, FullWeight);

	  
	  //Additional Kinematics Variables
	  cut_W_2->Fill(W2, FullWeight); 
	  cut_xbj->Fill(X, FullWeight); 
	  cut_P_f->Fill(Pfv2, FullWeight);
	  cut_k_f->Fill(kf, FullWeight);
	  cut_E_n->Fill(En, FullWeight);
	  cut_theta_q->Fill(th_q/dtr, FullWeight);
	  cut_q_vec->Fill(q, FullWeight);
	  cut_thet_pq->Fill(theta_pq/dtr, FullWeight);
	  cut_thet_pq_v2->Fill(th_pq/dtr, FullWeight);
	  cut_theta_nq->Fill(th_nq/dtr, FullWeight);

	  cut_Mmiss->Fill(MM, FullWeight);
	  cut_MM2->Fill(MM_2, FullWeight);

	  cut_KinN->Fill(Kn, FullWeight);
	  cut_KinP->Fill(Kp, FullWeight);
	  cut_E_p->Fill(Ep, FullWeight);

	  //Reconstructed Target Quantities (Lab Frame)
	  cut_x_tar->Fill(-tar_x, FullWeight);
	  
	  cut_y_tarH->Fill(h_yv, FullWeight);
	  cut_z_tarH->Fill(h_zv, FullWeight);
	  
	  cut_y_tarP->Fill(e_yv, FullWeight);         
          cut_z_tarP->Fill(e_zv, FullWeight); 
	  
	  //Hadron-Arm Target Reconstruction 
	  cut_hytar->Fill(h_ytar, FullWeight);
	  cut_hxptar->Fill(h_xptar, FullWeight);
	  cut_hyptar->Fill(h_yptar, FullWeight);
	  cut_hdelta->Fill(h_delta, FullWeight);
	  
	  //Hadron-Arm Focal Plane
	  cut_hxfp->Fill(h_xfp, FullWeight);
	  cut_hyfp->Fill(h_yfp, FullWeight);
	  cut_hxpfp->Fill(h_xpfp, FullWeight);
	  cut_hypfp->Fill(h_ypfp, FullWeight);
	  
	  //Electron-Arm Target Reconstruction
	  cut_eytar->Fill(e_ytar, FullWeight);
	  cut_exptar->Fill(e_xptar, FullWeight);
	  cut_eyptar->Fill(e_yptar, FullWeight);
	  cut_edelta->Fill(e_delta, FullWeight);
	  
	  //Electron-Arm Focal Plane
	  cut_exfp->Fill(e_xfp, FullWeight);
	  cut_eyfp->Fill(e_yfp, FullWeight);
	  cut_expfp->Fill(e_xpfp, FullWeight);
	  cut_eypfp->Fill(e_ypfp, FullWeight);
	  

	  //Fill 2D HMS Focal Plane Quantities
	  cut_h_xfp_vs_yfp->Fill(h_yfp, h_xfp, FullWeight);
	  cut_e_xfp_vs_yfp->Fill(e_yfp, e_xfp, FullWeight);
	  
	  //Fill 2D reconstructed variables
	  cut_hytar_vs_eytar->Fill(e_ytar, h_ytar, FullWeight);
	  cut_hxptar_vs_exptar->Fill(e_xptar, h_xptar, FullWeight);
	  cut_hyptar_vs_eyptar->Fill(e_yptar, h_yptar, FullWeight);
	  cut_hdelta_vs_edelta->Fill(e_delta, h_delta, FullWeight);

	  
	  //Heep cross check
	  cut_emiss_vs_pmiss->Fill(Pm, Em, FullWeight);
	  cut_edelta_vs_eyptar->Fill(e_yptar, e_delta, FullWeight);
	  
	  //OPTICS CHECK (W vs. electron arm focal plane)
	  cut_W_vs_exfp->Fill(e_xfp, W, FullWeight);
	  cut_W_vs_expfp->Fill(e_xpfp, W, FullWeight);
	  cut_W_vs_eyfp->Fill(e_yfp, W, FullWeight);
	  cut_W_vs_eypfp->Fill(e_ypfp, W, FullWeight);
	  
	  cut_W_vs_eytar->Fill(e_ytar, W, FullWeight);
	  cut_W_vs_exptar->Fill(e_xptar, W, FullWeight);
	  cut_W_vs_eyptar->Fill(e_yptar, W, FullWeight);
	  cut_W_vs_edelta->Fill(e_delta, W, FullWeight);

	  //OPTICS CHECK (W vs. hadron arm focal plane)
	  cut_W_vs_hxfp->Fill(h_xfp, W, FullWeight);
	  cut_W_vs_hxpfp->Fill(h_xpfp, W, FullWeight);
	  cut_W_vs_hyfp->Fill(h_yfp, W, FullWeight);
	  cut_W_vs_hypfp->Fill(h_ypfp, W, FullWeight);
	  
	  cut_W_vs_hytar->Fill(h_ytar, W, FullWeight);
	  cut_W_vs_hxptar->Fill(h_xptar, W, FullWeight);
	  cut_W_vs_hyptar->Fill(h_yptar, W, FullWeight);
	  cut_W_vs_hdelta->Fill(h_delta, W, FullWeight);
	  
	  //OPTICS CHECK (electron Arm Recon. vs. Focal Plane)
	  cut_eytar_vs_exfp->Fill(e_xfp, e_ytar);
	  cut_eytar_vs_expfp->Fill(e_xpfp, e_ytar);
	  cut_eytar_vs_eyfp->Fill(e_yfp, e_ytar);
	  cut_eytar_vs_eypfp->Fill(e_ypfp, e_ytar);
  
	  cut_eyptar_vs_exfp->Fill(e_xfp, e_yptar);
	  cut_eyptar_vs_expfp->Fill(e_xpfp, e_yptar);
	  cut_eyptar_vs_eyfp->Fill(e_yfp, e_yptar);
	  cut_eyptar_vs_eypfp->Fill(e_ypfp, e_yptar);

	  cut_exptar_vs_exfp->Fill(e_xfp, e_xptar);
	  cut_exptar_vs_expfp->Fill(e_xpfp, e_xptar);
	  cut_exptar_vs_eyfp->Fill(e_yfp, e_xptar);
	  cut_exptar_vs_eypfp->Fill(e_ypfp, e_xptar);

	  cut_edelta_vs_exfp->Fill(e_xfp, e_delta);
	  cut_edelta_vs_expfp->Fill(e_xpfp, e_delta);
	  cut_edelta_vs_eyfp->Fill(e_yfp, e_delta);
	  cut_edelta_vs_eypfp->Fill(e_ypfp, e_delta);

	  //OPTICS CHECK (hadron Arm Recon. vs. Focal Plane)
	  cut_hytar_vs_hxfp->Fill(h_xfp, h_ytar);
	  cut_hytar_vs_hxpfp->Fill(h_xpfp, h_ytar);
	  cut_hytar_vs_hyfp->Fill(h_yfp, h_ytar);
	  cut_hytar_vs_hypfp->Fill(h_ypfp, h_ytar);
  
	  cut_hyptar_vs_hxfp->Fill(h_xfp, h_yptar);
	  cut_hyptar_vs_hxpfp->Fill(h_xpfp, h_yptar);
	  cut_hyptar_vs_hyfp->Fill(h_yfp, h_yptar);
	  cut_hyptar_vs_hypfp->Fill(h_ypfp, h_yptar);

	  cut_hxptar_vs_hxfp->Fill(h_xfp, h_xptar);
	  cut_hxptar_vs_hxpfp->Fill(h_xpfp, h_xptar);
	  cut_hxptar_vs_hyfp->Fill(h_yfp, h_xptar);
	  cut_hxptar_vs_hypfp->Fill(h_ypfp, h_xptar);

	  cut_hdelta_vs_hxfp->Fill(h_xfp, h_delta);
	  cut_hdelta_vs_hxpfp->Fill(h_xpfp, h_delta);
	  cut_hdelta_vs_hyfp->Fill(h_yfp, h_delta);
	  cut_hdelta_vs_hypfp->Fill(h_ypfp, h_delta);

	  cut_Q2_vs_thnq->Fill(th_nq/dtr, Q2, FullWeight);
	  cut_Q2_vs_Pm->Fill(Pm, Q2, FullWeight);

	  //Solid Angle Acceptance                                                                                                    
          cut_exptar_vs_eyptar->Fill(e_yptar, e_xptar, FullWeight);                                                              
          cut_hxptar_vs_hyptar->Fill(h_yptar, h_xptar, FullWeight); 

	}//End CUTS LOOP

      //Fill Phase SPace
      pm_ps->Fill(Pm,  Fps);       
      
      //Kinematics
      Emiss->Fill(Em, FullWeight);

      pm->Fill(Pm, FullWeight);
      Q_2->Fill(Q2, FullWeight);
      omega->Fill(nu, FullWeight);
      W_inv->Fill(W, FullWeight);
      theta_elec->Fill(theta_e/dtr, FullWeight);
      theta_prot->Fill(theta_p/dtr, FullWeight);


      //Additional Kinematics Variables
      W_2->Fill(W2, FullWeight); 
      xbj->Fill(X, FullWeight); 
      P_f->Fill(Pfv2, FullWeight);
      k_f->Fill(kfv2, FullWeight);
      E_n->Fill(En, FullWeight);
      theta_q->Fill(th_q/dtr, FullWeight);
      q_vec->Fill(q, FullWeight);
      thet_pq->Fill(theta_pq/dtr, FullWeight);
      thet_pq_v2->Fill(th_pq/dtr, FullWeight);
      theta_nq->Fill(th_nq/dtr, FullWeight);

      Mmiss->Fill(MM, FullWeight);     
      MM2->Fill(MM_2, FullWeight);                                                                                                                                                 
      KinN->Fill(Kn, FullWeight);                                                                                                                                                  
      KinP->Fill(Kp, FullWeight);
      pmx->Fill(Pmx, FullWeight);
      pmy->Fill(Pmy, FullWeight);
      pmz->Fill(Pmz, FullWeight);
      E_p->Fill(Ep, FullWeight);

      //Reconstructed Target Quantities (Lab Frame)
      x_tar->Fill(-tar_x, FullWeight);          
      y_tarH->Fill(h_yv, FullWeight);                                                                                                                                             
      z_tarH->Fill(h_zv, FullWeight); 
      y_tarP->Fill(e_yv, FullWeight);                                                                                                                                             
      z_tarP->Fill(e_zv, FullWeight);    

      
      //Hadron-Arm Target Reconstruction 
      hytar->Fill(h_ytar, FullWeight);
      hxptar->Fill(h_xptar, FullWeight);
      hyptar->Fill(h_yptar, FullWeight);
      hdelta->Fill(h_delta, FullWeight);
      
      //Hadron-Arm Focal Plane
      hxfp->Fill(h_xfp, FullWeight);
      hyfp->Fill(h_yfp, FullWeight);
      hxpfp->Fill(h_xpfp, FullWeight);
      hypfp->Fill(h_ypfp, FullWeight);
      
      //Electron-Arm Target Reconstruction
      eytar->Fill(e_ytar, FullWeight);
      exptar->Fill(e_xptar, FullWeight);
      eyptar->Fill(e_yptar, FullWeight);
      edelta->Fill(e_delta, FullWeight);
      
      //Electron-Arm Focal Plane
      exfp->Fill(e_xfp, FullWeight);
      eyfp->Fill(e_yfp, FullWeight);
      expfp->Fill(e_xpfp, FullWeight);
      eypfp->Fill(e_ypfp, FullWeight);

      
      //Fill 2D HMS Focal Plane Quantities
      h_xfp_vs_yfp->Fill(h_yfp, h_xfp, FullWeight);
      e_xfp_vs_yfp->Fill(e_yfp, e_xfp, FullWeight);

      //Fill 2D reconstructed variables
      hytar_vs_eytar->Fill(e_ytar, h_ytar, FullWeight);
      hxptar_vs_exptar->Fill(e_xptar, h_xptar, FullWeight);
      hyptar_vs_eyptar->Fill(e_yptar, h_yptar, FullWeight);
      hdelta_vs_edelta->Fill(e_delta, h_delta, FullWeight);

      //Heep cross check
      emiss_vs_pmiss->Fill(Pm, Em, FullWeight);
      edelta_vs_eyptar->Fill(e_yptar, e_delta, FullWeight);
     	 
      //OPTICS CHECK (W vs. electron arm focal plane)
      W_vs_exfp->Fill(e_xfp, W, FullWeight);
      W_vs_expfp->Fill(e_xpfp, W, FullWeight);
      W_vs_eyfp->Fill(e_yfp, W, FullWeight);
      W_vs_eypfp->Fill(e_ypfp, W, FullWeight);
      
      W_vs_eytar->Fill(e_ytar, W, FullWeight);
      W_vs_exptar->Fill(e_xptar, W, FullWeight);
      W_vs_eyptar->Fill(e_yptar, W, FullWeight);
      W_vs_edelta->Fill(e_delta, W, FullWeight);
	  
      //OPTICS CHECK (W vs. hadron arm focal plane)
      W_vs_hxfp->Fill(h_xfp, W, FullWeight);
      W_vs_hxpfp->Fill(h_xpfp, W, FullWeight);
      W_vs_hyfp->Fill(h_yfp, W, FullWeight);
      W_vs_hypfp->Fill(h_ypfp, W, FullWeight);
      
      W_vs_hytar->Fill(h_ytar, W, FullWeight);
      W_vs_hxptar->Fill(h_xptar, W, FullWeight);
      W_vs_hyptar->Fill(h_yptar, W, FullWeight);
      W_vs_hdelta->Fill(h_delta, W, FullWeight);


      //OPTICS CHECK (Emiss vs. electron arm focal plane)
      Em_vs_exfp->Fill(e_xfp, Em, FullWeight);
      Em_vs_expfp->Fill(e_xpfp, Em, FullWeight);
      Em_vs_eyfp->Fill(e_yfp, Em, FullWeight);
      Em_vs_eypfp->Fill(e_ypfp, Em, FullWeight);
      
      Em_vs_eytar->Fill(e_ytar, Em, FullWeight);
      Em_vs_exptar->Fill(e_xptar, Em, FullWeight);
      Em_vs_eyptar->Fill(e_yptar, Em, FullWeight);
      Em_vs_edelta->Fill(e_delta, Em, FullWeight);
	  
      //OPTICS CHECK (Emiss vs. hadron arm focal plane)
      Em_vs_hxfp->Fill(h_xfp, Em, FullWeight);
      Em_vs_hxpfp->Fill(h_xpfp, Em, FullWeight);
      Em_vs_hyfp->Fill(h_yfp, Em, FullWeight);
      Em_vs_hypfp->Fill(h_ypfp, Em, FullWeight);
      
      Em_vs_hytar->Fill(h_ytar, Em, FullWeight);
      Em_vs_hxptar->Fill(h_xptar, Em, FullWeight);
      Em_vs_hyptar->Fill(h_yptar, Em, FullWeight);
      Em_vs_hdelta->Fill(h_delta, Em, FullWeight);
      
      //OPTICS CHECK (electron Arm Recon. vs. Focal Plane)
      eytar_vs_exfp->Fill(e_xfp, e_ytar);
      eytar_vs_expfp->Fill(e_xpfp, e_ytar);
      eytar_vs_eyfp->Fill(e_yfp, e_ytar);
      eytar_vs_eypfp->Fill(e_ypfp, e_ytar);
      
      eyptar_vs_exfp->Fill(e_xfp, e_yptar);
      eyptar_vs_expfp->Fill(e_xpfp, e_yptar);
      eyptar_vs_eyfp->Fill(e_yfp, e_yptar);
      eyptar_vs_eypfp->Fill(e_ypfp, e_yptar);
      
      exptar_vs_exfp->Fill(e_xfp, e_xptar);
      exptar_vs_expfp->Fill(e_xpfp, e_xptar);
      exptar_vs_eyfp->Fill(e_yfp, e_xptar);
      exptar_vs_eypfp->Fill(e_ypfp, e_xptar);
      
      edelta_vs_exfp->Fill(e_xfp, e_delta);
      edelta_vs_expfp->Fill(e_xpfp, e_delta);
      edelta_vs_eyfp->Fill(e_yfp, e_delta);
      edelta_vs_eypfp->Fill(e_ypfp, e_delta);
      
      //OPTICS CHECK (hadron Arm Recon. vs. Focal Plane)
      hytar_vs_hxfp->Fill(h_xfp, h_ytar);
      hytar_vs_hxpfp->Fill(h_xpfp, h_ytar);
      hytar_vs_hyfp->Fill(h_yfp, h_ytar);
      hytar_vs_hypfp->Fill(h_ypfp, h_ytar);
      
      hyptar_vs_hxfp->Fill(h_xfp, h_yptar);
      hyptar_vs_hxpfp->Fill(h_xpfp, h_yptar);
      hyptar_vs_hyfp->Fill(h_yfp, h_yptar);
      hyptar_vs_hypfp->Fill(h_ypfp, h_yptar);
      
      hxptar_vs_hxfp->Fill(h_xfp, h_xptar);
      hxptar_vs_hxpfp->Fill(h_xpfp, h_xptar);
      hxptar_vs_hyfp->Fill(h_yfp, h_xptar);
      hxptar_vs_hypfp->Fill(h_ypfp, h_xptar);
      
      hdelta_vs_hxfp->Fill(h_xfp, h_delta);
      hdelta_vs_hxpfp->Fill(h_xpfp, h_delta);
      hdelta_vs_hyfp->Fill(h_yfp, h_delta);
      hdelta_vs_hypfp->Fill(h_ypfp, h_delta);
      
      Q2_vs_thnq->Fill(th_nq/dtr, Q2, FullWeight);                                                                                                                  
      Q2_vs_Pm->Fill(Pm, Q2, FullWeight); 


      //Missing Energy Study                                                                                                                                                             
      if (c_hdelta&&c_edelta&&c_eSolid){                                                                                                                                                   
	pm_noemcut->Fill(Pm, FullWeight);                                                                                                                                                   
      }                                                                                                                                                                             
      if (c_hdelta&&c_edelta&&c_eSolid&&Em<0.03){                                                                                                                                          
        pm_em30cut->Fill(Pm, FullWeight);                                                                                                                                               
      }                                                                                                                                                                                             
      if (c_hdelta&&c_edelta&&c_eSolid&&Em<0.06){                                                                                                                                                      
        pm_em60cut->Fill(Pm, FullWeight);                                                                                                                                                           
      }                                                                                                                                                                                          
      if (c_hdelta&&c_edelta&&c_eSolid&&Em<0.09){                                                                                                                                                      
        pm_em90cut->Fill(Pm, FullWeight);                                                                                                                                                           
      } 
     
  } //end entry loop

  
  //Write to a ROOTfile
  outROOT->Write();

  
}



//Define Auxiliary Functions

  void GeoToSph( Double_t  th_geo, Double_t  ph_geo,
		 Double_t& th_sph, Double_t& ph_sph){

  // Convert geographical to spherical angles. Units are rad.

  static const Double_t twopi = 2.0*TMath::Pi();
  Double_t ct = cos(th_geo), cp = cos(ph_geo);
  Double_t tmp = ct*cp;
  th_sph = acos( tmp );
  tmp = sqrt(1.0 - tmp*tmp);
  ph_sph = (fabs(tmp) < 1e-6 ) ? 0.0 : acos( sqrt(1.0-ct*ct)*cp/tmp );
  if( th_geo/twopi-floor(th_geo/twopi) > 0.5 ) ph_sph = TMath::Pi() - ph_sph;
  if( ph_geo/twopi-floor(ph_geo/twopi) > 0.5 ) ph_sph = -ph_sph;
  }

  void SetCentralAngles(Double_t th_cent, Double_t ph_cent)
  {



    fThetaGeo = TMath::DegToRad()*th_cent; fPhiGeo = TMath::DegToRad()*ph_cent;
    GeoToSph( fThetaGeo, fPhiGeo, fThetaSph, fPhiSph );
    fSinThGeo = TMath::Sin( fThetaGeo ); fCosThGeo = TMath::Cos( fThetaGeo );
    fSinPhGeo = TMath::Sin( fPhiGeo );   fCosPhGeo = TMath::Cos( fPhiGeo );
    Double_t st, ct, sp, cp;
    st = fSinThSph = TMath::Sin( fThetaSph ); ct = fCosThSph = TMath::Cos( fThetaSph );
    sp = fSinPhSph = TMath::Sin( fPhiSph );   cp = fCosPhSph = TMath::Cos( fPhiSph );
    
    Double_t norm = TMath::Sqrt(ct*ct + st*st*cp*cp);
    TVector3 nx( st*st*sp*cp/norm, -norm, st*ct*sp/norm );
    TVector3 ny( ct/norm,          0.0,   -st*cp/norm   );
    TVector3 nz( st*cp,            st*sp, ct            );
    
    fToLabRot.SetToIdentity().RotateAxes( nx, ny, nz );
  }


void TransportToLab( Double_t p, Double_t xptar, Double_t yptar,
		     TVector3& pvect) 
{
  TVector3 v( xptar, yptar, 1.0 );
  v *= p/TMath::Sqrt( 1.0+xptar*xptar+yptar*yptar );
  pvect = fToLabRot * v;
}
