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

static int	hit_wall(t_data *data, int i, int j);
static double	draw_line(t_data *data, double angle_fov);

void	minimap_full(t_data *data)
{
	int		i;
	int		j;
	double	ray_cast;

	i = 0;
	data->player.angle_fov = (FOV * (M_PI / 180) / 2);
	while (data->parsing.map[i])
	{
		j = 0;
		while (data->parsing.map[i][j])
		{
			if (data->parsing.map[i][j] == WALL)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0xFF9E9E9E);
			else if (data->parsing.map[i][j] == EMPTY)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	//calculer correctemeent l'angle a incrementer pour qu'il est la meme distance. si non on va avoir une vue plongante.
	ray_cast = -data->player.angle_fov;
	i = 0;
	while (i < SCREEN_H)
	{
		draw_line(data, ray_cast);
		ray_cast += data->player.angle_fov / (SCREEN_H * 0.5);
		i++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

static int	hit_wall(t_data *data, int i, int j)
{
	int	x;

	x = 0;
	while (data->parsing.map[x])
		x++;
	x *= MAP_ZOOM;
	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
		return (0);
	if (i < x && data->parsing.map[(int)floor(i) / MAP_ZOOM] \
	[(int)floor(j) / MAP_ZOOM] && (int)floor(j) / MAP_ZOOM < \
	ft_strlen(data->parsing.map[(int)floor(i) / MAP_ZOOM]))
		if (data->parsing.map[(int)floor(i) / MAP_ZOOM] \
		[(int)floor(j) / MAP_ZOOM] == '1')
			return (0);
	return (1);
}

double d_coord(double x, double y, double i, double j)
{
	double	k;
	double	l;

	k = x - i;
	l = y - j;
	return (sqrt(k * k + l * l));
}

double	draw_line(t_data *data, double angle_fov)
{
	double	i;
	double	j;
	double	new_x;
	double	new_y;
	int		step;

	i = data->player.position.x;
	j = data->player.position.y;
	data->player.dx = cos(data->player.angle + angle_fov);
	data->player.dy = sin(data->player.angle + angle_fov);
	step = 1;
	new_x = 0;
	new_y = 0;
	while (hit_wall(data, j, i))
	{
		new_x += step * data->player.dx;
		new_y += step * data->player.dy;
		my_mlx_pixel_put(data, data->player.position.x + \
		new_x, data->player.position.y + new_y, 0x00FF66FF);
		i += data->player.dx;
		j += data->player.dy;
	}
	return (d_coord(data->player.position.x * MAP_ZOOM, data->player.position.y * MAP_ZOOM, i, j));
}

