for W in $(seq 1 20); do
	for B in $(seq 1 20 3520); do
		make fifo > /dev/null
		srt=$(($(date +%s%N)/1000000))
		./client -n 1000 -w $W -b $B > /dev/null
		end=$(($(date +%s%N)/1000000))
		T=$((end-srt))
		result="$W,$B,$T"

		echo $result
		echo $result >> output.csv

	done
done
