/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:25:14 by wta               #+#    #+#             */
/*   Updated: 2019/02/15 04:03:07 by rvalenti         ###   ########.fr       */
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

typedef enum 	s_lexer
{
	INST,
	REG,
	DIRE,
	ERROR,
	INDIR,
	COMMENT,
	SIX,
	SEVEN,
	LABEL
}				t_lexer;

typedef struct 	s_filter
{
	char	*name;
	t_lexer	label;
}				t_filter;

typedef struct	s_data
{
	t_header	header;
	t_op		op_tab[16];
	t_list_ref	list;
	char 		*tab[21];
	t_filter	*filter;
	int			f_size;
}				t_data;

t_error			read_file(char *file, t_data *data);
void			set_op_tab(t_op op_tab[]);
t_error			create_cor(t_data *data, char *str);
char			**split_by_str(char *str, char *delim);
char			*expand_label(char *str);
char			**split_by_str(char *str, char *delim);
char			*strjoin_add_c(char const *s1, char const *s2, char c);

t_error			lexer_parser(t_data *data, char **tab);
int				get_filter(char *str, t_filter *filter, t_lexer lex_id);
int				get_tab_size(char **tab);
t_lexer			check_if_valid(char *str, char **inst);
int				is_int(char *str);
void			init_inst(t_data *data);

#endif
