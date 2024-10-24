/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/24 13:03:50 by ritavasques      ###   ########.fr       */
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
		exit_error("Can't open the file.", data);
	}
	if (read_map(fd, data))
	{
		close(fd);
		exit_error("Problems with the file.", data);
	}
	printmap(data);
	if (check_textures(fd, data))
	{
		close(fd);
		exit_error("Problems with the file information.", data);
	}
	close(fd);
	return (0);
}

int	get_map_start(t_data *data)
{
	int	y;
	int start;

	y = 0;
	start = 0;
	while (data->map->map[y])
	{
		if (data->map->map[y][0] == 'N' && data->map->map[y][1] == 'O')
			start++;
		else if (data->map->map[y][0] == 'S' && data->map->map[y][1] == 'O')
			start++;
		else if (data->map->map[y][0] == 'W' && data->map->map[y][1] == 'E')
			start++;
		else if (data->map->map[y][0] == 'E' && data->map->map[y][1] == 'A')
			start++;
		else if (data->map->map[y][0] == 'F')
			start++;
		else if (data->map->map[y][0] == 'C')
			start++;
		else if (data->map->map[y][0] == '\n')
			start++;
		if (data->map->map[y][0] == ' ' || data->map->map[y][0] == '1' || data->map->map[y][0] == '0')
		{
			start = y;
			break ;
		}
		y++;
	}
	return (start);
}

int	get_line_len(int y, t_data *data)
{
	int	x;
	
	x = 0;
	while (data->map->map[y][x] && data->map->map[y][x] != '\n')
		x++;
	return (x);
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
/*static int	check_surrounded_walls(t_data *data)
{
	int	y;
	int	x;
	
	y = data->map->start_y;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '0' || (data->map->map[y][x] != '1' && data->map->map[y][x] != ' '))
			{
				if (y == data->map->map || !data->map->map[y + 1] || x == 0 || !data->map->map[y][x + 1])
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
			x++;
		}
		y++;
	}
	return (0);
}*/

// Only components 0, 1, N, S, E, W and space.
static int	check_components(t_data *data)
{
	int	y;
	int	x;
	
	y = data->map->start_y;
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
				break ;
			}
			x++;
		}
		y++;
	}
	return (0);
}

//Check there's a player and only one
static int	check_player(t_data *data)
{
	int	y;
	int	x;
	int count;

	y = data->map->start_y;
	count = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'N' ||
			data->map->map[y][x] == 'S' ||
			data->map->map[y][x] == 'E' ||
			data->map->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count > 1 || count == 0)
		return (1);
	return (0);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	if (check_components(data))
		return (1);
	if (check_player(data))
		return (1);
	//if (check_surrounded_walls(data))
	//	return (1);
	return (0);
}
