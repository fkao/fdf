/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/07/18 15:50:57 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_put_error(t_fdf *e)
{
	if (e == 0)
	{
		ft_putstr("usage: ./fdf [file] [maxrgb(rrrgggbbb)] ");
		ft_putendl("[minrgb(rrrgggbbb)] [zscale]");
	}
	else if (e->fd == -1)
		ft_putendl("file error: file cannot be found");
	else if (e->wide == -1)
		ft_putendl("map error: invalid map");
	else if (e->wide == 0)
		ft_putendl("map error: empty map");
	else
		return (0);
	free(e);
	return (1);
}

t_trig	*fdf_plot_line(t_fdf *e, t_trig *t)
{
	int	n;

	t->z2 = e->key[t->i][t->j];
	n = t->z2 * e->scale;
	if (t->down)
	{
		t->x2 = t->xo + (t->i * e->size) * cos(0.524);
		t->y2 = t->yo + (t->i * e->size) * sin(0.524 + e->tilt) - n;
		t->i++;
	}
	else
	{
		t->x2 = t->xo + (t->j * e->size) * cos(0.524);
		t->y2 = t->yo - (t->j * e->size) * sin(0.524 + e->tilt) - n;
		t->j++;
	}
	fdf_draw_line(e, t);
	t->y1 = t->y2;
	t->x1 = t->x2;
	t->z1 = t->z2;
	return (t);
}

t_trig	*fdf_set_plot(t_fdf *e, t_trig *t)
{
	int	n;

	t->of = (e->wide * e->size) * sin(0.524) + e->max * e->scale + e->yshift;
	t->z1 = e->key[t->i][t->j];
	n = (t->down) ? t->j : t->i;
	t->xo = (n * e->size) * cos(0.524) + e->size + e->xshift + e->xset;
	t->x1 = t->xo;
	if (t->down)
		t->yo = t->of - (n * e->size) * sin(0.524 + e->tilt) + e->size
			+ e->yset;
	else
		t->yo = t->of + (n * e->size) * sin(0.524 + e->tilt) + e->size
			+ e->yset;
	t->y1 = t->yo - (t->z1 * e->scale);
	return (t);
}

void	fils_de_fer(t_fdf *e)
{
	t_trig	*t;

	(e->scale <= 0) ? exit(0) : 0;
	t = (t_trig*)ft_memalloc(sizeof(*t));
	while (t->i < e->high + 1)
	{
		t->j = 0;
		t = fdf_set_plot(e, t);
		while (t->j < (e->wide + 1))
			t = fdf_plot_line(e, t);
		t->i++;
	}
	t->down = 1;
	t->j--;
	while (t->j >= 0)
	{
		t->i = 0;
		t = fdf_set_plot(e, t);
		while (t->i < (e->high + 1))
			t = fdf_plot_line(e, t);
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
		fdf_put_error(e = 0);
	return (0);
}
