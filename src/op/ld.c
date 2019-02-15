/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 01:45:57 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "corewar.h"
#include "func_op.h"

void	ld(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode	result;

	get_args(str + 2, *(str + 1), &result);
	ft_printf("ld %d %d\n", result.tab[0].value, result.tab[1].value);
	(void)env;
	(void)cur_process;
}
