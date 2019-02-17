/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multitype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 06:07:22 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "op.h"
#include "func_op.h"

static int	parse_multitype(unsigned char *dest
		, t_decode decode, t_arg arg, int islong)
{
	unsigned char	*tmp;

	if (arg.type == DIR_CODE)
	{
		ft_memcpy(dest, arg.value, REG_SIZE);
		return (4);
	}
	else if (arg.type == REG_CODE)
	{
		ft_memcpy(dest, decode.cur_process->reg[*((int *)arg.value) - 1]
				, REG_SIZE);
		return (1);
	}
	else if (arg.type == IND_CODE)
	{
		if (islong == 0)
			tmp = get_in_arena(decode.env, 4
					, decode.cur_process->pc + *((int *)arg.value) % IDX_MOD);
		else
			tmp = get_in_arena(decode.env, 4
					, decode.cur_process->pc + *((int *)arg.value));

		if (tmp == NULL)
			return (0);
		ft_memcpy(dest, tmp, REG_SIZE);
		free(tmp);
		return (2);
	}
	return (0);
}

int	dispatch_multitype(unsigned char *dest, t_decode decode, t_arg arg, int eb)
{
	int	ret;

	ret = 0;
	if (eb == T_NRML)
		ret = parse_multitype(dest, decode, arg, 0);
	else if (eb == T_LONG)
		ret = parse_multitype(dest, decode, arg, 1);
	else
	{
		if (arg.type == DIR_CODE)
		{
			ft_memset(dest, 0, 4);
			ft_memcpy(dest, arg.value, 2);
			return (2);
		}
		else
		{
			if (eb == T_INDX)
				ret = parse_multitype(dest, decode, arg, 0);
			else if (eb == T_INDX + T_LONG)
				ret = parse_multitype(dest, decode, arg, 1);
		}
	}
	return (ret);
}
