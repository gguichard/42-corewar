/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:01:13 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 02:58:33 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar.h"

# define HUD_COL	210
# define WIDTH		64
# define HEIGHT		64
# define X_PADD		3
# define Y_PADD		1

typedef struct	s_int2
{
	int			x;
	int			y;
}				t_int2;

typedef struct	s_data
{
	WINDOW		*win;
	WINDOW		*hud;
	int			champ[MAX_PLAYERS];
	t_int2		cursor;
}				t_data;

extern t_data	g_data;

void	init_screen(t_env *env);
void	loop_screen(t_env *env);
void	print_init_state(t_env *env);
void	write_ncurses(uint8_t *bytes_ptr, int id, int size, int index);
void	print_champ(t_env *env);
void	init_champ_color(void);
int		champ_color(int id);

#endif