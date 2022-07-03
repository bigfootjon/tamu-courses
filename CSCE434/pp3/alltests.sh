#!/bin/bash
for filename in samples/*.decaf; do
    ./test.sh $filename &>temp
    result=$?
    if [ $result -ne 0 ]; then
        echo "$filename failed!"
    fi
done
rm -f temp
