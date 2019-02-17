/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:25:14 by wta               #+#    #+#             */
/*   Updated: 2019/02/17 07:01:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <inttypes.h>
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

typedef struct	s_op
{
	char			*name;
	int				argc;
	uint8_t			type[3];
	uint8_t			opcode;
	int				cycle;
	char			*long_name;
	unsigned char			encoding	: 1;
	unsigned char			direct		: 1;
}				t_op;

typedef enum 	s_lexer
{
	LX_INST,
	LX_REG,
	LX_DIRE,
	LX_ERROR,
	LX_INDIR,
	LX_COMMENT,
	LX_SIX,
	LX_SEVEN,
	LX_LABEL
}				t_lexer;

typedef struct 	s_filter
{
	t_op			op;
	t_lexer			label;
	int				size;
	int				value;
	int				index;
}				t_filter;

typedef struct	s_data
{
	t_header	header;
	t_list_ref	label_lst;
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

t_error			classify(t_data *data, char **split);
int				get_filter(char *str, t_filter *filter, t_lexer lex_id);
int				get_tab_size(char **tab);
t_lexer			check_if_valid(char *str, char **inst);
int				is_int(char *str);
void			init_inst(t_data *data);
t_error			check_valid_tab(t_data *data);

void			lst_pushback(t_list_ref *list, t_list *node);
t_list			*lstnew_mallocfree(void *content);

void			write_bytes(uint8_t *ptr, int fd, int len, int size);

#endif
