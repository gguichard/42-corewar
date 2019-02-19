/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:12:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 04:47:12 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "libft.h"
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	ft_fork(t_env *env, t_process *cur_process, uint8_t *bytes)
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
		increase_pc(process, (int)decode.tab[0].value % IDX_MOD);
		ft_printf("fork %d (%d)\n", decode.tab[0].value, process->pc);
		ft_lstadd(&env->process_lst, node);
	}
	return (ret);
}
