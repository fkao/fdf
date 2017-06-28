/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:41:38 by fkao              #+#    #+#             */
/*   Updated: 2017/06/28 12:46:57 by fkao             ###   ########.fr       */
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
	float		size;
	int			wide;
	int			high;
	float		scale;
	int			**key;
	int			max;
	int			min;
	void		*mlx;
	void		*win;
	int			c;
	int			r;
	float		tilt;
	float		zoom;
	float		shift;
}				t_fdf;

typedef struct	s_plot
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			of;
	int			color;
}				t_plot;

typedef struct	s_trig
{
	int			i;
	int			j;
	int			z1;
	int			z2;
	int			offset;
	int			xo;
	int			yo;
	int			down;
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

void			fils_de_fer(t_fdf *map);
t_fdf			*fdf_height_width(t_fdf *map, char *file);
t_fdf			*fdf_grab_key(t_fdf *map, char *file);
void			fdf_open_window(t_fdf *map);
void			fdf_draw_line(void *mlx, void *win, t_plot *wire);
int				fdf_width_len(char *str);
int				fdf_put_error(t_fdf *map);
int				fdf_key_funct(int keycode, t_fdf *map);
t_plot			*fdf_expose_color(int z1, int z2, t_fdf *map, t_plot *wire);
#endif
