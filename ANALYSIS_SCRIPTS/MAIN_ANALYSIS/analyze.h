#ifndef ANALYZE_H
#define ANALYZE_H

#include <string>

class analyze
{
  
 public:

  //Consructor / Destructor
  analyze(int run=0, string e_arm="SHMS", string type="data");
  ~analyze();
  
  //Define Functions Prototypes
  void SetDefinitions();
  void SetFileNames();
  void SetHistBins();
  void CreateHist();
  void ReadScalerTree(string bcm_type="BCM4A");  
  void ScalerEventLoop(Double_t current_thrs_bcm=5.); //bcm current cut threshold in uA units
  void ReadTree();
  void EventLoop();
  void CalcEff();
  void WriteHist();
  void WriteReport();


  //Auxiliary Function Prototypes (obtained from hcana) to calculate Pmx, Pmy, Pmz in the Lab/q-frame correctly
  void GeoToSph( Double_t  th_geo, Double_t  ph_geo, Double_t& th_sph, Double_t& ph_sph);
  void SetCentralAngles(Double_t th_cent, Double_t ph_cent);
  void TransportToLab( Double_t p, Double_t xptar, Double_t yptar, TVector3& pvect ); 

  //Utilities Functions for String Parsing
  string getString(char x);
  vector <string> split(string str, char del=':');
  vector <string> FindString(string keyword, string fname);

  //Variables related to Utilities Functions

 private:
  
  //Initialization Parameters
  int runNUM;
  string e_arm_name;
  string analysis;

  string h_arm_name;

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

  //Set Default histogram Binning
  Double_t nbins = 100;
  Double_t Em_nbins = 100;
  Double_t Em_xmin = -0.05;
  Double_t Em_xmax = 0.1;
  
  //Create DATA/SIMC Histograms (MUST BE THE EXACT SAME HSITOGRAMS)
  TH1F *H_Emiss;

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


  //Data-Specific Boolean CUTS
  Bool_t c_noedtm;
  Bool_t c_edtm;
  Bool_t c_ptrig6;
  Bool_t c_hgcerNpesum;
  Bool_t c_ngcerNpesum;
  Bool_t c_etotnorm;
  Bool_t c_etottrknorm;
  Bool_t c_ctime;

  //e- tracking efficiency Boolean
  Bool_t good_elec_should;
  Bool_t good_elec_did;
  //h tracking efficiency Boolean
  Bool_t good_hadron_should;
  Bool_t good_hadron_did;
      
  //DATA/SIMC Boolean CUTS (CUTS MUST BE EXACT SAME. Which is why only a variable is used for both)
  Bool_t c_edelta;  
  Bool_t c_hdelta; 
  Bool_t c_W;
  Bool_t c_Em;
  
  //DATA/SIMC Cuts to select PWIA region in D(e,e'p)
  Bool_t c_Q2;
  Bool_t c_th_nq;
  Bool_t c_MM;



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
  Double_t pGoodScinHit;
  Double_t pdc_ntrack;

  //HMS Detectors
  Double_t hCER_npeSum; 
  Double_t hCAL_etotnorm; 
  Double_t hCAL_etottracknorm; 
  Double_t hBetanotrk;
  Double_t hGoodScinHit;
  Double_t hdc_ntrack;

  //Electron Arm Focal Plane / Reconstructed Quantities (USED BY DATA AND SIMC)
  Double_t e_xfp;
  Double_t e_xpfp;
  Double_t e_yfp;
  Double_t e_ypfp;
  
  Double_t e_ytar;
  Double_t e_yptar;
  Double_t e_xptar;
  Double_t e_delta;
  Double_t kf;
  Double_t ki;

  //Hadron Arm Focal Plane / Reconstructed Quantities (USED BY DATA AND SIMC)
  Double_t h_xfp;
  Double_t h_xpfp;
  Double_t h_yfp;
  Double_t h_ypfp;
  
  Double_t h_ytar;
  Double_t h_yptar;
  Double_t h_xptar;
  Double_t h_delta;
  Double_t Pf;
  
  //Target Quantities (tarx, tary, tarz) in Hall Coord. System (USED BY DATA AND SIMC)
  Double_t  htar_x;
  Double_t  htar_y;
  Double_t  htar_z;
  
  Double_t  etar_x;
  Double_t  etar_y;
  Double_t  etar_z;
  
  //Primary Kinematics (electron kinematics) (USED BY DATA AND SIMC)
  Double_t theta_e;              //Central electron arm angle relative to +z (hall coord. system)
  Double_t W;                    //Invariant Mass W (should be proton mass in H(e,e'p))
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
  Double_t E_recoil;              //Recoil Energy of the system (neutron total energy)
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
  Double_t Ein_v;               //incident beam energy at vertex (simulates external rad. has rad. tail) ??? 

  
  

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


  //Read/Write ROOTfiles
  TFile *inROOT;
  TFile *outROOT;
  

  //Input ROOTfile Name
  TString simc_InputFileName;
  TString data_InputFileName;

  //Input REPORT_FILE
  string data_InputReport;

  //Output ROOTfile Name
  TString simc_OutputFileName;
  TString data_OutputFileName;
  
  TString report_OutputFileName;
  
  
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
  TVector3 p_miss_q;   //recoil system in q-frame



  //------------------------------------------------------------------------------------

};

  


#endif  //ANALYZE_H
