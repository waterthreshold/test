#!/bin/sh
PROFILE=$1
HEADERNAME=ambitCfg.h

# [ -z "${PROFILE}" ] && CONFIGURE_FILE=config.mk || CONFIGURE_FILE=ambitCfg_$PROFILE.mk
CONFIGURE_FILE=${1-config.mk}
[ ! -e $CONFIGURE_FILE ]  && echo "cannot found $CONFIGURE_FILE" && exit 127
[ -e $HEADERNAME ] && rm $HEADERNAME || touch $HEADERNAME
echo "//This file were Automatically generated file by ${CONFIGURE_FILE}; DO NOT EDIT DIRECTLY." >>  $HEADERNAME
echo >>  $HEADERNAME
echo -e  "#ifndef _AMBITCFG_H\n#define _AMBITCFG_H\n" >>  $HEADERNAME

while read -r line  
do
TMP=$(echo $line | sed 's/ //g' )
[ "${TMP:0:1}" = "#" ] && continue 
key=$(echo $line | awk -F= '{print $1}')
value=$( echo $line | awk -F= '{print $2}')
key="${key#CONFIG_}"
if [ -z  "${key}" -o -z "${value}" ]; then
continue
fi
if [ "$value" = "y" ]; then 
key="__${key}__"
echo -e "#define\t$key" >> $HEADERNAME
else 
echo -e  "#define\t${key}\t${value}" >> $HEADERNAME
fi

done < ${CONFIGURE_FILE}


echo >>  $HEADERNAME
echo "#endif" >>  $HEADERNAME