/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:04:01 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/05 13:48:46 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render(t_data *data);

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_exit(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, SCREEN_W, SCREEN_H, "Cub3D");
	if (!data->mlx.win)
		ft_exit(data);
	data->mlx.img = mlx_new_image(data->mlx.mlx, SCREEN_W, SCREEN_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	//put_floor_ceiling(data);
	init_key(data);
	mlx_hook(data->mlx.win, 2, (1L << 0), key_press, data);
	mlx_hook(data->mlx.win, 3, (1L << 1), key_event_release, data);
	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
	mlx_loop_hook(data->mlx.mlx, render, data);
}

static int	render(t_data *data)
{
	player_move(data);
	// if (data->minimap == true)
	// 	minimap_player(data);
	// else
	minimap_full(data);
	usleep(350);
	return (EXIT_SUCCESS);
}

