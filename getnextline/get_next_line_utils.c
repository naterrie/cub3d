/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:07:30 by naterrie          #+#    #+#             */
/*   Updated: 2022/12/06 15:59:19 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while(s[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (!c)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *buf, char *temp)
{
	int		i;
	int		j;
	char	*str;

	if (!buf)
	{
		buf = malloc(sizeof(char) * 1);
		if (!buf)
			return (NULL);
		buf[0] = '\0';
	}
	if (!temp)
		return (free(buf = NULL), NULL);
	str = malloc(sizeof(char) * (ft_len(buf) + ft_len(temp) + 1));
	if (!str)
		return (free(buf), NULL);
	i = -1;
	j = 0;
	while (buf[++i])
		str[i] = buf[i];
	while (temp[j] != '\0')
		str[i++] = temp[j++];
	str[i] = '\0';
	return (free(buf), str);
}
