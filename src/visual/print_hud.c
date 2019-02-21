/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 03:20:25 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 16:22:19 by vifonne          ###   ########.fr       */
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
	mvwprintw(g_data.hud, 5 * TXT_HUD_PADD - 2, X_HUD_PADD, "Lifebar:");
	mvwprintw(g_data.hud, 7 * TXT_HUD_PADD - 2, X_HUD_PADD, "**RUNNING**");
	mvwprintw(g_data.hud, 5* TXT_HUD_PADD, X_HUD_PADD + 82, "|");
}

void	refresh_champ_lives(t_env *env)
{
	t_list	*cur_champ;
	t_int2	pos;
	int		champ;

	champ = 0;
	cur_champ = env->champ_lst;
	while (cur_champ)
	{
		pos = (t_int2){X_HUD_PADD, Y_HUD_PADD + champ * TXT_HUD_PADD + 1};
		mvwprintw(g_data.hud, pos.y, pos.x, "lives : %d", ((t_champ *)cur_champ->content)->lives);
		champ++;
		cur_champ = cur_champ->next;
	}
}

void	print_winner_visu(t_champ *winner)
{
	t_int2	dim;

	getmaxyx(g_data.hud, dim.y, dim.x);
	mvwprintw(g_data.hud, 40
			, (dim.x / 2 - (ft_strlen(winner->header.prog_name) + 10) / 2)
			, "%s has won!"
			, winner->header.prog_name);
	wrefresh(g_data.hud);
}

static int	total_lives(t_list *champ_lst)
{
	t_list	*cur_champ;
	int		total;

	total = 0;
	cur_champ = champ_lst;
	while (cur_champ != NULL)
	{
		total += ((t_champ *)cur_champ->content)->lives;
		cur_champ = cur_champ->next;
	}
	return (total);
}

void	print_bar(t_list *champ_lst)
{
	int		idx;
	int		color;
	t_int2	pos;
	int		total;
	t_list	*cur_champ;

	init_champ_color();
	cur_champ = champ_lst;
	total = total_lives(champ_lst);
	idx = 0;
	mvwprintw(g_data.hud, 5 * TXT_HUD_PADD, X_HUD_PADD, "|");
	while (total != 0 && cur_champ != NULL)
	{
		pos = (t_int2){idx + X_HUD_PADD + 1, 5 * TXT_HUD_PADD};
		idx = 0;
		color = champ_color(((t_champ *)cur_champ->content)->id);
		wattron(g_data.hud, COLOR_PAIR(color));
		while (idx < (((t_champ *)cur_champ->content)->lives / (float)total) * 80)
		{
			mvwprintw(g_data.hud, pos.y, pos.x, "-");
			idx++;
			pos.x += 1;
		}
		wattroff(g_data.hud, COLOR_PAIR(color));
		wrefresh(g_data.hud);
		cur_champ = cur_champ->next;
	}
}
