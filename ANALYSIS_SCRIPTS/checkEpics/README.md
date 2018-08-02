***Directory Content***

checkEpics.C  : ROOT script to read epics variables from root file, 
	      	and determine their sums and average over all events.
		This is mainly to determine the set/readback current
 		per run number, and write into a CSV file format.

plotMagn.py  : Python script to read .csv file containing epics info 
 	       and plot them. For example, magnet current vs. run number.
	       Also, uses the GetP() function (imported .py code) to convert
	       the currents to a momentum. The Currents/Momentum vs. Run
	       Number are plotted, and also saved in a .csv file.

MagInterpolate.py  : Python script where the GetP() function is defined.
		     This code reads in the tabulated momentum-current 
		     relation in the hms_magnet_data.csv and interpolates
		     these values. And based on the argument, it returns the 
		     momentum of Q1, Q2, Q3, D, or NMR, given an imput current. 

