/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:10 by wta               #+#    #+#             */
/*   Updated: 2019/02/15 01:10:56 by wta              ###   ########.fr       */
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

	if ((ret = read(fd, buf, 1)) == -1)
		return (ERR_ERRNO);
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
		str = skip_tab_n_space(*line);
		if (str[0] != '#' || str[0] != '\0')
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

void	set_op_tab(t_op op_tab[])
{
	op_tab[0] = (t_op){"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0};
	op_tab[1] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0};
	op_tab[2] = (t_op){"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0};
	op_tab[3] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1
		, 0};
	op_tab[4] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"
		, 1, 0};
	op_tab[5] = (t_op){"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR
		, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	op_tab[6] = (t_op){"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR
		, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	op_tab[7] = (t_op){"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR
		, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	op_tab[8] = (t_op){"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1};
	op_tab[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
		, 10, 25, "load index", 1, 1};
	op_tab[10] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
		, 11, 25, "store index", 1, 1};
	op_tab[11] = (t_op){"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1};
	op_tab[12] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10
		, "long load", 1, 0};
	op_tab[13] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
		, 14, 50, "long load index", 1, 1};
	op_tab[14] = (t_op){"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1};
	op_tab[15] = (t_op){"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0};
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
		if (*inst == NULL)
		{
			if ((*inst = ft_strdup(*line)) == NULL)
				err_id = ERR_MALLOC;
		}
		else
		{
			tmp = *inst;
			if ((*inst = ft_strjoin(*inst, *line)) == NULL)
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
	(void)data;
	if ((inst = expand_label(inst, ':', ' ')) == NULL)
		return (ERR_MALLOC);
	if ((*split = split_by_str(inst, " \t,")) == NULL)
		return (ERR_MALLOC);
	return (ERR_NOERROR);
}

t_error	read_file(char *file, t_data *data)
{
	t_error	err_id;
	char	**split;
	char	*line;
	char	*inst;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	err_id = check_first_line(fd);
	if (err_id == ERR_NOERROR)
	{
		if ((err_id = skip_useless(fd, &line)) != ERR_NOERROR)
			return (err_id);
		if ((err_id = get_name(data, fd, &line)) != ERR_NOERROR)
			return (err_id);
		if ((err_id = skip_useless(fd, &line)) != ERR_NOERROR)
			return (err_id);
		if ((err_id = get_comment(data, fd, &line)) != ERR_NOERROR)
			return (err_id);
		err_id = get_post_header(fd, &line, &inst);
		err_id = split_input(data, inst, &split);
	}
	close(fd);
	return (err_id);
}
