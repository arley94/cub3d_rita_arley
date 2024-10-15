/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/15 13:14:04 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**cpy_map(char **map, int size)
{
	int i;
	char	**cpy_map;
	
	i = 0;
	cpy_map = malloc(sizeof(char *) * size);
	if (!cpy_map)
		return (NULL);
	while (map[i])
	{
		cpy_map[i] = map[i];
		i++;
	}
	cpy_map[i] = NULL;
	cpy_map[i + 1] = NULL;
	free(map);
	return(cpy_map);
}

int	map(char *line, t_data *data)
{
	char	**tmp;
	if (!data->map->map)
	{
		data->map->map = malloc(sizeof(char *) * 2);
		if (!data->map->map)
			return(1);
		data->map->map[0] = ft_strdup(line);
		data->map->map[1] = NULL;
	}
	else
	{
		tmp = cpy_map(data->map->map, array_len(data->map->map) + 2);
		if (!tmp)
			return (1);
		data->map->map = tmp;
		data->map->map[array_len(data->map->map)] = ft_strdup(line);
	}
	return (0);
}

int    read_map(int fd, t_data *data)
{
	char	*line;
	int		bytesread;

	while (1)
	{
		bytesread = get_next_line(fd, &line);
		if (bytesread < 0)
			return (1);
		if (ft_strlen(line) == 0 && !data->map->map)
			;
		else if (map(line, data))
		{
			free(line);
			return (1);
		}
		free(line);
		if (bytesread == 0)
			break ;
	}
	return (0);
}

int	check_file(char *file, t_data *data)
{
	int fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_error("Cannot open file!", data);
	}
	if (read_map(fd, data) || check_textures(fd, data))
	{
		close(fd);
		exit_error("File information not correct", data);
	}
	close (fd);
	return (0);
}

//File extencion of map must be .cub
int	check_cub(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c' &&
		str[i - 3] == '.')
		return(1);
	else
		return (0);
}

//Map must be surrounded by walls (spaces are valid)
static int	check_surrounded_walls(int y, int x, t_data *data)
{
	if (data->map->map[y][x] == '0' || (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
	{
		if (y == 0 || !data->map->map[y + 1] || x == 0 || !data->map->map[y][x + 1])
			return (1);
		if (data->map->map[y - 1] && data->map->map[y - 1][x] && data->map->map[y - 1][x] == ' ')
			return (1);
		if (data->map->map[y + 1] && data->map->map[y + 1][x] && data->map->map[y + 1][x] == ' ')
			return (1);
		if (data->map->map[y] && data->map->map[y][x - 1] && data->map->map[y][x - 1] == ' ')
			return (1);
		if (data->map->map[y] && data->map->map[y][x + 1] && data->map->map[y][x + 1] == ' ')
			return (1);
	}
	return (0);
}

// Components 0, 1, N, S, E, W and space.
// Only one player
static int	check_components(t_data *data)
{
	int	y;
	int	x;
	int count;

	y = 0;
	count = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] != '0' && \
			data->map->map[y][x] != '1' && \
			data->map->map[y][x] != 'N' && \
			data->map->map[y][x] != 'S' && \
			data->map->map[y][x] != 'E' && \
			data->map->map[y][x] != 'W' && \
			data->map->map[y][x] != ' ')
			{
				return (1);
			}
			if (data->map->map[y][x] == 'N' || data->map->map[y][x] == 'S' || data->map->map[y][x] == 'W' || data->map->map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	map_end(int index, t_data *data)
{
	int i;
	
	i = index;
	i++;
	while (data->map->map[i])
	{
		if (ft_strlen(data->map->map[i]) > 0)
			return(1);
		i++;
	}
	data->map->map[i] = NULL;
	return (0);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	int x;
	int y;
	
	if (check_components(data) != 1)
		return (1);
	y = 0;
	while (data->map->map[y])
	{
		if (ft_strlen(data->map->map[y]) == 0)
		{
			if (map_end(y, data) == 1)
				return (1);
			break ;
		}
		x = 0;
		while (data->map->map[y][x])
		{
			if (check_surrounded_walls(x, y, data) == 1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
