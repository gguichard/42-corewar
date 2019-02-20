/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:58:20 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 03:30:40 by vifonne          ###   ########.fr       */
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
			, "lldi"
			, arg1
			, arg2
			, reg
			, addr);
}

int			lldi(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	uint32_t		args[3];
	int				addr;
	uint32_t		value;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE && decode.tab[0].type != BAD_REG)
	{
		store_multitype(args, decode, decode.tab[0], 0);
		store_multitype(args + 1, decode, decode.tab[1], 0);
		addr = (int)args[0] + (int)args[1];
		args[2] = (int)decode.tab[2].value;
		fill_buff_from_arena(env, (uint8_t *)&value, 4, cur_process->pc + addr);
		swap_bytes((uint8_t *)&value, 4);
		cur_process->reg[(int)decode.tab[2].value - 1] = (uint64_t)value;
		cur_process->carry = (value == 0);
	}
	if (env->debug == DEBUG_ON)
		debug_mode((int)args[0], (int)args[1], (int)decode.tab[2].value
				, cur_process->pc + addr);
	return (ret);
}
