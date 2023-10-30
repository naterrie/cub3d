/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:31:47 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/30 18:19:03 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hit_wall(t_data *data, int i, int j)
{
	int	x;

	x = 0;
	while (data->parsing.map[x])
		x++;
	x *= MAP_ZOOM;
	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
		return (0);
	if (i < x && data->parsing.map[(int)floor(i) / MAP_ZOOM][(int)floor(j) \
		/ MAP_ZOOM] && (int)floor(j) / MAP_ZOOM < \
		ft_strlen(data->parsing.map[(int)floor(i) / MAP_ZOOM]))
		if (data->parsing.map[(int)floor(i) / \
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

double	closest_x(t_data *data, double x, double angle)
{
	int		tempx;
	double	anglec;
	double	bc;
	double	ac;
	double	anglea;

	anglec = 90 + (angle * 180 / M_PI);
	if (anglec < -90)
		anglec = 180 - anglec;
	if (anglec > 90 || anglec < -90)
		anglec = 270 + (angle * 180 / M_PI);
	if (anglec < 0)
		anglec = -anglec;
	anglea = 90 - anglec;
	tempx = data->player.position.x;
	if (x > 0)
		tempx += 1;
	bc = data->player.position.x - tempx;
	if (bc < 0)
		bc = -bc;
	ac = bc / sin(anglea * M_PI / 180);
	printf("angle C = %f\n", anglec);
	return (data->player.position.x);
}

double	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;

	i = data->player.position.x * MAP_ZOOM;
	j = data->player.position.y * MAP_ZOOM;
	while (hit_wall(data, i, j) && (x != 0 || y != 0))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x0831838;
		i += x;
		j += y;
	}
	return (d_coord(data->player.position.x * MAP_ZOOM, \
		data->player.position.y * MAP_ZOOM, i, j));
}

void	raycast(t_data *data)
{
	int	i;

	i = 0;
	while (i < SCREEN_W)
	{
		closest_x(data, data->player.direction.x, data->player.angle);
		draw_line(data, data->player.direction.x, data->player.direction.y);
		i++;
	}
}
