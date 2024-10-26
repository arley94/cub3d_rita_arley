/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:23:20 by ritavasques       #+#    #+#             */
/*   Updated: 2024/10/26 11:18:56 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Find texture [0] and get adress [1]
static int	find_textures(char *line, t_data *data)
{
	char	**textures;
	
	textures = ft_split(line, ' ');
	if (array_len(textures) != 2)
		return (1);
	if (ft_strncmp(textures[0], "NO", 3) == 0)
		data->xpm[0] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "SO", 3) == 0)
		data->xpm[1] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "WE", 3) == 0)
		data->xpm[2] = ft_strdup(textures[1]);
	else if (ft_strncmp(textures[0], "EA", 3) == 0)
		data->xpm[3] = ft_strdup(textures[1]);
	else  if (ft_strncmp(textures[0], "F", 2) && ft_strncmp(textures[0], "C", 2))
		return (1);
	return (0);
}

//find floor/ceiling [0] and get rgb [1]
static int	find_rgb(char *line, t_data *data)
{
	char	**colors;
	
	colors = ft_split(line, ' ');
	if (array_len(colors) != 2)
		return (1);
	
	if (ft_strncmp(colors[0], "F", 1) == 0)
		data->rgb[0] = ft_strdup(colors[1]);
	else if (ft_strncmp(colors[0], "C", 1) == 0)
		data->rgb[1] = ft_strdup(colors[1]);
	free_array(colors);
	return (0);
}

int	check_textures(int fd, t_data *data)
{
	char	*line;
	int		bytesread;

	data->xpm = ft_calloc(sizeof(char *), 5);
	if (!data->xpm)
		return (1);
	
	while (array_len(data->xpm) != 4)
	{
		bytesread = get_next_line(fd, &line);
		if (bytesread < 0)
			return (1);
		if (ft_strlen(line) == 0)
			;
		else if (find_textures(line, data))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

int	get_rgb(int fd, t_data *data)
{
	char	*line;
	int		bytesread;

	data->rgb = ft_calloc(sizeof(char *), 3);
	if (!data->rgb)
		return (1);
	while (array_len(data->rgb) != 2)
	{
		bytesread = get_next_line(fd, &line);
		if (bytesread < 0)
			return (1);
		if (ft_strlen(line) == 0)
			;
		else if (find_rgb(line, data))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

//Textures Array
void get_textures(int i, t_data *data)
{
	int x;
	int y;
	
	y = -1;
	while (++y < data->texture[i].height)
	{
		x = -1;
		while (++x < data->texture[i].width)
		{
			data->textures[i][data->texture[i].height * y + x] = (data->texture[i].addr[data->texture[i].height * y + x]);
		}
	}
}

//Init textures
int	init_textures(t_data *data)
{
	int 	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->xpm[i], &(data->texture[i].width), &(data->texture[i].height));
		if (!data->texture[i].img)
			return (1);
		data->texture[i].addr = (int *) mlx_get_data_addr(data->texture[i].img, &data->texture[i].bits_per_pixel, &data->texture[i].line_lenght, &data->texture[i].endian);
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

void	get_texture_x(t_data *data)
{
	data->text_x = (int)(data->ray.wall_x * (double)TEXTURE_WIDTH);
	if (data->ray.side == 0 && data->ray.dir_x > 0)
		data->text_x = TEXTURE_WIDTH - data->text_x - 1;
	if (data->ray.side == 1 && data->ray.dir_y < 0)
		data->text_x = TEXTURE_WIDTH - data->text_x - 1;
}