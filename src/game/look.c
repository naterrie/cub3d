/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:14 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/09 14:45:00 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_data *data)
{
	double	old_dir_x;

	data->player.angle += ROT_SPEED;
	if (data->player.angle > 2 * M_PI)
		data->player.angle = 0;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * \
		cos(ROT_SPEED) - data->player.dir_y * sin(ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(ROT_SPEED) \
		+ data->player.dir_y * cos(ROT_SPEED);
}

void	look_right(t_data *data)
{
	double	old_dir_x;

	data->player.angle -= ROT_SPEED;
	if (data->player.angle < -2 * M_PI)
		data->player.angle = 0;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * \
		cos(-ROT_SPEED) - data->player.dir_y * sin(-ROT_SPEED);
	data->player.dir_y = old_dir_x * sin(-ROT_SPEED) \
		+ data->player.dir_y * cos(-ROT_SPEED);
}