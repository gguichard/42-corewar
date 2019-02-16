/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/16 02:22:35 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_arg(t_data *data, int i)
{
	int n;

	n = 0;
	while (++n <= data->filter[i].op.argc)
	{
		if (n == 1)
		{
			if ((data->filter[i + n].label
						& data->filter[i].op.arg_type.arg1) == 0)
				return (-1);
		}
		else if (n == 2)
		{
			if ((data->filter[i + n].label
						& data->filter[i].op.arg_type.arg2) == 0)
				return (-1);
		}
		else if (n == 3)
		{
			if ((data->filter[i + n].label
						& data->filter[i].op.arg_type.arg3) == 0)
				return (-1);
		}
	}
	return (n);
}

t_error		check_valid_tab(t_data *data)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < data->f_size)
	{
		printf("inst: %s\n", data->filter[i].op.name);
		if (data->filter[i].label == 0)
		{
			if ((n = check_arg(data, i)) == -1)
				return (ERR_BADFMT);
			i += n;
		}
		else if (data->filter[i].label == 8)
			i++;
		else
			return (ERR_BADFMT);
	}
	return (ERR_NOERROR);
}
