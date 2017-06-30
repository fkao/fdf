/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:11:23 by fkao              #+#    #+#             */
/*   Updated: 2017/06/29 17:42:27 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_width_len(char *str)
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

int	fdf_put_error(t_fdf *map)
{
	if (map == 0)
	{
		ft_putstr("usage: ./fdf [file][maxrgb(rrrgggbbb)] [minrgb(rrrgggbbb)]");
		ft_putendl(" [zscale]");
	}
	else if (map->fd == -1)
		ft_putendl("error: file cannot be found");
	else if (map->wide == 0)
		ft_putendl("map error: empty map");
	else if (map->wide == -1)
		ft_putendl("map error: invalid map");
	else
		return (0);
	return (1);
}

int	fdf_check_rgb(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
