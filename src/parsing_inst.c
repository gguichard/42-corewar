/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_inst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 23:20:11 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 00:50:18 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "corewar.h"

void	(*g_op[])(void) = {live, ld, st, add, sub, ft_and,
			ft_or, ft_xor, zjump, ldi, sti, ft_fork, lld, lldi, lfork, aff};

int		parsing_inst(unsigned char *str, t_process *proc, t_env *data)
{
	int	op_idx;
	int	done;

	op_idx = 0;
	done = 0;
	while (op_idx < 16)
	{
		if (op_idx == str[0])
		{
			done = 1;
			g_op[op_idx]();
		}
		op_idx++;
	}
	(void)proc;
	(void)data;
	return (done);
}
