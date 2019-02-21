/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:01:13 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 05:05:25 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar.h"

# define HUD_COL		250
# define WIDTH			64
# define HEIGHT			64
# define X_PADD			4
# define Y_PADD			2
# define X_HUD_PADD		2
# define Y_HUD_PADD		1
# define TXT_HUD_PADD	5

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
	int			time;
	t_int2		cursor;
}				t_data;

extern t_data	g_data;

void	init_screen(t_env *env);
void	loop_screen(void);
void	print_init_hud(t_env *env);
void	print_init_state(t_env *env);
void	write_ncurses(uint8_t *bytes_ptr, int id, int size, int index);
void	print_champ(t_env *env);
void	init_champ_color(void);
void	print_winner_visu(t_champ *winner);
int		champ_color(int id);
void	key_hook(void);
#endif
