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

#include "cub3d.h"

static int	char_start(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_start(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (char_start(data->map[i][j]))
			{
				data->map[i][j] = '0';
				data->x = i;
				data->y = j;
				count++;
			}
			j++;
		}
		i++;
	}
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
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' \
			&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' \
			&& map[i][j] != ' ' && map[i][j] != 10 && map[i][j] != 13)
				return (write(2, "Error : Invalid char\n", 22), 1);
			j++;
		}
		i++;
	}
	return (0);
}
