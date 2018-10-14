import numpy as np
import matplotlib.pyplot as pl
import glob as G
import LT.box as B


#Code to add an  Angle column to the kinematics file, by
#looping over the runs, getting the cam. angle image, and 
#prompting the user to enter the angle in the picture, which will
#automatically update the kin. file with the inputted angle
#Written by W.B. -October 10, 2017.

# directory for angle images
HMS_dir = './heepElastics_Analysis/HMS_angles/'

kd = B.get_file('./heepElastics_Analysis/hms_kin.dat')

kd_runs = kd['Run'] 

# file name pattern
ang_patt = 'HMS_angle_*.jpg'

ang_files = G.glob(HMS_dir + ang_patt)

# extract the availabel run numbers
runs = [int(af.split('_')[-1].split('.')[0]) for af in ang_files]

# add angles to kd
kd.add_key('theta_c','s')

# add default values
for i,dd in enumerate(kd.data):
    kd.data[i]['theta_c'] = 1000.

# setup the figure
pl.figure(0,figsize=(12,10))
def show_angle(r):
    name = HMS_dir + 'HMS_angle_{:05d}.jpg'.format(r)
    try:
        im = pl.imread(name)
    except:
        print "cannot read ", name
        return None
    pl.clf()
    pl.imshow(im)
    pl.title('Run number : {}'.format(r))
    pl.draw()
    pl.show()
    return im

def show_values(r):
    try:
        ikd = kd_runs.index(r)
        print kd.data[ikd]
    except:
        print "Run ", r, " not in kinematics file"
    return


def add_angle(r):
    iret = show_angle(r)
    if iret is not None:
        try:
            ikd = kd_runs.index(r)
            theta = input("Enter HMS angle for run number {:d} : ".format(r))
            kd.data[ikd]['theta_c'] = theta
        except:
            print "Run ", r, " not in kinematics file"
            return
    else:
        print "nothing to show, set angle to None"
        try:
            ikd = kd_runs.index(r)
            kd.data[ikd]['theta_c'] = 1000.
        except:
            print "Run ", r, " not in kinematics file"
            return

def save_final_file(f):
    kd.save(f)

      
