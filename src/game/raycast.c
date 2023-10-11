/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:31:47 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/11 16:45:58 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

double	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;
	double	it;
	double	jt;

	i = data->player.x * MAP_ZOOM;
	j = data->player.y * MAP_ZOOM;
	while (hit_wall(data, i, j) && (x != 0 || y != 0))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x00990033;
		it = i;
		jt = j;
		i += x;
		j += y;
		if (it == i && jt == j)
			return (0);
	}
	if (i > SCREEN_H || j > SCREEN_W || i < 0 || j < 0)
		return (0);
	if (x == 0.000000)
		return (i);
	else if (y == 0.000000)
		return (j);
	return (0);
}

int	closer_separation(t_data *data, double x, double y)
{
	int		d;

	d = 0;
	printf("Wall y %f y %f\n", draw_line(data, x, 0), data->player.y * 10);
	printf("Wall x %f x %f\n", draw_line(data, 0, y), data->player.x * 10);
	return (d);
}

void	raycast(t_data *data)
{
	int	d;

	draw_line(data, data->player.dir_x, data->player.dir_y);
	d = closer_separation(data, data->player.dir_x, data->player.dir_y);
}
