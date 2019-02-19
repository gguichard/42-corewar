/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:21:10 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 08:03:36 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

int	sti(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	uint32_t	args[3];
	int			addr;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	if (decode.tab[0].type == REG_CODE && decode.tab[1].type != BAD_REG
			&& (decode.tab[2].type == REG_CODE
				|| decode.tab[2].type == DIR_CODE))
	{
		idx = 0;
		while (idx < 3)
		{
			store_multitype(args + idx, decode, decode.tab[idx], 0);
			idx++;
		}
		addr = ((int)args[1] + (int)args[2]) % IDX_MOD;
		write_in_arena(env, (uint8_t *)args, 4, cur_process->pc + addr);
	}
	if (env->debug == DEBUG_ON)
		debug_mode_nodecode_val("sti", (int *)args, 3
				, cur_process->pc + addr);
	return (ret);
}
