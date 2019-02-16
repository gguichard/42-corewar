/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:28:28 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 22:38:26 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ldi(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	unsigned char	args[3][REG_SIZE];
	t_decode		decode;
	int				ret;
	int				tmp;
	unsigned char	*target;

	if (!get_args(bytes + 2, *(bytes + 1), &decode))
		return (0);
	idx = 0;
	ret = 2;
	while (idx < 2)
	{
		if ((idx == 1 && decode.tab[idx].type == IND_CODE)
				|| !(tmp = parse_multitype_args(args[idx], env, cur_process
						, decode.tab[idx])))
			return (0);
		ret += tmp;
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, REG_SIZE);
	tmp = *((int *)args[0]) + *((int *)args[1]);
	target = get_in_arena(env, REG_SIZE, (cur_process->pc + tmp) % IDX_MOD);
	if (target == NULL)
		return (0);
	ft_memcpy(cur_process->reg[*((int *)decode.tab[2].value)] - 1
			, target, REG_SIZE);
	return (ret);
}
