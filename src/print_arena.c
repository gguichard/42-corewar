/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 20:05:46 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/15 21:31:54 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "champion.h"
#include "corewar.h"
#include <unistd.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

void	print_arena(unsigned char *str, int size)
{
	int fd = open("test.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	write(fd, str, size);
	close(fd);
	system("hexdump -v test.txt | cut -d ' ' -f 2- | sed '$d' && rm -f test.txt");
}
