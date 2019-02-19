/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/19 07:46:47 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "libft.h"
#include "champion.h"
#include "corewar.h"
#include "parsing.h"

static t_error		parse_opts(t_env *env, char **argv, int *cur_arg)
{
	long	dump_cycles;
	char	*endptr;

	*cur_arg = 1;
	if (ft_strequ("-dump", argv[*cur_arg]))
	{
		*cur_arg += 1;
		if (argv[*cur_arg] == NULL)
			return (ERR_WRONGDUMPOPT);
		dump_cycles = ft_strtol(argv[*cur_arg], &endptr, 10);
		if (*endptr != '\0' || dump_cycles < 0 || dump_cycles > INT_MAX)
			return (ERR_WRONGDUMPOPT);
		*cur_arg += 1;
		env->dump_cycles = (int)dump_cycles;
	}
	return (ERR_NOERROR);
}

static t_process	*create_process(t_env *env, t_champ *champ)
{
	t_process	process;
	t_list		*node;

	ft_memset(&process, 0, sizeof(t_process));
	node = ft_lstnew(&process, sizeof(t_process));
	if (node == NULL)
		return (NULL);
	((t_process *)node->content)->champ_id = champ->id;
	((t_process *)node->content)->reg[0] = champ->id;
	ft_lstadd(&env->process_lst, node);
	return ((t_process *)node->content);
}

static void			setup_champ(t_env *env, t_champ *champ, int pc)
{
	t_process	*process;

	ft_memcpy(&env->arena[pc], champ->prog, champ->header.prog_size);
	ft_printf("Champion \"%s\" (%d bytes) has been loaded\n"
			, champ->header.prog_name
			, champ->header.prog_size);
	process = create_process(env, champ);
	if (process != NULL)
		process->pc = pc;
	else
		ft_dprintf(2, "corewar: error: Unable to create process for \"%s\""
				, champ->header.prog_name);
}

static void			print_winner(t_env *env)
{
	int		last_cycle;
	t_list	*best_champ;
	t_list	*cur_champ;

	last_cycle = -1;
	best_champ = NULL;
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		if (last_cycle <= (int)((t_champ *)cur_champ->content)->live_cycle)
		{
			last_cycle = (int)((t_champ *)cur_champ->content)->live_cycle;
			best_champ = cur_champ;
		}
		cur_champ = cur_champ->next;
	}
	if (best_champ != NULL)
		ft_printf("Winner is %s\n"
				, ((t_champ *)best_champ->content)->header.prog_name);
}

static void			run_vm(t_env *env)
{
	size_t	idx;
	size_t	nb_champs;
	t_list	*cur_champ;

	idx = 0;
	nb_champs = ft_lstsize(env->champ_lst);
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		setup_champ(env, (t_champ *)cur_champ->content
				, (MEM_SIZE / nb_champs) * idx);
		cur_champ = cur_champ->next;
		idx++;
	}
	if (env->dump_cycles != 0)
		run_cycles_loop(env);
	print_winner(env);
}

int					main(int argc, char **argv)
{
	t_env	env;
	int		cur_arg;
	t_error	err_id;

	ft_memset(&env, 0, sizeof(t_env));
	env.debug = 1;
	env.cur_cycle = 1;
	env.cycle_to_die = CYCLE_TO_DIE;
	env.cycle_before_die = env.cycle_to_die;
	env.dump_cycles = -1;
	err_id = parse_opts(&env, argv, &cur_arg);
	if (err_id == ERR_NOERROR)
		err_id = create_champs(&env, argv, argc, cur_arg);
	if (err_id == ERR_NOERROR && env.champ_lst == NULL)
		err_id = ERR_NOCHAMPS;
	if (err_id != ERR_NOERROR)
	{
		if (err_id != ERR_CHAMPREAD)
			ft_printf("corewar: error: %s\n", str_to_error(err_id));
		ft_printf("USAGE: %s [options] <champions>\n", argv[0]);
		ft_printf("You can load at most %d champions\n\n", MAX_PLAYERS);
		ft_printf("OPTIONS:\n");
		ft_printf("  -dump <cycle>\tDumps memory at specified cycle then "
				"exits\n");
		return (1);
	}
	run_vm(&env);
	return (0);
}
