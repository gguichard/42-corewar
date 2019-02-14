/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 20:35:44 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "process.h"
#include "corewar.h"
#include "champion.h"
#include "func_op.h"

void	live(t_env *env, t_process *cur_process, unsigned char *str)
{
	unsigned char	*tmp;
	unsigned int	champ_id;
	t_list			*champ;

	tmp = get_op(env, 5, str);
	champ_id = *((int *)(str + 1));
	printf("champ_id = %d\n", champ_id);
	champ = env->champ_lst;
	while (champ)
	{
		if (champ_id == ((t_champ *)champ->content)->id)
		{
			printf("champ_id match\n");
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			break ;
		}
		champ = champ->next;
	}
	//cur_process->lives += 1;
	//cur_process->->pc += 5;
	(void)cur_process;
}
