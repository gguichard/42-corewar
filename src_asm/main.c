/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 05:23:11 by wta               #+#    #+#             */
/*   Updated: 2019/02/13 07:50:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "asm.h"

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	ft_memset(&data, 0, sizeof(t_data));
	printf("%d\n", read_file(av[1], &data));
	printf("%s\n", data.name);
	return (0);
}
