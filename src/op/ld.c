/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 02:49:29 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "corewar.h"
#include "func_op.h"

void	ld(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode	decode;
	int			reg;
	int			value;
	unsigned char	*tmp;

	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	reg = result.tab[1].value;
	if (reg < 1 || reg > 16)
		return (0);
	value = result.tab[0].value;
	if (result.tab[0].type == IND_CODE)
	{
		tmp = get_op(env, 4, env->arena + (cur_process->pc + value % IDX_MOD) % MEM_SIZE);
		value = *((int *)tmp);
		free(tmp);
	}
	else if (result.tab[0].type == REG_CODE)
	{
		if (value < 1 || value > 16)
			return (0);
		value = cur_process->reg[value - 1];
	}
	cur_process->reg[reg - 1] = value;
}
