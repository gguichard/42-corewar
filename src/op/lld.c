/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 21:25:32 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	lld(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	t_decode		decode;
	int				reg;
	unsigned char	value[REG_SIZE];
	unsigned char	*tmp;
	int				ret;

	if (!get_args(bytes + 2, *(bytes + 1), &decode))
		return (0);
	ret = 3;
	reg = *((int *)decode.tab[1].value);
	ft_memset(value, 0, REG_SIZE);
	if (decode.tab[0].type == DIR_CODE)
	{
		ft_memcpy(value, decode.tab[0].value, 4);
		ret += 4;
	}
	else if (decode.tab[0].type == IND_CODE)
	{
		tmp = get_in_arena(env, 4
				, cur_process->pc + *((int *)decode.tab[0].value));
		if (tmp == NULL)
			return (0);
		ft_memcpy(value, tmp, 4);
		free(tmp);
		ret += 2;
	}
	ft_memcpy(cur_process->reg[reg - 1], value, REG_SIZE);
	return (ret);
}
