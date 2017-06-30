/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:41:38 by fkao              #+#    #+#             */
/*   Updated: 2017/06/29 19:10:05 by fkao             ###   ########.fr       */
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
	float		size;
	int			wide;
	int			high;
	float		scale;
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

void			fils_de_fer(t_fdf *map);
t_fdf			*fdf_height_width(t_fdf *map, char *file);
t_fdf			*fdf_grab_key(t_fdf *map, char *file);
void			fdf_open_window(t_fdf *map);
void			fdf_draw_line(t_fdf *map, t_plot *pix, t_trig *t);
int				fdf_size_init(int high, int widecd
);
int				fdf_width_len(char *str);
int				fdf_put_error(t_fdf *map);
int				fdf_check_rgb(char *str);
int				fdf_key_funct(int keycode, t_fdf *map);
int				fdf_key_bonus(int keycode, t_fdf *map);
int				fdf_key_tint(int keycode, t_fdf *map);
int				fdf_expose_color(t_fdf *map, t_plot *pix, t_trig *t,
					t_calc *store);
#endif
