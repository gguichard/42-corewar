/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:01:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 00:40:56 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	ft_and(t_env *env, t_process *cur_process, unsigned char *str)
{
	int				idx;
	t_decode		decode;
	unsigned char	*tmp;
	unsigned char	args[3][REG_SIZE];

	idx = 0;
	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	while (idx < 2)
	{
		if (decode.tab[idx].type == DIR_CODE)
			ft_memcpy(args[idx], decode.tab[idx].value, 4);
		else if (decode.tab[idx].type == IND_CODE)
		{
			tmp = get_in_arena(env, 4, cur_process->pc + *((int *)decode.tab[idx].value) % IDX_MOD);
			if (tmp == NULL)
				return (0);
			ft_memcpy(args[idx], tmp, 4);
			free(tmp);
		}
		else if (decode.tab[idx].type == REG_CODE)
		{
			if (!reg_isvalid(decode.tab[idx].value) || !reg_isvalid(decode.tab[2].value))
				return (0);
			ft_memcpy(args[idx], cur_process->reg[*((int *)decode.tab[idx].value) - 1], 4);
		}
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, 4);
	idx = *((int *)args[0]) & *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &idx, REG_SIZE);
	return (1);
}
