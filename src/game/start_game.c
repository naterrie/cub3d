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

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_MINIMAP && data->minimap == true)
		data->minimap = false;
	else if (keycode == KEY_MINIMAP && data->minimap == false)
		data->minimap = true;
	put_floor_ceiling(data);
	if (keycode == KEY_UP)
		move_up(data);
	else if (keycode == KEY_DOWN)
		move_down(data);
	else if (keycode == KEY_LEFT)
		move_left(data);
	else if (keycode == KEY_RIGHT)
		move_right(data);
	else if (keycode == KEY_ESC)
		exit_game(data);
	if (data->minimap == true)
		minimap_player(data);
	else if (data->minimap == false)
		minimap_full(data);
	return (0);
}

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
	put_floor_ceiling(data);
	minimap_full(data);
	mlx_hook(data->mlx.win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
	mlx_loop(data->mlx.mlx);
}
