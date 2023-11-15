/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/11 12:09:16 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_ray_dist_player_side(t_data *data, t_ray *ray);
void	init_raycasting(t_data *data, t_ray *ray);
void	dda(t_data *data, t_ray *ray);
void	ray_pos(t_ray *ray, t_data *data);

void	display_game(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 1;
	ft_bzero(&ray, sizeof(t_ray));
	ray.ray_angle = -data->player.angle_fov;
	while ((++x < SCREEN_W))
	{
		norm_cam_x(data, x);
		init_raycasting(data, &ray);
		dda(data, &ray);
		ray_pos(&ray, data);
		wall_height(&ray);
		put_wall(data, x, wall_height(&ray));
		ray.ray_angle += data->player.angle_fov / (SCREEN_W * 0.5);
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	dda(t_data *data, t_ray *ray)
{
	while (1)
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
		if (data->parsing.map[ray->dda_position.y] \
		[ray->dda_position.x] == WALL)
			break ;
	}
}

void	init_raycasting(t_data *data, t_ray *ray)
{
	data->player.d.x = cos(data->player.angle + ray->ray_angle);
	data->player.d.y = sin(data->player.angle + ray->ray_angle);
	data->player.fov = t_pos_rotate(data->player.d, degre_to_radian(FOV));
	ray->direction.x = data->player.d.x + 0 * data->cam.x;
	ray->direction.y = data->player.d.y + 0 * data->cam.x;
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

void	set_ray_dist_player_side(t_data *data, t_ray *ray)
{
	if (ray->direction.x > 0)
	{
		ray->dda_step.x = 1;
		ray->dist_player_to_side.x = (ray->dda_position.x + 1.0 \
	- data->player.map.x) * ray->step_dist.x;
	}
	else
	{
		ray->dda_step.x = -1;
		ray->dist_player_to_side.x = (data->player.map.x - \
	ray->dda_position.x) * ray->step_dist.x;
	}
	if (ray->direction.y > 0)
	{
		ray->dda_step.y = 1;
		ray->dist_player_to_side.y = (ray->dda_position.y + 1.0 \
	- data->player.map.y) * ray->step_dist.y;
	}
	else
	{
		ray->dda_step.y = -1;
		ray->dist_player_to_side.y = (data->player.map.y \
	- ray->dda_position.y) * ray->step_dist.y;
	}
}

void	ray_pos(t_ray *ray, t_data *data)
{
	if (ray->wall == WEST || ray->wall == EAST)
	{
		ray->distance = ray->dist_player_to_side.x - ray->step_dist.x;
		ray->dda_position.y = data->player.position.y + \
	ray->distance * ray->direction.y;
	}
	else
	{
		ray->distance = ray->dist_player_to_side.y - ray->step_dist.y;
		ray->dda_position.x = data->player.position.x + \
	ray->distance * ray->direction.x;
	}
	ray->wall_pos.x = data->player.map.x + ray->distance * ray->direction.x;
	ray->wall_pos.y = data->player.map.y + ray->distance * ray->direction.y;
	ray->ray_len = ray_len(data->player.map, ray->wall_pos);
}
