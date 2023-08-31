/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:36:41 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/31 14:07:47 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data)
{
	data->player.x += data->player.dir_x * MOVE_SPEED;
	data->player.y += data->player.dir_y * MOVE_SPEED;
}

void	move_down(t_data *data)
{
	data->player.x -= data->player.dir_x * MOVE_SPEED;
	data->player.y -= data->player.dir_y * MOVE_SPEED;
}

void	move_right(t_data *data)
{
	data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED) - \
		data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = data->player.dir_y * cos(-ROT_SPEED) + \
		data->player.dir_x * sin(-ROT_SPEED);
}

void	move_left(t_data *data)
{
	data->player.dir_x = data->player.dir_x * cos(ROT_SPEED) - \
		data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = data->player.dir_y * cos(ROT_SPEED) + \
		data->player.dir_x * sin(ROT_SPEED);
}