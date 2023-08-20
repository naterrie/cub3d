/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:04:51 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/17 11:04:51 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_data *data)
{
	if (data->NO != NULL)
		free(data->NO);
	if (data->SO != NULL)
		free(data->SO);
	if (data->WE != NULL)
		free(data->WE);
	if (data->EA != NULL)
		free(data->EA);
	if (data->map != NULL)
		free_str(data->map);
	exit(1);
}

int	nbline(char *file)
{
	int		line;
	int		fd;
	char	*temp;

	line = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == 0)
			break ;
		free (temp);
		line++;
	}
	close(fd);
	return (line + 1);
}

char	**get_map(char *file)
{
	char	**map;
	int		i;
	int		fd;
	int		line;
	char	*temp;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write (2, "Error, wrong file\n", 18), NULL);
	line = nbline(file);
	map = malloc(sizeof(char *) * line);
	if (!map)
		return (NULL);
	while (i < line)
	{
		temp = get_next_line(fd);
		map[i] = temp;
		i++;
	}
	close(fd);
	free (temp);
	return (map);
}
