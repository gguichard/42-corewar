/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:04:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/22 03:51:32 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int arg1, int arg2, int reg, int lvl)
{
	if (lvl == DEBUG_FIRST_LVL)
		ft_printf("%-5s\n", "xor");
	else if (lvl <= DEBUG_THIRD_LVL)
		ft_printf("%-5s: %d & %d r%d\n", "xor", arg1, arg2, reg);
}

int			ft_xor(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	uint32_t	args[2];
	uint32_t	tmp;

	fill_decode(env, cur_process, &decode, 3);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	if (decode.tab[0].type != BAD_REG
			&& decode.tab[1].type != BAD_REG
			&& decode.tab[2].type == REG_CODE)
	{
		idx = 0;
		while (idx < 2)
		{
			store_multitype(&args[idx], decode, decode.tab[idx], 0);
			idx++;
		}
		tmp = args[0] ^ args[1];
		cur_process->reg[(int)decode.tab[2].value - 1] = tmp;
		cur_process->carry = (tmp == 0);
		if (env->debug == DEBUG_ON)
			debug_mode(args[0], args[1], (int)decode.tab[2].value
					, env->debug_lvl);
	}
	return (ret);
}
