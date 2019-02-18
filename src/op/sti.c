/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:21:10 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 05:06:39 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	sti(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	int				tmp;
	int				idx;
	t_decode		decode;
	unsigned char	args[3][REG_SIZE];

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 1);
	fill_struct(env, cur_process, &decode);
	if (decode.tab[0].type == REG_CODE
			&& (decode.tab[1].type == REG_CODE
				|| decode.tab[1].type == DIR_CODE)
			&& (decode.tab[2].type == REG_CODE
				|| decode.tab[2].type == DIR_CODE))
	{
		idx = 0;
		while (idx < 3)
		{
			dispatch_multitype(args[idx], decode, decode.tab[idx], T_INDX);
			idx++;
		}
		tmp = *((short *)args[1]) + *((short *)args[2]);
		ft_printf("sti r%d %hd %hd (%d)\n", *((int *)decode.tab[0].value), *((short *)args[1]), *((short *)args[2]), cur_process->pc + tmp % IDX_MOD);
		write_in_arena(env, args[0], REG_SIZE, cur_process->pc + tmp % IDX_MOD);
	}
	return (ret);
}
