/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multitype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 05:30:13 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	parse_lmultitype(unsigned char *dest, t_env *env, t_process *cur_process
		, t_arg arg)
{
	unsigned char	*tmp;

	if (arg.type == DIR_CODE)
	{
		ft_memcpy(dest, arg.value, REG_SIZE);
		return (4);
	}
	else if (arg.type == REG_CODE)
	{
		ft_memcpy(dest, cur_process->reg[*((int *)arg.value) - 1], REG_SIZE);
		return (1);
	}
	else if (arg.type == IND_CODE)
	{
		tmp = get_in_arena(env, 4, cur_process->pc + *((int *)arg.value));
		if (tmp == NULL)
			return (0);
		ft_memcpy(dest, tmp, REG_SIZE);
		free(tmp);
		return (2);
	}
	return (0);
}

int	parse_multitype(unsigned char *dest, t_env *env, t_process *cur_process
		, t_arg arg)
{
	unsigned char	*tmp;

	if (arg.type == DIR_CODE)
	{
		ft_memcpy(dest, arg.value, REG_SIZE);
		return (4);
	}
	else if (arg.type == REG_CODE)
	{
		ft_memcpy(dest, cur_process->reg[*((int *)arg.value) - 1], REG_SIZE);
		return (1);
	}
	else if (arg.type == IND_CODE)
	{
		tmp = get_in_arena(env, 4
				, cur_process->pc + *((int *)arg.value) % IDX_MOD);
		if (tmp == NULL)
			return (0);
		ft_memcpy(dest, tmp, REG_SIZE);
		free(tmp);
		return (2);
	}
	return (0);
}

int	parse_imultitype(unsigned char *dest, t_env *env, t_process *cur_process
		, t_arg arg)
{
	if (arg.type == DIR_CODE)
	{
		ft_memset(dest, 0, 4);
		ft_memcpy(dest, arg.value, 2);
		return (2);
	}
	else
		return (parse_multitype(dest, env, cur_process, arg));
}

int	parse_limultitype(unsigned char *dest, t_env *env, t_process *cur_process
		, t_arg arg)
{
	if (arg.type == DIR_CODE)
	{
		ft_memset(dest, 0, 4);
		ft_memcpy(dest, arg.value, 2);
		return (2);
	}
	else
		return (parse_lmultitype(dest, env, cur_process, arg));
}
