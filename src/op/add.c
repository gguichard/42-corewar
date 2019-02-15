/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:55:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 00:02:05 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	add(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode	decode;
	int			args[3];
	int			tmp;
	int			idx;

	(void)env;
	idx = 0;
	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	while (idx < 3)
	{
		if (decode.tab[idx].type != REG_CODE
				|| !reg_isvalid(decode.tab[idx].value))
			return (0);
		args[idx] = *((int *)decode.tab[idx].value);
		idx++;
	}
	tmp = *((int *)cur_process->reg[args[0] - 1]) + *((int *)cur_process->reg[args[1] - 1]);
	ft_memcpy(cur_process->reg[args[2] - 1], &tmp, sizeof(int));
	return (3);
}
