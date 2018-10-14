#!/usr/bin/env python 
import wxdatafile as wd
import argparse as AG

parser = AG.ArgumentParser()
parser.add_argument("data_file",nargs='?',help="Data file to display")
args = parser.parse_args()
print 'showing : ', args.data_file
f = wd.dfile(args.data_file)
f.wxdisplay()
