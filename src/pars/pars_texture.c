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

char	**cpymap(char **map)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	while (map[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
			j++;
		tmp[i] = malloc(sizeof(char) * (j + 1));
		if (!tmp[i])
			return (NULL);
		j = -1;
		while (map[i][++j])
			tmp[i][j] = map[i][j];
		tmp[i][j] = '\0';
	}
	return (tmp);
}

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

int	split_file(char **map, t_data *data, char *file)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] ==)
			data->parsing.no = get_texture(map[i]);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			data->parsing.so = get_texture(map[i]);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			data->parsing.we = get_texture(map[i]);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			data->parsing.ea = get_texture(map[i]);
		else if (map[i][0] == 'F' && map[i][1] == ' ')
			data->parsing.floor = ft_pars_floor_ceil(map[i]);
		else if (map[i][0] == 'C' && map[i][1] == ' ')
			data->parsing.ceil = ft_pars_floor_ceil(map[i]);
		else if (ft_strlen(map[i]) > 2 && onlywall(map[i]) == 1)
			return (printf("Error, wrong line in file\n"), free_str(map), 1);
	}
	ft_set_map(data, map, file);
	free_str(map);
	return (0);
}
