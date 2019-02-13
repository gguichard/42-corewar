/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:10 by wta               #+#    #+#             */
/*   Updated: 2019/02/14 00:32:48 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "asm.h"

t_error	check_first_line(int fd)
{
	char	buf[1];
	int		ret;

	ret = read(fd, buf, 1);
	if (buf[0] != '\n' && buf[0] != '\t' && buf[0] != '#' && buf[0] != '.')
		return (ERR_BADFMT);
	ret = lseek(fd, 0, SEEK_CUR);
	if (ret == -1)
		return (ERR_ERRNO);
	return (ERR_NOERROR);
}

t_error	get_next_info(int fd)
{
	t_error	err_id;
	char	*line;

	err_id = ERR_NOERROR;

	return ();
}

t_error	read_file(char *file, t_data *data)
{
	t_error	err_id;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	err_id = check_first_line(fd);
	if (err_id == ERRNO_ERROR)
	{
		while (get_next_info(fd) == ERR_NOERROR)
		{
			
		}
	}
	close(fd);
	return (err_id);
}
