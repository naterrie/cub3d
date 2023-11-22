/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:24:55 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/22 19:03:50 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ray_len(t_double src, t_double dest)
{
	t_double	tmp;
	double		result;

	tmp.x = (src.x - dest.x);
	tmp.y = (src.y - dest.y);
	result = (tmp.x * tmp.x + tmp.y * tmp.y);
	result = sqrt(result);
	return (result * MAP_ZOOM);
}

void	norm_cam_x(t_data *data, double x)
{
	data->cam.x = 2.0 * x / SCREEN_W - 1;
}

double	degre_to_radian(double angle)
{
	return (angle * (M_PI / 180));
}

t_double	t_pos_rotate(t_double dir, double fov)
{
	return ((t_double){cos(fov) * dir.x + -sin(fov) * dir.y, \
		sin(fov) * dir.x + cos(fov) * dir.y});
}

int	wall_height(t_ray ray, int i)
{
	return (SCREEN_H / (ray.distance * cos(ray.ray_angle[i])));
}
