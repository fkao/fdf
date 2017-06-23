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
}				t_fdf;

typedef struct	s_pts
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			yflat;
}				t_pts;

int				fdf_width_len(char *str);
int				fdf_put_error(t_fdf *map);
void			fdf_color(int r, int g, int b);
#endif
