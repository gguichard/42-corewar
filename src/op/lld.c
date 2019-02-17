/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 21:25:00 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 06:38:19 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	lld(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int				ret;
	t_decode		decode;
	unsigned char	value[REG_SIZE];
	int				reg;

	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	fill_struct(env, cur_process, &decode);
	if ((decode.tab[0].type == IND_CODE || decode.tab[0].type == DIR_CODE)
			&& decode.tab[1].type == REG_CODE
			&& dispatch_multitype(value, decode, decode.tab[0], 1))
	{
		reg = *((int *)decode.tab[1].value);
		ft_memcpy(cur_process->reg[reg - 1], value, REG_SIZE);
		cur_process->carry = ft_memcmp(value, "\0\0\0\0", 4) == 0;
	}
	return (ret);
}
