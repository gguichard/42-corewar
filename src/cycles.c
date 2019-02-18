/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:56:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/18 02:20:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "op.h"
#include "func_op.h"

t_op	g_op[] = {
	{live, 10, 0, 0},
	{ld, 5, 1, 1},
	{st, 4, 0, 1},
	{add, 10, 1, 1},
	{sub, 10, 1, 1},
	{ft_and, 6, 1, 1},
	{ft_or, 6, 1, 1},
	{ft_xor, 6, 1, 1},
	{zjmp, 20, 0, 0},
	{ldi, 25, 1, 1},
	{sti, 25, 1, 1},
	{ft_fork, 800, 0, 0},
	{lld, 10, 1, 1},
	{lldi, 50, 1, 1},
	{ft_lfork, 1000, 0, 0},
	{aff, 2, 0, 0}
};

/*static void	print_reg(t_process *process)
  {
  int	idx;

  idx = 0;
  while (idx < 16)
  {
  ft_printf("REG[%d]=%d\n", idx + 1, *((int *)process->reg[idx]));
  idx++;
  }
  }*/

static int	kill_old_process(t_env *env)
{
	int			lives;
	t_list		*prev;
	t_list		*cur;
	t_process	*process;

	lives = 0;
	prev = NULL;
	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->lives > 0)
		{
			lives += process->lives;
			process->lives = 0;
		}
		else
		{
			if (prev == NULL)
				env->process_lst = cur->next;
			else
				prev->next = cur->next;
			//print_reg(process);
			free(cur->content);
			free(cur);
			cur = prev;
		}
		prev = cur;
		if (cur != NULL)
			cur = cur->next;
	}
	return (lives);
}

static void	exec_inst(t_env *env, t_process *process)
{
	t_op	op;
	int		result;

	op = g_op[process->queued_inst[0] - 1];
	//ft_printf("opcode %d|process %p|cur_cycle %d\n", process->queued_inst[0], process, env->cur_cycle);
	result = op.fn(env, process, process->queued_inst);
	if (op.use_encoding_byte)
		result += 1;
	process->pc += result + 1;
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	process->pc %= MEM_SIZE;
	ft_memdel((void **)&process->queued_inst);
}

void		setup_new_inst(t_env *env, t_process *process)
{
	int	opcode;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->pc = (process->pc + 1) % MEM_SIZE;
	else
	{
		process->queued_inst = get_in_arena(env, 32, process->pc);
		if (process->queued_inst != NULL)
			process->cycles_left = g_op[opcode - 1].cycles;
		else
			ft_dprintf(2, "corewar: error: Unexpected error while reading an "
					"instruction\n");
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
		if (process->cycles_left > 1)
			process->cycles_left -= 1;
		else
		{
			if (process->queued_inst != NULL)
				exec_inst(env, process);
			setup_new_inst(env, process);
		}
		cur = cur->next;
	}
}

void		run_cycles_loop(t_env *env)
{
	while (env->process_lst != NULL)
	{
		if (env->cycle_before_die > 0)
			env->cycle_before_die -= 1;
		else
		{
			kill_old_process(env);
			env->cycle_to_die -= CYCLE_DELTA;
			env->cycle_before_die = env->cycle_to_die;
		}
		inst_process(env);
		if (env->cur_cycle == env->dump_cycles)
		{
			print_arena(env);
			break ;
		}
		env->cur_cycle += 1;
	}
}
