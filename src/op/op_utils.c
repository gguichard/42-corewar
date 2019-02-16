/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/16 01:45:43 by gguichar         ###   ########.fr       */
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

static int		get_arg_with_type(unsigned char *dest, unsigned char *bytes
		, int type)
{
	int	size;
	int	reg;

	ft_memset(dest, 0, REG_SIZE);
	if (type == DIR_CODE)
		size = 4;
	else if (type == IND_CODE)
		size = 2;
	else if (type == REG_CODE)
		size = 1;
	else
		size = 0;
	ft_memcpy(dest, bytes, size);
	ft_swap_bytes(dest, size);
	if (type == REG_CODE)
	{
		reg = *((int *)dest);
		if (reg < 1 || reg > 16)
			return (0);
	}
	return (size);
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

int				reg_isvalid(unsigned char *reg)
{
	if (*((int *)reg) > 0 && *((int *)reg) < 17)
		return (1);
	return (0);
}
