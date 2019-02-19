/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:18:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 03:33:56 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "libft.h"
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	ft_lfork(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*node;
	t_process	*process;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	if (decode.tab[0].type == DIR_CODE)
	{
		node = ft_lstnew(cur_process, sizeof(t_process));
		if (node == NULL)
			return (-1);
		process = (t_process *)node->content;
		ft_memset(&process->queued_inst, 0, MAX_INST_SIZE);
		increase_pc(process, (int)decode.tab[0].value);
		ft_printf("lfork %d (%d)\n", decode.tab[0].value, process->pc);
		//setup_new_inst(env, process);
		ft_lstadd(&env->process_lst, node);
	}
	return (ret);
}
