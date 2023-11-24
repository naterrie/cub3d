/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:21:48 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/30 18:00:21 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	onlywall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != 10 && str[i] != 13 \
			&& str[i] != '0' && str[i] != 'N' \
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

int	check_color(char **str)
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

char	**split_atoi(char *str)
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

int	ft_pars_floor_ceil(char *str)
{
	int		temp[3];
	char	**colors;

	colors = split_atoi(str);
	if (!colors)
		return (-1);
	temp[0] = ft_atoi(colors[0]);
	temp[1] = ft_atoi(colors[1]);
	temp[2] = ft_atoi(colors[2]);
	if (temp[0] < 0 || temp[0] > 255 || temp[1] < 0 || temp[1] > 255 || \
		temp[2] < 0 || temp[2] > 255)
	{
		write(2, ERR_COLOR, 21);
		return (free_str(colors), -1);
	}
	free_str(colors);
	return (temp[0] * 256 * 256 + temp[1] * 256 + temp[2]);
}

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
