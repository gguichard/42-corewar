/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_multitype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 01:34:19 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	parse_multitype_args(unsigned char ***args, t_env *env
		, t_process *cur_process, t_decode decode)
{
	int				idx;
	unsigned char	*tmp;

	idx = -1;
	while (++idx < 2)
	{
		if (decode.tab[idx].type == DIR_CODE)
			ft_memcpy(args[idx], decode.tab[idx].value, 4);
		else if (decode.tab[idx].type == IND_CODE)
		{
			tmp = get_in_arena(env, 4
					, cur_process->pc
					+ *((int *)decode.tab[idx].value) % IDX_MOD);
			if (tmp == NULL)
				return (0);
			ft_memcpy(args[idx], tmp, 4);
			free(tmp);
		}
		else if (decode.tab[idx].type == REG_CODE)
		{
			ft_memcpy(args[idx]
					, cur_process->reg[*((int *)decode.tab[idx].value) - 1], 4);
		}
	}
	return (1);
}
