/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:31:47 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/17 15:54:38 by naterrie         ###   ########lyon.fr   */
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

double	d_coord(double x, double y, double xy, double yy)
{
	double	i;
	double	j;

	i = x - xy;
	j = y - yy;
	return (sqrt(i * i + j * j));
}

double	closest_x(t_data *data, double x)
{
	int		tempx;
	double	angle;
	//int		posx;
	double	ac;

	angle = 180 + (data->player.angle * 180 / M_PI);
	tempx = data->player.x;
	if (x > 0)
		tempx += 1;
	ac = (data->player.x - tempx) / sin(180 - angle);
	printf("bc = %f angle %f\n", ac, 180 - angle);
	printf("angle = %f ", 180 - angle);
	printf("d = %f\n\n", data->player.x - tempx);
	return (data->player.x);
}

double	try_line(t_data *data, double x, double y)
{
	int	i;
	int	j;

	i = data->player.x;
	j = data->player.y;
	while (0)
	{
		if (x <= 0 || y <= 0 || x >= SCREEN_H || y >= SCREEN_W)
			return (0);
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x0831838;
		i += x;
		j += y;
	}
	return (0);
}

double	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;

	i = data->player.x * MAP_ZOOM;
	j = data->player.y * MAP_ZOOM;
	while (hit_wall(data, i, j) && (x != 0 || y != 0))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x0831838;
		i += x;
		j += y;
	}
	//printf("%f %f\n", i, j);
	return (d_coord(data->player.x * MAP_ZOOM, \
		data->player.y * MAP_ZOOM, i, j));
}

void	raycast(t_data *data)
{
	closest_x(data, data->player.dir_x);
	draw_line(data, data->player.dir_x, data->player.dir_y);
	//printf("%f\n", try_line(data, data->player.dir_x, data->player.dir_y));

}
