/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map _2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 15:30:04 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	all_ellements_are_set(t_data *data)
{
	int	i;

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

int	parse_elements_but_map(t_data *data, int *line_nbr)
{
	int	elements_count;

	elements_count = 0;
	while (elements_count < 6 && data->cub_text[++(*line_nbr)])
	{
		if (!parse_textures(data->cub_text[*line_nbr], data, &elements_count)
			|| !parse_colors(data->cub_text[*line_nbr], data, &elements_count))
			continue ;
	}
	if (!all_ellements_are_set(data))
		return (1);
	return (0);
}

int	check_file(char *file, t_data *data)
{
	int	fd;
	int	line_nbr;

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
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] == 'b' && str[i - 1] == 'u' && str[i - 2] == 'c'
		&& str[i - 3] == '.')
		return (1);
	else
		return (0);
}

// Only components 0, 1, N, S, E, W and space.
int	check_components(t_data *data)
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
