/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:55:22 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/14 04:20:35 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include <unistd.h>
#include <errno.h>

static char	*get_file_name(char *str)
{
	char *file_name;
	size_t	len;

	len = ft_strlen(str);
	while (len != 0 && str[len] != '.')
		len--;
	if (len == 0)
		len = ft_strlen(str);
	if(!(file_name = ft_strnew(len + 5)))
		return (NULL);
	ft_memcpy(file_name, str, len);
	ft_strcat(file_name, ".cor");
	return (file_name);
}

static void fill_cor(t_data *data, int fd)
{
	t_header header;

	header = data->header;
	header.magic = 0x00f383ea;
	write(fd, "\0", 1);
	write(fd, &header.magic, 4);
	write(fd, header.prog_name, 128);
	write(fd, header.comment, 2048);
}


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
	fill_cor(data, fd);
	close(fd);
	return (err_id);
}
