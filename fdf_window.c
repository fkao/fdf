/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:06:32 by fkao              #+#    #+#             */
/*   Updated: 2017/07/03 16:08:18 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

int		fdf_width_len(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			i++;
			while (*str != ' ' && *str)
				str++;
		}
		else
			str++;
	}
	return (i);
}

t_fdf	*fdf_height_width(t_fdf *e, char *file)
{
	int		ret;
	char	*line;

	e->fd = open(file, O_RDONLY);
	if (e->fd != -1)
	{
		ret = get_next_line(e->fd, &line);
		e->wide = fdf_width_len(line);
		while (ret == 1)
		{
			ret = get_next_line(e->fd, &line);
			if (fdf_width_len(line) != e->wide)
			{
				e->wide = -1;
				break ;
			}
			e->high++;
		}
	}
	close(e->fd);
	return (e);
}

int		*fdf_min_max(t_fdf *e, char *line)
{
	int	*row;
	int	i;

	row = (int*)malloc(sizeof(int) * e->wide);
	i = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || *line == '-')
		{
			row[i] = ft_atoi(line);
			if (row[i] > e->max)
				e->max = row[i];
			if (row[i] < e->min)
				e->min = row[i];
			while (*line != ' ' && *line)
				line++;
			i++;
		}
		else
			line++;
	}
	return (row);
}

t_fdf	*fdf_grab_key(t_fdf *e, char *file)
{
	int		i;
	int		*row;
	char	*line;

	e->file = file;
	e->fd = open(file, O_RDONLY);
	e->key = (int**)malloc(sizeof(int*) * e->high);
	i = 0;
	while (get_next_line(e->fd, &line) == 1)
	{
		row = fdf_min_max(e, line);
		e->key[i++] = row;
	}
	close(e->fd);
	return (e);
}

void	fdf_open_window(t_fdf *e)
{
	int		winx;
	int		winy;
	int		winz;
	int		screen;

	e->mlx = mlx_init();
	e->size = 20;
	screen = e->high-- + e->wide--;
	while (screen > 130)
	{
		e->size /= 2;
		screen /= 2;
	}
	winx = (e->wide + e->high) * e->size * cos(0.524) + e->size * 2;
	winy = (e->wide + e->high) * e->size * sin(0.524) + e->size * 2;
	winz = e->scale * (e->max - e->min);
	e->win = mlx_new_window(e->mlx, winx, winy + winz, e->file);
	if (!e->wide && !e->high)
		mlx_pixel_put(e->mlx, e->win, e->size, e->size, 0x00FFFFFF);
	else
		fils_de_fer(e);
	mlx_key_hook(e->win, fdf_key_funct, e);
	mlx_mouse_hook(e->win, fdf_mouse_funct, e);
	mlx_loop(e->mlx);
	return ;
}
