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

static int	check_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != ' ')
				{
					printf("Error\nWrong character in map\n");
					return (1);
				}
			j++;
		}
	}
	return (0);
}

static int	countline(int fd)
{
	int		i;

	i = 0;
	while (get_next_line(fd))
		i++;
	return (i);
}

static char	**get_map(int fd)
{
	char	*line;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * countline(fd));
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		free(line);
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	parsing(char *file)
{
	int		fd;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCan't open file\n", 22);
		return (1);
	}
	map = get_map(fd);
	if (check_chars(map))
		return (1);
	return (0);
}
