/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:55:22 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/18 04:36:11 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include "libft.h"
#include "asm.h"



t_error		create_cor(t_data *data, char *str)
{
	(void)data;
	t_error err_id;
	int		fd;
	char	*file_name;

	err_id = ERR_NOERROR;
	if (!(file_name = get_file_name(str)))
		return (ERR_MALLOC);
	if((fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0644)) < 0)
		return (ERR_ERRNO);
	fill_header(data, fd);
	fill_instruction(data, fd);
	close(fd);
	return (err_id);
}
