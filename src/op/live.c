/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 08:00:28 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "process.h"
#include "champion.h"
#include "func_op.h"
#include "op.h"

int	live(t_env *env, t_process *cur_process, uint8_t *bytes)
{
	int			ret;
	t_decode	decode;
	t_list		*champ;

	fill_decode(env, cur_process, &decode, 1);
	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, REG_DIR) + 1;
	champ = env->champ_lst;
	while (champ != NULL)
	{
		if (((t_champ *)champ->content)->id == (int)decode.tab[0].value)
		{
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			ft_printf("%s is living\n"
					, ((t_champ *)champ->content)->header.prog_name);
			break ;
		}
		champ = champ->next;
	}
	cur_process->lives += 1;
	cur_process->last_live = env->cur_cycle;
	if (env->debug == DEBUG_ON)
		debug_mode("live", decode, 1);
	return (ret);
}
