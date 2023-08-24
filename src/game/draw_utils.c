/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:36 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/24 19:06:59 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_ZOOM)
	{
		j = 0;
		while (j < MAP_ZOOM)
		{
			my_mlx_pixel_put(data, y + j, x + i, color);
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_floor_ceiling(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			if (i < SCREEN_H / 2)
				my_mlx_pixel_put(data, j, i, data->c[0] * 256 * 256 + \
						data->c[1] * 256 + data->c[2]);
			else
				my_mlx_pixel_put(data, j, i, data->f[0] * 256 * 256 + \
						data->f[1] * 256 + data->f[2]);
			j++;
		}
		i++;
	}
	printf("%d\n", i);
}
