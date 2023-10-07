/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:17:50 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/07 16:18:38 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

# include "cub3d.h"

//	Parsing	//
int		parsing(char *file, t_data *data);

//	Pars char	//
int		check_chars(char **map);
int		check_start(t_data *data);

//	Check texture	//
int		ft_pars_floor_ceil(char *str);
void	replace_texture(char *str);
int		check_extension(t_data *data);

//	Pars texture	//
int		file_texture(t_data *data);
int		check_texture(t_data *data);
void	split_file(char **map, t_data *data, char *file);

//	Utils Pars	//
int		nbline(char *file);
int		line_null(char *str);
char	**get_file(char *file);
char	*get_texture(char *str);
void	ft_split_atoi(char *s, char c, int t[3]);

#endif
