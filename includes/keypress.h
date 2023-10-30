/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nibernar <nibernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:17:50 by naterrie          #+#    #+#             */
/*   Updated: 2023/10/29 16:04:57 by nibernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYPRESS_H
# define KEYPRESS_H

enum e_keypress
{
	KP_ERROR = -1,
	KP_UP,
	KP_DOWN,
	KP_LEFT,
	KP_RIGHT,
	K_POV_R,
	K_POV_L,
};

# ifdef __APPLE__

enum e_key
{
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	KEY_ESC = 53,
	KEY_POV_RIGHT = 124,
	KEY_POV_LEFT = 123,
	KEY_MINIMAP = 48,
};
#endif

# ifdef __linux__

enum e_key
{
	KEY_UP = 119,
	KEY_DOWN = 115,
	KEY_RIGHT = 100,
	KEY_LEFT = 97,
	KEY_ESC = 65307,
	KEY_POV_RIGHT = 65363,
	KEY_POV_LEFT = 65361,
	KEY_MINIMAP = 65289,
};
#endif

#endif
