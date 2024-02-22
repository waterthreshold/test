#!/bin/sh
token='EIsSolY4Q-UJETzyS4xNxZ-WJZL7QS74'
#url='https://172.18.223.170/u12/api/rest/issues/31646/files/18611'
url='https://172.18.223.170/u12/api/rest'
Mantis_get_all_projects (){
	url="$url/projects"
	content=$(curl -s -k i --location  -X GET $url --header "Authorization: $token")
	echo -n $content
}
Mantis_get_isssues_for_a_project (){
	local page=$2
	url="$url/issues?project_id=$1&page_size=100&page=$page"
#	curl -s -k i --location  -X GET $url --header "Authorization: $token"
	content=$(curl -s -k i --location  -X GET $url --header "Authorization: $token")
	echo -n $content
}
Mantis_get_issues_files(){
	
	local url="$url/issues/$1/files"
	content=$(curl -s -k i --location  -X GET $url --header "Authorization: $token")
	echo -n $content
}
project_id=$1 #218
root_dir=$2
[ ! -d "$root_dir" ] && mkdir $root_dir
#resp=$(Mantis_get_all_projects)
#echo -n $resp
page=1
resp=$(Mantis_get_isssues_for_a_project $project_id $page)
size=$(echo -n $resp | jq '.issues | length')

while true 
do
for ((i=0;i<$size;i++));
do
issue_id=$(echo -n $resp | jq  -r ".issues[$i].id")
summary=$(echo -n $resp | jq  -r ".issues[$i].summary")
description=$(echo -n $resp | jq  -r ".issues[$i].description")
#file_size=$(echo -n $resp | jq  -r ".issues[$i].attachments | length")
#echo $file_size
issue_dir="$root_dir/$issue_id"
mkdir $issue_dir
echo -e "## id: $issue_id\n---\n## SUMMARY \n$summary\n---\n## DESCRIPTION\n$description\n---" > $issue_dir/description
file_resp=$(Mantis_get_issues_files $issue_id)
file_size=$(echo -n $file_resp | jq ".files | length")
[ ${file_size} -gt 0 ] && mkdir $issue_dir/attachment
for ((j=0;j<$file_size;j++))
do
file_content=$(echo -n $file_resp | jq -r ".files[$j].content")
file_filename=$(echo -n $file_resp | jq -r ".files[$j].filename")
echo "issue: $issue_id($i), $j:$file_filename"
echo -n  $file_content | base64 -d   > $issue_dir/attachment/$file_filename
done
#for ((j=0;j<$file_size;j++));
#do
#	file_id=$(echo -n $resp | jq  -r ".issues[$i].attachments[$j].id") 
#	filename=$(echo -n $resp | jq  -r ".issues[$i].attachments.filename")
#	
#	
#done

done

((page++))
echo $page
resp=$(Mantis_get_isssues_for_a_project $project_id $page)
size=$(echo -n $resp | jq '.issues | length')
echo $size
[ $size -eq 0 ] && break 
done
#curl -s -k i --location  -X GET 'https://172.18.223.170/u12/api/rest/users/me' --header "Authorization: $token" --header "X-Mantis-Username: (TC SW) Ziv Wang"
