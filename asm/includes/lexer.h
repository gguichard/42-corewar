/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:44:00 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/14 20:53:47 by rvalenti         ###   ########.fr       */
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
	REG
}				t_lexer


#endif
