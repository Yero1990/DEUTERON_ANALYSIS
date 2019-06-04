****************
 MAIN_ANALYSIS
****************

This directory contains relevant code to analyze the
Deuteron-Electro-Disintegration Experiment (E12-10-003).


Comments / Discussions on Known Analysis Issues:

H(e,e'p):

   ** The elastic data for the E12-10-003 data / simc  ratio shows the
      first two data points (runs 3371, 3288) agree to very well (< 1%)
      after including all the corrections to the data yield. The last two
      runs show a drop (~2 % for 3374, and ~ 10% for 3377) as a function
      of SHMS 3/4 rate.  There is a possibility that the tracking efficiency
      at high rates is NOT yet well understood, and be resulting in a larger
      efficiency than normal. 

   ** Even though the elastic data was optimized in reconstruction delta and
      Ytar, and some offsets / corrections were applied to aligned data/simc,
      run 3377 still has an offset. This should be looked at in more detail
      later on. 

   ** When a missing energy cut is applied to the data/simc, W events in the
      main peak of data decrease, whereas in SIMC, they do NOT. It was found
      that the issue causing this is energy loss at the collimator in data.
      That is, protons from H(e,e') in HMS that were in coin. with e- in SHMS,
      interact pass through or near the edges of the hms collimator and make it to the
      Hodo to form a trigger. This events correspond to a W underneath the main peak 
      as calculated from the electron side. From the proton side, however, the corresponding
      missing energy is far from the main peak (> 40 MeV), so a cut on missing energy would cut
      out these proton events with large missing energy, but corresponding to the event underneath 
      W.  In W vs. Emiss plot, this phenomenon would show up as a horizontal band.
      
      In SIMC, however, energy loss in the collimators is NOT simulated. Mark is working on
      translating it to deut_simc, so we can apply it to SIMC. Hopefully, when a cut is made
      on SIMC missing energy, it would affect W events in SIMC as well, and there would be a 
      consistency in the events cut out in both data/simc W. 



D(e,e'p)n:

   ** Last work was presented at MIT, showing preliminary cross section results.
      Work still needs to be done.
