/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 04:01:13 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/20 07:31:16 by vifonne          ###   ########.fr       */
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
	t_int2		cursor;
}				t_data;

void	init_screen(t_env *env);
void	loop_screen(t_env *env, t_data *data);
void	print_init_state(t_env *env, t_data *data);
#endif
