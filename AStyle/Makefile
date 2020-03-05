##################
#
# Copyright (C) 2020, Bill Rees All rights reserved.
#
# Redirect the make call to build/gcc
#
#
##################

default: BIN=astyled
default:
	 $(MAKE) -C build/gcc prefix=~/usr BIN=$(BIN)  clean $(BIN) install
#	 $(MAKE) -C build/gcc prefix=~/usr BIN=$(BIN)  $(BIN)
#	 $(MAKE) -C build/gcc prefix=~/usr BIN=$(BIN)  install_debug

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

