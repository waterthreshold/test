#!/bin/sh
CURRENT_DIR=`pwd -P`
PROGRAM_NAME=${0##*/}
ROOT_NEED_DIR="userspace kernel"

ROOT_DIR=$CURRENT_DIR
find_rootdir (){
	while [ "${CURRENT_DIR}" != "" ];
	do
	#	echo $CURRENT_DIR
		IS_FIND_THE_DIR=1
		for var in ${ROOT_NEED_DIR}
		do
			ISGOTDIR=`ls -1 ${CURRENT_DIR} | grep $var`
			if [ -z ${ISGOTDIR}  ]; then
				IS_FIND_THE_DIR=0
				break
			fi
		done 
		if [ ${IS_FIND_THE_DIR} -eq 1 ]; then 
			ROOT_DIR=$CURRENT_DIR
			break
		fi   
		CURRENT_DIR=${CURRENT_DIR%/*}
	done 
}

complemnent () {
	cur_word="${COMP_WORDS[COMP_CWORD]}"
	#prev_word=${COMP_WORDS[COMP_CWORD-1]}
	prev_word=$GOTO_DIR
	LS_LIST=`ls $GOTO_DIR`
	echo $LS_LIST
	compgen -W "$LS_LIST"
}

setting_fastpath(){
GOTO_DIR=$ROOT_DIR
case $1 in 
	"acos")
		GOTO_DIR=$GOTO_DIR/userspace/ap/acos
		;;
	"project")
		GOTO_DIR=$GOTO_DIR/userspace/project/acos
		;;
	"kernel")
		GOTO_DIR=$GOTO_DIR/kernel/
		;;
	"userspace")
		GOTO_DIR=$GOTO_DIR/userspace
		;;
			
esac
#echo $GOTO_DIR
}
#complemnent
#complete -F complemnent j

find_rootdir
[ -n "$1" ] && setting_fastpath $1 || GOTO_DIR=$ROOT_DIR
#shift
#while  [ $# -ne 0 ]; do 
#[ -e "$GOTO_DIR/$1" ] && GOTO_DIR="$GOTO_DIR/$1" || exit 127
#shift 
#done 
cd $GOTO_DIR

