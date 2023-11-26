/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:54:51 by nibernar          #+#    #+#             */
/*   Updated: 2023/10/29 16:08:43 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

enum e_decor
{
	WALL = '1',
	EMPTY = '0',
};

struct s_pos
{
	double	x;
	double	y;
};

struct s_int
{
	int	x;
	int	y;
};

enum e_bool
{
	FALSE,
	TRUE,
};
#endif