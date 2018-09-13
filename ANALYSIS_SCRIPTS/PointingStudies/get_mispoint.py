import numpy as np
import scipy as sp
import sys

th = 13.5

horizontal_mispoint = 0.52 - 0.012*th + 0.002*th*th
vertical_mispoint = 2.37 - 0.086*th +0.0012*th*th

print ('horizontal-mispointing = ', horizontal_mispoint, 'mm')
print ('vertical-mispointing = ', vertical_mispoint, 'mm') 
