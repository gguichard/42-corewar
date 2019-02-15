/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:39:09 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/15 04:32:07 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "asm.h"

void		init_inst(t_data *data)
{
	data->tab[0] = "live";
	data->tab[1] = "ld";
	data->tab[2] = "st";
	data->tab[3] = "add";
	data->tab[4] = "sub";
	data->tab[5] = "and";
	data->tab[6] = "or";
	data->tab[7] = "xor";
	data->tab[8] = "zjmp";
	data->tab[9] = "ldi";
	data->tab[10] = "sti";
	data->tab[11] = "fork";
	data->tab[12] = "lld";
	data->tab[13] = "lldi";
	data->tab[14] = "lfork";
	data->tab[15] = "aff";
	data->tab[16] = "r";
	data->tab[17] = "%:";
	data->tab[18] = "%";
	data->tab[19] = "#";
	data->tab[20] = NULL;
}

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

t_lexer		check_if_valid(char *str, char *inst[])
{
	int		i;

	i = 0;
	if (is_int(str))
		return (INDIR);
	else if (check_label(str))
		return (LABEL);
	while (inst[i] != NULL)
	{
		if (ft_strnequ(str, inst[i], ft_strlen(inst[i])) == 1)
		{
			if (i <= 15 && ft_strlen(str) == ft_strlen(inst[i]))
				return (INST);
			else if (i == 16)
				return (is_int(str + 1) ? REG : ERROR);
			else if (i == 18)
				return ((is_int(str + 1) ? DIRE : ERROR));
			else if (i == 17)
				return (DIRE);
			else if (i == 19)
				return (COMMENT);
		}
		i++;
	}
	return (ERROR);
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

int			get_filter(char *str, t_filter *filter, t_lexer lex_id)
{
	if ((filter->name = ft_strdup(str)) == NULL)
		return (0);
	filter->label = lex_id;
	return (1);
}

t_error		lexer_parser(t_data *data, char **split)
{
	t_lexer		lex_id;
	int			i;
	int			j;

	i = 0;
	data->f_size = get_tab_size(split);
	init_inst(data);
	if (!(data->filter = (t_filter*)malloc(sizeof(t_filter) * data->f_size)))
		return (ERR_MALLOC);
	j = 0;
	while (split[i] != NULL && j < data->f_size)
	{
		printf("raw= %s\n", split[i]);
		lex_id = check_if_valid(split[i], data->tab);
		if (lex_id != COMMENT && lex_id != ERROR)
		{
			if (get_filter(split[i], &data->filter[j], lex_id) == 0)
				return (ERR_MALLOC);
			j++;
		}
		else if (lex_id == ERROR)
			return (ERR_BADFMT);
		i++;
	}
	return (ERR_NOERROR);
}
