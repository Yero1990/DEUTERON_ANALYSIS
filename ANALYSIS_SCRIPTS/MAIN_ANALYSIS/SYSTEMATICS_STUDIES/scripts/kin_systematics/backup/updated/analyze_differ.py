import numpy  as np
dtr = np.pi/180.

sigmas  = {\
    # electron arm
    'sig_the':0.12, \
    'sig_phe':0.23, \
    # proton arm
    'sig_thp':0.13, \
    'sig_php':0.29, \
    # beam directopm
    'sig_thb':0.1, \
    'sig_phb':0.1, \
    
    # final electron energy relative sigma
    'sig_ef':1.7e-4, \
    # incident beam
    'sig_E':3.e-4
        }


def get_sig_tot(differ_file, print_all = False, variances = sigmas):
    data = open(differ_file).readlines()
    found = 0
    
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
                omega = float(p[2])
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
    ef = E_inc - omega
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
