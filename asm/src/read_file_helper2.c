/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 05:21:48 by wta               #+#    #+#             */
/*   Updated: 2019/02/18 05:26:52 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "asm.h"

t_error	fill_prog_name(t_data *data, int fd, char **str, char **line)
{
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (ft_strlen(*str) + 1 + ft_strlen(data->header.prog_name)
			> PROG_NAME_LENGTH)
		err_id = ERR_BADFMT;
	ft_strcat(data->header.prog_name, *str);
	ft_strcat(data->header.prog_name, "\n");
	free(*line);
	if (get_next_line(fd, line) <= 0)
		err_id = ERR_BADFMT;
	*str = *line;
	return (err_id);
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
	str = (str == NULL) ? *line : str;
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
	if (ft_strlen(*str) + 1 + ft_strlen(data->header.comment)
			> COMMENT_LENGTH)
		err_id = ERR_BADFMT;
	ft_strcat(data->header.comment, *str);
	ft_strcat(data->header.comment, "\n");
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
