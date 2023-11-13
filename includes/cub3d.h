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

typedef enum	e_wall
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
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor;
	int			ceil;
	char		**map;
	t_double	map_max;
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
	double		ray_angle;
	t_double	wall_pos;
	t_wall		wall;
	t_int		dda_position;
	t_int		dda_step;
	double		distance;
};

void		display_game(t_data *data);
double		ray_len(t_double src, t_double dest);
void		norm_cam_x(t_data *data, double x);
double		degre_to_radian(double angle);
int			wall_height(t_ray *ray);
t_double	t_double_rotate(t_double dir, double fov);

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
int			exit_game(t_data *data);


/*########################
#	 	Minimap 		 #
########################*/
void		minimap_full(t_data *data);
void		minimap_player(t_data *data);
// double		draw_line(t_data *data, double x, double y);
void		draw_minimap(t_data *data);

/*########################
#	 	Input_key		 #
########################*/
int			key_event_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
void		init_key(t_data *data);

/*########################
#	 	Ray_Shoot		 #
#########################*/
// void		set_ray_dist_player_side(t_data *data, t_ray *ray);
// void		ray_pos(t_ray	*ray, t_data *data);

/*########################
#	 	Raycasting		 #
########################*/
void		display_game(t_data *data);
void		raycast(t_data *data);

/*########################
#	 	Draw utils		 #
########################*/
//void		put_floor_ceiling(t_data *data);
void		draw_square(t_data *data, int x, int y, int color);
void		my_mlx_pixel_put(t_data	*data, int x, int y, int color);
void		ft_exit(t_data *data);
//void		draw_fov(t_data *data);
void		my_mlx_pixel_put(t_data	*data, int x, int y, int color);
void		draw_line(t_data *data, t_ray *ray);

/*########################
#	 	raycast utils	 #
########################*/
t_double	t_pos_rotate(t_double dir, double fov);

#endif
