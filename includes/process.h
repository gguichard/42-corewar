/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:03:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/14 06:00:59 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <stdint.h>
# include "op.h"

typedef struct s_process	t_process;

struct	s_process
{
	unsigned int	champ_id;
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	char			*pc;
	int				carry:1;
	int				cycles_left;
	int				lives;
};

#endif
