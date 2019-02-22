/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 06:17:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/22 05:19:17 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "corewar.h"

static char		*get_optarg(const char *opt, char **argv, int *cur_arg)
{
	size_t	len;

	len = ft_strlen(opt);
	if (argv[*cur_arg][len] != '\0')
		return (argv[*cur_arg] + len);
	*cur_arg += 1;
	return (argv[*cur_arg]);
}

static t_error	parse_dump_opt(t_env *env, const char *optarg)
{
	long	dump_cycles;
	char	*endptr;

	if (optarg == NULL)
		return (ERR_WRONGDUMPOPT);
	dump_cycles = ft_strtol(optarg, &endptr, 10);
	if (*endptr != '\0' || dump_cycles < 0 || dump_cycles > INT_MAX)
		return (ERR_WRONGDUMPOPT);
	env->dump_cycles = (int)dump_cycles;
	return (ERR_NOERROR);
}

static t_error	parse_verbose_opt(t_env *env, const char *optarg)
{
	long	value;
	char	*endptr;

	if (optarg == NULL)
		env->debug_lvl = DEBUG_FIRST_LVL;
	else
	{
		value = ft_strtol(optarg, &endptr, 10);
		if (value != DEBUG_FIRST_LVL
				&& value != DEBUG_SECOND_LVL
				&& value != DEBUG_THIRD_LVL)
			return (ERR_WRONGVOPT);
		env->debug_lvl = value;
	}
	return (ERR_NOERROR);
}

t_error			parse_opt(t_env *env, t_opt *opts, char **argv, int *cur_arg)
{
	const char	*opt;
	int			idx;

	opt = argv[*cur_arg];
	idx = 0;
	while (opts[idx].name != NULL)
	{
		if (ft_strstr(opt, opts[idx].name) == opt)
			return (opts[idx].fn(env
						, get_optarg(opts[idx].name, argv, cur_arg)));
		idx++;
	}
	return (ERR_WRONGOPT);
}

t_error			parse_opts(t_env *env, char **argv, int *cur_arg)
{
	static t_opt	opts[] = {
		{"-dump", parse_dump_opt},
		{"-v", parse_verbose_opt},
		{NULL, NULL}
	};
	t_error			err_id;

	*cur_arg = 1;
	while (argv[*cur_arg] != NULL && argv[*cur_arg][0] == '-')
	{
		if (ft_strequ("--", argv[*cur_arg]))
		{
			*cur_arg += 1;
			break ;
		}
		err_id = parse_opt(env, opts, argv, cur_arg);
		if (err_id != ERR_NOERROR)
			return (err_id);
		*cur_arg += 1;
	}
	return (ERR_NOERROR);
}
