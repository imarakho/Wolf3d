/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:03:07 by imarakho          #+#    #+#             */
/*   Updated: 2017/01/22 14:24:26 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_words(char const *str, char c)
{
	int ks;
	int nw;

	ks = 0;
	nw = 0;
	while (*str)
	{
		if ((*str) == c && nw)
			nw = 0;
		if ((*str) != c && !nw)
		{
			nw = 1;
			ks++;
		}
		str++;
	}
	return (ks);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char		**ft_list(int ks, char const *str, char c)
{
	size_t	i;
	size_t	k;
	char	**res;

	res = (char**)malloc(sizeof(char*) * ks + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (ks)
	{
		while (str[k] == c && str[k])
			k++;
		res[i] = ft_strnew(ft_wordlen(&str[k], c));
		if (!res[i])
			return (NULL);
		res[i] = ft_strncpy(res[i], &str[k], ft_wordlen(&str[k], c));
		k = k + ft_wordlen(&str[k], c);
		ks--;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	int		ks;
	char	**res;

	if (!s || !c)
		return (NULL);
	ks = ft_words(s, c);
	res = ft_list(ks, s, c);
	if (!res)
		return (NULL);
	return (res);
}
