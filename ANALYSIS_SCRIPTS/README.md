Brief: This directory contains information/relevant codes about the Hall C 
livetime studies performed at different DAQ buffer levels during during the
July 2018.

===Directory/Code Structure===
replay_scalers.py   : Python script to perforem scaler replays over a range of runs.
		      The scaler report files produced will have the relevant information
 		      necessary to perform the live time studies.


livetime.py         : Python script containing defined functions [getLiveTimes(), dt_nonextended(), dt_extended()] 
		      to get the relevant info for live time studies from the report files, and calculate the 
		      non-extended (buffer level 1) and extended (buffer level > 1) live times from a model.
		      The main function, main(), call the above-mentioned functions. Plots of live-times vs. rate
		      from data/model are made.

(s)hms_livetime.csv : CSV file (created by getLiveTimes()) containing live-time information from the report files. 
		   

Discussion on Buffer Levels:

---|-| |-     |---
   | |_|      |
   |__________|        

Figure: The wide pulse represents Buffer Level 1 BUSY, which represents the intrinsic time
	for the single board computer (SBC) on the crate to transfer the data from the modules
	buffers to itself and to CODA. After this time, the TI is able to receive another trigger,
	generating another BUSY. For HMS, it is ~ 155-165 us wide.  

	The narrow pulse represents Buffer Level > 1 BUSY, which is the intrinsic time for the
	modules (ADCs/TDCs) to transfer data from its front end to its internal buffer (~ 190 ns, measured
	for the HMS). For example, in buffer level 10, the module waits for 10 triggers before the emitting a
	short BUSY.   

It was observed in the data that at a rate of ~10 kHz, the live-times stayed at ~60 %, with no improvement over the
range of Buffer Levels studies (1-10). This issue brings up one of many bottlenecks that we encounter during these DAQ studies.
This bottleneck refers to the data transfer rate limitations, in which no matter how fast the TI is able to process triggers,
the transfer rate to CODA hits a limit at some point below 10 kHz. From the long BUSY, this limit can be determined by: 
1 / (155-165 us) = 6.0 - 6.4 kHz of data transfer rate.  


Discussion on TDCs Internal Clocks:

______        ________________________________________________________ L1 Accept
      |      |
      |      |
      |______|

____________________________________________________	    ___________ Ref. Time
						    |      |
						    |      |
						    |______|

     |----25ns-----|
______	     ______	  ______       ______     ....   .....      .....       TDC 1190 40 MHz (25 ns) Internal Clock				   
      |     |      |     |      |     |
      |     |      |     |      |     |
      |_____|	   |_____|	|_____|				    

_____   __   __   __   __   ___  . . . . . . .           .....                  TDC 1190 10 GHz (0.1 ns) Internal Clock
     | |  | |  | |  | |  | |
     |_|  |_|  |_|  |_|  |_|
    

Before modern TDCs, old fastbus modules, had a level 1 accept (accepted trigger) being fed into their front end, and acted as the
start time, and was measured relative to the stop signal (fron-end input detector sgnals), and was therefore, a delta in the TDC distribution. 

On modern TDCs (Caen 1190), when the L1 accept comes in the TDC, it initiates data readout. The detector signal coming in the front-end of the
module serves as the 'TDC Start' (synched with the 40 MHz clock). The reference time (copy of the trigger before L1 acc.) will serve as the 'TDC Stop' (synched
with the high resolution, 10 GHz clock). The 'TDC Start' triggers on the leading edge of the next 40 MHz clock cycle, which means the pulse
could have landed anywhere in a 25 ns range between the previous and next clock cycle. As a result, a 25 ns jitter arises intrinsically, 
when one tries to take the difference between the TDC Start and Stop signals. 