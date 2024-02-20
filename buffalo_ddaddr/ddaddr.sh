#!/bin/sh
## This script for add file with Buffalo home gateway firmware header
die(){
	msg=$1
	echo $1 
	exit 127
}

[ "$#" -ne 2 ]  && die "please add paramater one  Buffalo gateway router model parameter 2 about firmware file" 
VERSION=2.23
SUBVERSION=1.05
MODEL=$1
HEADERFILE=header.txt
FIRMWARE=$2
OUTPUT_FIRMWARE="Buffalo-${MODEL}_${VERSION}-${SUBVERSION}.bin"
[ -e "$OUTPUT_FIRMWARE" ] && rm $OUTPUT_FIRMWARE
echo "${MODEL} ${VERSION} ${SUBVERSION}" > ${HEADERFILE}
echo -n "filelen=" >> ${HEADERFILE}
FILE_HEADER_LEN=`echo ${HEADERFILE} | wc -c`
FIRMWARE_LEN=$(ls -la ${FIRMWARE} | cut -d' ' -f 5 )
FIRMWARE_STRLEN=${#FIRMWARE_LEN}
echo ${FIRMWARE_LEN}
#SUM=`expr ${FIRMWARE_LEN} + ${FILE_HEADER_LEN} + ${FIRMWARE_STRLEN}`
#echo $SUM
echo ${FIRMWARE_LEN} >> ${HEADERFILE}
cat ${HEADERFILE} ${FIRMWARE} > ${OUTPUT_FIRMWARE}

