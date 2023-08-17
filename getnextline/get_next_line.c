/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naterrie <naterrie@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:07:31 by naterrie          #+#    #+#             */
/*   Updated: 2022/12/06 16:25:03 by naterrie         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *buf)
{
	int		i;
	char	*str;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i])
		str = malloc(sizeof(char) * (i + 2));
	else
		str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (buf[++i] && buf[i] != '\n')
		str[i] = buf[i];
	if (buf[i] == '\n')
	{
		str[i] = buf[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_next_buf(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	j = 0;
	if (!buf[i])
		return (free(buf), NULL);
	str = malloc(sizeof(char) * (ft_len(buf) - i));
	if (!str)
		return (free(buf), NULL);
	i++;
	while (buf[i])
		str[j++] = buf[i++];
	str[j] = '\0';
	return (free(buf), str);
}

char	*ft_read_line(int fd, char *buf)
{
	char	*temp;
	int		bytes;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (free(buf), buf = NULL, NULL);
	bytes = 1;
	while (!gnl_strchr(buf, '\n') && bytes != 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buf), free(temp), NULL);
		temp[bytes] = '\0';
		buf = ft_strjoin_gnl(buf, temp);
	}
	return (free(temp), buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	buf = ft_read_line(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_get_line(buf);
	if (!line)
		return (free(buf), buf = NULL, buf);
	buf = ft_next_buf(buf);
	if (!buf)
		return (free(buf), buf = NULL, line);
	return (line);
}
