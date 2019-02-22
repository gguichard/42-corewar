/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 03:50:43 by wta               #+#    #+#             */
/*   Updated: 2019/02/22 07:08:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H
# define BUFF_SIZE		4096
# define HEADER_SIZE	2192
# define NAME_STR		".name "
# define COMMENT_STR	".comment "
# define NAME_SIZE		128
# define COMMENT_SIZE	2048

typedef struct	s_op
{
	char					*name;
	int						argc;
	uint8_t					type[3];
	uint8_t					opcode;
	int						cycle;
	char					*long_name;
	unsigned char			encoding	: 1;
	unsigned char			direct		: 1;
}				t_op;

typedef struct	s_data
{
	char	buf[BUFF_SIZE + 1];
	uint8_t	*inst;
	int		inst_len;
	char	*filename;
	int		fd;
}				t_data;

#endif
