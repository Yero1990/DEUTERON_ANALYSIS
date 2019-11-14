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

ROGER BARLOW'S RATIO INTERPREATION:
The Roger Barlow's ratio should be "taken with a grain of salt", and is used mainly as a check that the systematics are NOT
out of control. Some important points are:

** For the Emiss cut, we do expect the ratio to change, as we are changing how much of the radiative tail we include in the cut,
   so a different number of counts is expected. This was found to be large in the deviations in the 80 MeV setting, however, it
   was OK beond 500 MeV/c settings. This could be attributed to the low number of statistics in the larger settings and hence
   larger variances (and statistical fluctuations)

** Some of the ratios might be slightly negative. So one asks, how it can be that when a subset cut cross section is subtracted
   from the cross section of the total set, we end up with negative? Which could only mean that the subset cross section is larger.
   One possible explanation is that this is due to the radiative correction factor becoming smaller with larget cuts, which means
   that a very tight cut (subset) can have a larger cross section due to a larger radiative correction factor.

** If the variances of the two measurements are almost the same, this can give very large values of the ratio, as the denominator
   is the difference in the variances. 

The ratio has many conditions or restrictions under which it applies, and therefore, we must take the results lightly, and only
as a cross check that the systematics are under control.

===================================================================================================================================

SYSTEMATIC UNCERTAINTIES DUE TO CORRECTION FACTORS OF THE DATA YIELD:

Recall, the corrected data yield is:

    Ycorr = f_radCorr * f_BCcorr / (eTrkEff * hTrkEff * tLT * pAbs_corr * tgtBoil_corr * Qtot);

Where each of the following contributes to the systematics:

f_radCorr: radiative correction factor (check how data Xsec vary when PWIA or FSI are used for the correction)
f_BCCorr: Bin-Centering correction factor (check how data Xsec vary when PWIA or FSI are used for the correction)

Each of the following corrections has an associated uncertainty f_corr +/- f_corr_err.  The idea (I had) was to
determine the cross section when the correction is varied within its uncertainty as follows:

dataXsec_+ : when using f_corr + f_corr_err
dataXsec_- : when using f_corr - f_corr_err

From Werner's email, the systematic uncertainty on the cross section from the correction factor f +/- df
is d(sig_exp)_sys = sig_exp * df  (product of experimental cross section times the uncertainty in the correction factor)
If the correction factor is, e.g. f = 1 / e,  df  = (df / de) * de = (-1/e**2) * de, where e is the correction in the denominator of the
cross section, for example, e: pAbs_corr, tgtBoil_corr, . . . etc . . .

The list of the remaining correction factors fot which systematics need to be determined is:
==========
==f_corr==
==========
eTrkEff:        e- tracking efficiency
hTrkEff:        hadron tracking efficiency
tLT:            total live time using EDTM    
pAbs_corr:      proton absorption correction
tgtBoil_corr:   target boiling correction
Qtot:           total BCM4A charge (ask Dave Mack for uncertainty)
f_rad:          radiative corrections based on PWIA of FSI, (so they may NOT be systematics. Have to ask . . .)
f_bc:           bin centering corrections based on PWIA of FSI, (so they may NOT be systematics. Have to ask . . .) 
===================================================================================================================================

KINEMATIC UNCERTAINTIES:

These uncertainties arise from our ignorance of the spectrometer angle and momentum settings:
(Werner as a code which determined the systematics given the average kinematics. His code has the table of values
obtained by varying the kinematics and observing changes in the cross section.)

The systematics should be calculated for:
Ebeam: Beam Energy
shms P:  SHMS (e-) absolute momentum
shms theta_e + eyptar: SHMS (e-) in-plane angle
shms phi_e + xptar: SHMS (e-) out-of-plane angle
hms P: HMS (p) absolute momentum


From Mark Jones, the initial values to try out are:
dEb     =  3.77e-4  [GeV?]         beam energy uncertainty  
dP_shms =  1e-3 (1 x 10^{-3})      absolute SHMS momentum uncertainty
dP_hms  =  1e-3 (1 x 10^{-3})      absolute HMS  momentum uncertainty

dtheta_e =  1 mr                   SHMS in-plane angle uncertainty
dphi_e   =  1 mr		   SHMS out-of-plane angle uncertainty




