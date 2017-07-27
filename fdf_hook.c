/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 12:59:45 by fkao              #+#    #+#             */
/*   Updated: 2017/07/27 16:34:29 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_key_zoom(int code, t_fdf *e)
{
	e->isize = (!e->isize) ? e->size : e->isize;
	e->iscale = (!e->iscale) ? e->scale : e->iscale;
	(code == 69) ? e->size++ : e->size--;
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
	if (code == 87 || code == 82)
	{
		e->rx = (code == 87) ? 0 : 0.9553;
		e->ry = 0;
		e->rz = (code == 87) ? 0 : 5.4978;
		e->xset = 0;
		e->yset = 0;
		e->xshift = 0;
		e->yshift = 0;
		e->size = (!e->isize) ? e->size : e->isize;
		e->scale = (!e->iscale) ? e->scale : e->iscale;
	}
	if (code == 86 || code == 88)
		e->ry = (code == 86) ? e->ry + 0.0873 : e->ry - 0.0873;
	if (code == 84 || code == 91)
		e->rx = (code == 91) ? e->rx + 0.0873 : e->rx - 0.0873;
	if (code == 92 || code == 89)
		e->rz = (code == 92) ? e->rz + 0.0524 : e->rz - 0.0524;
	if (code == 69 || code == 78)
		fdf_key_zoom(code, e);
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
	ft_putendl("action: number pad (mouse)");
	ft_putendl("zoom in: + (scroll up)\t\tzoom out: - (scroll down)");
	ft_putendl("tilt up: 8\t\t\ttilt down: 2");
	ft_putendl("tilt left: 4\t\t\ttilt right: 6");
	ft_putendl("rotate clockwise: 9\t\trotate counter clockwise: 7");
	ft_putendl("move up: (drag up)\t\tmove down: (drag down)");
	ft_putendl("move left: (drag left)\t\tmove right: (drag right)");
	ft_putendl("top view: 5\t\t\tisometric: 0\nexit: esc");
	mlx_hook(e->win, 2, 0, fdf_key_funct, e);
	mlx_hook(e->win, 4, 0, fdf_mouse_funct, e);
	mlx_hook(e->win, 6, 0, fdf_motion_hook, e);
	mlx_hook(e->win, 5, 0, fdf_mouse_release, e);
	return (0);
}
