void replay_shms (Int_t RunNumber = 0, Int_t MaxEvent = 0,const char* ftype="tgt_boiling") {

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
  const char* RunFileNamePattern = "shms_all_%05d.dat";
  vector<TString> pathList;
    pathList.push_back(".");
    pathList.push_back("./raw");
    pathList.push_back("./raw/../raw.copiedtotape");
    pathList.push_back("./cache");

  
  const char* ROOTFileNamePattern = "ROOTfiles/shms_replay_%s_%d_%d.root";
  
  // Load global parameters
  // Add variables to global list.
  gHcParms->Define("gen_run_number", "Run Number", RunNumber);
  gHcParms->AddString("g_ctp_database_filename", "DEUTERON_ANALYSIS/DBASE/SHMS/STD/standard.database");
  // Load varibles from files to global list.
  gHcParms->Load(gHcParms->GetString("g_ctp_database_filename"), RunNumber);
  gHcParms->Load(gHcParms->GetString("g_ctp_parm_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_calib_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_kinematics_filename"), RunNumber);
  
  // Load params for SHMS trigger configuration
  gHcParms->Load("DEUTERON_ANALYSIS/PARAM/TRIG/tshms.param");
  
  ifstream bcmFile;
  TString bcmParamFile = Form("DEUTERON_ANALYSIS/PARAM/SHMS/BCM/bcmcurrent_%d.param",  RunNumber);
  bcmFile.open(bcmParamFile);
  

  // Load the Hall C detector map
  gHcDetectorMap = new THcDetectorMap();


  gHcDetectorMap->Load("MAPS/SHMS/DETEC/STACK/shms_stack.map");

  //Add Module to explicitly plot all TDC hits from the trigger signals
  //THaDecData* decdata= new THaDecData("D","Decoder raw data");
  //gHaApps->Add(decdata);
  
  //Add trigger apparatus
  THaApparatus* TRG = new THcTrigApp("T", "TRG");
  gHaApps->Add(TRG);
  
  //Add trigger detector to trigger apparatus
  THcTrigDet* shms = new THcTrigDet("shms", "SHMS Trigger Information");
  TRG->AddDetector(shms);

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* SHMS = new THcHallCSpectrometer("P", "SHMS");
  gHaApps->Add(SHMS);
  // Add Noble Gas Cherenkov to SHMS apparatus
  THcCherenkov* ngcer = new THcCherenkov("ngcer", "Noble Gas Cherenkov");
  SHMS->AddDetector(ngcer);
  // Add drift chambers to SHMS apparatus
  THcDC* dc = new THcDC("dc", "Drift Chambers");
  SHMS->AddDetector(dc);
  // Add hodoscope to SHMS apparatus
  THcHodoscope* hod = new THcHodoscope("hod", "Hodoscope");
  SHMS->AddDetector(hod);
  // Add Heavy Gas Cherenkov to SHMS apparatus
  THcCherenkov* hgcer = new THcCherenkov("hgcer", "Heavy Gas Cherenkov");
  SHMS->AddDetector(hgcer);

  // Add Aerogel Cherenkov to SHMS apparatus
  THcAerogel* aero = new THcAerogel("aero", "Aerogel");
  SHMS->AddDetector(aero);
  // Add calorimeter to SHMS apparatus
  THcShower* cal = new THcShower("cal", "Calorimeter");
  SHMS->AddDetector(cal);

  // Include golden track information
  THaGoldenTrack* gtr = new THaGoldenTrack("P.gtr", "SHMS Golden Track", "P");
  gHaPhysics->Add(gtr);
  // Add Rastered Beam Apparatus
  THaApparatus* beam = new THcRasteredBeam("P.rb", "Rastered Beamline");
  gHaApps->Add(beam);
  THcReactionPoint* prp= new THcReactionPoint("P.react"," SHMS reaction point","P","P.rb");
  gHaPhysics->Add(prp);
  THcExtTarCor* pext = new THcExtTarCor("P.extcor"," HMS extended target corrections","P","P.react");
  gHaPhysics->Add(pext);
  // Add Physics Module to calculate primary (scattered beam - usually electrons) kinematics
  THcPrimaryKine* kin = new THcPrimaryKine("P.kin", "SHMS Single Arm Kinematics", "P", "P.rb");
  gHaPhysics->Add(kin);
 THcHodoEff* peff = new THcHodoEff("phodeff"," SHMS hodo efficiency","P.hod");
  gHaPhysics->Add(peff);
  
  if (bcmFile.is_open())
    {
      THcBCMCurrent* pbc = new THcBCMCurrent("P.bcm", "BCM current check");
      gHaPhysics->Add(pbc);
      
      gHcParms->Load(bcmParamFile);
      
    }

  else if (!bcmFile.is_open())
    {
      cout << "BCM Current Module will NOT be loaded . . ." << endl;
    }

  // Add event handler for prestart event 125.
  THcConfigEvtHandler* ev125 = new THcConfigEvtHandler("HC", "Config Event type 125");
  gHaEvtHandlers->Add(ev125);
  // Add event handler for EPICS events
  THaEpicsEvtHandler* hcepics = new THaEpicsEvtHandler("epics", "HC EPICS event type 180");
  gHaEvtHandlers->Add(hcepics);
  // Add event handler for scaler events
  THcScalerEvtHandler* pscaler = new THcScalerEvtHandler("P", "Hall C scaler event type 1");
  pscaler->AddEvtType(1);
  pscaler->AddEvtType(2);
  pscaler->AddEvtType(3);
  pscaler->AddEvtType(129);
  pscaler->SetDelayedType(129);
  pscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(pscaler);
  
  // Add event handler for DAQ configuration event
  THcConfigEvtHandler *pconfig = new THcConfigEvtHandler("pconfig", "Hall C configuration event handler");
  gHaEvtHandlers->Add(pconfig);

  // Set up the analyzer - we use the standard one,
  // but this could be an experiment-specific one as well.
  // The Analyzer controls the reading of the data, executes
  // tests/cuts, loops over Acpparatus's and PhysicsModules,
  // and executes the output routines.
  THcAnalyzer* analyzer = new THcAnalyzer;

  // A simple event class to be output to the resulting tree.
  // Creating your own descendant of THaEvent is one way of
  // defining and controlling the output.
  THaEvent* event = new THaEvent;

  // Define the run(s) that we want to analyze.
  // We just set up one, but this could be many.
  THcRun* run = new THcRun( pathList, Form(RunFileNamePattern, RunNumber) );

  // Set to read in Hall C run database parameters
  run->SetRunParamClass("THcRunParameters");
  
  // Eventually need to learn to skip over, or properly analyze
  // the pedestal events
  run->SetEventRange(1, MaxEvent);    // Physics Event number, does not
                                      // include scaler or control events.
  run->SetNscan(1);
  run->SetDataRequired(0x7);
  run->Print();

  // Define the analysis parameters
  TString ROOTFileName = Form(ROOTFileNamePattern,ftype, RunNumber, MaxEvent);
  analyzer->SetCountMode(2);    // 0 = counter is # of physics triggers
                                // 1 = counter is # of all decode reads
                                // 2 = counter is event number
  analyzer->SetEvent(event);
  // Set EPICS event type
  analyzer->SetEpicsEvtType(180);
  analyzer->AddEpicsEvtType(181);
    
  // Define crate map
  analyzer->SetCrateMapFileName("MAPS/db_cratemap.dat");
  // Define output ROOT file
  analyzer->SetOutFile(ROOTFileName.Data());
  // Define DEF-file
  TString DefTreeFile=Form("DEUTERON_ANALYSIS/DEF-files/SHMS/%s.def",ftype);
  analyzer->SetOdefFile(DefTreeFile);
  // Define cuts file
  // DefTreeFile=Form("UTIL_COMM_ONEPASS/DEF-files/SHMS/%s_cuts.def",ftype);
  DefTreeFile="DEUTERON_ANALYSIS/DEF-files/SHMS/CUTS/pstackana_production_cuts.def";
  analyzer->SetCutFile(DefTreeFile);  // optional
  // File to record accounting information for cuts
  analyzer->SetSummaryFile(Form("REPORT_OUTPUT/SHMS/PRODUCTION/summary_%s_%d_%d.report", ftype, RunNumber, MaxEvent));  // optional
  // Start the actual analysis.

  //Comment out all cuts summary that show up at the end of every replay
  analyzer->SetVerbosity(2);

  analyzer->Process(run);
  
  //Determine which template file to use based on ftype user input
  TString temp_file;
  
  if(strcmp(ftype,"scaler") == 0)
    { 
      temp_file = "pscalers.template";
    }
  else
    {
      temp_file="pstackana_production.template";
    }

  // Create report file from template
  analyzer->PrintReport("DEUTERON_ANALYSIS/TEMPLATES/SHMS/"+temp_file,
  			Form("REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_%s_%d_%d.report",ftype, RunNumber, MaxEvent));  // optional

}
