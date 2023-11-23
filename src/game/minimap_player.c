/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:38:07 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/23 13:25:00 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	player_draw(t_data *data, double pos)
{
	double	i;
	double	j;

	i = pos;
	while (i < pos + MAP_ZOOM)
	{
		j = pos;
		while (j < pos + MAP_ZOOM)
		{
			((int *)data->mlx.addr)[(int)(j) \
			*(data->line_length >> 2) + (int)(i)] = 0x00FF0000;
			j++;
		}
		i++;
	}
}

void	minimap_player(t_data *data)
{
	double playerx;
	double playery;
	playerx = ((MINI_SIZE -1 ) * MAP_ZOOM)/ 2;
	playery = playerx;
	(void)data;
	player_draw(data, playerx);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return ;
}
