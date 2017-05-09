/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:32:45 by imarakho          #+#    #+#             */
/*   Updated: 2017/02/13 21:36:27 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*newjoin(char *s1, char *s2)
{
	char	*r;

	if (!(r = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(r, s1);
	ft_strcat(r, s2);
	ft_strdel(&s1);
	return (r);
}

static int		read_line(int fd, char **buf, char **line, char *pos)
{
	int		res;

	*line = ft_strdup(*buf);
	while (!pos)
	{
		if ((res = read(fd, *buf, BUFF_SIZE)) < 0)
			return (-1);
		if ((pos = ft_strchr(*buf, '\n')) == NULL && !res)
			return ((*buf)[0] = 0);
		else if (pos)
		{
			(*buf)[res] = res ? 0 : (*buf)[res];
			pos[0] = 0;
			*line = newjoin(*line, *buf);
			ft_strcpy(*buf, pos + 1);
		}
		else
		{
			(*buf)[res] = res ? 0 : (*buf)[res];
			*line = newjoin(*line, *buf);
			(*buf)[0] = 0;
		}
	}
	return (*line ? 1 : -1);
}

int				get_next_line(int const fd, char **line)
{
	static char *buf;
	char		*pos;
	int			res;

	if (BUFF_SIZE <= 0 || !line)
		return (-1);
	if (!buf)
		if (!(buf = ft_strnew(BUFF_SIZE)))
			return (-1);
	pos = ft_strchr(buf, '\n');
	if (pos)
	{
		*pos = 0;
		*line = ft_strdup(buf);
		ft_strcpy(buf, pos + 1);
		return (*line ? 1 : -1);
	}
	else
		res = read_line(fd, &buf, line, NULL);
	if (res == 0 && ft_strlen(*line) == 0)
		ft_strdel(&buf);
	if (res == -1)
		return (-1);
	return (res ? 1 : ft_strlen(*line) != 0);
}
