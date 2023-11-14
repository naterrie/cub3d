/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:36:41 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/05 09:39:35 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_data *data);
static void	move_down(t_data *data);
static void	move_left(t_data *data);
static void	move_right(t_data *data);

void	player_move(t_data *data)
{
	t_keypress		k;

	k = KP_UP;
	while (k < 6)
	{
		if (data->keypress[k])
		{
			if (k == KP_UP)
				move_up(data);
			else if (k == KP_DOWN)
				move_down(data);
			else if (k == KP_LEFT)
				move_left(data);
			else if (k == KP_RIGHT)
				move_right(data);
			else if (k == K_POV_L)
				look_left(data);
			else if (k == K_POV_R)
				look_right(data);
		}
		k++;
	}
}

static void	check_wall(t_data *data, double posy, double posx)
{
	if (data->parsing.map[(int)(posy / MAP_ZOOM)][(int)(posx / MAP_ZOOM)] != WALL)
	{
		data->player.position.x = posx;
		data->player.position.y = posy;
	}
	else if (data->parsing.map[(int)(posy / MAP_ZOOM)][(int)(data->player.position.x / MAP_ZOOM)] != WALL)
		data->player.position.y = posy;
	else if (data->parsing.map[(int)(data->player.position.y / MAP_ZOOM)][(int)(posx / MAP_ZOOM)] != WALL)
		data->player.position.x = posx;
}

static void	move_up(t_data *data)
{
	double	tempx;
	double	tempy;

	tempx = data->player.position.x + data->player.direction.x * MOVE_SPEED;
	tempy = data->player.position.y + data->player.direction.y * MOVE_SPEED;
	check_wall(data, tempy, tempx);
}

static void	move_down(t_data *data)
{
	double	tempx;
	double	tempy;

	tempx = data->player.position.x - data->player.direction.x * MOVE_SPEED;
	tempy = data->player.position.y - data->player.direction.y * MOVE_SPEED;
	check_wall(data, tempy, tempx);
}

static void	move_left(t_data *data)
{
	double	tempx;
	double	tempy;

	tempx = data->player.position.x + data->player.direction.y * MOVE_SPEED;
	tempy = data->player.position.y - data->player.direction.x * MOVE_SPEED;
	check_wall(data, tempy, tempx);
}

static void	move_right(t_data *data)
{
	double	tempx;
	double	tempy;

	tempx = data->player.position.x - data->player.direction.y * MOVE_SPEED;
	tempy = data->player.position.y + data->player.direction.x * MOVE_SPEED;
	check_wall(data, tempy, tempx);
}
