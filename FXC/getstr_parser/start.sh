#!/bin/sh
if [ "${1}" = "revert" ]; then
	cd ..
	patch -i make.patch -p0 -R
	exit 0
fi
cd ..
patch -i make.patch -p0
cd -
cp strtable.db ../
make -C ../ 

