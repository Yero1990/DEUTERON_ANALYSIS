This directory contains the relevant codes to calculate and 
plot systematics from various sources:

-------------------------
---cuts_systematics.py---
-------------------------
This code calculates Roger Barlow's ratio, R, from the comparison of
data cross sections at different cut settings.


-------------------------
--fcorr_systematics.py---
-------------------------
This code calculates Roger Barlow's ratio R, from comparison of 
data cross sections when using PWIA or FSI model for the radiative correction,
and radiative + bin-centering corrections. 

-------------------------
--/kin_systematics DIR---
-------------------------
This directory will use Werner's code to estimate systematics of the
kinematic variables (beam energy, spectrometer angles and momenta) using the average 
kinematics and using also as input the absolute uncertainties in each of these 
kinematics.


----------------------
--plot_utils.py-------
----------------------
Python plotting utilities functions to facilitate the plotting of
systematics.


---------------
-calc_syst.py-
--------------
Code to determine the systematics due to correction factors
on the data cross section. The code reads the report file
output from analyze.C code, to get the values per run, and
ultimately calculate the weighted average and it uncertainty
from each correction factor. The uncertainties are then added
in quadrature to get a final systematic for each data set.
The individual contributions and final uncertainty will be written
as additional columns to the cross section data files (the bin-center corr. files)
Maybe, a copy of the file with the '_syst' extension is better.