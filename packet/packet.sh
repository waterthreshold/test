#!/bin/sh
MAGIC='*#$^'
FIRMWARE_NAME=${1}
FILE_NAME="${1}.chk"
FILE_NAME_TMP=".tmp.chk"
VERSION=${2}
BOARD_ID=${3}
SKU_ID=1
KERNEL_CHECKSUM=0
ROOTFS_CHKSUM=0
KERNEL_LENGTH=0
ROOTFS_LENGTH=0
IMAGE_CHECKSUM=0
HEADER_CHECKSUM=0

calculate_cksum(){
c0=0
c1=0
hexdump=$(xxd -p $1)
for byte in  $(echo "$hexdump" | awk '{for (i=1;i<=length;i+=2) print substr($0 ,i ,2)}'); 
do
	byte_decimal=$(printf "%d" "0x$byte")
	c0=$(( c0 + byte_decimal))
	c1=$(( c0 + c1 ))

done 
b=$(( (c0 & 0xFFFF) + ((c0 >> 16) & 0xFFFF) ))
c0=$(( ((b>>16)+ b) & 0xFFFF )) 

b=$(( (c1 & 0xFFFF) + ((c1 >> 16) & 0xFFFF) ))
c1=$(( ((b>>16)+ b ) & 0xFFFF ))
checksum=$(( (c1 << 16) | c0 )) 
printf "%08x" $checksum
return $checksum 
} 
die (){
	echo "strictly following the rule packet.sh <Filename> <Version> <Board ID>"
	echo "ex. packet.sh  R7000-V1.0.11.136_10.2.120.w 1.0.11.136_10.2.120 U12H270T00_NETGEAR"
	exit 127
}
[ $# -ne 3 ] && die  
[  -e $FILE_NAME_TMP ] && rm $FILE_NAME_TMP
touch $FILE_NAME_TMP
#hexdump=$(xxd -p "$FIRMWARE_NAME")
#for byte in $(echo "$hexdump" | awk '{for (i=1;i<= length;i+=2) print substr($0, i ,2)}'); do
#	byte_decimal=$(printf "%d" "0x$byte")
#	echo $byte_decimal
#	KERNEL_LENGTH=$(( KERNEL_LENGTH + byte_decimal ))
#done
KERNEL_LENGTH=$(stat -c %s "$FIRMWARE_NAME")

printf "%08x" $KERNEL_LENGTH
#KERNEL_CHECKSUM=$(printf "%d" "0x6A17768F") 
KERNEL_CHECKSUM=$(./fxcn_cksum $FIRMWARE_NAME)
echo $KERNEL_CHECKSUM
IMAGE_CHECKSUM=$KERNEL_CHECKSUM

printf "%s" $MAGIC >> $FILE_NAME_TMP
printf "%08x" $(( 40 + ${#BOARD_ID})) | xxd -r -p >> $FILE_NAME_TMP 
printf "%02x" $SKU_ID | xxd -r -p >> $FILE_NAME_TMP
MAIN_VER_STR=${VERSION%%_*}
SUB_VER_STR=${VERSION##*_}
echo "main version: $MAIN_VER_STR sub version: $SUB_VER_STR"
IFS='.' read -ra MAIN_VER <<< "$MAIN_VER_STR"
for byte in "${MAIN_VER[@]}"; do
printf "%02x" $byte  | xxd -r -p >> $FILE_NAME_TMP
done
IFS='.' read -ra SUB_VER <<< "$SUB_VER_STR"
for byte in "${SUB_VER[@]}"; do
printf "%02x" $byte | xxd -r -p  >> $FILE_NAME_TMP
done
printf "%08x" $KERNEL_CHECKSUM | xxd -r -p >> $FILE_NAME_TMP
printf "%08x" $ROOTFS_CHECKSUM | xxd -r -p >> $FILE_NAME_TMP
printf "%08x" $KERNEL_LENGTH  | xxd -r -p  >> $FILE_NAME_TMP
printf "%08x" $ROOTFS_LENGTH  | xxd -r -p  >>  $FILE_NAME_TMP
printf "%08x" $IMAGE_CHECKSUM  | xxd -r -p  >>  $FILE_NAME_TMP
printf "%08x" $HEADER_CHECKSUM | xxd -r -p  >>  $FILE_NAME_TMP
printf "%s" $BOARD_ID >> $FILE_NAME_TMP

#hexdump=$(xxd -p "$FILE_NAME_TMP")
calculate_cksum $FILE_NAME_TMP
#HEADER_CHECKSUM=$(printf "%d" "0x1C690B05")
HEADER_CHECKSUM=$(calculate_cksum $FILE_NAME_TMP)

printf "%08x" "0x$HEADER_CHECKSUM" 
file_size=$( stat -c %s "$FILE_NAME_TMP")
new_size=$(( file_size - ${#BOARD_ID} - 4))
dd if="$FILE_NAME_TMP" of="$FILE_NAME" bs=1 count="$new_size"
printf "%08x" "0x$HEADER_CHECKSUM" | xxd -r -p  >>  $FILE_NAME
printf "%s" $BOARD_ID >> $FILE_NAME
cat "$FILE_NAME" "$FIRMWARE_NAME" > $FIRMWARE_NAME-`date +'%s'`.chk
rm $FILE_NAME_TMP
