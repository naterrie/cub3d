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

static int	countline(int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line))
	{
		i++;
		free(line);
	}
	free(line);
	return (i);
}

static char	**get_map(int fd)
{
	char	*line;
	char	**map;
	int		i;

	i = 0;
	map = malloc(sizeof(char *) * countline(fd));
	while (get_next_line(fd, &line))
	{
		map[i] = line;
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
		return (write(2, "Error\nCan't open file\n", 22), 1);
	map = get_map(fd);
	return (0);
}
