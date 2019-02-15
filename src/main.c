/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/15 21:23:22 by gguichar         ###   ########.fr       */
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
	ft_memcpy(((t_process *)node->content)->reg[0], &champ->id, REG_SIZE);
	ft_lstadd(&env->process_lst, node);
	return ((t_process *)node->content);
}

static void			run_vm(t_env *env)
{
	t_list		*cur_champ;
	size_t		nb_champs;
	size_t		idx;
	int			pc;
	t_process	*process;

	idx = 0;
	nb_champs = ft_lstsize(env->champ_lst);
	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		pc = (MEM_SIZE / nb_champs) * idx;
		ft_memcpy(&env->arena[pc]
				, ((t_champ *)cur_champ->content)->prog
				, ((t_champ *)cur_champ->content)->header.prog_size);
		ft_printf("Champion \"%s\" (%d bytes) has been loaded\n"
				, ((t_champ *)cur_champ->content)->header.prog_name
				, ((t_champ *)cur_champ->content)->header.prog_size);
		process = create_process(env, (t_champ *)cur_champ->content);
		if (process != NULL)
			process->pc = pc;
		else
			ft_dprintf(2, "corewar: error: Unable to create process for \"%s\""
					, ((t_champ *)cur_champ->content)->header.prog_name);
		cur_champ = cur_champ->next;
		idx++;
	}
	run_cycles_loop(env);
}

int					main(int argc, char **argv)
{
	t_env	env;
	int		cur_arg;
	t_error	err_id;

	ft_memset(&env, 0, sizeof(t_env));
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
		return (1);
	}
	run_vm(&env);
	return (0);
}
