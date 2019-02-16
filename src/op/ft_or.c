/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 01:03:59 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 01:30:16 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <stdlib.h>

int	ft_or(t_env *env, t_process *cur_process, unsigned char *str)
{
	int				tmp;
	t_decode		decode;
	unsigned char	args[3][REG_SIZE];

	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	if (!parse_multitype_args((unsigned char ***)args
				, env, cur_process, decode))
		return (0);
	ft_memcpy(args[2], decode.tab[2].value, 4);
	tmp = *((int *)args[0]) | *((int *)args[1]);
	ft_memcpy(cur_process->reg[*((int *)args[2]) - 1], &tmp, REG_SIZE);
	return (1);
}
