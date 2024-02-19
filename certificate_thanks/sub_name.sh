#!/bin/sh
die (){
msg=$1
echo $1
exit 127
}

[ -z "$1" ]  && die "Please provide a name"
OUTPUT_TEX="Thank_$1.tex"
OUTPUT_IMAGE="Thank_$1.png"
OUTPUT_PDF="Thank_$1.pdf"
sed  "s/THESUBTITUTE/$1/g" thankful.tex > "$OUTPUT_TEX"
echo $OUTPUT_TEX
pdflatex "$OUTPUT_TEX"
echo "Do you want to Generate image(.png)"
select yn in "yes" "no"; do	
	case $yn in
		yes) pdftoppm  -png "$OUTPUT_PDF" > "${OUTPUT_IMAGE}";break;;
		no) exit ;;
	esac
done


