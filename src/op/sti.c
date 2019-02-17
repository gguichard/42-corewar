/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:21:10 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 04:44:54 by vifonne          ###   ########.fr       */
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

	idx = 0;
	ret = get_args(bytes + 2, *(bytes + 1), &decode, 1);
	if ((decode.tab[2].type == REG_CODE || decode.tab[2].type == DIR_CODE)
			&& decode.tab[0].type == REG_CODE
			&& decode.tab[1].type != BAD_CODE)
	{
		while (idx < 3)
		{
			parse_multitype(args[idx], env, cur_process, decode.tab[idx]);
			idx++;
		}
		tmp = *((short *)args[1]) + *((short *)args[2]);
		write_in_arena(env, args[0], REG_SIZE, cur_process->pc + tmp % IDX_MOD);
	}
	return (ret);
}
