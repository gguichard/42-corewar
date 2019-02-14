/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:25:14 by wta               #+#    #+#             */
/*   Updated: 2019/02/14 06:51:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"

typedef enum	s_error
{
	ERR_NOERROR,
	ERR_ERRNO,
	ERR_BADFMT,
	ERR_GNL,
	ERR_NAME,
	ERR_MALLOC
}				t_error;

typedef struct	s_list_ref
{
	t_list		*head;
	t_list		*tail;
}				t_list_ref;

typedef struct	s_label
{
	char	*name;
	int		offset;
}				t_label;

typedef struct	s_type
{
	char	arg1;
	char	arg2;
	char	arg3;
}				t_type;

typedef struct	s_op
{
	char			*op;
	int				argc;
	t_type			arg_type;
	char			opcode;
	int				cycle;
	char			*name;
	char			encoding	: 1;
	char			direct		: 1;
}				t_op;

typedef struct	s_param
{
	t_op		op;
	int			argv[3];
}				t_param;

typedef struct	s_data
{
	t_header	header;
	t_op		op_tab[16];
	t_list_ref	list;
}				t_data;

t_error			read_file(char *file, t_data *data);
void			set_op_tab(t_op op_tab[]);
t_error			create_cor(t_data *data, char *str);

#endif
