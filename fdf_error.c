/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <fkao@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 15:55:04 by fkao              #+#    #+#             */
/*   Updated: 2017/07/25 16:13:14 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		fdf_put_error(t_fdf *e)
{
	if (e == 0)
	{
		ft_putstr("usage: ./fdf [file] [zscale] [maxrgb(rrrgggbbb)] ");
		ft_putendl("[minrgb(rrrgggbbb)]");
	}
	else if (e->fd == -1)
		ft_putendl("file error: file cannot be found");
	else if (e->wide == -1)
		ft_putendl("map error: invalid map");
	else if (e->wide == 0)
		ft_putendl("map error: empty map");
	else
		return (0);
	free(e);
	return (1);
}
