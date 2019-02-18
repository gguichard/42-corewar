/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:39:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 09:05:03 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	sub(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			idx;
	int			value;

	(void)env;
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	idx = 0;
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE)
			return (ret);
		idx++;
	}
	ft_printf("sub r%d r%d r%d\n", decode.tab[0].value, decode.tab[1].value, decode.tab[2].value);
	value = (int)cur_process->reg[(int)decode.tab[0].value - 1];
	value -= (int)cur_process->reg[(int)decode.tab[1].value - 1];
	cur_process->reg[(int)decode.tab[2].value - 1] = (uint32_t)value;
	cur_process->carry = (value == 0);
	return (ret);
}
