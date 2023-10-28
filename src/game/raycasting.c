/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/10/28 18:00:41 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//utils raycast
void    norm_cam_x(t_data *data, double x)
{
    data->cam.x = 2 * x / SCREEN_W - 1;
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
		ray->dist_player_to_side.x
			= (ray->dda_position.x + 1.0 - data->player.map.x) * ray->step_dist.x;
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
			= (ray->dda_position.y + 1.0 - data->player.map.y) * ray->step_dist.y;
	}
}

void	init_raycasting(t_data *data, t_ray *ray)
{
    ray->direction.x = data->player.direction.x + 0 * data->cam.x; // 0 ==> data->player.fov.x
    ray->direction.y = data->player.direction.y + 0.66 * data->cam.x;
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


t_int	dda(t_data *data, t_ray *ray)
{
	t_bool	hit;

	hit = FALSE;
	while (hit == 0)
	{
		if (ray->dist_player_to_side.x < ray->dist_player_to_side.y)
		{
			ray->dist_player_to_side.x += ray->step_dist.x;
			ray->dda_position.x += ray->dda_step.x;
		}
		else
		{
			ray->dist_player_to_side.y += ray->step_dist.y;
			ray->dda_position.y += ray->dda_step.y;
		}
		if (data->parsing.map[ray->dda_position.y][ray->dda_position.x] == WALL)
		{
			//printf("ray->dist_player_to_side.x = %f ray->dist_player_to_side.y = %f\n",ray->dist_player_to_side.x, ray->dist_player_to_side.y);
            return(ray->dda_position); 
		}
	}
    return(ray->dda_position);
}

// void	rotate_view(double rotSpeed, t_player *player)
// {
// 	t_pos	dir;

// 	dir.x = player->dir.x;
// 	dir.y = player->dir.y;
// 	player->dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
// 	player->dir.y = dir.x * sin(rotSpeed) + dir.y * cos(rotSpeed);
// 	player->cam.plane = point_value(-player->dir.y * FOV, player->dir.x * FOV);
// }

double dist_step(t_pos src, t_pos dest)
{
    double  res_x;
    double  res_y;
    double  res_final;

    res_x = (src.x - dest.x);
    res_y = (src.y - dest.y);
    res_final = ((res_x * res_x) + (res_y * res_y));
    res_final = sqrt(res_final);
    return (res_final);
}

void	draw_line(t_data *data, t_int end, double angle_fov)
{
	t_pos	dest;
    t_int   tmp;
	double	new_x;
	double	new_y;
	int		step;

	dest.x = (double)end.x * MAP_ZOOM;
	dest.y = (double)end.y * MAP_ZOOM;
	//direction des laser.
	data->player.d.x = cos(data->player.angle + angle_fov);
	data->player.d.y = sin(data->player.angle + angle_fov);
	step = 1;
	new_x = 0;
	new_y = 0;
    //int l = 300;
    tmp.x = data->player.position.x / 50;
    tmp.y = data->player.position.y / 50;
    tmp.x = tmp.x * 50;
    tmp.y = tmp.y * 50;
    double truc = dist_step(data->player.position, dest);
	printf("p.x %f  p.x %f\n",data->player.position.x, data->player.position.y);
    // printf("truc = %f\n", truc);
	// printf("mur x = %f  mur y = %f\n",dest.x, dest.y);
    // printf("posx %d posy %d\n", tmp.x, tmp.y);
	//printf("tmp.x = %d  tmp.y = %d\n",tmp.x, tmp.y);
    int zgeg = 0;
	while (1)
	{
		if (zgeg >= truc)
        {   
    		return ;
        }
        //printf("step = %d\n", zgeg);
		new_x += step * data->player.d.x;
		new_y += step * data->player.d.y;
        tmp.x += step * data->player.d.x;
        tmp.y += step * data->player.d.y;
		my_mlx_pixel_put(data, data->player.position.x + new_x, data->player.position.y + new_y, 0x00FF66FF);
        //l--;
        zgeg++;
	}
	//printf("new_x = %f  new_y = %f\n",data->player.position.x + new_x, data->player.position.y + new_y);
}

void	display_game(t_data *data)
{
	double	x;
	t_ray	ray;
    t_int   lol;

	x = 0;
	ft_bzero(&ray, sizeof(t_ray));
	while (++x < SCREEN_W)
	{
		norm_cam_x(data, x);
		init_raycasting(data, &ray);
		lol = dda(data, &ray);
        draw_line(data, lol, 0);
	    printf("ray->dda_position.x %d ray->dda_position.y %d\n", lol.x, lol.y);
        
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}

