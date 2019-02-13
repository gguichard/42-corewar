/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/13 22:55:10 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "op.h"
#include "corewar.h"
#include "parsing.h"

static int	parse_opts(t_env *env, char **argv)
{
	int		cur_arg;
	long	dump_cycles;
	char	*endptr;

	cur_arg = 1;
	if (ft_strequ("-dump", argv[cur_arg]))
	{
		if (argv[cur_arg + 1] == NULL
				|| !(dump_cycles = ft_strtol(argv[cur_arg + 1], &endptr, 10))
				|| dump_cycles < 0 || dump_cycles > INT_MAX
				|| *endptr != '\0')
		{
			ft_dprintf(2, "corewar: error: dump cycles should be an integer "
					"between 0 and %d\n", INT_MAX);
			return (-1);
		}
		cur_arg += 2;
		env->dump_cycles = (int)dump_cycles;
	}
	return (cur_arg);
}

static int	get_next_champ_id(t_env *env)
{
	unsigned int	id;
	t_list			*cur_process;

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
		(*cur_arg)++;
		if (argv[*cur_arg] == NULL)
		{
			ft_dprintf(2, "corewar: error: Please specify champ number when "
					"using -n option\n");
			return (-1);
		}
		id = ft_strtol(argv[*cur_arg], &endptr, 10);
		if (*endptr != '\0' || id < 0 || id > INT_MAX)
		{
			ft_dprintf(2, "corewar: error: Champ number should be an integer "
					"between 0 and %d\n", INT_MAX);
			return (-1);
		}
		(*cur_arg)++;
	}
	return (id);
}

static int	add_champ_to_lst(t_env *env, t_champ champ)
{
	t_list	*node;

	node = ft_lstnew(&champ, sizeof(t_champ));
	if (node == NULL)
		return (0);
	ft_lstpush(&env->champ_lst, node);
	return (1);
}

static int	create_def_process(t_env *env, char **argv, int argc, int cur_arg)
{
	int			id;
	t_champ		champ;
	t_process	process;
	t_list		*node;

	ft_memset(&process, 0, sizeof(t_process));
	while (cur_arg < argc)
	{
		if ((id = get_champ_id(env, argv, &cur_arg)) < 0)
			return (0);
		else if (argv[cur_arg] == NULL || !read_file(argv[cur_arg], &champ))
		{
			if (argv[cur_arg] == NULL)
				ft_dprintf(2, "corewar: error: Missing champion file\n");
			return (0);
		}
		node = ft_lstnew(&process, sizeof(t_process));
		if (node == NULL || !add_champ_to_lst(env, champ))
		{
			free(node);
			ft_dprintf(2, "corewar: error: Unexpected error\n");
			return (0);
		}
		((t_process *)node->content)->champ_id = id;
		ft_lstadd(&env->process_lst, node);
		cur_arg++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		cur_arg;
	t_list	*cur_champ;

	ft_memset(&env, 0, sizeof(t_env));
	env.cycle_to_die = CYCLE_TO_DIE;
	env.cycle_before_die = env.cycle_to_die;
	env.dump_cycles = -1;
	if ((cur_arg = parse_opts(&env, argv)) != -1
			&& create_def_process(&env, argv, argc, cur_arg))
	{
		cur_champ = env.champ_lst;
		while (cur_champ != NULL)
		{
			ft_printf("Champion \"%s\" (%d bytes) has been loaded\n"
					, ((t_champ *)cur_champ->content)->header.prog_name
					, ((t_champ *)cur_champ->content)->header.prog_size);
			cur_champ = cur_champ->next;
		}
		return (0);
	}
	return (1);
}
