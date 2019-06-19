# find the averaged kinematics for all fixed values of theta for a range of kinematics
# and write them into a file for each theta  value. This is later used to calculate theoretical cross sections
# and their averaged reduced values for overlapping kinematics
import numpy as np
from LT.datafile import dfile

import os, sys, getopt
import os.path as p

import pdb


#----------------------------------------------------------------------
def remove_duplicates(array):
    na = []
    for a in array:
        try:
            na.index(a)
        except:
            na.append(a)
    return na
        
#----------------------------------------------------------------------
def find_duplicates(np_array):
    # np_array is a numpy array
    # return a list with np_array values that contain no duplicates and a
    # corresponding list of indices pointing to identical values in np_array
    array_no_duplicates = remove_duplicates( list(np_array) )
    # sort the array 
    array_no_duplicates.sort()
    index_list = []
    for a in array_no_duplicates:
        in_dup = np.where(np_array == a)[0]
        index_list.append( list(in_dup) )
    return array_no_duplicates, index_list

        
#----------------------------------------------------------------------
def make_key_list(keys):
    klist = ''
    for k in keys[:-1]:
        klist += k + ':'
    klist += keys[-1:][0]
    return klist

#----------------------------------------------------------------------
def get_data_array(set, kin):
    kin_name = []
    keys = set.get_keys()
    klist = make_key_list(keys)
    # new version of data file returns numpy arrays by default
    # here I need a list
    data = list(set.get_data_list(klist))
    for i,v in enumerate(data):
        kin_name.append(kin)
    # add the kinematics name
    return keys, data, kin_name



#----------------------------------------------------------------------
def get_filename(f):
    dir,full_name = p.split(f)
    name,ext = p.splitext(full_name)
    return (dir, name, ext)
#----------------------------------------------------------------------

# default values

# default file name fragments
datadir = "./"
output_dir = './av_kin_theta/'
output_file_head = 'theta'
output_tail = '.data'
head = 'kin_av_TP_'
tail = '.data'

#------------------------------------------------------------
def usage():   # describe the usage of this program
   print "\nusage: find_all_kin_theta_fixed.py [-options] kinematics_file \n"
   print "options:      -? this message "
   print "              -d directory of averaged kinematics"
   print "                 (./)"
   print "              -i input filename start"
   print "                 (kin_av_TP_)"
   print "              -e input filename end"
   print "                 (.data)"
   print "              -D directory of output files"
   print "                 (./av_kin_theta/)"
   print "              -o output file name start"
   print "                 (theta)"
   print "              -E output filename end"
   print "                 (.data)"
   
#------------------------------------------------------------

#------------------------------------------------------------
# commandline arguments

args = sys.argv[1:]  # argument list w/o program name
#------------------------------------------------------------
# handle options
options = "o:d:D:i:e:E:?"  # the ones following the colon require an argument
kinematics_files = None
try:
   options, arguments = getopt.getopt(args, options)

except getopt.GetoptError, (msg, opt) :   
   
   # print help information and exit:
   print "ERROR in option : ",  opt, " reason: ", msg
   usage()
   sys.exit(2)

# handle the option values
for o, v in options:
    if o == "-?":
        # help
        usage()
        sys.exit(2)
    if o == "-d":
        datadir = v
    if o == "-D":
        output_dir = v
    if o=="-o":
        output_file_head = v
    if o=="-i":
        head = v
    if o=="-e":
        tail = v
    if o=="-E":
        output_tail = v

#------------------------------------------------------------
# create a list of data files
#------------------------------------------------------------
dtr = np.pi/180.

# if nothing is given
if ( (len(arguments) != 1) & (kinematics_files == None) ):
     usage()
     sys.exit('you need to enter the name of at least 1 kinematics file ! \n')
#
kin_f = dfile(arguments[0])
#------------------------------------------------------------
init = True

keys0 = []
# loop over kinematics
for i, kk in enumerate(kin_f.data):
    kin = kk['kin'].strip()
    # kinematics file
    kf = datadir + head + kin + tail
    kin_data = dfile(kf)
    print 'working on : ', kf
    if init:
        keys0, full_array, all_kin_names =  get_data_array(kin_data, kin)
        init = False
    else:
        keys, array, kin_name = get_data_array(kin_data, kin)
        if keys == keys0:
            full_array += array
            all_kin_names += kin_name
        else:
            print 'cannot add data from : ', kf, ' keys are different!'
            continue
# full_array contains all data
np_full_array_unsorted = np.array(full_array)
# all the corresponding kinematic names
np_all_kin_names_unsorted = np.array(all_kin_names)    
# select the indices for certain variables in the general array
i_theta = keys.index('xb')
i_pm = keys.index('yb')
i_pm_mc = keys.index('pm_mc')
i_pm_pm = keys.index('pm')
# sort the array for ascending pm_mc values, is_pm is the array of indices that sorts the array
# is_pm = np.argsort(np_full_array_unsorted[:,i_pm_mc])
# using this sort variable. This pm agrees better with Misak's calculation
is_pm = np.argsort(np_full_array_unsorted[:,i_pm_pm])

np_full_array = np_full_array_unsorted[is_pm]
np_all_kin_names = np_all_kin_names_unsorted[is_pm]   
# look for different values of theta (here the bin center value)
atheta = remove_duplicates(np_full_array[:,i_theta])
atheta.sort()

# loop over all available angles
for theta_sel in atheta:
    
    # in_angle contains an array of indices
    in_angle = np.where(np_full_array[:,i_theta] == theta_sel)[0]
    
    # sel_array is a subset of the full array with the selected theta values
    sel_array = np_full_array[in_angle,:]
    
    # kin_names contains the corresponding kinematics names
    kin_names = np_all_kin_names[in_angle]
    
    # pm_array contains the pm_value array w/o duplicates
    # pm_indices contains lists of indices for each pm_array value
    pm_array, pm_indices = find_duplicates(sel_array[:, i_pm])
    # pm_values is just a numpy array of pm_array
    pm_values = np.array(pm_array)
    print 'found the following im values for theta = ', theta_sel
    for i,p in enumerate(pm_values):
        pm_a = sel_array[ pm_indices[i], i_pm_mc]
        print p, ' indices : ', pm_a, kin_names[ pm_indices[i]], np.average(pm_a)
    #
    # write output
    output_file = "%s_%0.2f%s"%(output_file_head, theta_sel, output_tail)
    print "writing : ", output_file
    out = open(output_dir + '/' + output_file,'w')
    # #header information
    header = \
    """
    # average kinematics results
    # averaged kinematic varibles used as input to calculate the averaged 
    # kinematics: Ei, omega, th_e, pf # variables with _mc attached are from histograms not calculated
    # phei: hor. angle of scattered electron in lab coord system (see MCEEP doc.) 
    # thei: vert. angle of scattered electron in lab coord system (see MCEEP doc.) 
    # phpi: hor. angle of ejected hadron in lab coord system (see MCEEP doc.) 
    # thpi: vert. angle of ejected hadron in lab coord system (see MCEEP doc.) 
    #! th_nq_mc[f,0]/ th_nq_calc[f,1]/ pm[f,2]/ Ei[f,3]/ omega[f,4]/ th_e[f,5]/ q_lab[f,6]/ pf[f,7]/ pm_mc[f,8]/ q_mc[f,9]/ th_pq_cm[f,10]/ beta_cm[f,11]/ phi[f,12]/ cos_phi[f,13]/ cos_2phi[f,14]/ Q^2[f,15]/ sin_phi[f,16]/ phei[f,17]/ thei[f,18]/ phpi[f,19]/ thpi[f,20]/ pm_b[f,21]/ ix[i,22]/ iy[i,23]/ pm_b_av[f,24]/ tot_err[f, 25]/ kin[s,26]/
	"""
    out.write(header)
    for i,p     in enumerate(pm_values):
        kin     = kin_names[ pm_indices[i]]
        pm_a = sel_array[ pm_indices[i], i_pm_mc]
        pm_b_av = np.average(pm_a)
        for i,l in enumerate( sel_array[ pm_indices[i], :] ):
            cur_kin = kin[i]
            # get the total error if it is avaliable in the input file
            try:
                tot_err = l[keys.index('tot_err')]
            except:
                tot_err = 0.
            ll = "%r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %r %d %d %r %r %s \n"%(\
                l[keys.index('xb')],\
                    l[keys.index('th_nq_calc')],\
                    l[keys.index('pm')],\
                    l[keys.index('Ei')],\
                    l[keys.index('omega')],\
                    l[keys.index('th_e')],\
                    l[keys.index('q_lab')],\
                    l[keys.index('pf')],\
                    l[keys.index('pm_mc')],\
                    l[keys.index('q_mc')],\
                    l[keys.index('th_pq_cm')],\
                    l[keys.index('beta_cm')],\
                    l[keys.index('phi')],\
                    l[keys.index('cos_phi')],\
                    l[keys.index('cos_2phi')],\
                    (l[keys.index('q_lab')])**2 - (l[keys.index('omega')])**2,\
                    l[keys.index('sin_phi')],\
                    l[keys.index('phei')],\
                    l[keys.index('thei')],\
                    l[keys.index('phpi')],\
                    l[keys.index('thpi')],\
                    l[keys.index('yb')],\
                    l[keys.index('ix')],\
                    l[keys.index('iy')],\
                    pm_b_av, \
                    tot_err, \
                    cur_kin
                    )     
            out.write(ll)
    #
    out.close()
# all done

