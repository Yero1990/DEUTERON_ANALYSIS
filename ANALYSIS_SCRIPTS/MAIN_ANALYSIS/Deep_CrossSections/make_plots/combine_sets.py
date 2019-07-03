import LT.box as B
import numpy as np
import matplotlib.pyplot as plt

ib1 = np.array([44, 104, 220])
ib2 = np.array([44, 104, 320])

xsec1 = np.array([1, 2, 3])
xsec1_err = np.array([0.02, 0.1, 0.03])
xsec2 = np.array([2, 9, 1])
xsec2_err = np.array([0.01, 0.02, 0.05])



def combine_sets(ib1 = [], ib2 = [], arr1 = [], arr1_err = [], arr2 = [], arr2_err = []):

    print('calling combine sets')
    
    NUM = 0.
    DEN = 0.

    #Loop over 2d bins in arr1
    for i, ib in enumerate(ib1):
        #Loop over 2d bins in arr2
        for j, jb in enumerate(ib2):
            #Check if 2d bins match
            if((ib-jb)==0):
                print('Found matching 2d bins')
                print('calculating weighted average')
               
                #function to take the weighted average two numpy arrays
                NUM =  (xsec1[i]/xsec1_err[i]**2) + (xsec2[j]/xsec2_err[j]**2)
                DEN =  (1.0/xsec1_err[i]**2) + (1.0/xsec2_err[j]**2)


                #Get Weighted average
                weighted_avg = NUM / DEN
                print('Weighted Avg = ', weighted_avg)
    #return weighted_avg
    

def main():
    print('calling main function')

    combine_sets(ib1, ib2, xsec1, xsec1_err, xsec2, xsec2_err)


if __name__ == "__main__":
    main()




