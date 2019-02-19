/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:55:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 06:43:32 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	add(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	int			value;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	idx = 0;
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE)
			return (ret);
		idx++;
	}
	value = (int)cur_process->reg[(int)decode.tab[0].value - 1];
	value += (int)cur_process->reg[(int)decode.tab[1].value - 1];
	cur_process->reg[(int)decode.tab[2].value - 1] = (uint32_t)value;
	cur_process->carry = (value == 0);
	if (env->debug == DEBUG_ON)
		debug_mode("add", decode, 3);
	return (ret);
}
