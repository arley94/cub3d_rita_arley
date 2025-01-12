/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:43:19 by acoto-gu          #+#    #+#             */
/*   Updated: 2025/01/12 12:59:34 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_colors(char **element, t_data *data)
{
	if (ft_strncmp(element[0], "C", 3) == 0)
	{
		if (data->rgb[1])
			return (1);
		data->rgb[1] = ft_strdup(element[1]);
	}
	else if (ft_strncmp(element[0], "F", 3) == 0)
	{
		if (data->rgb[0])
			return (1);
		data->rgb[0] = ft_strdup(element[1]);
	}
	else
		return (1);
	return (0);
}

int	parse_elements(char *line, t_data*data)
{
	char			**element;

	element = ft_split(line, ' ');
	if (array_len(element) != 2)
		return (free_array(element), 1);
	if (parse_colors(element, data)
		&& parse_textures_1(element, data)
		&& parse_textures_2(element, data))
	{
		free_array(element);
		return (1);
	}
	free_array(element);
	return (0);
}

char	*ft_trim(char *str)
{
	char	*end;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (ft_strdup(str));
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char)*end))
		end--;
	end[1] = '\0';
	return (ft_strdup(str));
}

int	parse_line_color_texture(const char *line, t_data *data,
								int *elements_count)
{
	char	*tmp_line;

	tmp_line = ft_trim((char *)line);
	if (ft_strlen(tmp_line) == 0)
		return (free(tmp_line), 0);
	if (parse_elements(tmp_line, data))
	{
		free(tmp_line);
		return (1);
	}
	free(tmp_line);
	(*elements_count)++;
	return (0);
}
