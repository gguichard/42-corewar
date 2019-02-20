/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/20 02:02:25 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include "asm.h"

void	err_handler(t_error err_id)
{
	char	buf[255];

	ft_bzero(&buf, 255);
	ft_strcat(buf, "Terminated with error: ");
	if (err_id == ERR_BADFMT)
		ft_strcat(buf, "Bad format");
	else if (err_id == ERR_GNL)
		ft_strcat(buf, "Read error");
	else if (err_id == ERR_NAME)
		ft_strcat(buf, "Bad header");
	else if (err_id == ERR_MALLOC)
		ft_strcat(buf, "Malloc error");
	else if (err_id == ERR_ERRNO)
		ft_strcat(buf, strerror(errno));
	ft_strcat(buf, "\n");
	write(2, buf, ft_strlen(buf));
}
