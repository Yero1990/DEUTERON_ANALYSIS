************************
*** Scripts Contents ***
************************

get_HMSfield.py : Executes field03/field17 scripts (../executables) for the
               full spectrometer momentum range. The magnet currents values
               are appended to a file, and the values are parsed, and written
               in .csv (Comma Separated Values) format.


getHMSRes.py     : Function [getQ('magnet', P )] is defined. Given a magnet
                ('Q1', 'Q2', 'Q3','D', 'NMR') and a momentum P, the 
		corresponding magnet current is returned. The main() func.
                is defined, and it reads the .csv file produced by get_field.py
  		An interpolation is performed, and the interpolation function,
                f(Q) is used along with the getQ() function to calculate the
		residuals from the interpolation. The interpolated function can
		also be used to determine the the momentum from the input 
		current. The interpolated function is plotted on top of the
                data points obtained from the .csv file
 
CSV2dataFrame_example.py : The code serves as an example of how to pass a .csv
			   file into a dataframe, and plot any two columns.
			   The code also shows how to interpolate the .csv
			   data, and plot it.

hms_magnet_data.csv : Comma-Separated Values (.csv) file containg the columns:
		      p,q1,q2,q3,dipole,nmr representing the momentum, currents
		      and nmr values determined from field03/17 codes.
		      