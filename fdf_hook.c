/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 12:59:45 by fkao              #+#    #+#             */
/*   Updated: 2017/07/18 15:34:57 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_key_zoom(int code, t_fdf *e)
{
	e->isize = (!e->isize) ? e->size : e->isize;
	e->iscale = (!e->iscale) ? e->scale : e->iscale;
	if (code == 1)
	{
		e->scale = e->iscale / e->isize * ++e->size;
		e->xset = (e->size - e->isize) * ((e->wide + e->high) *
			cos(0.524) + 2) / -2;
		e->yset = -1 * (e->wide * (e->size - e->isize)) * sin(0.524) - e->max
			* (e->scale - e->iscale);
	}
	if (code == 2)
	{
		e->scale = e->iscale / e->isize * --e->size;
		e->xset = (e->isize - e->size) * ((e->wide + e->high) *
			cos(0.524) + 2) / 2;
		e->yset = (e->wide * (e->isize - e->size)) * sin(0.524) + e->max
			* (e->iscale - e->scale);
	}
	mlx_clear_window(e->mlx, e->win);
	fils_de_fer(e);
	return (0);
}

int	fdf_mouse_funct(int code, int x, int y, t_fdf *e)
{
	(void)x;
	(void)y;
	if (code == 1 || code == 2)
		fdf_key_zoom(code, e);
	if (code == 6 || code == 7 || code == 123 || code == 124)
		e->xshift = (code == 6 || code == 123) ? e->xshift - 2 : e->xshift + 2;
	if (code == 4 || code == 5 || code == 125 || code == 126)
		e->yshift = (code == 4 || code == 126) ? e->yshift - 2 : e->yshift + 2;
	mlx_clear_window(e->mlx, e->win);
	fils_de_fer(e);
	return (0);
}

int	fdf_key_bonus(int code, t_fdf *e)
{
	if (code >= 123 && code <= 126)
		fdf_mouse_funct(code, 0, 0, e);
	if (code == 24 || code == 27)
		fdf_key_zoom((code == 24) ? 1 : 2, e);
	if (code == 15)
		e->r += 12;
	if (code == 5)
		e->g += 12;
	if (code == 11)
		e->b += 12;
	if (code == 116)
		e->tilt -= 0.01746;
	if (code == 121)
		e->tilt += 0.01746;
	mlx_clear_window(e->mlx, e->win);
	fils_de_fer(e);
	return (0);
}

int	fdf_key_funct(int code, t_fdf *e)
{
	if (code == 53)
	{
		free(e->key);
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	fdf_key_bonus(code, e);
	return (0);
}
