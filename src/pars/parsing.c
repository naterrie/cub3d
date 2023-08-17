/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:00 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/14 17:43:09 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_wall(char **map, int x, int y)
{
	if (map[x][y] == '0')
	{
		if (map[x + 1][y] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x - 1][y] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x][y + 1] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x][y - 1] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x + 1][y + 1] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x + 1][y - 1] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x - 1][y +1] != '1' || map[x + 1][y] != '0')
			return (1);
		if (map[x - 1][y -1] != '1' || map[x + 1][y] != '0')
			return (1);
	}
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
			if (check_wall(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_file_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'b')
	{
		i--;
		if (file[i] == 'u')
		{
			i--;
			if (file[i] == 'c')
				i--;
			if (file[i] == '.')
				return (0);
		}
	}
	write(2, "ERROR\nWRONG FILE NAME", 21);
	return (1);
}

int	parsing(char *file)
{
	char	**map;

	if (check_file_name(file))
		return (1);
	map = get_map(file);
	if (!map)
		return (1);
	if (check_start(map) != 1)
		return (free_str(map), 1);
	if (check_chars(map))
		return (free_str(map), 1);
	if (check_border(map))
		return (free(map), 1);
	return (free_str(map), 0);
}
