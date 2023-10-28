/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:34:56 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/10/23 14:16:50 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# include <math.h>

// Fonction DDA pour le lancer de rayons
t_pos dda(t_data *data, t_pos dest) 
{
    t_pos map = data->player.position;
    // dest = point d'arrivé
    //distance entre pos du player et point d'arrivé
    t_vector2_f dir = {dest.x - data->player.position.x, dest.y - data->player.position.y};
    t_vector2_f side_dist;
    t_vector2_f delta_dist;
	delta_dist.x = fabs(1 / dir.x);
	delta_dist.y = fabs(1 / dir.y);

    t_vector2_d step;

    if (data->player.direction.x < 0)
    {
        step.x = -1;
        side_dist.x = (data->player.position.x - map.x) * delta_dist.x;
    } else
    {
        step.x = 1;
        side_dist.x = (map.x + 1.0f - data->player.position.x) * delta_dist.x;
    }

    if (data->player.direction.y < 0)
    {
        step.y = -1;
        side_dist.y = (data->player.position.y - map.y) * delta_dist.y;
    } else
    {
        step.y = 1;
        side_dist.y = (map.y + 1.0f - data->player.position.y) * delta_dist.y;
    }
    while (1) 
    {
        if (side_dist.x < side_dist.y) 
        {
            side_dist.x += delta_dist.x;
            map.x += step.x;
        } else 
        {
            side_dist.y += delta_dist.y;
            map.y += step.y;
        }
        // //t_vector2_d cell = {map.x / MAP_ZOOM, map.y / MAP_ZOOM};

        // dprintf(2, "pos.x %f pos.y %f \n", data->player.position.x, data->player.position.y);
        // dprintf(2, "map.x %d map.y %d \n", (int)map.x / MAP_ZOOM, (int)map.y / MAP_ZOOM);
        my_mlx_pixel_put(data, map.x, map.y, 0x0099FFFF);
        if (data->parsing.map[(int)map.y / MAP_ZOOM][(int)map.x / MAP_ZOOM] == '1') 
            return (t_pos){map.x, map.y};
    }
    return (t_pos){map.x, map.y};
}