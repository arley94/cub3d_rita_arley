/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:23:20 by ritavasques       #+#    #+#             */
/*   Updated: 2025/01/12 12:53:03 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_textures_1(char **element, t_data *data)
{
	if (ft_strncmp(element[0], "NO", 4) == 0)
	{
		if (data->xpm[0])
			return (1);
		data->xpm[0] = ft_strdup(element[1]);
	}
	else if (ft_strncmp(element[0], "SO", 4) == 0)
	{
		if (data->xpm[1])
			return (1);
		data->xpm[1] = ft_strdup(element[1]);
	}
	else
		return (1);
	return (0);
}

int	parse_textures_2(char **element, t_data *data)
{
	if (ft_strncmp(element[0], "WE", 4) == 0)
	{
		if (data->xpm[2])
			return (1);
		data->xpm[2] = ft_strdup(element[1]);
	}
	else if (ft_strncmp(element[0], "EA", 4) == 0)
	{
		if (data->xpm[3])
			return (1);
		data->xpm[3] = ft_strdup(element[1]);
	}
	else
		return (1);
	return (0);
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
