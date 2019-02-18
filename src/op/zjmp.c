/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 02:17:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/18 09:20:05 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

int	zjmp(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;

	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, SHORT_DIR) + 1;
	fill_decode(env, cur_process, &decode);
	ft_printf("zjmp val=%d carry=%d\n", (int)decode.tab[0].value % IDX_MOD, cur_process->carry);
	if (decode.tab[0].type != DIR_CODE || cur_process->carry != 1)
		return (ret);
	else
		return ((int)decode.tab[0].value % IDX_MOD);
}
