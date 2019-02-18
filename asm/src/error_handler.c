/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/18 06:25:42 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <unistd.h>

void	err_handler(t_error err_id)
{
	if (err_id == ERR_BADFMT)
		write(2, "bad format\n", 11);
	else if (err_id == ERR_GNL)
		write(2, "Read Error\n", 11);
	else if (err_id == ERR_NAME)
		write(2, "bad header\n", 11);
	else if (err_id == ERR_MALLOC)
		write(2, "Malloc Error\n", 13);
}
