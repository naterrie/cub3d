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

int	ft_pars_floor_ceil(char *str)
{
	int	temp[3];

	ft_split_atoi(str, ' ', temp);
	if (temp[0] < 0 || temp[0] > 255 || temp[1] < 0 || temp[1] > 255 || \
		temp[2] < 0 || temp[2] > 255)
	{
		write(2, ERR_COLOR, 21);
		return (-1);
	}
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
