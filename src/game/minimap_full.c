/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:21:14 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/06 16:42:33 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(t_data *data)
{
	int	i;
	int	j;

	i = -MINI_SIZE;
	while (i < MINI_SIZE)
	{
		j = -MINI_SIZE;
		while (j < MINI_SIZE)
		{
			if (i == 0 && j == 0)
				draw_square(data, (data->player.position.y - 0.5) * MAP_ZOOM \
					, (data->player.position.x - 0.5) * MAP_ZOOM, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	minimap_full(t_data *data)
{
	int		i;
	int		j;
	double	t;

	i = 0;
	while (data->parsing.map[i])
	{
		j = -1;
		while (data->parsing.map[i][++j])
		{
			if (data->parsing.map[i][j] == WALL)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0xFF9E9E9E);
			else if (data->parsing.map[i][j] == EMPTY)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0x00FFFFFF);
		}
		i++;
	}
	t = (double)FOV * (M_PI / 180);
	data->player.fov.x = cosf(t) * data->player.direction.x \
		+ -sinf(t) * data->player.direction.y;
	data->player.fov.y = sinf(t) * data->player.direction.x \
		+ cosf(t) * data->player.direction.x;
	draw_player(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
