/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 00:01:29 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 06:23:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	ft_and(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				idx;
	int				ret;
	int				tmp;
	t_decode		decode;
	unsigned char	args[3][REG_SIZE];

	if (!get_args(bytes + 2, *(bytes + 1), &decode))
		return (0);
	idx = 0;
	ret = 2;
	while (idx < 2)
	{
		if (!(tmp = parse_multitype_args(args[idx], env, cur_process
						, decode.tab[idx])))
			return (0);
		ret += tmp;
		idx++;
	}
	ft_memcpy(args[2], decode.tab[2].value, 4);
	tmp = *((int *)args[0]) & *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &tmp, REG_SIZE);
	return (ret);
}