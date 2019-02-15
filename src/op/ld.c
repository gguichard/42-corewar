/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 04:12:09 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	ld(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode		decode;
	int				reg;
	int				reg_from;
	unsigned char	value[REG_SIZE];
	unsigned char	*tmp;

	if (!get_args(str + 2, *(str + 1), &decode))
		return (0);
	reg = *((int *)decode.tab[1].value);
	if (reg < 1 || reg > 16)
		return (0);
	ft_memset(value, 0, REG_SIZE);
	if (decode.tab[0].type == DIR_CODE)
		ft_memcpy(value + (REG_SIZE - 4), decode.tab[0].value, 4);
	else if (decode.tab[0].type == IND_CODE)
	{
		tmp = get_in_circle_mem(env, 4, cur_process->pc + *((int *)decode.tab[0].value) % IDX_MOD);
		if (tmp == NULL)
			return (0);
		ft_memcpy(value + (REG_SIZE - 4), tmp, 4);
		free(tmp);
	}
	else if (decode.tab[0].type == REG_CODE)
	{
		reg_from = *((int *)decode.tab[0].value);
		if (reg_from < 1 || reg_from > 16)
			return (0);
		ft_memcpy(value, cur_process->reg[reg_from - 1], REG_SIZE);
	}
	ft_memcpy(cur_process->reg[reg - 1], value, REG_SIZE);
	return (1);
}
