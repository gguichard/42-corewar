/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:39:09 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/18 05:13:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "asm.h"

extern t_op	g_op_tab[17];

int			check_label(char *str)
{
	int		i;
	int		n;
	int		len;

	i = 0;
	n = 0;
	len = ft_strlen(str) - 1;
	if (str[len] != ':')
		return (0);
	while (str[i] && i < len)
	{
		n = 0;
		while (LABEL_CHARS[n])
		{
			if (str[i] == LABEL_CHARS[n])
				break ;
			n++;
		}
		if (!LABEL_CHARS[n])
			return (0);
		i++;
	}
	return (1);
}

int			set_arg(char *str, t_filter *filter)
{
	if (is_int(str) == 1)
		filter->label = LX_INDIR;
	else if (check_label(str) == 1)
		filter->label = LX_LABEL;
	else if (*str == 'r' && is_int(str + 1) == 1)
		filter->label = LX_REG;
	else if (ft_strnequ("%:", str, 2) == 1)
		filter->label = LX_DIRE;
	else if (*str == '%' && (is_int(str + 1) == 1))
		filter->label = LX_DIRE;
	else if (*str == ':')
		filter->label = LX_INDIR;
	if (*str != '#')
		filter->op.name = ft_strdup(str);
	return (*str != '#');
}

int			set_labels(char *str, t_filter *filter)
{
	size_t	op_len;
	size_t	str_len;
	int		idx;

	idx = 0;
	str_len = ft_strlen(str);
	while (idx < 16)
	{
		op_len = ft_strlen(g_op_tab[idx].name);
		if (str_len == op_len && ft_strnequ(g_op_tab[idx].name, str, op_len))
		{
			filter->op = g_op_tab[idx];
			filter->label = LX_INST;
			return (1);
		}
		idx += 1;
	}
	return (set_arg(str, filter));
}

t_error		classify(t_data *data, char **split)
{
	int			i;
	int			j;

	i = 0;
	data->f_size = get_tab_size(split);
	if (!(data->filter = (t_filter*)malloc(sizeof(t_filter) * data->f_size)))
		return (ERR_MALLOC);
	ft_memset(data->filter, 0, sizeof(t_filter));
	j = 0;
	while (split[i] != NULL && j < data->f_size)
	{
		j += set_labels(split[i], &data->filter[j]);
		i++;
	}
	return (ERR_NOERROR);
}
