# make file for F2PY and installation into the utilities 
#
# default procedure for compiling a .f file
#
#suffix rule necessary for compiling with absoft
.f.so :
	$(F2PY) $(F2PYFLAGS) $<

HERE          = ./

CROSEC        = ./

CERNLIB       =

DEST          = ./build/


PRINT	      = 

F2PY          = /apps/python/2.7.12/bin/python f2py.py 
F2PYFLAGS     = -c --build-dir ./build/ -m

PROGRAM	      = Laget_Xsec_fp_1

SRCS          = Laget_Xsec_fp_1.f

all:		$(DEST)/$(PROGRAM).so

$(PROGRAM):     $(SRCS)
		$(F2PY) $(F2PYFLAGS) $(PROGRAM)  $(SRCS)
		touch $(PROGRAM)

clean:	
		rm $(PROGRAM).so
		rm $(PROGRAM)
		rm -rf ./build
		rm *.o


# copy to the instalation directory 

$(DEST)/$(PROGRAM).so:  $(PROGRAM)
		cp $(PROGRAM).so $(DEST)/$(PROGRAM).so










