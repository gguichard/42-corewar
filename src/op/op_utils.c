/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:35:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 03:41:21 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "corewar.h"
#include "func_op.h"
#include "op.h"

void	swap_bytes(uint8_t *str, int size)
{
	int		idx;
	uint8_t	tmp;

	idx = 0;
	while (idx < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[idx];
		str[idx] = tmp;
		idx++;
	}
}

/*
** Rempli un buffer depuis un zone de l'arene.
** ATTENTION : N'applique pas de swap_bytes.
*/
void	fill_buff_from_arena(t_env *env, uint8_t *buffer, size_t size
		, int offset)
{
	if (offset < 0)
		offset += MEM_SIZE;
	if (offset > MEM_SIZE)
		offset %= MEM_SIZE;
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(buffer, env->arena + offset, size);
	else
	{
		ft_memcpy(buffer, env->arena + offset, MEM_SIZE - offset);
		ft_memcpy((buffer + MEM_SIZE - offset), env->arena
				, size - MEM_SIZE + offset);
	}
}

/**
** Ecrit de facon circulaire dans l'arene.
** ATTENTION : Les donnes sont swap avant d'etre ecrites.
*/
void	write_in_arena(t_env *env, uint8_t *bytes, size_t size, int offset)
{
	if (offset < 0)
		offset += MEM_SIZE;
	if (offset > MEM_SIZE)
		offset %= MEM_SIZE;
	swap_bytes(bytes, size);
	if ((offset + size) <= MEM_SIZE)
		ft_memcpy(env->arena + offset, bytes, size);
	else
	{
		ft_memcpy(env->arena + offset, bytes, MEM_SIZE - offset);
		ft_memcpy(env->arena, bytes + (MEM_SIZE - offset)
				, size - MEM_SIZE + offset);
	}
	swap_bytes(bytes, size);
}

/*
** Parse les arguments d'une instruction grace a l'octet d'encodage envoye
** en deuxieme parametre. Permet de specifier une taille pour les types DIR.
** Renvoie le nombre d'octets correspondant a l'encoding byte.
*/
int		decode_args(t_decode *decode, uint8_t *args, uint8_t encoding_byte
		, int dir_size)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	while (idx < decode->max_args)
	{
		if ((encoding_byte & 0xC0) == 0x40)
		{
			decode->tab[idx].type = REG_CODE;
			decode->tab[idx].value = *((int8_t *)args);
			if ((int)decode->tab[idx].value < 1
					|| (int)decode->tab[idx].value > 16)
				decode->tab[idx].type = BAD_REG;
			ret += 1;
			args += 1;
		}
		else if ((encoding_byte & 0xC0) == 0xC0
				|| ((encoding_byte & 0xC0) == 0x80 && dir_size == SHORT_DIR))
		{
			decode->tab[idx].type = ((encoding_byte & 0xC0) == 0xC0)
				? IND_CODE : DIR_CODE;
			swap_bytes(args, 2);
			decode->tab[idx].value = *((int16_t *)args);
			ret += 2;
			args += 2;
		}
		else if ((encoding_byte & 0xC0) == 0x80)
		{
			decode->tab[idx].type = DIR_CODE;
			swap_bytes(args, 4);
			decode->tab[idx].value = *((int32_t *)args);
			ret += 4;
			args += 4;
		}
		else
			break ;
		encoding_byte <<= 2;
		idx++;
	}
	return (ret);
}
