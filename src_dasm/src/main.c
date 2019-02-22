/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 03:43:01 by wta               #+#    #+#             */
/*   Updated: 2019/02/22 07:43:15 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "op.h"
#include "dasm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0},
	{0, 0, {0, 0, 0}, 0, 0, 0, 0, 0}
};

int	rename_file(char *filename)
{
	int	len;
	int	idx;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	idx = len - 4;
	if (ft_strequ(&filename[idx], ".cor") == 0)
		return (0);
	ft_bzero(&filename[idx + 1], 3);
	filename[idx + 1] = 's';
	return (1);
}

int	get_name(t_data *data, char *filepath)
{
	char	*str;
	int		idx;
	int		len;

	if (filepath != NULL)
	{
		len = ft_strlen(filepath) - 1;
		idx = len;
		while (idx >= 0)
		{
			if (filepath[idx] == '/')
				break ;
			idx -= 1;
		}
		if (rename_file(&filepath[idx + 1]) == 0)
			return (0);
		str = (idx == -1) ? ft_strdup(filepath) : ft_strdup(&filepath[idx + 1]);
		if (str == NULL)
			return (0);
		data->filename = str;
		return (1);
	}
	return (0);
}

int	open_file(t_data *data, char *filepath)
{
	int	fd;

	if (access(filepath, F_OK) != 0)
		return (-1);
	if ((fd = open(filepath, O_RDONLY)) == -1)
		return (-1);
	if (get_name(data, filepath) == 0)
		return (-1);
	return (fd);
}

void	write_header(t_data *data, char *str, int idx, int len)
{
	char	*name;

	write(data->fd, str, ft_strlen(str));
	write(data->fd, "\"", 1);
	name = data->buf + idx;
	write(data->fd, name, len);
	write(data->fd, "\"\n", 2);
}

int	get_header(t_data *data, int fd)
{
	int	ret;

	ret = read(fd, data->buf, HEADER_SIZE);
	if (ret < HEADER_SIZE)
		return (0);
	data->buf[ret] = '\0';
	write_header(data, NAME_STR, 4, ft_strlen(data->buf + 4));
	write_header(data, COMMENT_STR, 140, ft_strlen(data->buf + 140));
	write(data->fd, "\n", 1);
	return (1);
}

uint8_t	*ft_memjoin(uint8_t *s1, uint8_t *s2, int s1_len, int s2_len)
{
	uint8_t	*new;
	int		total_len;
	int		idx;

	total_len = s1_len + s2_len;
	new = (uint8_t *)malloc(sizeof(uint8_t) * (total_len));
	if (new == NULL)
		return (NULL);
	idx = 0;
	total_len = (s1_len >= s2_len) ? s1_len : s2_len;
	while (idx < total_len)
	{
		if (idx < s1_len)
			new[idx] = s1[idx];
		if (idx < s2_len)
			new[s1_len + idx] = s2[idx];
		idx += 1;
	}
	return (new);
}

uint8_t	*ft_memdup(uint8_t *src, int len)
{
	uint8_t	*new;

	new = (uint8_t *)malloc(sizeof(uint8_t) * len);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, src, len);
	return (new);
}

void	get_inst(t_data *data, int fd)
{
	uint8_t	*tmp;
	int		ret;

	ft_bzero(data->buf, BUFF_SIZE + 1);
	while ((ret = read(fd, data->buf, BUFF_SIZE + 1)))
	{
		if (data->inst == NULL)
		{
			data->inst = ft_memdup((uint8_t*)data->buf, ret);
			data->inst_len = ret;
		}
		else
		{
			tmp = data->inst;
			data->inst = ft_memjoin(data->inst, (uint8_t*)data->buf, data->inst_len, ret);
			data->inst_len += ret;
			ft_memdel((void **)&tmp);
		}
		ft_bzero(data->buf, BUFF_SIZE + 1);
	}
}

t_op	find_op(uint8_t *byte)
{
	int	idx;

	idx = 0;
	while (idx < 16)
	{
		if (g_op_tab[idx].opcode == *byte)
			return (g_op_tab[idx]);
		idx += 1;
	}
	return (g_op_tab[idx]);
}

void	swap_bytes(uint8_t *str, int size)
{
	unsigned char	tmp;
	int				i;

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

int		write_indir(t_data *data, uint8_t *byte)
{
	int	nb;

	swap_bytes(byte, 2);
	nb = *((int16_t*)(byte));
	ft_putnbr_fd((int)nb, data->fd);
	return (2);
}

int		write_dire(t_data *data, uint8_t *byte, int direct)
{
	int	nb;

	swap_bytes(byte, (direct == 1) ? 2 : 4);
	nb = (direct == 1) ? *((int16_t*)byte) : *((int*)byte);
	write(data->fd, "%", 1);
	ft_putnbr_fd(nb, data->fd);
	return ((direct == 1) ? 2 : 4);
}

int		write_reg(t_data *data, uint8_t *byte)
{
	int	nb;

	nb = *((int8_t*)(byte));
	write(data->fd, "r", 1);
	ft_putnbr_fd(nb, data->fd);
	return (1);
}

int	manage_argv(t_data *data, t_op *op, uint8_t *byte)
{
	uint8_t	encoding;
	uint8_t	*ref;
	int		idx;

	idx = 0;
	ref = byte;
	if (op->encoding == 1)
	{
		encoding = *byte++;
		while (encoding > 0)
		{
			if ((encoding & 0xc0) == 0xc0)
				byte += write_indir(data, byte);
			else if ((encoding & 0x80) == 0x80)
				byte += write_dire(data, byte, op->direct);
			else if ((encoding & 0x40) == 0x40)
				byte += write_reg(data, byte);
			encoding <<= 2;
			if (encoding > 0)
				write(data->fd, ", ", 2);
		}
	}
	else
		byte += write_dire(data, byte, op->direct);
	write(data->fd, "\n", 1);
	return (byte - ref);
}

int		inst_manager(t_data *data, uint8_t *byte)
{
	t_op	op;

	op = find_op(byte);
	if (op.opcode == 0)
		return (0);
	write(data->fd, op.name, ft_strlen(op.name));
	write(data->fd, " ", 1);
	byte += 1;
	return (manage_argv(data, &op, byte) + 1);
}

int		write_inst(t_data *data)
{
	int	idx;
	int	ret;

	idx = 0;
	ret = 0;
	while (idx < data->inst_len)
	{
		if ((ret = inst_manager(data, &data->inst[idx])) == 0)
			return (0);
		idx += ret;
	}
	return (1);
}

int	deassemble(t_data *data, int fd)
{
	get_header(data, fd);
	get_inst(data, fd);
	close(fd);
	write_inst(data);
	free(data->inst);
	close(data->fd);
	return (1);
}

int	create_newfile(t_data *data)
{
	data->fd = open(data->filename, O_TRUNC | O_RDWR | O_CREAT, 0644);
	ft_strdel(&data->filename);
	if (data->fd == -1)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac == 2)
	{
		ft_memset(&data, 0, sizeof(t_data));
		fd = open_file(&data, av[1]);
		create_newfile(&data);
		deassemble(&data, fd);
	}
	return (0);
}
