/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/23 09:48:30 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_ray_dist_player_side(t_data *data);
void	init_raycasting(t_data *data, int x);
void	dda(t_data *data);

void	display_game(t_data *data)
{
	int		x;

	x = -1;
	while ((++x < SCREEN_W))
	{
		norm_cam_x(data, x);
		init_raycasting(data, x);
		dda(data);
		ray_pos(data);
		put_wall(data, x, wall_height(data->ray, x));
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

void	dda(t_data *data)
{
	while (1)
	{
		if (data->ray.dist_player_to_side.x < data->ray.dist_player_to_side.y)
		{
			data->ray.dist_player_to_side.x += data->ray.step_dist.x;
			data->ray.dda_position.x += data->ray.dda_step.x;
			data->ray.wall = EAST - (data->ray.dda_step.x == 1);
		}
		else
		{
			data->ray.dist_player_to_side.y += data->ray.step_dist.y;
			data->ray.dda_position.y += data->ray.dda_step.y;
			data->ray.wall = NORTH + (data->ray.dda_step.y == 1);
		}
		if (data->parsing.map[data->ray.dda_position.y] \
		[data->ray.dda_position.x] == WALL)
			break ;
	}
}

void	init_raycasting(t_data *data, int x)
{
	data->player.d.x = cos(data->player.angle + data->ray.ray_angle[x]);
	data->player.d.y = sin(data->player.angle + data->ray.ray_angle[x]);
	data->player.fov = t_pos_rotate(data->player.d, degre_to_radian(FOV));
	data->ray.direction.x = data->player.d.x + 0 * data->cam.x;
	data->ray.direction.y = data->player.d.y + 0 * data->cam.x;
	data->ray.dda_position.x = (int)data->player.position.x;
	data->ray.dda_position.y = (int)data->player.position.y;
	if (data->ray.direction.x == 0)
		data->ray.step_dist.x = 1e30;
	else if (data->ray.direction.x > 0)
		data->ray.step_dist.x = 1 / data->ray.direction.x;
	else
		data->ray.step_dist.x = -1 / data->ray.direction.x;
	if (data->ray.direction.y == 0)
		data->ray.step_dist.y = 1e30;
	else if (data->ray.direction.y > 0)
		data->ray.step_dist.y = 1 / data->ray.direction.y;
	else
		data->ray.step_dist.y = -1 / data->ray.direction.y;
	data->player.map.x = data->player.position.x;
	data->player.map.y = data->player.position.y;
	set_ray_dist_player_side(data);
}

void	set_ray_dist_player_side(t_data *data)
{
	if (data->ray.direction.x > 0)
	{
		data->ray.dda_step.x = 1;
		data->ray.dist_player_to_side.x = (data->ray.dda_position.x + 1.0 \
	- data->player.map.x) * data->ray.step_dist.x;
	}
	else
	{
		data->ray.dda_step.x = -1;
		data->ray.dist_player_to_side.x = (data->player.map.x - \
	data->ray.dda_position.x) * data->ray.step_dist.x;
	}
	if (data->ray.direction.y > 0)
	{
		data->ray.dda_step.y = 1;
		data->ray.dist_player_to_side.y = (data->ray.dda_position.y + 1.0 \
	- data->player.map.y) * data->ray.step_dist.y;
	}
	else
	{
		data->ray.dda_step.y = -1;
		data->ray.dist_player_to_side.y = (data->player.map.y \
	- data->ray.dda_position.y) * data->ray.step_dist.y;
	}
}

void	ray_pos(t_data *data)
{
	if (data->ray.wall == WEST || data->ray.wall == EAST)
	{
		data->ray.distance = \
			data->ray.dist_player_to_side.x - data->ray.step_dist.x;
		data->ray.dda_position.y = data->player.position.y + \
	data->ray.distance * data->ray.direction.y;
	}
	else
	{
		data->ray.distance = \
			data->ray.dist_player_to_side.y - data->ray.step_dist.y;
		data->ray.dda_position.x = data->player.position.x + \
		data->ray.distance * data->ray.direction.x;
	}
	data->ray.wall_pos.x = \
		data->player.map.x + data->ray.distance * data->ray.direction.x;
	data->ray.wall_pos.y = \
		data->player.map.y + data->ray.distance * data->ray.direction.y;
	data->ray.ray_len = ray_len(data->player.map, data->ray.wall_pos);
}
