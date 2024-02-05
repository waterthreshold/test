#!/bin/bash
#DIR_PATH=$1
RED='\033[0;31m'
ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
PURPLE='\033[0;35m'
NC='\033[0m'
rainbow=(RED ORANGE YELLOW GREEN BLUE CYAN PURPLE)
RAINBOW_FLAG=0
#getoption(){
while getopts "c:p:" opt; do
	case $opt in 
		c)
			color="${OPTARG^^}"
			[ "$color" == "RAINBOW" ] && RAINBOW_FLAG=1 ||	color=$(eval "echo \$$color")
			;;
		p)
			DIR_PATH=${OPTARG}
			;;
		?)
			echo "Invalid options: -$OPTARG" >&2
			;;
		:)
			echo "Option -$OPTARG requires an argument." >&2
			exit 1
			;;
	esac
done

#}
#getoption
#color=$BLACK
RAINBOW_INDEX=0
for file in `find $DIR_PATH -name "*.c"`
do 
	echo $file 
	while IFS= read -r line
	do
		for ((i=0;i<${#line};i++)); do
			ch=${line:$i:1}
			if [ "$RAINBOW_FLAG" -eq 1 ]; then
				RAINBOW_INDEX=$(( RAINBOW_INDEX % 7))	
				color=$(eval "echo \$${rainbow[$RAINBOW_INDEX]}")
				RAINBOW_INDEX=$(( RAINBOW_INDEX + 1 ))
				printf "\033[1m$color%s" "$ch"
					
			else
				printf "$color%s" "$ch"
			fi
			#echo -e "$RED$ch"
			sleep 0.005
		done 
		echo 
	done < "$file"
done 
