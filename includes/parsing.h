/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:57:40 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 04:21:05 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H
# define BUFF_SIZE 4096

# include "champion.h"
# include "process.h"
# include "corewar.h"

int	read_file(char *fn, t_champ *champ);

#endif
