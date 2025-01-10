/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:38:52 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 14:56:57 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	is_map(char *str)
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

int	store_map(char *line, t_data *data)
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
		tmp = cpy_map(data->map, array_len(data->map) + 2);
		if (!tmp)
			return (1);
		data->map = tmp;
		data->map[array_len(data->map)] = ft_strdup(line);
	}
	return (0);
}

int	parse_map(t_data *data, int *line_nbr)
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
	return (0);
}
