/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 01:51:02 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 03:50:56 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void	print_champ(t_env *env)
{
	t_list			*cur_champ;
	t_int2			cursor;
	unsigned int	idx;
	int				champ;
	int				len;

	init_champ_color();
	cur_champ = env->champ_lst;
	len = ft_lstsize(cur_champ);
	champ = 0;
	while (cur_champ)
	{
		idx = 0; 
		attron(COLOR_PAIR(champ_color(((t_champ *)cur_champ->content)->id)));
		cursor = (t_int2){0, (champ * (MEM_SIZE / len)) / 64};
		while (idx < ((t_champ *)cur_champ->content)->header.prog_size)
		{
			if (idx != 0 && idx % 64 == 0)
			{
				cursor.x = 0;
				cursor.y += 1;
			}
			mvwprintw(g_data.win, cursor.y + Y_PADD, cursor.x + X_PADD
					, "%.2x", ((t_champ *)cur_champ->content)->prog[idx]);
			cursor.x += 3;
			idx++;
		}
		attroff(COLOR_PAIR(champ_color(((t_champ *)cur_champ->content)->id)));
		cur_champ = cur_champ->next;
		champ++;
	}
}
