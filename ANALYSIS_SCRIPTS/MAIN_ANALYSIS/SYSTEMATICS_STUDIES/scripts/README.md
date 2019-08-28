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
--kin_systematics.py---
-------------------------
This code (yet to be written), will use Werner's code to estimate systematics of the
kinematic variables (beam energy, spectrometer angles and momenta) using the average 
kinematics and using also as input the absolute uncertainties in each of these 
kinematics.


----------------------
--plot_utils.py-------
----------------------
Python plotting utilities functions to facilitate the plotting of
systematics.