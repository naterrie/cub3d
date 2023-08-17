/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:07:33 by naterrie          #+#    #+#             */
/*   Updated: 2022/12/06 16:19:19 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "cub3d.h"
# include "../libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		gnl_strchr(char *s, int c);
int		ft_len(char *s);

char	*get_next_line(int fd);
char	*ft_next_buf(char *buf);
char	*ft_get_line(char *buf);
char	*ft_read_line(int fd, char *buf);
char	*ft_strjoin_gnl(char *buf, char *temp);

#endif
