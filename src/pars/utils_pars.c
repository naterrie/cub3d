#include "cub3d.h"

int	nbline(char *file)
{
	int		line;
	int		fd;
	char	*temp;

	line = 0;
	fd = open(file, O_RDONLY);
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == 0)
			break ;
		free (temp);
		line++;
	}
	close(fd);
	return (line + 1);
}

void	free_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**get_map(char *file)
{
	char	**map;
	int		i;
	int		fd;
	int		line;
	char	*temp;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (write (2, "Error, wrong file\n", 18), NULL);
	line = nbline(file);
	map = malloc(sizeof(char *) * line);
	if (!map)
		return (NULL);
	while (i < line)
	{
		temp = get_next_line(fd);
		map[i] = temp;
		i++;
	}
	close(fd);
	free (temp);
	return (map);
}
