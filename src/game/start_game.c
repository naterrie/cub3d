/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:04:01 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/30 18:56:40 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	put_floor_ceiling(data);
	if (keycode == 119)
		move_up(data);
	else if (keycode == 115)
		move_down(data);
	else if (keycode == 97)
		move_left(data);
	else if (keycode == 100)
		move_right(data);
	else if (keycode == 65307)
		exit_game(data);
	else if (keycode == 65289 && data->minimap == false)
		data->minimap = true;
	else if (keycode == 65289 && data->minimap == true)
		data->minimap = false;
	if (data->minimap == true)
		minimap_full(data);
	else if (data->minimap == false)
		minimap_player(data);
	return (0);
}

void	start_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_exit(data);
	data->win = mlx_new_window(data->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	if (!data->win)
		ft_exit(data);
	data->img = mlx_new_image(data->mlx, SCREEN_W, SCREEN_H);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	put_floor_ceiling(data);
	minimap_player(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 17, 0, exit_game, data);
	mlx_loop(data->mlx);
}
