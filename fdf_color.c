/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:05:12 by fkao              #+#    #+#             */
/*   Updated: 2017/07/03 16:07:55 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	c = (t_rgb*)ft_memalloc(sizeof(*c));
	c->r = (ft_atoi(ft_strsub(e->rgbmin, 0, 3)) + e->r) % 256;
	c->g = (ft_atoi(ft_strsub(e->rgbmin, 3, 3)) + e->g) % 256;
	c->b = (ft_atoi(ft_strsub(e->rgbmin, 6, 3)) + e->b) % 256;
	c->rz = (ft_atoi(ft_strsub(e->rgbmax, 0, 3)) + e->r) % 256;
	c->gz = (ft_atoi(ft_strsub(e->rgbmax, 3, 3)) + e->g) % 256;
	c->bz = (ft_atoi(ft_strsub(e->rgbmax, 6, 3)) + e->b) % 256;
	c->d = e->max - e->min;
	c->r1 = (c->r - c->rz) / c->d;
	c->g1 = (c->g - c->gz) / c->d;
	c->b1 = (c->b - c->bz) / c->d;
	c->d1 = e->max - z;
	c->rgb = ((c->rz + c->r1 * c->d1) << 16) + ((c->gz + c->g1 * c->d1) << 8) +
		(c->bz + c->b1 * c->d1);
	return (c->rgb);
}

int	fdf_expose_color(t_fdf *e, t_plot *pix, t_trig *t, t_calc *store)
{
	int	y0;
	int	z;

	if (pix->down)
		y0 = t->yo + (store->x - t->xo) * (sin(0.524 + e->tilt) / cos(0.524));
	else
		y0 = t->yo - (store->x - t->xo) * (sin(0.524 + e->tilt) / cos(0.524));
	z = (y0 - store->y) / e->scale;
	return (fdf_rgb_get(e, z));
}
