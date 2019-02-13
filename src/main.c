/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 04:35:03 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/13 08:07:53 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (0);
		}
		cur_arg += 2;
		env->dump_cycles = (int)dump_cycles;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;
	t_champ	*champ;

	(void)argc;
	champ = malloc(sizeof(t_champ));
	ft_memset(&env, 0, sizeof(t_env));
	env.cycle_to_die = CYCLE_TO_DIE;
	env.cycle_before_die = env.cycle_to_die;
	env.dump_cycles = -1;
	if (parse_opts(&env, argv))
	{
		read_file(argv[1], champ);
		return (0);
	}
	return (1);
}
