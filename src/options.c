/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 06:17:13 by gguichar          #+#    #+#             */
/*   Updated: 2019/02/20 06:27:07 by gguichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"
#include "corewar.h"

t_error	parse_opts(t_env *env, char **argv, int *cur_arg)
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
