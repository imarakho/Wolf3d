/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 19:35:33 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 14:58:38 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	check(t_wolf *wl, int i, int j)
{
	if (wl->r->m[i][j] > 0)
	{
		wl->r->rgb[0] = 0;
		wl->r->rgb[1] = 0;
		wl->r->rgb[2] = 0;
		draw_rect(wl, i, j);
	}
	else if (i == (int)wl->c->posx && j == (int)wl->c->posy)
	{
		wl->r->rgb[0] = 0;
		wl->r->rgb[1] = 0;
		wl->r->rgb[2] = 255;
		draw_rect(wl, i, j);
	}
	else
	{
		wl->r->rgb[0] = 255;
		wl->r->rgb[1] = 255;
		wl->r->rgb[2] = 255;
		draw_rect(wl, i, j);
	}
}

void	texture_calculations(t_wolf *wl)
{
	wl->t->texnum = wl->r->m[wl->c->mapx][wl->c->mapy] - 1;
	if (wl->c->side == 0)
		wl->t->wallx = wl->c->rayposy + wl->c->perpwalldist * wl->c->raydiry;
	else
		wl->t->wallx = wl->c->rayposx + wl->c->perpwalldist * wl->c->raydirx;
	wl->t->wallx -= floor(wl->t->wallx);
	wl->t->texx = (int)(wl->t->wallx * (double)(wl->t->textrw));
	if (wl->c->side == 0 && wl->c->raydirx > 0)
		wl->t->texx = wl->t->textrw - wl->t->texx - 1;
	if (wl->c->side == 1 && wl->c->raydiry < 0)
		wl->t->texx = wl->t->textrw - wl->t->texx - 1;
	generate_textures(wl);
}

void	generate_textures(t_wolf *wl)
{
	int		y;
	double	y1;
	int		tmp1;
	char	*buftex;

	y = wl->c->drawstart;
	wl->t->rangey = (double)(wl->t->textrh) / (double)(wl->c->lineheight);
	buftex = mlx_get_data_addr(wl->t->imgtextr[wl->t->texnum],
	&wl->r->bpp, &wl->t->szxpm, &wl->r->endian);
	y1 = 0;
	while (y < wl->c->drawend)
	{
		tmp1 = y * wl->r->sizeline + wl->c->i * 4;
		if (y > 0 && y < WIN_H)
			ft_memcpy(&wl->r->imbuf[tmp1],
			&buftex[wl->t->texx * 4 + (int)(y1) * wl->t->szxpm], 4);
		y1 += wl->t->rangey;
		y++;
	}
}
