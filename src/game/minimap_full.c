/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_full.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:21:14 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/06 16:42:33 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double  add_case_pos(double nbr)
{
    double  len;

    len = 0;
    while (nbr)
    {
        if ((int)nbr % MAP_ZOOM == 0)
            break;;
        len++;
        nbr++;
    }
    return (len);
}

double  add_case_neg(double nbr)
{
    double  len;

    len = 0;
    while (nbr)
    {
        if ((int)nbr % MAP_ZOOM == 0)
            break;;
        len++;
        nbr--;
    }
    return (len);
}

// static void	draw_player_full(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;

// 	// i = data->player.position.x * MAP_ZOOM + MAP_ZOOM * 0.5;
// 	// j = data->player.position.y * MAP_ZOOM + MAP_ZOOM * 0.5;
// 	x = 2;
// 	while (x < MAP_ZOOM - 2)
// 	{
// 		y = 2;
// 		while (y < MAP_ZOOM - 2)
// 		{
// 			if (i >= 0 && j >= 0 && i < SCREEN_H && j < SCREEN_W)
// 				((int *)data->mlx.addr)[(x + i) * \
// 				(data->line_length >> 2) + (y + j)] = 0x00003399;
// 			y++;
// 		}
// 		x++;
// 	}
// }

// static int	hit_wall(t_data *data, int i, int j)
// {
// 	int	x;

// 	x = 0;
// 	while (data->parsing.map[x])
// 		x++;
// 	x *= MAP_ZOOM;
// 	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
// 		return (0);
// 	if (i < x && data->parsing.map[(int)floor(i) / MAP_ZOOM] \
// 	[(int)floor(j) / MAP_ZOOM] && (int)floor(j) / MAP_ZOOM < \
// 	ft_strlen(data->parsing.map[(int)floor(i) / MAP_ZOOM]))
// 		if (data->parsing.map[(int)floor(i) / MAP_ZOOM] \
// 		[(int)floor(j) / MAP_ZOOM] == '1')
// 			return (0);
// 	return (1);
// }

double d_coord(double x, double y, double i, double j)
{
	double	k;
	double	l;

	k = x - i;
	l = y - j;
	return (sqrt(k * k + l * l));
}

t_pos	draw_li(t_data *data, double angle_fov)
{
	t_pos	dest;
	double	new_x;
	double	new_y;
	int		step;

	dest.x = data->player.position.x;
	dest.y = data->player.position.y;
	//direction des laser.
	data->player.d.x = cos(data->player.angle + angle_fov);
	data->player.d.y = sin(data->player.angle + angle_fov);
	step = 1;
	new_x = 0;
	new_y = 0;
	//printf("p.x %f  p.x %f\n",data->player.d.x, data->player.d.y);
	while (1)
	{
		//printf("x = %f  y = %f\n",dest.x, dest.y);
		if (dest.x < MAP_ZOOM || dest.x >= data->parsing.map_max.x || dest.y < MAP_ZOOM || dest.y >= data->parsing.map_max.y)
    		return(dest);
		new_x += step * data->player.d.x;
		new_y += step * data->player.d.y;
		my_mlx_pixel_put(data, data->player.position.x + new_x, data->player.position.y + new_y, 0x00FF66FF);
		//((int *)data->mlx.addr)[(data->player.position.x + new_x) * (data->line_length >> 2) + (data->player.position.y + new_y)] = 0x00FF66FF;
		dest.x += data->player.d.x;
		dest.y += data->player.d.y;
	}
	return (dest);
}

//----------------------------------------------------------------------
t_pos	make_ori(t_pos d, double h)
{
	//printf(" h = %f fov.x %f fov.y %f\n",h, d.x , d.y);
	return ((t_pos){d.y * h, d.x * h});
}

t_pos	make_dir(t_pos dir, t_pos origine)
{
	// printf("co1.x %f co2.x %f\n", dir.x , origine.x);
	// printf("co1.y %f co2.y %f\n", dir.y , origine.y);
	return ((t_pos){dir.x + origine.x, dir.y + origine.y});
}

// double	draw_linne(t_data *data, double angle_fov)
// {
// 	t_raycast	ray;
// 	//double ray_cast;

// 	data->player.d.x = cos(data->player.angle + angle_fov);
// 	data->player.d.y = sin(data->player.angle + angle_fov);
// 	//ray_cast = angle_fov / (SCREEN_W * 0.5);
// 	ray.origin = make_ori(data->player.d, 0.993);
// 	ray.dir = make_dir(data->player.direction, ray.origin);
// 	ray.delt_dist.x = fabs(1 / ray.dir.x);
// 	ray.delt_dist.y = fabs(1 / ray.dir.y);
// 	//printf("ray.origin.x %f ray.origin.y %f\n",ray.origin.x, ray.origin.y);
// 	// printf("ray.dir.x %f ray.dir.y %f\n\n",ray.dir.x, ray.dir.y);
// 	// printf("ray.delt_dist.x %f ray.delt_dist.y %f\n\n",ray.delt_dist.x, ray.delt_dist.y);
// 	if (data->player.direction.x < 0)
// 	{
// 		ray.step.x = -1;
// 		ray.side_dist.x = (ray.origin.x - ray.origin.x) * ray.delt_dist.x;
// 	}
// 	else
// 	{
// 		ray.step.x = 1; // Calculating X step (depending on the direction)
// 		ray.side_dist.x = (ray.origin.x + 1 - ray.origin.x) * ray.delt_dist.x; // Calculating X gap to the nearest integer coordinate
// 	}

// 	if (data->player.direction.y < 0)
// 	{
// 		ray.step.y = 1;
// 		ray.side_dist.y = (ray.origin.y - ray.origin.y) * ray.delt_dist.y;
// 	}
// 	else
// 	{
// 		ray.step.y = 1; // Calculating Y step (depending on the direction)
// 		ray.side_dist.y = (ray.origin.y + 1 - ray.origin.y) * ray.delt_dist.y; // Calculating Y gap to the nearest integer coordinate
// 	}
// 	my_mlx_pixel_put(data, data->player.position.x * ray.side_dist.x, data->player.position.y * ray.side_dist.y, 0xFF9E9E9E);

// 	return (0);
// }






void	draw_squarelol(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_ZOOM)
	{
		j = 0;
		while (j < MAP_ZOOM)
		{
			if (i == 0 || j == 0)
				((int *)data->mlx.addr)[(x + i) * \
				(data->line_length >> 2) + (y + j)] = color;
			j++;
		}
		i++;
	}
}


void	minimap_full(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	data->player.angle_fov = (FOV * (M_PI / 180) / 2);
	while (data->parsing.map[i])
	{
		j = 0;
		while (data->parsing.map[i][j])
		{
			if (data->parsing.map[i][j] == WALL)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0xFF9E9E9E);
			else if (data->parsing.map[i][j] == EMPTY)
				draw_square(data, i * MAP_ZOOM, j * MAP_ZOOM, 0x00FFFFFF);
			draw_squarelol(data, i * MAP_ZOOM, j * MAP_ZOOM, 0xFF9E9E9E);
			j++;
		}
		i++;
	}

	draw_li(data, 0);
	//draw_linne(data, 0);
	//draw_player_full(data);
	//dda(data, draw_li(data, 0));
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
