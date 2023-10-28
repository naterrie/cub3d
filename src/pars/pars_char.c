/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:04:28 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/17 11:04:28 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

static int	char_start(char c, int j, int i, t_data *data)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player.position.x = i * MAP_ZOOM + MAP_ZOOM * 0.5;
		data->player.position.y = j * MAP_ZOOM + MAP_ZOOM * 0.5;
		return (1);
	}
	return (0);
}

static void	set_player_info(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.angle = -M_PI_2;
		data->player.direction.x = 0;
		data->player.direction.y = -1;
	}
	else if (c == 'S')
	{
		data->player.angle = M_PI_2;
		data->player.direction.x = 0;
		data->player.direction.y = 1;
	}
	else if (c == 'E')
	{
		data->player.angle = 0;
		data->player.direction.x = 1;
		data->player.direction.y = 0;
	}
	else if (c == 'W')
	{
		data->player.angle += -M_PI;
		data->player.direction.x = -1;
		data->player.direction.y = 0;
	}
}

int	check_start(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->parsing.map[i])
	{
		j = 0;
		while (data->parsing.map[i][j])
		{
			if (char_start(data->parsing.map[i][j], i, j, data))
			{
				set_player_info(data, data->parsing.map[i][j]);
				data->parsing.map[i][j] = EMPTY;
				count++;
			}
			j++;
		}
		i++;
	}
	//trouver piexl max en x et y
	data->parsing.map_max.x = (j - 1) * MAP_ZOOM;
	data->parsing.map_max.y = i * MAP_ZOOM;

	if (count != 1)
		return (write(2, "Error : Start incorrect\n", 24), 1);
	return (0);
}

int	check_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != EMPTY && map[i][j] != WALL && \
			map[i][j] != 'N' && map[i][j] != 'S' && \
			map[i][j] != 'E' && map[i][j] != 'W' && map[i][j] \
			!= ' ' && map[i][j] != 10 && map[i][j] != 13)
				return (write(2, "Error : Invalid char\n", 22), 1);
			j++;
		}
		i++;
	}
	return (0);
}
