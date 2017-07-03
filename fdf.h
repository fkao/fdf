/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:41:38 by fkao              #+#    #+#             */
/*   Updated: 2017/07/03 16:21:52 by fkao             ###   ########.fr       */
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
	int			fd;
	char		*file;
	int			size;
	int			isize;
	int			wide;
	int			high;
	float		scale;
	float		iscale;
	int			**key;
	int			max;
	int			min;
	void		*mlx;
	void		*win;
	char		*rgbmax;
	char		*rgbmin;
	int			r;
	int			g;
	int			b;
	float		tilt;
	int			xshift;
	int			yshift;
	int			xset;
	int			yset;
}				t_fdf;

typedef struct	s_plot
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			of;
	int			down;
	int			color;
}				t_plot;

typedef struct	s_trig
{
	int			i;
	int			j;
	int			z1;
	int			z2;
	int			of;
	int			xo;
	int			yo;
	int			xflat;
}				t_trig;

typedef struct	s_calc
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
}				t_calc;

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
	int			rgb;
	int			d;
	int			d1;
}				t_rgb;

void			fils_de_fer(t_fdf *e);
t_fdf			*fdf_height_width(t_fdf *e, char *file);
t_fdf			*fdf_grab_key(t_fdf *e, char *file);
void			fdf_open_window(t_fdf *e);
void			fdf_draw_line(t_fdf *e, t_plot *pix, t_trig *t);
int				fdf_check_rgb(char *str);
int				fdf_key_funct(int keycode, t_fdf *e);
int				fdf_mouse_funct(int keycode, int x, int y, t_fdf *e);
int				fdf_expose_color(t_fdf *e, t_plot *pix, t_trig *t,
					t_calc *store);
#endif
