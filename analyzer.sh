#!/bin/zsh
./corewar -dump 5000 -n -1 ~/vm_champ/champs/Gagnant.cor | grep ADV | cut -d' ' -f2 > our
~/vm_champ/corewar -d 5000 -v 16 ~/vm_champ/champs/Gagnant.cor | grep ADV | cut -d' ' -f2 > zaz
diff -y zaz our
