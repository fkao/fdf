/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:41:38 by fkao              #+#    #+#             */
/*   Updated: 2017/07/25 16:13:21 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	int			fd;
	char		*file;
	int			**key;
	int			wide;
	int			high;
	int			max;
	int			min;
	int			size;
	int			isize;
	double		scale;
	double		iscale;
	double		rx;
	double		ry;
	double		rz;
	int			x;
	int			y;
	char		*rgbmax;
	char		*rgbmin;
	int			xshift;
	int			yshift;
	int			xset;
	int			yset;
	int			press;
	int			px;
	int			py;
}				t_fdf;

typedef struct	s_trig
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			z1;
	int			z2;
	int			color;
	int			i;
	int			j;
	int			xo;
	int			yo;
	int			of;
	int			down;
}				t_trig;

typedef struct	s_bres
{
	int			dx;
	int			dy;
	int			x;
	int			y;
	int			s1;
	int			s2;
	int			swap;
	int			tmp;
	int			dif;
}				t_bres;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
	int			rz;
	int			gz;
	int			bz;
	int			r1;
	int			g1;
	int			b1;
	int			d;
	int			d1;
}				t_rgb;

void			fils_de_fer(t_fdf *e);
void			fdf_height_width(t_fdf *e, char *file);
void			fdf_grab_key(t_fdf *e, char *file);
void			fdf_open_window(t_fdf *e);
void			fdf_draw_line(t_fdf *e, t_trig *t);
int				fdf_put_error(t_fdf *e);
int				fdf_key_cmd(t_fdf *e);
int				fdf_mouse_funct(int code, int x, int y, t_fdf *e);
int				fdf_motion_hook(int x, int y, t_fdf *e);
int				fdf_mouse_release(int code, int x, int y, t_fdf *e);
int				fdf_key_zoom(int code, t_fdf *e);
int				fdf_check_rgb(char *str);
int				fdf_expose_color(t_fdf *e, t_trig *t,
					t_bres *store);
#endif
