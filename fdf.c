/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/06/28 12:47:16 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_key_funct2(int keycode, t_fdf *map)
{
	float theta;

	if (keycode == 8)
		map->c = (map->c) ? 0 : 1;
	if (keycode == 15 && map->c)
		map->r = (map->r) ? 0 : 25;
	if (keycode == 126)
		map->tilt -= 0.017;
	if (keycode == 125)
		map->tilt += 0.017;
	if (keycode == 24)
	{
		theta = atan(map->scale / map->size);
		map->size++;
		map->scale = tan(theta) * map->size;
	}
	if (keycode == 27)
	{
		theta = atan(map->scale / map->size);
		map->size--;
		map->scale = tan(theta) * map->size;
	}
	mlx_clear_window(map->mlx, map->win);
	fils_de_fer(map);
	return (0);
}

int		fdf_key_funct(int keycode, t_fdf *map)
{
	ft_putstr("key event: ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	fdf_key_funct2(keycode, map);
	return (0);
}

t_trig	*fdf_plot_line(t_fdf *map, t_plot *wire, t_trig *t)
{
	int	n;

	t->z2 = map->key[t->i][t->j];
	wire = (map->c) ? fdf_expose_color(t->z1, t->z2, map, wire) : wire;
	n = t->z2 * map->scale;
	if (t->down)
	{
		wire->x2 = t->xo + (t->i * map->size) * cos(0.524);
		wire->y2 = t->yo + (t->i * map->size) * sin(0.524 + map->tilt) - n;
		t->i++;
	}
	else
	{
		wire->x2 = t->xo + (t->j * map->size) * cos(0.524);
		wire->y2 = t->yo - (t->j * map->size) * sin(0.524 + map->tilt) - n;
		t->j++;
	}
	fdf_draw_line(map->mlx, map->win, wire);
	wire->y1 = wire->y2;
	wire->x1 = wire->x2;
	t->z1 = t->z2;
	return (t);
}

t_trig	*fdf_set_plot(t_fdf *map, t_plot *wire, t_trig *t)
{
	int	n;

	t->z1 = map->key[t->i][t->j];
	n = (t->down) ? t->j : t->i;
	wire->x1 = (n * map->size) * cos(0.524) + map->size;
	t->xo = wire->x1;
	if (t->down)
		t->yo = wire->of - (n * map->size) * sin(0.524 + map->tilt) + map->size;
	else
		t->yo = wire->of + (n * map->size) * sin(0.524 + map->tilt) + map->size;
	wire->y1 = t->yo - (t->z1 * map->scale);
	return (t);
}

void	fils_de_fer(t_fdf *map)
{
	t_plot	*wire;
	t_trig	*t;

	if (!map->size)
		exit(0);
	t = (t_trig*)ft_memalloc(sizeof(*t));
	wire = (t_plot*)ft_memalloc(sizeof(*wire));
	wire->of = (map->wide * map->size) * sin(0.524) + map->max * map->scale;
	wire->color = 0x00FFFFFF;
	while (t->i < map->high + 1)
	{
		t->j = 0;
		t = fdf_set_plot(map, wire, t);
		while (t->j < (map->wide + 1))
			t = fdf_plot_line(map, wire, t);
		t->i++;
	}
	t->down = 1;
	t->j = 0;
	while (t->j < map->wide + 1)
	{
		t->i = 0;
		t = fdf_set_plot(map, wire, t);
		while (t->i < (map->high + 1))
			t = fdf_plot_line(map, wire, t);
		t->j++;
	}
}

int		main(int ac, char **av)
{
	t_fdf	*map;

	map = (t_fdf*)ft_memalloc(sizeof(*map));
	map->scale = 3;
	if (ac == 3 && ft_isdigit(av[2][0]))
	{
		map->scale = ft_atoi(av[2]);
		ac--;
	}
	if (ac == 2)
	{
		map = fdf_height_width(map, av[1]);
		if (!(fdf_put_error(map)))
		{
			map = fdf_grab_key(map, av[1]);
			fdf_open_window(map);
		}
	}
	else
		fdf_put_error(0);
	return (0);
}
