/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:09:25 by naterrie          #+#    #+#             */
/*   Updated: 2023/08/14 17:43:44 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
#include "../getnextline/get_next_line.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_data
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F[3];
	int		C[3];
}	t_data;

//	Parsing	//
int		parsing(char *file, t_data *data);

// Pars char //
int		check_start(char **map);
int		check_chars(char **map);

// Pars texture //
int		check_texture(t_data *data);
void	split_file(char **map, t_data *data);

// Utils Pars //
int		nbline(char *file);
char	**get_map(char *file);
void	ft_exit(t_data *data);

void	print_map(t_data *data);

#endif
