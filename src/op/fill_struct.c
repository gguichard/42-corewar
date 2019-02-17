/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:22:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 00:04:02 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"
#include "op.h"

void	fill_struct(t_env *env, t_process *cur_process, t_decode *decode)
{
	decode->env = env;
	decode->cur_process = cur_process;
}

void	increase_pc(t_process *process, int value)
{
	process->pc += value;
	if (process->pc < 0)
		process->pc += MEM_SIZE;
	if (process->pc >= MEM_SIZE)
		process->pc -= MEM_SIZE;
}
