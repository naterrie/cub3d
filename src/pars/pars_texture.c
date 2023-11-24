/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:37:46 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/23 13:37:46 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_texture(t_data *data)
{
	if (data->parsing.ceil == -1 || data->parsing.floor == -1)
		return (printf(ERR_COLOR_MISS), 1);
	if (!data->parsing.no || !data->parsing.so || !data->parsing.we \
	|| !data->parsing.ea)
		return (printf(ERR_TEXTURE), 1);
	if (!data->parsing.map)
		return (printf(ERR_MAP), 1);
	return (0);
}

static int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != EMPTY && line[i] != WALL \
		&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' \
		&& line[i] != 'W' && line[i] && line[i] != 13 && line[i] != 10)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_set_map(t_data *data, char **map, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (is_map(map[i]) && line_null(map[i]))
			break ;
		i++;
	}
	if (!map[i])
		return ;
	data->parsing.map = malloc(sizeof(char *) * (nbline(file) - i));
	if (!data->parsing.map)
		return ;
	while (map[i])
	{
		data->parsing.map[j] = ft_strdup(map[i]);
		i++;
		j++;
	}
	data->parsing.map[j] = NULL;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uns1;
	unsigned char	*uns2;

	i = 0;
	uns1 = ((unsigned char *) s1);
	uns2 = ((unsigned char *) s2);
	while ((uns1[i] != '\0' || uns2[i] != '\0') && i < n)
	{
		if (uns1[i] != uns2[i])
			return (uns1[i] - uns2[i]);
		i++;
	}
	return (0);
}


void	split_file(char **map, t_data *data, char *file)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strncmp(map[i], "NO ", 3) == 0)
			data->parsing.no = get_texture(map[i]);
		else if (ft_strncmp(map[i], "SO ", 3) == 0)
			data->parsing.so = get_texture(map[i]);
		else if (ft_strncmp(map[i], "WE ", 3) == 0)
			data->parsing.we = get_texture(map[i]);
		else if (ft_strncmp(map[i], "EA ", 3) == 0)
			data->parsing.ea = get_texture(map[i]);
		else if (ft_strncmp(map[i], "F ", 2) == 0)
			data->parsing.floor = ft_pars_floor_ceil(map[i]);
		else if (ft_strncmp(map[i], "C ", 2) == 0)
			data->parsing.ceil = ft_pars_floor_ceil(map[i]);
		i++;
	}
	ft_set_map(data, map, file);
	free_str(map);
}
