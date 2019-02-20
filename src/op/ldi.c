/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:28:28 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 03:29:26 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int arg1, int arg2, int reg, int addr)
{
	ft_printf("%-5s: %d %d r%d (pc %d)\n"
			, "ldi"
			, arg1
			, arg2
			, reg
			, addr);
}

int			ldi(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int				ret;
	t_decode		decode;
	uint32_t		args[3];
	int				address;
	uint32_t		value;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE
			&& decode.tab[0].type != BAD_REG)
	{
		store_multitype(args, decode, decode.tab[0], 0);
		store_multitype(args + 1, decode, decode.tab[1], 0);
		address = ((int)args[0] + (int)args[1]) % IDX_MOD;
		args[2] = (int)decode.tab[2].value;
		fill_buff_from_arena(env, (uint8_t *)&value, 4
				, cur_process->pc + address);
		swap_bytes((uint8_t *)&value, 4);
		cur_process->reg[(int)decode.tab[2].value - 1] = (uint64_t)value;
	}
	if (env->debug == DEBUG_ON)
		debug_mode((int)decode.tab[0].value, (int)args[1]
				, (int)decode.tab[2].value, cur_process->pc + address);
	return (ret);
}
