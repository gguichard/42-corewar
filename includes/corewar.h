/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/13 23:57:45 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include "process.h"

typedef struct s_env	t_env;

struct	s_env
{
	t_list			*champ_lst;
	t_list			*process_lst;
	unsigned char	arena[MEM_SIZE];
	int				cur_cycle;
	int				dump_cycles;
	int				cycle_to_die;
	int				cycle_before_die;
};

#endif
