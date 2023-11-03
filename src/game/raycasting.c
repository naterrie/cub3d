/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/03 13:58:18 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_raycasting(t_data *data, t_ray *ray)
{
	ray->direction.x = data->player.direction.x + 0 * data->cam.x;
	ray->direction.y = data->player.direction.y + 0 * data->cam.x;
	ray->dda_position.x = (int)data->player.position.x / MAP_ZOOM;
	ray->dda_position.y = (int)data->player.position.y / MAP_ZOOM;
	if (ray->direction.x == 0)
		ray->step_dist.x = 1e30;
	else if (ray->direction.x > 0)
		ray->step_dist.x = 1 / ray->direction.x;
	else
		ray->step_dist.x = -1 / ray->direction.x;
	if (ray->direction.y == 0)
		ray->step_dist.y = 1e30;
	else if (ray->direction.y > 0)
		ray->step_dist.y = 1 / ray->direction.y;
	else
		ray->step_dist.y = -1 / ray->direction.y;
	data->player.map.x = data->player.position.x / MAP_ZOOM;
	data->player.map.y = data->player.position.y / MAP_ZOOM;
	set_ray_dist_player_side(data, ray);
}

static void	dda(t_data *data, t_ray *ray)
{
	t_bool	hit;

	hit = FALSE;
	while (hit == 0)
	{
		if (ray->dist_player_to_side.x < ray->dist_player_to_side.y)
		{
			ray->dist_player_to_side.x += ray->step_dist.x;
			ray->dda_position.x += ray->dda_step.x;
			ray->wall = EAST - (ray->dda_step.x == 1);
		}
		else
		{
			ray->dist_player_to_side.y += ray->step_dist.y;
			ray->dda_position.y += ray->dda_step.y;
			ray->wall = NORTH + (ray->dda_step.y == 1);
		}
		if (data->parsing.map[ray->dda_position.y][ray->dda_position.x] == WALL)
			break ;
	}
}

void	draw_line(t_data *data, t_ray *ray, double angle_fov)
{
	double	new_x;
	double	new_y;
	int		step;
	int		len;

	data->player.d.x = cos(data->player.angle + angle_fov);
	data->player.d.y = sin(data->player.angle + angle_fov);
	step = 1;
	new_x = 0;
	new_y = 0;
	len = 0;
	while (len < ray->ray_len)
	{
		my_mlx_pixel_put(data, data->player.position.x \
		+ new_x, data->player.position.y + new_y, 0x00FF66FF);
		new_x += step * data->player.d.x;
		new_y += step * data->player.d.y;
		len++;
	}
}

void	display_game(t_data *data)
{
	double	x;
	t_ray	ray;

	x = 0;
	ft_bzero(&ray, sizeof(t_ray));
	ray.ray_angle = -data->player.angle_fov;
	while (++x < SCREEN_W)
	{
		data->cam.x = 2 * x / SCREEN_W - 1;
		init_raycasting(data, &ray);
		dda(data, &ray);
		ray_pos(&ray, data);
		draw_line(data, &ray, 0);
		ray.ray_angle += data->player.angle_fov / (SCREEN_H * 0.5);
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
