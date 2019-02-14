/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:24 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 20:40:08 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "corewar.h"
#include "func_op.h"

void	ld(t_env *env, t_process *cur_process, unsigned char *str)
{
	get_encoding_byte(str + 1);
	ft_printf("ld\n");
	(void)env;
	(void)cur_process;
}
