void replay_production_coin_pElec_hProt (Int_t RunNumber = 0, Int_t MaxEvent = 0,const char* ftype="tgt_boiling") {

  // Get RunNumber and MaxEvent if not provided.
  if(RunNumber == 0) {
    cout << "Enter a Run Number (-1 to exit): ";
    cin >> RunNumber;
    if( RunNumber<=0 ) return;
  }
  if(MaxEvent == 0) {
    cout << "\nNumber of Events to analyze: ";
    cin >> MaxEvent;
    if(MaxEvent == 0) {
      cerr << "...Invalid entry\n";
      exit;
    }
  }

  // Create file name patterns.
  const char* RunFileNamePattern = "coin_all_%05d.dat";
  vector<TString> pathList;
  pathList.push_back(".");
  pathList.push_back("./raw");
  pathList.push_back("./raw/../raw.copiedtotape");
  pathList.push_back("./cache");

  //const char* RunFileNamePattern = "raw/coin_all_%05d.dat";
  const char* ROOTFileNamePattern = "ROOTfiles/coin_replay_%s_%d_%d.root";

  // Load global parameters
  gHcParms->Define("gen_run_number", "Run Number", RunNumber);
  gHcParms->AddString("g_ctp_database_filename", "DEUTERON_ANALYSIS/DBASE/COIN/STD/standard.database");
  gHcParms->Load(gHcParms->GetString("g_ctp_database_filename"),RunNumber);
  gHcParms->Load(gHcParms->GetString("g_ctp_parm_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_calib_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_kinematics_filename"), RunNumber);

  // Load params for COIN trigger configuration
  gHcParms->Load("DEUTERON_ANALYSIS/PARAM/TRIG/tcoin.param");

  //gHcParms->Load("PARAM/TRIG/tcoin.param");


  //----------------------------------------
  //------------BCM Current Module----------
  //----------------------------------------
  ifstream hbcmFile;                                                                                
  TString hbcmParamFile = Form("DEUTERON_ANALYSIS/PARAM/HMS/BCM/Hbcmcurrent_%d.param",  RunNumber);       
  hbcmFile.open(hbcmParamFile);       
  
  ifstream pbcmFile;                                                                                
  TString pbcmParamFile = Form("DEUTERON_ANALYSIS/PARAM/SHMS/BCM/Pbcmcurrent_%d.param",  RunNumber);   
  pbcmFile.open(pbcmParamFile);   

  //-----------------------------------------


  // Load the Hall C detector map
  gHcDetectorMap = new THcDetectorMap();
  
  
  //All runs before coin 4361 did NOT have hDCREF_5 added in ROC3
  if(RunNumber < 4361)
    {
      gHcDetectorMap->Load("MAPS/COIN/DETEC/coin_comm18.map");
    }
  
  else{
    gHcDetectorMap->Load("MAPS/COIN/DETEC/coin.map");  //Fall 2018
  }
  
 //Add Module to explicitly plot all TDC hits from the trigger signals
  //THaDecData* decdata= new THaDecData("D","Decoder raw data");
  //gHaApps->Add(decdata);
  
  //=:=:=:=
  // SHMS 
  //=:=:=:=

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* SHMS = new THcHallCSpectrometer("P", "SHMS");
  SHMS->SetEvtType(1);
  SHMS->AddEvtType(4);
  SHMS->AddEvtType(5);
  SHMS->AddEvtType(6);
  SHMS->AddEvtType(7);
  gHaApps->Add(SHMS);
  // Add Noble Gas Cherenkov to SHMS apparatus
  THcCherenkov* pngcer = new THcCherenkov("ngcer", "Noble Gas Cherenkov");
  SHMS->AddDetector(pngcer);
  // Add drift chambers to SHMS apparatus
  THcDC* pdc = new THcDC("dc", "Drift Chambers");
  SHMS->AddDetector(pdc);
  // Add hodoscope to SHMS apparatus
  THcHodoscope* phod = new THcHodoscope("hod", "Hodoscope");
  SHMS->AddDetector(phod);
  // Add Heavy Gas Cherenkov to SHMS apparatus
  THcCherenkov* phgcer = new THcCherenkov("hgcer", "Heavy Gas Cherenkov");
  SHMS->AddDetector(phgcer);
  // Add Aerogel Cherenkov to SHMS apparatus
  THcAerogel* paero = new THcAerogel("aero", "Aerogel");
  SHMS->AddDetector(paero);
  // Add calorimeter to SHMS apparatus
  THcShower* pcal = new THcShower("cal", "Calorimeter");
  SHMS->AddDetector(pcal);

  // Add rastered beam apparatus
  THaApparatus* pbeam = new THcRasteredBeam("P.rb", "Rastered Beamline");
  gHaApps->Add(pbeam);
  // Add physics modules
  // Calculate reaction point
  THcReactionPoint* prp = new THcReactionPoint("P.react", "SHMS reaction point", "P", "P.rb");
  gHaPhysics->Add(prp);
  // Calculate extended target corrections
  THcExtTarCor* pext = new THcExtTarCor("P.extcor", "SHMS extended target corrections", "P", "P.react");
  gHaPhysics->Add(pext);
  // Calculate golden track quantites
  THaGoldenTrack* pgtr = new THaGoldenTrack("P.gtr", "SHMS Golden Track", "P");
  gHaPhysics->Add(pgtr);
  // Calculate the hodoscope efficiencies
  THcHodoEff* peff = new THcHodoEff("phodeff", "SHMS hodo efficiency", "P.hod");
  gHaPhysics->Add(peff);  

  // Add event handler for scaler events
  THcScalerEvtHandler* pscaler = new THcScalerEvtHandler("P", "Hall C scaler event type 1");
  pscaler->AddEvtType(1);
  pscaler->AddEvtType(4);
  pscaler->AddEvtType(5);
  pscaler->AddEvtType(6);
  pscaler->AddEvtType(7);
  pscaler->AddEvtType(129);
  pscaler->SetDelayedType(129);
  pscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(pscaler);

  //=:=:=
  // HMS 
  //=:=:=

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* HMS = new THcHallCSpectrometer("H", "HMS");
  HMS->SetEvtType(2);
  HMS->AddEvtType(4);
  HMS->AddEvtType(5);
  HMS->AddEvtType(6);
  HMS->AddEvtType(7);
  gHaApps->Add(HMS);
  // Add drift chambers to HMS apparatus
  THcDC* hdc = new THcDC("dc", "Drift Chambers");
  HMS->AddDetector(hdc);
  // Add hodoscope to HMS apparatus
  THcHodoscope* hhod = new THcHodoscope("hod", "Hodoscope");
  HMS->AddDetector(hhod);
  // Add Cherenkov to HMS apparatus
  THcCherenkov* hcer = new THcCherenkov("cer", "Heavy Gas Cherenkov");
  HMS->AddDetector(hcer);
  // Add Aerogel Cherenkov to HMS apparatus
  // THcAerogel* haero = new THcAerogel("aero", "Aerogel");
  // HMS->AddDetector(haero);
  // Add calorimeter to HMS apparatus
  THcShower* hcal = new THcShower("cal", "Calorimeter");
  HMS->AddDetector(hcal);

  // Add rastered beam apparatus
  THaApparatus* hbeam = new THcRasteredBeam("H.rb", "Rastered Beamline");
  gHaApps->Add(hbeam);  
  // Add physics modules
  // Calculate reaction point
  THcReactionPoint* hrp = new THcReactionPoint("H.react", "HMS reaction point", "H", "H.rb");
  gHaPhysics->Add(hrp);
  // Calculate extended target corrections
  THcExtTarCor* hext = new THcExtTarCor("H.extcor", "HMS extended target corrections", "H", "H.react");
  gHaPhysics->Add(hext);
  // Calculate golden track quantities
  THaGoldenTrack* hgtr = new THaGoldenTrack("H.gtr", "HMS Golden Track", "H");
  gHaPhysics->Add(hgtr);
  // Calculate the hodoscope efficiencies
  THcHodoEff* heff = new THcHodoEff("hhodeff", "HMS hodo efficiency", "H.hod");
  gHaPhysics->Add(heff);


  //BCM CUrrent Module
  
  if (hbcmFile.is_open())                                                        
    {                                                                                    
      THcBCMCurrent* hbc = new THcBCMCurrent("H.bcm", "BCM current check");
      gHaPhysics->Add(hbc);                                 
      gHcParms->Load(hbcmParamFile);                                                                         
    }                                                                 
  else if (!hbcmFile.is_open())                     
    {                                                                                                    
      cout << "HMS BCM Current Module will NOT be loaded . . ." << endl;                               
    } 

    if (pbcmFile.is_open())                                                        
    {                                                                                    
      THcBCMCurrent* pbc = new THcBCMCurrent("P.bcm", "BCM current check");
      gHaPhysics->Add(pbc);                                 
      gHcParms->Load(pbcmParamFile);                                                                         
    }                                                                 
  else if (!pbcmFile.is_open())                     
    {                                                                                                    
      cout << "SHMS BCM Current Module will NOT be loaded . . ." << endl;                               
    } 
  

  // Add event handler for scaler events
  THcScalerEvtHandler *hscaler = new THcScalerEvtHandler("H", "Hall C scaler event type 4");  
  hscaler->AddEvtType(2);
  hscaler->AddEvtType(4);
  hscaler->AddEvtType(5);
  hscaler->AddEvtType(6);
  hscaler->AddEvtType(7);
  hscaler->AddEvtType(129);
  hscaler->SetDelayedType(129);
  hscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(hscaler);

  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
  // Kinematics Modules
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

  // ---------------------------------
  // electrons in SHMS, protons in HMS
  // ---------------------------------
  // Add physics module to calculate primary (scattered electrons) beam kinematics
  THcPrimaryKine* pkin_primary = new THcPrimaryKine("P.kin.primary", "SHMS Single Arm Kinematics", "P", "P.rb");
  gHaPhysics->Add(pkin_primary);
  // Add physics module to calculate secondary (scattered hadrons) beam kinematics
  THcSecondaryKine* hkin_secondary = new THcSecondaryKine("H.kin.secondary", "HMS Single Arm Kinematics", "H", "P.kin.primary");
  gHaPhysics->Add(hkin_secondary);
 
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=
  // Global Objects & Event Handlers
  //=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=

  // Add trigger apparatus
  THaApparatus* TRG = new THcTrigApp("T", "TRG");
  gHaApps->Add(TRG);

 

  // Add trigger detector to trigger apparatus
  THcTrigDet* coin = new THcTrigDet("coin", "Coincidence Trigger Information");
  // Suppress missing reference time warnings for these event types
  coin->SetEvtType(1);
  coin->AddEvtType(2);
  TRG->AddDetector(coin); 

  //Add coin physics module
  THcCoinTime* coinTime = new THcCoinTime("CTime", "Coincidende Time Determination", "H", "P", "T.coin");
  gHaPhysics->Add(coinTime);

  // Add event handler for prestart event 125.
  THcConfigEvtHandler* ev125 = new THcConfigEvtHandler("HC", "Config Event type 125");
  gHaEvtHandlers->Add(ev125);
  // Add event handler for EPICS events
  THaEpicsEvtHandler* hcepics = new THaEpicsEvtHandler("epics", "HC EPICS event type 180");
  gHaEvtHandlers->Add(hcepics);
 
  // Set up the analyzer - we use the standard one,
  // but this could be an experiment-specific one as well.
  // The Analyzer controls the reading of the data, executes
  // tests/cuts, loops over Acpparatus's and PhysicsModules,
  // and executes the output routines.
  THcAnalyzer* analyzer = new THcAnalyzer;

  // A simple event class to be output to the resulting tree.
  // Creating your own descendant of THaEvent is one way of
  // defining and controlling the output.
  THaEvent* event = new THaEvent();

  // Define the run(s) that we want to analyze.
  // We just set up one, but this could be many.
  THcRun* run = new THcRun( pathList, Form(RunFileNamePattern, RunNumber) );

  // Set to read in Hall C run database parameters
  run->SetRunParamClass("THcRunParameters");
  
  // Eventually need to learn to skip over, or properly analyze the pedestal events
  run->SetEventRange(1, MaxEvent); // Physics Event number, does not include scaler or control events.
  run->SetNscan(1);
  run->SetDataRequired(0x7);
  run->Print();

  // Define the analysis parameters
  TString ROOTFileName = Form(ROOTFileNamePattern, ftype,RunNumber, MaxEvent);
  analyzer->SetCountMode(2);  // 0 = counter is # of physics triggers
                              // 1 = counter is # of all decode reads
                              // 2 = counter is event number

  analyzer->SetEvent(event);
  // Set EPICS event type
  analyzer->SetEpicsEvtType(180);
  analyzer->AddEpicsEvtType(181);
  analyzer->AddEpicsEvtType(182);

  // Define crate map
  analyzer->SetCrateMapFileName("MAPS/db_cratemap.dat");
  // Define output ROOT file
  analyzer->SetOutFile(ROOTFileName.Data());
  // Define DEF-file+
  TString DefTreeFile=Form("DEUTERON_ANALYSIS/DEF-files/COIN/%s.def",ftype);
  analyzer->SetOdefFile(DefTreeFile);
  // Define cuts file
  DefTreeFile="DEUTERON_ANALYSIS/DEF-files/COIN/CUTS/coin_production_cuts.def";
  analyzer->SetCutFile(DefTreeFile);  // optional
  // File to record accounting information for cuts
  analyzer->SetSummaryFile(Form("REPORT_OUTPUT/COIN/PRODUCTION/summary_production_%s_%d_%d.report", ftype, RunNumber, MaxEvent));  // optional
  
  //Comment out all cuts summary that show up at the end of every replay
  analyzer->SetVerbosity(2);

  // Start the actual analysis.
  analyzer->Process(run);
  // Create report file from template

  TString TemplateFile=Form("DEUTERON_ANALYSIS/TEMPLATES/COIN/coin_production.template");




   analyzer->PrintReport(TemplateFile,
   			 Form("REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_%s_%d_%d.report",ftype, RunNumber, MaxEvent));  
}
