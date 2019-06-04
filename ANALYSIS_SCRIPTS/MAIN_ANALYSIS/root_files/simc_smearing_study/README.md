*********************
SIMC Smearing Study
*********************

Study the effect of adding additional smearing on the reconstructed quantities
delta, yptar, xptar for both HMS/SHMS on the DATA/SIMC ratios Pmiss_data/Pmiss_simc

The general cuts applied were:
Emiss < 40 MeV
HMS Delta: (-8,8)%
SHMS Delta: (-10,22)%
W: (0.85, 1.05)
HMS Collimator Cut

H(e,e'p):
---------------------
delta_smearing study
---------------------
The SHMS/HMS Delta smearing parameter was varied in simc:
* no smear
* 0.001
* 0.005
* 0.01
* 0.05
The Ytar, X'tar, Y'tar smearing were kept at 1.0e-8 (no smearing)

No significant difference was observed in the Pmiss simc.

---------------------
Y'tar smearing study
---------------------
The SHMS/HMS Y'tar smearing parameter was varied in simc:
* no smear
* 3 mr:  largely affects W, PmissX, Pmiss
* 2 mr
* 1 mr
* 0.5 mr
* 0.1 mr

---------------------
X'tar smearing study
---------------------
The SHMS/HMS X'tar smearing parameter was varied in simc:
* no smear
* 20 mr
* 3 mr  
* 2 mr
* 1 mr
* 0.5 mr
* 0.1 mr

---------------------
Ytar smearing study
---------------------
The SHMS/HMS Ytar smearing parameter was varied in simc:
* no smear
* 3 cm  
* 1 cm
* 0.5 cm
* 0.1 cm