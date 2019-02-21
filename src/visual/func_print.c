/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 03:14:43 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 05:09:13 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void	loop_screen(void)
{
	getch();
	endwin();
}

int		champ_color(int id)
{
	int	idx;

	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		if (id == g_data.champ[idx])
			return (idx + 1);
		idx++;
	}
	return (0);
}

void	write_ncurses(uint8_t *bytes_ptr, int id, int size, int index)
{
	t_int2	pos;
	int		idx;
	int		color;

	idx = 0;
	init_champ_color();
	color = champ_color(id);
	fix_pc_offset(&index);
	pos = (t_int2) {index % WIDTH , index / HEIGHT};
	attron(COLOR_PAIR(color));
	while (idx < size)
	{
		mvwprintw(g_data.win, pos.y + Y_PADD, pos.x * 3 + X_PADD, "%.2x"
				, bytes_ptr[idx]);
		index += 1;
		fix_pc_offset(&index);
		pos = (t_int2) {index % WIDTH , index / HEIGHT};
		idx++;
		usleep(g_data.time);
	}
	refresh();
	attroff(COLOR_PAIR(color));
}

void	key_hook(void)
{
	int	ch;

	ch = getch();
	if (ch == 'r')
	{
		if (g_data.time <= 7000)
			g_data.time = 1000;
		else
			g_data.time -= 7000;
	}
	else if (ch == 'q')
		g_data.time += 7000;
}
