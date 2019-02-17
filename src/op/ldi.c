/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:28:28 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 02:21:34 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ldi(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	unsigned char	args[2][REG_SIZE];
	int				tmp;
	unsigned char	*target;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 1);
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE
			&& decode.tab[0].type != BAD_CODE
			&& parse_imultitype(args[0], env, cur_process, decode.tab[0])
			&& parse_imultitype(args[1], env, cur_process, decode.tab[1]))
	{
		tmp = *((int *)args[0]) + *((int *)args[1]);
		target = get_in_arena(env, REG_SIZE, cur_process->pc + tmp % IDX_MOD);
		if (target == NULL)
			return (-1);
		ft_memcpy(cur_process->reg[*((int *)decode.tab[2].value) - 1]
				, target, REG_SIZE);
	}
	return (ret);
}
