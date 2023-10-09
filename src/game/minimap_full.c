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

static void	draw_player_full(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = data->player.x * MAP_ZOOM - 5;
	j = data->player.y * MAP_ZOOM - 5;
	x = 2;
	while (x < MAP_ZOOM - 2)
	{
		y = 2;
		while (y < MAP_ZOOM - 2)
		{
			if (i >= 0 && j >= 0 && i < SCREEN_H && j < SCREEN_W)
				((int *)data->mlx.addr)[(x + i) * \
				(data->line_length >> 2) + (y + j)] = 0x00003399;
			y++;
		}
		x++;
	}
}

static int	hit_wall(t_data *data, int i, int j)
{
	int	x;

	x = 0;
	while (data->map[x])
		x++;
	x *= MAP_ZOOM;
	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
		return (0);
	if (i < x && data->map[(int)floor(i) / MAP_ZOOM][(int)floor(j) \
		/ MAP_ZOOM] && (int)floor(j) / MAP_ZOOM < \
		ft_strlen(data->map[(int)floor(i) / MAP_ZOOM]))
		if (data->map[(int)floor(i) / \
				MAP_ZOOM][(int)floor(j) / MAP_ZOOM] == '1')
			return (0);
	return (1);
}

static void	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;

	i = data->player.x * MAP_ZOOM;
	j = data->player.y * MAP_ZOOM;
	while (hit_wall(data, i, j) && (x != 0 || y != 0))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x00003399;
		i += x;
		j += y;
	}
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
	draw_line(data, data->player.dir_x, data->player.dir_y);
	draw_player_full(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
