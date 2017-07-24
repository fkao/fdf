/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:46:36 by fkao              #+#    #+#             */
/*   Updated: 2017/07/20 17:34:19 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	fdf_mouse_funct(int code, int x, int y, t_fdf *e)
{
	printf("%d\n", code);
	if (code == 1)
	{
		e->press = 1;
		e->px = x - e->xshift;
		e->py = y - e->yshift;
	}
	if (code == 4)
		e->tilt -= 0.01746;
	if (code == 5)
		e->tilt += 0.01746;
	mlx_clear_window(e->mlx, e->win);
	fils_de_fer(e);
	return (0);
}

int	fdf_motion_hook(int x, int y, t_fdf *e)
{
	if (e->press)
	{
		e->xshift = x - e->px;
		e->yshift = y - e->py;
		mlx_clear_window(e->mlx, e->win);
		fils_de_fer(e);
	}
	return (0);
}

int	fdf_mouse_release(int code, int x, int y, t_fdf *e)
{
	(void)x;
	(void)y;
	if (code == 1)
		e->press = 0;
	return (0);
}
