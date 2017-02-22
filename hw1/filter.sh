#!/bin/bash
function main {
    loc=$1 #arg1
    arr=(`du $loc* -b -d 0`)
    avg=
    average
    filter
}
function average {
    fcount=$((${#arr[@]}/2))
    sum=0
    for((i=0;i<${#arr[@]};i+=2)); do
	#echo ${arr[$i]}
	sum=$((sum+${arr[$i]}))
    done
    avg=$((sum/fcount))
}
function filter {
    for((i=0;i<${#arr[@]};i+=2)); do
	if [ ${arr[i]} -gt $avg ]; then
            echo ${arr[$((i + 1))]}
	fi
    done
}
main $1
