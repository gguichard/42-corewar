/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:39:09 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/15 01:44:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "asm.h"

void	init_inst(t_data *data)
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
	data->tab[17] = "%";
	data->tab[18] = "%:";
	data->tab[19] = "#";
	data->tab[20] = NULL;
}

int		is_int(char *str)
{
	int i;

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

t_lexer		check_if_valid(char *str, char *inst[])
{
	int i;
	int state;

	i = 0;
	while (inst[i] != NULL)
	{
		state = ft_strnequ(str, inst[i], ft_strlen(inst[i]));
		if (state == 1)
		{
			if (i <= 15)
				return (INST);
			else if (i == 16)
				return (is_int(str + 1) ? REG : ERROR);
			else if (i == 17)
				return ((is_int(str + 1) ? DIRE : ERROR));
			else if (i == 18)
				return (LABEL);
			else if (i == 19)
				return (COMMENT);
		}
		i++;
	}
	if (is_int(str))
		return (INDIR);
	return(ERROR);
}

int		get_tab_size(char **tab)
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

t_filter	get_filter(char **str, t_lexer lex_id)
{
	t_filter	elem;

	elem.name = *str;
	elem.label = lex_id;
	return(elem);
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
	while (i < data->f_size)
	{
		lex_id = check_if_valid(split[i], data->tab);
		if (lex_id != COMMENT && lex_id != ERROR)
		{
			data->filter[j] = get_filter(&split[i], lex_id);
			j++;
		}
		else if (lex_id == ERROR)
			return (ERR_BADFMT);
		i++;
	}
	return (ERR_NOERROR);
}
