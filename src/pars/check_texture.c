/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviscogl <aviscogl@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:21:48 by naterrie          #+#    #+#             */
/*   Updated: 2023/09/12 05:25:06 by aviscogl         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_pars_floor_ceil(char *str)
{
	int	temp[3];

	ft_split_atoi(str, ' ', temp);
	if (temp[0] < 0 || temp[0] > 255 || temp[1] < 0 || temp[1] > 255 || \
		temp[2] < 0 || temp[2] > 255)
	{
		write(2, "Error : Wrong color\n", 21);
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

static int	file_extention(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'm')
	{
		i--;
		if (file[i] == 'p')
		{
			i--;
			if (file[i] == 'x')
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
