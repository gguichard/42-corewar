/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 03:54:14 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 04:01:48 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

int	aff(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	int			reg;
	char		c;
	t_decode	decode;

	(void)env;
	ret = get_args(bytes + 2, *(bytes + 1), &decode, 0);
	if (decode.tab[0].type == REG_CODE)
	{
		reg = *((int *)decode.tab[0].value);
		c = *((int *)cur_process->reg[reg - 1]) % 256;
		ft_putchar(c);
	}
	return (ret);
}
