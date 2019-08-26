*********************
SYSTEMATICS STUDIES
*********************

Systematics studies are done on the deuteron data to determine which are the
systematic effects of most relevance and determine their associated systematics
uncertainties.  As a first step, the nominal cuts applied on both data and simc
are summarized, and used as a starting point to study the effects of cuts variations. 

------------------------

***SYSTEMATICS STUDIES (PART 1): CHECK NOMINAL CUTS***

Brief: The nominal cuts applied to the Deuteron Data are examined, and used as starting point for these studies.

==July 30, 2019==

The nominal cuts applied to the data and simc are summarized, by plotting each of the histograms
on which a cut is made will all other cuts except that histogram cut. 

DATA/SIMC: 80 MeV
Model: Laget PWIA
Radiative effects (not corrected)

NOMINAL CUTS APPLIED: 
Em:        (-20, 40) MeV          **    
h_delta:   (-8,8)%  
e_delta:   (-10,22)   
ztar_diff: (-2,2) cm              **
Q2:        (4, 5) GeV2  
theta_nq:  (35, 45) deg
HMS Coll:  geometry cut on coll.  **

#Cuts that Only Apply to data
SHMS Calorimeter EtotTrackNorm: (0.7, 5.)          **    
epCoinTime:                     (10.5, 14.5) ns    **

** The cuts with this (**) mark are relevant for systematic studies, and will be varied at different ranges or either turned ON/OFF

---IMPORTANT POINTS---- 
1) The Q2 and theta_nq represent different bins in which to plot the Xsec, but are NOT actually part of systematics.

2) The HMS/SHMS delta cut defines our good acceptance region in which the reconstruction matrix is relatively well known,
   so we do NOT vary these cuts and thus there are no associated systematics.

3) If a histogram from the systematics studies is in general very clean, then there might NOT be a need change the cuts, but
   rather, turn the cuts ON / OFF.    

----------------------


Each of the histograms were plotted with all the cuts above except its own cut. 

***SYSTEMATICS STUDIES (PART 2): VARY NOMINAL CUTS***

Brief: The variation in the data Xsec is studied by varying each cut from its 
mominal value. For each cut that is varied, the remaining cuts stay at the nominal
value. In general, if the analysis is done correctly, there should NOT be significant 
variation in the difference between Xsec when different cuts are applied. The approach to determine (or quantify) 
how large is a "significant difference" is Roger Barlow's approach in "Systematic Erros: Facts and Fictions".

---ROGER BARLOW'S APPROACH---
Consider a measurement done two different ways (i.e. apply different cuts). Let the measurements and its uncertainty be:
(a1, sig_1) and (a2, sig_2) where one of the measurements is a subset of the other and where 'sig' is the error bar or standard deviation of the measurement 'a'.
The difference, delta = a1 - a2 then has an associated uncertainty, (sig_delta)**2 = sig_1**2 - sig_2**2  (this is the difference of their variances)
Then, if : 
      	   delta / sig_delta < 2 to 4 (or the difference in the measurements is from 2 to 4 standard deviations)


The dataXsec vs. variational cuts was plotted for all Pmiss of a given theta_nq bin as well, in order to determine how large were
the variations in the cross section as a function of the different cuts. 


-----CUT RANGES STUDIED-----
Missing Energy (Emiss): (-20, 30),  (-20, 40), (-20, 45), (-20, 50), (-20, 60), (-20, 80) MeV
ZtarDifference : |Ztar Diff.| < n cm,   where n = 0.5, 1.0, 1.5, 2.0, 2.5, 3.0
HMS Collimator: scale n, where n = 1.1, 1.0, 0.9, 0.8     **scale refers to the collimator geometrical cut to match its actual size (1 means a collimator cut of its actual size)

SHMS Calorimeter EtotTrackNorm: cut ON: (0.7, 5.), cut OFF  
Coincidence Time Cut:   Cut ON: (10.5, 14.5) ns, cut OFF   
==> If the variable on which the cut is being made is sufficiently clean, it is enought to turn the cut on/off