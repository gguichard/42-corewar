/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:44:00 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/15 01:11:08 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum 	s_lexer
{
	INST,
	DIRE,
	INDIR,
	LABEL,
	COMMENT,
	REG,
	ERROR
}				t_lexer;

typedef struct 	s_filter
{
	char	*name;
	t_lexer	label;
}				t_filter;


t_error		lexer_parser(t_data *data, char **tab);
t_filter	*get_filter(char **str, t_lexer lex_id);
int			get_tab_size(char **tab);
t_lexer		check_if_valid(char *str, char **inst);
int			is_int(char *str);
void		init_inst(t_data *data);
#endif
