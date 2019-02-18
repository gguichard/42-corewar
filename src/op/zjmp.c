/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:17:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/18 00:59:53 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	zjmp(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	int			ret;
	t_decode	decode;

	ret = get_args(bytes + 1, DIR_CODE << 6, &decode, 1);
	fill_struct(env, cur_process, &decode);
	ft_printf("zjmp val=%d carry=%d\n", *((short *)decode.tab[0].value) % IDX_MOD, cur_process->carry);
	if (decode.tab[0].type == DIR_CODE && cur_process->carry == 1)
		return (*((short *)decode.tab[0].value) % IDX_MOD - 1);
	return (ret);
}
