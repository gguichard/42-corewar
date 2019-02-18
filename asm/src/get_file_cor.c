/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_cor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:55:22 by rvalenti          #+#    #+#             */
/*   Updated: 2019/02/18 01:37:15 by wta              ###   ########.fr       */
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

void		manage_ind(t_filter *arg, int fd)
{
	uint16_t	two_bytes;

	if (arg->size == 4)
	{
		swap_bytes((uint8_t*)&arg->value, 4);
		write(fd, &arg->value, 4);
	}
	else
	{
		two_bytes = (uint16_t)arg->value;
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
}

void		manage_dir(t_filter *inst, t_filter *arg, int fd)
{
	uint16_t	two_bytes;

	if (inst->op.direct == 1 || arg->size == 2)
	{
		two_bytes = (uint16_t)arg->value;
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
	else
	{
		swap_bytes((uint8_t*)&arg->value, 4);
		write(fd, &arg->value, 4);
	}
}

void		manage_label(t_filter *inst, t_filter *arg, t_filter *label, int fd)
{
	uint16_t	two_bytes;
	uint32_t	four_bytes;

	if (inst->op.direct == 1 || arg->size == 2)
	{
		two_bytes = (uint16_t)(label->index - inst->index);
		swap_bytes((uint8_t*)&two_bytes, 2);
		write(fd, &two_bytes, 2);
	}
	else
	{
		four_bytes = (uint32_t)(label->index - inst->index);
		swap_bytes((uint8_t*)&four_bytes, 4);
		write(fd, &four_bytes, 4);
	}
}

t_filter	*is_label(char *str, t_list *head)
{
	t_filter	*label;
	t_list		*node;
	int			offset;

	node = head;
	if (ft_strnequ("%:", str, 2) == 0 && *str != ':')
		return (NULL);
	offset = 1 + (*str == '%');
	while (node != NULL)
	{
		label = (t_filter*)node->content;
		if (ft_strlen(label->op.name) - 1 == ft_strlen(str + offset)
				&& ft_strnequ(label->op.name, str + offset, ft_strlen(str + offset)))
		{
			return (label);
		}
		node = node->next;
	}
	return (NULL);
}

int			manage_inst(t_filter *inst, t_data *data, int fd)
{
	t_filter	*arg;
	t_filter	*label;
	int			idx;

	arg = inst + 1;
	idx = 0;
	(void)data;
	write(fd, &inst->op.opcode, 1);
	if (inst->op.encoding == 1)
		write_encoding_byte(&inst->op, fd);
	while (idx < inst->op.argc)
	{
		if ((label = is_label(arg->op.name, data->label_lst.head)) != NULL)
			manage_label(inst, arg, label, fd);
		else if (arg->label == LX_INDIR)
			manage_ind(arg, fd);
		else if (arg->label == LX_REG)
			write(fd, &arg->value, 1);
		else if (arg->label == LX_DIRE)
			manage_dir(inst, arg, fd);
		arg += 1;
		idx += 1;
	}
	return (inst->op.argc);
}

int			manage_filter(t_filter *elem, t_data *data, int fd)
{
	(void)data;
	if (elem->label == LX_INST)
		return (manage_inst(elem, data, fd));
	return (1);
}

void		fill_instruction(t_data *data, int fd)
{
	t_filter	*elem;
	int			idx;

	idx = 0;
	while (idx < data->f_size)
	{
		elem = &data->filter[idx];
		idx += manage_filter(elem, data, fd);
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
