*********************************
SHMS TRacking Efficiency Studies
*********************************

------------------
February 1, 2019:
------------------
It was found that for runs 3374 and 3377, the Yield Ratio Ydata/Ysimc
was lower than 3288 and 3371.  Looking at the SHMS rates from these runs:
       SHMS_Rate      Trk Eff
3288:  55.2 kHz       0.9856
3371:  43.321 kHz     0.9842
3374:  271.992 kHz    0.9833
3377:  483.35 kHz     0.9815

the tracking efficiencies for the SHMS did not vary much from 98%, even though we had higher rates in the
last two runs.  

This study on the tracking efficinecy involves modifying various parameters in the SHMS/GEN/ptracking.param file
in order to study how would the tracking efficinecy and W yield vary for the data. It may be that the tracking eff. is OK.
but the yield in data is too low, or vice-versa, for the high rate runs. This study will examine this.
Hopefully, this is the main cause of the discrepancy between the first two and last two runs in terms of the Yields ratio.

------------------
February 5, 2019:
------------------
Not much improved in the Yields for run 3377 after changing the parameters in the ptracking.param
Some windows were tightened in the SHMS DC time Window, but this did not improved W by much.  
We decided to look into the Tracking process in hcana. There are three: best chi2, using scintillator, and pruning.
The last one involves making selective cuts on track variables like ytar, xptar, yptar, delta, etc.
This study involves looking at track variables, P.tr.* before selecting pruning parameters.

The end goal is to invrease the number of tracks with the hope of increasing the data Yield at high rates.