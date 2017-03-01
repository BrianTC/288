#!/bin/bash
views=(`cat index.html | egrep -o "[0-9][0-9]?[0-9]?(,[0-9]+)* views" | cut -d" " -f1`)
IFS=$'\n'
duration=(`cat index.html | egrep -o "Duration: ([0-9]+:)*[0-9]+" | cut -d" " -f2`)
IFS=$'\n'
unames=(`cat index.html | egrep -o "class=\"yt-lockup-byline yt-ui-ellipsis yt-ui-ellipsis-2\"><a.*</a>" | cut -d">" -f3 | cut -d"<" -f1`)
vid_id=(`cat index.html | egrep -o "watch\?v=[a-zA-Z0-9_-]+"`)
IFS=$'\n'
title=(`cat index.html | egrep -o "dir=\"ltr\">.*<" | cut -d">" -f2 | cut -d"<" -f1`)
#echo Title,Username,Views,Duration,Vid_ID > stats.csv
for (( i=0;i<${#views[@]};i++ )); do
	echo ${title[$i]//,/},${unames[$i]//,/},${views[$i]//,/},${duration[$i]},${vid_id[ $((i * 2)) ]} >> stats.csv
done

