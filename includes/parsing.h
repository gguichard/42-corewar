/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:57:40 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/13 08:07:52 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# define BUFF_SIZE 4096

# include "op.h"
# include "corewar.h"
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_champ
{
	t_header		header;
	char			*code;
	unsigned int	len;
}				t_champ;

int				read_file(char *fn, t_champ *champ);
#endif
