************************
*** Scripts Contents ***
************************

get_elastic.C : Calculates kinematics for a A(e,e') process to be elastic
                given the target, beam energy and electron angle
		Usage: >> root -l
                       >> .L get_elastic.C
                       >> get_elastic("", ebeam, eAngle)
		       ex. get_elastic("h", 10.59, 25.4)

get_field.py : Executes field03/field17 scripts (currently on cdaq) for the
               full spectrometer momentum range. The magnet currents values
               are appended to a file, and the values are parsed, and written
               in .csv (Comma Separated Values) format.

get_report.py : Reads report file (currently for HMS runs only), parses the
                relevant information (Charge, Current, Efficiency, etc. . .)
                and adds it to a list of lists. The list is converted to a
                data-frame via the 'pandas' python module.

getRes.py     : Function [getQ('magnet', P )] is defined. Given a magnet
                ('Q1', 'Q2', 'Q3','D', 'NMR') and a momentum P, the 
		corresponding magnet current is returned. The main() func.
                is defined, and it reads the .csv file produced by get_field.py
  		An interpolation is performed, and the interpolation function,
                f(Q) is used along with the getQ() function to calculate the
		residuals from the interpolation. The interpolated function can
		also be used to determine the the momentum from the input 
		current.
 
plot_HMS_magnets.py : The code plots any two columns of the .csv file mentioned
                      above. The Momentum:MagnetCurrent correlations are
		      plotted, and the interpolation function calculated,
		      and superimposed in the plots.  

hms_magnet_data.csv : Comma-Separated Values (.csv) file containg the columns:
		      p,q1,q2,q3,dipole,nmr representing the momentum, currents
		      and nmr values determined from field03/17 codes.
		      