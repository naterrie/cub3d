/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasbernard <nicolasbernard@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 00:07:26 by nicolasbern       #+#    #+#             */
/*   Updated: 2023/10/27 21:42:20 by nicolasbern      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
typedef struct s_ray
{
	t_pos	dist_player_to_side;
	t_pos	step_dist;
	t_int	dda_position;
	t_pos	direction;
	t_int	dda_step;
	double		dist_camera_side;
}   t_ray;


//t_pos camera_x   double x = le rayon de la fov
void    norm_cam_x(t_data *data, double x)
{
    data->cam.x = 2 * x / SCREEN_W - 1;
}

void    set_ray_direction(t_ray *ray, t_data *data)
{
    ray->direction.x = data->player.direction.x + 0 * data->cam.x;
    ray->direction.y = data->player.direction.y + 0.66 * data->cam.x;
    // ray->direction.x = data->player.direction.x + data->player.fov.x * data->cam.x;
    // ray->direction.y = data->player.direction.y + data->player.fov.y * data->cam.x;
	//printf("data->player.direction.x %f data->player.direction.y %f\n", data->player.direction.x, data->player.direction.y);
	//dprintf(2, "fov_x %f fov_y  %f cam_x %f\n", data->player.fov.x, data->player.fov.y, data->cam.x);
  //printf("dir.x = %f  dir.y = %f\n", ray->direction.x , ray->direction.y);
}

void	set_ray_dist_player_side(t_data *data, t_ray *ray, t_player *player)
{
    data->player.map.x = player->position.x / MAP_ZOOM;
    data->player.map.y = player->position.y / MAP_ZOOM;
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
    //dprintf(2, "pos.x en unité %f pos.y en unité %f\n", player->map.x, player->map.y);
    //dprintf(2, "side_dist.x %f side_dist.y %f\n", ray->dist_player_to_side.x, ray->dist_player_to_side.y);
}

void	set_ray_dist_to(t_data *data, t_ray *ray)
{
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
    my_mlx_pixel_put(data, data->player.position.x, data->player.position.y, 0x00FF66FF);
    //dprintf(2, "delt_dist.x %f delt_dist.y %f\n", ray->step_dist.x, ray->step_dist.y);
}

void	reset_dda_pos(t_player player, t_ray *ray)
{
	ray->dda_position.x = (int)player.position.x / MAP_ZOOM;
	ray->dda_position.y = (int)player.position.y / MAP_ZOOM;
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
        printf("ray->dist_player_to_side.x %df ray->dist_player_to_side.y %f\n", ray->dist_player_to_side.x, ray->dist_player_to_side.y);
        //printf("ray->dda_position.y %d ray->dda_position.x %d\n", ray->dda_position.y, ray->dda_position.x);
		//my_mlx_pixel_put(data, data->player.position.x, data->player.position.y, 0x00FF66FF);
		if (data->parsing.map[ray->dda_position.y][ray->dda_position.x] == WALL)
            return(ray->dda_position); 
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


    // calcule coor(x2 - x1) et (y2 - y1)
    //                  res_x       res_y
    //           carrée de res_x     carrée des res_y
    //          res_final = rs_x + res_y
    //          sqrt de res_fianl
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
    printf("truc = %f\n", truc);
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
		set_ray_direction(&ray, data);
		reset_dda_pos(data->player, &ray);
		set_ray_dist_to(data, &ray);
		set_ray_dist_player_side(data, &ray, &data->player);
		lol = dda(data, &ray);
        draw_line(data, lol, 0);
	    //printf("ray->dda_position.x %d ray->dda_position.y %d\n", lol.x, lol.y);
        
	}
//	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
//	draw_minimap(cub, player, mlx);
}

