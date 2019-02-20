/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:17:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/20 02:01:47 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int value, int carry)
{
	ft_printf("%-5s: %d (carry %d)\n"
			, "zjmp"
			, value
			, carry);
}

int			zjmp(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	if (env->debug == DEBUG_ON)
		debug_mode((int)decode.tab[0].value % IDX_MOD, (int)cur_process->carry);
	if (decode.tab[0].type != DIR_CODE || cur_process->carry != 1)
		return (ret);
	else
		return ((int)decode.tab[0].value % IDX_MOD);
}