/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:39:37 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 03:52:46 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "process.h"
#include "corewar.h"
#include "champion.h"
#include "func_op.h"
#include "op.h"

void	set_op_tab(t_op op_tab[])
{
	op_tab[0] = (t_op){"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0};
	op_tab[1] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0};
	op_tab[2] = (t_op){"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0};
	op_tab[3] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1
		, 0};
	op_tab[4] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"
		, 1, 0};
	op_tab[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR
		, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	op_tab[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR
		, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	op_tab[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR
		, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	op_tab[8] = (t_op){"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1};
	op_tab[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
		, 10, 25, "load index", 1, 1};
	op_tab[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
		, 11, 25, "store index", 1, 1};
	op_tab[11] = (t_op){"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1};
	op_tab[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10
		, "long load", 1, 0};
	op_tab[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
		, 14, 50, "long load index", 1, 1};
	op_tab[14] = (t_op){"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1};
	op_tab[15] = (t_op){"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0};
}
