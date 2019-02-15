/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 05:06:38 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H

# include "corewar.h"
# include "process.h"
# include "op.h"

typedef struct		s_encoding_byte
{
	unsigned int	f_arg4: 2;
	unsigned int	f_arg3: 2;
	unsigned int	f_arg2: 2;
	unsigned int	f_arg1: 2;
}					t_encoding_byte;

typedef struct		s_arg
{
	int				type;
	unsigned char	value[REG_SIZE];
}					t_arg;

typedef struct		s_decode
{
	t_encoding_byte	*raw_decode;
	t_arg			tab[MAX_ARGS_NUMBER];
}					t_decode;

int					live(t_env *env, t_process *cur_process, unsigned char *str);
int					ld(t_env *env, t_process *cur_process, unsigned char *str);

/*
**	UTILS
*/
unsigned char		*get_in_circle_mem(t_env *env, int size, int offset);
int					get_args(unsigned char *str, unsigned char encoding_byte
		, t_decode *result);

#endif
