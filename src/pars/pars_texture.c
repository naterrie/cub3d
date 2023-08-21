#include "cub3d.h"

int	check_texture(t_data *data)
{
	int	i;

	i= 0;
	if (!data->NO || !data->SO || !data->WE || !data->EA || !data->F || !data->C)
		return (write(2, "Error : Missing wall\n", 21), 1);
	if (!data->map)
		return (write(2, "Error : Missing map\n", 20), 1);
	while (i < 3)
	{
		if (data->F[i] < 0 || data->F[i] > 255 || data->C[i] < 0 || data->C[i] > 255)
			return (write(2, "Error : Wrong color\n", 21), 1);
		i++;
	}
	return (0);
}

static void	ft_split_atoi(char *s, char c, int t[3])
{
	char	**temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != c)
		i++;
	i++;
	temp = ft_split(s + i, ',');
	while (temp[j])
		j++;
	if (j != 3)
	{
		write(2, "Error : Wrong color\n", 21);
		return ;
	}
	t[0] = ft_atoi(temp[0]);
	t[1] = ft_atoi(temp[1]);
	t[2] = ft_atoi(temp[2]);
	free_str(temp);
}

static int	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1' && line[i] != 'N' \
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_set_map(t_data *data, char **map, char *file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(map[i])
	{
		if (is_map(map[i]))
			break ;
		i++;
	}
	printf("i = %d\n", i);
	if (!map[i])
		return ;
	data->map = malloc(sizeof(char *) * (nbline(file) - i));
	if (!data->map)
		return ;
	while (map[i])
	{
		printf("%s", map[i]);
		data->map[j] = ft_strdup(map[i]);
		i++;
		j++;
	}
	data->map[j] = NULL;
}

void	split_file(char **map, t_data *data, char *file)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O')
			data->NO = get_texture(map[i]);
		else if (map[i][0] == 'S' && map[i][1] == 'O')
			data->SO = get_texture(map[i]);
		else if (map[i][0] == 'W' && map[i][1] == 'E')
			data->WE = get_texture(map[i]);
		else if (map[i][0] == 'E' && map[i][1] == 'A')
			data->EA = get_texture(map[i]);
		else if (map[i][0] == 'F')
			ft_split_atoi(map[i], ' ', data->F);
		else if (map[i][0] == 'C')
			ft_split_atoi(map[i], ' ', data->C);
		i++;
	}
	ft_set_map(data, map, file);
	free_str(map);
}
