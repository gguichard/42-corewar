/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 06:18:54 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "process.h"
#include "champion.h"
#include "func_op.h"

int	live(t_env *env, t_process *cur_process, unsigned char *bytes)
{
	t_decode	decode;
	t_list		*champ;

	if (!get_args(bytes + 1, DIR_CODE << 6, &decode))
		return (0);
	champ = env->champ_lst;
	while (champ != NULL)
	{
		if (ft_memcmp(decode.tab[0].value, &((t_champ *)champ->content)->id
					, REG_SIZE) == 0)
		{
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			break ;
		}
		champ = champ->next;
	}
	if (champ == NULL)
		return (0);
	cur_process->lives += 1;
	return (5);
}
