==========================================
Hall C D(e,e'p)n Comissioning Experiment
Light-Cone Analysis

C. Yero
March 09, 2021
email (cyero@jlab.org, cyero002@fiu.edu)
==========================================

The light-cone analysis of the deuteron-electrodisintegration
experiment at Hall C consists of simply binning the experimental
and model Laget cross sections in 2D bins of Pt-Alpha,
where alpha is the momentum fraction of the struck nucleon, and
Pt is the transverse momentum of the recoil nucleon relative to
the q-vector.


=============
Directories
=============


average_kinematics_LC : This directory contains ROOTfiles containing the
                        2D averaged kinematics binned in Pt-Alpha. These
			averaged kineamtics were calculated by SIMC, using the
                        quantities at the vertex (no energy loss is needed)
			as well as non-radiative simulation (no rad. corrections needed)

			The relevant histograms in the ROOTfiles have
			the generic name:  "H_kinVar_2Davg_LC"
			where kinVar --> averaged kinematic variable
			so for example, the averaged incident beam energy
			would be:  "H_Ein_2Davg_LC"


average_Xsec_LC:        This directory contains ROOTfiles containing the
			experimental (and model) cross sections which have
			also been calculated (binned) in Pt-Alpha. The ROOTfile
			name indicate which model was used in the calculation
			of the simulated cross sections and the radiative corrections.

			The relevant histograms in the ROOTfiles have
			the generic name: "H_data2DXsec_LC" and
			"H_simc2DXsec_LC"
			These are 2D histograms binned in Pt (y-axis)
			vs. Alpha (x-axis), and the z-value corresponds to the
			average cross section in units of: ub / (sr^2*MeV)


ROOTfiles :             This directory contains ALL the output ROOTfiles from
	  		the full analysis. (See the two above directories for ONLY
			the relevant ROOTfiles)


**Note:  The ROOTfile names located inside the directories described above,
         specify which model (Laget FSI or PWIA) was used in the calculations
	 of the model cross sections, as well as which model was used for
	 radiative corrections. 