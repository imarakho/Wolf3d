/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:36:11 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 15:36:12 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	check_floor(t_wolf *wl)
{
	if (wl->c->side == 0 && wl->c->raydirx > 0)
	{
		wl->f->floorxwall = wl->c->mapx;
		wl->f->floorywall = wl->c->mapy + wl->t->wallx;
	}
	else if (wl->c->side == 0 && wl->c->raydirx < 0)
	{
		wl->f->floorxwall = wl->c->mapx + 1.0;
		wl->f->floorywall = wl->c->mapy + wl->t->wallx;
	}
	else if (wl->c->side == 1 && wl->c->raydiry > 0)
	{
		wl->f->floorxwall = wl->c->mapx + wl->t->wallx;
		wl->f->floorywall = wl->c->mapy;
	}
	else
	{
		wl->f->floorxwall = wl->c->mapx + wl->t->wallx;
		wl->f->floorywall = wl->c->mapy + 1.0;
	}
	wl->f->distwall = wl->c->perpwalldist;
}

static	void	floor_calc(t_wolf *wl)
{
	wl->f->weight = wl->f->currentdist / wl->f->distwall;
	wl->f->currentfloorx = wl->f->weight *
	wl->f->floorxwall + (1.0 - wl->f->weight) * wl->c->posx;
	wl->f->currentfloory = wl->f->weight *
	wl->f->floorywall + (1.0 - wl->f->weight) * wl->c->posy;
	wl->f->floortexx = (int)(wl->f->currentfloorx
	* (double)wl->t->textrw) % wl->t->textrw;
	wl->f->floortexy = (int)(wl->f->currentfloory
	* (double)wl->t->textrh) % wl->t->textrh;
}

void			lsd_floor(t_wolf *wl)
{
	int			y;
	int			tmp1;
	int			szflr;
	char		*buffloor;
	char		*bufcell;

	check_floor(wl);
	y = wl->c->drawend;
	bufcell = mlx_get_data_addr(wl->t->imgtextr[3],
	&wl->r->bpp, &szflr, &wl->r->endian);
	buffloor = mlx_get_data_addr(wl->t->imgtextr[7],
	&wl->r->bpp, &szflr, &wl->r->endian);
	while (y < WIN_H)
	{
		wl->f->currentdist = WIN_H / (2.0 * y - WIN_H);
		floor_calc(wl);
		tmp1 = y * wl->r->sizeline + (wl->c->i * 4);
		if (wl->flg->celfl == 1)
			ft_memcpy(&wl->r->imbuf[(WIN_H - y + 1) * wl->r->sizeline +
			(wl->c->i * 4)],
			&bufcell[wl->f->floortexx * 4 + wl->f->floortexy * szflr], 4);
		ft_memcpy(&wl->r->imbuf[tmp1], &buffloor[wl->f->floortexx
		* 4 + wl->f->floortexy * szflr], 4);
		y++;
	}
}
