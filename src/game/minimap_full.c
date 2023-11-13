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

void	minimap_full(t_data *data)
{
	int		i;
	int		j;
	double	t;

	i = 0;
	data->player.angle_fov = (FOV * (M_PI / 180) / 2);
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
	display_game(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
