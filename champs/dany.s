.name "Daenerys Targaryen"
.comment "Queen Daenerys Stormborn of the House Targaryen, the First of Her Name, Queen of the Andals, the Rhoynar and the First Men, Lady of the Seven Kingdoms and Protector of the Realm, Lady of Dragonstone, Queen of Meereen, Khaleesi of the Great Grass Sea, the Unburnt, Breaker of Chains, Mother of Dragons and winner of corewar."

init:	sti r1, %:live,%1
		ld %190,r2  # depart de la reecriture
		ld %4,r3	# pad de reecriture
		ld -21, r6	# valeur de la reecriture
		ld %-56,r7	# valeur debut champ
		ld %4,r8	# pad adress

live:	live %1
		add r2,r3,r2 		# incremetation
		sti r6, %:live,r2	#	ecriture
		ldi r7,r8,r6		# assignation new r6
		add r7,r8,r7		# incrementation
		and r4, %0, r4		# set carry 1

		zjmp %:live
