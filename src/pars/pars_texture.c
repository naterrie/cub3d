/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:22:39 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/25 15:40:18 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	texture_double(char *str, t_data *data)
{
	if (str[0] == 'N' && str[1] == 'O' && data->parsing.no)
		return (free(data->parsing.ea), 1);
	if (str[0] == 'S' && str[1] == 'O' && data->parsing.so)
		return (free(data->parsing.ea), 1);
	if (str[0] == 'W' && str[1] == 'E' && data->parsing.we)
		return (free(data->parsing.ea), 1);
	if (str[0] == 'E' && str[1] == 'A' && data->parsing.ea)
		return (free(data->parsing.ea), 1);
	return (0);
}

char	*get_texture(char *str, t_data *data)
{
	char	**split;
	char	*temp;

	split = ft_split(str, ' ');
	if (!split || !split[1])
		return (NULL);
	if (texture_double(str, data))
		return (free_str(split), NULL);
	temp = ft_strdup(split[1]);
	free_str(split);
	return (temp);
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
