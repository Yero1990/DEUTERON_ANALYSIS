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
Em:        (-20, 40) MeV  
h_delta:   (-8,8)%  
e_delta:   (-10,22) 
ztar_diff: (-2,2) cm
Q2:        (4, 5) GeV2
theta_nq:  (35, 45) deg

#Cuts that Only Apply to data
SHMS Calorimeter EtotTrackNorm: (0.7, 5.)   
epCoinTime:                     (10.5, 14.5) ns

Each of the histograms were plotted with all the cuts above except its own cut. 

***SYSTEMATICS STUDIES (PART 2): VARY NOMINAL CUTS***

Brief: The variation in Missing Momentum Yield Ratio (Pm_data/Pm_simc) is studied by varying each cut from its 
mominal value to either a "loose" or "tight" cut. For each cut that is varied, the remaining cuts stay at the nominal
value. The variation in the ratio is related to the "systematic effects" for which a systematic error must be determined. In general, if the analysis is done correctly, there should NOT be significant variation in the ratio when different cuts are applied. The approach to determine (or quantify) how large is a "significant difference" is Roger Barlow's
approach in "Systematic Erros: Facts and Fictions".

Consider a measurement done two different ways (e.g. apply different cuts). Let the measurements and its uncertainty be:
(a1, sig_1) and (a2, sig_2) where 'sig' is the error bar or standard deviation of the measurement 'a'.
The difference, delta = a1 - a2 then has an associated uncertainty, (sig_delta)**2 = sig_1**2 - sig_2**2  (this is the difference of their variances)
Then, if delta / sig_delta > 2 (or the measurement difference is greater than two standard deviations) then it is considere a significant difference.


==July 31, 2019==

The nominal cuts and their variations are in "../analyze.C" main analysis code. The cuts are summarized below:

These systematic studies were done for a Q2: (4, 5) GeV^2 and theta_nq: (35, 45) deg

:: Missing Energy [GeV]  :: nominal: (-0.02, 0.04)  loose: (-0.04, 0.06)  tight: (-0.01, 0.03)  
:: HMS Delta  [%]        :: nominal: (-8, 8)        loose: (-10, 10)      tight: (-5, 5)
:: SHMS Delta [%]        :: nominal: (-10, 22)      loose: (-3, 2)        tight: (-1.5, 1)
:: Ztar Diff  [cm]       :: nominal: (-2, 2)	    loose: (-4, 4)	  tight: (-1, 1)   **Might want to check loose cut, as there seems to be bkg in data (but not in simc)
:: etotTrkNorm           :: nominal: (0.7, 5)       loose: (0.8, 5)       tight: (0.9, 5)   ONLY APPLIES TO DATA
:: Coin. Time [ns]       :: nominal: (10.5, 14.5)   loose: (5, 20)        tight: (12, 14)   ONLY APPLIES TO DATA
:: HMS Collimator [cm]   :: nominal: scaled by 1    loose: scaled by 1.3  tight: scaled by 0.7   (hexagonal cut is scaled)        

NOTE: For the cuts that ONLY apply to data, the ratio was R = Pm_data / Pm_simc_nominal, 
where Pm_simc_nominal is the SIMC Yield with all nominal cuts applied.
For the rest of the quantities, the exact same cuts were applied on data and simc. 

-------------------------------------------------------------------

