/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 14:41:38 by fkao              #+#    #+#             */
/*   Updated: 2017/06/23 15:41:51 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"

typedef struct	s_fdf
{
	int			fd;
	int			size;
	int			wide;
	int			high;
	int			BUFF;
	int			**key;
	int			max;
	int			min;
	void		*mlx;
	void		*win;
	int			c;
	int			i;
	int			r;
}				t_fdf;

typedef struct	s_pts
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			color;
	int			rshift;
}				t_pts;

void			fils_de_fer(t_fdf *map);
int				fdf_width_len(char *str);
int				fdf_put_error(t_fdf *map);
t_pts			*fdf_expose_color(int z1, int z2, t_fdf*map, t_pts *ord);
#endif
