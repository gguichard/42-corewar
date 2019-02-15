/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 20:09:15 by wta               #+#    #+#             */
/*   Updated: 2019/02/15 03:32:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
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

int		cnt_space_to_add(char *str)
{
	int	count;
	int	idx;
	int	jdx;

	count = 0;
	idx = -1;
	while (str[++idx] != '\0')
	{
		jdx = -1;
		if ((str[idx] == ':' || str[idx] == '%') && idx == 0)
			return (-1);
		else if (idx > 0 && (str[idx] == ':' || str[idx] == '%'))
		{
			while (LABEL_CHARS[++jdx] != '\0')
			{
				if (str[idx - 1] == LABEL_CHARS[jdx] && (count += 1) > 0)
					break ;
			}
		}
	}
	return (count);
}

int		replace_mod(char *str, char *new)
{
	int	idx;

	idx = 0;
	while (LABEL_CHARS[idx] != '\0')
	{
		if (str[-1] == LABEL_CHARS[idx])
		{
			new[0] = ' ';
			new[1] = '%';
			return (1);
		}
		idx += 1;
	}
	new[0] = str[0];
	return (0);
}

int		replace_colon(char *str, char *new)
{
	int	idx;

	idx = 0;
	while (LABEL_CHARS[idx] != '\0')
	{
		if (str[-1] == LABEL_CHARS[idx])
		{
			new[0] = ':';
			new[1] = ' ';
			return (1);
		}
		idx += 1;
	}
	new[0] = str[0];
	return (0);
}

void	expand_space(char *str, char *new, int len)
{
	int		idx;
	int		jdx;

	idx = 0;
	jdx = 0;
	while (jdx < len)
	{
		if (idx > 0 && str[idx] == '%')
			jdx += replace_mod(&str[idx], &new[jdx]);
		else if (idx > 0 && str[idx] == ':')
			jdx += replace_colon(&str[idx], &new[jdx]);
		else
			new[jdx] = str[idx];
		idx += 1;
		jdx += 1;
	}
}

char	*expand_label(char *str)
{
	char	*new;
	int		len;

	if ((len = cnt_space_to_add(str)) == -1)
		return (NULL);
	else if (len == 0)
		return (str);
	len += ft_strlen(str);
	if ((new = ft_strnew(len)) == NULL)
		return (NULL);
	expand_space(str, new, len);
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
