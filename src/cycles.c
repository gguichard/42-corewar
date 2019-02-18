/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:56:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/18 23:45:27 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

t_op	g_op[] = {
	{live, 10},
	{ld, 5},
	{st, 4},
	{add, 10},
	{sub, 10},
	{ft_and, 6},
	{ft_or, 6},
	{ft_xor, 6},
	{zjmp, 20},
	{ldi, 25},
	{sti, 25},
	{ft_fork, 800},
	{lld, 10},
	{lldi, 50},
	{ft_lfork, 1000},
	{aff, 2}
};

static void	print_registers(t_process *process)
{
	int	idx;

	idx = 0;
	while (idx < 16)
	{
		ft_printf("REG[%d]=%d\n", idx, process->reg[idx]);
		idx++;
	}
}

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
			print_registers(process);
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

	if (process->queued_inst[0] != 0)
	{
		op = g_op[process->queued_inst[0] - 1];
		result = op.fn(env, process, process->queued_inst);
		process->pc += result;
		if (process->pc < 0)
			process->pc += MEM_SIZE;
		if (process->pc >= MEM_SIZE)
			process->pc %= MEM_SIZE;
		ft_memset(process->queued_inst, 0, MAX_INST_SIZE);
	}
}

void		setup_new_inst(t_env *env, t_process *process)
{
	int	opcode;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->pc = (process->pc + 1) % MEM_SIZE;
	else
	{
		fill_buff_from_arena(env, process->queued_inst, MAX_INST_SIZE
				, process->pc);
		process->cycles_left = g_op[opcode - 1].cycles;
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
		if (process->cycles_left == 0)
		{
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
		ft_printf("It is now cycle %d\n", env->cur_cycle);
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
