#!/bin/bash
function main {
    loc=$1
    index=0;
    declare -a arr
    for file in $loc* ; do
	arr[$index]=$file
	((index++))
    done
    reverse $index $arr
}
function reverse {
    index=$1
    arr=$2
    while [ $index -ge 0 ];  do
	echo ${arr[$index]} 
	((index--))
    done
}

main $1
