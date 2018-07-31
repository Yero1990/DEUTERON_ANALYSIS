***Directory Content***

checkEpics.C  : ROOT script to read epics variables from root file, 
	      	and determine their sums and average over all events.
		This is mainly to determine the set/readback current
 		per run number, and write into a CSV file format.

plotMagn.py  : Python script to read .csv file containing epics info 
 	       and plot them. For example, magnet current vs. run number.

