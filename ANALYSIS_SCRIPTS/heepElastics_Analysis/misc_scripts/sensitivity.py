import LT.box as B
import LT.plotting as P
import numpy as np

dtr = np.pi / 180.   #conversion from deg to radians

Mp = 0.938272    #proton mass in GeV

#theta_p = np.linspace(20, 50, 60)   #in degrees
Eb = np.linspace(2.0, 11., 50)   #in GeV
#Eb = [2.221, 6.430, 10.58794]
theta_p = [27.502, 27.511, 33.545, 37.29, 37.338, 42.9, 47.605, 47.915]

#Calculated Momentum
#Pp = A / B

for theta_p in theta_p:
#    print(Eb)

    A = 2.*Mp*Eb*(Eb+Mp)*np.cos(theta_p*dtr)
    B = pow(Mp,2) + 2.*Mp*Eb + pow(Eb*np.sin(theta_p*dtr), 2)

    Pp = A / B

    #Derivatives
    dAdE = 2.*Mp*np.cos(theta_p*dtr)*(2.*Eb + Mp)
    dBdE = 2.*Mp + 2.*Eb*pow(np.sin(theta_p*dtr),2)

    dAdth = -2.*Mp*Eb*(Eb + Mp)*np.sin(theta_p*dtr)
    dBdth = 2.*pow(Eb,2) * np.sin(theta_p*dtr)*np.cos(theta_p*dtr)
    
    #Proton Momentum Sensitivity to Beam Energy 
    dPdE = dAdE * (1./B) - (A/B**2)*dBdE
    
    
    #Proton Momentum Sensitivity to Angle
    dPdth = dAdth * (1./B) - (A/B**2) * dBdth   #GeV / rad
    
    #print(Pp)
    
    P.plot_exp(Eb, dPdE, label='dP / dE, Angle: %s deg' % theta_p)



P.pl.xlabel('Beam Energy (GeV)')
P.pl.ylabel('Sensitivity dP / dE ')
P.pl.title('Proton Momentum Sensitivity to Beam Energy')

P.pl.legend()
P.pl.show()

