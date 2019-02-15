/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 05:52:16 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

unsigned char	*get_in_circle_mem(t_env *env, int size, int offset)
{
	unsigned char	*ret;

	if (!(ret = (unsigned char *)ft_memalloc(sizeof(unsigned char) * size)))
		return (NULL);
	if (offset < 0)
		offset += MEM_SIZE;
	if (offset > MEM_SIZE)
		offset %= MEM_SIZE;
	if ((offset + size) <= MEM_SIZE)
		ft_memmove(ret, env->arena + offset, size);
	else
	{
		ft_memmove(ret, env->arena + offset, MEM_SIZE - offset);
		ft_memmove((ret + MEM_SIZE - offset), env->arena, size - MEM_SIZE + offset);
	}
	return (ret);
}

static void		ft_swap_bytes(unsigned char *str, int size)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	while (i < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
		i++;
	}
}

int				get_args(unsigned char *str, unsigned char encoding_byte
		, t_decode *result)
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
			ft_memcpy(result->tab[i].value, str, 1);
			str += 1;
		}
		else if (type == DIR_CODE)
		{
			ft_memcpy(result->tab[i].value, str, 4);
			ft_swap_bytes(result->tab[i].value, 4);
			str += 4;
		}
		else if (type == IND_CODE)
		{
			ft_memcpy(result->tab[i].value, str, 2);
			ft_swap_bytes(result->tab[i].value, 2);
			str += 2;
		}
		else
			return (0);
		i++;
	}
	return (1);
}
