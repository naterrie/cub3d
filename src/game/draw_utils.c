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
			if (!(x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H))
				((int *)data->mlx.addr)[(x + i) * \
				(data->line_length >> 2) + (y + j)] = color;
			j++;
		}
		i++;
	}
}

void	put_floor_ceiling(t_data *data)
{
	int			i;
	int			j;

	i = 0;
	while (i < SCREEN_H)
	{
		j = 0;
		while (j < SCREEN_W)
		{
			if (i < (SCREEN_H >> 1))
				((int *)data->mlx.addr)[i * \
				(data->line_length >> 2) + j] = data->ceil;
			else
				((int *)data->mlx.addr)[i * \
				(data->line_length >> 2) + j] = data->floor;
			j++;
		}
		i++;
	}
}
