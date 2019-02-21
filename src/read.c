/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:23:27 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/21 07:32:04 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "champion.h"
#include "parsing.h"
#include "func_op.h"

static int	read_magic(int fd, t_champ *champ)
{
	int		ret;
	char	buf[4];
	char	magic[4];

	magic[0] = 0x00;
	magic[1] = 0xEA;
	magic[2] = 0x83;
	magic[3] = 0xF3;
	ret = read(fd, buf, 4);
	if (ret != 4 || *((int *)buf) != *((int *)magic))
	{
		ft_dprintf(2, "corewar: error: No magic number\n");
		return (0);
	}
	champ->header.magic = 0x00EA83F3;
	return (1);
}

static int	read_name(int fd, t_champ *champ)
{
	int		ret;
	char	buf[PROG_NAME_LENGTH];

	ret = read(fd, buf, PROG_NAME_LENGTH);
	if (ret != PROG_NAME_LENGTH)
	{
		ft_dprintf(2, "corewar: error: Bad name\n");
		return (0);
	}
	ft_memcpy(champ->header.prog_name, buf, PROG_NAME_LENGTH);
	champ->header.prog_name[ret] = '\0';
	if (lseek(fd, 4, SEEK_CUR) < 0 || (ret = read(fd, buf, 4)) != 4)
	{
		ft_dprintf(2, "corewar: error: Bad champ size\n");
		return (0);
	}
	swap_bytes((uint8_t *)buf, 4);
	champ->header.prog_size = *((unsigned int *)buf);
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
	{
		ft_dprintf(2, "corewar: error: Champ size %u is too long\n"
				, champ->header.prog_size);
		return (0);
	}
	return (1);
}

static int	read_comment(int fd, t_champ *champ)
{
	int		ret;
	char	buf[COMMENT_LENGTH];

	ret = read(fd, buf, COMMENT_LENGTH);
	if (ret != COMMENT_LENGTH)
	{
		ft_dprintf(2, "corewar: error: Bad comment\n");
		return (0);
	}
	ft_memcpy(champ->header.comment, buf, COMMENT_LENGTH);
	champ->header.comment[ret] = '\0';
	if (lseek(fd, 4, SEEK_CUR) < 0)
	{
		ft_dprintf(2, "corewar: error: %s\n", strerror(errno));
		return (0);
	}
	return (1);
}

static int	read_prog(int fd, t_champ *champ)
{
	int				ret;
	unsigned char	buf[CHAMP_MAX_SIZE];

	ret = read(fd, buf, champ->header.prog_size + 1);
	if (ret != (int)champ->header.prog_size)
	{
		ft_dprintf(2, "corewar: error: Bad champ code reading\n");
		return (0);
	}
	ft_memcpy(champ->prog, buf, ret);
	return (1);
}

int			read_file(char *fn, t_champ *champ)
{
	int		fd;
	int		ret;

	fd = open(fn, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "corewar: error: %s\n", strerror(errno));
		return (0);
	}
	ret = 1;
	if (!read_magic(fd, champ)
			|| !read_name(fd, champ)
			|| !read_comment(fd, champ)
			|| !read_prog(fd, champ))
		ret = 0;
	close(fd);
	return (ret);
}
