/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:21:48 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/23 16:22:30 by naterrie         ###   ########lyon.fr   */
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

static int	file_extention(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'X')
	{
		i--;
		if (file[i] == 'P')
		{
			i--;
			if (file[i] == 'M')
				i--;
			if (file[i] == '.')
				return (0);
		}
	}
	return (1);
}

int	check_extension(t_data *data)
{
	if (file_extention(data->no))
		return (printf("Error : Wrong extention\n"), 1);
	if (file_extention(data->so))
		return (printf("Error : Wrong extention\n"), 1);
	if (file_extention(data->ea))
		return (printf("Error : Wrong extention\n"), 1);
	if (file_extention(data->we))
		return (printf("Error : Wrong extention\n"), 1);
	return (0);
}
