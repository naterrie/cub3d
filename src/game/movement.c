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

void	move_up(t_data *data)
{
	data->player.position.x += data->player.direction.x * MOVE_SPEED;
	data->player.position.y += data->player.direction.y * MOVE_SPEED;
}

void	move_down(t_data *data)
{
	data->player.position.x -= data->player.direction.x * MOVE_SPEED;
	data->player.position.y -= data->player.direction.y * MOVE_SPEED;
}

void	move_right(t_data *data)
{
	data->player.position.x -= data->player.direction.y * MOVE_SPEED;
	data->player.position.y += data->player.direction.x * MOVE_SPEED;
}

void	move_left(t_data *data)
{
	data->player.position.x += data->player.direction.y * MOVE_SPEED;
	data->player.position.y -= data->player.direction.x * MOVE_SPEED;
}
