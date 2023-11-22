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

static int	set_addr_img(t_data *data)
{
	data->no.addr = (int *)mlx_get_data_addr(data->no.img, \
		&data->no.bits_per_pixel, &data->no.line_length, &data->no.endian);
	data->so.addr = (int *)mlx_get_data_addr(data->so.img, \
		&data->so.bits_per_pixel, &data->so.line_length, &data->so.endian);
	data->we.addr = (int *)mlx_get_data_addr(data->we.img, \
		&data->we.bits_per_pixel, &data->we.line_length, &data->we.endian);
	data->ea.addr = (int *)mlx_get_data_addr(data->ea.img, \
		&data->ea.bits_per_pixel, &data->ea.line_length, &data->ea.endian);
	if (!data->no.addr || !data->so.addr || !data->we.addr || !data->ea.addr)
		return (printf(ERR_TEXTURE), 1);
	return (0);
}

static int	xpm_check(t_data *data)
{
	data->so.img = mlx_xpm_file_to_image(data->mlx.mlx, \
			data->parsing.so, &data->so.w, &data->so.h);
	data->no.img = mlx_xpm_file_to_image(data->mlx.mlx, \
			data->parsing.no, &data->no.w, &data->no.h);
	data->we.img = mlx_xpm_file_to_image(data->mlx.mlx, \
			data->parsing.we, &data->we.w, &data->we.h);
	data->ea.img = mlx_xpm_file_to_image(data->mlx.mlx, \
			data->parsing.ea, &data->ea.w, &data->ea.h);
	if (!data->so.img || !data->no.img || !data->we.img || \
				!data->ea.img || set_addr_img(data))
		return (printf(ERR_TEXTURE), 1);
	return (0);
}

static void	set_angle_ray(t_data *data)
{
	double	opposite;
	double	adjacent;
	int		i;

	i = 0;
	data->player.angle_fov = (FOV * (M_PI / 180));
	adjacent = (double)SCREEN_W / (2 * tan(data->player.angle_fov / 2));
	opposite = (double)SCREEN_W / 2;
	while (i < SCREEN_W)
	{
		data->ray.ray_angle[i] = -atan(opposite / adjacent);
		opposite--;
		i++;
	}
}

void	start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_exit(data);
	if (xpm_check(data))
		ft_exit(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, SCREEN_W, SCREEN_H, "Cub3D");
	if (!data->mlx.win)
		ft_exit(data);
	set_angle_ray(data);
	data->mlx.img = mlx_new_image(data->mlx.mlx, SCREEN_W, SCREEN_H);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
	init_key(data);
	mlx_hook(data->mlx.win, 2, (1L << 0), key_press, data);
	mlx_hook(data->mlx.win, 3, (1L << 1), key_event_release, data);
	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
	mlx_loop_hook(data->mlx.mlx, render, data);
}

static int	render(t_data *data)
{
	player_move(data);
	display_game(data);
	if (data->minimap == true)
		minimap_player(data);
	else
		minimap_full(data);
	usleep(350);
	return (EXIT_SUCCESS);
}
