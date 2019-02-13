/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:25:14 by wta               #+#    #+#             */
/*   Updated: 2019/02/14 00:31:47 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define BUFF_SIZE 4096

# include "op.h"

typedef enum	s_error
{
	ERR_NOERROR,
	ERR_ERRNO,
	ERR_BADFMT,
	ERR_NAME,
	ERR_MALLOC
}				t_error;

typedef struct	s_data
{
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
}				t_data;

t_error			read_file(char *file, t_data *data);

#endif
