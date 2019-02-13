/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:10 by wta               #+#    #+#             */
/*   Updated: 2019/02/13 08:11:16 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "asm.h"

t_error	manage_string(int idx, int fd, t_data *data)
{
	char	*needle;
	int		diff;
	int		ret;

	diff = BUFF_SIZE - idx;
	needle = ft_strchr(&data->buf[idx], '"');
	if ((needle == NULL && diff > PROG_NAME_LENGTH)
		|| (needle != NULL && (diff = needle - &data->buf[idx]) > PROG_NAME_LENGTH))
		return (ERR_NAME);
	else if (needle != NULL)
		ft_strncpy(data->name, &data->buf[idx], diff);
	else if (needle == NULL)
	{
		ft_strncat(data->name, &data->buf[idx], diff);
		if ((ret = read(fd, data->buf, BUFF_SIZE)) == -1)
			return (ERR_ERRNO);
		data->buf[ret] = '\0';
		if ((needle = ft_strchr(data->buf, '"')) == NULL)
			return (ERR_BADFMT);
		if ((diff + (needle - data->buf)) > PROG_NAME_LENGTH)
			return (ERR_NAME);
		ft_strncat(data->name, data->buf, needle - data->buf);
	}
	return (ERR_NOERROR);
}

t_error	get_name_string(int fd, t_data *data)
{
	t_error	err_id;
	int		ret;
	int		idx;

	err_id = ERR_NOERROR;
	if ((ret = read(fd, data->buf, BUFF_SIZE)) == -1)
		return (ERR_ERRNO);
	data->buf[ret] = '\0';
	idx = 0;
	while (idx < ret && err_id == ERR_NOERROR)
	{
		if (data->buf[idx] != '"' && data->buf[idx] != '\t'
				&& data->buf[idx] != ' ')
			err_id = ERR_BADFMT;
		else if (data->buf[idx] == '"')
			break ;
		idx += 1;
	}
	if (err_id == ERR_NOERROR && data->buf[idx] == '"')
		err_id = manage_string(idx + 1, fd, data);
	else
		err_id = ERR_BADFMT;
	return (err_id);
}

t_error	get_prog_name(int fd, t_data *data)
{
	t_error	err_id;
	char	buf[6];
	int		ret;

	err_id = ERR_NOERROR;
	if ((ret = read(fd, buf, 5)) == -1)
		return (ERR_ERRNO);
	else if (ret < 5)
		return (ERR_BADFMT);
	buf[ret] = '\0';
	if (ft_strequ(buf, ".name") == 0)
		return (ERR_BADFMT);
	err_id = get_name_string(fd, data);
	return (err_id);
}

t_error	read_file(char *file, t_data *data)
{
	t_error	err_id;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	err_id = get_prog_name(fd, data);
	close(fd);
	return (err_id);
}
