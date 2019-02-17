/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:12:44 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/17 05:28:21 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	ft_fork(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*node;
	t_process	*process;

	fill_struct(env, cur_process, &decode);
	ret = get_args(bytes + 1, DIR_CODE << 6, &decode, 1);
	if (decode.tab[0].type == DIR_CODE)
	{
		node = ft_lstnew(cur_process, sizeof(t_process));
		if (node == NULL)
			return (-1);
		process = (t_process *)node->content;
		process->pc = (process->pc + *((short *)decode.tab[0].value) % IDX_MOD)
			% MEM_SIZE;
		ft_lstadd(&env->process_lst, node);
	}
	return (ret);
}
