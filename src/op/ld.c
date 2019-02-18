/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 08:30:48 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ld(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	uint32_t	value;
	int			reg;

	ret = decode_args(&decode, bytes + 2, *(bytes + 1), REG_DIR);
	fill_decode(env, cur_process, &decode);
	if ((decode.tab[0].type == IND_CODE || decode.tab[0].type == DIR_CODE)
			&& decode.tab[1].type == REG_CODE)
	{
		store_multitype(&value, decode, decode.tab[0], 0);
		reg = (int)decode.tab[1].value;
		cur_process->reg[reg - 1] = value;
		ft_printf("ld %d r%d\n", value, reg);
		cur_process->carry = (value == 0);
	}
	return (ret + 2);
}
