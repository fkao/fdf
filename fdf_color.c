/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:05:12 by fkao              #+#    #+#             */
/*   Updated: 2017/06/29 18:39:21 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_key_tint(int keycode, t_fdf *map)
{
	if (keycode == 15)
		map->r += 10;
	if (keycode == 5)
		map->g += 10;
	if (keycode == 11)
		map->b += 10;
	mlx_clear_window(map->mlx, map->win);
	fils_de_fer(map);
	return (0);
}

int	fdf_rgb_get(t_fdf *map, int z)
{
	t_rgb	*c;

	c = (t_rgb*)ft_memalloc(sizeof(*c));
	c->r = (ft_atoi(ft_strsub(map->rgbmin, 0, 3)) + map->r) % 256;
	c->g = (ft_atoi(ft_strsub(map->rgbmin, 3, 3)) + map->g) % 256;
	c->b = (ft_atoi(ft_strsub(map->rgbmin, 6, 3)) + map->b) % 256;
	c->rz = (ft_atoi(ft_strsub(map->rgbmax, 0, 3)) + map->r) % 256;
	c->gz = (ft_atoi(ft_strsub(map->rgbmax, 3, 3)) + map->g) % 256;
	c->bz = (ft_atoi(ft_strsub(map->rgbmax, 6, 3)) + map->b) % 256;
	c->d = map->max - map->min;
	c->r1 = (c->r - c->rz) / c->d;
	c->g1 = (c->g - c->gz) / c->d;
	c->b1 = (c->b - c->bz) / c->d;
	c->d1 = map->max - z;
	c->rgb = ((c->rz + c->r1 * c->d1) << 16) + ((c->gz + c->g1 * c->d1) << 8) +
		(c->bz + c->b1 * c->d1);
	return (c->rgb);
}

int	fdf_expose_color(t_fdf *map, t_plot *pix, t_trig *t, t_calc *store)
{
	int	yo;
	int	z;

	if (pix->down)
		yo = t->yo + (store->x - t->xo) * (sin(0.524 + map->tilt) / cos(0.524));
	else
		yo = t->yo - (store->x - t->xo) * (sin(0.524 + map->tilt) / cos(0.524));
	z = (yo - store->y) / map->scale;
	return (fdf_rgb_get(map, z));
}
