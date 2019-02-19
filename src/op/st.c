/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:15:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 03:34:47 by vifonne          ###   ########.fr       */
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
	uint32_t	buffer;
	int			reg;
	int			value;

	fill_decode(env, cur_process, &decode, 2);
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), REG_DIR);
	if ((decode.tab[1].type == REG_CODE || decode.tab[1].type == IND_CODE)
			&& decode.tab[0].type == REG_CODE)
	{
		store_multitype(&buffer, decode, decode.tab[1], 0);
		reg = (int)decode.tab[0].value;
		value = (int)buffer;
		ft_printf("st r%d %d\n", reg, value);
		if (decode.tab[1].type != REG_CODE)
			write_in_arena(env, (uint8_t *)&cur_process->reg[reg - 1], 4
				, cur_process->pc + value % IDX_MOD);
		else
		{
			value = (int)decode.tab[1].value;
			cur_process->reg[value - 1] = cur_process->reg[reg - 1];
		}
	}
	return (ret + 2);
}
