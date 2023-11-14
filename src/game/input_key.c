/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:02:04 by nibernar          #+#    #+#             */
/*   Updated: 2023/10/30 18:00:04 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_key(t_data *data)
{
	data->keypress[0] = FALSE;
	data->keypress[1] = FALSE;
	data->keypress[2] = FALSE;
	data->keypress[3] = FALSE;
	data->keypress[4] = FALSE;
	data->keypress[5] = FALSE;
}

static t_keypress	get_keypress(int keycode)
{
	const int	key_tab[6] = \
		{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_POV_RIGHT, KEY_POV_LEFT};
	t_keypress	key;

	key = KP_UP;
	while (key < 6)
	{
		if (key_tab[key] == keycode)
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

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_MINIMAP && data->minimap == true)
		data->minimap = false;
	else if (keycode == KEY_MINIMAP && data->minimap == false)
		data->minimap = true;
	if (get_keypress(keycode) != KP_ERROR)
		data->keypress[get_keypress(keycode)] = TRUE;
	if (keycode == KEY_ESC)
		exit_game(data);
	return (0);
}
