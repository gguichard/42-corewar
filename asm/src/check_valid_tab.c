/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/17 03:33:44 by rvalenti         ###   ########.fr       */
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
		inst->op.direct = arg->op.direct;
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

void		set_label_size(t_data *data)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < data->f_size)
	{
		data->filter[i].index = n;
		if (data->filter[i].label == LX_INST && data->filter[i].op.encoding == 1)
			n += 2;
		else if (data->filter[i].label == LX_INST)
			n += 1;
		else if (data->filter[i].label == LX_REG)
			n += 1;
		else if (data->filter[i].label == LX_DIRE && data->filter[i].op.direct == 1)
			n += 2;
		else if (data->filter[i].label == LX_DIRE)
			n += 4;
		else if (data->filter[i].label == LX_INDIR)
			n += 2;
		i++;
	}
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
	set_label_size(data);
	for (int i = 0; i < data->f_size; i++)
		ft_printf("%s\tlabel= %d\tindex= %d\tencoding=%u\tdirect=%u\n", data->filter[i].op.name, data->filter[i].label, data->filter[i].index,data->filter[i].op.encoding,data->filter[i].op.direct);
	return (ERR_NOERROR);
}
