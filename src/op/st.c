/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:15:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/17 06:06:49 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

int	st(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;
	int			reg;
	int			to_reg;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	fill_struct(env, cur_process, &decode);
	if ((decode.tab[1].type == REG_CODE || decode.tab[1].type == IND_CODE)
			&& decode.tab[0].type == REG_CODE)
	{
		reg = *((int *)decode.tab[0].value);
		if (decode.tab[1].type == IND_CODE)
			write_in_arena(env, cur_process->reg[reg - 1], REG_SIZE
					, cur_process->pc + *((int*)decode.tab[1].value) % IDX_MOD);
		else if (decode.tab[1].type == REG_CODE)
		{
			to_reg = *((int *)decode.tab[1].value);
			ft_memcpy(cur_process->reg[to_reg - 1], cur_process->reg[reg - 1]
					, REG_SIZE);
		}
	}
	return (ret);
}
