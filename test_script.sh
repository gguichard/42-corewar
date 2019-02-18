#!/bin/zsh
echo -n "Dump max: "
read max_dump
echo -n "Dump offset: "
read offset
for i in `seq $offset $max_dump`
do
	~/vm_champs/corewar -d $i $1 $2 | grep '^0x' > zaz
	./corewar -dump $i -n -1 $1 -n -2 $2 | grep '^0x' > our
	diff zaz our > diff
	echo "Cycle: $i"
	cat diff
	echo ""
	rm -f our zaz diff
done
