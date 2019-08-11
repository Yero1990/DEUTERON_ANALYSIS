import LT.box as B
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d
import numpy.ma as ma
import sys                                     
import os                                                                                                       
from sys import argv  

#Conversion factor:  1 fm = 1/ (197 MeV),   
#The reduced cross section is in MeV^-3 units
MeV2fm = 197**3    #convert MeV^-3 to fm^3

#User Input (Dir. Name to store output)
sys_ext = sys.argv[1]   

dir_name = sys_ext+"_plots"
print(dir_name)
#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#Get Reduced Xsec Data File
f = B.get_file('./%s/redXsec_combined.txt'%(sys_ext))

#Get Bin Information
i_b = B.get_data(f, 'i_b')    #2D bin number
i_x = B.get_data(f, 'i_x')    #x (th_nq) bin number
i_y = B.get_data(f, 'i_y')    #y (pmiss) bin number
thnq = B.get_data(f, 'xb')      #th_nq value at bin center
pm =  B.get_data(f, 'yb')      #pmiss value at bin center



#Get 80 MeV Red. Xsec (prepare arrays for masking)
red_dataXsec_80     = B.get_data(f, 'red_dataXsec_80')
red_dataXsec_err_80 = B.get_data(f, 'red_dataXsec_err_80')
red_pwiaXsec_80     = B.get_data(f, 'red_pwiaXsec_80')
red_fsiXsec_80      = B.get_data(f, 'red_fsiXsec_80')

#Get 580 MeV Red. Xsec
red_dataXsec_580set1     = B.get_data(f,'red_dataXsec_580set1')
red_dataXsec_err_580set1 = B.get_data(f,'red_dataXsec_err_580set1')
red_dataXsec_580set2     = B.get_data(f,'red_dataXsec_580set2')
red_dataXsec_err_580set2 = B.get_data(f,'red_dataXsec_err_580set2')
red_dataXsec_580avg      = B.get_data(f,'red_dataXsec_580avg')
red_dataXsec_580avg_err  = B.get_data(f,'red_dataXsec_580avg_err')

red_pwiaXsec_580set1 = B.get_data(f,'red_pwiaXsec_580set1')
red_pwiaXsec_580set2 = B.get_data(f,'red_pwiaXsec_580set2')
red_pwiaXsec_580avg  = B.get_data(f,'red_pwiaXsec_580avg')
red_fsiXsec_580set1  = B.get_data(f,'red_fsiXsec_580set1')
red_fsiXsec_580set2  = B.get_data(f,'red_fsiXsec_580set2')
red_fsiXsec_580avg   = B.get_data(f,'red_fsiXsec_580avg')

#Get 750 MeV Red. Xsec
red_dataXsec_750set1     = B.get_data(f,'red_dataXsec_750set1')
red_dataXsec_err_750set1 = B.get_data(f,'red_dataXsec_err_750set1')
red_dataXsec_750set2     = B.get_data(f,'red_dataXsec_750set2')
red_dataXsec_err_750set2 = B.get_data(f,'red_dataXsec_err_750set2')
red_dataXsec_750set3     = B.get_data(f,'red_dataXsec_750set3')
red_dataXsec_err_750set3 = B.get_data(f,'red_dataXsec_err_750set3')
red_dataXsec_750avg      = B.get_data(f,'red_dataXsec_750avg')
red_dataXsec_750avg_err  = B.get_data(f,'red_dataXsec_750avg_err')

red_pwiaXsec_750set1 = B.get_data(f,'red_pwiaXsec_750set1')
red_pwiaXsec_750set2 = B.get_data(f,'red_pwiaXsec_750set2')
red_pwiaXsec_750set3 = B.get_data(f,'red_pwiaXsec_750set3')
red_pwiaXsec_750avg  = B.get_data(f,'red_pwiaXsec_750avg')
red_fsiXsec_750set1  = B.get_data(f,'red_fsiXsec_750set1')
red_fsiXsec_750set2  = B.get_data(f,'red_fsiXsec_750set2')
red_fsiXsec_750set3  = B.get_data(f,'red_fsiXsec_750set3')
red_fsiXsec_750avg   = B.get_data(f,'red_fsiXsec_750avg')

#Get Combined Final Red Xsec for all kinematics
red_dataXsec_avg     = B.get_data(f,'red_dataXsec_avg')
red_dataXsec_avg_err = B.get_data(f,'red_dataXsec_avg_err')
red_pwiaXsec_avg     = B.get_data(f,'red_pwiaXsec_avg')
red_fsiXsec_avg      = B.get_data(f,'red_fsiXsec_avg')

def plot_data_sets():
    
    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 


    for i, ithnq in enumerate(thnq_arr):
        print(ithnq)
            
        B.pl.figure(i)

        B.plot_exp(pm[thnq==ithnq], red_dataXsec_580set1[thnq==ithnq]*MeV2fm, red_dataXsec_err_580set1[thnq==ithnq]*MeV2fm, color='red',  marker='^', label='580 (set1)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_580set2[thnq==ithnq]*MeV2fm, red_dataXsec_err_580set2[thnq==ithnq]*MeV2fm, color='blue', marker='s', label='580 (set2)')
       
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set1[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set1[thnq==ithnq]*MeV2fm, color='magenta', markerfacecolor='none', marker='v', label='750 (set1)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set2[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set2[thnq==ithnq]*MeV2fm, color='cyan',    markerfacecolor='none', marker='D', label='750 (set2)')
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_750set3[thnq==ithnq]*MeV2fm, red_dataXsec_err_750set3[thnq==ithnq]*MeV2fm, color='green',   markerfacecolor='none', marker='s', label='750 (set3)')

        B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, color='black', marker='o', label='Combined Data')

        B.pl.yscale('log')


        B.pl.xlim(0,1.2)
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        B.pl.title(r'Reduced Data Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))

        B.pl.legend()
    
        B.pl.savefig(dir_name+'/dataSets_redXsec_thnq%i.pdf'%(ithnq))

    #B.pl.show('same')

def plot_theory_sets(model=''):
    
    
    if (model=='pwia'):
        thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 

        '''
        #Mask '-' values
        red_pwiaXsec_580set1_masked =  ma.masked_array(red_pwiaXsec_580set1, mask=red_pwiaXsec_580set1<0)
        red_pwiaXsec_580set2_masked =  ma.masked_array(red_pwiaXsec_580set2, mask=red_pwiaXsec_580set2<0)
        
        red_pwiaXsec_750set1_masked =  ma.masked_array(red_pwiaXsec_750set1, mask=red_pwiaXsec_750set1<0)
        red_pwiaXsec_750set2_masked =  ma.masked_array(red_pwiaXsec_750set2, mask=red_pwiaXsec_750set2<0)
        red_pwiaXsec_750set3_masked =  ma.masked_array(red_pwiaXsec_750set3, mask=red_pwiaXsec_750set3<0)
        '''


        for i, ithnq in enumerate(thnq_arr):
            print(ithnq)
            
            B.pl.figure(i)

            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_580set1[thnq==ithnq]*MeV2fm, color='red',  linestyle='--',  label='580 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_580set2[thnq==ithnq]*MeV2fm, color='blue', linestyle='--', label='580 (set2)')
            
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set1[thnq==ithnq]*MeV2fm, color='magenta',linestyle='--', label='750 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set2[thnq==ithnq]*MeV2fm, color='cyan',   linestyle='--', label='750 (set2)')
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_750set3[thnq==ithnq]*MeV2fm, color='green',  linestyle='--', label='750 (set3)')
            
            B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_avg[thnq==ithnq]*MeV2fm, color='black', linestyle='--', label='Combined PWIA Theory')

            B.pl.yscale('log')


            B.pl.xlim(0,1.2)
            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
            th_nq_min = ithnq - 5
            th_nq_max = ithnq + 5
            B.pl.title(r'Reduced PWIA Theoretical Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))

            B.pl.legend()
    
            B.pl.savefig(dir_name+'/%s_theorySets_redXsec_thnq%i.pdf'%(model, ithnq))

        #B.pl.show('same')

    if (model=='fsi'):
        thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]  #central theta_nq value 


        for i, ithnq in enumerate(thnq_arr):
            print(ithnq)
            
            B.pl.figure(i)
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_580set1[thnq==ithnq]*MeV2fm, color='red',  linestyle='--',  label='580 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_580set2[thnq==ithnq]*MeV2fm, color='blue', linestyle='--', label='580 (set2)')
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set1[thnq==ithnq]*MeV2fm, color='magenta',linestyle='--', label='750 (set1)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set2[thnq==ithnq]*MeV2fm, color='cyan',   linestyle='--', label='750 (set2)')
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_750set3[thnq==ithnq]*MeV2fm, color='green',  linestyle='--', label='750 (set3)')
            
            B.plot_exp(pm[thnq==ithnq], red_fsiXsec_avg[thnq==ithnq]*MeV2fm, color='black', linestyle='--', label='Combined FSI Theory')
            
            B.pl.yscale('log')
            
                
            B.pl.xlim(0,1.2)
            B.pl.xlabel('Neutron Recoil Momenta [GeV]')
            B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
            th_nq_min = ithnq - 5
            th_nq_max = ithnq + 5
            B.pl.title(r'Reduced FSI Theoretical Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
            
            B.pl.legend()
            
            B.pl.savefig(dir_name+'/%s_theorySets_redXsec_thnq%i.pdf'%(model, ithnq))
                
        #B.pl.show('same')

def plot_final():

    #----MASKING ARRAYS TO CHOOSE ERRORS BELOW 20 %-------
    #The Limit on the red. Xsec error should be placed at the very end, when the combined data is plotted (all data sets and overlapping bins have been combined)
    red_dataXsec_avg_masked = np.ma.array(red_dataXsec_avg, mask=(red_dataXsec_avg_err>0.2*red_dataXsec_avg))
    red_dataXsec_avg_masked = np.ma.filled(red_dataXsec_avg_masked.astype(float), -1.)


    thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]

    for i, ithnq in enumerate(thnq_arr):
        print(ithnq)
            
        B.pl.figure(i)

        B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, color='black', logy=True, label='Data' )
        B.plot_exp(pm[thnq==ithnq], red_dataXsec_avg_masked[thnq==ithnq]*MeV2fm, red_dataXsec_avg_err[thnq==ithnq]*MeV2fm, marker='s', color='gray', markerfacecolor='none', label='Data(Error < 20 % )' )
        B.plot_exp(pm[thnq==ithnq], red_pwiaXsec_avg[thnq==ithnq]*MeV2fm, linestyle='--', color='red', logy=True, label='Laget PWIA')
        B.plot_exp(pm[thnq==ithnq], red_fsiXsec_avg[thnq==ithnq]*MeV2fm, linestyle='--', color='blue', logy=True, label='Laget FSI')
        B.pl.xlabel('Neutron Recoil Momenta [GeV]')
        B.pl.ylabel(r'Reduced Cross Section, $\sigma_{red} [fm^{3}]$')
        B.pl.ylim(0, 10)
        th_nq_min = ithnq - 5
        th_nq_max = ithnq + 5
        B.pl.title(r'Reduced Cross Section, $\theta_{nq}:(%i, %i)$'%(th_nq_min, th_nq_max))
        B.pl.yscale('log')

        B.pl.legend()
            
        B.pl.savefig(dir_name+'/final_redXsec_thnq%i.pdf'%(ithnq))


    #B.pl.show('same')


def main():
    print('Entering Main . . .')

    plot_data_sets()

    plot_theory_sets('pwia')
    plot_theory_sets('fsi')
    plot_final()



if __name__=="__main__":
    main()



'''
#central th_nq values array
thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95]

fig, ax = plt.subplots(2, 5, sharex=True, sharey=True)

for i, ithnq in enumerate(thnq_arr):
    fig.add_subplot(2, 5, i+1)

    plt.tick_params(axis='x', which='both', bottom=False, top=False, labelbottom=False)     
    plt.tick_params(axis='y', which='both', right=False, left=False, labelleft=False) 
    B.plot_exp(pm[thnq==ithnq], red_dataXsec_80[thnq==ithnq], red_dataXsec_err_80[thnq==ithnq], logy=True)

    B.pl.xlabel('')
    B.pl.ylabel('')
    
    B.pl.title('')

#B.pl.ylim(0, 0.000001)
fig.text(0.5, 0.04, 'Missing Momentum [GeV]', ha='center')
fig.text(0.04, 0.5, r'$\sigma_{red}$ [fm$^{3}$]', va='center', rotation='vertical')
plt.subplots_adjust(left=0.125, bottom=0.1, right=0.9, top=0.9, wspace=0.2, hspace=0.2)

'''


#80 MeV


'''
#Get Bin-Conrr. Data Xsec, and theory
thnq80 = B.get_data(f80, 'xb')  #thnq bin center value (deg)
pm80 = B.get_data(f80, 'yb')    #pm bin cernter calue (GeV)
dataXsec80 = B.get_data(f80, 'dataXsec_bc')
dataXsec80_err = B.get_data(f80, 'dataXsec_bc_err')
pwiaXsec80_theory = B.get_data(f80, 'pwiaXsec_theory')
fsiXsec80_theory = B.get_data(f80, 'fsiXsec_theory')
red_dataXsec80 = B.get_data(f80, 'red_dataXsec')
red_dataXsec80_err = B.get_data(f80, 'red_dataXsec_err')
red_pwiaXsec80_theory = B.get_data(f80, 'red_pwiaXsec')
red_fsiXsec80_theory = B.get_data(f80, 'red_fsiXsec')

thnq580_set1 = B.get_data(f580_set1, 'xb')  
pm580_set1 = B.get_data(f580_set1, 'yb')   
dataXsec580_set1 = B.get_data(f580_set1, 'dataXsec_bc')
dataXsec580_err_set1 = B.get_data(f580_set1, 'dataXsec_bc_err')
pwiaXsec580_theory_set1 = B.get_data(f580_set1, 'pwiaXsec_theory')
fsiXsec580_theory_set1 = B.get_data(f580_set1, 'fsiXsec_theory')
red_dataXsec580_set1 = B.get_data(f580_set1, 'red_dataXsec')
red_dataXsec580_err_set1 = B.get_data(f580_set1, 'red_dataXsec_err')
red_pwiaXsec580_theory_set1 = B.get_data(f580_set1, 'red_pwiaXsec')
red_fsiXsec580_theory_set1 = B.get_data(f580_set1, 'red_fsiXsec')

thnq580_set2 = B.get_data(f580_set2, 'xb')  
pm580_set2 = B.get_data(f580_set2, 'yb')  
dataXsec580_set2 = B.get_data(f580_set2, 'dataXsec_bc')
dataXsec580_err_set2 = B.get_data(f580_set2, 'dataXsec_bc_err')
pwiaXsec580_theory_set2 = B.get_data(f580_set2, 'pwiaXsec_theory')
fsiXsec580_theory_set2 = B.get_data(f580_set2, 'fsiXsec_theory')
red_dataXsec580_set2 = B.get_data(f580_set2, 'red_dataXsec')
red_dataXsec580_err_set2 = B.get_data(f580_set2, 'red_dataXsec_err')
red_pwiaXsec580_theory_set2 = B.get_data(f580_set2, 'red_pwiaXsec')
red_fsiXsec580_theory_set2 = B.get_data(f580_set2, 'red_fsiXsec')

thnq750_set1 = B.get_data(f750_set1, 'xb')  
pm750_set1 = B.get_data(f750_set1, 'yb')  
dataXsec750_set1 = B.get_data(f750_set1, 'dataXsec_bc')
dataXsec750_err_set1 = B.get_data(f750_set1, 'dataXsec_bc_err')
pwiaXsec750_theory_set1 = B.get_data(f750_set1, 'pwiaXsec_theory')
fsiXsec750_theory_set1 = B.get_data(f750_set1, 'fsiXsec_theory')
red_dataXsec750_set1 = B.get_data(f750_set1, 'red_dataXsec')
red_dataXsec750_err_set1 = B.get_data(f750_set1, 'red_dataXsec_err')
red_pwiaXsec750_theory_set1 = B.get_data(f750_set1, 'red_pwiaXsec')
red_fsiXsec750_theory_set1 = B.get_data(f750_set1, 'red_fsiXsec')

thnq750_set2 = B.get_data(f750_set2, 'xb')  
pm750_set2 = B.get_data(f750_set2, 'yb')  
dataXsec750_set2 = B.get_data(f750_set2, 'dataXsec_bc')
dataXsec750_err_set2 = B.get_data(f750_set2, 'dataXsec_bc_err')
pwiaXsec750_theory_set2 = B.get_data(f750_set2, 'pwiaXsec_theory')
fsiXsec750_theory_set2 = B.get_data(f750_set2, 'fsiXsec_theory')
red_dataXsec750_set2 = B.get_data(f750_set2, 'red_dataXsec')
red_dataXsec750_err_set2 = B.get_data(f750_set2, 'red_dataXsec_err')
red_pwiaXsec750_theory_set2 = B.get_data(f750_set2, 'red_pwiaXsec')
red_fsiXsec750_theory_set2 = B.get_data(f750_set2, 'red_fsiXsec')

thnq750_set3 = B.get_data(f750_set3, 'xb')  
pm750_set3 = B.get_data(f750_set3, 'yb')  
dataXsec750_set3 = B.get_data(f750_set3, 'dataXsec_bc')
dataXsec750_err_set3 = B.get_data(f750_set3, 'dataXsec_bc_err')
pwiaXsec750_theory_set3 = B.get_data(f750_set3, 'pwiaXsec_theory')
fsiXsec750_theory_set3 = B.get_data(f750_set3, 'fsiXsec_theory')
red_dataXsec750_set3 = B.get_data(f750_set3, 'red_dataXsec')
red_dataXsec750_err_set3 = B.get_data(f750_set3, 'red_dataXsec_err')
red_pwiaXsec750_theory_set3 = B.get_data(f750_set3, 'red_pwiaXsec')
red_fsiXsec750_theory_set3 = B.get_data(f750_set3, 'red_fsiXsec')


#Plot Data
#B.plot_exp(pm80[thnq80==40], dataXsec80[thnq80==40], dataXsec80_err[thnq80==40], marker='s', color='r', label='DATA (80 MeV)', logy=True)
#B.plot_exp(pm580_set1[thnq580_set1==40], dataXsec580_set1[thnq580_set1==40], dataXsec580_err_set1[thnq580_set1==40], marker='s', color='b', label='DATA (580 MeV)', logy=True)
#B.plot_exp(pm750_set1[thnq750_set1==40], dataXsec750_set1[thnq750_set1==40], dataXsec750_err_set1[thnq750_set1==40], marker='s', color='g', label='DATA (750 MeV)', logy=True)

#Reduced Cross Section

#Convert from MeV^-3 to fm^3
red_dataXsec80 = red_dataXsec80 * MeV2fm
red_dataXsec580_set1 = red_dataXsec580_set1 * MeV2fm
red_dataXsec750_set1 = red_dataXsec750_set1 * MeV2fm
red_dataXsec580_set2 = red_dataXsec580_set2 * MeV2fm
red_dataXsec750_set2 = red_dataXsec750_set2 * MeV2fm
red_dataXsec750_set3 = red_dataXsec750_set3 * MeV2fm

red_dataXsec80_err = red_dataXsec80_err * MeV2fm
red_dataXsec580_err_set1 = red_dataXsec580_err_set1 * MeV2fm
red_dataXsec750_err_set1 = red_dataXsec750_err_set1 * MeV2fm
red_dataXsec580_err_set2 = red_dataXsec580_err_set2 * MeV2fm
red_dataXsec750_err_set2 = red_dataXsec750_err_set2 * MeV2fm
red_dataXsec750_err_set3 = red_dataXsec750_err_set3 * MeV2fm

#Theory
red_pwiaXsec80_theory = red_pwiaXsec80_theory * MeV2fm
red_fsiXsec80_theory = red_fsiXsec80_theory * MeV2fm
red_pwiaXsec580_theory_set1 = red_pwiaXsec580_theory_set1 * MeV2fm
red_fsiXsec580_theory_set1 = red_fsiXsec580_theory_set1 * MeV2fm
red_pwiaXsec750_theory_set1 = red_pwiaXsec750_theory_set1 * MeV2fm
red_fsiXsec750_theory_set1 = red_fsiXsec750_theory_set1 * MeV2fm


#Plot Data
B.plot_exp(pm80[thnq80==40], red_dataXsec80[thnq80==40], red_dataXsec80_err[thnq80==40], marker='s', color='r', label='DataSet1 (80 MeV)', logy=True)
B.plot_exp(pm580_set1[thnq580_set1==40], red_dataXsec580_set1[thnq580_set1==40], red_dataXsec580_err_set1[thnq580_set1==40], marker='s', color='b', label='DataSet1 (580 MeV)', logy=True)
B.plot_exp(pm580_set2[thnq580_set2==40], red_dataXsec580_set2[thnq580_set2==40], red_dataXsec580_err_set2[thnq580_set2==40], marker='^', color='b', label='DataSet2 (580 MeV)', logy=True)
B.plot_exp(pm750_set1[thnq750_set1==40], red_dataXsec750_set1[thnq750_set1==40], red_dataXsec750_err_set1[thnq750_set1==40], marker='s', color='g', label='DataSet1 (750 MeV)', logy=True)
B.plot_exp(pm750_set2[thnq750_set2==40], red_dataXsec750_set2[thnq750_set2==40], red_dataXsec750_err_set2[thnq750_set2==40], marker='^', color='g', label='DataSet2 (750 MeV)', logy=True)
B.plot_exp(pm750_set3[thnq750_set3==40], red_dataXsec750_set3[thnq750_set3==40], red_dataXsec750_err_set3[thnq750_set3==40], marker='o', color='g', label='DataSet3 (750 MeV)', logy=True)

#Plot Theory
B.plot_exp(pm80[thnq80==40], red_pwiaXsec80_theory[thnq80==40], linestyle='--', color='r', label='Laget PWIA (80 MeV)', logy=True)
B.plot_exp(pm80[thnq80==40], red_fsiXsec80_theory[thnq80==40], linestyle='-', color='r', label='Laget FSI (80 MeV)', logy=True)

B.plot_exp(pm580_set1[thnq580_set1==40], red_pwiaXsec580_theory_set1[thnq580_set1==40], linestyle='--', color='b', label='Laget PWIA (580 MeV)', logy=True)
B.plot_exp(pm580_set1[thnq580_set1==40], red_fsiXsec580_theory_set1[thnq580_set1==40], linestyle='-', color='b', label='Laget FSI (580 MeV)', logy=True)

B.plot_exp(pm750_set1[thnq750_set1==40], red_pwiaXsec750_theory_set1[thnq750_set1==40], linestyle='--', color='g', label='Laget PWIA (750 MeV)', logy=True)
B.plot_exp(pm750_set1[thnq750_set1==40], red_fsiXsec750_theory_set1[thnq750_set1==40], linestyle='-', color='g', label='Laget FSI (750 MeV)', logy=True)

B.pl.xlabel('Recoil Momenta [GeV/c]', fontsize=15)
B.pl.ylabel(r'$\sigma_{red}$ [fm$^{3}$]', fontsize=15)

B.pl.legend()
#B.pl.show('same')

'''
