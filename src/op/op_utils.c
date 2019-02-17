/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 06:42:45 by gguichar         ###   ########.fr       */
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

void			write_in_arena(t_env *env, unsigned char *bytes, size_t size
		, int offset)
{
	if (offset < 0)
		offset += MEM_SIZE;
	if (offset > MEM_SIZE)
		offset %= MEM_SIZE;
	ft_swap_bytes(bytes, size);
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(&env->arena[offset], bytes, size);
	else
	{
		ft_memcpy(env->arena + offset, bytes, MEM_SIZE - offset);
		ft_memcpy(env->arena, bytes + (MEM_SIZE - offset)
				, size - MEM_SIZE + offset);
	}
	ft_swap_bytes(bytes, size);
}

static int		get_arg_with_type(t_arg *arg, unsigned char *bytes, int type
		, int sizeof_dir)
{
	int	size;

	size = 0;
	if (type == DIR_CODE)
		size = 4;
	else if (type == IND_CODE)
		size = 2;
	else if (type == REG_CODE)
		size = 1;
	if (type == DIR_CODE && sizeof_dir == 1)
		size = 2;
	if (size > 0)
	{
		ft_memcpy(arg->value, bytes, size);
		ft_swap_bytes(arg->value, size);
	}
	if (type == REG_CODE && (*bytes < 1 || *bytes > 16))
		type = 0;
	arg->type = type;
	return (size);
}

int				get_args(unsigned char *bytes, unsigned char encoding_byte
		, t_decode *decode, int sizeof_dir)
{
	int	idx;
	int	ret;
	int	type;
	int	size;

	ft_memset(decode, 0, sizeof(t_decode));
	idx = 0;
	ret = 0;
	while (idx < MAX_ARGS_NUMBER)
	{
		type = encoding_byte & (0xC0 >> 2 * idx);
		if (type == 0)
			break ;
		type >>= (6 - 2 * idx);
		size = get_arg_with_type(decode->tab + idx, bytes + ret
				, type, sizeof_dir);
		if (size == 0)
			break ;
		ret += size;
		idx++;
	}
	return (ret);
}
