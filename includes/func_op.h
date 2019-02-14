/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 20:38:45 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H
# include "corewar.h"
# include "process.h"

typedef struct		s_encode
{
	unsigned int	arg1: 2;
	unsigned int	arg2: 2;
	unsigned int	arg3: 2;
	unsigned int	arg4: 2;
}					t_encode;

void				live(t_env *env, t_process *cur_process, unsigned char *str);
void				ld(t_env *env, t_process *cur_process, unsigned char *str);

void	st(void);
void	add(void);
void	sub(void);
void	ft_and(void);
void	ft_or(void);
void	ft_xor(void);
void	zjump(void);
void	ldi(void);
void	sti(void);
void	ft_fork(void);
void	lld(void);
void	lldi(void);
void	lfork(void);
void	aff(void);
/*
**	UTILS
*/
unsigned char		*get_op(t_env *env, int size, unsigned char *str);
unsigned int		get_encoding_byte(unsigned char *str);
#endif
