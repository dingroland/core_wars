# Makefile for GAlib
# Copyright 1994 Massachusetts Institute of Technology
# mbwall 19jun95

LIBSRC_DIR  =ga
EXSRC_DIR   =examples

all: lib examples
lib::
	cd $(LIBSRC_DIR); make -k
examples::
	cd $(EXSRC_DIR); make -k

depend:
	cd $(LIBSRC_DIR); make depend
	cd $(EXSRC_DIR); make depend

clean:
	cd $(LIBSRC_DIR); make -k clean
	cd $(EXSRC_DIR); make -k clean

install:
	cd $(LIBSRC_DIR); make -k install
	cd $(EXSRC_DIR); make -k install

remove:
	cd $(LIBSRC_DIR); make -k remove
	cd $(EXSRC_DIR); make -k remove  
