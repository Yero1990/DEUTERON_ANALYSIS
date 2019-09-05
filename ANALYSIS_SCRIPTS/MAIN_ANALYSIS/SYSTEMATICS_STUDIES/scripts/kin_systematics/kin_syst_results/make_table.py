from LT.datafile import dfile
import numpy as np
import csv

kin_file1 = dfile('pm80_fsi_results_the1mr.txt')    #pm80, dthe: 1 mr
kin_file2 = dfile('pm80_fsi_results_the0.2mr.txt')  #pm80, dthe: 0.2 mr

pm = kin_file1['yb']
thnq = kin_file1['xb']

tot_err1 = kin_file1['tot_err']
tot_err2 = kin_file2['tot_err']

 
thnq_arr = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105]


#Loop over theta_nq angle bins
for i, ithnq in enumerate(thnq_arr):
    print('theta_nq:',ithnq,' deg')
    print(pm)

    ftable = open('table_thnq%s.txt'%(ithnq), 'w')
    #ftable.write("Pm    th_nq    sys_err_1mr    sys_err_0.2mr")
    
    
    #print('pm:',pm[thnq==ithnq],' thnq:',thnq[thnq==ithnq], 'tot_err1:',tot_err2[thnq==ithnq])
    print( zip(pm[thnq==ithnq], thnq[thnq==ithnq], tot_err2[thnq==ithnq]) )

    with open('table_thnq%s.txt'%(ithnq), 'w') as f:
        writer = csv.writer(f, delimiter='\t')
        writer.writerows(zip(pm[thnq==ithnq], thnq[thnq==ithnq], tot_err1[thnq==ithnq], tot_err2[thnq==ithnq]))
