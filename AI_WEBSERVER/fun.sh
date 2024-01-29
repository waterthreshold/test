#!/bin/bash
my_list=("C" "go" "python" "C++" "haskell" "javascript" "rust" )
declare -A my_dict
declare -A comment
comment["C"]="//"
comment["go"]="//"
comment["python"]="#"
comment["C++"]="//"
comment["haskell"]="--"
comment["javascript"]="//"
comment["rust"]="//"

my_dict["C"]="c"
my_dict["go"]="go"
my_dict["python"]="py"
my_dict["Cpp"]="cpp"
my_dict["haskell"]="hs"
my_dict["javascript"]="js"
my_dict["rust"]="rs"
for item in "${my_list[@]}"; do
	[ ! -d "$item" ] && mkdir ${item} 
	LOWERCASE_ITEM=${item,,}
	SERVER_CODEPATH="${item}/server.${my_dict[$item]}"
	READMEMD_PATH="${item}/README.md"
	MESSAGE="please create a web server sample code using ${LOWERCASE_ITEM} language and also teach me how to build and run it"	
	echo "SERVER_CODEPATH=$SERVER_CODEPATH READMEMD_PATH=$READMEMD_PATH"
	echo $MESSAGE
	curl -X POST https://d27vkanbfmjob6.cloudfront.net/api/chatbot/v1/chatWithKnowledge -H 'Content-Type: application/json'   -d "{\"chatMessage\":\"${MESSAGE}\",\"lang\": \"tw\", \"userEmail\":\"\",\"userName\":\"\",\"userId\":\"b6a9825b-9230-4667-8d0a-eae140d3ec7a\"}" | jq -r '.result' | jq -r '.content'  > $READMEMD_PATH
	sed -i 's/<\/br>/\n/g' $READMEMD_PATH
	echo "${comment[$item]} This $item Program generate by AI" > $SERVER_CODEPATH
	cat ${READMEMD_PATH}  | sed -n  "/\`\`\`${item,,}/{:start \/\`\`\`\n/!{N;b start};p}" | sed '1d;$d' | sed '$d' >> $SERVER_CODEPATH
done


