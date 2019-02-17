/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/17 03:43:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_arg(t_data *data, int i)
{
	t_filter	*inst;
	t_filter	*arg;
	t_lexer		id;
	char		*endptr;
	int			n;

	n = 0;
	inst = &data->filter[i];
	while (n < data->filter[i].op.argc)
	{
		arg = &data->filter[i + 1 + n];
		id = arg->label;
		if (arg->label == LX_DIRE)
			arg->op.direct = inst->op.direct;
		if ((id & inst->op.type[n]) == 0)
			return (-1);
		if (id == LX_DIRE || id == LX_REG)
			inst->argv[n] = ft_strtol(arg->op.name + 1, &endptr, 10);
		else if (id == LX_INDIR)
			inst->argv[n] = ft_strtol(arg->op.name, &endptr, 10);
		n += 1;
	}
	return (n + 1);
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
		if (data->filter[i].label == LX_INST)
		{
			if ((n = check_arg(data, i)) == -1)
				return (ERR_BADFMT);
			i += n;
		}
		else if (data->filter[i].label == LX_LABEL)
			i++;
		else
			return (ERR_BADFMT);
	}
	if (check_is_label(data) != ERR_NOERROR)
		return (ERR_BADFMT);
	return (ERR_NOERROR);
}
