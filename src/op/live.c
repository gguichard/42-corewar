/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 02:05:54 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "process.h"
#include "corewar.h"
#include "champion.h"
#include "func_op.h"

int	live(t_env *env, t_process *cur_process, unsigned char *str)
{
	t_decode	decode;
	t_list		*champ;

	if (!get_args(str + 1, REG_CODE << 6, &decode))
		return (0);
	champ = env->champ_lst;
	while (champ != NULL)
	{
		if (decode.tab[0].value == ((t_champ *)champ->content)->id)
		{
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			break ;
		}
		champ = champ->next;
	}
	cur_process->lives += 1;
	return (1);
}
