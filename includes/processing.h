/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:40:23 by nibernar          #+#    #+#             */
/*   Updated: 2023/11/24 15:22:34 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSING_H
# define PROCESSING_H

# ifdef __APPLE__
#  include "../mlx_macos/mlx.h"
# endif

# ifdef __linux__
#  include "../mlx/mlx.h"
# endif

# include "keypress.h"
# include "utils.h"
# include "typedef.h"

# include "../libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define MINI_SIZE 10
# define MAP_ZOOM 10
# define SCREEN_W 1600
# define SCREEN_H 800
# define MOVE_SPEED 0.051
# define ROT_SPEED 0.02
# define FOV 90

# define ERR_FILE			"Error : Wrong file name\n"
# define ERR_MAP_BORDER		"Error : wrong border\n"
# define ERR_COLOR			"Error : Wrong color\n"
# define ERR_EXTENTION		"Error : Wrong extention\n"
# define ERR_CHAR			"Error : Invalid char\n"
# define ERR_NO_PLAYER		"Error : Wrong number of player\n"
# define ERR_MAP			"Error : No map detected\n"
# define ERR_COLOR_MISS		"Error : No color\n"
# define ERR_TEXTURE		"Error : No texture\n"
# define ERR_PATH_NO		"Error : Wrong path NO\n"
# define ERR_PATH_SO		"Error : Wrong path SO\n"
# define ERR_PATH_WE		"Error : Wrong path WE\n"
# define ERR_PATH_EA		"Error : Wrong path EA\n"
#endif
