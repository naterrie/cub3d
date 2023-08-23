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

typedef struct s_image
{
	void	*img;
	int		w;
	int		h;
}	t_image;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];
}	t_data;

//	Start game	//
void	start_game(t_data *data);

//	Utils game	//
int		exit_game(t_data *data);

//	Parsing	//
int		parsing(char *file, t_data *data);

//	Pars char	//
int		check_start(char **map);
int		check_chars(char **map);

//	Pars texture	//
int		check_texture(t_data *data);
void	split_file(char **map, t_data *data, char *file);

//	Utils Pars	//
int		nbline(char *file);
int		line_null(char *str);
char	**get_file(char *file);
char	*get_texture(char *str);
void	ft_split_atoi(char *s, char c, int t[3]);

void	ft_exit(t_data *data);

#endif
