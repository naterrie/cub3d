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

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	printf ("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", data->NO, data->SO, data->WE, data->EA);
	printf ("F = %d %d %d\nC = %d %d %d\n", data->F[0], data->F[1], data->F[2], data->C[0], data->C[1], data->C[2]);
	while (data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
}

static void	set_data(t_data *data)
{
	int	i;

	i = 0;
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
	//print_map(&data);
}
