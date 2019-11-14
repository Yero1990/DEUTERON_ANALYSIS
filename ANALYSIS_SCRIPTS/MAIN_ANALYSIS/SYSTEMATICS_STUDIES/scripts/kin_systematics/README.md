This directory contains useful code to determine the systematic uncertainty
on kinematic variables such as beam energy, spectrometer angles and momenta.

How to run the code:

differ3.f  --> main code ( DO NOT TOUCH !)

run_differ_general_v2.py ---> run differ3.py (steering scripts. might need to modify to read avg. kin. files)

analyze_differ.py (the relative errors on the beam, spectrometer momenta and angles are input here!),  
sig_thb (vertical beam direction uncertainty)
sig_phb (horizontal beam direction uncertainty)

sig_th_e (in-plane electron angle uncertainty)
sig_ph_e (out-of-plane electron angle uncertainty)

sig_ef: how well do we know final electron energy
sig_E:  how well do we know the beam energy


Compile the code to get differ3 executable (ONLY NEED TO DO THIS ONCE!)
1) make -f differ3.mak   #this will produce an executable, ./differ3, which is run by
   the steering script

The steering script will read the avg. kin file line by line and
overwrite the differ.in / differ.out for each (thnq, pm) bin in each line of avg. kin. file
look in differ.in for input of average kinematics.
look in differ.out for the derivatives  (systematics results)

2) To run the code, do:
   ipython run_differ_general_v2.py pm_set model data_set
   (example: ipython run_differ_general_v2.py 580 fsi 2)

At the end, the average kinematics file will be sent to ./kin_syst_results with an additional header at the
end called 'tot_err'.  This represents the systematic uncertainty on the the kinematic variables added in
quadrature.  An additional summary files will be sent to ./summary_files, representing the input/output
files used to calcuate the systematics. These are the kinematics for each bin (input) and the derivatives
of the cross sections with respect to each of the kinematics (output). In the /summary_files dir. there is also 
a .txt file containing the individual Xsec derivatives for each (thnq, Pm) bin, as well as the individual Xsec
relative error for each kinematic variable. The advantage of this .txt file is that it wan be used to plot
quickly the derivatives or relative systematics errors vs. Pmiss.



=================================
=Comparison of Derivatives Study=
=================================
Date: September 10, 2019

Brief: This study consists of comparing the kinematic derivatives calculated using Werner's code to those determined from SIMC.
       Each kinematic variable is changed individually to study its effect on the cross section.

In Werner's code: 
   The relative uncertainty of the kinematic variable in question is set to a value (how well we know the kinematic), and the rest are set to zero
   meaning, we think we know the rest perfectly.  (See analyze_differ.py)  Running Werner's code will produce a table of derivative with derivatives
   for each kinematic bin (Pm, th_nq) in units of %/mr or %/MeV,  meaning, how much (percentege-wise) each cross section changes with a +1mr or +1MeV
   change in the kinematic variable.

In SIMC: 
   To determine the derivatives via SIMC, if we were to compare the cross sections in DATA/SIMC by varying the cross section by a certain amount, 
   the issue is that in DATA, we may already be off in our kinematics, even before we change by 1mr or MeV, so when we take the difference in cross
   section, it may not truly represent a change /mr or /MeV, but it may be more.  ^
                                                                                  |
   **THIS IS WHY IT WAS DECIDED TO CALCULATE THE DERIVATIVES USING SIMC ONLY** ----

   To determine the derivatives using SIMC:

   ** Treat SIMC as PSEUDO-DATA (SIMC with radiative effects ON), and get the cross section the same as one would get using real data. That is, by dividing the Yield by SIMC PhaseSpace
      where SIMC PhaseSpace. One would have SIMC rad/norad at the nominal kinematic setting, and apply the radiative corrections to the SIMC PSEUDO-DATA, just
      as one would to the real data. The pseudo-data cross section at the offset kinematics are then compared to the pseudo-data cross sections at the nominal
      kinemaics, and the change would have to be per the amount we changed the kinematics.

      % change in Xsec / (MeV or mr) = (Xsec_Nominal - Xsec_KinOffset)/Xsec_Nominal  * 100

      The derivative is nothing but the relative change in cross section, in percent.


      **NOTE: When the kinematic offset is compared to the nominal, the kinematic is changed two ways. 
      1) Keep the kinematics at the nominal setting in the input file (thrown) and apply the (1mr or 1MeV) offset at the reconstruction stage of the pseudo-data.
      	 *** We simulate an offset in the reconstruction to mimic what actually happens in the experiment, when there is an offset in the spectrometer.

      2) Vary the kinematics in the input file (thrown) and correct for in the reconstruction stage of the pseudo-data.
      	 *** Varying the input (thrown) will give a completely different cross section(opposite to nominal), but we reconstruct at the correct kinematics. This
	     is to mimic what would happen if apply an offset, when there should NOT be one. 
      
      The comparison between Werner's and SIMC derivatives will give us a better idea of the sensitivies in the cross section, from each kinematic variable.
      These are just used as cross-checks that the derivatives behave as we expect when kinematics are changed. Then we can determine the true kinematic
      relative uncertainties from the H(e,e'p) data.

      
    
    