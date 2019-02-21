/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:17:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/21 01:39:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int value, int carry)
{
	ft_printf("%-5s: %d %s\n"
			, "zjmp"
			, value
			, (carry == 1 ? "OK" : "KO"));
}

int			zjmp(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	if (cur_process->carry == 1)
		ret = (int)decode.tab[0].value % IDX_MOD;
	if (env->debug == DEBUG_ON)
		debug_mode((int)decode.tab[0].value % IDX_MOD, cur_process->carry);
	return (ret);
}
