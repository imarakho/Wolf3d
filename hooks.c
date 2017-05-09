/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:16:14 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/16 19:41:46 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	check_camera(int key, t_wolf *wl)
{
	if (key == 124)
	{
		wl->c->olddirx = wl->c->dirx;
		wl->c->dirx = wl->c->dirx *
		cos(-wl->c->rotspeed) - wl->c->diry * sin(-wl->c->rotspeed);
		wl->c->diry = wl->c->olddirx *
		sin(-wl->c->rotspeed) + wl->c->diry * cos(-wl->c->rotspeed);
		wl->c->oldplanex = wl->c->planex;
		wl->c->planex = wl->c->planex *
		cos(-wl->c->rotspeed) - wl->c->planey * sin(-wl->c->rotspeed);
		wl->c->planey = wl->c->oldplanex *
		sin(-wl->c->rotspeed) + wl->c->planey * cos(-wl->c->rotspeed);
	}
}

static void	check_move(int key, t_wolf *wl)
{
	if (key == 53)
		exit(1);
	if (key == 10)
		wl->flg->mapfl *= -1;
	if (key == 126)
	{
		if (!wl->r->m[(int)(wl->c->posx +
		wl->c->dirx * wl->c->movespeed)][(int)(wl->c->posy)])
			wl->c->posx += wl->c->dirx * wl->c->movespeed;
		if (!wl->r->m[(int)(wl->c->posx)][(int)(wl->c->posy +
		wl->c->diry * wl->c->movespeed)])
			wl->c->posy += wl->c->diry * wl->c->movespeed;
	}
	if (key == 125)
	{
		if (!wl->r->m[(int)(wl->c->posx - wl->c->dirx
		* wl->c->movespeed)][(int)(wl->c->posy)])
			wl->c->posx -= wl->c->dirx * wl->c->movespeed;
		if (!wl->r->m[(int)(wl->c->posx)][(int)(wl->c->posy -
			wl->c->diry * wl->c->movespeed)])
			wl->c->posy -= wl->c->diry * wl->c->movespeed;
	}
}

int			key_func(int key, t_wolf *wl)
{
	check_move(key, wl);
	check_camera(key, wl);
	if (key == 123)
	{
		wl->c->olddirx = wl->c->dirx;
		wl->c->dirx = wl->c->dirx *
		cos(wl->c->rotspeed) - wl->c->diry * sin(wl->c->rotspeed);
		wl->c->diry = wl->c->olddirx *
		sin(wl->c->rotspeed) + wl->c->diry * cos(wl->c->rotspeed);
		wl->c->oldplanex = wl->c->planex;
		wl->c->planex = wl->c->planex *
		cos(wl->c->rotspeed) - wl->c->planey * sin(wl->c->rotspeed);
		wl->c->planey = wl->c->oldplanex *
		sin(wl->c->rotspeed) + wl->c->planey * cos(wl->c->rotspeed);
	}
	wolf(wl);
	return (0);
}
