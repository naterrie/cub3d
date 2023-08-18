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

static void	check_border(char **map)
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
			{
				free_str(map);
				write(2, "ERROR\n, WRONG BORDER\n", 22);
				exit(1);
			}
			j++;
		}
		i++;
	}
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
	printf("ERROR\nWRONG FILE NAME\n");
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
	check_start(map);
	check_chars(map);
	check_border(map);
	return (free_str(map), 0);
}
