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

void	draw_li(t_data *data, double angle_fov)
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
    		return ;
		new_x += step * data->player.d.x;
		new_y += step * data->player.d.y;
		my_mlx_pixel_put(data, data->player.position.x + new_x, data->player.position.y + new_y, 0x00FF66FF);
		//printf("new_x %f nex_y %f\n", data->player.position.x + new_x, data->player.position.y + new_y);
		dest.x += data->player.d.x;
		dest.y += data->player.d.y;
	}
}

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


//planeX et planeY
// 	data->player.d.x = cos(data->player.angle + angle_fov);
// 	data->player.d.y = sin(data->player.angle + angle_fov);
//cameraX = 2 * x / double(w) - 1;  si cameraX = 0 ca veux dire que je regarde au milieu.
//double dirX = -1, dirY = 0; -> direction du rayon.
//calcule de la direction des rayons en fonction de la place en orizontale
//double rayDirX = dirX + planeX * cameraX;
//double rayDirY = dirY + planeY * cameraX;

void	minimap_full(t_data *data)
{
	int		i;
	int		j;
	//double camera_x = 0;
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
	double t = (double)FOV * (M_PI / 180);
	data->player.fov.x = cosf(t) * data->player.direction.x + -sinf(t) * data->player.direction.y;
	data->player.fov.y = sinf(t) * data->player.direction.x + cosf(t) * data->player.direction.x;
	//draw_li(data, 0);
	//draw_linne(data, 0);
	display_game(data);
	printf("map.x = %f   map.y = %f\n", data->player.fov.x, data->player.fov.y);
	//my_mlx_pixel_put(data, lol.x, lol.y, 0x0099FFFF);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
