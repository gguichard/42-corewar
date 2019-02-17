#!/bin/zsh
echo -n "Dump max: "
read max_dump
echo -n "Dump offset: "
read offset
for i in `seq $offset $max_dump`
do
	~/vm_champ/corewar -d $i $1 $2 > zaz
	./corewar -dump $i -n -1 $1 -n -2 $2 > our
	sed "1,2d" zaz > tmp_zaz
	mv tmp_zaz zaz
	sed "1,1d" our > tmp_our
	sed '$d' tmp_our > our
	rm -f tmp_our
	diff zaz our > diff
	echo "Cycle: $i"
	cat diff
	echo ""
	rm -f our zaz diff
done
