----------------------
   THcRaster.cxx
----------------------

Parameters READ IN:
    {"fr_cal_mom",           &fFrCalMom,             kDouble},_
    {"frxa_adcpercm",        &fFrXA_ADCperCM,        kDouble}, |
    {"frya_adcpercm",        &fFrYA_ADCperCM,        kDouble}, | ---> (max_frRawAdc + min_frRawAdc)/raster_size (cm) conversion factor from raw ADC to cm.
    {"frxb_adcpercm",        &fFrXB_ADCperCM,        kDouble}, |
    {"fryb_adcpercm",        &fFrYB_ADCperCM,        kDouble},_|
    {"frxa_adc_zero_offset", &fFrXA_ADC_zero_offset, kDouble}, |
    {"frya_adc_zero_offset", &fFrYA_ADC_zero_offset, kDouble}, | ---> (max_frRawAdc + min_frRawAdc)/2. raster offset from center of unrastered beam
    {"frxb_adc_zero_offset", &fFrXB_ADC_zero_offset, kDouble}, |
    {"fryb_adc_zero_offset", &fFrYB_ADC_zero_offset, kDouble},_|
    {"pbeam",                &fgpbeam,               kDouble,0,1},  -->Beam Energy
    {"frx_dist",             &fgfrx_dist,            kDouble},      -->Pos. of FR magnets relative to the target
    {"fry_dist",             &fgfry_dist,            kDouble},
    {"beam_x",               &fgbeam_xoff,           kDouble,0,1},  ---> START: Hall C Epics BPM Values (in cm)
    {"beam_xp",              &fgbeam_xpoff,          kDouble,0,1},
    {"beam_y",               &fgbeam_yoff,           kDouble,0,1},
    {"beam_yp",              &fgbeam_ypoff,          kDouble,0,1},__---> END:   Hall C Epics BPM Values (in cm)                              
    {"bpmxa_slope",          &fgbpmxa_slope,         kDouble,0,1},  |                         
    {"bpmxa_off",            &fgbpmxa_off,           kDouble,0,1},  |
    {"bpmxb_slope",          &fgbpmxb_slope,         kDouble,0,1},  |
    {"bpmxb_off",            &fgbpmxb_off,           kDouble,0,1},  |
    {"bpmxc_slope",          &fgbpmxc_slope,         kDouble,0,1},  |
    {"bpmxc_off",            &fgbpmxc_off,           kDouble,0,1},  |
    {"bpmya_slope",          &fgbpmya_slope,         kDouble,0,1},  | ---->  Parameters obtained from HARP calibration  
    {"bpmya_off",            &fgbpmya_off,           kDouble,0,1},  |
    {"bpmyb_slope",          &fgbpmyb_slope,         kDouble,0,1},  |
    {"bpmyb_off",            &fgbpmyb_off,           kDouble,0,1},  |
    {"bpmyc_slope",          &fgbpmyc_slope,         kDouble,0,1},  |
    {"bpmyc_off",            &fgbpmyc_off,           kDouble,0,1},__|_                                               
    {"bpma_zpos",            &fgbpma_zpos,           kDouble,0,1},    |
    {"bpmb_zpos",            &fgbpmb_zpos,           kDouble,0,1},    | ---> z-positions of BPMs relative to target
    {"bpmc_zpos",            &fgbpmc_zpos,           kDouble,0,1},____|
    {"usefr",                &fgusefr,               kInt,0,1},    ---> flag to use fast raster data in calculating beam positions


 #Raw BPMs positions (What are the units?)   
 BPMXA_raw = atof(fEpicsHandler->GetString("IPM3H07A.XRAW"))  --> Obtained from EPICS, raw BPM position 

 fPedADC[0] = pulseIntRaw

 FRYA_rawadc = pulseIntRaw

 fFrYA_ADC_zero_offset = fPedADC[0]/ fNPedestalEvents   --> Why is this re-defined. It is already read from the gbeam.param file

 #Raster raw ADC in Channels, offset corrected
 fXA_ADC =  FRXA_rawadc-fFrXA_ADC_zero_offset  

 #Convert raster position from Channels to cm
 fXA_pos = (fXA_ADC/fFrXA_ADCperCM)*(fFrCalMom/fgpbeam);    --> Raster positions in cm
 fYA_pos = (-1.)*(fYA_ADC/fFrYA_ADCperCM)*(fFrCalMom/fgpbeam);  --> Why (-1), I forgot.

 #BPM positions using calib parameters from HARP SCANS (0.1 is to convert from mm to cm)
 BPMXA_pos = 0.1*(fgbpmxa_slope*BPMXA_raw + fgbpmxa_off);


OUTPUT to TTree:
{"frxaRawAdc",  "Raster XA raw ADC",                     "FRXA_rawadc"},
{"fryaRawAdc",  "Raster YA raw ADC",                     "FRYA_rawadc"},
{"frxbRawAdc",  "Raster XB raw ADC",                     "FRXB_rawadc"},
{"frybRawAdc",  "Raster YB raw ADC",                     "FRYB_rawadc"},
{"frxa_adc",    "Raster XA ADC",                         "fXA_ADC"},
{"frya_adc",    "Raster YA ADC",                         "fYA_ADC"},
{"frxb_adc",    "Raster XB ADC",                         "fXB_ADC"},
{"fryb_adc",    "Raster YB ADC",                         "fYB_ADC"},
{"fr_xa",       "Raster XA position",                    "fXA_pos"},
{"fr_ya",       "Raster YA position",                    "fYA_pos"},
{"fr_xb",       "Raster XB position",                    "fXB_pos"},
{"fr_yb",       "Raster YB position",                    "fYB_pos"},
{"fr_xbpm_tar", "X BPM at target (+X is beam right)",    "fXbpm_tar"},
{"fr_ybpm_tar", "Y BPM at target (+Y is up)",            "fYbpm_tar"},
{"fr_xbpmA",    "X BPM at BPMA (+X is beam right)",      "fXbpm_A"},
{"fr_ybpmA",    "Y BPM at BPMA (+Y is up)",              "fYbpm_A"},
{"fr_xbpmB",    "X BPM at BPMB (+X is beam right)",      "fXbpm_B"},
{"fr_ybpmB",    "Y BPM at BPMB (+Y is up)",              "fYbpm_B"},
{"fr_xbpmC",    "X BPM at BPMC (+X is beam right)",      "fXbpm_C"},
{"fr_ybpmC",    "Y BPM at BPMC (+Y is up)",              "fYbpm_C"},
{"ebeam_epics", "Beam energy of epics variable HALLC:p", "fEbeamEpics"},