/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/14 02:05:51 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "champion.h"
#include "corewar.h"

static t_error	parse_opts(t_env *env, char **argv, int *cur_arg)
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

static void		run_vm(t_env *env)
{
	t_list	*cur_champ;

	cur_champ = env->champ_lst;
	while (cur_champ != NULL)
	{
		ft_printf("Champion \"%s\" (%d bytes) has been loaded\n"
				, ((t_champ *)cur_champ->content)->header.prog_name
				, ((t_champ *)cur_champ->content)->header.prog_size);
		cur_champ = cur_champ->next;
	}
	run_cycles_loop(env);
}

int				main(int argc, char **argv)
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
		err_id = create_def_process(&env, argv, argc, cur_arg);
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
