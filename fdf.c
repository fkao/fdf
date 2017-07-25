/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/07/25 16:13:29 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_3d_rotate(t_fdf *e, int x, int y, int z)
{
	int	xc;
	int	yc;

	xc = (e->wide + e->high) * e->size * cos(0.524) / 2 + e->size
		+ e->xshift - e->xset;
	yc = (e->wide + e->high) * e->size * sin(0.524) / 2 + e->size
		+ e->scale * (e->max - e->min) + e->yshift - e->yset;
	x = x - xc;
	y = y - yc;
	z = z * e->scale;
	e->x = x * cos(e->ry) * cos(e->rz) - y * sin(e->rz) - z * sin(e->ry) + xc;
	z = z * cos(e->ry) * cos(e->rx) + x * sin(e->ry) + y * sin(e->rx);
	e->y = y * cos(e->rz) * cos(e->rx) + x * sin(e->rz) - z + yc;
}

void	fdf_plot_line(t_fdf *e, t_trig *t)
{
	t->z2 = e->key[t->i][t->j];
	if (t->down)
	{
		t->x2 = t->xo + (t->i * e->size) * cos(0.524);
		t->y2 = t->yo + (t->i * e->size) * sin(0.524);
		t->i++;
	}
	else
	{
		t->x2 = t->xo + (t->j * e->size) * cos(0.524);
		t->y2 = t->yo - (t->j * e->size) * sin(0.524);
		t->j++;
	}
	fdf_3d_rotate(e, t->x2, t->y2, t->z2);
	t->x2 = e->x;
	t->y2 = e->y;
	fdf_draw_line(e, t);
	t->y1 = t->y2;
	t->x1 = t->x2;
	t->z1 = t->z2;
}

void	fdf_set_plot(t_fdf *e, t_trig *t)
{
	int	n;

	t->of = (e->wide * e->size) * sin(0.524) + e->max * e->scale + e->yshift
		- e->yset;
	t->z1 = e->key[t->i][t->j];
	n = (t->down) ? t->j : t->i;
	t->xo = (n * e->size) * cos(0.524) + e->size + e->xshift - e->xset;
	if (t->down)
		t->yo = t->of - (n * e->size) * sin(0.524) + e->size;
	else
		t->yo = t->of + (n * e->size) * sin(0.524) + e->size;
	fdf_3d_rotate(e, t->xo, t->yo, t->z1);
	t->x1 = e->x;
	t->y1 = e->y;
}

void	fils_de_fer(t_fdf *e)
{
	t_trig	*t;

	t = (t_trig*)ft_memalloc(sizeof(*t));
	while (t->i < e->high + 1)
	{
		t->j = 0;
		fdf_set_plot(e, t);
		while (t->j < (e->wide + 1))
			fdf_plot_line(e, t);
		t->i++;
	}
	t->down = 1;
	t->j--;
	while (t->j >= 0)
	{
		t->i = 0;
		fdf_set_plot(e, t);
		while (t->i < (e->high + 1))
			fdf_plot_line(e, t);
		t->j--;
	}
	free(t);
}

int		main(int ac, char **av)
{
	t_fdf	*e;

	e = (t_fdf*)ft_memalloc(sizeof(*e));
	e->scale = 3;
	e->rgbmax = "250250000";
	e->rgbmin = "250000200";
	if (ac == 5 && ft_strlen(av[4]) == 9 && fdf_check_rgb(av[4]))
		e->rgbmin = av[--ac];
	if (ac == 4 && ft_strlen(av[3]) == 9 && fdf_check_rgb(av[3]))
		e->rgbmax = av[--ac];
	if (ac == 3 && (ft_isdigit(av[2][0]) && ft_atoi(av[2]) > 0 &&
		ft_atoi(av[4]) < 20))
		e->scale = ft_atoi(av[--ac]);
	if (ac == 2)
	{
		fdf_height_width(e, av[1]);
		if (!fdf_put_error(e))
		{
			fdf_grab_key(e, av[1]);
			fdf_open_window(e);
		}
	}
	else
		fdf_put_error(e = 0);
	return (0);
}
