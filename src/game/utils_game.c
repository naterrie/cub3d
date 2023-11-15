/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:49:28 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/05 12:21:53 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(t_data *data)
{
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win && data->mlx.mlx)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free(data->mlx.mlx);
	ft_exit(data);
	return (0);
}

void	check_wall_move(t_data *data, double posy, double posx)
{
	if (data->parsing.map[(int)(posy / MAP_ZOOM)] \
		[(int)(posx / MAP_ZOOM)] != WALL)
	{
		data->player.position.x = posx;
		data->player.position.y = posy;
	}
	else if (data->parsing.map[(int)(posy / MAP_ZOOM)] \
		[(int)(data->player.position.x / MAP_ZOOM)] != WALL)
		data->player.position.y = posy;
	else if (data->parsing.map[(int)(data->player.position.y \
		/ MAP_ZOOM)][(int)(posx / MAP_ZOOM)] != WALL)
		data->player.position.x = posx;
}
