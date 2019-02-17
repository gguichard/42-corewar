/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/18 00:04:24 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H

# include "corewar.h"
# include "process.h"
# include "op.h"

# define T_NRML	0
# define T_LONG	1
# define T_INDX	2

typedef struct		s_arg
{
	int				type;
	unsigned char	value[REG_SIZE];
}					t_arg;

typedef struct		s_decode
{
	t_arg			tab[MAX_ARGS_NUMBER];
	t_env			*env;
	t_process		*cur_process;
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
int					zjmp(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ldi(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					sti(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ft_fork(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					lld(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					lldi(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					ft_lfork(t_env *env, t_process *cur_process
		, unsigned char *bytes);
int					aff(t_env *env, t_process *cur_process
		, unsigned char *bytes);

/*
**	UTILS
*/
unsigned char		*get_in_arena(t_env *env, size_t size, int offset);
void				write_in_arena(t_env *env, unsigned char *bytes, size_t size
		, int offset);
int					get_args(unsigned char *bytes, unsigned char encoding_byte
		, t_decode *result, int sizeof_dir);
int					dispatch_multitype(unsigned char *dest
		, t_decode decode, t_arg arg, int eb);
void				fill_struct(t_env *env, t_process *cur_process
		, t_decode *decode);
void				increase_pc(t_process *process, int value);

#endif
