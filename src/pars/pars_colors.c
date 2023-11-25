/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 12:13:40 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/25 16:08:59 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_color(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] < '0' || str[i][j] > '9') \
				&& str[i][j] != 13 && str[i][j] != 10)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

static char	**split_atoi(char *str)
{
	char	**split;
	char	**temp;
	int		i;
	int		count;

	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	i = -1;
	count = 0;
	while (split[1][++i])
		if (split[1][i] == ',')
			count++;
	if (count != 2)
		return (free_str(split), NULL);
	temp = ft_split(split[1], ',');
	i = -1;
	if (check_color(temp) == -1)
		return (free_str(split), free_str(temp), NULL);
	free_str(split);
	return (temp);
}

int	ft_pars_floor_ceil(char *str, int color)
{
	int		temp[3];
	char	**colors;

	if (color == -2 || color != -1)
		return (-2);
	colors = split_atoi(str);
	if (!colors)
		return (-1);
	temp[0] = ft_atoi(colors[0]);
	temp[1] = ft_atoi(colors[1]);
	temp[2] = ft_atoi(colors[2]);
	if (temp[0] < 0 || temp[0] > 255 || temp[1] < 0 || temp[1] > 255 || \
		temp[2] < 0 || temp[2] > 255)
		return (free_str(colors), -1);
	free_str(colors);
	return (temp[0] * 256 * 256 + temp[1] * 256 + temp[2]);
}
