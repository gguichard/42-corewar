/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:32 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 07:45:31 by gguichar         ###   ########.fr       */
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

	ret = decode_args(&decode, bytes + 1, DIR_CODE << 6, REG_DIR);
	fill_decode(env, cur_process, &decode);
	champ = env->champ_lst;
	ft_printf("live %d\n", decode.tab[0].value);
	while (champ != NULL)
	{
		if (((t_champ *)champ->content)->id == (int)decode.tab[0].value)
		{
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			break ;
		}
		champ = champ->next;
	}
	cur_process->lives += 1;
	return (ret + 1);
}
