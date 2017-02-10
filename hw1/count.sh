#!/bin/bash
arr=(ls /bin/*)
for l in {a..z}
do
	echo "$l `eval ${arr[@]} | grep  /bin/$l.* | wc -l`"
done
