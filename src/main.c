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

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (write(2, "Wrong number args\n", 18));
	if (parsing(argv[1]) == -1)
		return (write(2, "Parsing error\n", 14));
}
