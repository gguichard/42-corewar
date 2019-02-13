/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 06:03:00 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/13 22:47:23 by gguichar         ###   ########.fr       */
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
	uint32_t		pc_reg;
	int				carry:1;
};

#endif
