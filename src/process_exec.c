/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 22:53:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 23:38:55 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

t_op		g_op[] = {
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

static void	exec_inst(t_env *env, t_process *process)
{
	int		opcode;
	int		ret;

	opcode = process->queued_inst[0];
	if (opcode < 1 || opcode > 16)
		process->pc += 1;
	else
	{
		ret = g_op[opcode - 1].fn(env, process, process->queued_inst);
		if (g_op[opcode - 1].fn != zjmp || process->carry == 0)
			ft_printf("ADV %d %d (%#.4x -> %#.4x)\n", ret, opcode, process->pc
					, process->pc + ret);
		process->pc += ret;
	}
	ft_memset(process->queued_inst, 0, MAX_INST_SIZE);
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	if (process->pc >= MEM_SIZE)
		process->pc %= MEM_SIZE;
}

static void	setup_new_inst(t_env *env, t_process *process)
{
	int	opcode;

	opcode = env->arena[process->pc];
	if (opcode < 1 || opcode > 16)
		process->cycles_left = 1;
	else
	{
		fill_buff_from_arena(env, process->queued_inst, MAX_INST_SIZE
				, process->pc);
		process->cycles_left = g_op[opcode - 1].cycles;
	}
}

void		process_instructions(t_env *env)
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
