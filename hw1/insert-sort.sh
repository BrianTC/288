#!/bin/bash
arr=($@)
#echo ${arr[@]}
for i in `seq 0 $((${#arr[@]} - 1))`; do
	j=$i
	j_sub=$((j - 1))
	if [ $j -le 0 ]; then
		continue
	fi
	while [ ${arr[$j_sub]} -gt ${arr[$j]} ]; do
		temp=${arr[$j]}
		arr[$j]=${arr[$j_sub]}
		arr[ $j_sub ]=$temp
		j=$j_sub
		j_sub=$((j_sub - 1))
		if [ $j -le 0 ]; then
		      break
		fi
				
	done
done
echo ${arr[@]}
