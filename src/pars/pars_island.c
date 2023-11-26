/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_island.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:19:01 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/24 14:45:21 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_for_diffusion(char **map, int y, int x)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	if (x >= 0 && y >= 0 && y < height && x < ft_strlen(map[y]) \
		&& map[y][x] && (map[y][x] == '0' || map[y][x] == '1') \
		&& ft_strlen(map[y]) > 1)
		return (true);
	return (false);
}

static void	ft_diffusion(char **map, int y, int x)
{
	map[y][x] = '*';
	if (check_for_diffusion(map, y - 1, x) == true)
		ft_diffusion(map, y - 1, x);
	if (check_for_diffusion(map, y, x - 1) == true)
		ft_diffusion(map, y, x - 1);
	if (check_for_diffusion(map, y + 1, x) == true)
		ft_diffusion(map, y + 1, x);
	if (check_for_diffusion(map, y, x + 1) == true)
		ft_diffusion(map, y, x + 1);
	return ;
}

static int	diff_island(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
			{
				ft_diffusion(map, i, j);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_no_star(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '*' && map[i][j] != ' ' \
				&& map[i][j] != 13 && map[i][j] != 10)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	pars_island(char **map)
{
	char	**map_temp;
	int		i;

	i = 0;
	map_temp = cpymap(map);
	if (map_temp == NULL)
		return (1);
	while (map[i])
		i++;
	map_temp[i] = NULL;
	if (diff_island(map_temp) == 1)
	{
		free_str(map_temp);
		return (1);
	}
	if (check_no_star(map_temp) == 1)
	{
		free_str(map_temp);
		return (write(1, "Error, double map detected\n", 27), 1);
	}
	free_str(map_temp);
	return (0);
}
