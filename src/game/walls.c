/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:51:05 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/23 12:38:35 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_color_east(t_data *data, int posx, int posy, int height)
{
	posy = ((double)data->ea.h / (double)height) \
		* (posy - (SCREEN_H / 2) + (height / 2));
	posx = (1 - (data->ray.wall_pos.y - \
		(int)data->ray.wall_pos.y)) * data->ea.w;
	return (data->ea.addr[(posy * data->ea.line_length >> 2) + posx]);
}

static int	wall_color(t_data *data, int posx, int posy, int height)
{
	if (data->ray.wall == NORTH)
	{
		posy = ((double)data->no.h / (double)height) \
			* (posy - (SCREEN_H / 2) + (height / 2));
		posx = (data->ray.wall_pos.x - (int)data->ray.wall_pos.x) * data->no.w;
		return (data->no.addr[(posy * data->no.line_length >> 2) + posx]);
	}
	else if (data->ray.wall == SOUTH)
	{
		posy = ((double)data->so.h / (double)height) \
			* (posy - (SCREEN_H / 2) + (height / 2));
		posx = (1 -(data->ray.wall_pos.x - \
			(int)data->ray.wall_pos.x)) * data->so.w;
		return (data->so.addr[(posy * data->so.line_length >> 2) + posx]);
	}
	else if (data->ray.wall == WEST)
	{
		posy = ((double)data->we.h / (double)height) \
			* (posy - (SCREEN_H / 2) + (height / 2));
		posx = (data->ray.wall_pos.y - (int)data->ray.wall_pos.y) * data->we.w;
		return (data->we.addr[(posy * data->we.line_length >> 2) + posx]);
	}
	else if (data->ray.wall == EAST)
		return (wall_color_east(data, posx, posy, height));
	return (0);
}

void	put_wall(t_data *data, int pos, int height)
{
	int	i;

	i = 0;
	while (i < (SCREEN_H / 2) - (height / 2))
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = data->parsing.ceil;
		i++;
	}
	while (i < (SCREEN_H / 2) + (height / 2) && i < SCREEN_H)
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = wall_color(data, pos, i, height);
		i++;
	}
	while (i < SCREEN_H)
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = data->parsing.floor;
		i++;
	}
}
