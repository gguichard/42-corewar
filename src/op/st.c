/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:15:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 07:13:11 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

int	st(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	uint32_t	args[2];

	fill_decode(env, cur_process, &decode, 2);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), REG_DIR) + 2;
	if ((decode.tab[1].type == REG_CODE || decode.tab[1].type == IND_CODE)
			&& decode.tab[0].type == REG_CODE)
	{
		store_multitype(args, decode, decode.tab[1], 0);
		args[1] = (int)decode.tab[0].value;
		if (decode.tab[1].type != REG_CODE)
			write_in_arena(env, (uint8_t *)&cur_process->reg[args[0] - 1], 4
				, cur_process->pc + args[1] % IDX_MOD);
		else
		{
			args[1] = (int)decode.tab[1].value;
			cur_process->reg[args[1] - 1] = cur_process->reg[args[0] - 1];
		}
	}
	if (env->debug == DEBUG_ON)
		debug_mode_nodecode("st", (int *)args, 2);
	return (ret);
}
