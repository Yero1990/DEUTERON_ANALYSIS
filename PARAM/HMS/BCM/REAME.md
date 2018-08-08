===============================================
  Brief on How to set BCM CUrrent Thresholds
===============================================

To set a cut on the BCM current, go to: UTIL_COMM_ONEPASS/PARAM/GEN/gscalers.param,
and look for the variable, ex. 'gBCM_Current_threshold = 4.8'

Description: This parameter will set a cut on the beam current, so only the accumulated charge
	     will be counted if the beam current exceeds 4.8 uA . This will only have repercusion
	     in the REPORT FILE, as there will be variables denoted 'blah_cut', which will display
	     the average beam current/charge when the current > 4.8. 
	     
	     The ROOTfile itsels will still have entries that correspond to a beam current < 4.8 uA
	     This is where we use Sanghwa's Physics Module, to determine which which scaler reads
	     fall below this threhshold.

To use Sanghwa's Physics Module:
             * First make sure to load the Module and the BCM parameter the module outputs (if it exists)
	       into the replay script being used to replay the data.

	     * Add the block variable, block H.bcm.* in the DEF-file that the replay script loads, so that
	       the variables from the Module show up in the ROOT tree.

	     * cd to: /hallc_replay/CALIBRATION/bcm_current_map/, and take a look at the README file to learn
	       how to run the bcm script over your ROOT file.

	       The steps should be . . .

	              root [0] .L ScalerCalib.C+ 
		      (Do this once to make shared libraries (or after modifying the marco))

	       	      To run a script:
	       	      > root -l
	       	      root [0] .x run.C("/path/Scaler root output file");

		      This should produce a bcmcurrent_runNUM.param in this directory, which you
		      then must move to PARAM/${SPEC}/BCM/ so that it can be read by the replay script.

		      	       	  		      	   