/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_op.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:13:03 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 01:13:25 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_OP_H
# define FUNC_OP_H
# include "corewar.h"
# include "process.h"

void	live(t_env *env, t_process *cur_process, unsigned char *str);
void	ld(void);
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
#endif
