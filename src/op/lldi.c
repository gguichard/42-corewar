/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:58:20 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 06:06:43 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	lldi(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	unsigned char	args[2][REG_SIZE];
	int				tmp;
	unsigned char	*target;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 1);
	fill_struct(env, cur_process, &decode);
	if ((decode.tab[1].type == DIR_CODE || decode.tab[1].type == REG_CODE)
			&& decode.tab[2].type == REG_CODE && decode.tab[0].type != BAD_CODE
			&& dispatch_multitype(args[0], decode, decode.tab[0], 3)
			&& dispatch_multitype(args[1], decode, decode.tab[1], 3))
	{
		tmp = *((short *)args[0]) + *((short *)args[1]);
		target = get_in_arena(env, REG_SIZE, cur_process->pc + tmp);
		if (target == NULL)
			return (-1);
		ft_memcpy(cur_process->reg[*((int *)decode.tab[2].value) - 1]
				, target, REG_SIZE);
	}
	return (ret);
}
