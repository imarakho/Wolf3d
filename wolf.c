/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 19:45:50 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/27 16:53:47 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		wolf2(t_wolf *wl)
{
	if (wl->c->side == 0)
		wl->c->perpwalldist = (wl->c->mapx - wl->c->rayposx
		+ (1 - wl->c->stepx) / 2) / wl->c->raydirx;
	else
		wl->c->perpwalldist = (wl->c->mapy - wl->c->rayposy
		+ (1 - wl->c->stepy) / 2) / wl->c->raydiry;
	wl->c->lineheight = (int)(WIN_H / wl->c->perpwalldist);
	wl->c->drawstart = -wl->c->lineheight / 2 + WIN_H / 2;
	wl->c->drawend = wl->c->lineheight / 2 + WIN_H / 2;
	texture_calculations(wl);
	lsd_floor(wl);
}

static void		dif_analysis(t_wolf *wl)
{
	while (wl->c->hit == 0)
	{
		if (wl->c->sidedistx < wl->c->sidedisty)
		{
			wl->c->sidedistx += wl->c->deltadistx;
			wl->c->mapx += wl->c->stepx;
			wl->c->side = 0;
		}
		else
		{
			wl->c->sidedisty += wl->c->deltadisty;
			wl->c->mapy += wl->c->stepy;
			wl->c->side = 1;
		}
		if (wl->r->m[wl->c->mapx][wl->c->mapy] > 0)
			wl->c->hit = 1;
	}
}

static void		check_rays(t_wolf *wl)
{
	if (wl->c->raydirx < 0)
	{
		wl->c->stepx = -1;
		wl->c->sidedistx = (wl->c->rayposx - wl->c->mapx) * wl->c->deltadistx;
	}
	else
	{
		wl->c->stepx = 1;
		wl->c->sidedistx = (wl->c->mapx + 1.0 -
		wl->c->rayposx) * wl->c->deltadistx;
	}
	if (wl->c->raydiry < 0)
	{
		wl->c->stepy = -1;
		wl->c->sidedisty = (wl->c->rayposy - wl->c->mapy) * wl->c->deltadisty;
	}
	else
	{
		wl->c->stepy = 1;
		wl->c->sidedisty = (wl->c->mapy + 1.0 -
		wl->c->rayposy) * wl->c->deltadisty;
	}
	dif_analysis(wl);
	wolf2(wl);
}

static	void	start_init(t_wolf *wl)
{
	wl->c->camerax = 2 * wl->c->i / (double)(WIN_W) - 1;
	wl->c->rayposx = wl->c->posx;
	wl->c->rayposy = wl->c->posy;
	wl->c->raydirx = wl->c->dirx + wl->c->planex * wl->c->camerax;
	wl->c->raydiry = wl->c->diry + wl->c->planey * wl->c->camerax;
	wl->c->mapx = (int)(wl->c->rayposx);
	wl->c->mapy = (int)(wl->c->rayposy);
	wl->c->deltadistx = sqrt(1 + (wl->c->raydiry * wl->c->raydiry)
	/ (wl->c->raydirx * wl->c->raydirx));
	wl->c->deltadisty = sqrt(1 + (wl->c->raydirx * wl->c->raydirx)
	/ (wl->c->raydiry * wl->c->raydiry));
	wl->c->hit = 0;
}

void			wolf(t_wolf *wl)
{
	int a;

	wl->c->i = -1;
	draw_background(wl);
	while (++wl->c->i < WIN_W)
	{
		start_init(wl);
		check_rays(wl);
	}
	wl->c->oldtime = wl->c->time;
	wl->c->time = clock();
	wl->c->frametime = (wl->c->time - wl->c->oldtime) / CLOCKS_PER_SEC;
	wl->c->movespeed = wl->c->frametime * 5.0;
	wl->c->rotspeed = wl->c->frametime * 3.0;
	wl->flg->mapfl == 1 ? draw_map(wl) : 0;
	a = mlx_put_image_to_window(wl->r->mlx, wl->r->win, wl->r->img, 0, 0);
	mlx_destroy_image(wl->r->mlx, wl->r->img);
}
