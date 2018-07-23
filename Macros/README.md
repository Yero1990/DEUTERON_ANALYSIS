************************
*** Scripts Contents ***
************************

get_elastic.C : Calculates kinematics for a A(e,e') process to be elastic
                given the target, beam energy and electron angle
		Usage: >> root -l
                       >> .L get_elastic.C
                       >> get_elastic("", ebeam, eAngle)
		       ex. get_elastic("h", 10.59, 25.4)

get_report.py : Reads report file (currently for HMS runs only), parses the
                relevant information (Charge, Current, Efficiency, etc. . .)
                and adds it to a list of lists. The list is converted to a
                data-frame via the 'pandas' python module.
