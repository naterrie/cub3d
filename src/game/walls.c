/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:51:05 by naterrie          #+#    #+#             */
/*   Updated: 2023/11/20 12:49:37 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall(t_data *data, int pos, int height)
{
	int	i;

	i = 0;
	if (height < 0)
		height = SCREEN_H;
	while (i < (SCREEN_H / 2) - (height / 2))
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = data->parsing.ceil;
		i++;
	}
	while (i < (SCREEN_H / 2) + (height / 2))
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = 0xFF56A0;
		i++;
	}
	while (i < SCREEN_H)
	{
		((int *)data->mlx.addr)[(i) * (data->line_length >> 2) \
				+ (pos)] = data->parsing.floor;
		i++;
	}
}
