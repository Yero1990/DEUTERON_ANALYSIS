//Script to make comparison between SIMC and Commissioning Data from HallC Spring 2018
//Compare Target Reconstruction/FOCAL PLANE/ Kinematics Variables

void compare_deep_norm(int set, int pm, string model, string rad)
{

  gROOT->SetBatch(kTRUE);  
  gStyle->SetOptStat(1001111);
  //TString simc_filename =  "weighted_ep_coin_simc_1854.root"; //"ep_coin_simc_1929.root";
  
  //Pre-defined SIMC/data root file names containing histogram object to comapare
  TString simc_filename = "../deep_simc_histos_pm580_set1.root";

  //Data File
  TString data_filename = "../deep_data_histos_pm580_set1.root"; 

  TString simc_path;
  TString data_path;
  
  simc_path =  simc_filename;
  data_path = data_filename;
  
  //Open SIMC/data ROOT files;
  TFile *simc_file = new TFile(simc_path);
  TFile *data_file = new TFile(data_path);

  //---------------Target ----------------
  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  
  TH1F *simc_xtar =  0;
  TH1F *simc_ytarH =  0;
  TH1F *simc_ztarH =  0;

  TH1F *simc_ytarP =  0;                                                                                                                                     
  TH1F *simc_ztarP =  0; 

  //Define data histos
  TH1F *data_xtarH = 0;
  TH1F *data_ytarH = 0;
  TH1F *data_ztarH = 0;
  
  TH1F *data_xtarP = 0;
  TH1F *data_ytarP = 0;
  TH1F *data_ztarP = 0;
  


  //---------------Target Reconstruction Variables----------------
  //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *simc_eytar =  0;
  TH1F *simc_exptar =  0;
  TH1F *simc_eyptar =  0;
  TH1F *simc_edelta =  0;

  TH1F *simc_hytar =  0;
  TH1F *simc_hxptar =  0;
  TH1F *simc_hyptar =  0;
  TH1F *simc_hdelta =  0;

  //Define data histos
  TH1F *data_eytar = 0;
  TH1F *data_exptar =  0;
  TH1F *data_eyptar =  0;
  TH1F *data_edelta =  0;

  TH1F *data_hytar = 0;
  TH1F *data_hxptar =  0;
  TH1F *data_hyptar =  0;
  TH1F *data_hdelta =  0;

  //-----------------------------------------------------------
 
  //--------------FOCAL PLANE VARIABLES------------------------

 //Define SIMC histos ('h'-->hadron arm,  'e'-->electron arm)
  TH1F *simc_exfp =  0;
  TH1F *simc_eyfp =  0;
  TH1F *simc_expfp =  0;
  TH1F *simc_eypfp =  0;

  TH1F *simc_hxfp =  0;
  TH1F *simc_hyfp =  0;
  TH1F *simc_hxpfp =  0;
  TH1F *simc_hypfp =  0;
  
  //Define data histos
  TH1F *data_exfp =  0;
  TH1F *data_eyfp =  0;
  TH1F *data_expfp =  0;
  TH1F *data_eypfp =  0;

  TH1F *data_hxfp =  0;
  TH1F *data_hyfp =  0;
  TH1F *data_hxpfp =  0;
  TH1F *data_hypfp =  0;

  //--------------------------------------------------------------

  //-------------------------KINEMATICS---------------------------
  TH1F *simc_Q2 =  0;
  TH1F *simc_omega =  0;
  TH1F *simc_W2 =  0;
  TH1F *simc_thq = 0;

  TH1F *simc_xbj = 0;
  TH1F *simc_th_elec = 0;                                  
  TH1F *simc_kf = 0;  
  TH1F *simc_emiss = 0;

  //Kinematics 2
  TH1F *simc_Pm = 0;
  TH1F *simc_Pf = 0;
  TH1F *simc_th_prot = 0;
  TH1F *simc_q = 0;    //q-vector magnitude
  TH1F *simc_thpq = 0;
  TH1F *simc_thnq = 0;
  
  //Kinematics 3
  TH1F *simc_MM = 0;
  TH1F *simc_En = 0;
  TH1F *simc_Ep = 0;
  TH1F *simc_Kn = 0;
  TH1F *simc_Kp = 0;
  TH1F *simc_Pmx = 0;
  TH1F *simc_Pmy = 0;
  TH1F *simc_Pmz = 0;
  
  //Define data histos
  TH1F *data_Q2 =  0;
  TH1F *data_omega =  0;
  TH1F *data_W2 =  0;
  TH1F *data_thq = 0;

  TH1F *data_xbj = 0;
  TH1F *data_th_elec = 0;
  TH1F *data_kf = 0;
  TH1F *data_emiss = 0;

   //Kinematics 2
  TH1F *data_Pm = 0;
  TH1F *data_Pf = 0;
  TH1F *data_th_prot = 0;
  TH1F *data_q = 0;    //q-vector magnitude
  TH1F *data_thpq = 0;
  TH1F *data_thnq = 0;

  //Kinematics 3
  TH1F *data_MM = 0;
  TH1F *data_En = 0;
  TH1F *data_Ep = 0;
  TH1F *data_Kn = 0;
  TH1F *data_Kp = 0;
  TH1F *data_Pmx = 0;
  TH1F *data_Pmy = 0;
  TH1F *data_Pmz = 0;


  //DATA/SIMC Ratios
  TH1F *Pm_ratio;
  TH1F *th_nq_ratio;

  //---------------------------------------------------------------

 //change to simc_file
  simc_file->cd();

  
  //----------Get Target Histograms------------------
  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("H_hx_tar", simc_xtar);

  simc_file->GetObject("H_hy_tar", simc_ytarH);
  simc_file->GetObject("H_hz_tar", simc_ztarH);

  simc_file->GetObject("H_ey_tar", simc_ytarP);    
  simc_file->GetObject("H_ez_tar", simc_ztarP);   

  //Set SIMC Histo Aesthetics
  simc_xtar->SetFillColorAlpha(kRed, 0.35);
  simc_xtar->SetFillStyle(3004);
  simc_xtar->SetLineColor(kRed);

  simc_ytarH->SetFillColorAlpha(kRed, 0.35);
  simc_ytarH->SetFillStyle(3004);
  simc_ytarH->SetLineColor(kRed);

  simc_ztarH->SetFillColorAlpha(kRed, 0.35);
  simc_ztarH->SetFillStyle(3004);
  simc_ztarH->SetLineColor(kRed);

  simc_ytarP->SetFillColorAlpha(kRed, 0.35);          
  simc_ytarP->SetFillStyle(3004);                   
  simc_ytarP->SetLineColor(kRed);
  
  simc_ztarP->SetFillColorAlpha(kRed, 0.35);                                          
  simc_ztarP->SetFillStyle(3004); 
  simc_ztarP->SetLineColor(kRed);
  
  //change to data_file
  data_file->cd();

  //Get Histogram objects from data rootfile
  data_file->GetObject("H_hx_tar", data_xtarH);
  data_file->GetObject("H_hy_tar", data_ytarH);
  data_file->GetObject("H_hz_tar", data_ztarH);

  data_file->GetObject("H_ex_tar", data_xtarP);
  data_file->GetObject("H_ey_tar", data_ytarP);
  data_file->GetObject("H_ez_tar", data_ztarP);


    //Set data Histo Aesthetics
  data_xtarH->SetLineColor(kBlue);
  data_xtarH->SetLineWidth(2);
  data_ytarH->SetLineColor(kBlue);
  data_ytarH->SetLineWidth(2);
  data_ztarH->SetLineColor(kBlue);
  data_ztarH->SetLineWidth(2);


  data_xtarP->SetLineColor(kBlue);
  data_xtarP->SetLineWidth(2);
  data_ytarP->SetLineColor(kBlue);
  data_ytarP->SetLineWidth(2);
  data_ztarP->SetLineColor(kBlue);
  data_ztarP->SetLineWidth(2);

  //-----------------------------------------------------------------


  //---------------------------------------------------------------

 //change to simc_file
  simc_file->cd();

  //----------Get Target Reconstructed Histograms------------------
  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("H_eytar", simc_eytar);
  simc_file->GetObject("H_exptar", simc_exptar);
  simc_file->GetObject("H_eyptar", simc_eyptar);
  simc_file->GetObject("H_edelta", simc_edelta);

  simc_file->GetObject("H_hytar", simc_hytar);
  simc_file->GetObject("H_hxptar", simc_hxptar);
  simc_file->GetObject("H_hyptar", simc_hyptar);
  simc_file->GetObject("H_hdelta", simc_hdelta);

  //Set SIMC Histo Aesthetics
  simc_eytar->SetFillColorAlpha(kRed, 0.35);
  simc_eytar->SetFillStyle(3004);
  simc_eytar->SetLineColor(kRed);
  
  simc_exptar->SetFillColorAlpha(kRed, 0.35);
  simc_exptar->SetFillStyle(3004);
  simc_exptar->SetLineColor(kRed);
    
  simc_eyptar->SetFillColorAlpha(kRed, 0.35);
  simc_eyptar->SetFillStyle(3004);
  simc_eyptar->SetLineColor(kRed);

  simc_edelta->SetFillColorAlpha(kRed, 0.35);
  simc_edelta->SetFillStyle(3004);
  simc_edelta->SetLineColor(kRed);

  simc_hytar->SetFillColorAlpha(kRed, 0.35);
  simc_hytar->SetFillStyle(3004);
  simc_hytar->SetLineColor(kRed);

  simc_hxptar->SetFillColorAlpha(kRed, 0.35);
  simc_hxptar->SetFillStyle(3004);
  simc_hxptar->SetLineColor(kRed);

  simc_hyptar->SetFillColorAlpha(kRed, 0.35);
  simc_hyptar->SetFillStyle(3004);
  simc_hyptar->SetLineColor(kRed);

  simc_hdelta->SetFillColorAlpha(kRed, 0.35);
  simc_hdelta->SetFillStyle(3004);
  simc_hdelta->SetLineColor(kRed);

  //change to data_file
  data_file->cd();

  //Get Histogram objects from data rootfile
  data_file->GetObject("H_eytar", data_eytar);
  data_file->GetObject("H_exptar", data_exptar);
  data_file->GetObject("H_eyptar", data_eyptar);
  data_file->GetObject("H_edelta", data_edelta);
  
  data_file->GetObject("H_hytar", data_hytar);
  data_file->GetObject("H_hxptar", data_hxptar);
  data_file->GetObject("H_hyptar", data_hyptar);
  data_file->GetObject("H_hdelta", data_hdelta);

  //Set data Histo Aesthetics
  data_eytar->SetLineColor(kBlue);
  data_eytar->SetLineWidth(2);
  data_exptar->SetLineColor(kBlue);
  data_exptar->SetLineWidth(2);
  data_eyptar->SetLineColor(kBlue);
  data_eyptar->SetLineWidth(2);
  data_edelta->SetLineColor(kBlue);
  data_edelta->SetLineWidth(2);

  data_hytar->SetLineColor(kBlue);
  data_hytar->SetLineWidth(2);
  data_hxptar->SetLineColor(kBlue);
  data_hxptar->SetLineWidth(2);
  data_hyptar->SetLineColor(kBlue);
  data_hyptar->SetLineWidth(2);
  data_hdelta->SetLineColor(kBlue);
  data_hdelta->SetLineWidth(2);

  //-----------------------------------------------------------------

  

  //---------------Get FOCAL PLANE Histograms------------------------

   //change to simc_file
  simc_file->cd();

  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("H_exfp", simc_exfp);
  simc_file->GetObject("H_eyfp", simc_eyfp);
  simc_file->GetObject("H_expfp", simc_expfp);
  simc_file->GetObject("H_eypfp", simc_eypfp);

  simc_file->GetObject("H_hxfp", simc_hxfp);
  simc_file->GetObject("H_hyfp", simc_hyfp);
  simc_file->GetObject("H_hxpfp", simc_hxpfp);
  simc_file->GetObject("H_hypfp", simc_hypfp);
  //Set SIMC Histo Aesthetics
  simc_exfp->SetFillColorAlpha(kRed, 0.35);
  simc_exfp->SetFillStyle(3004);
  simc_exfp->SetLineColor(kRed);
  
  simc_eyfp->SetFillColorAlpha(kRed, 0.35);
  simc_eyfp->SetFillStyle(3004);
  simc_eyfp->SetLineColor(kRed);
  
  simc_expfp->SetFillColorAlpha(kRed, 0.35);
  simc_expfp->SetFillStyle(3004);
  simc_expfp->SetLineColor(kRed);

  simc_eypfp->SetFillColorAlpha(kRed, 0.35);
  simc_eypfp->SetFillStyle(3004);
  simc_eypfp->SetLineColor(kRed);

  simc_hxfp->SetFillColorAlpha(kRed, 0.35);
  simc_hxfp->SetFillStyle(3004);
  simc_hxfp->SetLineColor(kRed);

  simc_hyfp->SetFillColorAlpha(kRed, 0.35);
  simc_hyfp->SetFillStyle(3004);
  simc_hyfp->SetLineColor(kRed);

  simc_hxpfp->SetFillColorAlpha(kRed, 0.35);
  simc_hxpfp->SetFillStyle(3004);
  simc_hxpfp->SetLineColor(kRed);

  simc_hypfp->SetFillColorAlpha(kRed, 0.35);
  simc_hypfp->SetFillStyle(3004);
  simc_hypfp->SetLineColor(kRed);

  //change to data_file
  data_file->cd();

  //Get Histogram objects from data rootfile
  data_file->GetObject("H_exfp", data_exfp);
  data_file->GetObject("H_eyfp", data_eyfp);
  data_file->GetObject("H_expfp", data_expfp);
  data_file->GetObject("H_eypfp", data_eypfp);

  data_file->GetObject("H_hxfp", data_hxfp);
  data_file->GetObject("H_hyfp", data_hyfp);
  data_file->GetObject("H_hxpfp", data_hxpfp);
  data_file->GetObject("H_hypfp", data_hypfp);
  //Set data Histo Aesthetics
  data_exfp->SetLineColor(kBlue);
  data_exfp->SetLineWidth(2);
  data_eyfp->SetLineColor(kBlue);
  data_eyfp->SetLineWidth(2);
  data_expfp->SetLineColor(kBlue);
  data_expfp->SetLineWidth(2);
  data_eypfp->SetLineColor(kBlue);
  data_eypfp->SetLineWidth(2);

  data_hxfp->SetLineColor(kBlue);
  data_hxfp->SetLineWidth(2);
  data_hyfp->SetLineColor(kBlue);
  data_hyfp->SetLineWidth(2);
  data_hxpfp->SetLineColor(kBlue);
  data_hxpfp->SetLineWidth(2);
  data_hypfp->SetLineColor(kBlue);
  data_hypfp->SetLineWidth(2);

  //--------------------------------------------------------------
  
  //------------------Get KINEMATICS VARIABLES--------------------

   //change to simc_file
  simc_file->cd();

  //Get Histogram objects from SIMC rootfile
  simc_file->GetObject("H_Q2", simc_Q2);
  simc_file->GetObject("H_omega", simc_omega);
  simc_file->GetObject("H_W2", simc_W2);
  simc_file->GetObject("H_theta_q", simc_thq);

  simc_file->GetObject("H_xbj", simc_xbj);
  simc_file->GetObject("H_theta_elec", simc_th_elec);
  simc_file->GetObject("H_kf", simc_kf);
  simc_file->GetObject("H_Emiss", simc_emiss);

  simc_file->GetObject("H_Pm", simc_Pm);
  simc_file->GetObject("H_Pf", simc_Pf);
  simc_file->GetObject("H_theta_prot", simc_th_prot);
  simc_file->GetObject("H_q", simc_q);
  simc_file->GetObject("H_theta_pq", simc_thpq);
  simc_file->GetObject("H_theta_nq", simc_thnq);
  
  simc_file->GetObject("H_MM", simc_MM);
  simc_file->GetObject("H_En", simc_En);
  simc_file->GetObject("H_Ep", simc_Ep);
  simc_file->GetObject("H_Kn", simc_Kn);
  simc_file->GetObject("H_Kp", simc_Kp);
  simc_file->GetObject("H_Pmx_Lab", simc_Pmx);
  simc_file->GetObject("H_Pmy_Lab", simc_Pmy);
  simc_file->GetObject("H_Pmz_Lab", simc_Pmz);

  //Set SIMC Histo Aesthetics
  simc_Q2->SetFillColorAlpha(kRed, 0.35);
  simc_Q2->SetFillStyle(3004);
  simc_Q2->SetLineColor(kRed);
  
  simc_omega->SetFillColorAlpha(kRed, 0.35);
  simc_omega->SetFillStyle(3004);
  simc_omega->SetLineColor(kRed);
  
  simc_W2->SetFillColorAlpha(kRed, 0.35);
  simc_W2->SetFillStyle(3004);
  simc_W2->SetLineColor(kRed);

  simc_thq->SetFillColorAlpha(kRed, 0.35);
  simc_thq->SetFillStyle(3004);
  simc_thq->SetLineColor(kRed);

  simc_xbj->SetFillColorAlpha(kRed, 0.35);
  simc_xbj->SetFillStyle(3004);
  simc_xbj->SetLineColor(kRed);

  simc_th_elec->SetFillColorAlpha(kRed, 0.35);
  simc_th_elec->SetFillStyle(3004);
  simc_th_elec->SetLineColor(kRed);

  simc_kf->SetFillColorAlpha(kRed, 0.35);
  simc_kf->SetFillStyle(3004);
  simc_kf->SetLineColor(kRed);
    
  simc_emiss->SetFillColorAlpha(kRed, 0.35);
  simc_emiss->SetFillStyle(3004);
  simc_emiss->SetLineColor(kRed);

  simc_Pm->SetFillColorAlpha(kRed, 0.35);
  simc_Pm->SetFillStyle(3004);
  simc_Pm->SetLineColor(kRed);

  simc_Pf->SetFillColorAlpha(kRed, 0.35);
  simc_Pf->SetFillStyle(3004);
  simc_Pf->SetLineColor(kRed);

  simc_th_prot->SetFillColorAlpha(kRed, 0.35);
  simc_th_prot->SetFillStyle(3004);
  simc_th_prot->SetLineColor(kRed);

  simc_q->SetFillColorAlpha(kRed, 0.35);
  simc_q->SetFillStyle(3004);
  simc_q->SetLineColor(kRed);

  simc_thpq->SetFillColorAlpha(kRed, 0.35);
  simc_thpq->SetFillStyle(3004);
  simc_thpq->SetLineColor(kRed);

  simc_thnq->SetFillColorAlpha(kRed, 0.35);
  simc_thnq->SetFillStyle(3004);
  simc_thnq->SetLineColor(kRed);

  simc_MM->SetFillColorAlpha(kRed, 0.35);
  simc_MM->SetFillStyle(3004);
  simc_MM->SetLineColor(kRed);

  simc_En->SetFillColorAlpha(kRed, 0.35);
  simc_En->SetFillStyle(3004);
  simc_En->SetLineColor(kRed);

  simc_Ep->SetFillColorAlpha(kRed, 0.35);
  simc_Ep->SetFillStyle(3004);
  simc_Ep->SetLineColor(kRed);

  simc_Kn->SetFillColorAlpha(kRed, 0.35);
  simc_Kn->SetFillStyle(3004);
  simc_Kn->SetLineColor(kRed);

  simc_Kp->SetFillColorAlpha(kRed, 0.35);
  simc_Kp->SetFillStyle(3004);
  simc_Kp->SetLineColor(kRed);

  simc_Pmx->SetFillColorAlpha(kRed, 0.35);
  simc_Pmx->SetFillStyle(3004);
  simc_Pmx->SetLineColor(kRed);

  simc_Pmy->SetFillColorAlpha(kRed, 0.35);
  simc_Pmy->SetFillStyle(3004);
  simc_Pmy->SetLineColor(kRed);

  simc_Pmz->SetFillColorAlpha(kRed, 0.35);
  simc_Pmz->SetFillStyle(3004);
  simc_Pmz->SetLineColor(kRed);

  //change to data_file
  data_file->cd();
  
  //Get Histogram objects from data rootfile
  data_file->GetObject("H_Q2", data_Q2);
  data_file->GetObject("H_omega", data_omega);
  data_file->GetObject("H_W2", data_W2);
  data_file->GetObject("H_theta_q", data_thq);

  
  data_file->GetObject("H_xbj", data_xbj);
  data_file->GetObject("H_theta_elec", data_th_elec);
  data_file->GetObject("H_kf", data_kf);
  data_file->GetObject("H_Em_nuc", data_emiss);

  data_file->GetObject("H_Pm", data_Pm);
  data_file->GetObject("H_Pf", data_Pf);
  data_file->GetObject("H_theta_prot", data_th_prot);
  data_file->GetObject("H_q", data_q);
  data_file->GetObject("H_theta_pq", data_thpq);
  data_file->GetObject("H_theta_nq", data_thnq);

  data_file->GetObject("H_MM", data_MM);
  data_file->GetObject("H_En", data_En);
  data_file->GetObject("H_Ep", data_Ep);
  data_file->GetObject("H_Kn", data_Kn);
  data_file->GetObject("H_Kp", data_Kp);
  data_file->GetObject("H_Pmx_Lab", data_Pmx);
  data_file->GetObject("H_Pmy_Lab", data_Pmy);
  data_file->GetObject("H_Pmz_Lab", data_Pmz);

  //Set data Histo Aesthetics
  data_Q2->SetLineColor(kBlue);
  data_Q2->SetLineWidth(2);
  data_omega->SetLineColor(kBlue);
  data_omega->SetLineWidth(2);
  data_W2->SetLineColor(kBlue);
  data_W2->SetLineWidth(2);
  data_thq->SetLineColor(kBlue);
  data_thq->SetLineWidth(2);

  data_xbj->SetLineColor(kBlue);
  data_xbj->SetLineWidth(2);
  data_th_elec->SetLineColor(kBlue);
  data_th_elec->SetLineWidth(2);
  data_kf->SetLineColor(kBlue);
  data_kf->SetLineWidth(2);
  data_emiss->SetLineColor(kBlue);
  data_emiss->SetLineWidth(2);

  data_Pm->SetLineColor(kBlue);
  data_Pm->SetLineWidth(2);
  data_Pf->SetLineColor(kBlue);
  data_Pf->SetLineWidth(2);
  data_th_prot->SetLineColor(kBlue);
  data_th_prot->SetLineWidth(2);
  data_q->SetLineColor(kBlue);
  data_q->SetLineWidth(2);
  data_thpq->SetLineColor(kBlue);
  data_thpq->SetLineWidth(2);
  data_thnq->SetLineColor(kBlue);
  data_thnq->SetLineWidth(2);

  data_MM->SetLineColor(kBlue);
  data_MM->SetLineWidth(2);
  data_En->SetLineColor(kBlue);
  data_En->SetLineWidth(2);
  data_Ep->SetLineColor(kBlue);
  data_Ep->SetLineWidth(2);
  data_Kn->SetLineColor(kBlue);
  data_Kn->SetLineWidth(2);
  data_Kp->SetLineColor(kBlue);
  data_Kp->SetLineWidth(2);
  data_Pmx->SetLineColor(kBlue);
  data_Pmx->SetLineWidth(2);
  data_Pmy->SetLineColor(kBlue);
  data_Pmy->SetLineWidth(2);
  data_Pmz->SetLineColor(kBlue);
  data_Pmz->SetLineWidth(2);

  //Overlay SIMC/data plots (*** VERY IMPORTANT ***: Range and #bins must be same)


   //Set Legend
   auto leg5 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg6 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg7 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg8 = new TLegend(0.1,0.8,0.28,0.9);

  
   //-----------------PLOT Target Reconstructed Variables SIMC/Data comparison-----------------------

   //Create A Canvas to store Target Recon. variable comparisons in HADRON ARM
   
   TCanvas *c1 = new TCanvas("c1", "Electron Arm: Target Reconstruction", 5000, 3000);
   c1->Divide(2,2);

   c1->cd(1);
   simc_eytar->DrawNormalized("histE0");
   data_eytar->DrawNormalized("samesE0");
   leg5->AddEntry(data_eytar,"Data","f");
   leg5->AddEntry(simc_eytar,"SIMC");
   leg5->Draw();

   c1->cd(2);
   simc_exptar->DrawNormalized("histE0");
   data_exptar->DrawNormalized("samesE0");
   leg5->AddEntry(data_exptar,"Data", "f");
   leg5->AddEntry(simc_exptar,"SIMC");
   leg5->Draw();

   c1->cd(3);
   simc_eyptar->DrawNormalized("histE0");
   data_eyptar->DrawNormalized("samesE0");
   leg7->AddEntry(data_eyptar,"Data", "f");
   leg7->AddEntry(simc_eyptar,"SIMC");
   leg7->Draw();
     
   c1->cd(4);
   simc_edelta->DrawNormalized("histE0");
   data_edelta->DrawNormalized("samesE0");
   leg8->AddEntry(data_edelta,"Data", "f");
   leg8->AddEntry(simc_edelta,"SIMC");
   leg8->Draw();

   c1->SaveAs(Form("eArm_TargRecon_pm%d_set%d.pdf", pm, set));

   //------------------------------------------------------------------------------

   
   //-----------------PLOT FOCAL PLANE  Variables SIMC/Data comparison-----------------------

  //Set Legend
   auto leg9 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg10 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg11 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg12 = new TLegend(0.1,0.8,0.28,0.9);

      //Set Legend
   auto leg13 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg14 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg15 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg16 = new TLegend(0.1,0.8,0.28,0.9);

   TCanvas *c2 = new TCanvas("c2", "Electron Arm: Focal Plane", 5000, 3000);
   c2->Divide(2,2);

   c2->cd(1);
   simc_exfp->DrawNormalized("histE0");
   data_exfp->DrawNormalized("samesE0");
   leg13->AddEntry(data_exfp,"Data","f");
   leg13->AddEntry(simc_exfp,"SIMC");
   leg13->Draw();
   
   c2->cd(2);
   simc_eyfp->DrawNormalized("histE0");
   data_eyfp->DrawNormalized("samesE0");
   leg14->AddEntry(data_eyfp,"Data", "f");
   leg14->AddEntry(simc_eyfp,"SIMC");
   leg14->Draw();

   c2->cd(3);
   simc_expfp->DrawNormalized("histE0");
   data_expfp->DrawNormalized("samesE0");
   leg15->AddEntry(data_expfp,"Data", "f");
   leg15->AddEntry(simc_expfp,"SIMC");
   leg15->Draw();
     
   c2->cd(4);
   simc_eypfp->DrawNormalized("histE0");
   data_eypfp->DrawNormalized("samesE0");
   leg16->AddEntry(data_eypfp,"Data", "f");
   leg16->AddEntry(simc_eypfp,"SIMC");
   leg16->Draw();

   c2->SaveAs(Form("eArm_FocalPlane_pm%d_set%d.pdf", pm, set));                                                                                   

   //----------------------------------------------------------- 
 
   
   //-----------------PLOT KINEMATICS SIMC/Data comparison---------------

   //Kinematics 1:  Missing Varibales
   auto leg_em = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_MM = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Pm = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Pmx = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Pmy = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Pmz = new TLegend(0.1,0.8,0.28,0.9);


   TCanvas *ck1 = new TCanvas("ck1", "Kinematics1", 5000, 3000);
   ck1->Divide(3,2);
   ck1->cd(1);
   simc_emiss->DrawNormalized("histE0");
   data_emiss->DrawNormalized("samesE0");
   data_emiss->GetXaxis()->SetTitle("Missing Energy, E_{m} [GeV] ");
   data_emiss->GetXaxis()->CenterTitle();      
   leg_em->AddEntry(data_emiss,"Data","f");
   leg_em->AddEntry(simc_emiss,"SIMC");
   leg_em->Draw();
   
   ck1->cd(2);
   data_MM->GetXaxis()->SetTitle("Missing Mass, M_{miss} [GeV]");
   data_MM->GetXaxis()->CenterTitle();
   simc_MM->DrawNormalized("histE0");
   data_MM->DrawNormalized("samesE0");
   leg_MM->AddEntry(data_MM,"Data", "f");
   leg_MM->AddEntry(simc_MM,"SIMC");
   leg_MM->Draw();

   ck1->cd(3);
   data_Pm->GetXaxis()->SetTitle("Missing Momentum, P_{miss} [GeV]");
   data_Pm->GetXaxis()->CenterTitle();
   simc_Pm->DrawNormalized("histE0");
   data_Pm->DrawNormalized("samesE0");
   leg_Pm->AddEntry(data_Pm,"Data", "f");
   leg_Pm->AddEntry(simc_Pm,"SIMC");
   leg_Pm->Draw();

   ck1->cd(4);
   data_Pmx->GetXaxis()->SetTitle("Missing Momentum X-comp., Pm_{x} [GeV]");
   data_Pmx->GetXaxis()->CenterTitle();
   simc_Pmx->DrawNormalized("histE0");
   data_Pmx->DrawNormalized("samesE0");
   leg_Pmx->AddEntry(data_Pmx,"Data", "f");
   leg_Pmx->AddEntry(simc_Pmx,"SIMC");
   leg_Pmx->Draw();
   
   ck1->cd(5);
   data_Pmy->GetXaxis()->SetTitle("Missing Momentum Y-comp., Pm_{y} [GeV]");
   data_Pmy->GetXaxis()->CenterTitle();
   simc_Pmy->DrawNormalized("histE0");
   data_Pmy->DrawNormalized("samesE0");
   leg_Pmy->AddEntry(data_Pmy,"Data", "f");
   leg_Pmy->AddEntry(simc_Pmy,"SIMC");
   leg_Pmy->Draw();

   ck1->cd(6);
   data_Pmz->GetXaxis()->SetTitle("Missing Momentum Z-comp., Pm_{z} [GeV]");
   data_Pmz->GetXaxis()->CenterTitle();
   simc_Pmz->DrawNormalized("histE0");
   data_Pmz->DrawNormalized("samesE0");
   leg_Pmz->AddEntry(data_Pmz,"Data", "f");
   leg_Pmz->AddEntry(simc_Pmz,"SIMC");
   leg_Pmz->Draw();

   ck1->SaveAs(Form("Kinematics1_pm%d_set%d.pdf", pm, set));                                                                   


   //Kinematics 2:  Electron Kinematics

   //Set Legend
   auto leg_Q2 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_om = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_xbj = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_W2 = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_the = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_kf = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_thq = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_q = new TLegend(0.1,0.8,0.28,0.9);


   TCanvas *ck2 = new TCanvas("ck2", "Kinematics2", 5000, 3000);
   ck2->Divide(4,2);
   
   ck2->cd(1);
   data_Q2->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
   data_Q2->GetXaxis()->CenterTitle();
   simc_Q2->DrawNormalized("histE0");
   data_Q2->DrawNormalized("samesE0");
   leg_Q2->AddEntry(data_Q2,"Data", "f");
   leg_Q2->AddEntry(simc_Q2,"SIMC");
   leg_Q2->Draw();
     
   ck2->cd(2);
   data_omega->GetXaxis()->SetTitle("Energy Transfer, #omega [GeV]");
   data_omega->GetXaxis()->CenterTitle();  
   simc_omega->DrawNormalized("histE0");
   data_omega->DrawNormalized("samesE0");
   leg_om->AddEntry(data_omega,"Data", "f");
   leg_om->AddEntry(simc_omega,"SIMC");
   leg_om->Draw();
   
   ck2->cd(3);
   data_xbj->GetXaxis()->SetTitle("BjorkenX,  X_{bj} ");
   data_xbj->GetXaxis()->CenterTitle();
   simc_xbj->DrawNormalized("histE0");
   data_xbj->DrawNormalized("samesE0");
   leg_xbj->AddEntry(data_xbj,"Data","f");
   leg_xbj->AddEntry(simc_xbj,"SIMC");
   leg_xbj->Draw();

   ck2->cd(4);
   data_W2->GetXaxis()->SetTitle("Invariant Mass , W2 [GeV]");
   data_W2->GetXaxis()->CenterTitle();
   simc_W2->DrawNormalized("histE0");
   data_W2->DrawNormalized("samesE0");
   leg_W2->AddEntry(data_W2,"Data", "f");
   leg_W2->AddEntry(simc_W2,"SIMC");
   leg_W2->Draw();
   
   ck2->cd(5);
   data_th_elec->GetXaxis()->SetTitle("Electron Scatt. Angle, #theta_{e} [deg]");
   data_th_elec->GetXaxis()->CenterTitle();
   simc_th_elec->DrawNormalized("histE0");
   data_th_elec->DrawNormalized("samesE0");
   leg_the->AddEntry(data_th_elec,"Data","f");
   leg_the->AddEntry(simc_th_elec,"SIMC");
   leg_the->Draw();
   
   ck2->cd(6);
   data_kf->GetXaxis()->SetTitle("Electron Final Momentum, k_{f} [GeV/c] ");
   data_kf->GetXaxis()->CenterTitle();   
   simc_kf->DrawNormalized("histE0");
   data_kf->DrawNormalized("samesE0");
   leg_kf->AddEntry(data_kf,"Data","f");
   leg_kf->AddEntry(simc_kf,"SIMC");
   leg_kf->Draw();

   ck2->cd(7);
   data_thq->GetXaxis()->SetTitle("q-vector Angle, #theta_{q} [deg]");
   data_thq->GetXaxis()->CenterTitle();
   simc_thq->DrawNormalized("histE0");
   data_thq->DrawNormalized("samesE0");
   leg_thq->AddEntry(data_thq,"Data", "f");
   leg_thq->AddEntry(simc_thq,"SIMC");
   leg_thq->Draw();

   ck2->cd(8);
   data_q->GetXaxis()->SetTitle("q-Vector Magnitude, |q| [GeV]");
   data_q->GetXaxis()->CenterTitle();
   simc_q->DrawNormalized("histE0");
   data_q->DrawNormalized("samesE0");
   leg_q->AddEntry(data_q,"Data", "f");
   leg_q->AddEntry(simc_q,"SIMC");
   leg_q->Draw();

   ck2->SaveAs(Form("Kinematics2_pm%d_set%d.pdf", pm, set));                                                                   


   
   //Kinematics 3: Proton Kinematics
   
   auto leg_Pf = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_thp = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Kp = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Ep = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_Kn = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_En = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_thpq = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_thnq = new TLegend(0.1,0.8,0.28,0.9);


   //Create A Canvas to store kinematic variable comparisons
   TCanvas *ck3 = new TCanvas("ck3", "Kinematics3", 5000, 3000);
   
   ck3->Divide(4,2);
 
   ck3->cd(1);
   data_Pf->GetXaxis()->SetTitle("Proton Momentum, P_{p} [GeV]");
   data_Pf->GetXaxis()->CenterTitle();
   simc_Pf->DrawNormalized("histE0");
   data_Pf->DrawNormalized("samesE0");
   leg_Pf->AddEntry(data_Pf,"Data", "f");
   leg_Pf->AddEntry(simc_Pf,"SIMC");
   leg_Pf->Draw();

   ck3->cd(2);
   data_th_prot->GetXaxis()->SetTitle("Proton Scatt. Angle, #theta_{p} [deg]");
   data_th_prot->GetXaxis()->CenterTitle();
   simc_th_prot->DrawNormalized("histE0");
   data_th_prot->DrawNormalized("samesE0");
   leg_thp->AddEntry(data_th_prot,"Data", "f");
   leg_thp->AddEntry(simc_th_prot,"SIMC");
   leg_thp->Draw();

   ck3->cd(3);
   data_Kp->GetXaxis()->SetTitle("Proton Kin. Energy, K_{p} [GeV]");
   data_Kp->GetXaxis()->CenterTitle();
   simc_Kp->DrawNormalized("histE0");
   data_Kp->DrawNormalized("samesE0");
   leg_Kp->AddEntry(data_Kp,"Data", "f");
   leg_Kp->AddEntry(simc_Kp,"SIMC");
   leg_Kp->Draw();

   ck3->cd(4);
   data_Ep->GetXaxis()->SetTitle("Proton Energy, E_{p} [GeV]");
   data_Ep->GetXaxis()->CenterTitle();
   simc_Ep->DrawNormalized("histE0");
   data_Ep->DrawNormalized("samesE0");
   leg_Ep->AddEntry(data_Ep,"Data", "f");
   leg_Ep->AddEntry(simc_Ep,"SIMC");
   leg_Ep->Draw();

   ck3->cd(5);
   data_Kn->GetXaxis()->SetTitle("Neutron Kin. Energy, K_{n} [GeV]");
   data_Kn->GetXaxis()->CenterTitle();
   simc_Kn->DrawNormalized("histE0");
   data_Kn->DrawNormalized("samesE0");
   leg_Kn->AddEntry(data_Kn,"Data", "f");
   leg_Kn->AddEntry(simc_Kn,"SIMC");
   leg_Kn->Draw();

   ck3->cd(6);
   data_En->GetXaxis()->SetTitle("Neutron Energy, E_{n} [GeV]");
   data_En->GetXaxis()->CenterTitle();
   simc_En->DrawNormalized("histE0");
   data_En->DrawNormalized("samesE0");
   leg_En->AddEntry(data_En,"Data", "f");
   leg_En->AddEntry(simc_En,"SIMC");
   leg_En->Draw();


   ck3->cd(7);
   data_thpq->GetXaxis()->SetTitle("(Proton, qVec.) Angle, #theta_{pq} [deg]");
   data_thpq->GetXaxis()->CenterTitle();
   simc_thpq->DrawNormalized("histE0");
   data_thpq->DrawNormalized("samesE0");
   leg_thpq->AddEntry(data_thpq,"Data", "f");
   leg_thpq->AddEntry(simc_thpq,"SIMC");
   leg_thpq->Draw();

   ck3->cd(8);
   data_thnq->GetXaxis()->SetTitle("(Neutron, qVec.) Angle, #theta_{nq} [deg]");
   data_thnq->GetXaxis()->CenterTitle();
   simc_thnq->DrawNormalized("histE0");
   data_thnq->DrawNormalized("samesE0");
   leg_thnq->AddEntry(data_thnq,"Data", "f");
   leg_thnq->AddEntry(simc_thnq,"SIMC");
   leg_thnq->Draw();

   ck3->SaveAs(Form("Kinematics3_pm%d_set%d.pdf", pm, set));                                                                   
                                                               

 //-----------------PLOT TARGET  Variables SIMC/Data comparison-----------------------

  //Set Legend
   auto leghxt = new TLegend(0.1,0.8,0.28,0.9);
   auto leghyt = new TLegend(0.1,0.8,0.28,0.9);
   auto leghzt = new TLegend(0.1,0.8,0.28,0.9);
   
   auto legpxt = new TLegend(0.1,0.8,0.28,0.9);
   auto legpyt = new TLegend(0.1,0.8,0.28,0.9);
   auto legpzt = new TLegend(0.1,0.8,0.28,0.9);


   TCanvas *c4a = new TCanvas("c4a", "HMS Target Variables", 5000, 3000);
   c4a->Divide(3,1);

   c4a->cd(1);
   simc_xtar->DrawNormalized("histE0");
   data_xtarH->DrawNormalized("samesE0");
   leghxt->AddEntry(data_xtarH,"Data","f");
   leghxt->AddEntry(simc_xtar,"SIMC");
   leghxt->Draw();
  
   c4a->cd(2);
   simc_ytarH->DrawNormalized("histE0");
   data_ytarH->DrawNormalized("samesE0");
   leghyt->AddEntry(data_ytarH,"Data","f");
   leghyt->AddEntry(simc_ytarH,"SIMC");
   leghyt->Draw();

   c4a->cd(3);
   simc_ztarH->DrawNormalized("histE0");
   data_ztarH->DrawNormalized("samesE0");
   leghzt->AddEntry(data_ztarH,"Data","f");
   leghzt->AddEntry(simc_ztarH,"SIMC");
   leghzt->Draw();
  
   c4a->SaveAs(Form("hArm_TargVar_pm%d_set%d.pdf", pm, set));                                                                                              

   TCanvas *c4b = new TCanvas("c4b", "SHMS Target Variables", 5000, 3000);
   c4b->Divide(3,1);

   c4b->cd(1);
   simc_xtar->DrawNormalized("histE0");
   data_xtarP->DrawNormalized("samesE0");
   legpxt->AddEntry(data_xtarP,"Data","f");
   legpxt->AddEntry(simc_xtar,"SIMC");
   legpxt->Draw();
  
   c4b->cd(2);
   simc_ytarP->DrawNormalized("histE0");
   data_ytarP->DrawNormalized("samesE0");
   legpyt->AddEntry(data_ytarP,"Data","f");
   legpyt->AddEntry(simc_ytarP,"SIMC");
   legpyt->Draw();

   c4b->cd(3);
   simc_ztarP->DrawNormalized("histE0");
   data_ztarP->DrawNormalized("samesE0");
   legpzt->AddEntry(data_ztarP,"Data","f");
   legpzt->AddEntry(simc_ztarP,"SIMC");
   legpzt->Draw();
  
   c4b->SaveAs(Form("pArm_TargVar_pm%d_set%d.pdf", pm, set));      
   //--------PLOT HADRON ARM QUANTITIES--------


   
   //-----------------PLOT Target Reconstructed Variables SIMC/Data comparison-----------------------
 
   //Set Legend
   auto htr_l1 = new TLegend(0.1,0.8,0.28,0.9);
   auto htr_l2 = new TLegend(0.1,0.8,0.28,0.9);
   auto htr_l3 = new TLegend(0.1,0.8,0.28,0.9);
   auto htr_l4 = new TLegend(0.1,0.8,0.28,0.9);
   
   //Create A Canvas to store Target Recon. variable comparisons in HADRON ARM
   
   TCanvas *htr = new TCanvas("htr", "Hadron Arm: Target Reconstruction", 5000, 3000);
   htr->Divide(2,2);

   htr->cd(1);
   simc_hytar->DrawNormalized("histE0");
   data_hytar->DrawNormalized("samesE0");
   htr_l1->AddEntry(data_hytar,"Data","f");
   htr_l1->AddEntry(simc_hytar,"SIMC");
   htr_l1->Draw();

   htr->cd(2);
   simc_hxptar->DrawNormalized("histE0");
   data_hxptar->DrawNormalized("samesE0");
   htr_l2->AddEntry(data_hxptar,"Data", "f");
   htr_l2->AddEntry(simc_hxptar,"SIMC");
   htr_l2->Draw();

   htr->cd(3);
   simc_hyptar->DrawNormalized("histE0");
   data_hyptar->DrawNormalized("samesE0");
   htr_l3->AddEntry(data_hyptar,"Data", "f");
   htr_l3->AddEntry(simc_hyptar,"SIMC");
   htr_l3->Draw();
     
   htr->cd(4);
   simc_hdelta->DrawNormalized("histE0");
   data_hdelta->DrawNormalized("samesE0");
   htr_l4->AddEntry(data_hdelta,"Data", "f");
   htr_l4->AddEntry(simc_hdelta,"SIMC");
   htr_l4->Draw();

   htr->SaveAs(Form("hArm_TargRecon_pm%d_set%d.pdf", pm, set));

   //------------------------------------------------------------------------------

   
   //-----------------PLOT FOCAL PLANE  Variables SIMC/Data comparison-----------------------

   //Set Legend
   auto hfp_l1 = new TLegend(0.1,0.8,0.28,0.9);
   auto hfp_l2 = new TLegend(0.1,0.8,0.28,0.9);
   auto hfp_l3 = new TLegend(0.1,0.8,0.28,0.9);
   auto hfp_l4 = new TLegend(0.1,0.8,0.28,0.9);

   TCanvas *hfp = new TCanvas("hfp", "Hadron Arm: Focal Plane", 5000, 3000);
   hfp->Divide(2,2);

   hfp->cd(1);
   simc_hxfp->DrawNormalized("histE0");
   data_hxfp->DrawNormalized("samesE0");
   hfp_l1->AddEntry(data_hxfp,"Data","f");
   hfp_l1->AddEntry(simc_hxfp,"SIMC");
   hfp_l1->Draw();
   
   hfp->cd(2);
   simc_hyfp->DrawNormalized("histE0");
   data_hyfp->DrawNormalized("samesE0");
   hfp_l2->AddEntry(data_hyfp,"Data", "f");
   hfp_l2->AddEntry(simc_hyfp,"SIMC");
   hfp_l2->Draw();

   hfp->cd(3);
   simc_hxpfp->DrawNormalized("histE0");
   data_hxpfp->DrawNormalized("samesE0");
   hfp_l3->AddEntry(data_hxpfp,"Data", "f");
   hfp_l3->AddEntry(simc_hxpfp,"SIMC");
   hfp_l3->Draw();
     
   hfp->cd(4);
   simc_hypfp->DrawNormalized("histE0");
   data_hypfp->DrawNormalized("samesE0");
   hfp_l4->AddEntry(data_hypfp,"Data", "f");
   hfp_l4->AddEntry(simc_hypfp,"SIMC");
   hfp_l4->Draw();

   hfp->SaveAs(Form("hArm_FocalPlane_pm%d_set%d.pdf", pm, set));                                                                                   

   //----------------------------------------------------------- 
 
     //Set Legend
   auto leg_pmr = new TLegend(0.1,0.8,0.28,0.9);
   auto leg_thnqr = new TLegend(0.1,0.8,0.28,0.9);

  
   //-----------------PLOT Target Reconstructed Variables SIMC/Data comparison-----------------------

   //Create A Canvas to store Target Recon. variable comparisons in HADRON ARM
   
   TCanvas *cR = new TCanvas("cR", "Data/SIMC Ratio", 5000, 3000);
   cR->Divide(1,2);

   cR->cd(1);
   data_Pm->Divide(simc_Pm);
   data_Pm->DrawNormalized();
   data_Pm->GetXaxis()->SetRangeUser(-0.01,0.25);
   data_Pm->GetYaxis()->SetRangeUser(0.8,1.3);

   data_Pm->SetMarkerStyle(21);
   data_Pm->SetMarkerColor(kRed);
   data_Pm->SetLineColor(kRed);
   leg_pmr->AddEntry(data_Pm,"Ratio","f");
   leg_pmr->Draw();

   cR->cd(2);
   data_thnq->Divide(simc_thnq);
   data_thnq->Draw();
   data_thnq->GetYaxis()->SetRangeUser(0.8,1.3);
   data_thnq->SetMarkerStyle(21);
   data_thnq->SetMarkerColor(kRed);
   data_thnq->SetLineColor(kRed);
   leg_thnqr->AddEntry(data_thnq,"Ratio","f");
   leg_thnqr->Draw();

   cR->SaveAs(Form("YieldRatio_pm%d_set%d.pdf", pm, set));                                        



}
