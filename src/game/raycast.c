/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:31:47 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/10 18:01:29 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	hit_wall(t_data *data, int i, int j)
{
	int	x;

	x = 0;
	while (data->map[x])
		x++;
	x *= MAP_ZOOM;
	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
		return (0);
	if (i < x && data->map[(int)floor(i) / MAP_ZOOM][(int)floor(j) \
		/ MAP_ZOOM] && (int)floor(j) / MAP_ZOOM < \
		ft_strlen(data->map[(int)floor(i) / MAP_ZOOM]))
		if (data->map[(int)floor(i) / \
				MAP_ZOOM][(int)floor(j) / MAP_ZOOM] == '1')
			return (0);
	return (1);
}

int	draw_line(t_data *data, double x, double y)
{
	double	i;
	double	j;
	int		len;

	len = 0;
	i = data->player.x * MAP_ZOOM;
	j = data->player.y * MAP_ZOOM;
	while ((x != 0 || y != 0) && hit_wall(data, i, j))
	{
		((int *)data->mlx.addr)[(int)i * \
			(data->line_length >> 2) + (int)j] = 0x00990033;
		i += x;
		j += y;
		len++;
	}
	if (i < 0 || j < 0 || i > SCREEN_H || j > SCREEN_W)
		return (0);
	return (len);
}

int	hit_border(t_data *data, double x, double y)
{
	double	i;
	double	j;
	int		len;
	int		temp;

	len = 0;
	i = data->player.x * MAP_ZOOM;
	j = data->player.y * MAP_ZOOM;
	temp = (int)floor(i);
	printf("%d, %f\n", temp, i);
	while (temp == (int)floor(i) / MAP_ZOOM)
	{
		i += y;
		j += x;
		len++;
	}
	return (len);
}

void	raycast(t_data *data)
{
	int	d;

	draw_line(data, data->player.dir_x, data->player.dir_y);
	d = hit_border(data, data->player.dir_x, data->player.dir_y);
}
