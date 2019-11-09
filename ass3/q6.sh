#!/bin/bash
END=10
SUM=0
for((i = 0; i < END; i++));do
cc q6.c
./a.out
OUTPUT=$?
echo $OUTPUT
SUM=$((SUM+OUTPUT))
done
SUM=$((SUM/10))
echo AVERAGE:
echo $SUM
