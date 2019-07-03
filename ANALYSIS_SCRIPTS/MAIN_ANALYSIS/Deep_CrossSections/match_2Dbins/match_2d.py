import LT.box as B
import numpy as np

def match_arrays(a1, a2, eps=0.001, return_pairs = False):
    # return arrays
    m1 = []
    m2 = []
    ma = []
    for i1, v1 in enumerate(a1):
        for i2, v2 in enumerate(a2):
            if ( abs(v1-v2)<=eps ):
                m1.append(i1)
                m2.append(i2)
                ma.append( (i1,i2) )
    if return_pairs:
        return ma
    else:
        return m1,m2
# end of match_arrays



f1 = B.get_file('test.txt')
f2 = B.get_file('test2.txt')

ib1 = B.get_data(f1, 'i_b')
ib2 = B.get_data(f2, 'i_b')

m = match_arrays(ib1,ib2, 0.001, True)
print(m)
