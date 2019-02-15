/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:39:09 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/15 01:08:56 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

void	init_inst(t_data *data)
{
	char **inst;

	inst = data->tab;
	inst[0] = "live";
	inst[1] = "ld";
	inst[2] = "st";
	inst[3] = "add";
	inst[4] = "sub";
	inst[5] = "and";
	inst[6] = "or";
	inst[7] = "xor";
	inst[8] = "zjmp";
	inst[9] = "ldi";
	inst[10] = "sti";
	inst[11] = "fork";
	inst[12] = "lld";
	inst[13] = "lldi";
	inst[14] = "lfork";
	inst[15] = "aff";
	inst[16] = "r";
	inst[17] = "%";
	inst[18] = "%:";
	inst[19] = "#";
	inst[20] = NULL;
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

t_lexer		check_if_valid(char *str, char **inst)
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

t_filter	*get_filter(char **str, t_lexer lex_id)
{
	t_filter	*elem;

	if (!(elem = (t_filter *)malloc(sizeof(t_filter))))
		return (NULL);
	elem->name = *str;
	elem->label = lex_id;
	return(elem);
}

t_error		lexer_parser(t_data *data, char **tab)
{
	t_lexer		lex_id;
	int			i;
	int			n;
	char		**inst;
	t_filter	**filter;

	i = 0;
	n = get_tab_size(tab);
	inst = data->tab;
	init_inst(data);
	if (!(filter = (t_filter**)malloc(sizeof(t_filter*) * (n + 1))))
		return (ERR_MALLOC);
	filter[n] = NULL;
	n = 0;
	while (tab[i])
	{
		lex_id = check_if_valid(tab[i], inst);
		if (lex_id != COMMENT && lex_id != ERROR)
		{
			if (!(filter[n] = get_filter(&tab[i], lex_id)))
				return (ERR_MALLOC);
			else if (lex_id == ERROR)
				return (ERR_BADFMT);
			n++;
		}
		i++;
	}
	return (ERR_NOERROR);
}
