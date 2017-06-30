/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/06/29 17:42:08 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_key_funct(int keycode, t_fdf *map)
{
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	fdf_key_bonus(keycode, map);
	return (0);
}

t_trig	*fdf_plot_line(t_fdf *map, t_plot *pix, t_trig *t)
{
	int	n;

	t->z2 = map->key[t->i][t->j];
	n = t->z2 * map->scale;
	if (pix->down)
	{
		pix->x2 = t->xo + (t->i * map->size) * cos(0.524);
		pix->y2 = t->yo + (t->i * map->size) * sin(0.524 + map->tilt) - n;
		t->i++;
	}
	else
	{
		pix->x2 = t->xo + (t->j * map->size) * cos(0.524);
		pix->y2 = t->yo - (t->j * map->size) * sin(0.524 + map->tilt) - n;
		t->j++;
	}
	fdf_draw_line(map, pix, t);
	pix->y1 = pix->y2;
	pix->x1 = pix->x2;
	t->z1 = t->z2;
	return (t);
}

t_trig	*fdf_set_plot(t_fdf *map, t_plot *pix, t_trig *t)
{
	int	n;

	t->z1 = map->key[t->i][t->j];
	n = (pix->down) ? t->j : t->i;
	t->xo = (n * map->size) * cos(0.524) + map->size;
	pix->x1 = t->xo;
	if (pix->down)
		t->yo = pix->of - (n * map->size) * sin(0.524 + map->tilt) + map->size;
	else
		t->yo = pix->of + (n * map->size) * sin(0.524 + map->tilt) + map->size;
	pix->y1 = t->yo - (t->z1 * map->scale);
	return (t);
}

void	fils_de_fer(t_fdf *map)
{
	t_plot	*pix;
	t_trig	*t;

	t = (t_trig*)ft_memalloc(sizeof(*t));
	pix = (t_plot*)ft_memalloc(sizeof(*pix));
	pix->of = (map->wide * map->size) * sin(0.524) + map->max * map->scale;
	while (t->i < map->high + 1)
	{
		t->j = 0;
		t = fdf_set_plot(map, pix, t);
		while (t->j < (map->wide + 1))
			t = fdf_plot_line(map, pix, t);
		t->i++;
	}
	pix->down = 1;
	t->j = 0;
	while (t->j < map->wide + 1)
	{
		t->i = 0;
		t = fdf_set_plot(map, pix, t);
		while (t->i < (map->high + 1))
			t = fdf_plot_line(map, pix, t);
		t->j++;
	}
}

int		main(int ac, char **av)
{
	t_fdf	*map;

	map = (t_fdf*)ft_memalloc(sizeof(*map));
	map->scale = 3;
	map->rgbmax = "255255255";
	map->rgbmin = "255255255";
	if (ac == 5 && (ft_isdigit(av[4][0]) && ft_atoi(av[4]) > 0 &&
		ft_atoi(av[4]) < 20))
		map->scale = ft_atoi(av[--ac]);
	if (ac == 4 && ft_strlen(av[3]) == 9 && fdf_check_rgb(av[3]))
		map->rgbmin = av[--ac];
	if (ac == 3 && ft_strlen(av[2]) == 9 && fdf_check_rgb(av[2]))
		map->rgbmax = av[--ac];
	if (ac == 2)
	{
		map = fdf_height_width(map, av[1]);
		if (!fdf_put_error(map))
		{
			map = fdf_grab_key(map, av[1]);
			fdf_open_window(map);
		}
	}
	else
		fdf_put_error(0);
	return (0);
}
