/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:55:22 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/17 07:40:00 by wta              ###   ########.fr       */
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

	idx = 0;
	while (idx < len)
	{
		if (ptr[idx] > 0)
			write(fd, &ptr[idx], 1);
		idx += 1;
	}
}

void        swap_bytes(unsigned char *str, int size)
{
	int                i;
	unsigned char    tmp;

	i = 0;
	while (i < size)
	{
		size--;
		tmp = str[size];
		str[size] = str[i];
		str[i] = tmp;
		i++;
	}
}

static void fill_header(t_data *data, int fd)
{
	t_header *header;

	header = &data->header;
	header->magic = COREWAR_EXEC_MAGIC;
	swap_bytes((unsigned char *)&header->magic, 4);
	write(fd, "\0", 1);
	write_magic((unsigned char *)&header->magic, fd, 4);
	write(fd, header->prog_name, 128);
	write(fd, "\0\0\0\0", 4);
	swap_bytes((unsigned char *)&data->header.prog_size, 4);
	write(fd, &data->header.prog_size, 4);
	write(fd, header->comment, 2048);
	write(fd, "\0\0\0\0", 4);
}

void		write_encoding_byte(t_op *op, int fd)
{
	uint8_t	encoding_byte;
	uint8_t	dire;
	uint8_t	ind;
	uint8_t	reg;
	int		idx;

	reg = 0x1;
	dire = 0x2;
	ind = 0x3;
	idx = 0;
	encoding_byte = 0;
	while (idx < 3)
	{
		if (op->type[idx] & T_DIR)
			encoding_byte |= dire;
		else if (op->type[idx] & T_IND)
			encoding_byte |= ind;
		else if (op->type[idx] & T_REG)
			encoding_byte |= reg;
		encoding_byte <<= 2;
		idx += 1;
	}
	write(fd, &encoding_byte, 1);
}

void		fill_instruction(t_data *data, int fd)
{
	t_filter	*elem;
	int			idx;
	int			jdx;

	idx = 0;
	while (idx < data->f_size)
	{
		elem = &data->filter[idx];
		if (elem->label != LX_LABEL)
		{
			if (elem->label == LX_INST)
			{
				write(fd, &elem->op.opcode, 1);
				if (elem->op.encoding > 0)
					write_encoding_byte(&elem->op, fd);
				jdx = 0;
				while (jdx < elem->op.argc)
				{
					swap_bytes((uint8_t*)&data->filter[idx + jdx + 1].value, 4);
					if (data->filter[idx + jdx + 1].label == LX_LABEL)
						write(fd, &data->filter[idx + jdx + 1].size, data->filter[idx + jdx + 1].size);
					else
						write(fd, &data->filter[idx + jdx + 1].value, data->filter[idx + jdx + 1].size);
					jdx += 1;
				}
				idx += jdx;
			}
		}
		idx += 1;
	}
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
