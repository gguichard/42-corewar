/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:43 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/14 02:05:40 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

typedef enum e_error	t_error;
typedef struct s_env	t_env;

enum		e_error
{
	ERR_NOERROR = 0,
	ERR_UNEXPECTED = 1,
	ERR_NOCHAMPNAME,
	ERR_WRONGNOPT,
	ERR_WRONGDUMPOPT,
	ERR_CHAMPREAD,
	ERR_NOCHAMPS
};

struct		s_env
{
	t_list			*champ_lst;
	t_list			*process_lst;
	unsigned char	arena[MEM_SIZE];
	int				cur_cycle;
	int				dump_cycles;
	int				cycle_to_die;
	int				cycle_before_die;
};

t_error		create_def_process(t_env *env, char **argv, int argc, int cur_arg);

void		run_cycles_loop(t_env *env);

const char	*str_to_error(t_error err_id);

#endif
