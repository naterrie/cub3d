/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:25:43 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/25 15:23:24 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	onlywall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != 10 && str[i] != 13 \
			&& str[i] != '0' && str[i] != 'N' \
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

static int	border_char(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (x < 0 || y < 0 || x >= i || y >= ft_strlen(map[x]) || \
	(map[x][y] != WALL && map[x][y] != EMPTY && map[x][y] != 'E' \
	&& map[x][y] != 'N' && map[x][y] != 'S' && map[x][y] != 'W'))
		return (write(2, ERR_MAP_BORDER, 22), 1);
	return (0);
}

static int	check_wall(char **map, int x, int y)
{
	if (border_char(map, x + 1, y))
		return (1);
	if (border_char(map, x - 1, y))
		return (1);
	if (border_char(map, x, y + 1))
		return (1);
	if (border_char(map, x, y - 1))
		return (1);
	if (border_char(map, x + 1, y + 1))
		return (1);
	if (border_char(map, x - 1, y - 1))
		return (1);
	if (border_char(map, x + 1, y - 1))
		return (1);
	if (border_char(map, x - 1, y + 1))
		return (1);
	return (0);
}

int	check_border(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == EMPTY)
				if (check_wall(map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}
