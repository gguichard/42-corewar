/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:03:15 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 02:59:07 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>
#include "corewar.h"
#include "visual.h"

t_data	g_data;

void	init_screen(t_env *env)
{
	struct winsize	win;

	g_data.cursor = (t_int2){X_PADD, Y_PADD};
	initscr();
	start_color();
	use_default_colors();
	ioctl(0, TIOCGSIZE, &win);
	g_data.hud = subwin(stdscr, win.ws_row - 2,
			win.ws_col - HUD_COL, 1, HUD_COL - 2);
	wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwaddstr(stdscr, 0, (win.ws_col * 0.5) - 6, " Corewar ");
	wborder(g_data.hud, '|', '|', '-', '-', '+', '+', '+', '+');
	g_data.win = stdscr;
	print_init_state(env);
	print_champ(env);
}

void	init_champ_color(void)
{
	init_pair(0, -1, -1);
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_BLUE, -1);
	init_pair(3, COLOR_GREEN, -1);
	init_pair(4, COLOR_YELLOW, -1);
}

void	print_init_state(t_env *env)
{
	t_int2	cursor;
	t_int2	pos;

	(void)env;
	init_champ_color();
	cursor = (t_int2) {X_PADD, Y_PADD};
	pos = (t_int2) {0, 0};
	while (pos.y < HEIGHT)
	{
		cursor.x = X_PADD;
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			mvwprintw(g_data.win, cursor.y, cursor.x, "00 ");
			cursor.x += 3;
			pos.x += 1;
		}
		cursor.y += 1;
		pos.y += 1;
	}
}

void	loop_screen(t_env *env)
{
	(void)env;
	getch();
	delwin(g_data.hud);
	endwin();
}

int		champ_color(int id)
{
	int	idx;

	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		wprintw(g_data.hud, "id=%d|\n", g_data.champ[idx]);
		if (id == g_data.champ[idx])
		{
			wprintw(g_data.hud, "%d\n", idx);
			return (idx + 1);
		}
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
	start_color();
	use_default_colors();
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
		usleep(4000);
	}
	refresh();
	attroff(COLOR_PAIR(color));
}
