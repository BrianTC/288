#!/bin/bash
i=0;
maxTime=60;
interval=60;
while [ $i -lt $maxTime ]; do
	((i++))
	DATE=`date +%Y-%m-%d:%H:%M:%S`
	wget -b -O stock/$DATE.html http://online.wsj.com/mdc/public/page/2_3021-activnyse-actives.html
	java -jar /usr/share/java/tagsoup.jar --files stock/$DATE.html 
	rm stock/$DATE.html
	#python sqlUpdate stock/$DATE.html
	sleep $interval
done
