/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:57:40 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 01:41:08 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# define BUFF_SIZE 4096

# include "champion.h"
# include "process.h"
# include "corewar.h"

int	read_file(char *fn, t_champ *champ);
int	parsing_inst(unsigned char *str, t_process *proc, t_env *data);

#endif
