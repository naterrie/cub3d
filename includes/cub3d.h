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
# include "../getnextline/get_next_line.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define MINI_SIZE 10
# define MAP_ZOOM 10
# define SCREEN_H 1080
# define SCREEN_W 1920
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1

typedef struct s_image
{
	void	*img;
	int		w;
	int		h;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		*addr;
	void		*img;
}	t_mlx;

typedef struct s_data
{
	char		**map;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	bool		minimap;
	int			floor;
	int			ceil;
	t_mlx		mlx;
	t_player	player;
}	t_data;

//	Movement	//
void	move_up(t_data *data);
void	move_down(t_data *data);
void	move_right(t_data *data);
void	move_left(t_data *data);

//	Start game	//
void	start_game(t_data *data);

//	Utils game	//
int		exit_game(t_data *data);

//	Minimap	//
void	minimap_full(t_data *data);
void	minimap_player(t_data *data);

//	Draw utils	//
void	put_floor_ceiling(t_data *data);
void	draw_square(t_data *data, int x, int y, int color);

void	ft_exit(t_data *data);

#endif
