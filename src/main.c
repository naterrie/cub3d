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
	if (data->parsing.no != NULL)
		free(data->parsing.no);
	if (data->parsing.so != NULL)
		free(data->parsing.so);
	if (data->parsing.we != NULL)
		free(data->parsing.we);
	if (data->parsing.ea != NULL)
		free(data->parsing.ea);
	if (data->parsing.map != NULL)
		free_str(data->parsing.map);
	exit(1);
}

static void	set_data(t_data *data)
{
	data->mlx.addr = NULL;
	data->mlx.win = NULL;
	data->mlx.mlx = NULL;
	data->mlx.img = NULL;
	data->parsing.map = NULL;
	data->parsing.no = NULL;
	data->parsing.so = NULL;
	data->parsing.we = NULL;
	data->parsing.ea = NULL;
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
	mlx_loop(data.mlx.mlx);
	return (0);
}
