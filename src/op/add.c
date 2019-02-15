/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:55:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 22:49:39 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"
#include <unistd.h>

static int	reg_isvalid(int *reg)
{
	if (reg[0] > 0 && reg[0] < 17
			&& reg[1] > 0 && reg[1] < 17
			&& reg[2] > 0 && reg[2] < 17)
		return (1);
	return (0);
}

int			add(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode		decode;
	int				args[3];
	int				i;
	unsigned char	tmp[REG_SIZE];

	i = -1;
	while (++i < 3)
		args[i] = *((int *)decode.tab[i].value);
	if (!get_args(str + 1, REG_CODE << 6 | REG_CODE << 4 | REG_CODE << 2, &decode)
			|| !reg_isvalid(args))
		return (0);
	i = -1;
	while (++i < REG_SIZE)
		tmp[i] = cur_process->reg[args[1]][i] + cur_process->reg[args[2]][i];
	//write(1, tmp, REG_SIZE);
	ft_memcpy(cur_process->reg[args[3]], tmp, REG_SIZE);
	(void)env;
	return (3);
}
