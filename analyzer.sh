#!/bin/zsh
./corewar -dump 5000 -n -1 ~/vm_champ/champs/Gagnant.cor | grep ADV > our
~/vm_champ/corewar -d 5000 -v 16 ~/vm_champ/champs/Gagnant.cor | grep ADV | cut -d' ' -f1-5 > zaz
diff -y zaz our
