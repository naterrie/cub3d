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

//	Parsing	//
int		parsing(char *file);

// Pars char //
int		check_start(char **map);
int		check_chars(char **map);

// Utils Pars //
void	free_str(char **s);
int		nbline(char *file);
char	**get_map(char *file);

#endif
