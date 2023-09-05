/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:36 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/05 13:47:11 by naterrie         ###   ########lyon.fr   */
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
	if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H)
		return ;
	((int *)data->mlx.addr)[y * (data->line_length >> 2) + x] = color;
}

void	put_floor_ceiling(t_data *data)
{
	static int	c = -1;
	static int	f = -1;
	int			i;
	int			j;

	if (c == -1)
	{
		c = data->c[0] * 256 * 256 + data->c[1] * 256 + data->c[2];
		f = data->f[0] * 256 * 256 + data->f[1] * 256 + data->f[2];
	}
	i = 0;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			if (i < (SCREEN_H >> 1))
				((int *)data->mlx.addr)[i * (data->line_length >> 2) + j] = c;
			else
				((int *)data->mlx.addr)[i * (data->line_length >> 2) + j] = f;
			j++;
		}
		i++;
	}
}
