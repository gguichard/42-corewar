/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:58:20 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 00:47:58 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

int	lldi(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	uint32_t		args[2];
	int				address;
	uint32_t		value;

	ret = decode_args(&decode, bytes + 2, *(bytes + 1), SHORT_DIR) + 2;
	fill_decode(env, cur_process, &decode);
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE
			&& decode.tab[0].type != BAD_REG)
	{
		store_multitype(args, decode, decode.tab[0], 0);
		store_multitype(args + 1, decode, decode.tab[1], 0);
		address = (int)args[0] + (int)args[1];
		ft_printf("lldi %d %d r%d (pc %d)\n", args[0], args[1], (int)decode.tab[2].value, cur_process->pc + address);
		fill_buff_from_arena(env, (uint8_t *)&value, 4
				, cur_process->pc + address);
		swap_bytes((uint8_t *)&value, 4);
		cur_process->reg[(int)decode.tab[2].value - 1] = (uint64_t)value;
		cur_process->carry = (value == 0);
	}
	return (ret);
}
