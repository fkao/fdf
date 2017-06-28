/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/27 12:05:12 by fkao              #+#    #+#             */
/*   Updated: 2017/06/27 15:14:06 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_rgb_contrast(int z)
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
		return (fdf_rgb_contrast(z));
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

t_plot	*fdf_expose_color(int z1, int z2, t_fdf *map, t_plot *wire)
{
	int	rshift;

	if (z2 < z1)
	{
		rshift = map->r * ((ft_toabsl(z1) < 10) ? ft_toabsl(z1) : 10);
		wire->color = fdf_rgb_hex(z1);
	}
	else
	{
		rshift = map->r * ((ft_toabsl(z2) < 10) ? ft_toabsl(z2) : 10);
		wire->color = fdf_rgb_hex(z2);
	}
	wire->color -= rshift;
	return (wire);
}
