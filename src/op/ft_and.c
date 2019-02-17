/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:01:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 01:17:14 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	ft_and(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	int				idx;
	unsigned char	args[3][REG_SIZE];
	int				tmp;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	idx = 0;
	while (idx < 2)
	{
		if (!parse_multitype(args[idx], env, cur_process, decode.tab[idx]))
			return (ret);
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, REG_SIZE);
	tmp = *((int *)args[0]) & *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &tmp, REG_SIZE);
	return (ret);
}
