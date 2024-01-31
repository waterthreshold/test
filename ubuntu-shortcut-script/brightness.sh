#!/bin/bash
brightness_interval=0.1
outputname="eDP"

get_outputname (){
	outputname=`xrandr --listmonitors | grep 0: | awk '{print $NF}'`
	[ -z "$outputname" ] && echo "capture nothing"
}
ACTION=$1 
get_outputname
current_brightness=`xrandr --verbose | awk '/Brightness/ { print $2}'`


case "$ACTION" in 
	"up")
		new_brightness=$(echo "scale=1;${current_brightness} + ${brightness_interval}" | bc)
	;;
	"down")
		new_brightness=$(echo "scale=1;${current_brightness} - ${brightness_interval}" | bc)
	;;
esac	
echo "xrandr --output $outputname --brightness $new_brightness"
xrandr --output $outputname --brightness $new_brightness
