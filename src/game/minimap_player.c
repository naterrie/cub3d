/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:38:07 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/31 15:39:11 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	minimap_check(t_data *data, int i, int j, char c)
{
	if (c == 'N')
		if (data->map[(int)data->player.x + i][(int)data->player.y + j])
			return (1);
	if (data->map[(int)data->player.x + i][(int)data->player.y + j] == c)
		return (1);
	return (0);
}

static void	draw_player_mini(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = MINI_SIZE * MAP_ZOOM;
	j = MINI_SIZE * MAP_ZOOM;
	x = 2;
	while (x < MAP_ZOOM - 2)
	{
		y = 2;
		while (y < MAP_ZOOM - 2)
		{
			my_mlx_pixel_put(data, y + j, x + i, 0x00003399);
			y++;
		}
		x++;
	}
}

void	minimap_player(t_data *data)
{
	int	i;
	int	j;

	i = -MINI_SIZE;
	while (data->player.x + i < 0)
		i++;
	while (i < MINI_SIZE && data->map[(int)data->player.x + i])
	{
		j = -MINI_SIZE;
		while (data->player.y + j < 0)
			j++;
		while (j < MINI_SIZE && minimap_check(data, i, j, 'N'))
		{
			if (minimap_check(data, i, j, '1'))
				draw_square(data, (i + MINI_SIZE) * MAP_ZOOM, \
					(j + MINI_SIZE) * MAP_ZOOM, 0xFF9E9E9E);
			else if (minimap_check(data, i, j, '0'))
				draw_square(data, (i + MINI_SIZE) * MAP_ZOOM, \
					(j + MINI_SIZE) * MAP_ZOOM, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	draw_player_mini(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
