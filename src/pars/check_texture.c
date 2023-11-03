/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:21:48 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/29 17:08:33 by nibernar         ###   ########.fr       */
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
// ne rentre jamais ici, quit a file texture
int	check_extension(t_data *data)
{
	if (file_extention(data->parsing.no))
		return (printf(ERR_EXTENTION), 1);
	if (file_extention(data->parsing.so))
		return (printf(ERR_EXTENTION), 1);
	if (file_extention(data->parsing.ea))
		return (printf(ERR_EXTENTION), 1);
	if (file_extention(data->parsing.we))
		return (printf(ERR_EXTENTION), 1);
	return (0);
}
