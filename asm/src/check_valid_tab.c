/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/15 21:46:41 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_error		check_arg(t_data *data, t_op op, t_type type, int i)
{

}

t_error		check_op(t_data *data, t_filter filter, t_op op, int i)
{
	int		n;

	n = 0;
	while (n < op.argc)
	{
		check_arg();
	}
}

t_error		check_inst(t_data *data, t_filter filter, int i)
{
	int		n;

	n = 0;
	while (data->op_tab[n])
	{
		if (ft_strequ(filter.name, data->op_tab[n]))
		{
			if (check_op(data, filter, data->op_tab[n], i) != ERR_NOERROR)
				return (ERR_BADFMT);
		}
		n++;
	}
}

t_error		check_valid_tab(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->f_size)
	{	
		if (data->filter[i].label == 0)
		{
			if (check_inst(data, data->filter[i], i) != ERR_NOERROR)
				return (ERR_BADFMT);	
		}
		i++;
	}
}
