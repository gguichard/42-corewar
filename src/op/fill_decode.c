/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_decode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 05:22:48 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 05:26:59 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "process.h"
#include "func_op.h"

int	fill_struct(t_env *env, t_process *cur_process, t_decode *decode)
{
	decode->env = env;
	decode->cur_process = cur_process;
}
