/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 15:46:36 by fkao              #+#    #+#             */
/*   Updated: 2017/08/24 14:30:33 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_mouse_funct(int code, int x, int y, t_fdf *e)
{
	if (code == 1)
	{
		e->press = 1;
		e->px = x - e->xshift;
		e->py = y - e->yshift;
	}
	if (code == 4)
		fdf_key_zoom(24, e);
	if (code == 5)
		fdf_key_zoom(27, e);
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
