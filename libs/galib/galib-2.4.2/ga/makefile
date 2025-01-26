# Makefile for GAlib - library
# Copyright (c) 1994-1996 Massachusetts Institute of Technology
# mbwall 27feb95
# -----------------------------------------------------------------------------
# Before you try to compile you should edit the parameters below.  Once you
# have done that, do 'make depend; make'.  This assumes that your system has
# makedepend on it.  If not, then simply type 'make'.  You can do 'make clean'
# to put things back into their pristine condition.
#   Edit the C++C macro to specify the compiler that you're using.  You may 
# also need to edit CC_INC_DIR to specify where your C++ compiler's headers are
# located.  Some compilers do explicit prelinking (for example DCC).  If your
# compiler requires you to prelink libraries, then put the appropriate command
# in the PRELINK line.
#   You an also do 'make install' which will build the library then install 
# the archive in the LIB_DEST_DIR on your system.  It also installs the header 
# and template files in the HDR_DEST_DIR directory on your system.
#   If you do an install then decide you didn't really want to install it, just
# do 'make remove' and the library and headers will be removed.
# -----------------------------------------------------------------------------

### Set these directories to whatever is appropriate for your system.  These 
### used only if you do a 'make install'.  They specify where the library and
### header files should be installed.
HDR_DEST_DIR=/usr/local/include
LIB_DEST_DIR=/usr/local/lib

### If you want to define any of the GA library pre-processor directives, do it
### here.  See the config.h file for all of the options.  You can either define
### them there or do it here.
DEFINES= 

### If your system has any special include directories, set them here.
INC_DIRS= -I..

### Use these for g++ 
C++C= g++
PRELINK= @echo "no prelinking defined"
CC_INC_DIR=/usr/local/gnu/lib/g++-include
CCFLAGS= -Wall -O $(INC_DIRS) $(DEFINES)

### If you're on SGI IRIX and have DCC then use these
#C++C= DCC
#PRELINK= /usr/lib/DCC/edg_prelink $(OBJS)
#CC_INC_DIR=/usr/include/CC
#CCFLAGS= +w +pp -O -g $(INC_DIRS) $(DEFINES)

### Make sure these are OK for your particular flavor of unix.
INSTALL= install
AR= ar rvs

# -----------------------------------------------------------------------------
# You shouldn't have to change anything after this.
# -----------------------------------------------------------------------------
LIB= libga.a

HDRS= ga.h gaconfig.h gatypes.h gaid.h garandom.h gaerror.h \
 GAEvalData.h GAParameter.h GAStatistics.h \
 GABaseGA.h GASStateGA.h GASimpleGA.h GAIncGA.h GADemeGA.h \
 GASelector.h GAScaling.h GAPopulation.h GAGenome.h GAMask.h \
 GABinStr.h gabincvt.h GAAllele.h GAArray.h GANode.h \
 GA1DBinStrGenome.h GA2DBinStrGenome.h GA3DBinStrGenome.h GABin2DecGenome.h \
 GA1DArrayGenome.h GA2DArrayGenome.h GA3DArrayGenome.h \
 GAStringGenome.h GARealGenome.h \
 GATreeBASE.h GATree.h GATreeGenome.h GAListBASE.h GAList.h GAListGenome.h 
SRCS= garandom.C gaerror.C GAParameter.C GAStatistics.C \
 GABaseGA.C GASStateGA.C GASimpleGA.C GAIncGA.C GADemeGA.C \
 GASelector.C GAScaling.C GAPopulation.C GAGenome.C \
 GABinStr.C gabincvt.C GAAllele.C GAStringGenome.C GARealGenome.C \
 GA1DBinStrGenome.C GA2DBinStrGenome.C GA3DBinStrGenome.C GABin2DecGenome.C \
 GA1DArrayGenome.C GA2DArrayGenome.C GA3DArrayGenome.C \
 GATreeBASE.C GATree.C GATreeGenome.C GAListBASE.C GAList.C GAListGenome.C
OBJS= garandom.o gaerror.o GAParameter.o GAStatistics.o \
 GABaseGA.o GASStateGA.o GASimpleGA.o GAIncGA.o GADemeGA.o \
 GASelector.o GAScaling.o GAPopulation.o GAGenome.o \
 GABinStr.o gabincvt.o GAAllele.o \
 GA1DBinStrGenome.o GA2DBinStrGenome.o GA3DBinStrGenome.o GABin2DecGenome.o \
 GA1DArrayGenome.o GA2DArrayGenome.o GA3DArrayGenome.o \
 GATreeBASE.o GATree.o GATreeGenome.o GAListBASE.o GAList.o GAListGenome.o
TMPL_SRCS= GAAllele.C \
 GA1DArrayGenome.C GA2DArrayGenome.C GA3DArrayGenome.C \
 GATree.C GATreeGenome.C GAList.C GAListGenome.C \
 GAStringGenome.C GARealGenome.C

.SUFFIXES: .o .C
.C.o:
	$(C++C) $(CCFLAGS) -c $<

$(LIB): $(OBJS)
	$(PRELINK)
	$(AR) $(LIB) $?
	@echo $(LIB) is now up-to-date
.c.a:;
.C.a:;

install:: $(LIB)
	$(INSTALL) $(LIB) $(LIB_DEST_DIR)
	rm -rf $(HDR_DEST_DIR)/ga; mkdir $(HDR_DEST_DIR)/ga
	cp $(HDRS) $(TMPL_SRCS) ../VERSION $(HDR_DEST_DIR)/ga

remove:
	rm -rf $(LIB_DEST_DIR)/$(LIB) $(HDR_DEST_DIR)/ga

clean:
	rm -rf $(LIB) *~ *.bak *.out *.o core

depend:
	makedepend -I$(CC_INC_DIR) $(INC_DIRS) $(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.
