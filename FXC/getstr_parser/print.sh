#!/bin/sh
pattern='<%\ *([^("]+)\("([^"]+)"\);\ *%>'
STRING_TABLE="string_table"
database_file="strtable.db"
die()
{
	msg=$1
	echo $msg
	exit 127
}
create_database (){
	str_tbl_pattern='([^="]+)="([^"]+)"'
	[ ! -e "$STRING_TABLE" ] && die "String table not found !!"
	COMMAND="CREATE TABLE IF NOT EXISTS strtbl ( KEY TEXT PRIMARY KEY,VALUE TEXT );"
#	COMMAND=$(cat <<EOL
#		CREATE TABLE IF NOT EXISTS strtbl (
#			KEY TEXT PRIMARY KEY,
#			VALUE TEXT
#	);
#	EOL
#	)
	sqlite3 "$database_file" "$COMMAND"
	while read line ; do
		
		if [ -n "`echo $line | grep -e '^[0-9a-zA-Z]'`" ]; then
			# echo $line
			str_key=$(echo $line | cut -d"=" -f 1)
			str_val=$(echo $line | sed -E 's/([^="]+)="([^"]+)"/\2/')
			# echo "${str_key}: ${str_val}"
			COMMAND="INSERT INTO strtbl (KEY,VALUE) VALUES ('${str_key}','${str_val}');"
			sqlite3 "$database_file" "$COMMAND"
		fi
	done < $STRING_TABLE
	
}
	
	
sql_search()
{	
	key=$1
	value=`sqlite3 "$database_file" "SELECT VALUE FROM strtbl WHERE KEY=\"${key}\";"`
	value=$(echo "$value" | tr '\r' ' ')
	echo $value
}

[ ! -e "$database_file" ] && create_database 
# exit 
while [ "$#" -gt "0" ]; do
shift
file=$1
echo "FILE: $file"
#tmp=$(echo "$file" | grep -E "*\.htm$")
#[ -z "$tmp" ] && continue
while read line; do

matches=$(echo $line | grep -oP "$pattern")
# echo $matches
while IFS= read -r match; do
fun=$(echo $match | sed -E 's/<%\ *([^("]+)\("([^"]+)"\);\ *%>/\1/')
val=$(echo $match | sed -E 's/<%\ *([^("]+)\("([^"]+)"\);\ *%>/\2/')

[ -n "$fun" ] && echo "[$match] $fun: $val"
if [ "$fun" = "getstr" ]; then
sub_text=`sql_search ${val}`
if [[ $sub_text == *"/"* ]]; then
	sub_text=$(echo "$sub_text" | sed 's/\//\\\//g')
	echo "detected !! $sub_text"
	sed -i "s/$match/$sub_text/g" $file
else 		
# echo -n $sub_text > test.bin
	echo $sub_text
	sed -i "s/$match/$sub_text/g" $file
fi
elif [ "$fun" = "nvram_get" ]; then
sub_text="NVRAM_${val}"
sed -i "s/$match/$sub_text/g" $file
elif [ "$fun" = "nvram_invmatch"  ]; then 
sed -i "s/$match//g" $file
elif [ "$fun" = "nvram_match"  ]; then 
sed -i "s/$match//g" $file
fi
done <<< "$matches"

done < $file
done
