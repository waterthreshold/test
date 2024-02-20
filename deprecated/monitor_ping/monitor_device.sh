#!/bin/bash
DEVICE_NUM=0
LOG=log/device_log
INTERVAL=30 #second
declare -A homeIOT
declare -A latest_table
latest_table=()
init(){
device_number=$(cat homeIoT_dev.json | jq '.client | length')
END=$((device_number - 1))
for i in $(seq 0 ${END});
do 
KEY=$(cat  homeIoT_dev.json | jq -r ".client[${i}].MAC")
VALUE=$(cat  homeIoT_dev.json | jq -r  ".client[${i}].name")
homeIOT[${KEY}]=${VALUE}
#echo ${homeIOT[$KEY]}
done 
}
show_init(){
		for arr_ref in "${!homeIOT[@]}"; do
			echo "${arr_ref}=${homeIOT[${arr_ref}]}"
		done
}
setting_currentattach (){
	unset current_table
	declare -A current_table
	for i in $(seq 0 ${NUM}); do 
		tmp_mac=$(cat tmp | jq -r ".connDevices[${i}].mac")
		tmp_name=$(cat tmp | jq -r ".connDevices[${i}].name")
		current_table[${tmp_mac}]=${tmp_name}
	done 
}
compare_latest (){
	echo 'start working on it '
}
clone_curent2latest ()
{
	echo "start work on it"
	unset latest_table
	declare -A latest_table
}
compare_HOMEIOT(){
	NUM=$(($1 - 1 ))
	echo "-----------${NUM}------------------------------------"
	unset boolean_array
	declare -A boolean_array
	for mac in "${!homeIOT[@]}"; do 
		boolean_array[${mac}]="0"
	done 
	for i in $(seq 0 ${NUM}); do 
		tmp_mac=$(cat tmp | jq -r ".connDevices[${i}].mac")
		[ "${boolean_array[${tmp_mac}]}" == "0"  ] && boolean_array[${tmp_mac}]="1"
	done 
	for mac in ${!homeIOT[@]}; do
#		echo "${boolean_array[${mac}]}"
		if [  "${boolean_array[${mac}]}" == "0" ]; then 
			echo "Cannot find device ${mac} name:${homeIOT[$mac]}"
		fi
	done 
	echo "-----------------------------------------------"
}
init
#show_init
[ ! -e "$LOG" ] && touch $LOG || rm $LOG;touch $LOG
while true
do
DETECCT_NUM=`../curl_attachdev.sh $1 | tee  tmp |  jq -r ".numberOfDevices"`
#../curl_attachdev.sh $1 
#[ "$?" -ne 0 ] && echo "fetch error"; sleep $INTERVAL ;continue;
#setting_currentattach
compare_HOMEIOT $DETECCT_NUM
#compare_latest 

echo "$DETECCT_NUM"
if [ "$DEVICE_NUM" -ne "$DETECCT_NUM" ]; 
then
	DEVICE_NUM=${DETECCT_NUM}
	echo "`date +"%Y/%m/%d-%H:%M:%S"`" >> $LOG
	echo "---------------Device Num: $DEVICE_NUM--------------" >> $LOG
	cat tmp >> $LOG
	echo "----------------------------------------------------" >> $LOG
fi
sleep $INTERVAL
done 
