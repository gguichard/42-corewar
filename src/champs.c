/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 01:15:16 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/21 03:07:53 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "corewar.h"
#include "parsing.h"
#include "champion.h"
#include "process.h"
#include "visual.h"

static int	get_next_champ_id(t_env *env)
{
	int		id;
	t_list	*cur_champ;

	id = -1;
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (id == ((t_champ *)cur_champ->content)->id)
		{
			id--;
			cur_champ = env->champ_lst;
			continue ;
		}
		cur_champ = cur_champ->next;
	}
	return (id);
}

static int	set_champ_id(t_env *env, char **argv, int *cur_arg, int *id)
{
	long	parsed_id;
	char	*endptr;

	if (!ft_strequ("-n", argv[*cur_arg]))
		*id = get_next_champ_id(env);
	else
	{
		*cur_arg += 1;
		if (argv[*cur_arg] == NULL)
			return (0);
		parsed_id = ft_strtol(argv[*cur_arg], &endptr, 10);
		if (*endptr != '\0' || parsed_id < INT_MIN || parsed_id > INT_MAX)
			return (0);
		*id = parsed_id;
		*cur_arg += 1;
	}
	return (1);
}

t_error		create_champs(t_env *env, char **argv, int argc, int cur_arg)
{
	int		id;
	t_champ	champ;
	t_list	*node;
	int		total;

	ft_memset(&champ, 0, sizeof(t_champ));
	total = 0;
	while (cur_arg < argc)
	{
		if (total > MAX_PLAYERS)
			return (ERR_TOOMANYCHAMPS);
		else if (!set_champ_id(env, argv, &cur_arg, &id))
			return (ERR_WRONGNOPT);
		else if (argv[cur_arg] == NULL)
			return (ERR_NOCHAMPNAME);
		else if (!read_file(argv[cur_arg], &champ))
			return (ERR_CHAMPREAD);
		node = ft_lstnew(&champ, sizeof(t_champ));
		if (node == NULL)
			return (ERR_UNEXPECTED);
		((t_champ *)node->content)->id = id;
		g_data.champ[total] = id;
		ft_lstpush(&env->champ_lst, node);
		cur_arg++;
		total++;
	}
	return (ERR_NOERROR);
}

void		setup_champ(t_env *env, t_champ *champ, int pc)
{
	t_process	*process;

	ft_memcpy(&env->arena[pc], champ->prog, champ->header.prog_size);
	if (env->visu != VISU_ON)
		ft_printf("Champion \"%s\" (%d bytes) has been loaded\n"
				, champ->header.prog_name
				, champ->header.prog_size);
	process = create_process(env, champ);
	if (process != NULL)
		process->pc = pc;
	else
	{
		if (env->visu != VISU_ON)
			ft_dprintf(2, "corewar: error: Unable to create process for \"%s\""
					, champ->header.prog_name);
	}
}

void		print_winner_champ(t_env *env)
{
	int		best_cycle;
	t_list	*best_champ;
	t_list	*cur_champ;

	best_cycle = -1;
	best_champ = NULL;
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (best_cycle <= ((t_champ *)cur_champ->content)->live_cycle)
		{
			best_cycle = ((t_champ *)cur_champ->content)->live_cycle;
			best_champ = cur_champ;
		}
		cur_champ = cur_champ->next;
	}
	if (best_champ != NULL)
	{
		if (env->visu != VISU_ON)
			ft_printf("Le joueur %d \"%s\" a gagne\n"
					, ((t_champ *)best_champ->content)->id
					, ((t_champ *)best_champ->content)->header.prog_name);
	}
}