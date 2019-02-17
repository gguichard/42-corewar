/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 01:17:35 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ld(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	unsigned char	value[REG_SIZE];
	int				reg;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	if ((decode.tab[0].type == IND_CODE || decode.tab[0].type == DIR_CODE)
			&& decode.tab[1].type == REG_CODE
			&& parse_multitype(value, env, cur_process, decode.tab[0]))
	{
		reg = *((int *)decode.tab[1].value);
		ft_memcpy(cur_process->reg[reg - 1], value, REG_SIZE);
	}
	return (ret);
}
