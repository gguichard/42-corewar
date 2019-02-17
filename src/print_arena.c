/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:05:46 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/17 22:31:14 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	put_hex(size_t nb)
{
	if (nb >= 16)
		put_hex(nb / 16);
	ft_putchar("0123456789abcdef"[nb % 16]);
}

static void	put_hex_with_pad(size_t nb, int padding)
{
	size_t	value;
	int		count;
	int		idx;

	value = nb;
	count = (nb == 0);
	while (value != 0)
	{
		value /= 16;
		count++;
	}
	idx = 0;
	while (idx < (padding - count))
	{
		ft_putchar('0');
		idx++;
	}
	put_hex(nb);
}

void		print_arena(t_env *env)
{
	size_t	idx;
	size_t	jdx;

	idx = 0;
	while (idx < MEM_SIZE)
	{
		ft_putstr("0x");
		put_hex_with_pad(idx, 4);
		ft_putstr(" :");
		jdx = 0;
		while (jdx < 64 && idx < MEM_SIZE)
		{
			ft_putchar(' ');
			put_hex_with_pad(env->arena[idx], 2);
			jdx++;
			idx++;
		}
		ft_putchar('\n');
	}
}
