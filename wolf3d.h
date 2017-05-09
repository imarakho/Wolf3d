/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imarakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:44:45 by imarakho          #+#    #+#             */
/*   Updated: 2017/03/17 15:19:11 by imarakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <mlx.h>
# include "libft/libft.h"
# include "get_next_line.h"
# define WIN_H 1024
# define WIN_W 1280

typedef struct		s_flags
{
	short	mapfl;
	short	celfl;
}					t_flag;
typedef struct		s_read
{
	void			*mlx;
	void			*img;
	void			*win;
	int				bpp;
	int				sizeline;
	int				endian;
	char			**arr;
	int				x;
	int				y;
	char			*imbuf;
	int				**m;
	unsigned short	rgb[3];
}					t_read;
typedef struct		s_tex
{
	double			wallx;
	int				texx;
	int				texy;
	int				texnum;
	void			**imgtextr;
	int				textrh;
	int				textrw;
	int				szxpm;
	double			rangex;
	double			rangey;
	void			*imgback;
}					t_tex;
typedef struct		s_floor
{
	double			weight;
	double			distwall;
	double			distplayer;
	double			currentdist;
	double			currentfloorx;
	double			currentfloory;
	double			floorxwall;
	double			floorywall;
	int				floortexx;
	int				floortexy;
}					t_floor;

typedef struct		s_cast
{
	int				w;
	int				h;
	int				i;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			posy;
	double			posx;
	double			dirx;
	double			olddirx;
	double			diry;
	double			planex;
	double			oldplanex;
	double			planey;
	double			time;
	double			oldtime;
	double			frametime;
	double			movespeed;
	double			rotspeed;
}					t_cast;
typedef struct		s_wolf
{
	t_floor			*f;
	t_cast			*c;
	t_tex			*t;
	t_read			*r;
	t_flag			*flg;
}					t_wolf;

void				draw_rect(t_wolf *wl, int x, int y);
void				check(t_wolf *wl, int i, int j);
void				draw_map(t_wolf *wl);
void				ft_readbuf(t_wolf *wl, char *arg);
void				ft_draw_pixel(int x, int y,
						unsigned short *rgb, t_wolf *wl);
void				texture_calculations(t_wolf *wl);
void				generate_textures(t_wolf *wl);
void				read_textures(t_wolf *wl);
void				draw_background(t_wolf *wl);
void				check_color(t_wolf *wl);
int					key_func(int key, t_wolf *wl);
void				wolf(t_wolf *wl);
void				draw_vertical_line(t_wolf *wl);
void				lsd_floor(t_wolf *wl);

#endif
