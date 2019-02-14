/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifonne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 00:39:37 by vifonne           #+#    #+#             */
/*   Updated: 2019/02/14 06:00:58 by vifonne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "process.h"
#include "corewar.h"
#include "champion.h"

/*t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};*/

static unsigned char	*inst_loop(t_env *env, int size, unsigned char *str)
{
	unsigned char	*ret;
	int				offset;

	if (!(ret = (unsigned char *)ft_memalloc(sizeof(unsigned char) * size)))
		return (NULL);
	offset = size - ((env->arena + MEM_SIZE) - str);
	if (offset > 0)
	{
		ft_memmove(ret, str, (env->arena + MEM_SIZE) - str);
		ft_memmove((ret + ((env->arena + MEM_SIZE) - str)), env->arena, offset);
	}
	else
		ft_memmove(ret, str, size);
	return (ret);
}

void	live(t_env *env, t_process *cur_process, unsigned char *str)
{
	unsigned char	*tmp;
	unsigned int	champ_id;
	t_list			*champ;

	tmp = inst_loop(env, 5, str);
	champ_id = *((int *)(str + 1));
	printf("champ_id = %d\n", champ_id);
	champ = env->champ_lst;
	while (champ)
	{
		if (champ_id == ((t_champ *)champ->content)->id)
		{
			printf("champ_id match\n");
			((t_champ *)champ->content)->live_cycle = env->cur_cycle;
			break ;
		}
		champ = champ->next;
	}
	//cur_process->lives += 1;
	(void)cur_process;
}

/*void	ld(void)
{
	ft_printf("ld\n");
}
void	st(void)
{
	ft_printf("st\n");
}

void	add(void)
{
	ft_printf("add\n");
}

void	sub(void)
{
	ft_printf("sub\n");
}

void	ft_and(void)
{
	ft_printf("and\n");
}

void	ft_or(void)
{
	ft_printf("or\n");
}

void	ft_xor(void)
{
	ft_printf("xor\n");
}

void	zjump(void)
{
	ft_printf("zjump\n");
}

void	ldi(void)
{
	ft_printf("ldi\n");
}

void	sti(void)
{
	ft_printf("sti\n");
}

void	ft_fork(void)
{
	ft_printf("fork\n");
}

void	lld(void)
{
	ft_printf("lld\n");
}

void	lldi(void)
{
	ft_printf("lldi\n");
}

void	lfork(void)
{
	ft_printf("lfork\n");
}

void	aff(void)
{
	ft_printf("aff\n");
}*/
