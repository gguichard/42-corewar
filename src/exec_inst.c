/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_inst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 23:20:11 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 03:54:07 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	(*g_op[])(t_env *env, t_process *cur_process, unsigned char *str) = {
	live,
	ld/*, st, add, sub, ft_and, ft_or, ft_xor, zjump, ldi, sti, ft_fork, lld, lldi, lfork, aff*/
};

int	parsing_inst(unsigned char *str, t_process *cur_process, t_env *env)
{
	int	op_idx;

	op_idx = str[0];
	if (op_idx > 0 && op_idx < 3)
		g_op[op_idx - 1](env, cur_process, str);
	return (0);
}
