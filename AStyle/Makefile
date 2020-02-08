##################
#
# Copyright (C) 2020, Bill Rees All rights reserved.
#
# Redirect the make call to build/gcc
#
#
##################

default:
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyle

install:
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyled install

clobber:
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyled clobber
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyle  clobber

clean:
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyled clean
	 $(MAKE) -C build/gcc prefix=~/usr BIN=astyle  clean

%:
	 $(MAKE) -C build/gcc $(MAKECMDGOALS)

