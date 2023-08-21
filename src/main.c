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

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	if (data->NO != NULL)
		free(data->NO);
	if (data->SO != NULL)
		free(data->SO);
	if (data->WE != NULL)
		free(data->WE);
	if (data->EA != NULL)
		free(data->EA);
	if (data->map != NULL)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	exit(1);
}

static void	set_data(t_data *data)
{
	int	i;

	i = 0;
	data->map = NULL;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	while (i < 3)
	{
		data->F[i] = -1;
		data->C[i] = -1;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(2, "Wrong number args\n", 18));
	set_data(&data);
	if (parsing(argv[1], &data))
		return (1);
	ft_exit(&data);
	//print_map(&data);
}
