/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:15:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/18 23:40:52 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "parsing.h"
#include "process.h"
#include "corewar.h"

static int	get_next_champ_id(t_env *env)
{
	int		id;
	t_list	*cur_process;

	id = 0;
	cur_process = env->process_lst;
	while (cur_process != NULL)
	{
		if (id == ((t_process *)cur_process)->champ_id)
		{
			id++;
			cur_process = env->process_lst;
			continue ;
		}
		cur_process = cur_process->next;
	}
	return (id);
}

static int	get_champ_id(t_env *env, char **argv, int *cur_arg)
{
	int		id;
	char	*endptr;

	if (!ft_strequ("-n", argv[*cur_arg]))
		id = get_next_champ_id(env);
	else
	{
		*cur_arg += 1;
		if (argv[*cur_arg] == NULL)
			return (-5);
		id = ft_strtol(argv[*cur_arg], &endptr, 10);
		if (*endptr != '\0' || id < INT_MIN || id > INT_MAX)
			return (-5);
		*cur_arg += 1;
	}
	return (id);
}

t_error		create_champs(t_env *env, char **argv, int argc, int cur_arg)
{
	int		id;
	t_champ	champ;
	t_list	*node;

	while (cur_arg < argc)
	{
		if ((id = get_champ_id(env, argv, &cur_arg)) < -4)
			return (ERR_WRONGNOPT);
		else if (argv[cur_arg] == NULL)
			return (ERR_NOCHAMPNAME);
		else if (!read_file(argv[cur_arg], &champ))
			return (ERR_CHAMPREAD);
		node = ft_lstnew(&champ, sizeof(t_champ));
		if (node == NULL)
			return (ERR_UNEXPECTED);
		((t_champ *)node->content)->id = id;
		ft_lstpush(&env->champ_lst, node);
		cur_arg++;
	}
	return (ERR_NOERROR);
}
