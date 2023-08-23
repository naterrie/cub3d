/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:04:01 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/23 14:49:33 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_game(data);
	return (0);
}

void	start_game(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		ft_exit(data);
	data->win = mlx_new_window(data->mlx, 1920, 1080, "Cub3D");
	if (!data->win)
		ft_exit(data);
	mlx_hook(data->win, 2, 1L << 0, key_press, &data);
	mlx_hook(data->win, 17, 0, exit_game, &data);
	mlx_loop(data->mlx);
}
