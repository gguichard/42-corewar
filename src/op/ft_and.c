/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:01:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 03:53:00 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(uint32_t *args, int r1)
{
	ft_printf("%-5s: %d & %d r%d\n"
			, "and"
			, (int)args[0]
			, (int)args[1]
			, r1);
}

int			ft_and(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	uint32_t	args[2];
	uint32_t	tmp;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	idx = 0;
	while (idx < 2)
	{
		if (decode.tab[idx].type == BAD_REG)
			return (ret);
		store_multitype(args + idx, decode, decode.tab[idx], 0);
		idx++;
	}
	tmp = args[0] & args[1];
	cur_process->reg[(int)decode.tab[2].value - 1] = tmp;
	cur_process->carry = (tmp == 0);
	if (env->debug == DEBUG_ON)
		debug_mode(args, (int)decode.tab[2].value);
	return (ret);
}
