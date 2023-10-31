/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:31:47 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/31 16:50:10 by naterrie         ###   ########lyon.fr   */
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

/* Angles x par rapport a l'angle originale =
	90 && 270
	Donc separation a 0 et 180
*/

double	closest_x(t_data *data, double angle)
{
	double	cosa;
	double	y;
	double	x;

	(void)data;
	x = 1;
	cosa = cos(angle);
	printf("cosa %f\n", angle);
	if (!cosa)
		return (0);
	if ((angle > 0 && angle < 180) || (angle > -0 && angle < -180))
		x = -1;
	y = x * tan(angle);
	printf("y %f, x %f\n", y, x);
	return (angle);
}

double	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;

	i = data->player.position.y;
	j = data->player.position.x;
	while (hit_wall(data, i, j) && (x != 0 || y != 0))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x0000000;
		i += x;
		j += y;
	}
	return (d_coord(data->player.position.x * MAP_ZOOM, \
		data->player.position.y * MAP_ZOOM, i, j));
}

// static void	get_ray_dir(t_data *data, t_dda *dda, int i)
// {
// 	double	cam;

// 	cam = 2 * i / SCREEN_W - 1;
// 	dda->ray.x = data->player.direction.x + 0 * cam;
// 	dda->ray.y = data->player.direction.y + 0 * cam;
// }

void	raycast(t_data *data)
{
	int		i;
	// t_dda	dda;

	i = 1;
	// while (i < SCREEN_W)
	// {
		// get_ray_dir(data, &dda, i);
		printf ("%f\n", closest_x(data, data->player.angle * 180 / M_PI));
		draw_line(data, data->player.direction.y, data->player.direction.x);
		//draw_line(data, dda.ray.y, dda.ray.x);
	// 	i++;
	// }
}
