/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:23:11 by wta               #+#    #+#             */
/*   Updated: 2019/02/15 04:04:27 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "asm.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	set_op_tab(data.op_tab);
	printf("err %d\n", read_file(av[1], &data));
	free(data.filter);
	//TODO free NAME dans data->filter
//	printf("%s\n", data.header.prog_name);
//	printf("%s\n", data.header.comment);
//	printf("%d\n", create_cor(&data, av[1]));
	return (0);
}
