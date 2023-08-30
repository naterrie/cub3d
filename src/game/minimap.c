/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:21:14 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/30 18:50:51 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	draw_player_full(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = data->player.x * MAP_ZOOM - 4;
	j = data->player.y * MAP_ZOOM - 4;
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

static int	minimap_check(t_data *data, int i, int j, char c)
{
	if (c == 'N')
		if (data->map[(int)data->player.x + i][(int)data->player.y + j])
			return (1);
	if (data->map[(int)data->player.x + i][(int)data->player.y + j] == c)
		return (1);
	return (0);
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
	draw_player_full(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
