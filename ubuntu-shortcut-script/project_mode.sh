#!/bin/bash
#PC_SCRENN_ONLY
#DUPLICATE
#EXTEND
#SECOND_SCREEN_ONLY
PRIMARY_INTERFACE=$(xrandr -q | grep  " connected " | grep "primary" | awk '{print $1}')
SECOND_INTERFACE=$(xrandr -q | grep " connected " | grep -v "primary" -m1 | awk '{print $1}')
DEBUG_MODE=0
#debug mode 

 [ "$DEBUG_MODE" -eq "1" ] &&  echo "PRIMARY:${PRIMARY_INTERFACE} SECONDARY:${SECOND_INTERFACE}"

#debug mode


choice=$(zenity	--list \
		--title="Project Mode" \
	   	--width=400 --height=300 \
		--column "Index" \
		--column "mode" \
		0 "Primary screen Only" \
		1 "Duplicate" \
		2 "Extend" \
		3 "Second screen only" )


case $choice in 
	0)
		xrandr --output ${PRIMARY_INTERFACE} --auto --output ${SECOND_INTERFACE} --off
		;;
	1)
		xrandr --output ${PRIMARY_INTERFACE} --auto --same-as ${SECOND_INTERFACE} 
		;;
	2)
		xrandr --output ${PRIMARY_INTERFACE} --auto --left-of ${SECOND_INTERFACE}
		;;
	3)
		xrandr --output ${PRIMARY_INTERFACE} --off --output ${SECOND_INTERFACE} --auto
		;;
	
esac
	

	
