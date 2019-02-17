/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:04:23 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 06:37:18 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	ft_xor(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	int				idx;
	t_decode		decode;
	unsigned char	args[3][REG_SIZE];
	int				tmp;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	fill_struct(env, cur_process, &decode);
	idx = 0;
	while (idx < 2)
	{
		if (!dispatch_multitype(args[idx], decode, decode.tab[idx], 0))
			return (ret);
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, REG_SIZE);
	tmp = *((int *)args[0]) ^ *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &tmp, REG_SIZE);
	cur_process->carry = tmp == 0;
	return (ret);
}
