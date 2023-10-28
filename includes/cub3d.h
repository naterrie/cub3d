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

// Linux
# include "../mlx/mlx.h"

// //macOs
//# include "../mlx_macos/mlx.h"

# include "../libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define MINI_SIZE 16
# define MAP_ZOOM 50
# define SCREEN_W 1030
# define SCREEN_H 950
# define MOVE_SPEED 0.5
# define ROT_SPEED 0.02
# define FOV 60

/*########################
#	 	Input key		 #
########################*/

//linux
typedef enum e_key
{
	KEY_UP = 119,
	KEY_DOWN = 115,
	KEY_RIGHT = 100,
	KEY_LEFT = 97,
	KEY_ESC = 65307,
	KEY_POV_RIGHT = 65363,
	KEY_POV_LEFT = 65361,
	KEY_MINIMAP = 65289,
}	t_key;

//macos
// typedef enum e_key
// {
// 	KEY_UP = 13,
// 	KEY_DOWN = 1,
// 	KEY_LEFT = 0,
// 	KEY_RIGHT = 2,
// 	KEY_ESC = 53,
// 	KEY_POV_RIGHT = 124,
// 	KEY_POV_LEFT = 123,
// 	KEY_MINIMAP = 48,
// }	t_key;

typedef enum e_keypress
{
	KP_ERROR = -1,
	KP_UP,
	KP_DOWN,
	KP_LEFT,
	KP_RIGHT,
	K_POV_R,
	K_POV_L,
}	t_keypress;

/*########################
#	 	   utils		 #
########################*/

typedef enum e_decor
{
	WALL = '1',
	EMPTY = '0',
}	t_decor;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

/*########################
#	 	 struc_MLX		 #
########################*/

typedef struct s_image
{
	void	*img;
	int		w;
	int		h;
}	t_image;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	char	*addr;
	void	*img;
}	t_mlx;

/*########################
#	 struct_parsing		 #
########################*/


typedef struct s_parsing
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceil;
	char	**map;
	t_pos	map_max;
}	t_parsing;

/*########################
#	 struct_raycasting	 #
########################*/

typedef	struct	s_raycast
{
	//distance entre pos du player et position du mur
	t_pos	dir;
	t_pos	step;
	t_pos	side_dist;
	t_pos	delt_dist;
}	t_raycast;


/*########################
#	 struct_player		 #
########################*/

typedef struct s_player
{
	t_pos	d;
	t_pos	position;
	t_pos	direction;
	double	angle;
	double	angle_fov;
}	t_player;

/*########################
#	 struct_data		 #
########################*/

typedef struct s_data
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	bool		minimap;
	t_parsing	parsing;
	t_mlx		mlx;
	t_player	player;
	t_bool		keypress[6];
}	t_data;

/*---------------------------------------*/
typedef struct {
    double x;
    double y;
} t_vector2_d;

typedef struct {
    float x;
    float y;
} t_vector2_f;

typedef struct {
    int cell_size;
    int tab[SCREEN_W][SCREEN_H]; // Remplacez GRID_HEIGHT et GRID_WIDTH par les dimensions réelles
} t_lala;

/*########################
#	 	Movement		 #
########################*/
void	player_move(t_data *data);

/*########################
#	 	  Look	    	 #
########################*/
void	look_right(t_data *data);
void	look_left(t_data *data);

/*########################
#	 	Start game		 #
########################*/
void	start_game(t_data *data);

/*########################
#	 	Utils game		 #
########################*/
int		exit_game(t_data *data);


/*########################
#	 	Minimap 		 #
########################*/
void	minimap_full(t_data *data);
void	minimap_player(t_data *data);

/*########################
#	 	Input_key		 #
########################*/
int		key_event_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
void	init_key(t_data *data);

/*########################
#	 	Draw utils		 #
########################*/
void	put_floor_ceiling(t_data *data);
void	draw_square(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put(t_data	*data, int x, int y, int color);
void	ft_exit(t_data *data);
void	my_mlx_pixel_put(t_data	*data, int x, int y, int color);
t_pos	dda(t_data *data, t_pos dest);
#endif