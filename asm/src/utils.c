/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:09:15 by wta               #+#    #+#             */
/*   Updated: 2019/02/15 01:49:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
	return (count);
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

int		strcntchar(char *str, char c)
{
	int	count;
	int	idx;

	count = 0;
	idx = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] == c)
			count += 1;
		idx += 1;
	}
	return (count);
}

char	*expand_label(char *str, char c1, char c2)
{
	char	*new;
	int		idx;
	int		jdx;
	int		len;

	if ((len = strcntchar(str, c1)) == 0)
		return (str);
	len += ft_strlen(str);
	if ((new = ft_strnew(len)) == NULL)
		return (NULL);
	idx = 0;
	jdx = 0;
	while (idx < len)
	{
		new[idx] = str[jdx];
		if (str[jdx] == c1)
		{
			idx += 1;
			new[idx] = c2;
		}
		jdx += 1;
		idx += 1;
	}
	free(str);
	return (new);
}

char	*strjoin_add_c(char const *s1, char const *s2, char c)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = (s1 == NULL) ? 0 : ft_strlen(s1);
	s2_len = (s2 == NULL) ? 0 : ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(*str) * (s1_len + s2_len + 2))))
		return (NULL);
	if (s1_len > 0)
		ft_memcpy(str, s1, s1_len);
	str[s1_len] = c;
	if (s2_len > 0)
		ft_memcpy(str + s1_len + 1, s2, s2_len);
	str[s1_len + s2_len + 1] = '\0';
	return (str);
}
