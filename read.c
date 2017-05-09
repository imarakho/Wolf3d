/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 18:00:47 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 16:35:52 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_getnbr(const char *s, int i)
{
	int result;
	int sign;

	i = 0;
	result = 0;
	sign = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\f' ||
					s[i] == '\t' || s[i] == '\v' || s[i] == '\r'))
		i++;
	if ((s[i] == 43) || (s[i] == 45))
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] != '\0' && (s[i] > 47 && s[i] < 58))
	{
		result = result * 10 + (s[i] - 48);
		i++;
	}
	return (sign * result);
}

static	void	filecheck(int fd)
{
	if (fd < 0)
	{
		ft_putstr("Wrong file!\n");
		exit(1);
	}
}

void			get_map(t_wolf *wl, char *arg)
{
	int		fd;
	char	*res;
	int		ret;
	int		i;

	i = 1;
	wl->r->y = 1;
	wl->r->x = 1;
	fd = open(arg, O_RDONLY);
	filecheck(fd);
	ret = get_next_line(fd, &res);
	while (res[i] != '\0')
	{
		if (res[i] <= '9' && res[i] >= '0')
			wl->r->x++;
		i++;
	}
	ft_strdel(&res);
	while (get_next_line(fd, &res) == 1)
	{
		ft_strdel(&res);
		wl->r->y++;
	}
	ft_strdel(&res);
	close(fd);
}

static int		**intmemalloc(t_wolf *wl)
{
	int		i;
	int		j;
	int		**m;

	j = -1;
	i = wl->r->y;
	if (!(m = (int**)malloc(sizeof(int*) * (i))))
		exit(1);
	while (++j < i)
		if (!(m[j] = (int*)malloc(sizeof(int) * (wl->r->x))))
			exit(1);
	return (m);
}

void			ft_readbuf(t_wolf *wl, char *arg)
{
	char	*str;
	int		j;
	int		fd;

	wl->c->i = 0;
	get_map(wl, arg);
	wl->r->m = intmemalloc(wl);
	fd = open(arg, O_RDONLY);
	while (get_next_line(fd, &str) == 1)
	{
		wl->r->arr = ft_strsplit(str, ' ');
		j = 0;
		while (j < wl->r->x)
		{
			wl->r->m[wl->c->i][j] = ft_getnbr(wl->r->arr[j], j);
			ft_strdel(&wl->r->arr[j]);
			j++;
		}
		if (str != NULL)
			ft_strdel(&str);
		free(wl->r->arr);
		wl->c->i++;
	}
	ft_strdel(&str);
	close(fd);
}
