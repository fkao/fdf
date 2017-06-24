/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:11:23 by fkao              #+#    #+#             */
/*   Updated: 2017/06/23 15:06:22 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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

int		fdf_put_error(t_fdf *map)
{
	if (map->fd == -1)
		ft_putendl("error: file cannot be found");
	else if (map->wide == 0)
		ft_putendl("map error: empty map");
	else if (map->wide == -1)
		ft_putendl("map error: invalid map");
	else
		return (0);
	return (1);
}

void	printkey(t_fdf *map)
{
	int		i;
	int		j;

	printf("%d\n", map->max);
	printf("%d\n", map->min);
	i = 0;
	while (i < map->high)
	{
		j = 0;
		while (j < map->wide)
		{
			printf("%4d", map->key[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int		fdf_rgb_hex2(int z)
{
	int		rgbhex;

	if (z <= 0)
		rgbhex = 0x00FFFFFF;
	if (z == -1)
		rgbhex = 0x00E0F2FF;
	if (z == -2)
		rgbhex = 0x00C9E8FF;
	if (z == -3)
		rgbhex = 0x00AFDEFF;
	if (z == -4)
		rgbhex = 0x0096D3FF;
	if (z == -5)
		rgbhex = 0x007CC8FF;
	if (z == -6)
		rgbhex = 0x0063B5FF;
	if (z == -7)
		rgbhex = 0x004CB4FF;
	if (z == -8)
		rgbhex = 0x0032A9FF;
	if (z == -9)
		rgbhex = 0x00199FFF;
	if (z <= -10)
		rgbhex = 0x000096FF;
	return (rgbhex);
}

int		fdf_rgb_hex(int z)
{
	int		rgbhex;

	if (z <= 0)
		return (fdf_rgb_hex2(z));
	if (z == 1)
		rgbhex = 0x00F2E0FF;
	if (z == 2)
		rgbhex = 0x00E8C9FF;
	if (z == 3)
		rgbhex = 0x00DEAFFF;
	if (z == 4)
		rgbhex = 0x00D396FF;
	if (z == 5)
		rgbhex = 0x00C87CFF;
	if (z == 6)
		rgbhex = 0x00B563FF;
	if (z == 7)
		rgbhex = 0x00B44CFF;
	if (z == 8)
		rgbhex = 0x00A932FF;
	if (z == 9)
		rgbhex = 0x009F19FF;
	if (z >= 10)
		rgbhex = 0x009600FF;
	return (rgbhex);
}

t_pts	*fdf_expose_color(int z1, int z2, t_fdf *map, t_pts *ord)
{
	if (map->i)
	{
		if (z1 == 0)
			z1 = (map->min) ? map->min : 10;
		else
			z1 = (z1 > 0) ? map->max - z1 : map->min - z1;
		if (z2 == 0)
			z2 = (map->min) ? map->min : 10;
		else
		z2 = (z2 > 0) ? map->max - z2 : map->min - z2;
	}
	if (z2 < z1)
	{
		ord->rshift = map->r * ((ft_toabsl(z1) < 10) ? ft_toabsl(z1) : 10);
		ord->color = fdf_rgb_hex(z1);
	}
	else
	{
		ord->rshift = map->r * ((ft_toabsl(z2) < 10) ? ft_toabsl(z2) : 10);
		ord->color = fdf_rgb_hex(z2);
	}
	return (ord);
}
