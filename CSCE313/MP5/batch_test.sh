#!/bin/bash
for W in $(seq 1 20); do
	for B in $(seq 1 20); do
		start=$(date +%s)
		./client -n 1000 -w $W >/dev/null 2>&1
		nohup ./dataserver -b $B >/dev/null 2>&1 &
		end=$(date +%s)
		T=$((end-start))
		result="$W,$B,$T"

		echo $result
		echo $result >> output.csv

	done
done
