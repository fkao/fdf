/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 12:59:45 by fkao              #+#    #+#             */
/*   Updated: 2017/07/20 17:37:53 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_key_zoom(int code, t_fdf *e)
{
	e->isize = (!e->isize) ? e->size : e->isize;
	e->iscale = (!e->iscale) ? e->scale : e->iscale;
	(code == 24) ? e->size++ : e->size--;
	e->scale = e->iscale / e->isize * e->size;
	e->xset = (e->size - e->isize) * ((e->wide + e->high) *
		cos(0.524) + 2) / 2;
	e->yset = (e->size - e->isize) * ((e->wide + e->high) *
		sin(0.524) + 2) / 2;
	mlx_clear_window(e->mlx, e->win);
	fils_de_fer(e);
	return (0);
}

int	fdf_key_bonus(int code, t_fdf *e)
{
	if (code == 123 || code == 124)
		e->xshift = (code == 123) ? e->xshift - 3 : e->xshift + 3;
	if (code == 125 || code == 126)
		e->yshift = (code == 126) ? e->yshift - 3 : e->yshift + 3;
	if (code == 24 || code == 27)
		fdf_key_zoom(code, e);
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

int	fdf_key_cmd(t_fdf *e)
{
	ft_putendl("action: key command (mouse command)");
	ft_putendl("zoom in: =\t\t\tzoom out: -");
	ft_putendl("tilt up: page up\t\ttilt down: page down");
	ft_putendl("tint red: r\t\t\ttint green: g\t\t\ttint blue: b");
	ft_putendl("move up: up (drag up)\t\tmove down: down (drag down)");
	ft_putendl("move left: left (drag left)\tmove right: right (drag right)");
	ft_putendl("exit: esc");
	mlx_hook(e->win, 2, 0, fdf_key_funct, e);
	mlx_hook(e->win, 4, 0, fdf_mouse_funct, e);
	mlx_hook(e->win, 6, 0, fdf_motion_hook, e);
	mlx_hook(e->win, 5, 0, fdf_mouse_release, e);
	return (0);
}
