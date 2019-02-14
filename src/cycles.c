/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:56:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/14 03:49:45 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"

static void	kill_old_process(t_env *env)
{
	t_list		*prev;
	t_list		*cur;
	t_process	*process;

	prev = NULL;
	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->lives > 0)
			process->lives = 0;
		else
		{
			ft_printf("Process from champ %d killed\n", process->champ_id);
			if (prev == NULL)
				env->process_lst = cur->next;
			else
				prev->next = cur->next;
			free(cur->content);
			free(cur);
			cur = prev;
		}
		prev = cur;
		if (cur != NULL)
			cur = cur->next;
	}
}

static void	inst_process(t_env *env)
{
	t_list		*cur;
	t_process	*process;

	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->cycles_left > 0)
			process->cycles_left -= 1;
		else
		{
			// TODO: execute inst & set PC
			process->cycles_left = 42;
		}
		cur = cur->next;
	}
}

void		run_cycles_loop(t_env *env)
{
	while (env->process_lst != NULL)
	{
		if (env->cur_cycle == env->dump_cycles)
			break ;
		if (env->cycle_before_die > 0)
			env->cycle_before_die -= 1;
		else
		{
			kill_old_process(env);
			env->cycle_before_die = env->cycle_to_die;
		}
		inst_process(env);
		env->cur_cycle += 1;
	}
}
