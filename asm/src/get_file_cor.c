/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:55:22 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/17 05:17:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include "libft.h"
#include "asm.h"

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

void	write_magic(uint8_t *ptr, int fd, int len)
{
	int		idx;

	idx = len - 1;
	while (idx >= 0)
	{
		if (ptr[idx] > 0)
			write(fd, &ptr[idx], 1);
		idx -= 1;
	}
}

void	write_bytes(uint8_t *ptr, int fd, int len)
{
	int		idx;

	idx = len - 1;
	while (idx >= 0)
	{
		write(fd, &ptr[idx], 1);
		idx -= 1;
	}
}

static void fill_header(t_data *data, int fd)
{
	t_header *header;

	header = &data->header;
	header->magic = COREWAR_EXEC_MAGIC;
	write(fd, "\0", 1);
	write_magic((uint8_t *)&header->magic, fd, sizeof(uint32_t));
	write(fd, header->prog_name, 128);
	write(fd, "\0\0\0\0", 4);
	write_bytes((uint8_t *)&data->header.prog_size, fd, sizeof(uint32_t));
	write(fd, header->comment, 2048);
	write(fd, "\0\0\0\0", 4);
}

void		fill_instruction(t_data *data, int fd)
{
	
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
	fill_header(data, fd);
	fill_instruction(data, fd);
	close(fd);
	return (err_id);
}
