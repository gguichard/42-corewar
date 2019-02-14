/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:44:00 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/14 23:49:55 by rvalenti         ###   ########.fr       */
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
}				t_lexer

typedef struct 	s_filter
{
	char	*name;
	t_lexer	label;
}				t_filter;

#endif
