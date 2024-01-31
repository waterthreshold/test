#!/bin/bash
NEED_COMMAND="zenity"
die(){
	msg=$1
	echo $1
	exit 127
}
ask_filename(){
	date=`echo $(date '+%Y-%m-%d_%H%M%S')`
	NAME="ScreenShot-${date}.png"
	NAME=`zenity --entry --text="Input sreeshot name" --entry-text "$NAME"`
	[ -z "${NAME}" ] && die "input filename is empty!!"
	echo $NAME
}
SCREENSHOT_DIR="${HOME}/Pictures/ScreenShot"
if ! command -v "$NEED_COMMAND" &> /dev/null; then
	exit 127
fi 
[ ! -d "$SCREENSHOT_DIR" ]  && mkdir $SCREENSHOT_DIR

RESULT=$(zenity --list \
	--title="screenshot" \
	--column="method"  \
	"clipboard" \
	"save" \
	"both" )

case "$RESULT" in 
	clipboard)
		gnome-screenshot -a -c 
		;;
	save)
		filename=`ask_filename`
		filepath=$SCREENSHOT_DIR/$filename
		gnome-screenshot -a -f "$filepath" 
		
		;;
	both)
		filename=`ask_filename`
		filepath=$SCREENSHOT_DIR/$filename
		gnome-screenshot -a -c -f  "$filepath"
		;;
	*)
		;;
esac
