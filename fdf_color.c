/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:05:12 by fkao              #+#    #+#             */
/*   Updated: 2017/07/28 17:40:01 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	fdf_check_rgb(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	fdf_rgb_get(t_fdf *e, int z)
{
	t_rgb	*c;
	int		rgb;

	c = (t_rgb*)ft_memalloc(sizeof(*c));
	c->r = ft_atoi(ft_strsub(e->rgbmin, 0, 3)) % 256;
	c->g = ft_atoi(ft_strsub(e->rgbmin, 3, 3)) % 256;
	c->b = ft_atoi(ft_strsub(e->rgbmin, 6, 3)) % 256;
	c->rz = ft_atoi(ft_strsub(e->rgbmax, 0, 3)) % 256;
	c->gz = ft_atoi(ft_strsub(e->rgbmax, 3, 3)) % 256;
	c->bz = ft_atoi(ft_strsub(e->rgbmax, 6, 3)) % 256;
	c->d = e->max - e->min;
	if (c->d == 0)
		rgb = (c->r << 16) + (c->g << 8) + (c->b);
	else
	{
		c->r1 = (c->r - c->rz) / c->d;
		c->g1 = (c->g - c->gz) / c->d;
		c->b1 = (c->b - c->bz) / c->d;
		c->d1 = e->max - z;
		rgb = ((c->rz + c->r1 * c->d1) << 16) + ((c->gz + c->g1 * c->d1) << 8) +
			(c->bz + c->b1 * c->d1);
	}
	free(c);
	return (rgb);
}

int	fdf_expose_color(t_fdf *e, t_trig *t, t_bres *store)
{
	int	z;
	int	f;

	z = t->z1;
	if ((t->x2 - t->x1) != 0 && (t->y2 - t->y1) == 0)
	{
		f = (store->x - t->x1) * 10 / (t->x2 - t->x1) * (t->z2 - t->z1);
		z = t->z1 + f / 10;
	}
	else if ((t->y2 - t->y1) != 0)
	{
		f = (store->y - t->y1) * 10 / (t->y2 - t->y1) * (t->z2 - t->z1);
		z = t->z1 + f / 10;
	}
	return (fdf_rgb_get(e, z));
}
