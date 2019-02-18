/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:19:44 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/18 01:26:02 by wta              ###   ########.fr       */
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
		if (id == LX_DIRE)
			arg->op.direct = inst->op.direct;
		if ((id & inst->op.type[n]) == 0)
			return (-1);
		inst->op.type[n] &= id;
		if (id == LX_DIRE || id == LX_REG)
			arg->value = (int)ft_strtol(arg->op.name + 1, &endptr, 10);
		else if (id == LX_INDIR)
			arg->value = (int)ft_strtol(arg->op.name, &endptr, 10);
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
		if (ft_strnequ(data->filter[i].op.name, "%:", 2)
				|| *data->filter[i].op.name == ':')
			while (n < data->f_size)
			{
				if (ft_strnequ((data->filter[i].op.name + 1 + (*data->filter[i].op.name != ':')),
							data->filter[n].op.name,
							ft_strlen(data->filter[i].op.name + 1 + (*data->filter[i].op.name != ':'))))
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
	unsigned int	size;
	int				i;

	i = 0;
	size = 0;
	while (i < data->f_size)
	{
		data->filter[i].index = size;
		if (data->filter[i].label == LX_LABEL)
			lst_pushback(&data->label_lst, lstnew_mallocfree(&data->filter[i].op));
		if (data->filter[i].label == LX_INST && data->filter[i].op.encoding == 1)
			data->filter[i].size = 2;
		else if (data->filter[i].label == LX_INST)
			data->filter[i].size = 1;
		else if (data->filter[i].label == LX_REG)
			data->filter[i].size = 1;
		else if (data->filter[i].label == LX_DIRE && data->filter[i].op.direct == 1)
			data->filter[i].size = 2;
		else if (data->filter[i].label == LX_DIRE)
			data->filter[i].size = 4;
		else if (data->filter[i].label == LX_INDIR)
			data->filter[i].size = 2;
		size += data->filter[i].size;
		i++;
	}
	data->header.prog_size = size;
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
			{
				ft_printf("1\n");
				return (ERR_BADFMT);
			}
			i += n;
		}
		else if (data->filter[i].label == LX_LABEL)
			i++;
		else
		{
				ft_printf("2\n");
			return (ERR_BADFMT);
		}
	}
	if (check_is_label(data) != ERR_NOERROR)
		return (ERR_BADFMT);
	set_label_size(data);
//	for (int i = 0; i < data->f_size; i++)
//		ft_printf("%s\tlabel= %d\tindex= %d\tencoding=%u\tdirect=%u\n", data->filter[i].op.name, data->filter[i].label, data->filter[i].index,data->filter[i].op.encoding,data->filter[i].op.direct);
	return (ERR_NOERROR);
}
