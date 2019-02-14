/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:09:15 by wta               #+#    #+#             */
/*   Updated: 2019/02/14 22:07:48 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delim_str(char *str, char *delim)
{
	int	idx;
	int	jdx;

	idx = 0;
	while (str[idx] != '\0')
	{
		jdx = 0;
		while (delim[jdx] != '\0')
		{
			if (str[idx] == delim[jdx])
			{
				str[idx] = '\0';
				break ;
			}
			jdx += 1;
		}
		idx += 1;
	}
}

int		count_words(char *str, int len)
{
	int		idx;
	int		in_wd;
	int		count;

	idx = 0;
	in_wd = 0;
	count = 0;
	while (idx < len)
	{
		if (str[idx] != '\0' && in_wd == 0)
		{
			in_wd = 1;
			count += 1;
		}
		else if (str[idx] == '\0' && in_wd == 1)
			in_wd = 0;
		idx += 1;
	}
	return (idx);
}

int		dup_in_split(char *str, char **split, int len)
{
	int	idx;
	int	jdx;
	int	in_wd;

	idx = 0;
	jdx = 0;
	in_wd = 0;
	while (idx < len)
	{
		if (str[idx] != '\0' && in_wd == 0)
		{
			in_wd = 1;
			if ((split[jdx] = ft_strdup(&str[idx])) == NULL)
				return (0);
			jdx += 1;
		}
		else if (str[idx] == '\0' && in_wd == 1)
			in_wd = 0;
		idx += 1;
	}
	return (1);
}

char	**split_by_str(char *str, char *delim)
{
	char	**split;
	int		nb_wd;
	int		len;

	len = ft_strlen(str);
	delim_str(str, delim);
	nb_wd = count_words(str, len);
	if ((split = (char **)malloc((nb_wd + 1) * sizeof(char *))) == NULL)
		return (NULL);
	split[nb_wd] = NULL;
	if ((dup_in_split(str, split, len)) == 0)
		return (ft_strtab_free(split));
	return (split);
}
