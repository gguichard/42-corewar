/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:39:09 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/16 00:33:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "asm.h"

extern t_op		g_op_tab[17];

int			is_int(char *str)
{
	int		i;

	i = 0;
	if (((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
			|| (ft_isdigit(str[i])))
		i++;
	else
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int			get_tab_size(char **tab)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (tab[i])
	{
		if (tab[i][0] != '#')
			n++;
		i++;
	}
	return (n);
}

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
	if (*str == 'r' && is_int(str + 1) == 1)
		filter->label = LX_REG;
	else if (ft_strnequ("%:", str, 2) == 1)
		filter->label = LX_DIRE;
	else if (*str == '%' && (is_int(str + 1) == 1))
		filter->label = LX_DIRE;
	else if (is_int(str) == 1)
		filter->label = LX_INDIR;
	else if (check_label(str) == 1)
		filter->label = LX_LABEL;
	if (*str != '#')
		filter->op.name = ft_strdup(str);
	return (*str != '#');
}

int			set_labels(char *str, t_filter *filter)
{
	int	idx;

	idx = 0;
	while (idx < 16)
	{
		if (ft_strnequ(g_op_tab[idx].name, str, ft_strlen(g_op_tab[idx].name)))
		{
			filter->op = g_op_tab[idx];
			filter->label = LX_INST;
			return (1);
		}
		idx += 1;
	}
	return (set_arg(str, filter));
}

t_error		lexer_parser(t_data *data, char **split)
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
		printf("raw= %s\n", split[i]);
		j += set_labels(split[i], &data->filter[j]);
		i++;
	}
	return (ERR_NOERROR);
}
