/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 14:22:37 by fkao              #+#    #+#             */
/*   Updated: 2017/07/25 13:50:45 by fkao             ###   ########.fr       */
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

t_bres	*fdf_populate_store(t_trig *t, t_bres *store)
{
	store->x = t->x1;
	store->y = t->y1;
	store->dx = ft_toabsl(t->x2 - t->x1);
	store->dy = ft_toabsl(t->y2 - t->y1);
	store->s1 = sign(t->x2 - t->x1);
	store->s2 = sign(t->y2 - t->y1);
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

void	fdf_draw_line(t_fdf *e, t_trig *t)
{
	t_bres	*store;
	int		i;

	store = fdf_populate_store(t, (t_bres*)ft_memalloc(sizeof(*store)));
	i = 0;
	while (i < store->dx)
	{
		t->color = fdf_expose_color(e, t, store);
		mlx_pixel_put(e->mlx, e->win, store->x, store->y, t->color);
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
	free(store);
}
