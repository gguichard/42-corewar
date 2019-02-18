/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:39:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 01:22:17 by gguichar         ###   ########.fr       */
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

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	fill_struct(env, cur_process, &decode);
	idx = 0;
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE)
			return (ret);
		args[idx] = *((int *)decode.tab[idx].value);
		idx++;
	}
	ft_printf("sub r%d r%d r%d\n", args[0], args[1], args[2]);
	tmp = *((int *)cur_process->reg[args[0] - 1]);
	tmp -= *((int *)cur_process->reg[args[1] - 1]);
	ft_memcpy(cur_process->reg[args[2] - 1], &tmp, sizeof(int));
	cur_process->carry = tmp == 0;
	return (ret);
}
