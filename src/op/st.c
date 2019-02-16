/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:15:06 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/16 01:39:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

int	st(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	t_decode	decode;
	int			ret;
	int			reg;
	int			to_reg;

	if (!get_args(bytes + 2, *(bytes + 1), &decode))
		return (0);
	if (decode.tab[0].type != REG_CODE
			|| (decode.tab[1].type != REG_CODE
				&& decode.tab[1].type != IND_CODE))
		return (0);
	ret = 3;
	reg = *((int *)decode.tab[0].value);
	if (decode.tab[1].type == IND_CODE)
	{
		write_in_arena(env, cur_process->reg[reg - 1], REG_SIZE
				, cur_process->pc + *((int *)decode.tab[1].value));
		ret += 2;
	}
	else
	{
		to_reg = *((int *)decode.tab[1].value);
		ft_memcpy(cur_process->reg[to_reg - 1], cur_process->reg[reg - 1]
				, REG_SIZE);
		ret += 1;
	}
	print_arena(env->arena, MEM_SIZE);
	return (ret);
}
