/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:18:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/20 21:23:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

static void	debug_mode(int param, int pc)
{
	ft_printf("%-5s: %d (pc %d)\n"
			, "lfork"
			, param
			, pc);
}

int			ft_lfork(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*node;
	t_process	*process;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	node = ft_lstnew(cur_process, sizeof(t_process));
	if (node == NULL)
		return (-1);
	process = (t_process *)node->content;
	process->queued_op = 0;
	increase_pc(process, (int)decode.tab[0].value);
	ft_lstadd(&env->process_lst, node);
	if (env->debug == DEBUG_ON)
		debug_mode(decode.tab[0].value, process->pc);
	return (ret);
}