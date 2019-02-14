/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 20:35:54 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "process.h"
#include "corewar.h"
#include "champion.h"
#include "func_op.h"

unsigned char	*get_op(t_env *env, int size, unsigned char *str)
{
	unsigned char	*ret;
	int				offset;

	if (!(ret = (unsigned char *)ft_memalloc(sizeof(unsigned char) * size)))
		return (NULL);
	offset = size - ((env->arena + MEM_SIZE) - str);
	if (offset > 0)
	{
		ft_memmove(ret, str, (env->arena + MEM_SIZE) - str);
		ft_memmove((ret + ((env->arena + MEM_SIZE) - str)), env->arena, offset);
	}
	else
		ft_memmove(ret, str, size);
	return (ret);
}

unsigned int		get_encoding_byte(unsigned char *str)
{
	t_encode	*decode;

	decode = (t_encode *)str;
	printf("%d|%d|%d|%d\n", decode->arg1, decode->arg2, decode->arg3, decode->arg4);
	return (2);
}
