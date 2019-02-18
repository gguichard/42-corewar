/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 03:54:14 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 23:47:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	aff(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	int			reg;
	char		c;

	(void)env;
	ret = decode_args(&decode, bytes + 2, *(bytes + 1), 0) + 2;
	if (decode.tab[0].type == REG_CODE)
	{
		reg = (int)decode.tab[0].value;
		c = ((int)cur_process->reg[reg - 1]) % 256;
		ft_putchar(c);
	}
	return (ret);
}
