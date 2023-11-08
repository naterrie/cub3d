/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/08 19:49:24 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    norm_cam_x(t_data *data, double x)
{
    data->cam.x = 2.0 * x / SCREEN_W - 1;
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

double	degre_to_radian(double angle)
{
	return (angle * (M_PI / 180));
}

double	angle_to_degre(double angle)
{
	return (angle * (180 / M_PI));
}

t_pos	t_pos_rotate(t_pos co, double t)
{
	return ((t_pos){cos(t) * co.x + -sin(t) * co.y, \
		sin(t) * co.x + cos(t) * co.y});
}

void	init_raycasting(t_data *data, t_ray *ray)
{
	data->player.angle_degre = angle_to_degre(data->player.angle);
	data->player.angle_radian = degre_to_radian(data->player.angle_degre);
	data->player.d.x = cos(data->player.angle_radian + ray->ray_angle);
	data->player.d.y = sin(data->player.angle_radian + ray->ray_angle);
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


void	dda(t_data *data, t_ray *ray)
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
		if (data->parsing.map[ray->dda_position.y] \
		[ray->dda_position.x] == WALL)
            break ;
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

double ray_len(t_pos src, t_pos dest)
{
	t_pos	result;
    double  res_final;

    result.x = (src.x - dest.x);
    result.y = (src.y - dest.y);
    res_final = (result.x * result.x + result.y * result.y);
    res_final = sqrt(res_final);
    return (res_final * MAP_ZOOM);
}

void    ray_pos(t_ray   *ray, t_data *data)
{
    if (ray->wall == WEST || ray->wall == EAST)
	{
        ray->distance =  ray->dist_player_to_side.x - ray->step_dist.x;
        ray->dda_position.y = data->player.position.y + \
	ray->distance * ray->direction.y;
	}
	else
	{
        ray->distance =  ray->dist_player_to_side.y - ray->step_dist.y;
        ray->dda_position.x = data->player.position.x + \
	ray->distance * ray->direction.x;
	}
    ray->wall_pos.x = data->player.map.x + ray->distance * ray->direction.x;
    ray->wall_pos.y = data->player.map.y + ray->distance * ray->direction.y;
    ray->ray_len = ray_len(data->player.map, ray->wall_pos);
}

void	display_game(t_data *data)
{
	double	x;
	t_ray	ray;

	x = 1;
	ft_bzero(&ray, sizeof(t_ray));
    ray.ray_angle = -data->player.angle_fov;
	while (++x < SCREEN_W)
	{
		norm_cam_x(data, x);
		init_raycasting(data, &ray);
		dda(data, &ray);
        ray_pos(&ray, data);
        draw_line(data, &ray);
        ray.ray_angle += data->player.angle_fov / (SCREEN_H * 0.5);
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

