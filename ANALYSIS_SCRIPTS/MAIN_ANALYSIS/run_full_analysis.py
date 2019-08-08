import os
import shutil
import glob
import subprocess as sp
import sys
from sys import argv

'''
#==Pm= 750 FSI (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi  750 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_fsi_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)




#==Pm= 750 FSI (set2)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi  750 2")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_fsi_set2"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)




#==Pm= 750 FSI (set3)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi  750 3")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_fsi_set3"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)


#==Pm= 750 PWIA (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia  750 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_pwia_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)
'''

#==Pm= 750 PWIA (set2)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia 750 2")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_pwia_set2"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 750 PWIA (set3)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia 750 3")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm750_pwia_set3"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)



#==Pm= 80 FSI (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi 80 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm80_fsi_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 80 PWIA (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia 80 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm80_pwia_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 580 FSI (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi 580 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm580_fsi_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 580 FSI (set2)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py fsi 580 2")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm580_fsi_set2"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 580 PWIA (set1)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia 580 1")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm580_pwia_set1"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)

#==Pm= 580 PWIA (set2)==

#Generate Input File for D(e,e'p)
os.system("python gen_inp.py pwia 580 2")

#Run main_analysis script
os.system("root -l -q \"main_analysis.C(2)\"")

#declare directory name
dir_name="./pm580_pwia_set2"

#check if directory exists, else creates it.
if not os.path.exists(dir_name):
    os.makedirs(dir_name)

#move ouput to relevant directory
os.system("mv *.root report_deep* "+dir_name)
