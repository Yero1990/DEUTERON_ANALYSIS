************************
*** Scripts Contents ***
************************

get_SHMSfield.py : Executes field03/field17 scripts (../executables/) for the
               full spectrometer momentum range. The magnet currents values
               are appended to a file, and the values are parsed, and written
               in .csv (Comma Separated Values) format.


getSHMSRes.py     : Function [getQ('magnet', P )] is defined. Given a magnet
                ('Q1', 'Q2', 'Q3','D', 'NMR') and a momentum P, the 
		corresponding magnet current is returned. The main() func.
                is defined, and it reads the .csv file produced by get_field.py
  		An interpolation is performed, and the interpolation function,
                f(Q) is used along with the getQ() function to calculate the
		residuals from the interpolation. The interpolated function can
		also be used to determine the the momentum from the input 
		current. The interpolated function is plotted on top of the
                data points obtained from the .csv file

shms_magnet_data.csv : Comma-Separated Values (.csv) file containg the columns:
		      p,hb,q1,q2,q3,dipole representing the momentum, currents
		      and nmr values determined from field03/17 codes.
		      