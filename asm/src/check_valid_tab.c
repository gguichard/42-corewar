/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/16 03:07:14 by rvalenti         ###   ########.fr       */
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

t_error		check_is_label(t_data *data)
{
	int		i;
	int		n;

	i = 0;
	while (i < data->f_size)
	{
		n = 0;
		if (ft_strnequ(data->filter[i].op.name, "%:", 2))
			while (n < data->f_size)
			{
				if (ft_strnequ((data->filter[i].op.name + 2),
							data->filter[n].op.name,
							ft_strlen(data->filter[i].op.name + 2)))
					break ;
				n++;
			}
		if (n == data->f_size)
			return (ERR_BADFMT);
		i++;
	}
	return (ERR_NOERROR);
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
	if (check_is_label(data) != ERR_NOERROR)
		return (ERR_BADFMT);
	return (ERR_NOERROR);
}
