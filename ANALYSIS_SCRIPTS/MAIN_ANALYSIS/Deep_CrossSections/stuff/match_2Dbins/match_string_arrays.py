#
# find matching string pairs 
#
# return a list of tuples containing the indices of the matching pairs
#
# in general this works with any array of dictionaries
#
# matchin array entriesL (more general)
#
# m1, m2 = match_arrays(a1, a2, eps = 0.001)
#
# m1, m2 contains a list of indices pointing to the matching values
# in a1 and a2
# e.g
# 
# a1[ m1[0] ] is within eps of a2[m2[0]]
#
# alternative
# ma = match_arrays(a1, a2, eps = 0.001, return_pairs=True)
#
# returns a list of tuplese as match
#
def match(set1, key1, set2, key2, eps=0.001):
    # return array
    ma=[]
    for s1 in set1:
        for s2 in set2:
            if ( s1[key1] == s2[key2] ): 
                ma.append( (set1.index(s1), set2.index(s2)) )
    return ma

def match_arrays(a1, a2, eps=0.001, return_pairs = False):
    # return arrays
    m1 = []
    m2 = []
    ma = []
    for i1, v1 in enumerate(a1):
        for i2, v2 in enumerate(a2):
            if ( v1 == v2 ):
                m1.append(i1)
                m2.append(i2)
                ma.append( (i1,i2) )
    if return_pairs:
        return ma
    else:
        return m1,m2
# end of match_arrays
