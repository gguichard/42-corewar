/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:56:50 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 03:05:52 by gguichar         ###   ########.fr       */
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

/*static void	print_registers(t_process *process)
  {
  int	idx;

  idx = 0;
  while (idx < 16)
  {
  ft_printf("REG[%d]=%d\n", idx, process->reg[idx]);
  idx++;
  }
  }*/

static void	kill_old_process(t_env *env)
{
	t_list		*prev;
	t_list		*cur;
	t_list		*next;
	t_process	*process;

	prev = NULL;
	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->lives > 0)
		{
			process->lives = 0;
			prev = cur;
			cur = cur->next;
		}
		else
		{
			next = cur->next;
			if (prev == NULL)
				env->process_lst = next;
			else
				prev->next = next;
			ft_printf("process hasn't lived for %d cycles\n", env->cur_cycle - process->last_live);
			//print_registers(process);
			free(cur->content);
			free(cur);
			cur = next;
		}
	}
}

static void	exec_inst(t_env *env, t_process *process)
{
	int		opcode;
	int		ret;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->pc += 1;
	else
	{
		fill_buff_from_arena(env, process->queued_inst, MAX_INST_SIZE,
				process->pc);
		ret = g_op[opcode - 1].fn(env, process, process->queued_inst);
		if (g_op[opcode - 1].fn != zjmp || process->carry == 0)
			ft_printf("ADV %d\n", ret);
		process->pc += ret;
		/*if (g_op[opcode - 1].fn == zjmp)
		{
			ft_printf("under byte %d", *(env->arena + process->pc));
			ft_printf(" %.2x", *(env->arena + process->pc + 1));
			ft_printf("%.2x", *(env->arena + process->pc + 2));
			ft_printf(" %.2x", *(env->arena + process->pc + 3));
			ft_printf("%.2x", *(env->arena + process->pc + 4));
			ft_printf(" %.2x", *(env->arena + process->pc + 5));
			ft_printf("%.2x", *(env->arena + process->pc + 6));
			ft_printf(" %.2x", *(env->arena + process->pc + 7));
			ft_printf("%.2x\n", *(env->arena + process->pc + 8));
		}*/
	}
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	if (process->pc >= MEM_SIZE)
		process->pc %= MEM_SIZE;
}

void		setup_new_inst(t_env *env, t_process *process)
{
	int	opcode;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->cycles_left = 1;
	else
		process->cycles_left = g_op[opcode - 1].cycles;
}

static void	inst_process(t_env *env)
{
	t_list		*cur;
	t_process	*process;

	cur = env->process_lst;
	while (cur != NULL)
	{
		process = (t_process *)cur->content;
		if (process->cycles_left == 0)
			setup_new_inst(env, process);
		process->cycles_left -= 1;
		if (process->cycles_left == 0)
			exec_inst(env, process);
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
		if (env->cycle_before_die == 0)
		{
			kill_old_process(env);
			//	env->cycle_to_die -= CYCLE_DELTA;
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
