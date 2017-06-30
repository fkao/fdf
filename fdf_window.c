/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 17:06:32 by fkao              #+#    #+#             */
/*   Updated: 2017/06/29 17:25:54 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

int		fdf_key_bonus(int keycode, t_fdf *map)
{
	float theta;

	if (keycode == 15 || keycode == 5 || keycode == 11)
		fdf_key_tint(keycode, map);
	else
	{
		theta = atan(map->scale / map->size);
		if (keycode == 126)
			map->tilt -= 0.01746;
		if (keycode == 125)
			map->tilt += 0.01746;
		if (keycode == 24 || keycode == 27)
		{
			(keycode == 24) ? map->size++ : map->size--;
			map->scale = tan(theta) * map->size;
			mlx_destroy_window(map->mlx, map->win);
			fdf_open_window(map);
		}
		mlx_clear_window(map->mlx, map->win);
		fils_de_fer(map);
	}
	return (0);
}

t_fdf	*fdf_height_width(t_fdf *map, char *file)
{
	int		ret;
	char	*line;

	map->fd = open(file, O_RDONLY);
	if (map->fd != -1)
	{
		ret = get_next_line(map->fd, &line);
		map->wide = fdf_width_len(line);
		while (ret == 1)
		{
			ret = get_next_line(map->fd, &line);
			if (fdf_width_len(line) != map->wide)
			{
				map->wide = -1;
				break ;
			}
			map->high++;
		}
	}
	close(map->fd);
	return (map);
}

int		*fdf_min_max(t_fdf *map, char *line)
{
	int	*row;
	int	i;

	row = (int*)malloc(sizeof(int) * map->wide);
	i = 0;
	while (*line)
	{
		if (ft_isdigit(*line) || *line == '-')
		{
			row[i] = ft_atoi(line);
			if (row[i] > map->max)
				map->max = row[i];
			if (row[i] < map->min)
				map->min = row[i];
			while (*line != ' ' && *line)
				line++;
			i++;
		}
		else
			line++;
	}
	return (row);
}

t_fdf	*fdf_grab_key(t_fdf *map, char *file)
{
	int		i;
	int		*row;
	char	*line;

	map->fd = open(file, O_RDONLY);
	map->key = (int**)malloc(sizeof(int*) * map->high);
	i = 0;
	while (get_next_line(map->fd, &line) == 1)
	{
		row = fdf_min_max(map, line);
		map->key[i++] = row;
	}
	close(map->fd);
	return (map);
}

void	fdf_open_window(t_fdf *map)
{
	int		screen;
	int		winx;
	int		winy;
	int		zeta;

	map->mlx = mlx_init();
	if (!map->size)
	{
		map->size = 20;
		screen = map->high-- + map->wide--;
		while (screen > 130)
		{
			map->size /= 2;
			screen /= 2;
		}
	}
	winx = (map->wide + map->high) * map->size * cos(0.524) + map->size * 2;
	winy = (map->wide + map->high) * map->size * sin(0.524) + map->size * 2;
	zeta = map->scale * (map->max - map->min);
	map->win = mlx_new_window(map->mlx, winx, winy + zeta, "mlx 42");
	if (!map->wide && !map->high)
		mlx_pixel_put(map->mlx, map->win, map->size, map->size, 0x00FFFFFF);
	else
		fils_de_fer(map);
	mlx_key_hook(map->win, fdf_key_funct, map);
	mlx_loop(map->mlx);
	return ;
}
