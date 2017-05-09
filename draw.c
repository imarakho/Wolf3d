/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 15:01:18 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 16:41:23 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw_pixel(int x, int y, unsigned short *rgb, t_wolf *wl)
{
	int		a;

	if (x <= 0 || y <= 0 || x >= WIN_W || y >= WIN_H)
		return ;
	wl->r->bpp = 0;
	wl->r->sizeline = 0;
	wl->r->endian = 0;
	wl->r->imbuf = mlx_get_data_addr(wl->r->img, &wl->r->bpp,
	&wl->r->sizeline, &wl->r->endian);
	a = y * wl->r->sizeline + (x << 2);
	wl->r->imbuf[a] = rgb[0];
	wl->r->imbuf[a + 1] = rgb[1];
	wl->r->imbuf[a + 2] = rgb[2];
}

static	void	draw_background2(t_wolf *wl, char *bufxpm, int tmp1, int tmp2)
{
	int			x;
	int			y;
	double		x1;
	double		y1;

	y = 0;
	y1 = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		x1 = 0;
		while (x < WIN_W)
		{
			tmp1 = y * wl->r->sizeline + (x << 2);
			tmp2 = (int)y1 * wl->t->szxpm + ((int)x1 << 2);
			ft_memcpy(&wl->r->imbuf[tmp1], &bufxpm[tmp2], 4);
			x1 += wl->t->rangex;
			x++;
		}
		y++;
		y1 += wl->t->rangey;
	}
}

void			draw_background(t_wolf *wl)
{
	int		tmp1;
	int		tmp2;
	char	*bufxpm;

	tmp1 = 0;
	tmp2 = 0;
	wl->r->img = mlx_new_image(wl->r->mlx, WIN_W, WIN_H);
	wl->t->imgback = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/kosmos.xpm", &wl->c->w, &wl->c->h);
	wl->t->rangex = (double)(wl->c->w) / (double)(WIN_W);
	wl->t->rangey = (double)(wl->c->h) / (double)(WIN_H);
	wl->r->imbuf = mlx_get_data_addr(wl->r->img, &wl->r->bpp,
	&wl->r->sizeline, &wl->r->endian);
	bufxpm = mlx_get_data_addr(wl->t->imgback,
	&wl->r->bpp, &wl->t->szxpm, &wl->r->endian);
	mlx_destroy_image(wl->r->mlx, wl->t->imgback);
	draw_background2(wl, bufxpm, tmp1, tmp2);
}

void			draw_rect(t_wolf *wl, int x, int y)
{
	int		sx;
	int		sy;
	int		ex;
	int		ey;

	sx = x * 6;
	sy = y * 6;
	ex = sx + 6;
	ey = sy + 6;
	while (sy < ey)
	{
		sx = x * 6;
		while (sx < ex)
		{
			ft_draw_pixel(sx, sy, wl->r->rgb, wl);
			sx++;
		}
		sy++;
	}
}

void			draw_map(t_wolf *wl)
{
	int i;
	int j;

	i = 0;
	while (i < wl->r->y)
	{
		j = 0;
		while (j < wl->r->x)
		{
			check(wl, i, j);
			j++;
		}
		i++;
	}
}
