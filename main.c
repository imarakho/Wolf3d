/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 17:02:23 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 16:40:19 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int	destroy_window(void)
{
	exit(1);
}

static void	cast_init(t_wolf *wl, char *arg)
{
	if (ft_strequ(arg, "3.txt") == 1)
	{
		wl->c->posx = 2;
		wl->c->posy = 2;
	}
	else
	{
		wl->c->posx = 22;
		wl->c->posy = 12;
	}
	wl->c->dirx = -1;
	wl->c->diry = 0;
	wl->c->h = 0;
	wl->c->w = 0;
	wl->c->planex = 0;
	wl->c->planey = 0.66;
	wl->c->time = 0;
	wl->c->oldtime = 0;
	wl->flg->mapfl = -1;
	wl->flg->celfl = -1;
}

static void	struct_init(t_wolf **wl)
{
	(*wl)->r = (t_read*)ft_memalloc(sizeof(t_read));
	(*wl)->f = (t_floor*)ft_memalloc(sizeof(t_floor));
	(*wl)->c = (t_cast*)ft_memalloc(sizeof(t_cast));
	(*wl)->t = (t_tex*)ft_memalloc(sizeof(t_tex));
	(*wl)->flg = (t_flag*)ft_memalloc(sizeof(t_flag));
}

static void	txtr_init(t_wolf *wl)
{
	wl->t->imgtextr = (void **)malloc(sizeof(void *) * 9);
	wl->t->imgtextr[0] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/redbrick.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[1] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/mossy.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[2] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/wood.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[3] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/greystone.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[4] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/eagle.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[5] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/eblo.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[6] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/putin.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[7] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/colorstone.xpm", &wl->t->textrw, &wl->t->textrh);
	wl->t->imgtextr[8] = mlx_xpm_file_to_image(wl->r->mlx,
	"pics/obolon.xpm", &wl->t->textrw, &wl->t->textrh);
}

int			main(int argc, char **argv)
{
	t_wolf	*wl;

	wl = (t_wolf*)ft_memalloc(sizeof(t_wolf));
	struct_init(&wl);
	if (argc != 2)
	{
		ft_putstr("You must choose level:1.txt,2.txt or 3.txt.\n");
		exit(1);
	}
	ft_readbuf(wl, argv[1]);
	cast_init(wl, argv[1]);
	wl->r->mlx = mlx_init();
	txtr_init(wl);
	ft_strequ(argv[1], "3.txt") == 1 ? wl->flg->celfl = 1 : 0;
	wl->r->win = mlx_new_window(wl->r->mlx, WIN_W, WIN_H, "wolf");
	wolf(wl);
	mlx_hook(wl->r->win, 2, 0, key_func, wl);
	mlx_hook(wl->r->win, 17, 0, destroy_window, 0);
	mlx_loop(wl->r->mlx);
	return (0);
}
