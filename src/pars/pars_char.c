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

int	check_start(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
				i++;
			j++;
		}
		i++;
	}
	return (i);
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
			{
				printf("Error\nWrong character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
