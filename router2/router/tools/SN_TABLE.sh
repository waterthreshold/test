#!/bin/sh 
STR="'0'"
for i in `seq 1 9`; do
	STR="${STR}, '${i}'"
done 
for i in {A..Z}; do
	if [ "$i" = "I" -o  "$i" == "Q" -o  "$i" == "O" -o  "$i" == "Z" ]; then
		continue
	fi
	STR="${STR}, '${i}'"
done

echo -e "{${STR}};"