#Tracking Efficiency STUDIES
#BCM Current is corrected (BCMCurrent.cxx module)
#Live Time is corrected by including only events > 5 uA (bcm current flag==1 cut)

Brief: After taking the data/simc yield ratio for D2 H(e,e'p) it was found the following was found:

#Units:  rate[kHz],   charge[mC],  
#!Run[i,0]/   hms3of4_rate[f,1]/    shms3of4_rate[f,2]/     coin_rate[f,3]/     bcm4a_charge[f,4]/    hms_trkEff[f,5]/     shms_trkEff[f,6]/     cpuLT[f,7]/    tLT[f,8]/    Ydata_to_Ysimc[f,9]/
3288	      0.367		    76.859		    0.107		152.241		      0.9876		   0.9729		 0.980857	0.924374     0.9092		 
3371	      0.277		    44.447		    0.050		52.020		      0.9874		   0.9744                0.988501       0.944654     0.8972
3374	      1.026		    271.992		    0.387		52.575		      0.9892		   0.9620		 0.936735	0.845108     0.8537
3377	      2.415		    588.849		    0.952		41.432		      0.9906		   0.9488		 0.853053	0.764917     0.7615

It seems the driving parameter that is causing a drop in the Yield Ratio is the shms3of4_rate. With higher SHMS rates, the ratio drops from 90% (<100 kHz) to 85% (at ~ 270 kHz) 
and 76% at (~588 kHz).

The ratio is as follows:  R ~ Ydata /[ Ysimc * Weight * charge * htrkEff *ptrkEff * tLT  ]  
To compensate the drop in the ratio, the shms tracking efficiency would have to be smaller than it currently is. Or, the data yield has to increase. To achieve this, one would have
to understand how tracking parameters affect the number of tracks formed, and seek to increase the events with zero-tracks. 

-------
PLAN 1:
-------
The tracking efficiencies studies will consist of trying out different combinations of
tracking parameters along with the Track Fitting method. For example, using the best chi2 method,
how can we optimize the parameters to get a more realistic tracking efficiency?  We are mainly
interested in Run 3377, which is a high rate run, and the ratio of data/simc is 15% away from 0.9
so, we need to lower the tracking efficiency by ~15% somehow, or inrease the number of tracks formed.

We start with the nominal tracking parameters in HMS/SHMS, and will focus on the SHMS tracking parameters. 

---------
NOMINAL:
---------
Track Fitting Method: BEST CHI2
Max # of hits = 25, 25 --> (DC1,DC2)
Max # of focal_plane tracks = 10
Min. # of hits in each spacepoint = 5,5
Min. # of pairs (combos) in each spacepoint = 4,4
Min. separation of distinct spacepoints = 1.2, 1.2 (1.0, 1.0 for HMS)
pstub_max_xpdiff = .2   (stub_xp - stub_x*fRatio_xpfp_to_xfp < pstub_max_xpdiff)

Stubs Criteria (Max. dist between DC1 & DC2 stubs difference)  
ex. |dpos_x| = |(DC1_xstub - DC2_xstub)| < pxt_track_criterion
pxt_track_criterion = 20. [cm]
pyt_track criterion = 5.0 [cm]
pxpt_track_criterion = 0.4 [rad]
pypt_track_criterion = 1.0 [rad]


Conclusion: It seems that changing the tracking parameters did not make much difference in the W yields that would account for the large differences observed in the 
High Rate runs yields.

--------
Plan 2:  
--------

Increasing the Hodoscope fiducial region based on Xfp vs. Yfp of the high rate runs did not make any difference at all. This parameter 
consist of increasing the range of paddles in X-Y hodo planes used as criteria for a good scintillator hit. 
The parameters were present on ptracking.param, and were as follows:

;loscin to hiscin inclusive will be included as "good" scintillator hits. (ORIGINAL)
;  pxloscin  = 4, 4
;  pxhiscin  = 11, 10
;  pyloscin  = 4, 6
;  pyhiscin  = 11, 14
;Fiducial Cuts based on Xfp vs. Yfp for D2 Heep Elastics
  pxloscin  = 4, 4
  pxhiscin  = 11, 11
  pyloscin  = 4, 6
  pyhiscin  = 11, 17


-------
Plan 3: 
-------

Brief: Look at W with cuts on ntrack ==1  and ntrack>1 to see if the multi-tracking
algorithm is causing a problem.

Conclusion: The multi-tracking seems to be working, as the shape of W was the same. It was not smeared out.


----PRUNING METHOD------
IMPORTANT: The pruning method is a way to select the best track when there is more than one track. 
	   The pruning method (on or off) will not affect the tracking efficiency or the number of
	   tracks produced. It can only affect when there are two or more tracks, which one to select
	   and this could affect  the number of events with the proper W. --Email from M.K.Jones


--------
Plan 4:
--------

Brief: Consider electron tracking efficiencies as a single tracking efficiency and multi-tracking efficiency components.
       Using the following formula: 

       e_trk = P1 * e1_trk  + P2 * e2_trk,   where Pi = Probability for a single or multiple particles passing through the Drift Chambers.
       	       	    	      	   	     and   ei_trk = tracking efficiency for a single or multiple tracks

       To estimate the probability of finding multiple tracks, assume the drift chambers have a similar rate to the 1st hodoscopoe plane in front of them, say S1X.
       Using this approximation, then:
       	     
	     P2 = 1 -  e^{-Rt} ~ Rt,  where R ~ S1X Rate, and t = DC Gate Width (found by taking difference between tdc_min_win and tdc_max_win from pdc_cuts.param file)

	     P1 + P2 = 1 ---> P1 = 1 - P2

      The general expression for electron tracking efficiency can then be written as:
      	    
	     e_trk = (1 - Rt)*e1_trk + Rt*e2_trk 


      To determine the single/multiple tracking efficiencies, the CUTS file has been modified to include the different ranges of the total normalized calorimeter energy.
      If one plot this variable, there will typically be two bumps.  The first one, a few order larger than the second. These represent the single and multiple tracks 
      detected by the calorimeter. As multiple tracks will deposit more energy than single tracks.

See Tanja Horn's thesis section on tracking efficiencies. 


**NOTE: The coin_template.def file has been modified to include these calculations.


