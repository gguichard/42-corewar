.name "unicorn"
.comment "blblblblblblblblblblblblblblbl"

init: sti r1,%:live,%1
ld %90,r2
ld %6,r3
ld %0,r4
ld 123,r5

live:live%1
sti r4,r2,r4
add r4,r3,r4
and r1,%0,r1
zjmp%:live
