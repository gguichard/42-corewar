/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:10 by wta               #+#    #+#             */
/*   Updated: 2019/02/16 23:38:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "asm.h"

t_error	check_first_line(int fd)
{
	char	buf[1];
	int		ret;

	if ((ret = read(fd, buf, 1)) < 1)
		return ((ret == -1) ? ERR_ERRNO : ERR_BADFMT);
	if (buf[0] != '\n' && buf[0] != '\t' && buf[0] != '#' && buf[0] != '.')
		return (ERR_BADFMT);
	if ((ret = lseek(fd, 0, SEEK_SET)) == -1)
		return (ERR_ERRNO);
	return (ERR_NOERROR);
}

char	*skip_tab_n_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] == '\0')
		return (NULL);
	return (&str[i]);
}

t_error	skip_useless(int fd, char **line)
{
	char	*str;
	int		ret;

	while ((ret = get_next_line(fd, line)) > 0)
	{
		if (((str = skip_tab_n_space(*line)) != NULL)
				&& (str[0] != '#' && str[0] != '\0'))
			break ;
		free(*line);
	}
	if (ret <= 0)
		return (ERR_BADFMT);
	return (ERR_NOERROR);
}

char	*get_dquote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] == '\0' && str[i] != '"')
		return (NULL);
	return (&str[i + 1]);
}

t_error	fill_prog_name(t_data *data, int fd, char **str, char **line)
{
	t_error	err_id;

	if (ft_strlen(*str) + ft_strlen(data->header.prog_name)
			> PROG_NAME_LENGTH)
		err_id = ERR_BADFMT;
	ft_strcat(*str, data->header.prog_name);
	free(*line);
	if (get_next_line(fd, line) <= 0)
		err_id = ERR_BADFMT;
	*str = *line;
	return (err_id);
}

t_error	check_endline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			i += 1;
		else
			break ;
	}
	if (str[i] != '#' && str[i] != '\0')
		return (ERR_BADFMT);
	return (ERR_NOERROR);
}

t_error	get_name(t_data *data, int fd, char **line)
{
	t_error	err_id;
	char	*needle;
	char	*str;

	err_id = ERR_NOERROR;
	if ((str = skip_tab_n_space(*line)) == NULL)
		return (ERR_BADFMT);
	if ((ft_strnequ(str, NAME_CMD_STRING, 5) == 0)
			|| ((str = get_dquote((str) + 5)) == NULL))
		err_id = ERR_BADFMT;
	while (err_id == ERR_NOERROR && (needle = ft_strchr(str, '"')) == NULL)
		err_id = fill_prog_name(data, fd, &str, line);
	if (err_id == ERR_NOERROR
			&& (ft_strlen(data->header.prog_name)
				+ (needle - str) > PROG_NAME_LENGTH))
		err_id = ERR_NAME;
	else
		ft_strncat(data->header.prog_name, str, needle - str);
	if (needle != NULL)
		err_id = check_endline(needle + 1);
	free(*line);
	return (err_id);
}

t_error	fill_comment(t_data *data, int fd, char **str, char **line)
{
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (ft_strlen(*str) + ft_strlen(data->header.comment)
			> COMMENT_LENGTH)
		err_id = ERR_BADFMT;
	ft_strcat(*str, data->header.comment);
	free(*line);
	if (get_next_line(fd, line) <= 0)
		err_id = ERR_BADFMT;
	*str = *line;
	return (err_id);
}

t_error	get_comment(t_data *data, int fd, char **line)
{
	t_error	err_id;
	char	*needle;
	char	*str;

	err_id = ERR_NOERROR;
	if ((str = skip_tab_n_space(*line)) == NULL)
		return (ERR_BADFMT);
	if ((ft_strnequ(*line, COMMENT_CMD_STRING, 8) == 0)
			|| ((str = get_dquote((*line) + 8)) == NULL))
		err_id = ERR_BADFMT;
	while (err_id == ERR_NOERROR && (needle = ft_strchr(str, '"')) == NULL)
		err_id = fill_comment(data, fd, &str, line);
	str = (str == NULL) ? *line : str;
	if (err_id == ERR_NOERROR && (ft_strlen(data->header.comment)
				+ (needle - str) > COMMENT_LENGTH))
		err_id = ERR_NAME;
	else
		ft_strncat(data->header.comment, str, needle - str);
	if (needle != NULL)
		err_id = check_endline(needle + 1);
	free(*line);
	return (err_id);
}

t_error	get_post_header(int fd, char **line, char **inst)
{
	t_error	err_id;
	char	*tmp;
	int		ret;

	err_id = ERR_NOERROR;
	*line = NULL;
	*inst = NULL;
	while ((ret = get_next_line(fd, line)) > 0)
	{
		if ((tmp = ft_strchr(*line, '#')) != NULL 
				|| (tmp = ft_strchr(*line, ';')) != NULL)
			*tmp = '\0';
		if (*inst == NULL)
		{
			if ((*inst = ft_strdup(*line)) == NULL)
				err_id = ERR_MALLOC;
		}
		else
		{
			tmp = *inst;
			if ((*inst = strjoin_add_c(*inst, *line, ' ')) == NULL)
				err_id = ERR_MALLOC;
			free(tmp);
		}
		free(*line);
	}
	if (ret == -1)
		err_id = ERR_BADFMT;
	return (err_id);
}

t_error	split_input(t_data *data, char *inst, char ***split)
{
	t_error	err_id;
	(void)data;
	err_id = ERR_NOERROR;
	if ((inst = expand_label(inst)) == NULL)
		err_id = ERR_MALLOC;
	if (err_id == ERR_NOERROR
			&& (*split = split_by_str(inst, " \t,")) == NULL)
		err_id = ERR_MALLOC;
	free(inst);
	return (err_id);
}

t_error	get_first_part(t_data *data, int fd, char **line)
{
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (err_id == ERR_NOERROR)
		err_id = check_first_line(fd);
	if (err_id == ERR_NOERROR)
		err_id = skip_useless(fd, line);
	if (err_id == ERR_NOERROR)
		err_id = get_name(data, fd, line);
	if (err_id == ERR_NOERROR)
		err_id = skip_useless(fd, line);
	if (err_id == ERR_NOERROR)
		return (get_comment(data, fd, line));
	return (err_id);
}

t_error	read_file(char *file, t_data *data)
{
	t_error	err_id;
	char	**split;
	char	*line;
	char	*inst;
	int		fd;

	split = NULL;
	err_id = ERR_NOERROR;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	if (err_id == ERR_NOERROR)
		err_id = get_first_part(data, fd, &line);
	if (err_id == ERR_NOERROR)
		err_id = get_post_header(fd, &line, &inst);
	if (err_id == ERR_NOERROR)
		err_id = split_input(data, inst, &split);
	if (err_id == ERR_NOERROR)
		err_id = classify(data, split);
	ft_strtab_free(split);
	for (int i = 0; i < data->f_size; i++)
		ft_printf("%s\tlabel= %d\n", data->filter[i].op.name, data->filter[i].label);
	close(fd);
	return (err_id);
}
