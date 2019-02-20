/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 02:01:22 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

static void	debug_mode(int value, int reg)
{
	ft_printf("%-5s: %d r%d\n"
			, "ld"
			, value
			, reg);
}

int			ld(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	uint32_t	args[2];

	fill_decode(env, cur_process, &decode, 2);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), REG_DIR) + 2;
	if ((decode.tab[0].type == IND_CODE || decode.tab[0].type == DIR_CODE)
			&& decode.tab[1].type == REG_CODE)
	{
		store_multitype(args, decode, decode.tab[0], 0);
		args[1] = decode.tab[1].value;
		cur_process->reg[(int)args[1] - 1] = args[0];
		cur_process->carry = (args[0] == 0);
	}
	if (env->debug == DEBUG_ON)
		debug_mode((int)args[0], (int)args[1]);
	return (ret);
}
