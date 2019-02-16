/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multitype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 06:22:25 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	parse_multitype_args(unsigned char *dest, t_env *env
		, t_process *cur_process, t_arg arg)
{
	unsigned char	*tmp;

	if (arg.type == DIR_CODE)
	{
		ft_memcpy(dest, arg.value, 4);
		return (4);
	}
	else if (arg.type == REG_CODE)
	{
		ft_memcpy(dest
				, cur_process->reg[*((int *)arg.value) - 1], 4);
		return (1);
	}
	else if (arg.type == IND_CODE)
	{
		tmp = get_in_arena(env, 4
				, cur_process->pc + *((int *)arg.value) % IDX_MOD);
		if (tmp == NULL)
			return (0);
		ft_memcpy(dest, tmp, 4);
		free(tmp);
		return (2);
	}
	return (0);
}
