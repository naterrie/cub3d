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

void	ft_split_atoi(char *s, char c, int t[3])
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != c)
		i++;
	i++;
	temp = ft_split(s + i, ',');
	while (temp[j])
		j++;
	if (j != 3)
	{
		write(2, ERR_COLOR, 21);
		return ;
	}
	t[0] = ft_atoi(temp[0]);
	t[1] = ft_atoi(temp[1]);
	t[2] = ft_atoi(temp[2]);
	free_str(temp);
}

char	*get_texture(char *str)
{
	char	**split;
	char	*temp;

	split = ft_split(str, ' ');
	if (!split || !split[1])
		return (NULL);
	temp = ft_strdup(split[1]);
	free_str(split);
	return (temp);
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

int	line_null(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != 10 && str[i] != 13)
			return (1);
		i++;
	}
	return (0);
}

char	**get_file(char *file)
{
	char	**map;
	int		i;
	int		fd;
	int		line;
	char	*temp;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write (2, ERR_FILE, 23), NULL);
	line = nbline(file);
	map = malloc(sizeof(char *) * line);
	if (!map)
		return (close(fd), NULL);
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
