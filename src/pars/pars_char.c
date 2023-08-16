#include "cub3d.h"

int	check_start(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				i++;
			j++;
		}
		i++;
	}
	return (i);
}

int	check_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N' \
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W' \
				&& map[i][j] != ' ' && map[i][j] != 10 && map[i][j] != 13)
				{
					printf("Error\nWrong character in map\n");
					return (1);
				}
			j++;
		}
		i++;
	}
	return (0);
}
