/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 23:54:55 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ld(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode		decode;
	int				reg;
	unsigned char	value[REG_SIZE];
	unsigned char	*tmp;
	int				ret;

	ret = 2;
	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	reg = *((int *)decode.tab[1].value);
	if (reg < 1 || reg > 16)
		return (0);
	ft_memset(value, 0, REG_SIZE);
	if (decode.tab[0].type == DIR_CODE)
	{
		ft_memcpy(value, decode.tab[0].value, 4);
		ret += 4;
	}
	else if (decode.tab[0].type == IND_CODE)
	{
		tmp = get_in_arena(env, 4
				, cur_process->pc + *((int *)decode.tab[0].value) % IDX_MOD);
		if (tmp == NULL)
			return (0);
		ft_memcpy(value, tmp, 4);
		free(tmp);
		ret += 2;
	}
	ft_memcpy(cur_process->reg[reg - 1], value, REG_SIZE);
	return (ret);
}
