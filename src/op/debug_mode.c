/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 06:16:22 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/19 07:15:51 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "func_op.h"
#include "op.h"

void	debug_mode_value(char *op, t_decode decode, int nb_args, int value)
{
	int	idx;

	idx = 0;
	ft_printf("%-10s :", op);
	while (idx < nb_args)
	{
		ft_printf("\t%s%-5d"
				, (decode.tab[idx].type == REG_CODE ? "r" : "")
				, decode.tab[idx].value);
		idx++;
	}
	ft_printf("\t(%d)", value);
	ft_printf("\n");
}

void	debug_mode(char *op, t_decode decode, int nb_args)
{
	int	idx;

	idx = 0;
	ft_printf("%-10s :", op);
	while (idx < nb_args)
	{
		ft_printf("\t%s%-5d"
				, (decode.tab[idx].type == REG_CODE ? "r" : "")
				, decode.tab[idx].value);
		idx++;
	}
	ft_printf("\n");
}

void	debug_mode_nodecode_val(char *op, int *args, int nb_args, int value)
{
	int	idx;

	idx = 0;
	ft_printf("%-10s :", op);
	while (idx < nb_args)
	{
		ft_printf("\t%-5d", args[idx]);
		idx++;
	}
	ft_printf("\t(%d)", value);
	ft_printf("\n");
}

void	debug_mode_nodecode(char *op, int *args, int nb_args)
{
	int	idx;

	idx = 0;
	ft_printf("%-10s :", op);
	while (idx < nb_args)
	{
		ft_printf("\t%-5d", args[idx]);
		idx++;
	}
	ft_printf("\n");
}
