/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:35:40 by fkao              #+#    #+#             */
/*   Updated: 2017/06/23 15:44:18 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int		fdf_key_hook(int keycode, t_fdf *map)
{
	ft_putstr("key event: ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	if (keycode == 8)
		map->c = (map->c) ? 0 : 1;
	if (keycode == 34 && map->c)
		map->i = (map->i) ? 0 : 1;
	if (keycode == 15 && map->c)
		map->r = (map->r) ? 0 : 25;
	mlx_clear_window(map->mlx, map->win);
	fils_de_fer(map);
	return (0);
}

int		sign(int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	return (0);
}

void	fdf_draw_line(void *mlx, void *win, t_pts *ord)
{
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	s1;
	int	s2;
	int swap;
	int tmp;
	int	p;
	int	i;

	x = ord->x1;
	y = ord->y1;
	dx = ord->x2 - ord->x1;
	dy = ft_toabsl(ord->y2 - ord->y1);
	s1 = sign(ord->x2 - ord->x1);
	s2 = sign(ord->y2 - ord->y1);
	swap = 0;
	if (dy > dx)
	{
		tmp = dx;
		dx = dy;
		dy = tmp;
		swap = 1;
	}
	p = 2 * dy - dx;
	i = 0;
	while (i < dx)
	{
		mlx_pixel_put(mlx, win, x, y, ord->color - ord->rshift);
		while (p >= 0)
		{
			p = p - 2 * dx;
			if (swap)
				x += s1;
			else
				y += s2;
		}
		p = p + 2*dy;
		if (swap)
			y += s2;
		else
			x += s1;
		i++;
	}
}

void	fdf_draw_down(t_fdf *map, t_pts *ord)
{
	int	i;
	int	j;
	int	z1;
	int z2;
	int	yo;
	int	xbar;
	int ybar;

	i = 0;
	yo = (map->wide * map->size) * sin(0.524) + map->max * map->BUFF;
	while (i < map->wide + 1)
	{
		z1 = map->key[0][i];
		ord->x1 = (i * map->size) * cos(0.524);
		xbar = ord->x1;
		ord->y1 = yo - (i * map->size) * sin(0.524) - (z1 * map->BUFF);
		ybar = yo - (i * map->size) * sin(0.524);
		j = 0;
		while (j < (map->high + 1))
		{
			z2 = map->key[j][i];
			ord = (map->c) ? fdf_expose_color(z1, z2, map, ord) : ord;
			ord->x2 = xbar + (j * map->size) * cos(0.524);
			ord->y2 = ybar + (j * map->size) * sin(0.524) - (z2 * map->BUFF);
			fdf_draw_line(map->mlx, map->win, ord);
			j++;
			ord->y1 = ord->y2;
			ord->x1 = ord->x2;
			z1 = z2;
		}
		i++;
	}
}
void	fils_de_fer(t_fdf *map)
{
	int	i;
	int	j;
	int	z1;
	int	z2;
	int	yo;
	int	xbar;
	int ybar;
	t_pts	*ord;

	i = 0;
	yo = (map->wide * map->size) * sin(0.524) + map->max * map->BUFF;
	ord = (t_pts*)ft_memalloc(sizeof(*ord));
	ord->color = 0x00FFFFFF;
	while (i < map->high + 1)
	{
		z1 = map->key[i][0];
		ord->x1 = (i * map->size) * cos(0.524);
		xbar = ord->x1;
		ord->y1 = yo + (i * map->size) * sin(0.524) - (z1 * map->BUFF);
		ybar = yo + (i * map->size) * sin(0.524);
		j = 0;
		while (j < (map->wide + 1))
		{
			z2 = map->key[i][j];
			ord = (map->c) ? fdf_expose_color(z1, z2, map, ord) : ord;
			ord->x2 = xbar + (j * map->size) * cos(0.524);
			ord->y2 = ybar - (j * map->size) * sin(0.524) - (z2 * map->BUFF);
			fdf_draw_line(map->mlx, map->win, ord);
			j++;
			ord->y1 = ord->y2;
			ord->x1 = ord->x2;
			z1 = z2;
		}
		i++;
	}
	fdf_draw_down(map, ord);
}

void	fdf_open_window(t_fdf *map)
{
	int		winx;
	int		winy;
	int		zeta;

	map->mlx = mlx_init();
	map->wide -= 1;
	map->high -= 1;
	map->size = 20;
	winx = (map->wide + map->high) * map->size * cos(0.524);
	winy = (map->wide + map->high) * map->size * sin(0.524);
	zeta = map->BUFF * (map->max - map->min);
	map->win = mlx_new_window(map->mlx, winx, winy + zeta, "mlx 42");
	fils_de_fer(map);
	mlx_key_hook(map->win, fdf_key_hook, map);
	mlx_loop(map->mlx);
	return ;
}

t_fdf	*fdf_max_min(t_fdf *map, char *file)
{
	int		i;
	int		j;
	int		ret;
	int		*row;
	char	*line;

	map->fd = open(file, O_RDONLY);
	map->key = (int**)malloc(sizeof(int*) * map->high);
	ret = get_next_line(map->fd, &line);
	j = 0;
	while (ret == 1)
	{
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
		map->key[j++] = row;
		ret = get_next_line(map->fd, &line);
	}
	close(map->fd);
	return (map);
}

int		fdf_invalid_key(char *line, int width)
{
	int	len;

	len = fdf_width_len(line);
	if (len != width)
		return (1);
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
			if (fdf_invalid_key(line, map->wide))
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


int		main(int ac, char **av)
{
	t_fdf	*map;

	map = (t_fdf*)ft_memalloc(sizeof(*map));
	map->BUFF = 3;
	if (ac == 3 && ft_isdigit(av[2][0]))
	{
		map->BUFF = ft_atoi(av[2]);
		ac--;
	}
	// if (ac == 3 && ())
	if (ac == 2)
	{
		map = fdf_height_width(map, av[1]);
		if (!(fdf_put_error(map)))
		{
			map = fdf_max_min(map, av[1]);
			fdf_open_window(map);
		}
	}
	else
		ft_putendl("usage: ./fdf [file]");
	return (0);
}
