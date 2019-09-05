import numpy  as np
dtr = np.pi/180.

sigmas  = {\
    # electron arm
    'sig_the':1.0, \
    'sig_phe':1.0, \
    # proton arm
    'sig_thp':1.0, \
    'sig_php':1.0, \
    # beam directopm
    'sig_thb':0., \
    'sig_phb':0., \
    
    # final electron energy relative sigma
    'sig_ef':1.0e-3, \
    # incident beam
    'sig_E':1.0e-3
        }

def get_sig_tot(differ_file='',  ftable_name='', ftable_bin = np.array([]), variances = sigmas, print_all = False):
    data = open(differ_file).readlines()
    found = 0
    
    # This is where you enter the estimated uncertainties
    # sigma in mr 
    #electron arm uncertainties
    #sig_the = 1.    #electron theta_e (in-plane, horizontal) uncertainty in mr
    #sig_phe = 1.    #electron phi_e (out-of-plane, vertical) uncertainty in mr
    
    #proton (or hadron) arm uncertainties
    #sig_thp = 1.    #proton theta_p (in-plane, horizontal) uncertainty mr 
    #sig_php = 1.    #proton phi_p (out-of-plane, vertical) uncertainty mr
    
    #beam direction uncertainties (need to ask Mark Jones)
    #sig_thb = 0.     #beam theta_b (out-of-plane, vertical, YES! IT IS OPPOSITE) uncertainty
    #sig_phb = 0.     #beam phi_b (in-plane, horizontal, YES! IT IS OPPOSITE) uncertainty
    
    # relative sigma
    #final electron energy relative uncertainty (dEf/Ef)
    #sig_ef = 1.e-3
    #beam energy relative uncertainty (dEb / Eb)
    #sig_E = 1.e-3   
    
    # This is where you enter the estimated uncertainties
    # sigma in mr 
    
    sig_the = variances['sig_the']
    sig_phe = variances['sig_phe']
    
    sig_thp = variances['sig_thp']
    sig_php = variances['sig_php']
    
    sig_thb = variances['sig_thb']
    sig_phb = variances['sig_phb'] 
    
    # final energy relative sigma
    sig_ef = variances['sig_ef']
    # incident energy
    sig_E = variances['sig_E']
    
    ds_dthe = 0.
    ds_dphe = 0.
    ds_def = 0.
    ds_dthp = 0.
    ds_dphp = 0.
    ds_dthb = 0.
    ds_dphb = 0.
    ds_dE = 0.
    # these derivatives are in %/deg or %/MeV ->convert to %/rad
    for d in data:
        p = d.split(':')
        if len(p) >= 2:
            # there are values separated by colons
            if p[0].find('incident energy') >= 0:
                E_inc = float(p[1])
                found += 1
            if p[0].find('scattering angle') >= 0:
                ef = float(p[2])
                found += 1
        f = d.split()
        if len(f) == 0 :
            continue
        if f[0].find('dth_e') >= 0:
            ds_dthe = float(f[1])/dtr
            found += 1
        if f[0].find('dph_e') >= 0:
            ds_dphe = float(f[1])/dtr
            found += 1
        if f[0].find('def') >= 0:
            ds_def = float(f[1])
            found += 1
        if f[0].find('dth_p') >= 0:
            ds_dthp = float(f[1])/dtr
            found += 1
        if f[0].find('dph_p') >= 0:
            ds_dphp = float(f[1])/dtr
            found += 1
        if f[0].find('dth_b') >= 0:
            ds_dthb = float(f[1])/dtr
            found += 1
        if f[0].find('dph_b') >= 0:
            ds_dphb = float(f[1])/dtr
            found += 1
        if f[0].find('dE') >= 0:
            ds_dE = float(f[1])
            found += 1
    if found != 10 :
        print 'did not find all data !'
    # calculate total errors
    sigma_the = ds_dthe*sig_the*1.e-3
    sigma_phe = ds_dphe*sig_phe*1.e-3
    
    sigma_thp = ds_dthp*sig_thp*1.e-3
    sigma_php = ds_dphp*sig_php*1.e-3
    
    sigma_thb = ds_dthb*sig_thb*1.e-3
    sigma_phb = ds_dphb*sig_phb*1.e-3
    
    sigma_ef = ds_def*sig_ef*ef
    sigma_dE = ds_dE*sig_E*E_inc
    
    sigma_tot = np.sqrt(sigma_the**2 + 
                        sigma_phe**2 + 
                        sigma_thp**2 + 
                        sigma_php**2 + 
                        sigma_thb**2 + 
                        sigma_phb**2 + 
                        sigma_ef**2 + 
                        sigma_dE**2)
    problem = np.isnan(sigma_tot)

    #array to store individual systematics errors (relative error to Xsec in %)
    sig_arr = np.array([sigma_the, sigma_phe, sigma_thp, sigma_php, sigma_thb, sigma_phb, sigma_ef, sigma_dE, sigma_tot]) 
    
    #array to store derivatives
    derv_arr = np.array([ds_dthe, ds_dphe, ds_dthp, ds_dphp, ds_dthb, ds_dphb, ds_def, ds_dE])
    
    #Write derivatives to table
    write_table(sig_arr, derv_arr, ftable_bin, ftable_name)


    if (print_all or problem):
        print 'sigma_the  = ', sigma_the
        print 'sigma_phe = ', sigma_phe
        
        print 'sigma_thp = ', sigma_thp
        print 'sigma_php = ', sigma_php
        
        print 'sigma_thb = ', sigma_thb
        print 'sigma_phb = ', sigma_phb
        
        print 'sigma_ef = ' , sigma_ef
        print 'sigma_dE = ', sigma_dE
        
        print 'sigma_tot = ', sigma_tot
    return sigma_tot
# end of it all


#Define a function to write derivatives to a .txt file
def write_table(sig_arr = np.array([]), derv_arr = np.array([]), bin_arr=np.array([]), ftable_name=''):
    
    #open file to be writte in append mode
    fout = open(ftable_name, 'a')
    
    ib = bin_arr[0]
    pm = bin_arr[1]
    thnq = bin_arr[2]

    #Derivatives are in %/rad or %/MeV
    ds_dthe = derv_arr[0] * 1.e-3    #convert %/rad to %/mr (1 mr = 1e-3 rad)
    ds_dphe = derv_arr[1] * 1.e-3
    ds_dthp = derv_arr[2] * 1.e-3
    ds_dphp = derv_arr[3] * 1.e-3
    ds_dthb = derv_arr[4] * 1.e-3
    ds_dphb = derv_arr[5] * 1.e-3 
    ds_def = derv_arr[6]
    ds_dE = derv_arr[7]

    #Get individual systematic errors [in %]
    sig_the = sig_arr[0] 
    sig_phe = sig_arr[1] 
    sig_thp = sig_arr[2] 
    sig_php = sig_arr[3] 
    sig_thb = sig_arr[4] 
    sig_phb = sig_arr[5]  
    sig_ef = sig_arr[6]
    sig_E = sig_arr[7]
    sig_tot = sig_arr[8]   #total systematic error (added in quadrature)

    fout.write('%i   %f   %f   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e   %.3e\n'%(ib, pm, thnq, ds_dthe, ds_dphe, ds_def, ds_dthp, ds_dphp, ds_dthb, ds_dphb, ds_dE, sig_the, sig_phe, sig_ef, sig_thp, sig_php, sig_thb, sig_phb, sig_E, sig_tot))
    fout.close()
