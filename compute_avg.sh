#!/bin/bash
avg=0
diff=0
result=0
gen=0
number=1
sum=0

GEN=./generator
LEMIN=./lem-in
FILE1=/tmp/file_test1
FILE2=/tmp/file_test2
set -e
set -o pipefail
echo -n "" > $FILE1
echo -n "" > $FILE2
while true
do
	$GEN --big-superposition > $FILE1
	if [[ $(diff $FILE1 $FILE2) ]]
		then
		result="$( $LEMIN < $FILE1 | grep L | wc -l )"
		gen=$( tail -2 $FILE1 | grep '#' | cut -d":" -f2 )
		diff=$(( result - gen ))
		echo "diff = $diff"
		sum=$(( sum + diff ))
		printf "for $number of rounds, average =  "
		echo "scale=1; $sum / $number " | bc
		number=$(( number + 1 ))
	fi
	cat $FILE1 > $FILE2
done
