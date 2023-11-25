/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:00 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/14 17:43:09 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	split_file(char **map, t_data *data, char *file)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			data->parsing.no = get_texture(map[i], data);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			data->parsing.so = get_texture(map[i], data);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			data->parsing.we = get_texture(map[i], data);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			data->parsing.ea = get_texture(map[i], data);
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			data->parsing.floor = ft_pars_floor_ceil(map[i], \
						data->parsing.floor);
		else if (map[i][0] == 'C' && map[i][1] == ' ')
			data->parsing.ceil = ft_pars_floor_ceil(map[i], data->parsing.ceil);
		else if (ft_strlen(map[i]) > 2 && onlywall(map[i]) == 1)
			return (printf("Error, wrong line in file\n"), free_str(map), 1);
	}
	ft_set_map(data, map, file);
	free_str(map);
	return (0);
}

static int	check_texture(t_data *data)
{
	if (data->parsing.ceil < 0 || data->parsing.floor < 0)
		return (printf(ERR_COLOR_MISS), 1);
	if (!data->parsing.no || !data->parsing.so || !data->parsing.we \
	|| !data->parsing.ea)
		return (printf(ERR_TEXTURE), 1);
	if (!data->parsing.map)
		return (printf(ERR_MAP), 1);
	return (0);
}

static int	check_file_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	i--;
	if (file[i] == 'b')
	{
		i--;
		if (file[i] == 'u')
		{
			i--;
			if (file[i] == 'c')
				i--;
			if (file[i] == '.')
				return (0);
		}
	}
	printf(ERR_FILE);
	return (1);
}

int	parsing(char *file, t_data *data)
{
	char	**map;

	if (check_file_name(file))
		return (1);
	map = get_file(file);
	if (!map)
		return (1);
	if (split_file(map, data, file) == 1)
		ft_exit(data);
	if (check_texture(data))
		ft_exit(data);
	if (check_start(data))
		ft_exit(data);
	if (check_border(data->parsing.map))
		ft_exit(data);
	if (pars_island(data->parsing.map))
		ft_exit(data);
	replace_texture(data->parsing.no);
	replace_texture(data->parsing.so);
	replace_texture(data->parsing.we);
	replace_texture(data->parsing.ea);
	return (0);
}
