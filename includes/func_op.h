/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 01:45:58 by vifonne          ###   ########.fr       */
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
	int				value;
}					t_arg;

typedef struct		s_decode
{
	t_encoding_byte	*raw_decode;
	t_arg			tab[MAX_ARGS_NUMBER];
}					t_decode;

void				live(t_env *env, t_process *cur_process, unsigned char *str);
void				ld(t_env *env, t_process *cur_process, unsigned char *str);

/*
**	UTILS
*/
unsigned char		*get_op(t_env *env, int size, unsigned char *str);
int					get_args(unsigned char *str, char encoding_byte, t_decode *result);

#endif
