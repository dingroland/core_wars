# Makefile for GAlib 2.x - example programs
# Copyright (c) 1994-1996 Massachusetts Institute of Technology
# mbwall 19apr95 all rights reserved
# -----------------------------------------------------------------------------
#   To make all of the examples, do 'make depend; make'.  If your system does 
# not have makedepend on it, simply type 'make'.  You can compile any one of
# the examples by typing 'make exN' where N is the number of the example you
# want to compile.  See the README for a description of what each example does.
# -----------------------------------------------------------------------------

# This is where the examples should be installed (this is used only if you do
# a 'make install')
EX_DEST_DIR= /usr/local/ga/examples

# Specify the compiler here.
C++C= g++

# Set this to the location of the headers for your C++ compiler (this is used
# only by makedepend, so if you're not using makedepend don't worry about it).
CC_INC_DIR= /usr/local/gnu/lib/g++-include

# Specify the compiler flags appropriate for the compiler/platform that you use
# Uncomment the line that corresponds to your system.
### DCC with SGI IRIX
#CCFLAGS= -ptv +w +pp -O -g $(INC_DIRS)
### g++ with: SGI IRIX, DEC MIPS ultrix, IBM RSAIX, HPUX, SUN Solaris
CCFLAGS= -Wall -O -g $(INC_DIRS)

# Set these paths to the location of the GA library and headers.
#GA_INC_DIR= /usr/local/include
#GA_LIB_DIR= /usr/local/lib
GA_INC_DIR= ..
GA_LIB_DIR= ../ga


# -----------------------------------------------------------------------------
# That's all of the configuration macros!  The rest of this file is all
# dependencies.  You shouldn't have to edit anything after this line, unless
# you are using GNU's make.
# -----------------------------------------------------------------------------
INC_DIRS= -I$(GA_INC_DIR)
LIB_DIRS= -L$(GA_LIB_DIR)

SRCS= randtest.C \
 ex1.C  ex2.C  ex3.C  ex4.C  ex5.C  ex6.C  ex7.C  ex8.C  ex9.C \
 ex10.C ex11.C ex12.C ex13.C ex14.C ex15.C ex16.C ex17.C ex18.C \
 ex19.C ex20.C ex21.C ex22.C ex23.C ex24.C ex25.C ex26.C ex27.C
EXS=  randtest \
 ex1    ex2    ex3    ex4    ex5    ex6    ex7    ex8    ex9 \
 ex10   ex11   ex12   ex13   ex14   ex15   ex16   ex17   ex18 \
 ex19   ex20   ex21   ex22   ex23   ex24   ex25   ex26   ex27

.SUFFIXES: .o .C
.C.o:
	$(C++C) -c $(CCFLAGS) $<

all: $(EXS)

$(EXS): $$@.o
	$(C++C) $@.o -o $@ $(LIB_DIRS) -lga -lm

# Use this for gnu-make
#$(EXS): %: %.o
#	$(C++C) $@.o -o $@ $(LIB_DIRS) -lga -lm

install:
	rm -rf $(EX_DEST_DIR); mkdir -p $(EX_DEST_DIR)
	cp makefile *.txt *.C *.h $(EX_DEST_DIR)

remove:
	rm -rf $(EX_DEST_DIR)

clean:
	rm -rf *~ *.bak *.out *.pixie *.o core $(EXS) *.dat

depend:
	makedepend -I$(CC_INC_DIR) $(INC_DIRS) $(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.
