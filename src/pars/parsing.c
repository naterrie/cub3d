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

static void	border_char(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (x < 0 || y < 0 || x >= i || y >= ft_strlen(map[x]) || \
	(map[x][y] != '1' && map[x][y] != '0' && map[x][y] != 'E' && map[x][y] != 'N'\
	&& map[x][y] != 'S' && map[x][y] != 'W'))
	{
		printf("ERROR: Invalid border\n");
		free_str(map);
		exit(1);
	}
}

static void	check_wall(char **map, int x, int y)
{
	border_char(map, x + 1, y);
	border_char(map, x - 1, y);
	border_char(map, x, y + 1);
	border_char(map, x, y - 1);
	border_char(map, x + 1, y + 1);
	border_char(map, x - 1, y - 1);
	border_char(map, x + 1, y - 1);
	border_char(map, x - 1, y + 1);
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
			if (map[i][j] == '0')
				check_wall(map, i, j);
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
