#!/bin/sh
count=0
ALL_FILES=`find $* -name "*.c" -o -name  "*.h" -type f`
echo $*
#easy_way(){

#}
#while read -r file
#do
#	echo $file
#	MULTIPLE_DETECT_FLAG=0
#	while read -r line 
#	do
#		line=`echo $line | sed 's/ //g'`
##		if [ $MULTIPLE_DETECT_FLAG -eq 1  ]; then 
##				
##			if [ "${line:0:2}" = "*/" ]; then 
##				MULTIPLE_DETECT_FLAG=0
##			elif [ -z "${line##*/}" ]; then 
##				MULTIPLE_DETECT_FLAG=0
##			else 
##				continue
##			fi 
##		fi
#
#		if [ "${line:0:2}" = "//" ]; then
#			continue
#		elif [ -z ${line} ]; then 
#			continue
##		elif [ "${line:0:2}" = "/*" -a $MULTIPLE_DETECT_FLAG -eq 0 ]; then
##			MULTIPLE_DETECT_FLAG=1
##			continue
#		fi
#		count=$((count+1))
#	done < $file 
#done  <<< "$ALL_FILES"
#echo $count
count2=0
while read -r filename
do
	echo $filename
	code_lines=$(grep -E -v '^\s*//|^\s*/\*|\*/|^\s*\*' "$filename" | grep -c .)
	count2=$((count2 + code_lines))
done <<< "$ALL_FILES"
echo $count2
#d((count ))
