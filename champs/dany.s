.name "Daenerys Targaryen"
.comment "Queen Daenerys Stormborn of the House Targaryen, the First of Her Name, Queen of the Andals, the Rhoynar and the First Men, Lady of the Seven Kingdoms and Protector of the Realm, Lady of Dragonstone, Queen of Meereen, Khaleesi of the Great Grass Sea, the Unburnt, Breaker of Chains, Mother of Dragons and winner of corewar."

l2:		sti r1, %:live, %10
		and r16, %0, r1

live:	live %1
		zjmp %:live
