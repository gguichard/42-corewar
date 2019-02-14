/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 21:32:41 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/14 04:46:18 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAMPION_H
# define CHAMPION_H

# include "op.h"

typedef struct	s_champ
{
	t_header		header;
	unsigned char	prog[CHAMP_MAX_SIZE];
	unsigned int	id;
	unsigned int	live_cycle;
}				t_champ;

#endif
