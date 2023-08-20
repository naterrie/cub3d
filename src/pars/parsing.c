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

static int	border_char(char **map, int x, int y)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (x < 0 || y < 0 || x >= i || y >= ft_strlen(map[x]) || \
	(map[x][y] != '1' && map[x][y] != '0' && map[x][y] != 'E' && map[x][y] != 'N'\
	&& map[x][y] != 'S' && map[x][y] != 'W'))
		return (write(2, "Error : wrong border\n", 22), 1);
	return (0);
}

static int	check_wall(char **map, int x, int y)
{
	int	i;

	i = border_char(map, x + 1, y);
	i = border_char(map, x - 1, y);
	i = border_char(map, x, y + 1);
	i = border_char(map, x, y - 1);
	i = border_char(map, x + 1, y + 1);
	i = border_char(map, x - 1, y - 1);
	i = border_char(map, x + 1, y - 1);
	i = border_char(map, x - 1, y + 1);
	return (i);
}

static int	check_border(char **map)
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
	printf("ERROR\nWRONG FILE NAME\n");
	return (1);
}

int	parsing(char *file, t_data *data)
{
	char	**map;

	if (check_file_name(file))
		return (1);
	map = get_map(file);
	if (!map)
		return (1);
	split_file(map, data);
	if (check_texture(data))
		ft_exit(data);
	if (check_start(data->map))
		ft_exit(data);
	if (check_chars(data->map))
		ft_exit(data);
	if (check_border(map))
		ft_exit(data);
	return (0);
}
