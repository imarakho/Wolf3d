/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:37:22 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/16 17:37:46 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		i;

	i = 0;
	if (s1)
		ft_strdel(&s1);
	while (s1[i] != '\0')
		i++;
	s = (char *)malloc((i + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
