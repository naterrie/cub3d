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


//============================================

void	ft_print_map(char **str)
{
	int i = 0;
	int j;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			printf("%c", str[i][j]);
			j++;
		}
		i++;
	}
}

int	if_is_space_in_column(char **str, int j, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i + 1][j] != ' ') && (str[i + 1][j] != '\0') && (str[i + 1][j] != '\n'))
		{
			printf("char = |%c| c= %d  j = %d\n", str[i + 1][j], c, j);
			return (0);
		}
		i++;
	}
	printf("j = %d  c = %d\n", j, c);
	return (1); 
}

int	ft_check_double_map(char **str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == ' ')
			{
				if (if_is_space_in_column(str, j, i) == 1)
				{
					printf("double map\n");
					return (-1);
				}
			}
			j++;
		}
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
		if (map[i][0] == 'N' && map[i][1] == 'O' && map[i][2] == ' ')
			data->parsing.no = get_texture(map[i]);
		else if (map[i][0] == 'S' && map[i][1] == 'O' && map[i][2] == ' ')
			data->parsing.so = get_texture(map[i]);
		else if (map[i][0] == 'W' && map[i][1] == 'E' && map[i][2] == ' ')
			data->parsing.we = get_texture(map[i]);
		else if (map[i][0] == 'E' && map[i][1] == 'A' && map[i][2] == ' ')
			data->parsing.ea = get_texture(map[i]);
		else if (map[i][0] == 'F')
			data->parsing.floor = ft_pars_floor_ceil(map[i]);
		else if (map[i][0] == 'C')
			data->parsing.ceil = ft_pars_floor_ceil(map[i]);
		i++;
	}
	ft_set_map(data, map, file);
	//ft_print_map(data->parsing.map);
	if (ft_check_double_map(data->parsing.map) != 0)
		printf("err double map \n");
	free_str(map);
}
