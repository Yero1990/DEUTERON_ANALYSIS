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

   ** Recent DATA/SIMC Missing Momentum Yield for the 80 MeV setting shows an agreement of up to 10% for the
      40-100 MeV range, and from 20-30 on the extremes (statistical)







*************************
Determining Phase Space
& FullWeight
*************************

What are the components of FullWeight, and how is phase space obtained from them?

FullWeight = Weight * Normfac / n_acc.   n_acc: accepted events

For D(e,e'p), the leaf variables are: 

SIMC Tree-------SIMC code--------SIMC file
Weight          main%weight      event.f (search 'LAGET_DEUT')
sig             main%sig         event.f true theoretical cross section
sigcc           main%sigcc       event.f (deForect cross section)
Jacobian        main%jacobian    event.f

The main%weight is broken down as follows:

main%weight = main%sig*main%gen_weight*main%jacobian_corr*main%coul_corr

** main%sig = LagetXsec(vertex)  :: true theoretical cross section from model

** main%gen_weight = main%gen_weight*(Emax-Emin)/(gen%e%E%max-gen%e%E%min)
-----------------------------------
(event.f)
	if (doing_deuterium.or.doing_heavy.or.doing_pion.or.doing_kaon
     >       .or.doing_delta.or.doing_rho.or.doing_semi) then
	  Emin=gen%e%E%min
	  Emax=gen%e%E%max
	  if (doing_deuterium .or. (doing_heavy .and. doing_bound) 
     >	     .or. doing_pion .or. doing_kaon .or. doing_delta .or. doing_rho) then
	    Emin = max(Emin,gen%sumEgen%min)  
	    Emax = min(Emax,gen%sumEgen%max)

(init.f)
	else				!generated ELECTRON energy limits.
	  gen%sumEgen%max = Ebeam_max + targ%Mtar_struck - targ%Mrec_struck -
     >		edge%p%E%min - VERTEXedge%Em%min - VERTEXedge%Trec%min -
     >		VERTEXedge%Trec_struck%min
	  gen%sumEgen%min = Ebeam_min + targ%Mtar_struck - targ%Mrec_struck -
     >		edge%p%E%max - VERTEXedge%Em%max - VERTEXedge%Trec%max -
     >		VERTEXedge%Trec_struck%max - Egamma_tot_max
	  gen%sumEgen%max = min(gen%sumEgen%max, edge%e%E%max+Egamma2_max)
	  gen%sumEgen%min = max(gen%sumEgen%min, edge%e%E%min)  --------
	endif                                                           |
                                                                        |
	else if (doing_deuterium .or. doing_pion .or. doing_kaon        |
     >      .or. doing_rho .or. doing_delta                             |
     >      .or. (doing_heavy.and.doing_bound)) then                    |
	  gen%e%E%min = gen%sumEgen%min  <------------------------------
	  gen%e%E%max = gen%sumEgen%max

------------------------------------

** main%jacobian_corr =  main%jacobian_corr / r**3
--------------------------------------------------------------------------------------
(event.f)
! Determine PHYSICS scattering angles theta/phi for the two spectrometer
! vectors, and the Jacobian which we must include in our xsec computation
! to take into account the fact that we're not generating in the physics
! solid angle d(omega) but in 'spectrometer angles' yptar,xptar.
! NOTE: the conversion from spectrometer to physics angles was done when
! the angles were first generated (except for the proton angle for hydrogen
! elastic, where it was done earlier in complete_ev).
!
.
.
.
C changed to include Deuterium, this should be checked
	if (doing_deuterium .or. doing_heavy .or. doing_pion .or. doing_kaon .or. 
     >      doing_delta .or. doing_semi) then
	  r = sqrt(1.+vertex%p%yptar**2+vertex%p%xptar**2)
	  main%jacobian = main%jacobian / r**3		   !1/cos**3(theta-theta0)
	  main%jacobian_corr = main%jacobian_corr / r**3   !jac. correction factor
	endif
--------------------------------------------------------------------------------------

* main%coul_corr = (1.0+targ%Coulomb%ave/Ebeam)**2
--------------------------------------------------------------
C If using Coulomb corrections, include focusing factor
	if(using_Coulomb) then
	   main%coul_corr = (1.0+targ%Coulomb%ave/Ebeam)**2
	endif
---------------------------------------------------------------

Where does Normfac come into the picture?
----------------------------------------------------------------
(simc.f)

normfac = luminosity/ntried*nevent |  :: luminosity = EXPER%charge/targetfac  :: targetfac=targ%mass_amu/3.75914d+6/(targ%abundancy/100.) * abs(cos(targ%angle))/(targ%thick*1000.)
ntried: number of events thrown into a volume
nevent: number of accepted events that fall within the spectrometer phase space volume

!e- and proton solid angles
domega_e=(gen%e%yptar%max-gen%e%yptar%min)*(gen%e%xptar%max-gen%e%xptar%min)
domega_p=(gen%p%yptar%max-gen%p%yptar%min)*(gen%p%xptar%max-gen%p%xptar%min)

genvol = domega_e

! ... 2-fold to 5-fold.
	if (doing_deuterium.or.doing_heavy.or.doing_pion.or.doing_kaon
     >      .or.doing_delta.or.doing_rho .or. doing_semi) then
	  genvol = genvol * domega_p * (gen%e%E%max-gen%e%E%min)  !general volume if (De,e'p)n
	endif

!The 'general volume' genvol = e-_SolidAngle * p_SolidAngle * (dE') 
	
	normfac = normfac * genvol

!The FINAL Normfac is :: Normfac =  luminosity*(nevent/ntried) * domega_e * domega_p * (gen%e%E%max-gen%e%E%min)
------------------------------------------------------------------
The FullWeight can then be expressed as:

**************************************************************************************************************************************************************************************
*    FullWeight = Weight * Normfac / nevent 
*
*               = main%sig * [(min(Emax,gen%sumEgen%max) - max(Emin,gen%sumEgen%min) )/(gen%e%E%max-gen%e%E%min)] * main%jacobian_corr
*                 * main%coul_corr * (luminosity/ntried) * domega_e * domega_p * (gen%e%E%max-gen%e%E%min)
*
*	       = main%sig * [(min(Emax,gen%sumEgen%max) - max(Emin,gen%sumEgen%min) )] * main%jacobian_corr * main%coul_corr * (luminosity/ntried) * domega_e * domega_p 
*
*
*    The Phase Space can then be expressed by dividing out the main cross section, main%sig
*
*    PhaseSpace = FullWeight / sig = [(min(Emax,gen%sumEgen%max) - max(Emin,gen%sumEgen%min) )] * main%jacobian_corr * main%coul_corr * (luminosity/ntried) * domega_e * domega_p 
***************************************************************************************************************************************************************************************

