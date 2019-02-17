/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:39:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 05:29:48 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	sub(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	int			args[3];
	int			tmp;

	fill_struct(env, cur_process, &decode);
	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	idx = 0;
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE)
			return (ret);
		args[idx] = *((int *)decode.tab[idx].value);
		idx++;
	}
	tmp = *((int *)cur_process->reg[args[0] - 1]);
	tmp -= *((int *)cur_process->reg[args[1] - 1]);
	ft_memcpy(cur_process->reg[args[2] - 1], &tmp, sizeof(int));
	return (ret);
}
