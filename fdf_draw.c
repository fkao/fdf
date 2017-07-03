/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 14:22:37 by fkao              #+#    #+#             */
/*   Updated: 2017/07/03 14:53:51 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		sign(int n)
{
	if (n > 0)
		return (1);
	else if (n < 0)
		return (-1);
	return (0);
}

t_calc	*fdf_populate_store(t_plot *pix, t_calc *store)
{
	store->x = pix->x1;
	store->y = pix->y1;
	store->dx = pix->x2 - pix->x1;
	store->dy = ft_toabsl(pix->y2 - pix->y1);
	store->s1 = sign(pix->x2 - pix->x1);
	store->s2 = sign(pix->y2 - pix->y1);
	if (store->dy > store->dx)
	{
		store->tmp = store->dx;
		store->dx = store->dy;
		store->dy = store->tmp;
		store->swap = 1;
	}
	store->dif = 2 * store->dy - store->dx;
	return (store);
}

void	fdf_draw_line(t_fdf *e, t_plot *pix, t_trig *t)
{
	t_calc	*store;
	int		i;

	store = (t_calc*)ft_memalloc(sizeof(*store));
	store = fdf_populate_store(pix, store);
	i = 0;
	while (i < store->dx)
	{
		pix->color = fdf_expose_color(e, pix, t, store);
		mlx_pixel_put(e->mlx, e->win, store->x, store->y, pix->color);
		while (store->dif >= 0)
		{
			store->dif = store->dif - 2 * store->dx;
			if (store->swap)
				store->x += store->s1;
			else
				store->y += store->s2;
		}
		store->dif += 2 * store->dy;
		if (store->swap)
			store->y += store->s2;
		else
			store->x += store->s1;
		i++;
	}
}
