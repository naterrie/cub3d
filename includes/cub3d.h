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
#	 	   utils		 #
########################*/

typedef enum e_wall
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_wall;

/*########################
#	 	 struc_MLX		 #
########################*/

struct s_image
{
	int		*addr;
	void	*img;
	int		w;
	int		h;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceil;
	char		**map;
	t_double	map_max;
};

/*########################
#		check_map		 #
########################*/
int			onlywall(char *str);
int			check_border(char **map);

/*########################
#		pars_colors		 #
########################*/
int			ft_pars_floor_ceil(char *str, int color);

/*########################
#		pars_island		 #
########################*/
int			pars_island(char **map);

/*########################
#		pars_start		 #
########################*/
int			check_start(t_data *data);

/*########################
#		pars_texture	 #
########################*/
char		*get_texture(char *str, t_data *data);
void		replace_texture(char *str);

/*########################
#		parsing			 #
########################*/
int			parsing(char *file, t_data *data);
void		ft_set_map(t_data *data, char **map, char *file);

/*########################
#		utils_pars		 #
########################*/
char		**get_file(char *file);
int			nbline(char *file);
int			line_null(char *str);

/*########################
#	 struct_dda			 #
########################*/
struct s_dda
{
	double		wall_x;
	double		wall_y;
	t_double	ray;
	double		dist_wall;
	int			side;
};

/*########################
#	 struct_raycasting	 #
########################*/
struct s_ray
{
	t_double	dist_player_to_side;
	t_double	step_dist;
	t_double	direction;
	double		ray_len;
	double		ray_angle[SCREEN_W];
	t_double	wall_pos;
	t_wall		wall;
	t_int		dda_position;
	t_int		dda_step;
	double		distance;
};

/*########################
#	 struct_player		 #
########################*/
struct s_player
{
	t_double	d;
	t_double	position;
	t_double	direction;
	t_double	map;
	double		angle;
	double		angle_degre;
	double		angle_radian;
	t_double	fov;
	double		angle_fov;
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
	t_ray		ray;
	t_image		no;
	t_image		so;
	t_image		we;
	t_image		ea;
	t_parsing	parsing;
	t_mlx		mlx;
	t_player	player;
	t_double	cam;
	t_bool		keypress[6];
};

/*########################
#	 	Movement		 #
########################*/
void		player_move(t_data *data);

/*########################
#	 	  Look	    	 #
########################*/
void		look_right(t_data *data);
void		look_left(t_data *data);

/*########################
#	 	Start game		 #
########################*/
void		start_game(t_data *data);

/*########################
#	 	Utils game		 #
########################*/
char		**cpymap(char **map);
void		check_wall_move(t_data *data, double posy, double posx);
int			exit_game(t_data *data);

/*########################
#	 	Minimap 		 #
########################*/
void		minimap_full(t_data *data);

/*########################
#	 	Input_key		 #
########################*/
int			key_event_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
void		init_key(t_data *data);

/*########################
#	 	Ray_Shoot		 #
#########################*/
void		ray_pos(t_data *data);

/*########################
#	 	Raycasting		 #
########################*/
void		display_game(t_data *data);

/*########################
#	 	Draw utils		 #
########################*/
void		draw_square(t_data *data, int x, int y, int color);
void		my_mlx_pixel_put(t_data	*data, int x, int y, int color);
void		ft_exit(t_data *data);

/*########################
#	 	raycast utils	 #
########################*/
t_double	t_pos_rotate(t_double dir, double fov);
void		norm_cam_x(t_data *data, double x);
double		degre_to_radian(double angle);

/*########################
#			Walls		 #
########################*/
void		put_wall(t_data *data, int pos, int height);
double		ray_len(t_double src, t_double dest);
int			wall_height(t_ray ray, int i);

#endif
