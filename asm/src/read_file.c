/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:24:10 by wta               #+#    #+#             */
/*   Updated: 2019/02/18 07:32:59 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "asm.h"

t_error	get_post_header(int fd, char **line, char **inst)
{
	t_error	err_id;
	char	*tmp;
	int		ret;

	err_id = ERR_NOERROR;
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
	return (ret == -1 ? ERR_BADFMT : err_id);
}

t_error	split_input(char *inst, char ***split)
{
	t_error	err_id;

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
	inst = NULL;
	err_id = ERR_NOERROR;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	if (err_id == ERR_NOERROR)
		err_id = get_first_part(data, fd, &line);
	if (err_id == ERR_NOERROR)
		err_id = get_post_header(fd, &line, &inst);
	if (err_id == ERR_NOERROR)
		err_id = split_input(inst, &split);
	if (err_id == ERR_NOERROR)
		err_id = classify(data, split);
	ft_strtab_free(split);
	close(fd);
	return (err_id);
}
