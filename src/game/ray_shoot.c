/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shoot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:54:42 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/09 16:51:45 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ray_len(t_double src, t_double dest)
{
	double	res_x;
	double	res_y;
	double	res_final;

	res_x = (src.x - dest.x);
	res_y = (src.y - dest.y);
	res_final = ((res_x * res_x) + (res_y * res_y));
	res_final = sqrt(res_final);
	return (res_final * MAP_ZOOM);
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
		ray->distance =  ray->dist_player_to_side.y - ray->step_dist.y;
		ray->dda_position.x = data->player.position.x + \
	ray->distance * ray->direction.x;
	}
	ray->wall_pos.x = data->player.map.x + ray->distance * ray->direction.x;
	ray->wall_pos.y = data->player.map.y + ray->distance * ray->direction.y;
	ray->ray_len = ray_len(data->player.map, ray->wall_pos);
}

void	set_ray_dist_player_side(t_data *data, t_ray *ray)
{
	if (ray->direction.x < 0)
	{
		ray->dda_step.x = -1;
		ray->dist_player_to_side.x
			= (data->player.map.x - ray->dda_position.x) * ray->step_dist.x;
	}
	else
	{
		ray->dda_step.x = 1;
		ray->dist_player_to_side.x = \
		(ray->dda_position.x + 1.0 - data->player.map.x) * ray->step_dist.x;
	}
	if (ray->direction.y < 0)
	{
		ray->dda_step.y = -1;
		ray->dist_player_to_side.y
			= (data->player.map.y - ray->dda_position.y) * ray->step_dist.y;
	}
	else
	{
		ray->dda_step.y = 1;
		ray->dist_player_to_side.y
			= (ray->dda_position.y + 1.0 \
			- data->player.map.y) * ray->step_dist.y;
	}
}
