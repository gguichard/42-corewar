/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 23:12:22 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"
#include "func_op.h"

unsigned char	*get_in_arena(t_env *env, size_t size, int offset)
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
		ft_memcpy(ret, env->arena + offset, MEM_SIZE - offset);
		ft_memcpy((ret + MEM_SIZE - offset), env->arena
				, size - MEM_SIZE + offset);
	}
	return (ret);
}

void			write_in_arena(t_env *env, unsigned char *bytes, size_t size
		, int offset)
{
	if (offset < 0)
		offset += MEM_SIZE;
	if (offset > MEM_SIZE)
		offset %= MEM_SIZE;
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(&env->arena[offset], bytes, size);
	else
	{
		ft_memcpy(env->arena + offset, bytes, MEM_SIZE - offset);
		ft_memcpy(env->arena, bytes + (MEM_SIZE - offset)
				, size - MEM_SIZE + offset);
	}
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

static int		get_arg_with_type(unsigned char *dest, unsigned char *bytes
		, int type)
{
	if (type == REG_CODE)
	{
		ft_memcpy(dest, bytes, 1);
		return (1);
	}
	else if (type == DIR_CODE)
	{
		ft_memcpy(dest, bytes, 4);
		ft_swap_bytes(dest, 4);
		return (4);
	}
	else if (type == IND_CODE)
	{
		ft_memcpy(dest, bytes, 2);
		ft_swap_bytes(dest, 2);
		return (2);
	}
	return (0);
}

int				get_args(unsigned char *bytes, unsigned char encoding_byte
		, t_decode *result)
{
	int	i;
	int	type;
	int	size;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		type = encoding_byte & (0xC0 >> 2 * i);
		if (type == 0)
			break ;
		type >>= (6 - 2 * i);
		result->tab[i].type = type;
		size = get_arg_with_type(result->tab[i].value, bytes, type);
		if (size == 0)
			return (0);
		bytes += size;
		i++;
	}
	return (1);
}
