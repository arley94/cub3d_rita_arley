/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/14 12:00:31 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char    **copy_map(char **map, int size)
{
	int		i;
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
	return (cpy_map);
}

static int	map(char *line, t_data *data)
{
	char	**tmp;

	if (!data->map)
	{
		data->map = malloc(sizeof(char *) * 2);
		if (!data->map)
			return (1);
		data->map[0] = ft_strdup(line);
		data->map[1] = NULL;
	}
	else
	{
		tmp = copy_map(data->map, array_len(data->map) + 2);
		if (!tmp)
			return (1);
		data->map = tmp;
		data->map[array_len(data->map)] = ft_strdup(line);
	}
	return (0);
}

int read_map(int fd, t_data *data)
{
	char	*line;
	int 	bytesread;
	
	while (1)
	{
		bytesread = get_next_line(fd, &line);
		if (bytesread < 0)
			return (1);
		if (ft_strlen(line) == 0 && !data->map)
			;
		else if (map(line, data) == 1)
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

static int map_end(int i, t_data *data)
{
	int x;

	x = i;
	x++;
	while (data->map[x])
	{
		if (ft_strlen(data->map[x]) > 0)
			return (1);
		i++;
	}
	data->map[x] = NULL;
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
static int	check_surrounded_walls(int x, int y, t_data *data)
{
	if (data->map[y][x] == '0' || (data->map[y][x] != '1' && data->map[y][x] != ' '))
	{
		if (y == 0 || !data->map[y + 1] || x == 0 || !data->map[y][x + 1])
			return (1);
		if (data->map[y - 1] && data->map[y - 1][x] && data->map[y - 1][x] == ' ')
			return (1);
		if (data->map[y + 1] && data->map[y + 1][x] && data->map[y + 1][x] == ' ')
			return (1);
		if (data->map[y] && data->map[y][x - 1] && data->map[y][x - 1] == ' ')
			return (1);
		if (data->map[y] && data->map[y][x + 1] && data->map[y][x + 1] == ' ')
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
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (!ft_strchr(" 10NSWE", data->map[y][x]))
				return (0);
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'W' || data->map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	int x;
	int y;
	
	if (check_components(data) != 1)
		return (1);
	y = 0;
	while (data->map[y])
	{
		if (ft_strlen(data->map[y]) == 0)
		{
			if (map_end(y, data) == 1)
				return (1);
			break ;
		}
		x = 0;
		while (data->map[y][x])
		{
			if (check_surrounded_walls(x, y, data) == 1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
