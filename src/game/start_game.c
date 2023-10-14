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

static t_keypress	get_keypress(int keycode)
{
	const int	dic[KEY_DIR] = {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_POV_RIGHT, KEY_POV_LEFT};
	t_keypress	key;

	key = KP_UP;
	while (key < KEY_DIR)
	{
		if (dic[key] == keycode)
			return (key);
		key++;
	}
	return (KP_ERROR);
}

int	key_event_release(int keycode, t_data *data)
{
	if (get_keypress(keycode) != KP_ERROR)
		data->keypress[get_keypress(keycode)] = FALSE;
	return (EXIT_SUCCESS);
}

// int	key_press(int keycode, t_data *data)
// {
// 	if (keycode == KEY_MINIMAP && data->minimap == true)
// 		data->minimap = false;
// 	else if (keycode == KEY_MINIMAP && data->minimap == false)
// 		data->minimap = true;
// 	put_floor_ceiling(data);
// 	if (keycode == KEY_UP)
// 		move_up(data);
// 	else if (keycode == KEY_DOWN)
// 		move_down(data);
// 	else if (keycode == KEY_LEFT)
// 		move_left(data);
// 	else if (keycode == KEY_RIGHT)
// 		move_right(data);
// 	else if (keycode == KEY_POV_LEFT)
// 		look_left(data);
// 	else if (keycode == KEY_POV_RIGHT)
// 		look_right(data);
// 	else if (keycode == KEY_ESC)
// 		exit_game(data);
// 	if (data->minimap == true)
// 		minimap_player(data);
// 	else if (data->minimap == false)
// 		minimap_full(data);
// 	return (0);
// }

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_MINIMAP && data->minimap == true)
		data->minimap = false;
	else if (keycode == KEY_MINIMAP && data->minimap == false)
		data->minimap = true;
	put_floor_ceiling(data);
	if (get_keypress(keycode) != KP_ERROR)
		data->keypress[get_keypress(keycode)] = TRUE;
	if (keycode == KEY_ESC)
		exit_game(data);
	if (data->minimap == true)
		minimap_player(data);
	else if (data->minimap == false)
		minimap_full(data);
	return (0);
}


// int	render(t_data *data)
// {
// 	dprintf(2, "couille\n");
// 	t_keypress		k;

// 	k = KP_UP;
// 	while (k < 4)
// 	{
// 		if (data->keypress[k])
// 		{
// 			if (k == KP_UP)
// 				move_up(data);
// 			else if (k == KP_DOWN)
// 				move_down(data);
// 			else if (k == KP_LEFT)
// 				move_left(data);
// 			else if (k == KP_RIGHT)
// 				move_right(data);
// 		}
// 		dprintf(2, "\n\n\n\n");
// 		k++;
// 	}
// 	if (data->keypress[K_POV_L] || data->keypress[K_POV_L])
// 	{
// 		if (data->keypress[K_POV_L])
// 			look_left(data);
// 		else if (data->keypress[K_POV_R])
// 			look_right(data);
// 	}
// 	return (EXIT_SUCCESS);
// }

static int	hook_loop(t_data *data)
{
	(void) data;
	printf("zgeg\n");
	return (EXIT_SUCCESS);
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
	mlx_hook(data->mlx.win, 3, (1L << 1), key_event_release, data);
	mlx_hook(data->mlx.win, 17, 0, exit_game, data);
	//mlx_loop_hook(data->mlx.win, render, data);
	mlx_loop_hook(data->mlx.win, hook_loop, data);
}
