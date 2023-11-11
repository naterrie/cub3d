/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 09:24:55 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/11/11 12:11:59 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double ray_len(t_pos src, t_pos dest)
{
	t_pos	tmp;
    double  result;

    tmp.x = (src.x - dest.x);
    tmp.y = (src.y - dest.y);
    result = (tmp.x * tmp.x + tmp.y * tmp.y);
    result = sqrt(result);
    return (result * MAP_ZOOM);
}

void    norm_cam_x(t_data *data, double x)
{
    data->cam.x = 2.0 * x / SCREEN_W - 1;
}

double	degre_to_radian(double angle)
{
	return (angle * (M_PI / 180));
}

t_pos	t_pos_rotate(t_pos dir, double fov)
{
	return ((t_pos){cos(fov) * dir.x + -sin(fov) * dir.y, \
		sin(fov) * dir.x + cos(fov) * dir.y});
}

void	wall_height(t_ray *ray)
{
	int		line_height;
	int		len_wall;

	line_height = SCREEN_H / ray->distance;
	if (line_height > SCREEN_H)
		len_wall = SCREEN_H ;
	else
		len_wall = line_height;
	printf("taille du mur %d", len_wall);
}