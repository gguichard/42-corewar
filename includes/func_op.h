/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 23:23:46 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H

# include "corewar.h"
# include "process.h"
# include "op.h"

typedef struct		s_arg
{
	int				type;
	unsigned char	value[REG_SIZE];
}					t_arg;

typedef struct		s_decode
{
	t_arg			tab[MAX_ARGS_NUMBER];
}					t_decode;

int					live(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ld(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					st(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					add(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					sub(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ft_and(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ft_or(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ft_xor(t_env *env, t_process *cur_process
		, unsigned char *bytes);

/*
**	UTILS
*/
unsigned char		*get_in_arena(t_env *env, size_t size, int offset);
void				write_in_arena(t_env *env, unsigned char *bytes, size_t size
		, int offset);
int					get_args(unsigned char *bytes, unsigned char encoding_byte
		, t_decode *result);
int					parse_lmultitype(unsigned char *dest, t_env *env
		, t_process *cur_process, t_arg arg);
int					parse_multitype(unsigned char *dest, t_env *env
		, t_process *cur_process, t_arg arg);

#endif
