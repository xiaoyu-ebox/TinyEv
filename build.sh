#!/bin/bash

if [ $# == 0 ]; then
	aclocal
	autoheader
	autoconf
	libtoolize -f -c
	automake --add-missing
	./configure
fi

make CXXFLAGS="-std=c++11 " && sudo make install

