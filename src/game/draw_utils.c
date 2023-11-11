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

void	my_mlx_pixel_put(t_data	*data, int x, int y, int color)
{
	if (x < 0 || y < 0)
		return ;
	((int *)data->mlx.addr)[(y) * (data->line_length >> 2) + (x)] = color;
}

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
				(data->line_length >> 2) + j] = data->parsing.ceil;
			else
				((int *)data->mlx.addr)[i * \
				(data->line_length >> 2) + j] = data->parsing.floor;
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *data, t_ray *ray)
{
	t_pos	new;
	int		step;
    int     len;

	step = 1;
	new.x = 0;
	new.y = 0;
    len = 0;
	while (len < ray->ray_len)
	{
		my_mlx_pixel_put(data, data->player.position.x + new.x, \
	data->player.position.y + new.y, 0x00FF66FF);
		new.x += step * data->player.d.x;
		new.y += step * data->player.d.y;
        len++;
	}
}