/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/07/03 16:07:39 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_put_error(t_fdf *e)
{
	if (e == 0)
	{
		ft_putstr("usage: ./fdf [file][maxrgb(rrrgggbbb)] [minrgb(rrrgggbbb)]");
		ft_putendl(" [zscale]");
	}
	else if (e->fd == -1)
		ft_putendl("error: file cannot be found");
	else if (e->wide == 0)
		ft_putendl("e error: empty e");
	else if (e->wide == -1)
		ft_putendl("e error: invalid e");
	else
		return (0);
	return (1);
}

t_trig	*fdf_plot_line(t_fdf *e, t_plot *pix, t_trig *t)
{
	int	n;

	t->z2 = e->key[t->i][t->j];
	n = t->z2 * e->scale;
	if (pix->down)
	{
		pix->x2 = t->xo + (t->i * e->size) * cos(0.524);
		pix->y2 = t->yo + (t->i * e->size) * sin(0.524 + e->tilt) - n;
		t->i++;
	}
	else
	{
		pix->x2 = t->xo + (t->j * e->size) * cos(0.524);
		pix->y2 = t->yo - (t->j * e->size) * sin(0.524 + e->tilt) - n;
		t->j++;
	}
	fdf_draw_line(e, pix, t);
	pix->y1 = pix->y2;
	pix->x1 = pix->x2;
	t->z1 = t->z2;
	return (t);
}

t_trig	*fdf_set_plot(t_fdf *e, t_plot *pix, t_trig *t)
{
	int	n;

	t->z1 = e->key[t->i][t->j];
	n = (pix->down) ? t->j : t->i;
	t->xo = (n * e->size) * cos(0.524) + e->size + e->xshift + e->xset;
	pix->x1 = t->xo;
	if (pix->down)
		t->yo = pix->of - (n * e->size) * sin(0.524 + e->tilt) + e->size
			+ e->yset;
	else
		t->yo = pix->of + (n * e->size) * sin(0.524 + e->tilt) + e->size
			+ e->yset;
	pix->y1 = t->yo - (t->z1 * e->scale);
	return (t);
}

void	fils_de_fer(t_fdf *e)
{
	t_plot	*pix;
	t_trig	*t;

	(e->scale <= 0) ? exit(0) : 0;
	t = (t_trig*)ft_memalloc(sizeof(*t));
	pix = (t_plot*)ft_memalloc(sizeof(*pix));
	pix->of = (e->wide * e->size) * sin(0.524) + e->max * e->scale + e->yshift;
	while (t->i < e->high + 1)
	{
		t->j = 0;
		t = fdf_set_plot(e, pix, t);
		while (t->j < (e->wide + 1))
			t = fdf_plot_line(e, pix, t);
		t->i++;
	}
	pix->down = 1;
	t->j = 0;
	while (t->j < e->wide + 1)
	{
		t->i = 0;
		t = fdf_set_plot(e, pix, t);
		while (t->i < (e->high + 1))
			t = fdf_plot_line(e, pix, t);
		t->j++;
	}
}

int		main(int ac, char **av)
{
	t_fdf	*e;

	e = (t_fdf*)ft_memalloc(sizeof(*e));
	e->scale = 3;
	e->rgbmax = "255255255";
	e->rgbmin = "255255255";
	if (ac == 5 && (ft_isdigit(av[4][0]) && ft_atoi(av[4]) > 0 &&
		ft_atoi(av[4]) < 20))
		e->scale = ft_atoi(av[--ac]);
	if (ac == 4 && ft_strlen(av[3]) == 9 && fdf_check_rgb(av[3]))
		e->rgbmin = av[--ac];
	if (ac == 3 && ft_strlen(av[2]) == 9 && fdf_check_rgb(av[2]))
		e->rgbmax = av[--ac];
	if (ac == 2)
	{
		e = fdf_height_width(e, av[1]);
		if (!fdf_put_error(e))
		{
			e = fdf_grab_key(e, av[1]);
			fdf_open_window(e);
		}
	}
	else
		fdf_put_error(0);
	return (0);
}
