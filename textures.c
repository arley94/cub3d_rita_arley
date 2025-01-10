/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:23:20 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/10 16:04:23 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_textures(char *line, t_data *data, int *count)
{
	char			**textures;
	unsigned char	is_valid_texture;

	is_valid_texture = 1;
	textures = ft_split(line, ' ');
	if (array_len(textures) != 2)
		return (free_array(textures), 1);
	if (ft_strncmp(textures[0], "NO", 3) == 0)
		data->xpm[0] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "SO", 3) == 0)
		data->xpm[1] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "WE", 3) == 0)
		data->xpm[2] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "EA", 3) == 0)
		data->xpm[3] = ft_strdup(textures[1]);
	else
		is_valid_texture = 0;
	free_array(textures);
	if (is_valid_texture)
		return ((*count)++, 0);
	return (1);
}

int	parse_colors(char *line, t_data *data, int *count)
{
	char			**colors;
	unsigned char	is_valid_color;

	is_valid_color = 1;
	colors = ft_split(line, ' ');
	if (array_len(colors) != 2)
		return (free_array(colors), 1);
	if (ft_strncmp(colors[0], "F", 2) == 0)
		data->rgb[0] = ft_strdup(colors[1]);
	else if (ft_strncmp(colors[0], "C", 2) == 0)
		data->rgb[1] = ft_strdup(colors[1]);
	else
		is_valid_color = 0;
	free_array(colors);
	if (is_valid_color)
		return ((*count)++, 0);
	return (1);
}

//Textures Array
void	get_textures(int i, t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->texture[i].height)
	{
		x = -1;
		while (++x < data->texture[i].width)
		{
			data->textures[i][data->texture[i].height * y + x]
				= (data->texture[i].addr[data->texture[i].height * y + x]);
		}
	}
}

//Init textures
int	init_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->xpm[i],
				&(data->texture[i].width), &(data->texture[i].height));
		if (!data->texture[i].img)
			return (1);
		data->texture[i].addr = (int *) mlx_get_data_addr(data->texture[i].img,
				&data->texture[i].bits_per_pixel, &data->texture[i].line_lenght,
				&data->texture[i].endian);
		if (!data->texture[i].addr)
			return (1);
		get_textures(i, data);
		mlx_destroy_image(data->mlx, data->texture[i].img);
		i++;	
	}
	return (0);
}

void	set_texture(t_data *data)
{
	if (data->ray.side == 0)
	{
		if (data->ray.map_x > data->player.x)
			data->text_number = 1;
		else
			data->text_number = 3;
	}
	else
	{
		if (data->ray.map_y > data->player.y)
			data->text_number = 2;
		else
			data->text_number = 0;
	}
}
