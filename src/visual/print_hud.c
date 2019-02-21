/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 03:20:25 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 05:09:14 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void	print_init_hud(t_env *env)
{
	t_list	*cur_champ;
	t_int2	pos;
	int		champ;
	int		color;

	champ = 0;
	init_champ_color();
	cur_champ = env->champ_lst;
	while (cur_champ)
	{
		color = champ_color(((t_champ *)cur_champ->content)->id);
		pos = (t_int2){X_HUD_PADD, Y_HUD_PADD + champ * TXT_HUD_PADD};
		wattron(g_data.hud, COLOR_PAIR(color));
		mvwprintw(g_data.hud, pos.y, pos.x, "Champ %d"
				, ((t_champ *)cur_champ->content)->id);
		wattroff(g_data.hud, COLOR_PAIR(color));
		mvwprintw(g_data.hud, pos.y, pos.x + 16, "%.25s"
				, ((t_champ *)cur_champ->content)->header.prog_name);
		champ++;
		cur_champ = cur_champ->next;
	}
}

void	print_winner_visu(t_champ *winner)
{
	t_int2	dim;

	getmaxyx(g_data.hud, dim.y, dim.x);
	mvwprintw(g_data.hud, 40
			, (dim.x / 2) - (ft_strlen(winner->header.prog_name) + 10) / 2
			, "%s has won !"
			, winner->header.prog_name);
	delwin(g_data.hud);
}
