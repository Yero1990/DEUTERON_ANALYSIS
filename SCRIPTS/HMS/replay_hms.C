void replay_hms(Int_t RunNumber=0, Int_t MaxEvent=0,const char* ftype="hscaler") {

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
  const char* RunFileNamePattern = "hms_all_%05d.dat";
  vector<TString> pathList;
    pathList.push_back(".");
    pathList.push_back("./raw");
    pathList.push_back("./raw/../raw.copiedtotape");
    pathList.push_back("./cache");

  const char* ROOTFileNamePattern = "ROOTfiles/hms_replay_%s_%d_%d.root";

  //Load Global parameters
  // Add variables to global list.
  gHcParms->Define("gen_run_number", "Run Number", RunNumber);
  gHcParms->AddString("g_ctp_database_filename", "UTIL_COMM_ONEPASS/DBASE/HMS/STD/standard.database");
  // Load varibles from files to global list.
  gHcParms->Load(gHcParms->GetString("g_ctp_database_filename"), RunNumber);
  // g_ctp_parm_filename and g_decode_map_filename should now be defined.
  gHcParms->Load(gHcParms->GetString("g_ctp_kinematics_filename"), RunNumber);
  gHcParms->Load(gHcParms->GetString("g_ctp_parm_filename"));
  gHcParms->Load(gHcParms->GetString("g_ctp_calib_filename"));
  // Load params for HMS trigger configuration
  gHcParms->Load("PARAM/TRIG/thms.param");
  //   gHcParms->Load("PARAM/HMS/HODO/CALIB/htofcalib.param");
  
  ifstream bcmFile;
  TString bcmParamFile = Form("UTIL_COMM_ONEPASS/PARAM/HMS/BCM/bcmcurrent_%d.param",  RunNumber);
  bcmFile.open(bcmParamFile);


  // Load the Hall C detector map
  gHcDetectorMap = new THcDetectorMap();
  //gHcDetectorMap->Load("MAPS/HMS/DETEC/STACK/hms_stack.map");  //Post Spring-2018 Run Period HMS Map 
  gHcDetectorMap->Load("MAPS/HMS/DETEC/STACK/hms_stack_comm18.map");  //Dec 2017/Sprin-2018 Run HMS Map (with ROC3, TDC SLot 2 pointing to hDCREF1)
  gHcParms->Load("PARAM/HMS/GEN/h_fadc_debug.param");

  // Add trigger apparatus
  THaApparatus* TRG = new THcTrigApp("T", "TRG");
  gHaApps->Add(TRG);
  
// Add trigger detector to trigger apparatus
  THcTrigDet* hms = new THcTrigDet("hms", "HMS Trigger Information");
  TRG->AddDetector(hms);

  // Set up the equipment to be analyzed.
  THcHallCSpectrometer* HMS = new THcHallCSpectrometer("H", "HMS");
  gHaApps->Add(HMS);
  // Add drift chambers to HMS apparatus
  THcDC* dc = new THcDC("dc", "Drift Chambers");
  HMS->AddDetector(dc);
  // Add hodoscope to HMS apparatus
  THcHodoscope* hod = new THcHodoscope("hod", "Hodoscope");
  HMS->AddDetector(hod);
  // Add Cherenkov to HMS apparatus
  THcCherenkov* cer = new THcCherenkov("cer", "Heavy Gas Cherenkov");
  HMS->AddDetector(cer);
  // Add Aerogel Cherenkov to HMS apparatus
  //THcAerogel* aero = new THcAerogel("aero", "Aerogel");
  //HMS->AddDetector(aero);
  // Add calorimeter to HMS apparatus
  THcShower* cal = new THcShower("cal", "Calorimeter");
  HMS->AddDetector(cal);

// Add Rastered Beam Apparatus
  THaApparatus* beam = new THcRasteredBeam("H.rb", "Rastered Beamline");
  gHaApps->Add(beam);  
  THcReactionPoint* hrp= new THcReactionPoint("H.react"," HMS reaction point","H","H.rb");
  gHaPhysics->Add(hrp);
  THcExtTarCor* hext = new THcExtTarCor("H.extcor"," HMS extended target corrections","H","H.react");
  gHaPhysics->Add(hext);
  // Include golden track information
  THaGoldenTrack* gtr = new THaGoldenTrack("H.gtr", "HMS Golden Track", "H");
  gHaPhysics->Add(gtr);
// Add Ideal Beam Apparatus
 // THaApparatus* beam = new THaIdealBeam("IB", "Ideal Beamline");
 // gHaApps->Add(beam);
  // Add Physics Module to calculate primary (scattered) beam kinematics
  THcPrimaryKine* hkin = new THcPrimaryKine("H.kin", "HMS Single Arm Kinematics", "H", "H.rb");
  gHaPhysics->Add(hkin);
  THcHodoEff* heff = new THcHodoEff("hhodeff"," HMS hodo efficiency","H.hod");
  gHaPhysics->Add(heff);

  if (bcmFile.is_open())
    {
      THcBCMCurrent* hbc = new THcBCMCurrent("H.bcm", "BCM current check");
      gHaPhysics->Add(hbc);
      
      gHcParms->Load(bcmParamFile);

    }

  else if (!bcmFile.is_open())
    {
      cout << "BCM Current Module will NOT be loaded . . ." << endl;
    }

  // Add handler for prestart event 125.
  THcConfigEvtHandler* ev125 = new THcConfigEvtHandler("hconfig", "Config Event type 125");
  gHaEvtHandlers->Add(ev125);
  // Add handler for EPICS events
  THaEpicsEvtHandler *hcepics = new THaEpicsEvtHandler("epics", "HC EPICS event type 180");
  gHaEvtHandlers->Add(hcepics);
  // Add handler for scaler events
  THcScalerEvtHandler *hscaler = new THcScalerEvtHandler("H", "Hall C scaler event type 2");  
  hscaler->AddEvtType(2);
  hscaler->AddEvtType(129);
  hscaler->SetDelayedType(129);
  hscaler->SetUseFirstEvent(kTRUE);
  gHaEvtHandlers->Add(hscaler);

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
 // Define crate map
 analyzer->SetCrateMapFileName("MAPS/db_cratemap.dat");
 // Define output ROOT file
 analyzer->SetOutFile(ROOTFileName.Data());
 // Define output DEF-file 
  TString DefTreeFile=Form("UTIL_COMM_ONEPASS/DEF-files/HMS/%s.def",ftype);
  analyzer->SetOdefFile(DefTreeFile);
  // Define cuts file
  //  DefTreeFile=Form("UTIL_COMM_ONEPASS/DEF-files/HMS/%s_cuts.def",ftype);
  DefTreeFile="UTIL_COMM_ONEPASS/DEF-files/HMS/CUTS/hstackana_production_cuts.def";
  analyzer->SetCutFile(DefTreeFile);  // optional
  //
 analyzer->SetSummaryFile(Form("REPORT_OUTPUT/HMS/PRODUCTION/summary_%s_%d_%d.report", ftype, RunNumber, MaxEvent));    // optional
 // Start the actual analysis.
 analyzer->Process(run);
 
 //Determine which template file to use based on ftype user input
 TString temp_file;
 
 if(strcmp(ftype,"hscaler") == 0)
   { 
     temp_file = "hscalers.template";
   }
 else
   {
     temp_file="hstackana_production.template";
   }

// Create report file from template.
 analyzer->PrintReport("UTIL_COMM_ONEPASS/TEMPLATES/HMS/"+temp_file,
		       Form("REPORT_OUTPUT/HMS/PRODUCTION/replay_hms_%s_%d_%d.report", ftype,RunNumber, MaxEvent));
  
 
 
}
