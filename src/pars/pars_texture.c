#include "cub3d.h"

int	check_texture(t_data *data)
{
	int	i;

	i= 0;
	if (!data->NO || !data->SO || !data->WE || !data->EA || !data->F || !data->C)
		return (write(2, "Error : Missing wall\n", 21), 1);
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
}

static int	get_map_pos(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O')
			j++;
		else if (map[i][0] == 'W' && map[i][1] == 'E')
			j++;
		else if (map[i][0] == 'E' && map[i][1] == 'A')
			j++;
		else if (map[i][0] == 'S' && map[i][1] == 'O')
			j++;
		else if (map[i][0] == 'F')
			j++;
		else if (map[i][0] == 'C')
			j++;
		if (j == 6)
			break;
		i++;
	}
	return (i);
}

void	ft_set_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = get_map_pos(map);
	while (ft_strlen(map[i]) == 0 && map[i])
		i++;
	data->map = malloc(sizeof(char *) * (i + 1));
	if (!data->map)
		return ;
	while(map[i])
	{
		data->map[j] = map[i];
		i++;
		j++;
	}
}

void	split_file(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'N' && map[i][1] == 'O')
			data->NO = ft_split(map[i], ' ')[1];
		else if (map[i][0] == 'S' && map[i][1] == 'O')
			data->SO = ft_split(map[i], ' ')[1];
		else if (map[i][0] == 'W' && map[i][1] == 'E')
			data->WE = ft_split(map[i], ' ')[1];
		else if (map[i][0] == 'E' && map[i][1] == 'A')
			data->EA = ft_split(map[i], ' ')[1];
		else if (map[i][0] == 'F')
			ft_split_atoi(map[i], ' ', data->F);
		else if (map[i][0] == 'C')
			ft_split_atoi(map[i], ' ', data->C);
		i++;
	}
	ft_set_map(data, map);
	free_str(map);
}
