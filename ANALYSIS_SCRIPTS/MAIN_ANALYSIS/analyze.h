#ifndef ANALYZE_H
#define ANALYZE_H

#include <string>

class analyze
{
  
 public:

  //Consructor / Destructor
  analyze(int run=-1, string e_arm="SHMS", string type="data", string react="heep");
  ~analyze();
  
  //Define Functions Prototypes
  void SetDefinitions();
  void SetFileNames();
  void SetCuts();
  void SetHistBins();
  void CreateHist();
  void ReadScalerTree(string bcm_type="BCM4A");  
  void ScalerEventLoop(Double_t current_thrs_bcm=5.); //bcm current cut threshold in uA units
  void ReadTree(string rad_flag="");
  void EventLoop();
  void CalcEff();
  void ApplyWeight();
  void WriteHist(string rad_flag="");
  void WriteReport();
  void CalcRadCorr();
  void ApplyRadCorr();

  //Auxiliary Function Prototypes (obtained from hcana) to calculate Pmx, Pmy, Pmz in the Lab/q-frame correctly
  void GeoToSph( Double_t  th_geo, Double_t  ph_geo, Double_t& th_sph, Double_t& ph_sph);
  void SetCentralAngles(Double_t th_cent, Double_t ph_cent);
  void TransportToLab( Double_t p, Double_t xptar, Double_t yptar, TVector3& pvect ); 

  //Utilities Functions for String Parsing
  string getString(char x);
  vector <string> split(string str, char del=':');
  vector <string> FindString(string keyword, string fname);

  string& ltrim(std::string& s);
  string& rtrim(std::string& s);
  string& trim(std::string& s);


  //-------Specialized Studies Methods-----------
  void CollimatorStudy();

  //------------Run Analysis Mehods--------------
  void run_simc_analysis(Bool_t rad_corr_flag=0);
  void run_data_analysis();


 private:
  
  //Initialization Parameters
  int runNUM;
  string e_arm_name;
  string analysis;
  string reaction;
  string h_arm_name;

  //Additional Parameters for D(e,e'p) Theory (Read from deep_input_file.dat)
  int pm_setting;      //80, 580, 750 MeV
  string theory;      //laget, misak, . . .
  string model;       //pwia, fsi, . . .
  int data_set;      //1, 2, 3

  //Spectrometer prefixes to be used in SetBranchAddress()
  string eArm;
  string hArm;

  //Set Constants
  Double_t pi; 
  Double_t dtr;
  Double_t MP;  
  Double_t MD;  
  Double_t MN; 
  Double_t me;
  Double_t tgt_mass;

  //Set Varibales to be read from REPORT_FILE
  Double_t e_th=0.;    //electron arm central angle
  Double_t e_ph=0.;    
  Double_t h_th=0.;    //hadron arm central angle
  Double_t h_ph=0.;

  Double_t xBPM;  //in cm
  Double_t yBPM;  //in cm
  
  Double_t e_xMisPoint;
  Double_t e_yMisPoint;
  Double_t h_xMisPoint;
  Double_t h_yMisPoint;

  //Central Spec. Momenta
  Double_t e_Pcen;
  Double_t h_Pcen;

  //-----------Set Default histogram Binning--------------
  Double_t nbins = 100;

  //Trigger Detector
  Double_t coin_nbins;
  Double_t coin_xmin;
  Double_t coin_xmax;

  //HMS DETECTORS
  Double_t hbeta_nbins = 100;
  Double_t hbeta_xmin = 0.5;
  Double_t hbeta_xmax = 1.5;

  Double_t hdc_dist_nbins = 100.;
  Double_t hdc_dist_xmin = -0.05;
  Double_t hdc_dist_xmax = 0.55;

  Double_t hdc_res_nbins = 100;
  Double_t hdc_res_xmin = -0.05;
  Double_t hdc_res_xmax = 0.05;

  Double_t hcer_nbins = 100;
  Double_t hcer_xmin = 0.001;
  Double_t hcer_xmax = 20.;

  Double_t hcal_nbins = 100;
  Double_t hcal_xmin = 0.001;
  Double_t hcal_xmax = 1.5;

  //SHMS Detectors
  Double_t pbeta_nbins = 100;
  Double_t pbeta_xmin = 0.5;
  Double_t pbeta_xmax = 1.5;

  Double_t pdc_dist_nbins = 100.;
  Double_t pdc_dist_xmin = -0.05;
  Double_t pdc_dist_xmax = 0.55;

  Double_t pdc_res_nbins = 100;
  Double_t pdc_res_xmin = -0.05;
  Double_t pdc_res_xmax = 0.05;

  Double_t pngcer_nbins = 100;
  Double_t pngcer_xmin = 0.001;
  Double_t pngcer_xmax = 20.;

  Double_t pcal_nbins = 100;
  Double_t pcal_xmin = 0.001;
  Double_t pcal_xmax = 1.5;

  //---------KINEMATICS-----
  
  //Missing Energy
  Double_t Em_nbins = 100;
  Double_t Em_xmin = -0.05;
  Double_t Em_xmax = 0.1;
  
  //Missing Momentum (and its components)
  Double_t Pm_nbins = nbins;
  Double_t Pm_xmin = -0.02;
  Double_t Pm_xmax = 0.08;
  
  Double_t Pmx_nbins = nbins;
  Double_t Pmx_xmin = -0.15;
  Double_t Pmx_xmax = 0.15;
  
  Double_t Pmy_nbins = nbins;
  Double_t Pmy_xmin = -0.15;
  Double_t Pmy_xmax = 0.15;
  
  Double_t Pmz_nbins = nbins;
  Double_t Pmz_xmin = -0.15;
  Double_t Pmz_xmax = 0.15;
  
  //Missing Mass 
  Double_t MM_nbins = nbins;
  Double_t MM_xmin = -0.1;
  Double_t MM_xmax = 0.1;
  
  //Missing Mass Squared
  Double_t MM2_nbins = nbins;
  Double_t MM2_xmin = -0.01;
  Double_t MM2_xmax = 0.01;
  

  //Q2
  Double_t Q2_nbins = nbins;
  Double_t Q2_xmin = 2.5;
  Double_t Q2_xmax = 5;
 
  //omega (E-E')
  Double_t om_nbins = nbins;
  Double_t om_xmin = 1.8;
  Double_t om_xmax = 2.6;

  //W_inv
  Double_t W_nbins = nbins;
  Double_t W_xmin = 0.85;
  Double_t W_xmax = 1.05;;

  //W2
  Double_t W2_nbins = nbins;
  Double_t W2_xmin = 0.5;                                                 
  Double_t W2_xmax = 0.9;; 

  //theta_elec
  Double_t the_nbins = nbins;
  Double_t the_xmin = 10.;
  Double_t the_xmax = 15.;

  //theta_prot
  Double_t thp_nbins = nbins;
  Double_t thp_xmin = 34.;
  Double_t thp_xmax = 42.;

  //xBj
  Double_t xbj_nbins = nbins;
  Double_t xbj_xmin = 0.8;
  Double_t xbj_xmax = 1.1;

  //Final Proton Momentum
  Double_t Pf_nbins = nbins;
  Double_t Pf_xmin = 2.5;
  Double_t Pf_xmax = 3.5;

  //Final Proton Energy
  Double_t Ep_nbins = nbins;
  Double_t Ep_xmin = 2.5;
  Double_t Ep_xmax = 3.5;

  //Final Proton Kinetic Energy
  Double_t Kp_nbins = nbins;
  Double_t Kp_xmin = 1.6;
  Double_t Kp_xmax = 2.6;

  //Final Neutron Energy
  Double_t En_nbins = nbins;
  Double_t En_xmin = 0.93;
  Double_t En_xmax = 0.96;

  //Final Proton Kinetic Energy
  Double_t Kn_nbins = nbins;
  Double_t Kn_xmin = -0.004;
  Double_t Kn_xmax = 0.02;

  //Final Electron Momentum
  Double_t kf_nbins = nbins;
  Double_t kf_xmin = 8;
  Double_t kf_xmax = 9;

  //th_q (Angle between +Z(hall) and q-vector)
  Double_t thq_nbins = nbins;
  Double_t thq_xmin = 32.;
  Double_t thq_xmax = 42.;
  
  //Magnitude of q-ector
  Double_t q_nbins = nbins;
  Double_t q_xmin = 2.6;
  Double_t q_xmax = 4.;
  
  //th_nq (Angle between proton and q-vector)
  Double_t thnq_nbins = nbins;
  Double_t thnq_xmin = 0.;
  Double_t thnq_xmax = 180.;

  //th_pq (Angle between proton and q-vector)
  Double_t thpq_nbins = nbins;
  Double_t thpq_xmin = -0.05;
  Double_t thpq_xmax = 1.2;



  //------Target Reconstruction Variables (Hall Coord. System)----------
  Double_t xtar_nbins = nbins;
  Double_t xtar_xmin = -0.5;
  Double_t xtar_xmax = 0.5;

  Double_t ytar_nbins = nbins;
  Double_t ytar_xmin = -0.5;
  Double_t ytar_xmax = 0.5;
  
  Double_t ztar_nbins = nbins;
  Double_t ztar_xmin = -10.0;
  Double_t ztar_xmax = 10.0;

  //Hadron arm Reconstructed Quantities (ytar, xptar, yptar, delta)
  Double_t hytar_nbins = nbins;
  Double_t hytar_xmin = -5.;
  Double_t hytar_xmax = 5.;
  
  Double_t hxptar_nbins = 70;
  Double_t hxptar_xmin = -0.1;
  Double_t hxptar_xmax = 0.1;
  
  Double_t hyptar_nbins = 70;
  Double_t hyptar_xmin = -0.05;
  Double_t hyptar_xmax = 0.05;
  
  Double_t hdelta_nbins = 70;
  Double_t hdelta_xmin = -9.;
  Double_t hdelta_xmax = 9.;

  //-----Hadron arm Focal Plane Quantities-----
  
  //X-focal plane
  Double_t hxfp_nbins = nbins;
  Double_t hxfp_xmin = -50.;
  Double_t hxfp_xmax = 40.;

  Double_t hyfp_nbins = nbins;  
  Double_t hyfp_xmin = -10.;
  Double_t hyfp_xmax = 25.;

  Double_t hxpfp_nbins = nbins;
  Double_t hxpfp_xmin = -0.06;
  Double_t hxpfp_xmax = 0.06;
  
  Double_t hypfp_nbins = nbins;
  Double_t hypfp_xmin = -0.015;
  Double_t hypfp_xmax = 0.03;

  
  //Electron Arm Reconstructed Quantities ( ytar, xptar, yptar, delta)
  Double_t eytar_nbins = nbins;
  Double_t eytar_xmin = -4.;
  Double_t eytar_xmax = 4.;
  
  Double_t exptar_nbins = nbins;
  Double_t exptar_xmin = -0.06;
  Double_t exptar_xmax = 0.06;
  
  Double_t eyptar_nbins = nbins;
  Double_t eyptar_xmin = -0.03;
  Double_t eyptar_xmax = 0.02;
  
  Double_t edelta_nbins = nbins;
  Double_t edelta_xmin = -5.;  
  Double_t edelta_xmax = 5.;   

  //Electron Arm Focal Plane Quantities
  Double_t exfp_nbins = nbins;
  Double_t exfp_xmin = -15.;
  Double_t exfp_xmax = 10.;
 
  Double_t eyfp_nbins = nbins;
  Double_t eyfp_xmin = -10.;
  Double_t eyfp_xmax = 10.;

  Double_t expfp_nbins = nbins;
  Double_t expfp_xmin = -0.04;
  Double_t expfp_xmax = 0.04;

  Double_t eypfp_nbins = nbins;
  Double_t eypfp_xmin = -0.03;
  Double_t eypfp_xmax = 0.03;

  //Collimator
  Double_t hXColl_nbins = 100;
  Double_t hXColl_xmin = -15.;  
  Double_t hXColl_xmax = 15.;   
  
  Double_t hYColl_nbins = 100;                                           
  Double_t hYColl_xmin = -15.;                                                                                                  
  Double_t hYColl_xmax = 15.;
  
  Double_t eXColl_nbins = 100;
  Double_t eXColl_xmin = -15.;
  Double_t eXColl_xmax = 15.;
  
  Double_t eYColl_nbins = 100;      
  Double_t eYColl_xmin = -15.;                                                                      
  Double_t eYColl_xmax = 15.;

  //---------------------END SET DEFAULT HISTOGRAM BINNING-----------------------

  //Detector Histograms (DATA ONLY)
  
  //Trigger Detector
  TH1F *H_ctime;

  //HMS Detectors
  TH1F *H_hbeta;
  TH1F *H_hdc_dist;
  TH1F *H_hdc_res;
  TH1F *H_hcer;
  TH1F *H_hcal;

  //SHMS Detectors
  TH1F *H_pbeta;
  TH1F *H_pdc_dist;
  TH1F *H_pdc_res;
  TH1F *H_pngcer;
  TH1F *H_pcal_etotnorm;
  TH1F *H_pcal_etotTrkNorm;


  //Create DATA/SIMC Histograms (MUST BE THE EXACT SAME HSITOGRAMS)

  //Primary (electron) Kinematics
  TH1F *H_Q2;
  TH1F *H_omega;
  TH1F *H_W;
  TH1F *H_W2;
  TH1F *H_xbj;
  TH1F *H_kf;
  TH1F *H_theta_q;
  TH1F *H_q;
  TH1F *H_theta_elec;
  
  
  //Secondary (Hadron) Kinematics
  TH1F *H_Em;
  TH1F *H_Em_nuc;
  TH1F *H_Pm;
  TH1F *H_Pmx_lab;
  TH1F *H_Pmy_lab;
  TH1F *H_Pmz_lab;
  TH1F *H_Pmx_q;
  TH1F *H_Pmy_q;
  TH1F *H_Pmz_q;
  TH1F *H_MM;
  TH1F *H_MM2;
  TH1F *H_Pf;
  TH1F *H_Ep;
  TH1F *H_En;
  TH1F *H_Kp;
  TH1F *H_Kn;
  TH1F *H_theta_prot;
  TH1F *H_theta_pq;
  TH1F *H_theta_nq;

  //Target Reconstruction Histos
  TH1F *H_hx_tar;
  TH1F *H_hy_tar;
  TH1F *H_hz_tar;

  TH1F *H_ex_tar;
  TH1F *H_ey_tar;
  TH1F *H_ez_tar;

  TH1F *H_ztar_diff;

  //Hadron Arm Recon. / Focal Plane Histos
  TH1F *H_hytar;
  TH1F *H_hxptar;
  TH1F *H_hyptar;
  TH1F *H_hdelta;

  TH1F *H_hxfp;
  TH1F *H_hyfp;
  TH1F *H_hxpfp;
  TH1F *H_hypfp;
  
  //Electron Arm Recon. / Focal Plane Histos
  TH1F *H_eytar;
  TH1F *H_exptar;
  TH1F *H_eyptar;
  TH1F *H_edelta;

  TH1F *H_exfp;
  TH1F *H_eyfp;
  TH1F *H_expfp;
  TH1F *H_eypfp;

  //HMS/SHMS Collimator
  TH1F *H_hXColl;
  TH1F *H_hYColl;
  TH1F *H_eXColl;
  TH1F *H_eYColl;

  //2D Collimator Histos
  TH2F *H_hXColl_vs_hYColl;
  TH2F *H_eXColl_vs_eYColl;

  //2D Kinematics Check
  TH2F *H_Em_vs_Pm;
  TH2F *H_Em_nuc_vs_Pm;

  //Create Scaler Related Histogram (ONLY FOR SCALERS)
  TH1F *H_bcmCurrent;

  //------------------------------Data Related Variables--------------------------------
  TTree *tree;
  Long64_t nentries;
  
  //Set-Up Tdc Counters for accepted triggers
  Double_t total_ptrig1_accp = 0;
  Double_t total_ptrig2_accp = 0;
  Double_t total_ptrig3_accp = 0;
  Double_t total_ptrig4_accp = 0;
  Double_t total_ptrig6_accp = 0;
  Double_t total_pedtm_accp = 0;
  
  //Set-Up Tdc Counters for accepted triggers (passed bcm cut)
  Double_t total_ptrig1_accp_bcm_cut = 0;
  Double_t total_ptrig2_accp_bcm_cut = 0;
  Double_t total_ptrig3_accp_bcm_cut = 0;
  Double_t total_ptrig4_accp_bcm_cut = 0;
  Double_t total_ptrig6_accp_bcm_cut = 0;
  Double_t total_pedtm_accp_bcm_cut = 0;

  //Tracking Efficiency Counter / Live Time (passed bcm cuts)
  //HMS
  Double_t h_did = 0;
  Double_t h_should = 0;
  Double_t hTrkEff;
  Double_t hTrkEff_err;
  
  //SHMS
  Double_t e_did = 0;
  Double_t e_should = 0;
  Double_t eTrkEff;
  Double_t eTrkEff_err;

  //Live Time 
  Double_t cpuLT;
  Double_t cpuLT_err;
  Double_t tLT;
  Double_t tLT_err;


  //Data-Specific Boolean CUTS (For Tracking Eff. ONLY)
  Bool_t c_noedtm;
  Bool_t c_edtm;
  Bool_t c_ptrig6;
  Bool_t c_hgcerNpesum;
  Bool_t c_ngcerNpesum;
  Bool_t c_etotnorm;
  Bool_t c_etottrknorm;
 

  //e- tracking efficiency Boolean
  Bool_t good_elec_should;
  Bool_t good_elec_did;
  //h tracking efficiency Boolean
  Bool_t good_hadron_should;
  Bool_t good_hadron_did;
      
  //DATA/SIMC Boolean CUTS (CUTS MUST BE EXACT SAME. Which is why only a variable is used for both)
  Bool_t Em_cut_flag;
  Bool_t W_cut_flag;
  Bool_t hdelta_cut_flag;
  Bool_t edelta_cut_flag;
  Bool_t ztar_diff_cut_flag;
  Bool_t Q2_cut_flag;
  Bool_t thnq_cut_flag;
  Bool_t MM_cut_flag;

  Bool_t base_cuts;
  Bool_t pid_cuts;

  Bool_t c_edelta;    Double_t edel_min;      Double_t edel_max;
  Bool_t c_hdelta;    Double_t hdel_min;      Double_t hdel_max;
  Bool_t c_W;         Double_t W_min;         Double_t W_max;
  Bool_t c_Em;        Double_t Em_min;        Double_t Em_max;
  Bool_t c_Em_nuc;    Double_t Em_nuc_min;    Double_t Em_nuc_max;

  Bool_t c_Q2;        Double_t Q2_min;        Double_t Q2_max;
  Bool_t c_th_nq;     Double_t thnq_min;      Double_t thnq_max;
  Bool_t c_MM;        Double_t MM_min;        Double_t MM_max;
  
  Bool_t c_ztarDiff;  Double_t ztarDiff_min;  Double_t ztarDiff_max;

  //Detector PID CUTS ON DATA
  Bool_t shmsCal_cut_flag;  
  Bool_t coin_cut_flag;

  Bool_t c_shms_cal;  Double_t shms_cal_min;   Double_t shms_cal_max;
  Bool_t c_ctime;     Double_t ctime_min;      Double_t ctime_max;


  //------------------------------------------------------------------------------------

  //--------------------Data TTree Leaf Variable Names (DATA)---------------------------

  //Coincidence Time
  Double_t epCoinTime;
 
  //Trigger Detector / Global Variables
  Double_t gevtyp;
  Double_t gevnum;
  Double_t pTRIG1_tdcTimeRaw;
  Double_t pTRIG2_tdcTimeRaw;
  Double_t pTRIG3_tdcTimeRaw;
  Double_t pTRIG4_tdcTimeRaw;
  Double_t pTRIG6_tdcTimeRaw;
  Double_t pEDTM_tdcTimeRaw;
  
  //SHMS Detectors
  Double_t pHGCER_npeSum;
  Double_t pNGCER_npeSum;
  Double_t pCAL_etotnorm; 
  Double_t pCAL_etottracknorm; 
  Double_t pBetanotrk;
  Double_t pBeta;
  Double_t pGoodScinHit;
  Double_t pdc_ntrack;
  Double_t pdc_dist;
  Double_t pdc_res;

  //HMS Detectors
  Double_t hCER_npeSum; 
  Double_t hCAL_etotnorm; 
  Double_t hCAL_etottracknorm; 
  Double_t hBetanotrk;
  Double_t hBeta;
  Double_t hGoodScinHit;
  Double_t hdc_ntrack;
  Double_t hdc_dist;
  Double_t hdc_res;

  //Electron Arm Focal Plane / Reconstructed Quantities (USED BY DATA AND SIMC)
  Double_t e_xfp;
  Double_t e_xpfp;
  Double_t e_yfp;
  Double_t e_ypfp;
  
  Double_t e_ytar;
  Double_t e_yptar;
  Double_t e_xptar;
  Double_t e_delta;
  Double_t kf;                        //final electron momentum
  Double_t ki;                        //initial electron momentum

  //Hadron Arm Focal Plane / Reconstructed Quantities (USED BY DATA AND SIMC)
  Double_t h_xfp;
  Double_t h_xpfp;
  Double_t h_yfp;
  Double_t h_ypfp;
  
  Double_t h_ytar;
  Double_t h_yptar;
  Double_t h_xptar;
  Double_t h_delta;
  Double_t Pf;                 //final proton momentum
  
  //Target Quantities (tarx, tary, tarz) in Hall Coord. System (USED BY DATA AND SIMC)
  Double_t tar_x; //For SIMC ONLY (It is the same for HMS/SHMS)

  Double_t  htar_x;
  Double_t  htar_y;
  Double_t  htar_z;
  
  Double_t  etar_x;
  Double_t  etar_y;
  Double_t  etar_z;

  Double_t ztar_diff;

  //Collimators
  Double_t hXColl, hYColl, eXColl, eYColl;

  //Primary Kinematics (electron kinematics) (USED BY DATA AND SIMC)
  Double_t theta_e;              //Central electron arm angle relative to +z (hall coord. system)
  Double_t W;                    //Invariant Mass W (should be proton mass in H(e,e'p))
  Double_t W2;                    //Invariant mass squared
  Double_t Q2;                   //Four-momentum trasfer
  Double_t X;                    //B-jorken X  scaling variable
  Double_t nu;                   //Energy Transfer
  Double_t q;                  //magnitude of the 3-vector q
  Double_t th_q;                 //angle between q and +z (hall coord. system)

  //Secondary Kinematics (USED BY DATA AND SIMC)
  Double_t Ep;                     //proton energy
  Double_t Em;                    //Standard Missing Energy for H(e,e'p)
  Double_t Em_nuc;                //Nuclear definition of Missing Energy (Used for D(e,e'p): B.E. of deuteron)
  Double_t Pm;                    //Missing Momentum (should be zero for H(e,e'p). Should be neutron momentum for D(e,e'p))
  Double_t Pmx_lab;               //X-Component of Missing Momentum (in Lab(or Hall) frame. +X: beam left, +Y: up, +Z: downstream beam) 
  Double_t Pmy_lab;
  Double_t Pmz_lab;
  Double_t Pmx_q;                 //X-Component of Missing Momentum (in frame where +z_lab is rotated to +z_q. Pmz_q is along +z(parallel to q))
  Double_t Pmy_q;
  Double_t Pmz_q;
  Double_t Kp;                    //Kinetic Energy of detected particle (proton)
  Double_t Kn;                    //Kinetic Energy of recoil system (neutron)
  Double_t M_recoil;              //Missing Mass (neutron Mass)
  Double_t MM2;                   //Missing Mass Squared
  Double_t E_recoil;              //Recoil Energy of the system (neutron total energy)
  Double_t En;                    //Same as above
  Double_t th_pq;                  //Polar angle of detected particle with q   ----> th_pq
  Double_t th_nq;                  //Polar angle of recoil system with q (rad)  ---> th_nq (neutreon-q angle. IMPORTANT in D(e,e'p))
  Double_t ph_pq;                  //Azimuth angle of detected particle with q    ----> phi_pq angle between proton and q-vector
  Double_t ph_nq;                  //Azimuth of recoil system with scattering plane (rad) ----> phi_nq angle between neutron and q-vector
  Double_t xangle;                //Angle of detected particle with scattered electron (Used to determine hadron angle)
  Double_t theta_p;               //to be calculated separately (in data)


  //SIMC Specific TTree Variable Names
  Double_t Normfac;
  
  //Thrown quantities (Used to determine spec. resolution)
  Double_t h_deltai;
  Double_t h_yptari;
  Double_t h_xptari;
  Double_t h_ytari;
  
  Double_t e_deltai;
  Double_t e_yptari;
  Double_t e_xptari;
  Double_t e_ytari;
  
  Double_t epsilon;
  Double_t corrsing;
  Double_t fry;
  Double_t radphot;
  Double_t sigcc;
  Double_t Weight;               //This Weight has the cross section in it
  Double_t Jacobian;
  Double_t Genweight;
  Double_t SF_weight;
  Double_t Jacobian_corr;
  Double_t sig;
  Double_t sig_recon;
  Double_t sigcc_recon;
  Double_t coul_corr;
  Double_t Ein;                  //single beam energy value (SIMC Uses this energy. If not corr. for energy loss, it should be same as in input file)
  Double_t theta_rq;
  Double_t SF_weight_recon;
  Double_t h_Thf;
  //Vertex Quantities (no Eloss) that will be used to calculated the cross section @ the average kinematics
  Double_t Ein_v;               //incident beam energy at vertex (simulates external rad. has rad. tail) ??? 
  Double_t Q2_v;
  Double_t nu_v;
  Double_t q_lab_v;
  Double_t pm_v;
  Double_t pm_par_v;
  Double_t pf_v;
  Double_t Ep_v;
  Double_t Ef_v;
  
  Double_t prob_abs;  // Probability of absorption of particle in the HMS Collimator
                      //(Must be multiplies by the weight. If particle interation is
                      //NOT simulated, it is set to 1.)

  
  //SIMC Collimator
  Double_t htarx_corr;
  Double_t etarx_corr;


  //-----------------------------------------------------------------


  //-------------------Scaler Related variables----------------------
  TTree *scaler_tree;
  Long64_t scal_entries;
  Int_t *evt_flag_bcm;  //flag (0 or 1) to determine whether the scaler read passed the cut
  Int_t *scal_evt_num;   //store data event number associated with scaler read 
  Double_t set_current;  //Set current for each run. For now, take the current ->  maximum bin content of bcm current histogram 
  Int_t scal_read = 0; //scaler read counter (actually used inside data loop to count scaler reads)


  //Define Quantities To Store Previous Reads
  Double_t prev_time = 0.;
  Double_t prev_charge_bcm = 0.;
  Double_t prev_ps1x_scaler = 0;
  Double_t prev_ptrig1_scaler = 0;
  Double_t prev_ptrig2_scaler = 0;
  Double_t prev_ptrig3_scaler = 0;
  Double_t prev_ptrig4_scaler = 0;
  Double_t prev_ptrig6_scaler = 0;
  Double_t prev_pedtm_scaler = 0;

  //Define Quantities To Store Accumulated Reads
  Double_t total_time = 0.;
  Double_t total_charge_bcm = 0.;
  Double_t total_ps1x_scaler = 0;
  Double_t total_ptrig1_scaler = 0;
  Double_t total_ptrig2_scaler = 0;
  Double_t total_ptrig3_scaler = 0;
  Double_t total_ptrig4_scaler = 0;
  Double_t total_ptrig6_scaler = 0;
  Double_t total_pedtm_scaler = 0;

  //Store Accumulated Reads if they passed BCM Current Cut
  Double_t total_time_bcm_cut = 0.;
  Double_t total_charge_bcm_cut = 0.;
  Double_t total_ps1x_scaler_bcm_cut = 0;
  Double_t total_ptrig1_scaler_bcm_cut = 0;
  Double_t total_ptrig2_scaler_bcm_cut = 0;
  Double_t total_ptrig3_scaler_bcm_cut = 0;
  Double_t total_ptrig4_scaler_bcm_cut = 0;
  Double_t total_ptrig6_scaler_bcm_cut = 0;
  Double_t total_pedtm_scaler_bcm_cut = 0;

  //Store Scaler Rates if current cut passed
  Double_t pS1XscalerRate_bcm_cut;
  Double_t pTRIG1scalerRate_bcm_cut;
  Double_t pTRIG2scalerRate_bcm_cut;
  Double_t pTRIG3scalerRate_bcm_cut;
  Double_t pTRIG4scalerRate_bcm_cut;
  Double_t pTRIG6scalerRate_bcm_cut;
  Double_t pEDTMscalerRate_bcm_cut;

  //Store Average BCM Current
  Double_t  avg_current_bcm_cut;

  //-----------------------------------------------------------------

  //Scaler TTree Variable Names (DATA)
  Double_t Scal_evNum;
  Double_t Scal_BCM_charge;
  Double_t Scal_BCM_current;
  Double_t Scal_time;
  Double_t pS1X_scaler;
  Double_t pTRIG1_scaler;   //SHMS 3/4 (in COIN MODE)
  Double_t pTRIG2_scaler;   //SHMS EL-REAL (in COIN MODE)
  Double_t pTRIG3_scaler;   //SHMS EL-CLEAN (in COIN MODE)
  Double_t pTRIG4_scaler;   //HMS 3/4 (in COIN MODE)
  Double_t pTRIG6_scaler;   //HMS 3/4 : SHMS 3/4 Coin. Trigger
  Double_t pEDTM_scaler;     

  //-----------------Variable Related to FullWeight Applied to Yield------------------

  Double_t FullWeight = 1;  //default
  
  //For References to Proton Absorption / Target Boiling Studies, See Hall C DOC_DB (Carlos Yero)
  Double_t pAbs_corr;            //correct for lost coincidences due to the proton in HMS NOT making it to the hodo to form trigger
  Double_t tgtBoil_corr;        //correct for lost coincidences due to localized target boiling at high currents

  //Slope of Norm. Yield vs. avg beam current (Determined from target boiling studies)
  Double_t LH2_slope = 0.0006;     //Units Yield / mC    
  Double_t LD2_slope = 0.0008;


  //----------------------------------------------------------------------------------

  //Read/Write ROOTfiles
  TFile *inROOT;
  TFile *outROOT;
  

  //Input ROOTfile Name
  TString simc_InputFileName_rad;  
  TString simc_InputFileName_norad;
  TString data_InputFileName;

  //Input REPORT_FILE
  string data_InputReport;

  string input_CutFileName;

  //Output ROOTfile Name
  TString simc_OutputFileName_rad;
  TString simc_OutputFileName_norad;
  TString simc_OutputFileName_radCorr;

  TString data_OutputFileName;
  TString data_OutputFileName_radCorr;

  TString report_OutputFileName;
  TString YieldStudy_FileName;
  
  //FileStreams to READ/WRITE to a txt file
  ofstream out_file;
  ifstream in_file;
 
  
  //----------Variables Used in Auxiliary Functions--------------------------------------

  TRotation       fToLabRot;              //Rotation matrix from TRANSPORT to lab
  Double_t        fThetaGeo;              //In-plane geographic central angle (rad)
  Double_t        fPhiGeo;                //Out-of-plane geographic central angle (rad)
  Double_t        fThetaSph, fPhiSph;     //Central angles in spherical coords. (rad)
  Double_t        fSinThGeo, fCosThGeo;   //Sine and cosine of central angles
  Double_t        fSinPhGeo, fCosPhGeo;   // in geographical coordinates
  Double_t        fSinThSph, fCosThSph;   //Sine and cosine of central angles in 
  Double_t        fSinPhSph, fCosPhSph;   // spherical coordinates


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

  //Declare necessary variables for rotaion from +z to +q
  TVector3 qvec;
  TVector3 kfvec;
  TRotation rot_to_q;
  TVector3 bq;   //recoil system in lab frame (Pmx, Pmy, Pmz)
  TVector3 xq;   //detected system in lab frame
  TVector3 p_miss_q;   //recoil system in q-frame

  //Leaf Variables
  Double_t fTheta_xq;
  Double_t fPhi_xq;
  Double_t fTheta_bq;
  Double_t fPhi_bq;


  //------------------------------------------------------------------------------------
 

  //-------Collimator Study-------
  Bool_t hmsCollCut_flag;      //flag to enable/disable collimator cut
  Bool_t shmsCollCut_flag;

  Bool_t hmsColl_Cut;
  Bool_t shmsColl_Cut;

  TCutG *hms_Coll_gCut;   //HMS Collimator Graphical Cut
  TCutG *shms_Coll_gCut;  //SHMS Collimator Graphical Cut

  //HMS Octagonal Collimator Size (Each of the octagonal points is a multiple of 1 or 1/2 of these values)
  Double_t hms_hsize = 4.575;  //cm
  Double_t hms_vsize = 11.646;
 
  //SHMS Octagonal Collimator Size (Each of the octagonal points is a multiple of 1 or 1/2 of these values)
  Double_t shms_hsize = 17.;  //cm
  Double_t shms_vsize = 25.;

  //Scaling factor to scale collimator cuts from original size cut
  Double_t hms_scale=1.;   //Default
  Double_t shms_scale=1.;

  //------------------------------



};

  


#endif  //ANALYZE_H
