/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 05:30:48 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include "champion.h"
#include "parsing.h"
#include "visual.h"

static void	show_help(char **argv)
{
	ft_printf("USAGE: %s [options] <champions>\n", argv[0]);
	ft_printf("You can load at most %d champions\n\n", MAX_PLAYERS);
	ft_printf("OPTIONS:\n");
	ft_printf("  -dump <cycle>\tDumps memory at specified cycle then "
			"exits\n");
}

/*static void	debug_mode_welcome(t_env *env)
{
	if (env->debug == DEBUG_ON)
	{
		ft_printf("Welcome into Debug mode v1.0 :\n");
		ft_printf("3 levels are available :\n");
		ft_printf("\t- 1 : Display only instructions\n");
		ft_printf("\t- 2 : Display instructions with their parameters\n");
		ft_printf("\t- 3 : Same as 2 but with amount of bytes that each PC increase.\n");
	}
}*/

static void	run_vm(t_env *env)
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
	print_winner_champ(env);
}

int			main(int argc, char **argv)
{
	t_env	env;
	int		cur_arg;
	t_error	err_id;

	ft_memset(&env, 0, sizeof(t_env));
	env.visu = 1;
	env.cur_cycle = 1;
	env.cycle_to_die = CYCLE_TO_DIE;
	env.cycle_before_die = env.cycle_to_die;
	env.dump_cycles = -1;
	env.debug = 0;
	err_id = parse_opts(&env, argv, &cur_arg);
	if (err_id == ERR_NOERROR)
		err_id = create_champs(&env, argv, argc, cur_arg);
	if (err_id == ERR_NOERROR && env.champ_lst == NULL)
		err_id = ERR_NOCHAMPS;
	if (err_id != ERR_NOERROR)
	{
		if (err_id != ERR_CHAMPREAD)
			ft_printf("corewar: error: %s\n", str_to_error(err_id));
		show_help(argv);
		return (1);
	}
	if (env.visu == VISU_ON)
		init_screen(&env);
	run_vm(&env);
	if (env.visu == VISU_ON)
		loop_screen();
	return (0);
}
