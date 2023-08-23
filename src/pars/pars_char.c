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

void	replace_texture(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == 13)
		{
			str[i] = 0;
			break ;
		}
		i++;
	}
}

int	check_start(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
				count++;
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
