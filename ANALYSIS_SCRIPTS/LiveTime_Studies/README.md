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
		   