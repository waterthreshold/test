#!/bin/sh
increase_volumn () {
	amixer -D pulse sset Master 5%+
}

decrease_volumn (){
	amixer -D pulse sset Master 5%-
}

mute_volumn(){
	MUTE=`pactl list sinks | grep Mute: | cut -d ':' -f 2 | tr -d ' '`
	case "$MUTE" in
		"yes")
			amixer -D pulse sset Master unmute
			;;

		"no")
			amixer -D pulse sset Master mute
			;;
	esac
}

ACTION=$1

case "$ACTION" in
	"up")
		increase_volumn
		;;
	"down")
		decrease_volumn
		;;
	"mute")
		mute_volumn	
		;;
esac
