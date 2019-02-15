/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 01:45:58 by vifonne          ###   ########.fr       */
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

int		get_args(unsigned char *str, char encoding_byte, t_decode *result)
{
	int	i;
	int	type;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		type = encoding_byte & (192 >> 2 * i);
		if (type == 0)
			break ;
		type >>= (6 - 2 * i);
		result->tab[i].type = type;
		if (type == REG_CODE)
		{
			result->tab[i].value = *str;
			str += sizeof(char);
		}
		else if (type == DIR_CODE)
		{
			result->tab[i].value = *((int *)str);
			str += sizeof(int);
		}
		else if (type == IND_CODE)
		{
			result->tab[i].value = *((short *)str);
			str += sizeof(short);
		}
		else
			return (0);
		i++;
	}
	return (1);
}
