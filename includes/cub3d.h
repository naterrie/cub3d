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

# include "processing.h"

/*########################
#	 	 struc_MLX		 #
########################*/

struct s_image
{
	void	*img;
	int		w;
	int		h;
};

struct s_mlx
{
	void	*mlx;
	void	*win;
	char	*addr;
	void	*img;
};

/*########################
#	 struct_parsing		 #
########################*/


struct s_parsing
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceil;
	char	**map;
	t_pos	map_max;
};

int		parsing(char *file, t_data *data);
int		check_chars(char **map);
int		check_start(t_data *data);
int		ft_pars_floor_ceil(char *str);
void	replace_texture(char *str);
int		check_extension(t_data *data);
int		file_texture(t_data *data);
int		check_texture(t_data *data);
void	split_file(char **map, t_data *data, char *file);
int		nbline(char *file);
int		line_null(char *str);
char	**get_file(char *file);
char	*get_texture(char *str);
void	ft_split_atoi(char *s, char c, int t[3]);

/*########################
#	 struct_raycasting	 #
########################*/

struct s_ray
{
	t_pos	dist_player_to_side;
	t_pos	step_dist;
	t_pos	direction;
	t_int	dda_position;
	t_int	dda_step;
	t_pos	dist_player_to_wall;
	int		wall;
};


/*########################
#	 struct_player		 #
########################*/

struct s_player
{
	t_pos	d;
	t_pos	position;
	t_pos	direction;
	t_pos	map;
	double	angle;
	t_pos	fov;
	double	angle_fov;
};

/*########################
#	 struct_data		 #
########################*/

struct s_data
{
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	bool		minimap;
	t_parsing	parsing;
	t_mlx		mlx;
	t_player	player;
	t_pos		cam;
	t_bool		keypress[6];
};


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
//t_pos 	dda(t_data *data, t_pos ray) ;
void	display_game(t_data *data);
#endif