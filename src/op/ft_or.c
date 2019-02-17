/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:03:59 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 05:28:35 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	ft_or(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	int				idx;
	t_decode		decode;
	unsigned char	args[3][REG_SIZE];
	int				tmp;

	fill_struct(env, cur_process, &decode);
	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	idx = 0;
	while (idx < 2)
	{
		if (!parse_multitype(args[idx], env, cur_process, decode.tab[idx]))
			return (ret);
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, REG_SIZE);
	tmp = *((int *)args[0]) | *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &tmp, REG_SIZE);
	return (ret);
}
