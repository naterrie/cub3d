/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:11:04 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/14 16:12:18 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "pars.h"

void	ft_exit(t_data *data)
{
	if (data->no != NULL)
		free(data->no);
	if (data->so != NULL)
		free(data->so);
	if (data->we != NULL)
		free(data->we);
	if (data->ea != NULL)
		free(data->ea);
	if (data->map != NULL)
		free_str(data->map);
	exit(1);
}

static void	set_data(t_data *data)
{
	data->mlx.addr = NULL;
	data->mlx.win = NULL;
	data->mlx.mlx = NULL;
	data->mlx.img = NULL;
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->minimap = false;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(2, "Wrong number args\n", 18));
	set_data(&data);
	if (parsing(argv[1], &data))
		return (1);
	start_game(&data);
	return (0);
}
