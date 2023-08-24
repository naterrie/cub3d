/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:21:14 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/24 19:29:57 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_player(t_data *data)
{
	int	i;
	int	j;

	i = -MINI_SIZE;
	while (data->x + i < 0)
		i++;
	while (i < MINI_SIZE && data->map[data->x + i])
	{
		j = -MINI_SIZE;
		while (data->y + j < 0)
			j++;
		while (j < MINI_SIZE && data->map[data->x + i][data->y + j])
		{
			if (data->map[data->x + i][data->y + j] == '1')
				draw_square(data, (i + MINI_SIZE) * MAP_ZOOM, \
					(j + MINI_SIZE) * MAP_ZOOM, 0xFF9E9E9E);
			else if (data->map[data->x + i][data->y + j] == '0')
				draw_square(data, (i + MINI_SIZE) * MAP_ZOOM, \
					(j + MINI_SIZE) * MAP_ZOOM, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	draw_square(data, MINI_SIZE * MAP_ZOOM, MINI_SIZE * MAP_ZOOM, 0x00003399);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	minimap_full(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0xFF9E9E9E);
			else if (data->map[i][j] == '0')
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	draw_square(data, data->x * MAP_ZOOM, data->y * MAP_ZOOM, 0x00003399);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
