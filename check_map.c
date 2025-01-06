/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/06 13:57:58 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int		is_map(char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isspace(*str) && !ft_strchr("01NSEW", *str))
			return (0);
		str++;
	}
	return (1);
}

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

int	store_map(char *line, t_data *data)
{
	char	**tmp;
	if (!data->map)
	{
		data->map = malloc(sizeof(char *) * 2);
		if (!data->map)
			return(1);
		data->map[0] = ft_strdup(line);
		data->map[1] = NULL;
	}
	else
	{
		tmp = cpy_map(data->map, array_len(data->map) + 2);
		if (!tmp)
			return (1);
		data->map = tmp;
		data->map[array_len(data->map)] = ft_strdup(line);
	}
	return (0);
}

int    parse_map(t_data *data, int *line_nbr)
{

	while (data->cub_text[(*line_nbr)] && !is_map(data->cub_text[(*line_nbr)]))
	{
		(*line_nbr)++;
	}
	if (!data->cub_text[(*line_nbr)])
		return (1);
	while (data->cub_text[(*line_nbr)] && is_map(data->cub_text[(*line_nbr)]))
	{
		store_map(data->cub_text[(*line_nbr)], data);
		(*line_nbr)++;
	}
	return(0);
}

static int all_ellements_are_set(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data->xpm[i] == NULL)
			return (O);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (data->rgb[i] == NULL)
			return (0);
		i++;
	}
	return (1);
}

static int parse_elements_but_map(t_data *data, int * line_nbr)
{
	int	elements_count;

	elements_count = 0;
	while (elements_count < 6 && data->cub_text[++(*line_nbr)])
	{	
		if (!parse_textures(data->cub_text[*line_nbr],  data, &elements_count)
				|| !parse_colors(data->cub_text[*line_nbr],  data, &elements_count))
			continue;
	}
	if (!all_ellements_are_set(data))
		return (1);
	return(0);
}

int	check_file(char *file, t_data *data)
{
	int	fd;
	int line_nbr;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_error("Can't open the file.", data);
	}
	parse_cub(fd, data);
	line_nbr = -1;
	if (parse_cub(fd, data) 
		|| parse_elements_but_map(data, &line_nbr)
		|| parse_map(data, &line_nbr))
	{
		close(fd);
		exit_error("Problems with the file.", data);
	}
	close(fd);
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

// Only components 0, 1, N, S, E, W and space.
static int	check_components(t_data *data)
{
	int	y;
	int	x;
	
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] != '0' && \
			data->map[y][x] != '1' && \
			data->map[y][x] != 'N' && \
			data->map[y][x] != 'S' && \
			data->map[y][x] != 'E' && \
			data->map[y][x] != 'W' && \
			data->map[y][x] != ' ')
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

	y = 0;
	count = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' ||
			data->map[y][x] == 'S' ||
			data->map[y][x] == 'E' ||
			data->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count > 1 || count == 0)
		return (1);
	return (0);
}

int		checkwall(char *str)
{
	while (*str)
	{
		if (*str != '1' && !ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int		check_all_sides(char **strs, int j)
{
	if (ft_isspace(strs[-1][j - 1]) || !strs[-1][j - 1])
		return (0);
	if (ft_isspace(strs[-1][j]) || !strs[-1][j])
		return (0);
	if (ft_isspace(strs[-1][j + 1]) || !strs[-1][j + 1])
		return (0);
	if (ft_isspace(strs[0][j - 1]) || !strs[0][j - 1])
		return (0);
	if (ft_isspace(strs[0][j + 1]) || !strs[0][j + 1])
		return (0);
	if (ft_isspace(strs[1][j - 1]) || !strs[1][j - 1])
		return (0);
	if (ft_isspace(strs[1][j]) || !strs[1][j])
		return (0);
	if (ft_isspace(strs[1][j + 1]) || !strs[1][j + 1])
		return (0);
	return (1);
}

int		checkmapclosed(char **strs)
{
	int j;

	j = 0;
	while (strs[0][j])
	{
		if (ft_strchr("0NSEW", strs[0][j]))
		{
			if (!check_all_sides(strs, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int		check_map_walls(t_data *data)
{
	int		i;
	char	**strs;

	i = -1;
	strs = data->map;
	while (strs[++i])
	{
		if (i == 0 && !checkwall(strs[i]))
			return (1);
		else if (!strs[i + 1] && !checkwall(strs[i]))
			return (1);
		else if (!strs[i + 1] && i < 2)
			return (1);
		else if (!checkmapclosed(&strs[i]))
			return (1);
	}
	return (0);
}

//Check that map rules apply
int	map_ok(t_data *data)
{
	if (check_components(data))
		return (1);
	if (check_player(data))
		return (1);
	if (check_map_walls(data))
		return (1);
	return (0);
}
