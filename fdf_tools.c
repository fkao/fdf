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
